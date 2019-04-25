#ifndef SCENARIODATA_H
#define SCENARIODATA_H

#include "PageData.h"

#include <string>
#include <map>

using namespace std;

class ScenarioData
{
    public:
        ScenarioData(string& _pathScenario);
        virtual ~ScenarioData();

        map<string, PageData*> m_pages;

    protected:
    private:
        void parse(string& _pathScenario);
};

#endif // SCENARIODATA_H
