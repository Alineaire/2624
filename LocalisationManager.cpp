#include "LocalisationManager.h"
#include "csvparser.h"

LocalisationManager::LocalisationManager()
{
    //ctor
}

LocalisationManager::~LocalisationManager()
{
    //dtor
}

void LocalisationManager::setLanguage()
{
    //TODO
    string lang = "FR";
    m_currentLanguageLocalisations = &(m_allLocalisations[lang]);
}

string LocalisationManager::getLoc(string _key)
{
    map<string,string>::iterator it = m_currentLanguageLocalisations->find(_key);
    if (it == m_currentLanguageLocalisations->end())
        return "<ERROR>";
    return it->second;
}

void LocalisationManager::addLoc(string _language, string _key, string _value)
{
    m_allLocalisations[_language][_key] = _value;
}

void LocalisationManager::loadTSV(string& _pathLoc)
{
    CsvParser* csvparser = CsvParser_new(_pathLoc.c_str(), "\t", 1);
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
            for (int i = 1; i < CsvParser_getNumFields(row) ; i++)
                addLoc(headerFields[i], rowFields[0], rowFields[i]);
        }
        CsvParser_destroy_row(row);
    }

    CsvParser_destroy(csvparser);
}
