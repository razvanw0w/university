package exceptions;

public class TypeCheckException extends Exception {
    public TypeCheckException(String message) {
        super(message);
    }

    @Override
    public String toString() {
        return "Typecheck error: " + super.getMessage();
    }
}
