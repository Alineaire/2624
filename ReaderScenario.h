#ifndef READERSCENARIO_H
#define READERSCENARIO_H

#include "ScenarioData.h"
#include "PageData.h"

#include "graphics.h"

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

        void start(rgb_matrix::Canvas* _matrix, rgb_matrix::Font* _font, ScenarioData* _scenario);
        void update();
        void changePage(PageData* newPage);
        void setSprite(string _sprite);
        void changeMusic(string _music);
        void changeFX(string _FX);
        void setColor(int _red, int _green, int _blue);
        void setBrightness(int _brightness);

        ScenarioData* getScenarioData() { return m_scenario; }
        rgb_matrix::Canvas* getMatrix() { return m_matrix; }
        rgb_matrix::Font* getFont() { return m_font; }
        int getRed() { return m_red; }
        int getGreen() { return m_green; }
        int getBlue() { return m_blue; }


    protected:
    private:
        void parseScenario(string& _pathScenario, string& _pathLoc);

        static ReaderScenario* m_instance;
        ScenarioData* m_scenario;
        PageData* m_page;
        string m_sprite;
        string m_music;
        string m_FX;
        int m_red;
        int m_green;
        int m_blue;
        int m_brightness;
        rgb_matrix::Canvas* m_matrix;
        rgb_matrix::Font* m_font;
};

#endif // READERSCENARIO_H
