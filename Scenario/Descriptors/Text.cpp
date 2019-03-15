#include "Text.h"
#include "LocalisationManager.h"
#include "ReaderScenario.h"

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
    string valueToDisplay = " ";
    if (!m_isBlinking || (m_isBlinking && _displayBlink))
    {
        valueToDisplay = m_value;
    }
    _posXDisplay += rgb_matrix::DrawText(_matrix, *_font, _posXDisplay, _posYDisplay + _font->baseline(), m_color, valueToDisplay.c_str());
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
    for (unsigned int i = 0; i < text.length(); ++i)
    {
        m_characters.push_back(Character(text[i], false, 255, 255, 255));
    }
}
bool Text::haveBlinker()
{
    for (vector<Character>::iterator it = m_characters.begin(); it != m_characters.end(); ++it)
    {
        if ((*it).isBlinking())
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
        if (x > matrix->width())
        {
          x = 0;
          y = font->height();
        }
        (*it).update(matrix, font, _displayBlink, x, y);
    }
}
