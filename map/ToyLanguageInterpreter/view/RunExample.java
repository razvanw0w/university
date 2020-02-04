package view;

import controller.Controller;
import exceptions.MyException;
import exceptions.TypeCheckException;
import model.ADT.MyList;

import java.util.concurrent.ExecutionException;

public class RunExample extends Command {
    private Controller controller;

    public RunExample(String key, String description, Controller controller) {
        super(key, description);
        this.controller = controller;
    }

    @Override
    public void execute() {
        try {
            controller.typecheckOriginalProgram();
            controller.evaluateOneStep();
        }
        catch (MyException | TypeCheckException e) {
            System.out.println(e.toString());
        }
    }
}
