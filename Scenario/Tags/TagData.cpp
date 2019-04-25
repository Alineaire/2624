#include "TagData.h"

BoolTagData::BoolTagData() : ITagData() { m_value = false; }
BoolTagData::BoolTagData(string _name) : ITagData(_name) { m_value = false; }
void BoolTagData::doAction(ChangeBool _action, bool _value)
{
    switch (_action)
    {
        case ChangeBool::affect:
            m_value = _value;
            break;
        case ChangeBool::reverse:
            m_value = !m_value;
            break;
    }
}
bool BoolTagData::checkValue(CheckBool _action)
{
    switch (_action)
    {
        case CheckBool::isTrue:
            return m_value;
        case CheckBool::isFalse:
            return !m_value;
    }
    return false;
}

IntTagData::IntTagData() : ITagData() { m_value = 0; }
IntTagData::IntTagData(string _name) : ITagData(_name) { m_value = 0; }
void IntTagData::doAction(ChangeInt _action, int _value)
{
    switch (_action)
    {
        case ChangeInt::increment:
            m_value += _value;
            break;
        case ChangeInt::decrement:
            m_value -= _value;
            break;
        case ChangeInt::affect:
            m_value = _value;
            break;
    }
}
bool IntTagData::checkValue(CheckInt _action, int _valueTest)
{
    switch (_action)
    {
        case CheckInt::equals:
            return m_value == _valueTest;
        case CheckInt::notEquals:
            return m_value != _valueTest;
        case CheckInt::superior:
            return m_value > _valueTest;
        case CheckInt::equalsSuperior:
            return m_value >= _valueTest;
        case CheckInt::inferior:
            return m_value < _valueTest;
        case CheckInt::equalsInferior:
            return m_value <= _valueTest;
    }
    return false;
}

StringTagData::StringTagData() : ITagData() { m_value = ""; }
StringTagData::StringTagData(string _name) : ITagData(_name) { m_value = ""; }
void StringTagData::doAction(ChangeString _action, string _value)
{
    switch (_action)
    {
        case ChangeString::affect:
            m_value = _value;
            break;
    }
}
bool StringTagData::checkValue(CheckString _action, string _valueTest)
{
    switch (_action)
    {
        case CheckString::equals:
            return m_value == _valueTest;
        case CheckString::notEquals:
            return m_value != _valueTest;
    }
    return false;
}
