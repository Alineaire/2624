
class SoundDescriptorData : public IDescriptorData
{
    public AudioClip _Sound;

    public override void Read()
    {
        base.Read();

        ReaderScenario.Instance.ChangeFX(_Sound);
    }

    public override void Unload()
    {
        base.Unload();

        ReaderScenario.Instance.ChangeFX(null);
    }
};
