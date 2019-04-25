#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include "TagData.h"

#include <map>
#include <string>

using namespace std;

class TagsManager
{
    public:
        TagsManager();
        virtual ~TagsManager();
        static TagsManager* Instance()
        {
            if (TagsManager::m_instance == nullptr)
            {
                TagsManager::m_instance = new TagsManager();
            }
            return TagsManager::m_instance;
        }

        BoolTagData* addBoolTag(string _name);
        IntTagData* addIntTag(string _name);
        StringTagData* addStringTag(string _name);

        map<string, ITagData*> m_tags;

    protected:
    private:
        static TagsManager* m_instance;
};

#endif // TAGSMANAGER_H
