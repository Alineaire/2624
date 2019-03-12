
class IDescriptorData : public ScriptableObject
{
    public void OnValidate()
    {
        ReaderScenario.Instance.ReadAgain();
    }

    public virtual void Read()
    {
    }

    public virtual void Unload()
    {
    }
};
