#ifndef TEXT_H
#define TEXT_H

#include "graphics.h"

#include <vector>

using namespace std;

class Character
{
    public:
        Character();
        Character(char _value, bool _isBlinking = false, int _r = -1, int _g = -1, int _b = -1);
        virtual ~Character();
        void update(rgb_matrix::Canvas* _matrix, rgb_matrix::Font* _font, bool _displayBlink, int& _posXDisplay, int& _posYDisplay);
        bool isBlinking() { return m_isBlinking; }
        int getUnicodeCharacter(bool _displayBlink);

    protected:
    private:
        char m_value;
        bool m_isBlinking;
        rgb_matrix::Color m_color;
};

class Text
{
    public:
        Text(string _idText = "", int _r = -1, int _g = -1, int _b = -1);
        virtual ~Text();
        void parse();
        bool haveBlinker();
        void update(bool _displayBlink = true);

        string m_idText;

    protected:
    private:
        rgb_matrix::Color m_color;
        vector<Character> m_characters;
};

#endif // TEXT_H
