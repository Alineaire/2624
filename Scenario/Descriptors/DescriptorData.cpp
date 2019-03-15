#include "DescriptorData.h"
#include "ReaderScenario.h"
#include "TagsManager.h"
#include "utils.h"

IDescriptorData::IDescriptorData()
{
    //ctor
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
        vector<string> content = split(*it, '=');
        if (content.size() == 2)
        {
            IntTagModifierDescriptorData* data = new IntTagModifierDescriptorData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = ChangeInt::affect;
            data->m_value = stoi(content[1]);
            _descriptors.push_back(data);
            continue;
        }
        content = split(*it, "+=");
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
    ReaderScenario::Instance()->changeFX(m_sound);
}
void SFXDescriptorData::unload()
{
    ReaderScenario::Instance()->changeFX(nullptr);
}
void SFXDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    SFXDescriptorData* data = new SFXDescriptorData();
    data->m_sound = _text;
    _descriptors.push_back(data);
}

void MusicDescriptorData::read()
{
    ReaderScenario::Instance()->changeMusic(m_sound);
}
void MusicDescriptorData::unload()
{
    ReaderScenario::Instance()->changeMusic(nullptr);
}
void MusicDescriptorData::parse(vector<IDescriptorData*>& _descriptors, string _text)
{
    MusicDescriptorData* data = new MusicDescriptorData();
    data->m_sound = _text;
    _descriptors.push_back(data);
}

void TextDescriptorData::read()
{
    m_text.parse();
    if (!m_text.haveBlinker())
        m_text.update();
}
void TextDescriptorData::update()
{
    if (m_text.haveBlinker())
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
    ReaderScenario::Instance()->setSprite(m_sprite);
}
void SpriteDescriptorData::unload()
{
    ReaderScenario::Instance()->setSprite(nullptr);
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
