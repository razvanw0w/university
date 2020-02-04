package model.ADT;

import exceptions.MyException;

import java.util.List;

public interface IMyStack<T> {
    public T pop() throws MyException;
    public void push(T value);
    public boolean isEmpty();
    public List<T> toList();
}
