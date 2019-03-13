#include "TagData.h"

void BoolTagData::doAction(ChangeBool _action, bool _value)
{
    switch (_action)
    {
        case ChangeBool::setTrue:
            m_value = true;
            break;
        case ChangeBool::setFalse:
            m_value = false;
            break;
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
