#ifndef CONDITIONDATA_H
#define CONDITIONDATA_H

#include "LinkData.h"
#include "TagData.h"

#include <string>

using namespace std;

class IConditionData
{
    public:
        IConditionData() {}
        virtual ~IConditionData() {}
        virtual void initialize(LinkData* _link) {}
        virtual bool validate() { return true; }

    protected:
    private:
};

class BoolTagConditionData : public IConditionData
{
    public:
        BoolTagConditionData() {}
        virtual ~BoolTagConditionData() {}
        bool validate();
        static void parse(vector<IConditionData*>& _conditions, string _text);

        BoolTagData* m_data;
        CheckBool m_action;

    protected:
    private:
};
class IntTagConditionData : public IConditionData
{
    public:
        IntTagConditionData() {}
        virtual ~IntTagConditionData() {}
        bool validate();
        static void parse(vector<IConditionData*>& _conditions, string _text);

        IntTagData* m_data;
        CheckInt m_action;
        int m_value;

    protected:
    private:
};
class StringTagConditionData : public IConditionData
{
    public:
        StringTagConditionData() {}
        virtual ~StringTagConditionData() {}
        bool validate();
        static void parse(vector<IConditionData*>& _conditions, string _text);

        StringTagData* m_data;
        CheckString m_action;
        string m_value;

    protected:
    private:
};

class TimeConditionData : public IConditionData
{
    public:
        TimeConditionData() {}
        virtual ~TimeConditionData() {}
        void initialize(LinkData* _link);
        bool validate();

        float m_duration;
        float m_time;

    protected:
    private:
};

class InputConditionData : public IConditionData
{
    public:
        InputConditionData() {}
        virtual ~InputConditionData() {}
        void initialize(LinkData* _link);
        bool validate();

        string m_input;

    protected:
    private:
};

#endif // CONDITIONDATA_H
