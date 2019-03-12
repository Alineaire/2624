#ifndef TAGSMANAGER_H
#define TAGSMANAGER_H

#include "TagData.h"

#include <list>

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

        list<ITagData> m_tags;

    protected:
    private:
    static TagsManager* m_instance;
};

#endif // TAGSMANAGER_H
