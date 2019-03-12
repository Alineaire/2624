#include "TagData.h"

void BoolTagData::doAction(ChangeBool _action)
{
    switch (_action)
    {
        case ChangeBool::SetTrue:
            m_value = true;
            break;
        case ChangeBool::SetFalse:
            m_value = false;
            break;
        case ChangeBool::Reverse:
            m_value = !m_value;
            break;
    }
}

bool BoolTagData::checkValue(CheckBool _action)
{
    switch (_action)
    {
        case CheckBool::IsTrue:
            return m_value;
        case CheckBool::IsFalse:
            return !m_value;
    }
    return false;
}

bool IntTagData::checkValue(CheckInt _action, int _valueTest)
{
    switch (_action)
    {
        case CheckInt::Equals:
            return m_value == _valueTest;
        case CheckInt::NotEquals:
            return m_value != _valueTest;
        case CheckInt::Superior:
            return m_value > _valueTest;
        case CheckInt::EqualsSuperior:
            return m_value >= _valueTest;
        case CheckInt::Inferior:
            return m_value < _valueTest;
        case CheckInt::EqualsInferior:
            return m_value <= _valueTest;
    }
    return false;
}
