#include "Text.h"
#include "LocalisationManager.h"
#include "ReaderScenario.h"
#include "utils.h"

#include <string>

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

Text::Text(string _idText, int _r, int _g, int _b)
{
    m_idText = _idText;
    m_color.r = _r;
    m_color.g = _g;
    m_color.b = _b;
}
Text::~Text()
{
}
void Text::parse()
{
    string text = LocalisationManager::Instance()->getLoc(m_idText);

    vector<int> r, g, b;
    r.push_back(ReaderScenario::Instance()->getRed());
    g.push_back(ReaderScenario::Instance()->getGreen());
    b.push_back(ReaderScenario::Instance()->getBlue());
    bool blink = false;

    unsigned int index = 0;
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
                index = text.find(">", index);
                continue;
            }

            // color
            if (foundColor != std::string::npos && foundColor <= index+2 &&
                (foundBlink == std::string::npos || (foundBlink != std::string::npos && foundColor < foundBlink)))
            {
                bool startNewColor = foundColor == index+1;
                if (startNewColor)
                {
                    int startColor = text.find("=", index);
                    int endColor = text.find(">", startColor);
                    string color = text.substr(startColor, endColor-startColor);
                    vector<string> colors = split(color, ',');
                    if (colors.size() == 3)
                    {
                        r.push_back(stoi(colors[0]));
                        g.push_back(stoi(colors[1]));
                        b.push_back(stoi(colors[2]));
                    }
                    index = endColor;
                }
                else
                {
                    r.pop_back(); g.pop_back(); b.pop_back();
                    index = text.find(">", index);
                }
                continue;
            }

            // nothing it's the character '<'
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
void Text::update(bool _displayBlink)
{
    rgb_matrix::Canvas* matrix = ReaderScenario::Instance()->getMatrix();
    rgb_matrix::Font* font = ReaderScenario::Instance()->getFont();
    int x = 0, y = 0;
    for (vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it)
    {
        if (x + font->CharacterWidth(it->getUnicodeCharacter(_displayBlink)) > matrix->width())
        {
            x = 0;
            y = font->height();
        }
        it->update(matrix, font, _displayBlink, x, y);
    }
}
