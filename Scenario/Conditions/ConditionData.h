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
        virtual bool validate(LinkData* _link) { return true; }

    protected:
    private:
};

class BoolTagConditionData : public IConditionData
{
    public:
        BoolTagConditionData() {}
        virtual ~BoolTagConditionData() {}
        bool validate(LinkData* _link);
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
        bool validate(LinkData* _link);
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
        bool validate(LinkData* _link);
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
        bool validate(LinkData* _link);
        static void parse(vector<IConditionData*>& _conditions, string _text);

        float m_duration;
        float m_time;

    protected:
    private:
};

struct CheckInput
{
    vector<string> m_inputs;
    unsigned int m_index;
    float m_time;
};

class InputConditionData : public IConditionData
{
    public:
        InputConditionData() {}
        virtual ~InputConditionData() {}
        void initialize(LinkData* _link);
        bool validate(LinkData* _link);
        static void parse(vector<IConditionData*>& _conditions, string _text);

        vector<CheckInput> m_inputs;

    protected:
    private:
};

#endif // CONDITIONDATA_H
