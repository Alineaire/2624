#ifndef SCENARIODATA_H
#define SCENARIODATA_H

#include "PageData.h"

#include <list>

using namespace std;

class ScenarioData
{
    public:
        ScenarioData();
        virtual ~ScenarioData();
        list<PageData> m_pages;

    protected:
    private:
};

#endif // SCENARIODATA_H
