package model.type;

import model.value.RefValue;
import model.value.Value;

import java.util.Objects;

public class RefType implements Type {
    private Type innerType;

    public RefType(Type innerType) {
        this.innerType = innerType;
    }

    public Type getInnerType() {
        return innerType;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RefType refType = (RefType) o;
        return Objects.equals(innerType, refType.innerType);
    }

    @Override
    public int hashCode() {
        return Objects.hash(innerType);
    }

    @Override
    public Value defaultValue() {
        return new RefValue(innerType, 0);
    }

    @Override
    public Type deepCopy() {
        return new RefType(innerType.deepCopy());
    }

    @Override
    public String toString() {
        return "Ref(" + innerType + ")";
    }
}
