package model.ADT;

import java.util.LinkedList;
import java.util.List;
import java.util.NoSuchElementException;
import java.util.Vector;

import exceptions.*;

public class MyList<T> implements IMyList<T> {
    private List<T> list;

    public MyList() {
        list = new Vector<T>();
    }

    @Override
    public void add(T item) {
        list.add(item);
    }

    @Override
    public void remove(T item) throws MyException {
        try {
            list.remove(item);
        }
        catch (NoSuchElementException e) {
            throw new MyException("No such element " + item);
        }
    }

    @Override
    public T get(int index) throws MyException {
        try {
            return list.get(index);
        }
        catch (IndexOutOfBoundsException e) {
            throw new MyException("Index out of bounds");
        }
    }

    @Override
    public int size() {
        return list.size();
    }

    @Override
    public String toString() {
        StringBuilder content = new StringBuilder("[");
        for (T item: list) {
            content.append(item).append("|");
        }
        return content + "]";
    }
}

