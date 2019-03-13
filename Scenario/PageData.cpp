#include "PageData.h"
#include "DescriptorData.h"
#include "csvparser.h"

#include <iostream>

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

void PageData::update()
{
    for (vector<LinkData*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
    {
        if ((*it)->check())
            break;
    }
}

void PageData::parse(const char** _headerFields, const char** _rowFields, int _nbRows)
{
    for (int i = 1; i < _nbRows ; i++)
    {
        IDescriptorData* descriptor = nullptr;

        string colName(_headerFields[i]);
        string content(_rowFields[i]);
        if (content != "")
        {
            if (colName == "Color")
                descriptor = new ColorDescriptorData();
            else if(colName == "Brightness")
                descriptor = new BrightnessDescriptorData();
            else if(colName == "Text")
                descriptor = new TextDescriptorData();
            else if(colName == "Sprite")
                descriptor = new SpriteDescriptorData();
            else if(colName == "SFX")
                descriptor = new SFXDescriptorData();
            else if(colName == "Music")
                descriptor = new MusicDescriptorData();
            else if(colName == "BoolTag")
                descriptor = new BoolTagModifierDescriptorData();
            else if(colName == "IntTag")
                descriptor = new IntTagModifierDescriptorData();
            else if(colName == "StringTag")
                descriptor = new StringTagModifierDescriptorData();
            else if(colName == "Arduino")
                descriptor = new ArduinoDescriptorData();
            if (descriptor != nullptr)
            {
                descriptor->parse(content);
                m_descriptors.push_back(descriptor);
            }
        }
    }
    cout << m_descriptors.size() << endl;
}
