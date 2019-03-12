#include "ReaderScenario.h"

ReaderScenario::ReaderScenario()
{
    //ctor
}

ReaderScenario::~ReaderScenario()
{
    //dtor
}

void ReaderScenario::start()
{
    changePage(&(*(m_scenario->m_pages.begin())));
}

void ReaderScenario::update()
{
    if (m_page != nullptr)
        m_page->update();
}

void ReaderScenario::changePage(PageData* newPage)
{
    resetText();
    if (m_page != nullptr)
        m_page->unload();
    m_page = newPage;
    m_page->read();
}

void ReaderScenario::resetText()
{
    setText("");
    setUp("");
    setDown("");
    setRight("");
    setLeft("");
    setButton("");
}

void ReaderScenario::setText(string _text)
{
    m_text = _text;
}

void ReaderScenario::setSprite(string _sprite)
{
    m_sprite = _sprite;
}
void ReaderScenario::changeMusic(string _music)
{
    m_music = _music;
}
void ReaderScenario::changeFX(string _FX)
{
    m_FX = _FX;
}

void ReaderScenario::setUp(string _text)
{
    m_inputUp = _text;
}
void ReaderScenario::setDown(string _text)
{
    m_inputDown = _text;
}
void ReaderScenario::setRight(string _text)
{
    m_inputRight = _text;
}
void ReaderScenario::setLeft(string _text)
{
    m_inputLeft = _text;
}
void ReaderScenario::setButton(string _text)
{
    m_button = _text;
}
