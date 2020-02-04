package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyStack;
import model.PrgState;
import model.expression.Exp;
import model.value.Value;
import model.type.*;

public class AssignStmt implements IStmt {
    private String identifier;
    private Exp expression;

    public AssignStmt(String identifier, Exp expression) {
        this.identifier = identifier;
        this.expression = expression;
    }

    @Override
    public String toString() {
        return identifier + "=" + expression;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyStack<IStmt> stk = state.getStack();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value value = expression.eval(symTable, state.getHeap());
        if (symTable.isDefined(identifier)) {
            Type type = (symTable.lookup(identifier)).getType();
            if (value.getType().equals(type)) {
                symTable.update(identifier, value);
            }
            else {
                throw new MyException("declared type of variable " +
                                      identifier +
                                      " and type of the assigned expression do not match");
            }
        }
        else {
            throw new MyException("the used variable " + identifier + " was not declared before");
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (!typeEnvironment.isDefined(identifier)) {
            throw new TypeCheckException("variable " + identifier + " is not defined in assignment statement " + this.toString());
        }
        else {
            Type variableType = typeEnvironment.lookup(identifier);
            Type expType = expression.typecheck(typeEnvironment);
            if (variableType.equals(expType)) {
                return typeEnvironment;
            }
            else {
                throw new TypeCheckException("right hand side and left hand side of assignment " + this.toString() + " have different types");
            }
        }
    }

    @Override
    public IStmt deepCopy() {
        return new AssignStmt(new String(identifier), expression.deepCopy());
    }
}
