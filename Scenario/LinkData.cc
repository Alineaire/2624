
class LinkData : public ScriptableObject
{
    public string _Name;
    public PageData _NextPage;
    public List<IConditionData> _Conditions = new List<IConditionData>();

    public LinkData()
    {
    }

    public bool Check()
    {
        if (_NextPage != null)
        {
            foreach (IConditionData condition in _Conditions)
            {
                if (!condition.Validate())
                    return false;
            }
            ReaderScenario.Instance.ChangePage(_NextPage);
            return true;
        }
        return false;
    }

    public virtual void Initialize()
    {
        foreach (IConditionData condition in _Conditions)
        {
            condition.Initialize(this);
        }
    }
};
