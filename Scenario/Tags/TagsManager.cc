
class TagsManager : public ScriptableObject
{
    private static TagsManager _instance = null;
    public static TagsManager Instance
    {
        get
        {
            if (TagsManager._instance == null)
            {
                TagsManager[] tags = Resources.FindObjectsOfTypeAll<TagsManager>();
                TagsManager._instance = tags.FirstOrDefault();
            }
            return TagsManager._instance;
        }
    }

    public List<ITagData> _Tags = new List<ITagData>();


    public TagsManager()
    {
    }

    public List<T> GetTagsOfType<T>() where T : ITagData
    {
        List<T> objects = new List<T>();
        foreach (ITagData tag in _Tags)
        {
            if (tag is T)
                objects.Add(tag as T);
        }
        return objects;
    }
};
