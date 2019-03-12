#ifndef TAGDATA_H
#define TAGDATA_H

#include <string>

using namespace std;

enum ChangeBool
{
    SetTrue,
    SetFalse,
    Reverse,
};

enum CheckBool
{
    IsTrue,
    IsFalse,
};

enum CheckInt
{
    Equals,
    NotEquals,
    Superior,
    EqualsSuperior,
    Inferior,
    EqualsInferior,
};

class ITagData
{
    public:
        ITagData() {}
        virtual ~ITagData() {}

        string m_name;

    protected:
    private:
};

class BoolTagData : public ITagData
{
    public:
        BoolTagData() {}
        virtual ~BoolTagData() {}
        void doAction(ChangeBool _action);
        bool checkValue(CheckBool _action);
        void reset() { m_value = m_initialValue; }

        bool m_initialValue;
        bool m_value;

    protected:
    private:
};

class IntTagData : public ITagData
{
    public:
        IntTagData() {}
        virtual ~IntTagData() {}
        void add(int _addValue) { m_value += _addValue; }
        bool checkValue(CheckInt _action, int _valueTest);
        void reset() { m_value = m_initialValue; }

        int m_initialValue;
        int m_value;

    protected:
    private:
};

#endif // TAGDATA_H
