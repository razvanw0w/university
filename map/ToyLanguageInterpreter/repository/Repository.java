package repository;

import exceptions.MyException;
import model.ADT.IMyHeap;
import model.ADT.IMyList;
import model.PrgState;
import model.statement.IStmt;
import model.value.Value;

import java.io.FileWriter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Repository implements IRepository {
    private List<PrgState> states;
    private String fileName;
    private IStmt originalProgram;
    private String error;

    public Repository(PrgState prgState, String fileName) {
        this.originalProgram = prgState.getOriginalProgram();
        this.fileName = fileName;
        restartProgram();
    }

    @Override
    public void restartProgram() {
        this.states = new LinkedList<PrgState>();
        PrgState prg = PrgState.createEmptyProgramState(this.originalProgram);
        states.add(prg);
        this.error = "";
    }

    @Override
    public List<PrgState> getPrgList() {
        return states;
    }

    @Override
    public void setPrgList(List<PrgState> list) {
        states = list;
    }

    @Override
    public IMyHeap<Value> getProgramHeap() {
        return states.get(0).getHeap();
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    @Override
    public boolean errorThrown() {
        return !error.equals("");
    }

    @Override
    public String getError() {
        return error;
    }

    @Override
    public void addError(String error) {
        this.error += error + '\n';
    }

    @Override
    public void logPrgStateExec(PrgState prgState) throws MyException {
        try (FileWriter fileWriter = new FileWriter(fileName, true)) {
            fileWriter.write(prgState + "\n");
        }
        catch (IOException e) {
            throw new MyException(e.getMessage());
        }
    }
}
