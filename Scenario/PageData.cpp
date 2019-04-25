#include "PageData.h"
#include "DescriptorData.h"
#include "ConditionData.h"
#include "csvparser.h"
#include "utils.h"

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

void PageData::parse(const char** _headerFields, const char** _rowFields, int _nbCols)
{
    vector<IDescriptorData*> descriptors;
    int colLink = 0;
    for (int i = 1; i < _nbCols ; i++)
    {
        string colName(_headerFields[i]);
        if (colName == "$")
        {
            colLink = i;
            break;
        }

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

    LinkData* link = nullptr;
    while (colLink < _nbCols)
    {
        string colName(_headerFields[colLink]);
        if (colName == "$")
        {
            string linkRef(toUpper(_rowFields[++colLink]));
            ++colLink;
            if (linkRef == "")
            {
                link = nullptr;
                continue;
            }
            link = new LinkData(linkRef);
            m_links.push_back(link);
        }

        string content(_rowFields[colLink++]);
        if (link == nullptr || content == "")
            continue;

        if (colName == "SFXInput")
            SFXDescriptorData::parse(link->m_descriptors, content);
        else if (colName == "Input")
            InputConditionData::parse(link->m_conditions, content);
        else if (colName == "Time (in seconds)")
            TimeConditionData::parse(link->m_conditions, content);
        else if (colName == "BoolTag")
            BoolTagConditionData::parse(link->m_conditions, content);
        else if (colName == "IntTag")
            IntTagConditionData::parse(link->m_conditions, content);
        else if (colName == "StringTag")
            StringTagConditionData::parse(link->m_conditions, content);
    }
}

void PageData::finalizeLink(map<string, PageData*>& _pages)
{
    for (vector<LinkData*>::iterator it = m_links.begin(); it != m_links.end(); ++it)
    {
        (*it)->makeLink(_pages);
    }
}
