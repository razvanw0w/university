package model.statement;
import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.IMyDictionary;
import model.PrgState;
import model.type.Type;

public interface IStmt {
    PrgState execute(PrgState state) throws MyException; // execution method for a statement
    IMyDictionary<String, Type> typecheck(IMyDictionary<String, Type> typeEnvironment) throws TypeCheckException;
    IStmt deepCopy();
}
