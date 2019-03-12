
class TimeConditionData : public IConditionData
{
    public float _Duration;
    [HideInInspector]
    public float _Time;

    public override void Initialize(LinkData link)
    {
        base.Initialize(link);

        _Time = Time.time;
    }

    public override bool Validate()
    {
        return base.Validate() && Time.time >= _Time + _Duration;
    }
};
