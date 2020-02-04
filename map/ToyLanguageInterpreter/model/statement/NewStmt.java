package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyHeap;
import model.PrgState;
import model.expression.Exp;
import model.type.RefType;
import model.type.Type;
import model.value.RefValue;
import model.value.Value;

public class NewStmt implements IStmt {
    private String variableName;
    private Exp exp;

    public NewStmt(String variableName, Exp exp) {
        this.variableName = variableName;
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyHeap<Value> heap = state.getHeap();
        if (symTable.isDefined(variableName)) {
            if (symTable.lookup(variableName).getType() instanceof RefType) {
                Value val = exp.eval(symTable, heap);
                if (symTable.lookup(variableName).getType().equals(new RefType(val.getType()))) {
                    int address = heap.allocate(val);
                    symTable.update(variableName, new RefValue(val.getType(), address));
                }
                else {
                    throw new MyException("reference doesn't point to expected type");
                }
            }
            else {
                throw new MyException("variable is not a RefType");
            }
        }
        else {
            throw new MyException(variableName + " is not defined");
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (!typeEnvironment.isDefined(variableName)) {
            throw new TypeCheckException("variable " + variableName + " not defined");
        }
        else {
            Type variableType = typeEnvironment.lookup(variableName);
            Type expType = exp.typecheck(typeEnvironment);
            if (variableType.equals(new RefType(expType))) {
                return typeEnvironment;
            }
            else {
                throw new TypeCheckException("right hand side and left hand side in " + this.toString() + " have different types");
            }
        }
    }

    @Override
    public IStmt deepCopy() {
        return new NewStmt(new String(variableName), exp.deepCopy());
    }

    @Override
    public String toString() {
        return "new(" + variableName + "," + exp + ")";
    }
}
