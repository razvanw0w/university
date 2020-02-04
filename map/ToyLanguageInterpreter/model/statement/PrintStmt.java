package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyList;
import model.PrgState;
import model.expression.Exp;
import model.type.Type;
import model.value.Value;

public class PrintStmt implements IStmt {
    private Exp exp;

    public PrintStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "print(" + exp + ")";
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyList<Value> outList = state.getOutList();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        outList.add(exp.eval(symTable, state.getHeap()));
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        exp.typecheck(typeEnvironment);
        return typeEnvironment;
    }

    @Override
    public IStmt deepCopy() {
        return new PrintStmt(exp.deepCopy());
    }
}
