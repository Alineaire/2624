
class PageData : public ScriptableObject
{
    public List<IDescriptorData> _Descriptors = new List<IDescriptorData>();
    public List<LinkData> _Links = new List<LinkData>();


    public PageData()
    {
    }

    public void Read()
    {
        foreach (IDescriptorData descriptor in _Descriptors)
        {
            descriptor.Read();
        }
        foreach (LinkData link in _Links)
        {
            link.Initialize();
        }
    }

    public void Unload()
    {
        foreach (IDescriptorData descriptor in _Descriptors)
        {
            descriptor.Unload();
        }
    }

    public void Update()
    {
        foreach (LinkData link in _Links)
        {
            if (link.Check())
                break;
        }
    }
};
