#ifndef LINKDATA_H
#define LINKDATA_H

#include "DescriptorData.h"

#include <string>
#include <vector>

using namespace std;

class PageData;
class IConditionData;
class LinkData
{
    public:
        LinkData(string _namePage = "");
        virtual ~LinkData();
        void makeLink();
        bool check();
        void initialize();

        string m_namePage;
        PageData* m_nextPage;
        vector<IDescriptorData*> m_descriptors;
        vector<IConditionData*> m_conditions;

    protected:
    private:
};

#endif // LINKDATA_H
