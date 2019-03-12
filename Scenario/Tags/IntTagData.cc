
public enum CheckInt
{
    Equals,
    NotEquals,
    Superior,
    EqualsSuperior,
    Inferior,
    EqualsInferior,
}

class IntTagData : public ITagData
{
    public int _InitialValue;
    public int _Value;

    public void Add(int additionalValue)
    {
        _Value += additionalValue;
    }

    public bool CheckValue(CheckInt action, int valueTest)
    {
        switch (action)
        {
            case CheckInt.Equals:
                return _Value == valueTest;
            case CheckInt.NotEquals:
                return _Value != valueTest;
            case CheckInt.Superior:
                return _Value > valueTest;
            case CheckInt.EqualsSuperior:
                return _Value >= valueTest;
            case CheckInt.Inferior:
                return _Value < valueTest;
            case CheckInt.EqualsInferior:
                return _Value <= valueTest;
        }
        return false;
    }

    public void Reset()
    {
        _Value = _InitialValue;
    }
};
