#ifndef LINKDATA_H
#define LINKDATA_H

#include <string>
#include <vector>

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
        vector<IConditionData> m_conditionsDisplay;
        vector<IConditionData> m_conditionsValidation;

    protected:
    private:
};

#endif // LINKDATA_H
