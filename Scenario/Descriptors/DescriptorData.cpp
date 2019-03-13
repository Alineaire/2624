#include "DescriptorData.h"
#include "ReaderScenario.h"
#include "utils.h"

IDescriptorData::IDescriptorData()
{
    //ctor
}

void BoolTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void BoolTagModifierDescriptorData::parse(string _text)
{
    m_value = (_text == "true" ? true : false);
}
void IntTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void IntTagModifierDescriptorData::parse(string _text)
{
    m_value = stoi(_text);
}
void StringTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void StringTagModifierDescriptorData::parse(string _text)
{
    m_value = _text;
}

void SFXDescriptorData::read()
{
    ReaderScenario::Instance()->changeFX(m_sound);
}
void SFXDescriptorData::unload()
{
    ReaderScenario::Instance()->changeFX(nullptr);
}
void SFXDescriptorData::parse(string _text)
{
    m_sound = _text;
}

void MusicDescriptorData::read()
{
    ReaderScenario::Instance()->changeMusic(m_sound);
}
void MusicDescriptorData::unload()
{
    ReaderScenario::Instance()->changeMusic(nullptr);
}
void MusicDescriptorData::parse(string _text)
{
    m_sound = _text;
}

void TextDescriptorData::read()
{
    string formatText = m_text;
    //formatText = formatText.Replace("\\n", "\n");
    //formatText = formatText.Replace("\n ", "\n");
    ReaderScenario::Instance()->setText(formatText);
}
void TextDescriptorData::parse(string _text)
{
    m_text = _text;
}

void SpriteDescriptorData::read()
{
    ReaderScenario::Instance()->setSprite(m_sprite);
}
void SpriteDescriptorData::unload()
{
    ReaderScenario::Instance()->setSprite(nullptr);
}
void SpriteDescriptorData::parse(string _text)
{
    m_sprite = _text;
}

void ColorDescriptorData::read()
{
    ReaderScenario::Instance()->setColor(m_red, m_green, m_blue);
}
void ColorDescriptorData::parse(string _text)
{
    vector<string> colors = split(_text, ',');
    if (colors.size() < 2)
        return;
    m_red = stoi(colors[0]);
    m_green = stoi(colors[1]);
    m_blue = stoi(colors[2]);
}

void BrightnessDescriptorData::read()
{
    ReaderScenario::Instance()->setBrightness(m_brightness);
}
void BrightnessDescriptorData::parse(string _text)
{
    m_brightness = stoi(_text);
}

void ArduinoDescriptorData::read()
{
    //TODO
}
void ArduinoDescriptorData::parse(string _text)
{
    m_text = _text;
}
