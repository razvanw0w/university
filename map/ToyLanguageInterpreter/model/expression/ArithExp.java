package model.expression;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.type.IntType;
import model.type.Type;
import model.value.IntValue;
import model.value.Value;

public class ArithExp implements Exp {
    private Exp e1;
    private Exp e2;
    private int operation; // 1 = +, 2 = -, 3 = *, 4 = /

    public ArithExp(Exp e1, Exp e2, int operation) {
        this.e1 = e1;
        this.e2 = e2;
        this.operation = operation;
    }

    @Override
    public Value eval(IMyDictionary<String, Value> symTable, IMyHeap<Value> heap) throws MyException {
        Value val1, val2;
        val1 = e1.eval(symTable, heap);
        if (val1.getType().equals(new IntType())) {
            val2 = e2.eval(symTable, heap);
            if (val2.getType().equals(new IntType())) {
                IntValue intVal1 = (IntValue)val1;
                IntValue intVal2 = (IntValue)val2;
                int x = intVal1.getValue();
                int y = intVal2.getValue();
                if (operation == 1) {
                    return new IntValue(x + y);
                }
                else if (operation == 2) {
                    return new IntValue(x - y);
                }
                else if (operation == 3) {
                    return new IntValue(x * y);
                }
                else if (operation == 4) {
                    if (y == 0) {
                        throw new MyException("division by zero");
                    }
                    else {
                        return new IntValue(x / y);
                    }
                }
            }
            else {
                throw new MyException("second operand is not an integer");
            }
        }
        else {
            throw new MyException("first operand is not an integer");
        }

        return new IntValue(0);
    }

    @Override
    public String toString() {
        String sign = "";
        if (operation == 1)
            sign = "+";
        if (operation == 2)
            sign = "-";
        if (operation == 3)
            sign = "*";
        if (operation == 4)
            sign = "/";
        return e1 + sign + e2;
    }

    @Override
    public Type typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        Type type1 = e1.typecheck(typeEnvironment);
        Type type2 = e2.typecheck(typeEnvironment);

        if (type1.equals(new IntType())) {
            if (type2.equals(new IntType())) {
                return new IntType();
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
        return new ArithExp(e1.deepCopy(), e2.deepCopy(), operation);
    }
}
