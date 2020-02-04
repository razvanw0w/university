package model.value;

import model.type.BoolType;
import model.type.Type;

import java.util.Objects;

public class BoolValue implements Value {
    private boolean val;

    public BoolValue() {
        this.val = false;
    }

    public BoolValue(boolean val) {
        this.val = val;
    }

    public boolean isTrue() {
        return val;
    }

    @Override
    public Type getType() {
        return new BoolType();
    }

    public boolean getValue() {
        return val;
    }

    @Override
    public String toString() {
        return val ? "true" : "false";
    }

    @Override
    public Value deepCopy() {
        return new BoolValue(val);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        BoolValue boolValue = (BoolValue) o;
        return val == boolValue.val;
    }

    @Override
    public int hashCode() {
        return Objects.hash(val);
    }
}
