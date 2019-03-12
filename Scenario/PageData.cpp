#include "PageData.h"

PageData::PageData()
{
    //ctor
}

PageData::~PageData()
{
    //dtor
}

void PageData::read()
{
    for (list<IDescriptorData>::iterator it=m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        it->read();
    }
    for (list<LinkData>::iterator it=m_links.begin(); it != m_links.end(); ++it)
    {
        it->initialize();
    }
}

void PageData::unload()
{
    for (list<IDescriptorData>::iterator it=m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        it->unload();
    }
}

void PageData::update()
{
    for (list<LinkData>::iterator it=m_links.begin(); it != m_links.end(); ++it)
    {
        if (it->check())
            break;
    }
}
