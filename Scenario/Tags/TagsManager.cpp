#include "TagsManager.h"

TagsManager::TagsManager()
{
    //ctor
}

TagsManager::~TagsManager()
{
    //dtor
}

BoolTagData* TagsManager::addBoolTag(string _name)
{
    if (m_tags[_name] == nullptr)
    {
        m_tags[_name] = new BoolTagData(_name);
    }
    return (BoolTagData*)m_tags[_name];
}

IntTagData* TagsManager::addIntTag(string _name)
{
    if (m_tags[_name] == nullptr)
    {
        m_tags[_name] = new IntTagData(_name);
    }
    return (IntTagData*)m_tags[_name];
}

StringTagData* TagsManager::addStringTag(string _name)
{
    if (m_tags[_name] == nullptr)
    {
        m_tags[_name] = new StringTagData(_name);
    }
    return (StringTagData*)m_tags[_name];
}
