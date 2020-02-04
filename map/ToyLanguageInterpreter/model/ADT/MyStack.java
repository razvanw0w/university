package model.ADT;

import exceptions.MyException;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Stack;
import java.util.stream.Collectors;

public class MyStack<T> implements IMyStack<T> {
    private Stack<T> stk;

    public MyStack() {
        this.stk = new Stack<T>();
    }

    @Override
    public T pop() throws MyException {
        if (stk.size() == 0) {
            throw new MyException("stack is empty");
        }
        T top = (T) stk.pop();
        return top;
    }

    @Override
    public void push(T value) {
        stk.push(value);
    }

    @Override
    public boolean isEmpty() {
        return stk.isEmpty();
    }

    @Override
    public List<T> toList() {
        List<T> list = new ArrayList<>(stk);
        Collections.reverse(list);
        return list;
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder();
        for (T item: stk) {
            content.append(item).append("|");
        }
        return content.toString();
    }
}
