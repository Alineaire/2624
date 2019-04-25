#ifndef LOCALISATIONMANAGER_H
#define LOCALISATIONMANAGER_H

#include <map>
#include <string>

using namespace std;

class LocalisationManager
{
    public:
        LocalisationManager();
        virtual ~LocalisationManager();
        static LocalisationManager* Instance()
        {
            if (LocalisationManager::m_instance == nullptr)
            {
                LocalisationManager::m_instance = new LocalisationManager();
            }
            return LocalisationManager::m_instance;
        }

        void setLanguage();
        string getLoc(string _key);
        void addLoc(string _language, string _key, string _value);
        void loadTSV(string& _pathLoc);

    protected:
    private:
        static LocalisationManager* m_instance;
        map<string, map<string, string>> m_allLocalisations;
        string m_currentLanguage;
        map<string, string>* m_currentLanguageLocalisations;
};

#endif // LOCALISATIONMANAGER_H
