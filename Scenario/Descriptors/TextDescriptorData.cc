
class TextDescriptorData : public IDescriptorData
{
    public string _Text;
    public Color _TextColor = Color.white;

    public override void Read()
    {
        base.Read();

        string formatText = _Text;
        formatText = formatText.Replace("\\n", "\n");
        formatText = formatText.Replace("\n ", "\n");
        ReaderScenario.Instance.SetText(formatText, _TextColor);
    }
};
