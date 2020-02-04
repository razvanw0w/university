package model.value;

import model.type.Type;

public interface Value {
    public Type getType();
    Value deepCopy();
}
