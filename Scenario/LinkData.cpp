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
        for (vector<IConditionData>::iterator it = m_conditionsValidation.begin(); it != m_conditionsValidation.end(); ++it)
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
    bool validateToDisplay = true;
    for (vector<IConditionData>::iterator it = m_conditionsDisplay.begin(); it != m_conditionsDisplay.end(); ++it)
    {
        validateToDisplay = validateToDisplay && it->validate();
    }

    if (validateToDisplay)
    {
        for (vector<IConditionData>::iterator it = m_conditionsValidation.begin(); it != m_conditionsValidation.end(); ++it)
        {
            it->initialize(this);
        }
    }
}
