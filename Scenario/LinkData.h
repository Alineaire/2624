#ifndef LINKDATA_H
#define LINKDATA_H

#include <string>
#include <list>

using namespace std;

class PageData;
class IConditionData;
class LinkData
{
    public:
        LinkData();
        virtual ~LinkData();
        bool check();
        virtual void initialize();

        string m_name;
        PageData* m_nextPage;
        list<IConditionData> m_conditions;

    protected:
    private:
};

#endif // LINKDATA_H
