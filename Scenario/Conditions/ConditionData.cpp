#include "ConditionData.h"
#include "ReaderScenario.h"

bool BoolTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action);
}
bool IntTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action, m_value);
}
bool StringTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action, m_value);
}

void TimeConditionData::initialize(LinkData* _link)
{
    this->IConditionData::initialize(_link);

    //m_time = Time.time; //TODO
}

bool TimeConditionData::validate()
{
    return this->IConditionData::validate()
            //&& Time.time >= m_time + m_duration //TODO
            ;
}

void InputConditionData::initialize(LinkData* _link)
{
    this->IConditionData::initialize(_link);

    if (m_input == "UpArrow")
        ReaderScenario::Instance()->setUp(_link->m_name);
    if (m_input == "DownArrow")
        ReaderScenario::Instance()->setDown(_link->m_name);
    if (m_input == "RightArrow")
        ReaderScenario::Instance()->setRight(_link->m_name);
    if (m_input == "LeftArrow")
        ReaderScenario::Instance()->setLeft(_link->m_name);
    if (m_input == "Space")
        ReaderScenario::Instance()->setButton(_link->m_name);
}

bool InputConditionData::validate()
{
    return this->IConditionData::validate()
            //&& Input.GetKeyDown(m_input)//TODO
            ;
}
