#include "Text.h"
#include "LocalisationManager.h"
#include "ReaderScenario.h"
#include "Time.h"
#include "utils.h"

#include <math.h>
#include <string>

#define BLINKDISPLAY 0.5f
#define BLINKHIDE 0.25f
#define BLINKINGTIME (BLINKDISPLAY + BLINKHIDE)

using namespace std;

Character::Character()
{
}
Character::Character(char _value, bool _isBlinking, int _r, int _g, int _b)
{
    m_value = _value;
    m_isBlinking = _isBlinking;
    m_color.r = _r;
    m_color.g = _g;
    m_color.b = _b;
}
Character::~Character()
{
}
void Character::update(rgb_matrix::Canvas* _matrix, rgb_matrix::Font* _font, bool _displayBlink, int& _posXDisplay, int& _posYDisplay)
{
    char valueToDisplay = ' ';
    if (!m_isBlinking || (m_isBlinking && _displayBlink))
    {
        valueToDisplay = m_value;
    }
    _posXDisplay += rgb_matrix::DrawText(_matrix, *_font, _posXDisplay, _posYDisplay + _font->baseline(), m_color, &valueToDisplay);
}
int Character::getUnicodeCharacter(bool _displayBlink)
{
    if (!m_isBlinking || (m_isBlinking && _displayBlink))
    {
        return atoi(&m_value);
    }
    return 32; //space
}

Text::Text(string _idText)
{
    m_idText = _idText;
}
Text::~Text()
{
}
void Text::init()
{
    parse();
    startingTime = Time::Instance()->ActualTime();
}
void Text::parse()
{
    string text = LocalisationManager::Instance()->getLoc(m_idText);

    vector<int> r, g, b;
    r.push_back(ReaderScenario::Instance()->getRed());
    g.push_back(ReaderScenario::Instance()->getGreen());
    b.push_back(ReaderScenario::Instance()->getBlue());
    bool blink = false;

    m_characters.clear();
    unsigned int index = 0;
    center = false;
    if (text.find("<center>", index) != std::string::npos)
    {
        center = true;
        index = text.find(">", index)+1;
    }
    while (index < text.length())
    {
        char character = text[index];
        if (character == '<')
        {
            std::size_t foundBlink = text.find("blink", index);
            std::size_t foundColor = text.find("color", index);

            // blink
            if (foundBlink != std::string::npos && foundBlink <= index+2 &&
                (foundColor == std::string::npos || (foundColor != std::string::npos && foundBlink < foundColor)))
            {
                blink = foundBlink == index+1;
                index = text.find(">", index)+1;
                continue;
            }

            // color
            if (foundColor != std::string::npos && foundColor <= index+2 &&
                (foundBlink == std::string::npos || (foundBlink != std::string::npos && foundColor < foundBlink)))
            {
                bool startNewColor = foundColor == index+1;
                if (startNewColor)
                {
                    int startColor = text.find("=", index)+1;
                    int endColor = text.find(">", startColor);
                    string color = text.substr(startColor, endColor-startColor);
                    vector<string> colors = split(color, ',');
                    if (colors.size() == 3)
                    {
                        r.push_back(stoi(colors[0]));
                        g.push_back(stoi(colors[1]));
                        b.push_back(stoi(colors[2]));
                    }
                    index = endColor+1;
                }
                else
                {
                    r.pop_back(); g.pop_back(); b.pop_back();
                    index = text.find(">", index)+1;
                }
                continue;
            }

            // nothing it's the character '<'
        }
        if (index > 1 && text[index-1] == '$' && character == ' ')
        {
            ++index;
            continue;
        }

        // add character
        m_characters.push_back(Character(character, blink, r.back(), g.back(), b.back()));
        ++index;
    }
}
bool Text::haveBlinker()
{
    for (vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it)
    {
        if (it->isBlinking())
            return true;
    }
    return false;
}
void Text::update()
{
    rgb_matrix::Canvas* matrix = ReaderScenario::Instance()->getOffscreen();
    rgb_matrix::Font* font = ReaderScenario::Instance()->getFont();
    int fontWidth = ReaderScenario::Instance()->getFontWidth();
    int i = 0, x = calculateOffsetCenter(0), y = 0;
    bool blink = fmod(Time::Instance()->ActualTime() - startingTime, BLINKINGTIME) <= BLINKDISPLAY;
    for (vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it, ++i)
    {
        bool returnCharacter = it->getCharacter() == '$';
        if (returnCharacter || x + fontWidth > matrix->width())
        {
            x = calculateOffsetCenter(i+1);
            y = font->height();
        }
        if (!returnCharacter)
            it->update(matrix, font, blink, x, y);
    }
}
int Text::sizeLine(int indexCharacter)
{
    rgb_matrix::Canvas* matrix = ReaderScenario::Instance()->getOffscreen();
    int fontWidth = ReaderScenario::Instance()->getFontWidth();
    int actualSizeLine = 0;
    for (unsigned int i = indexCharacter; i < m_characters.size(); ++i)
    {
        bool returnCharacter = m_characters[i].getCharacter() == '$';
        if (returnCharacter || actualSizeLine + fontWidth > matrix->width())
            break;
        actualSizeLine += fontWidth;
    }
    return actualSizeLine;
}
int Text::calculateOffsetCenter(int indexCharacter)
{
    if (!center)
        return 0;
    rgb_matrix::Canvas* matrix = ReaderScenario::Instance()->getOffscreen();
    return (matrix->width() - sizeLine(indexCharacter)) / 2.0f;
}
