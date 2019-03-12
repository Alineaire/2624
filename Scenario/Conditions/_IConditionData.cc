
class IConditionData : public ScriptableObject
{
    public:
    virtual void Initialize(LinkData link)
    {
    }

    virtual bool Validate()
    {
        return true;
    }
};
