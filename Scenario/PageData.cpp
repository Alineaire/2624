#include "PageData.h"
#include "DescriptorData.h"
#include "csvparser.h"

PageData::PageData()
{
}
PageData::PageData(string _name)
{
    m_name = _name;
}

PageData::~PageData()
{
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        delete (*it);
    }
    m_descriptors.clear();
    for (vector<LinkData*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
    {
        delete (*it);
    }
    m_links.clear();
}

void PageData::read()
{
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        (*it)->read();
    }
    for (vector<LinkData*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
    {
        (*it)->initialize();
    }
}

void PageData::unload()
{
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        (*it)->unload();
    }
}

void PageData::update(rgb_matrix::Canvas* _matrix, rgb_matrix::Font* _font)
{
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        (*it)->update();
    }
    for (vector<LinkData*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
    {
        if ((*it)->check())
            break;
    }
}

void PageData::parse(const char** _headerFields, const char** _rowFields, int _nbRows)
{
    vector<IDescriptorData*> descriptors;
    for (int i = 1; i < _nbRows ; i++)
    {
        string colName(_headerFields[i]);
        string content(_rowFields[i]);
        if (content != "")
        {
            descriptors.clear();
            if (colName == "Color")
                ColorDescriptorData::parse(descriptors, content);
            else if(colName == "Brightness")
                BrightnessDescriptorData::parse(descriptors, content);
            else if(colName == "Text")
                TextDescriptorData::parse(descriptors, _rowFields[0]);
            else if(colName == "Sprite")
                SpriteDescriptorData::parse(descriptors, content);
            else if(colName == "SFX")
                SFXDescriptorData::parse(descriptors, content);
            else if(colName == "Music")
                MusicDescriptorData::parse(descriptors, content);
            else if(colName == "BoolTag")
                BoolTagModifierDescriptorData::parse(descriptors, content);
            else if(colName == "IntTag")
                IntTagModifierDescriptorData::parse(descriptors, content);
            else if(colName == "StringTag")
                StringTagModifierDescriptorData::parse(descriptors, content);
            else if(colName == "Arduino")
                ArduinoDescriptorData::parse(descriptors, content);

            if (descriptors.size() > 0)
            {
                m_descriptors.insert(m_descriptors.end(), descriptors.begin(), descriptors.end());
            }
        }
    }
}
