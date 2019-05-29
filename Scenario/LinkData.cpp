#include "LinkData.h"
#include "PageData.h"
#include "ConditionData.h"
#include "ReaderScenario.h"

#include <iostream>

LinkData::LinkData(string _namePage)
{
    m_namePage = _namePage;
}

LinkData::~LinkData()
{
    for (vector<IConditionData*>::iterator it = m_conditions.begin(); it != m_conditions.end(); ++it)
    {
        delete (*it);
    }
    m_conditions.clear();
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        delete (*it);
    }
    m_descriptors.clear();
}

void LinkData::makeLink(map<string, PageData*>& _pages)
{
    m_nextPage = _pages[m_namePage];
    if (m_nextPage == nullptr)
    {
        fprintf(stderr, "Not find page '%s'\n", m_namePage.c_str());
    }
}

bool LinkData::check()
{
    if (m_nextPage != nullptr)
    {
        for (vector<IConditionData*>::iterator it = m_conditions.begin(); it != m_conditions.end(); ++it)
        {
            if (!(*it)->validate(this))
                return false;
        }
        launchValidateDescriptors();
        ReaderScenario::Instance()->changePage(m_nextPage);
        return true;
    }
    return false;
}

void LinkData::initialize()
{
    for (vector<IConditionData*>::iterator it = m_conditions.begin(); it != m_conditions.end(); ++it)
    {
        (*it)->initialize(this);
    }
}

void LinkData::launchValidateDescriptors()
{
    for (vector<IDescriptorData*>::iterator it = m_descriptors.begin(); it != m_descriptors.end(); ++it)
    {
        (*it)->read();
    }
}
