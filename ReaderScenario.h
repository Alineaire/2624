#ifndef READERSCENARIO_H
#define READERSCENARIO_H

#include "ScenarioData.h"
#include "PageData.h"

#include "graphics.h"
#include "led-matrix.h"

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

        void start(rgb_matrix::RGBMatrix* _matrix, rgb_matrix::FrameCanvas* _offscreen, rgb_matrix::Font* _font, ScenarioData* _scenario);
        void update();
        void changePage(PageData* newPage);
        void setSprite(string _sprite);
        void setColor(int _red, int _green, int _blue);
        void setBrightness(int _brightness);

        ScenarioData* getScenarioData() { return m_scenario; }
        rgb_matrix::RGBMatrix* getMatrix() { return m_matrix; }
        rgb_matrix::FrameCanvas* getOffscreen() { return m_offscreen; }
        void setOffscreen(rgb_matrix::FrameCanvas* _offscreen) { m_offscreen = _offscreen; }
        rgb_matrix::Font* getFont() { return m_font; }
        int getFontWidth() { return m_font->CharacterWidth(32); } //space
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
        int m_red;
        int m_green;
        int m_blue;
        int m_brightness;
        rgb_matrix::RGBMatrix* m_matrix;
        rgb_matrix::FrameCanvas* m_offscreen;
        rgb_matrix::Font* m_font;
};

#endif // READERSCENARIO_H
