package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.PrgState;
import model.expression.Exp;
import model.type.IntType;
import model.type.RefType;
import model.type.StringType;
import model.type.Type;
import model.value.RefValue;
import model.value.Value;

public class WriteHeapStmt implements IStmt {
    private String variableName;
    private Exp exp;

    public WriteHeapStmt(String variableName, Exp exp) {
        this.variableName = variableName;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();

        if (symTable.isDefined(variableName)) {
            if (symTable.lookup(variableName).getType() instanceof RefType) {
                RefValue refVal = (RefValue) symTable.lookup(variableName);
                if (heap.isDefined(refVal.getAddress())) {
                    Value val = exp.eval(symTable, heap);
                    if (symTable.lookup(variableName).getType().equals(new RefType(val.getType()))) {
                        int address = refVal.getAddress();
                        heap.update(address, val);
                    }
                    else {
                        throw new MyException("the evaluated expression has a different type than the pointing variable");
                    }
                }
                else {
                    throw new MyException("the address to which " + variableName + " points is not in the heap");
                }
            }
            else {
                throw new MyException(variableName + " is not a reference variable");
            }
        }
        else {
            throw new MyException(variableName + " is not defined");
        }

        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (typeEnvironment.isDefined(variableName)) {
            Type variableType = typeEnvironment.lookup(variableName);
            Type expType = exp.typecheck(typeEnvironment);
            if (!(variableType instanceof RefType)) {
                throw new TypeCheckException("file name in " + this.toString() + " is not a string");
            }
            if (!variableType.equals(new RefType(expType))) {
                throw new TypeCheckException("right hand side of " + this.toString() + " has other type than the referenced type of the left hand side");
            }
            return typeEnvironment;
        }
        else {
            throw new TypeCheckException("variable " + variableName + " is not defined");
        }
    }

    @Override
    public IStmt deepCopy() {
        return new WriteHeapStmt(new String(variableName), exp.deepCopy());
    }

    @Override
    public String toString() {
        return "wH(" + variableName + "," + exp + ")";
    }
}
