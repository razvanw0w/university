package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.PrgState;
import model.expression.Exp;
import model.type.StringType;
import model.type.Type;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFileStmt implements IStmt {
    private Exp exp;

    public CloseRFileStmt(Exp exp) {
        this.exp = exp;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        Value val = exp.eval(symTable, state.getHeap());
        if (val.getType().equals(new StringType())) {
            IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();
            StringValue stringVal = (StringValue) val;
            if (fileTable.isDefined(stringVal)) {
                BufferedReader bufferedReader = fileTable.lookup(stringVal);
                try {
                    bufferedReader.close();
                }
                catch (IOException e) {
                    throw new MyException(e.getMessage());
                }
                fileTable.remove(stringVal);
            }
            else {
                throw new MyException("The file doesn't exist in the file table");
            }
        }
        else {
            throw new MyException("expression could not be evaluated to a string in file close");
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        Type expType = exp.typecheck(typeEnvironment);
        if (expType.equals(new StringType())) {
            return typeEnvironment;
        }
        else {
            throw new TypeCheckException("the close file expression " + this.toString() + " is not a string");
        }
    }

    @Override
    public String toString() {
        return "close(" + exp + ")";
    }

    @Override
    public IStmt deepCopy() {
        return new CloseRFileStmt(exp.deepCopy());
    }
}
