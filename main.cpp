#include "ReaderScenario.h"
#include "TagsManager.h"
#include "LocalisationManager.h"
#include "ScenarioData.h"

#include <iostream>
#include <string>

using namespace std;

ReaderScenario* ReaderScenario::m_instance = nullptr;
TagsManager* TagsManager::m_instance = nullptr;
LocalisationManager* LocalisationManager::m_instance = nullptr;

#if 1
int main()
{

    string pathScenario = "Scenario - Scenario.tsv";
    string pathLoc = "Scenario - Loc.tsv";
    ScenarioData scenario(pathScenario);
    LocalisationManager::Instance()->loadTSV(pathLoc);

    ReaderScenario::Instance()->start(&scenario);

    delete LocalisationManager::Instance();
    delete TagsManager::Instance();
    delete ReaderScenario::Instance();
    return 0;
}
#endif
