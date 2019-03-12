
class BackgroundDescriptorData : public IDescriptorData
{
    public Color _BackgroundColor;

    public override void Read()
    {
        base.Read();

        ReaderScenario.Instance.SetBackground(_BackgroundColor);
    }
};
