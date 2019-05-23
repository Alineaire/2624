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
        char getCharacter() { return m_value; }
        int getUnicodeCharacter(bool _displayBlink = true);

    protected:
    private:
        char m_value;
        bool m_isBlinking;
        rgb_matrix::Color m_color;
};

class Text
{
    public:
        Text(string _idText = "");
        virtual ~Text();
        void init();
        bool haveBlinker();
        void update();

        string m_idText;

    protected:
    private:
        vector<Character> m_characters;
        float startingTime;
        bool center;

        void parse();
        int sizeLine(int indexCharacter = 0);
        int calculateOffsetCenter(int indexCharacter = 0);
};

#endif // TEXT_H
