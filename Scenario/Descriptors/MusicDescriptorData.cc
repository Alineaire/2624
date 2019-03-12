
class MusicDescriptorData : public IDescriptorData
{
    public AudioClip _Sound;

    public override void Read()
    {
        base.Read();

        ReaderScenario.Instance.ChangeMusic(_Sound);
    }

    public override void Unload()
    {
        base.Unload();

        ReaderScenario.Instance.ChangeMusic(null);
    }
};
