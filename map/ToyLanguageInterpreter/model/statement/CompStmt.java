package model.statement;

import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyStack;
import model.PrgState;
import model.type.Type;

public class CompStmt implements IStmt {
    private IStmt firstStatement;
    private IStmt secondStatement;

    public CompStmt(IStmt firstStatement, IStmt secondStatement) {
        this.firstStatement = firstStatement;
        this.secondStatement = secondStatement;
    }

    @Override
    public PrgState execute(PrgState state) {
        IMyStack <IStmt> stack = state.getStack();
        stack.push(secondStatement);
        stack.push(firstStatement);
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        return secondStatement.typecheck(firstStatement.typecheck(typeEnvironment));
    }

    @Override
    public String toString() {
        return "{" + firstStatement + ";" + secondStatement + "}";
    }

    @Override
    public IStmt deepCopy() {
        return new CompStmt(firstStatement.deepCopy(), secondStatement.deepCopy());
    }
}
