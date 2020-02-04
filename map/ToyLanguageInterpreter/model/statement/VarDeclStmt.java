package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.PrgState;
import model.type.Type;
import model.value.Value;

public class VarDeclStmt implements IStmt {
    private String name;
    private Type type;

    public VarDeclStmt(String name, Type type) {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        if (symTable.isDefined(name)) {
            throw new MyException("variable " + name + " is already declared");
        }
        else {
            symTable.update(name, type.defaultValue());
        }
        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (typeEnvironment.isDefined(name)) {
            throw new TypeCheckException("variable " + name + " already defined");
        }
        typeEnvironment.update(name, type);
        return typeEnvironment;
    }

    @Override
    public String toString() {
        return type + " " + name;
    }

    @Override
    public IStmt deepCopy() {
        return new VarDeclStmt(new String(name), type.deepCopy());
    }
}
