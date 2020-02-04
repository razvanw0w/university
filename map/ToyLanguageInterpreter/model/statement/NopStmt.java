package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.PrgState;
import model.type.Type;

public class NopStmt implements IStmt {

    @Override
    public PrgState execute(PrgState state) throws MyException {
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        return typeEnvironment;
    }

    @Override
    public IStmt deepCopy() {
        return new NopStmt();
    }
}
