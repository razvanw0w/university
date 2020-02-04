package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.Type;
import model.value.Value;

public interface Exp {
    Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException;
    Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException;
    Exp deepCopy();
}
