package model.statement;

import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.PrgState;
import model.expression.Exp;
import model.type.IntType;
import model.type.StringType;
import model.type.Type;
import model.value.IntValue;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class ReadFileStmt implements IStmt {
    private Exp exp;
    private String variableName;
    private String fileName;

    public ReadFileStmt(Exp expression, String variableName) {
        this.exp = expression;
        this.variableName = variableName;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        IMyDictionary<String, Value> symTable = state.getSymTable();
        IMyDictionary<StringValue, BufferedReader> fileTable = state.getFileTable();

        if (symTable.isDefined(variableName)) {
            if (symTable.lookup(variableName).getType().equals(new IntType())) {
                Value val = exp.eval(symTable, state.getHeap());
                if (val.getType().equals(new StringType())) {
                    StringValue stringVal = (StringValue) val;
                    if (fileTable.isDefined(stringVal)) {
                        BufferedReader bufferedReader = fileTable.lookup(stringVal);
                        try {
                            String line = bufferedReader.readLine();
                            Value intVal;
                            IntType type = new IntType();
                            if (line == null) {
                                intVal = type.defaultValue();
                            }
                            else {
                                intVal = new IntValue(Integer.parseInt(line));
                            }
                            symTable.update(variableName, intVal);
                        }
                        catch (IOException e) {
                            throw new MyException(e.getMessage());
                        }
                    }
                    else {
                        throw new MyException("the file " + stringVal.getValue() + " doesn't exist in the filetable");
                    }
                }
                else {
                    throw new MyException("the value could not be evaluated to a string value");
                }
            }
            else {
                throw new MyException(variableName + " is not of type int");
            }
        }
        else {
            throw new MyException(variableName + " is not defined in symTable");
        }

        return null;
    }

    @Override
    public IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException {
        if (typeEnvironment.isDefined(variableName)) {
            Type variableType = typeEnvironment.lookup(variableName);
            Type expType = exp.typecheck(typeEnvironment);
            if (!variableType.equals(new IntType())) {
                throw new TypeCheckException("variable in " + this.toString() + " is not an integer");
            }
            if (!expType.equals(new StringType())) {
                throw new TypeCheckException("file name in " + this.toString() + " is not a string");
            }
            return typeEnvironment;
        }
        else {
            throw new TypeCheckException("variable " + variableName + " is not defined");
        }
    }

    @Override
    public String toString() {
        return "readfrom " + exp + " into " + variableName;
    }

    @Override
    public IStmt deepCopy() {
        return new ReadFileStmt(exp.deepCopy(), new String(variableName));
    }
}
