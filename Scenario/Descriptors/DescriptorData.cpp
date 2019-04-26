#include "DescriptorData.h"
#include "ReaderScenario.h"
#include "SoundManager.h"
#include "TagsManager.h"
#include "utils.h"

#include <stdlib.h>

IDescriptorData::IDescriptorData()
{
}

void BoolTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void BoolTagModifierDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, "=");
        if (content.size() == 2)
        {
            BoolTagModifierDescriptorData* data = new BoolTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addBoolTag(content[0]);
            data->m_action = ChangeBool::affect;
            data->m_value = (content[1] == "true" ? true : false);
            _descriptors.push_back(data);
            continue;
        }
        if ((*it).find("!") != string::npos)
        {
            BoolTagModifierDescriptorData* data = new BoolTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addBoolTag(content[0]);
            data->m_action = ChangeBool::reverse;
            _descriptors.push_back(data);
            continue;
        }
    }
}
void IntTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void IntTagModifierDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, "+=");
        if (content.size() == 2)
        {
            IntTagModifierDescriptorData* data = new IntTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = ChangeInt::increment;
            data->m_value = stoi(content[1]);
            _descriptors.push_back(data);
            continue;
        }
        content = split(*it, "-=");
        if (content.size() == 2)
        {
            IntTagModifierDescriptorData* data = new IntTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = ChangeInt::decrement;
            data->m_value = stoi(content[1]);
            _descriptors.push_back(data);
            continue;
        }
        content = split(*it, '=');
        if (content.size() == 2)
        {
            IntTagModifierDescriptorData* data = new IntTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = ChangeInt::affect;
            data->m_value = stoi(content[1]);
            _descriptors.push_back(data);
            continue;
        }
    }
}
void StringTagModifierDescriptorData::read()
{
    m_data->doAction(m_action, m_value);
}
void StringTagModifierDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, "=");
        if (content.size() == 2)
        {
            StringTagModifierDescriptorData* data = new StringTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addStringTag(content[0]);
            data->m_action = ChangeString::affect;
            data->m_value = content[1];
            _descriptors.push_back(data);
            continue;
        }
    }
}

void SFXDescriptorData::read()
{
    if (m_sounds.size() > 0)
    {
        int index = rand() % m_sounds.size();
        SoundManager::Instance()->playSFX(m_sounds[index]);
    }
}
void SFXDescriptorData::unload()
{
}
void SFXDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    SFXDescriptorData* data = new SFXDescriptorData();
    if (!endWith(_text, "/"))
        data->m_sounds.push_back(_text);
    else
        getFilesLocation(_text, data->m_sounds, ".wav");

    // load
    for (vector<string>::iterator it = data->m_sounds.begin(); it != data->m_sounds.end(); ++it)
        SoundManager::Instance()->loadSFX(*it);

    _descriptors.push_back(data);
}

void MusicDescriptorData::read()
{
    if (m_sounds.size() > 0)
    {
        int index = rand() % m_sounds.size();
        SoundManager::Instance()->playMusic(m_sounds[index], m_fade);
    }
}
void MusicDescriptorData::unload()
{
}
void MusicDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    MusicDescriptorData* data = new MusicDescriptorData();
    vector<string> content = split(_text, '#');
    data->m_fade = (content.size() > 1 ? stof(content[1]) * 1000.0f : 0.0f);
    if (!endWith(content[0], "/"))
        data->m_sounds.push_back(content[0]);
    else
        getFilesLocation(content[0], data->m_sounds, ".wav");

    // load
    for (vector<string>::iterator it = data->m_sounds.begin(); it != data->m_sounds.end(); ++it)
        SoundManager::Instance()->loadMusic(*it);

    _descriptors.push_back(data);
}

void TextDescriptorData::read()
{
    m_text.parse();
    //if (!m_text.haveBlinker())
    //    m_text.update();
}
void TextDescriptorData::unload()
{
}
void TextDescriptorData::update()
{
    //if (m_text.haveBlinker())
        m_text.update();
}
void TextDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _idText)
{
    TextDescriptorData* data = new TextDescriptorData();
    data->m_text.m_idText = _idText;
    _descriptors.push_back(data);
}

void SpriteDescriptorData::read()
{
    ReaderScenario::Instance()->setSprite(m_sprite); //TODO
}
void SpriteDescriptorData::unload()
{
    ReaderScenario::Instance()->getMatrix()->Clear();
}
void SpriteDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    SpriteDescriptorData* data = new SpriteDescriptorData();
    data->m_sprite = _text;
    _descriptors.push_back(data);
}

void ColorDescriptorData::read()
{
    ReaderScenario::Instance()->setColor(m_red, m_green, m_blue);
}
void ColorDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    ColorDescriptorData* data = new ColorDescriptorData();
    vector<string> colors = split(_text, ',');
    if (colors.size() == 3)
    {
        data->m_red = stoi(colors[0]);
        data->m_green = stoi(colors[1]);
        data->m_blue = stoi(colors[2]);
    }
    _descriptors.push_back(data);
}

void BrightnessDescriptorData::read()
{
    ReaderScenario::Instance()->setBrightness(m_brightness);
}
void BrightnessDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    BrightnessDescriptorData* data = new BrightnessDescriptorData();
    data->m_brightness = stoi(_text);
    _descriptors.push_back(data);
}

void ArduinoDescriptorData::read()
{
    //TODO
}
void ArduinoDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    ArduinoDescriptorData* data = new ArduinoDescriptorData();
    data->m_text = _text;
    _descriptors.push_back(data);
}
