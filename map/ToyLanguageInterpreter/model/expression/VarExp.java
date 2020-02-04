package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.Type;
import model.value.Value;

public class VarExp implements Exp {
    private String identifier;

    public VarExp(String identifier) {
        this.identifier = identifier;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException {
        if (!symTable.isDefined(identifier))
            throw new MyException("variable involved in expression not defined");
        return symTable.lookup(identifier);
    }

    @Override
    public String toString() {
        return identifier;
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (typeEnvironment.isDefined(identifier)) {
            return typeEnvironment.lookup(identifier);
        }
        else {
            throw new TypeCheckException("variable " + this.toString() + " is not defined");
        }
    }

    @Override
    public Exp deepCopy() {
        return new VarExp(new String(identifier));
    }
}
