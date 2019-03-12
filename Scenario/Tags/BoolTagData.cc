
public enum ChangeBool
{
    SetTrue,
    SetFalse,
    Reverse,
}

public enum CheckBool
{
    IsTrue,
    IsFalse,
}

class BoolTagData : public ITagData
{
    public bool _InitialValue;
    public bool _Value;

    public void DoAction(ChangeBool action)
    {
        switch (action)
        {
            case ChangeBool.SetTrue:
                _Value = true;
                break;
            case ChangeBool.SetFalse:
                _Value = false;
                break;
            case ChangeBool.Reverse:
                _Value = !_Value;
                break;
        }
    }

    public bool CheckValue(CheckBool action)
    {
        switch (action)
        {
            case CheckBool.IsTrue:
                return _Value;
            case CheckBool.IsFalse:
                return !_Value;
        }
        return false;
    }

    public void Reset()
    {
        _Value = _InitialValue;
    }
};
