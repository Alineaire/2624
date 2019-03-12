
class ImageDescriptorData : public IDescriptorData
{
    public Sprite _Sprite;

    public override void Read()
    {
        base.Read();

        ReaderScenario.Instance.SetImage(_Sprite);
    }

    public override void Unload()
    {
        base.Unload();

        ReaderScenario.Instance.SetImage(null);
    }
};
