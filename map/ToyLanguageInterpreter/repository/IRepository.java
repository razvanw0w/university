package repository;

import exceptions.MyException;
import model.ADT.IMyHeap;
import model.PrgState;
import model.statement.IStmt;
import model.value.Value;

import java.util.List;

public interface IRepository {
    List<PrgState> getPrgList();
    void setPrgList(List<PrgState> list);
    void logPrgStateExec(PrgState prgState) throws MyException;
    IMyHeap<Value> getProgramHeap();
    IStmt getOriginalProgram();
    boolean errorThrown();
    String getError();
    void addError(String error);
    void restartProgram();
}
