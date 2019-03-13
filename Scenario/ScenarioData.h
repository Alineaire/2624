#ifndef SCENARIODATA_H
#define SCENARIODATA_H

#include "PageData.h"

#include <vector>

using namespace std;

class ScenarioData
{
    public:
        ScenarioData(string& _pathScenario);
        virtual ~ScenarioData();

        vector<PageData*> m_pages;

    protected:
    private:
        void parse(string& _pathScenario);
};

#endif // SCENARIODATA_H
