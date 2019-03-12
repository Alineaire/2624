
class IntTagConditionData : public IConditionData
{
    public IntTagData _Data;
    public CheckInt _Action;
    public int _Value;

    public override bool Validate()
    {
        return base.Validate() && _Data.CheckValue(_Action, _Value);
    }
};
