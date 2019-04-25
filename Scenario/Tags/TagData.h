#ifndef TAGDATA_H
#define TAGDATA_H

#include <string>

using namespace std;

enum class ChangeBool
{
    affect,
    reverse,
};
enum class CheckBool
{
    isTrue = 0,
    isFalse,
};

enum class ChangeInt
{
    increment = 0,
    decrement,
    affect,
};
enum class CheckInt
{
    equals = 0,
    notEquals,
    superior,
    equalsSuperior,
    inferior,
    equalsInferior,
};

enum class ChangeString
{
    affect = 0,
};
enum class CheckString
{
    equals = 0,
    notEquals,
};

class ITagData
{
    public:
        ITagData() {}
        ITagData(string _name) { m_name = _name; }
        virtual ~ITagData() {}

        string m_name;

    protected:
    private:
};

class BoolTagData : public ITagData
{
    public:
        BoolTagData();
        BoolTagData(string _name);
        virtual ~BoolTagData() {}
        void doAction(ChangeBool _action, bool _value);
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
        IntTagData();
        IntTagData(string _name);
        virtual ~IntTagData() {}
        void doAction(ChangeInt _action, int _value);
        bool checkValue(CheckInt _action, int _valueTest);
        void reset() { m_value = m_initialValue; }

        int m_initialValue;
        int m_value;

    protected:
    private:
};

class StringTagData : public ITagData
{
    public:
        StringTagData();
        StringTagData(string _name);
        virtual ~StringTagData() {}
        void doAction(ChangeString _action, string _value);
        bool checkValue(CheckString _action, string _valueTest);
        void reset() { m_value = m_initialValue; }

        string m_initialValue;
        string m_value;

    protected:
    private:
};

#endif // TAGDATA_H
