package model;

import exceptions.MyException;
import model.ADT.*;
import model.statement.IStmt;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;

public class PrgState {
    private IMyStack<IStmt> stk;
    private IMyDictionary<String, Value> symTable;
    private IMyList<Value> outList;
    private IMyDictionary<StringValue, BufferedReader> fileTable;
    private IMyHeap<Value> heap;
    private IStmt originalProgram;
    private int stateID;
    public static int lastID = 0;

    public PrgState(IMyStack<IStmt> stk, IMyDictionary<String, Value> symTable, IMyList<Value> outList,
                    IMyDictionary<StringValue, BufferedReader> fileTable, IMyHeap<Value> heap, IStmt program) {
        this.stk = stk;
        this.symTable = symTable;
        this.outList = outList;
        this.fileTable = fileTable;
        this.heap = heap;
        stk.push(program);
        this.originalProgram = program.deepCopy();
        this.stateID = getNewProgramStateID();
    }

    public static PrgState createEmptyProgramState(IStmt program) {
        return new PrgState(new MyStack<IStmt>(),
                            new MyDictionary<String, Value>(),
                            new MyList<Value>(),
                            new MyDictionary<StringValue, BufferedReader>(),
                            new MyHeap<Value>(),
                            program);
    }

    public IMyStack<IStmt> getStack() {
        return stk;
    }

    public IMyDictionary<String, Value> getSymTable() {
        return symTable;
    }

    public IMyList<Value> getOutList() {
        return outList;
    }

    public IMyDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public IMyHeap<Value> getHeap() {
        return heap;
    }

    public IStmt getOriginalProgram() {
        return originalProgram;
    }

    public int getStateID() {
        return stateID;
    }

    public boolean isNotCompleted() {
        return !stk.isEmpty();
    }

    public PrgState oneStep() throws MyException {
        if (stk.isEmpty()) {
            throw new MyException("program stack is empty");
        }
        IStmt currentStatement = stk.pop();
        return currentStatement.execute(this);
    }

    public static synchronized int getNewProgramStateID() {
        ++lastID;
        return lastID;
    }

    @Override
    public String toString() {
        String content = "==== PROGRAM STATE ====";
        content += "\nID: " + stateID;
        content += "\nStack: " + stk;
        content += "\nSymTable: " + symTable;
        content += "\nOut: " + outList;
        content += "\nFileTable: " + fileTable;
        content += "\nHeap: " + heap;
        return content;
    }
}
