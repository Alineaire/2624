#include "DescriptorData.h"
#include "ReaderScenario.h"

IDescriptorData::IDescriptorData()
{
    //ctor
}

IDescriptorData::~IDescriptorData()
{
    //dtor
}

void SoundDescriptorData::read()
{
    this->IDescriptorData::read();

    ReaderScenario::Instance()->changeFX(m_sound);
}

void SoundDescriptorData::unload()
{
    this->IDescriptorData::unload();

    ReaderScenario::Instance()->changeFX(nullptr);
}

void MusicDescriptorData::read()
{
    this->IDescriptorData::read();

    ReaderScenario::Instance()->changeMusic(m_sound);
}

void MusicDescriptorData::unload()
{
    this->IDescriptorData::unload();

    ReaderScenario::Instance()->changeMusic(nullptr);
}

void TextDescriptorData::read()
{
    this->IDescriptorData::read();

    string formatText = m_text;
    //formatText = formatText.Replace("\\n", "\n");
    //formatText = formatText.Replace("\n ", "\n");
    ReaderScenario::Instance()->setText(formatText);
}

void ImageDescriptorData::read()
{
    this->IDescriptorData::read();

    ReaderScenario::Instance()->setSprite(m_sprite);
}

void ImageDescriptorData::unload()
{
    this->IDescriptorData::unload();

    ReaderScenario::Instance()->setSprite(nullptr);
}
