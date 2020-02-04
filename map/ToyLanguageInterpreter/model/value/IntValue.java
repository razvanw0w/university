package model.value;

import model.type.IntType;
import model.type.Type;

import java.util.Objects;

public class IntValue implements Value {
    private int val;

    public IntValue() {
        val = 0;
    }

    public IntValue(int i) {
        val = i;
    }

    @Override
    public Type getType() {
        return new IntType();
    }

    @Override
    public String toString() {
        return Integer.toString(val);
    }

    public int getValue() {
        return val;
    }

    @Override
    public Value deepCopy() {
        return new IntValue(val);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        IntValue intValue = (IntValue) o;
        return val == intValue.val;
    }

    @Override
    public int hashCode() {
        return Objects.hash(val);
    }
}
