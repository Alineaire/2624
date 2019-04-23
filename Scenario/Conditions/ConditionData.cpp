#include "ConditionData.h"
#include "ReaderScenario.h"
#include "TagsManager.h"
#include "utils.h"

bool BoolTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action);
}
void BoolTagConditionData::parse(vector<IConditionData*>& _conditions, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, "=");
        if (content.size() == 2)
        {
            BoolTagConditionData* data = new BoolTagConditionData();
            data->m_data = TagsManager::Instance()->addBoolTag(content[0]);
            data->m_action = (content[1] == "true" ? CheckBool::isTrue : CheckBool::isFalse);
            _conditions.push_back(data);
            continue;
        }
        if ((*it).find("!") != string::npos)
        {
            BoolTagConditionData* data = new BoolTagConditionData();
            data->m_data = TagsManager::Instance()->addBoolTag(content[0]);
            data->m_action = CheckBool::isFalse;
            _conditions.push_back(data);
            continue;
        }
        if ((*it).find("!") != string::npos)
        {
            BoolTagConditionData* data = new BoolTagConditionData();
            data->m_data = TagsManager::Instance()->addBoolTag(content[0]);
            data->m_action = CheckBool::isTrue;
            _conditions.push_back(data);
            continue;
        }
    }
}

bool IntTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action, m_value);
}
void IntTagConditionData::parse(vector<IConditionData*>& _conditions, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, '=');
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::equals;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, "!=");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::notEquals;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, ">");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::superior;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, ">=");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::equalsSuperior;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, "<");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::inferior;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, "<=");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::equalsInferior;
            data->m_value = stoi(content[1]);
            _conditions.push_back(data);
            continue;
        }
    }
}

bool StringTagConditionData::validate()
{
    return this->IConditionData::validate()
            && m_data->checkValue(m_action, m_value);
}
void StringTagConditionData::parse(vector<IConditionData*>& _conditions, string _text)
{
    vector<string> variables = split(_text, '#');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        vector<string> content = split(*it, "=");
        if (content.size() == 2)
        {
            StringTagConditionData* data = new StringTagConditionData();
            data->m_data = TagsManager::Instance()->addStringTag(content[0]);
            data->m_action = CheckString::equals;
            data->m_value = content[1];
            _conditions.push_back(data);
            continue;
        }
        content = split(*it, "!=");
        if (content.size() == 2)
        {
            StringTagConditionData* data = new StringTagConditionData();
            data->m_data = TagsManager::Instance()->addStringTag(content[0]);
            data->m_action = CheckString::notEquals;
            data->m_value = content[1];
            _conditions.push_back(data);
            continue;
        }
    }
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
        ReaderScenario::Instance()->setUp(_link->m_namePage);
    if (m_input == "DownArrow")
        ReaderScenario::Instance()->setDown(_link->m_namePage);
    if (m_input == "RightArrow")
        ReaderScenario::Instance()->setRight(_link->m_namePage);
    if (m_input == "LeftArrow")
        ReaderScenario::Instance()->setLeft(_link->m_namePage);
    if (m_input == "Space")
        ReaderScenario::Instance()->setButton(_link->m_namePage);
}
bool InputConditionData::validate()
{
    return this->IConditionData::validate()
            //&& Input.GetKeyDown(m_input)//TODO
            ;
}
