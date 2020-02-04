package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.ADT.IMyStack;
import model.PrgState;
import model.expression.Exp;
import model.type.BoolType;
import model.type.Type;
import model.value.BoolValue;
import model.value.Value;

public class IfStmt implements IStmt {
    private Exp expression;
    private IStmt thenStatement;
    private IStmt elseStatement;

    public IfStmt(Exp expression, IStmt thenStatement, IStmt elseStatement) {
        this.expression = expression;
        this.thenStatement = thenStatement;
        this.elseStatement = elseStatement;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyStack<IStmt> stk = state.getStack();
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value condition = expression.eval(symTable, state.getHeap());
        if (!condition.getType().equals(new BoolType())) {
            throw new MyException("conditional expression could not evaluated to a boolean");
        }
        else {
            BoolValue booleanCondition = (BoolValue) condition;
            if (booleanCondition.isTrue()) {
                stk.push(thenStatement);
            }
            else {
                stk.push(elseStatement);
            }
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        Type expType = expression.typecheck(typeEnvironment);
        if (expType.equals(new BoolType())) {
            thenStatement.typecheck(typeEnvironment.deepCopy());
            elseStatement.typecheck(typeEnvironment.deepCopy());
            return typeEnvironment;
        }
        else {
            throw new TypeCheckException("The condition in " + this.toString() + " statement is not a boolean");
        }
    }

    @Override
    public String toString() {
        return "if (" + expression + ") then {" + thenStatement + "} else {" + elseStatement + "}";
    }

    @Override
    public IStmt deepCopy() {
        return new IfStmt(expression.deepCopy(), thenStatement.deepCopy(), elseStatement.deepCopy());
    }
}
