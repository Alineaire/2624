#include "ReaderScenario.h"
#include "LocalisationManager.h"

ReaderScenario::ReaderScenario()
{
    m_page = nullptr;
}

ReaderScenario::~ReaderScenario()
{
}

void ReaderScenario::start(rgb_matrix::RGBMatrix* _matrix, rgb_matrix::FrameCanvas* _offscreen, rgb_matrix::Font* _font, ScenarioData* _scenario)
{
    m_matrix = _matrix;
    m_offscreen = _offscreen;
    m_font = _font;
    m_scenario = _scenario;
    changePage(m_scenario->m_pages.begin()->second);
}

void ReaderScenario::update()
{
    if (m_page != nullptr)
        m_page->update(m_matrix, m_font);
}

void ReaderScenario::changePage(PageData* newPage)
{
    if (m_page != nullptr)
        m_page->unload();
    m_page = newPage;
    m_page->read();
}

void ReaderScenario::setSprite(string _sprite)
{
    m_sprite = _sprite;
}
void ReaderScenario::setColor(int _red, int _green, int _blue)
{
    m_red = _red;
    m_green = _green;
    m_blue = _blue;
}
void ReaderScenario::setBrightness(int _brightness)
{
    m_brightness = _brightness;
    m_matrix->SetBrightness(m_brightness);
}
