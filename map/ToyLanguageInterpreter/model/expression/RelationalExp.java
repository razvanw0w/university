package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.BoolType;
import model.type.IntType;
import model.type.Type;
import model.value.BoolValue;
import model.value.IntValue;
import model.value.Value;

public class RelationalExp implements Exp {
    private Exp exp1;
    private Exp exp2;
    private int operation;

    public RelationalExp(Exp exp1, Exp exp2, int operation) {
        this.exp1 = exp1;
        this.exp2 = exp2;
        this.operation = operation;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException {
        Value val1, val2;
        val1 = exp1.eval(symTable, heap);
        val2 = exp2.eval(symTable, heap);
        if (val1.getType().equals(new IntType()) && val2.getType().equals(new IntType())) {
            IntValue intVal1, intVal2;
            intVal1 = (IntValue) val1;
            intVal2 = (IntValue) val2;
            int x = intVal1.getValue();
            int y = intVal2.getValue();
            switch (operation) {
                case 1:
                    return new BoolValue(x < y);
                case 2:
                    return new BoolValue(x <= y);
                case 3:
                    return new BoolValue(x == y);
                case 4:
                    return new BoolValue(x != y);
                case 5:
                    return new BoolValue(x > y);
                case 6:
                    return new BoolValue(x >= y);
            }
        }
        else {
            throw new MyException("at least one operand is not an integer");
        }

        return new BoolValue(false);
    }

    @Override
    public String toString() {
        String s = "";
        switch (operation) {
            case 1:
                s = "<";
                break;
            case 2:
                s = "<=";
                break;
            case 3:
                s = "==";
                break;
            case 4:
                s = "!=";
                break;
            case 5:
                s = ">";
                break;
            case 6:
                s = ">=";
                break;
        }
        return exp1 + s + exp2;
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        Type type1 = exp1.typecheck(typeEnvironment);
        Type type2 = exp2.typecheck(typeEnvironment);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new BoolType();
            }
            else {
                throw new TypeCheckException("second operand is not an integer in " + this.toString());
            }
        }
        else {
            throw new TypeCheckException("first operand is not an integer in " + this.toString());
        }
    }

    @Override
    public Exp deepCopy() {
        return new RelationalExp(exp1.deepCopy(), exp2.deepCopy(), operation);
    }
}
