#ifndef READERSCENARIO_H
#define READERSCENARIO_H

#include "ScenarioData.h"
#include "PageData.h"

#include <string>

using namespace std;

class ReaderScenario
{
    public:
        ReaderScenario();
        virtual ~ReaderScenario();
        static ReaderScenario* Instance()
        {
            if (ReaderScenario::m_instance == nullptr)
            {
                ReaderScenario::m_instance = new ReaderScenario();
            }
            return ReaderScenario::m_instance;
        }

        void start();
        void update();
        void changePage(PageData* newPage);
        void resetText();
        void setText(string _text);
        void setSprite(string _sprite);
        void changeMusic(string _music);
        void changeFX(string _FX);
        void setUp(string _text);
        void setDown(string _text);
        void setRight(string _text);
        void setLeft(string _text);
        void setButton(string _text);

    protected:
    private:
        static ReaderScenario* m_instance;

        ScenarioData* m_scenario;
        PageData* m_page;
        string m_text;
        string m_sprite;
        string m_music;
        string m_FX;
        string m_inputUp;
        string m_inputDown;
        string m_inputRight;
        string m_inputLeft;
        string m_button;
};

#endif // READERSCENARIO_H
