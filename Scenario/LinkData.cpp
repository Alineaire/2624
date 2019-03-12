#include "LinkData.h"
#include "PageData.h"
#include "ConditionData.h"
#include "ReaderScenario.h"

LinkData::LinkData()
{
}

LinkData::~LinkData()
{
}

bool LinkData::check()
{
    if (m_nextPage != nullptr)
    {
        for (list<IConditionData>::iterator it=m_conditions.begin(); it != m_conditions.end(); ++it)
        {
            if (!it->validate())
                return false;
        }
        ReaderScenario::Instance()->changePage(m_nextPage);
        return true;
    }
    return false;
}

void LinkData::initialize()
{
    for (list<IConditionData>::iterator it=m_conditions.begin(); it != m_conditions.end(); ++it)
    {
        it->initialize(this);
    }
}
