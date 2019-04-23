#include "ScenarioData.h"
#include "csvparser.h"

ScenarioData::ScenarioData(string& _pathScenario)
{
    parse(_pathScenario);
}

ScenarioData::~ScenarioData()
{
    for (std::map<string,PageData*>::iterator it = m_pages.begin(); it != m_pages.end(); ++it)
    {
        delete it->second;
    }
    m_pages.clear();
}

void ScenarioData::parse(string& _pathScenario)
{
    CsvParser* csvparser = CsvParser_new(_pathScenario.c_str(), "\t", 1);
    const CsvRow* header = CsvParser_getHeader(csvparser);
    if (header == nullptr)
    {
        printf("%s\n", CsvParser_getErrorMessage(csvparser));
        return;
    }
    const char** headerFields = CsvParser_getFields(header);
    CsvRow* row;
    while ((row = CsvParser_getRow(csvparser)) )
    {
        const char** rowFields = CsvParser_getFields(row);
        string key = rowFields[0];
        if (key != "")
        {
            PageData* page = new PageData(key);
            page->parse(headerFields, rowFields, CsvParser_getNumFields(row));
            m_pages[key] = page;
        }
        CsvParser_destroy_row(row);
    }
    CsvParser_destroy(csvparser);

    for (std::map<string,PageData*>::iterator it = m_pages.begin(); it != m_pages.end(); ++it)
    {
        it->second->finalizeLink();
    }
}
