#include "ConditionData.h"
#include "ReaderScenario.h"
#include "TagsManager.h"
#include "Time.h"
#include "InputManager.h"
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
        vector<string> content = split(*it, "!=");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::notEquals;
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
        content = split(*it, "=");
        if (content.size() == 2)
        {
            IntTagConditionData* data = new IntTagConditionData();
            data->m_data = TagsManager::Instance()->addIntTag(content[0]);
            data->m_action = CheckInt::equals;
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

    m_time = Time::Instance()->ActualTime();
}
bool TimeConditionData::validate()
{
    return this->IConditionData::validate() && Time::Instance()->ActualTime() >= m_time + m_duration;
}
void TimeConditionData::parse(vector<IConditionData*>& _conditions, string _text)
{
    TimeConditionData* data = new TimeConditionData();
    data->m_duration = stof(_text);
    _conditions.push_back(data);
}

void InputConditionData::initialize(LinkData* _link)
{
    this->IConditionData::initialize(_link);
    for (vector<CheckInput>::iterator it = m_inputs.begin(); it != m_inputs.end(); ++it)
    {
        it->m_index = 0;
        it->m_time = 0.0f;
    }
}
bool InputConditionData::validate()
{
    bool oneFinish = false;
    for (vector<CheckInput>::iterator it = m_inputs.begin(); it != m_inputs.end(); ++it)
    {
        string currentInput = it->m_index < it->m_inputs.size() ? it->m_inputs[it->m_index] : "";
        if (currentInput != "")
        {
            bool nextInput = false;
            if (currentInput.find("MOUSE") != string::npos)
            {
                vec2f delta = InputManager::Instance()->getMouseDeltaPosition();
                if (delta.length() > 1)
                {
                    it->m_time += Time::Instance()->DeltaTime();
                    float duration = stof(split(currentInput, "#")[1]);
                    nextInput = (it->m_time > duration);
                }
            }
            else if (InputManager::Instance()->keyJustPress(it->m_inputs[it->m_index]))
                nextInput = true;

            if (nextInput)
            {
                ++(it->m_index);
                it->m_time = 0.0f;
            }
        }
        if (it->m_index >= it->m_inputs.size())
        {
            oneFinish = true;
            break;
        }
    }
    return this->IConditionData::validate() && oneFinish;
}
void InputConditionData::parse(vector<IConditionData*>& _conditions, string _text)
{
    InputConditionData* data = new InputConditionData();
    vector<string> variables = split(_text, '|');
    for (vector<string>::iterator it = variables.begin(); it != variables.end(); ++it)
    {
        CheckInput ci;
        vector<string> inputs = split(*it, ",");
        for (vector<string>::iterator it2 = inputs.begin(); it2 != inputs.end(); ++it2)
            ci.m_inputs.push_back(toUpper(*it2));
        data->m_inputs.push_back(ci);
    }
    _conditions.push_back(data);
}
