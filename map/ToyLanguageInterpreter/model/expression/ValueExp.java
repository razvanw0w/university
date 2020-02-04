package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.Type;
import model.value.Value;

public class ValueExp implements Exp {
    private Value val;

    public ValueExp(Value val) {
        this.val = val;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException {
        return val;
    }

    @Override
    public String toString() {
        return val.toString();
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        return val.getType();
    }

    @Override
    public Exp deepCopy() {
        return new ValueExp(val.deepCopy());
    }
}
