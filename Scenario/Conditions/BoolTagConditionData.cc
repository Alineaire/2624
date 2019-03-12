
class BoolTagConditionData : public IConditionData
{
    public:
    BoolTagData _Data;
    CheckBool _Action;

    override bool Validate()
    {
        return base.Validate() && _Data.CheckValue(_Action);
    }
};
