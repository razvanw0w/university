package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.BoolType;
import model.type.IntType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class LogicExp implements Exp {
    private Exp e1;
    private Exp e2;
    private int operation; // 1 = and, 2 = or

    public LogicExp(Exp e1, Exp e2, int operation) {
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException {
        Value val1, val2;
        val1 = e1.eval(symTable, heap);
        if (val1.getType().equals(new BoolType())) {
            val2 = e2.eval(symTable, heap);
            if (val2.getType().equals(new BoolType())) {
                BoolValue intVal1 = (BoolValue)val1;
                BoolValue intVal2 = (BoolValue)val2;
                boolean x = intVal1.getValue();
                boolean y = intVal2.getValue();
                if (operation == 1) {
                    return new BoolValue(x && y);
                }
                else if (operation == 2) {
                    return new BoolValue(x || y);
                }
            }
            else {
                throw new MyException("second operand is not an integer");
            }
        }
        else {
            throw new MyException("first operand is not an integer");
        }

        return new BoolValue();
    }

    @Override
    public String toString() {
        return e1 + (operation == 1 ? "&&" : "||") + e2;
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        Type type1 = e1.typecheck(typeEnvironment);
        Type type2 = e2.typecheck(typeEnvironment);

        if (type1.equals(new BoolType())) {
            if (type2.equals(new BoolType())) {
                return new BoolType();
            }
            else {
                throw new TypeCheckException("second operand is not a boolean in " + this.toString());
            }
        }
        else {
            throw new TypeCheckException("first operand is not a boolean in " + this.toString());
        }
    }

    @Override
    public Exp deepCopy() {
        return new LogicExp(e1.deepCopy(), e2.deepCopy(), operation);
    }
}
