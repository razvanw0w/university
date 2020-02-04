package view;

import controller.Controller;
import exceptions.MyException;
import exceptions.TypeCheckException;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import model.ADT.MyList;
import model.PrgState;
import model.expression.*;
import model.statement.*;
import model.type.*;
import model.value.*;
import repository.Repository;

import java.util.LinkedList;

public class ProgramChooserController {
    @FXML
    private ListView<Controller> programsListView;

    @FXML
    private Button startProgramButton;

    @FXML
    public void startProgram(ActionEvent event) {
        Controller controller = programsListView.getSelectionModel().getSelectedItem();
        try {
            controller.typecheckOriginalProgram();
            FXMLLoader loader = new FXMLLoader();
            loader.setLocation(getClass().getResource("ProgramExecutor.fxml"));
            ProgramExecutorController executorController = new ProgramExecutorController(controller);
            loader.setController(executorController);
            StackPane executorRoot = (StackPane) loader.load();
            Scene executorScene = new Scene(executorRoot, 600, 400);
            Stage executorStage = new Stage();
            executorStage.setScene(executorScene);
            executorStage.setTitle("Program Execution");
            executorStage.show();
        }
        catch (TypeCheckException e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Typecheck Error");
            alert.setHeaderText("A typecheck error has occured!");
            alert.setContentText(e.toString());

            alert.showAndWait();
        }
        catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.ERROR);
            alert.setTitle("Loading Error");
            alert.setHeaderText("A loading error has occured!");
            alert.setContentText(e.toString());

            alert.showAndWait();
        }
    }

    @FXML
    public void initialize() {
        programsListView.setItems(getControllerList());
        programsListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    }

    public MyList<IStmt> getStatementList() {
        IStmt ex1= new CompStmt(new VarDeclStmt("v",new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(2))),
                        new PrintStmt(new VarExp("v"))));
        IStmt ex2 = new CompStmt(new VarDeclStmt("a",new IntType()),
                new CompStmt(new VarDeclStmt("b",new IntType()),
                        new CompStmt(new AssignStmt("a", new ArithExp(new ValueExp(new IntValue(2)),
                                new ArithExp(new ValueExp(new IntValue(3)),
                                        new ValueExp(new IntValue(5)), 3),
                                1)),
                                new CompStmt(new AssignStmt("b",new ArithExp(new VarExp("a"),
                                        new ValueExp(new IntValue(1)),
                                        1)),
                                        new PrintStmt(new VarExp("b"))))));
        IStmt ex3 = new CompStmt(new VarDeclStmt("a",new BoolType()),
                new CompStmt(new VarDeclStmt("v", new IntType()),
                        new CompStmt(new AssignStmt("a", new ValueExp(new BoolValue(true))),
                                new CompStmt(new IfStmt(new VarExp("a"),new AssignStmt("v",new ValueExp(new IntValue(2))), new AssignStmt("v", new ValueExp(new IntValue(3)))),
                                        new PrintStmt(new VarExp("v"))))));

        IStmt ex4 = new CompStmt(new VarDeclStmt("varf", new StringType()), new CompStmt(new AssignStmt("varf", new ValueExp(new StringValue("test.txt"))),
                new CompStmt(new OpenRFileStmt(new VarExp("varf")),
                        new CompStmt(new VarDeclStmt("varc", new IntType()),
                                new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                                new CompStmt(new ReadFileStmt(new VarExp("varf"), "varc"),
                                                        new CompStmt(new PrintStmt(new VarExp("varc")),
                                                                new CloseRFileStmt(new VarExp("varf"))))))))));
        IStmt ex5 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                new PrintStmt(new VarExp("a")))))));

        IStmt ex6 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                                new PrintStmt(new ArithExp(new ReadHeapExp(new ReadHeapExp(new VarExp("a"))),
                                                        new ValueExp(new IntValue(5)),
                                                        1)))))));

        IStmt ex7 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new PrintStmt(new ReadHeapExp(new VarExp("v"))),
                                new CompStmt(new WriteHeapStmt("v", new ValueExp(new IntValue(30))),
                                        new PrintStmt(new ArithExp(new ReadHeapExp(new VarExp("v")), new ValueExp(new IntValue(5)), 1))))));

        IStmt ex8 = new CompStmt(new VarDeclStmt("v", new RefType(new IntType())),
                new CompStmt(new NewStmt("v", new ValueExp(new IntValue(20))),
                        new CompStmt(new VarDeclStmt("a", new RefType(new RefType(new IntType()))),
                                new CompStmt(new NewStmt("a", new VarExp("v")),
                                        new CompStmt(new NewStmt("v", new ValueExp(new IntValue(30))),
                                                new PrintStmt(new ReadHeapExp(new ReadHeapExp(new VarExp("a")))))))));

        IStmt ex9 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(4))),
                        new CompStmt(new WhileStmt(new RelationalExp(new VarExp("v"), new ValueExp(new IntValue(0)), 5), new CompStmt(new PrintStmt(new VarExp("v")), new AssignStmt("v", new ArithExp(new VarExp("v"), new ValueExp(new IntValue(1)), 2)))),
                                new PrintStmt(new VarExp("v")))));

        IStmt ex10 = new CompStmt(new VarDeclStmt("v", new IntType()),
                new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                        new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(10))),
                                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(22))),
                                        new CompStmt(new ForkStmt(new CompStmt(new WriteHeapStmt("a", new ValueExp(new IntValue(30))),
                                                new CompStmt(new AssignStmt("v", new ValueExp(new IntValue(32))),
                                                        new CompStmt(new PrintStmt(new VarExp("v")),
                                                                new PrintStmt(new ReadHeapExp(new VarExp("a"))))))),
                                                new CompStmt(new PrintStmt(new VarExp("v")),
                                                        new PrintStmt(new ReadHeapExp(new VarExp("a")))))))));

        IStmt arithBad = new PrintStmt(new ArithExp(new ValueExp(new BoolValue(true)), new ValueExp(new IntValue(3)), 1));
        IStmt assignBad = new CompStmt(new VarDeclStmt("a", new IntType()),
                new AssignStmt("a", new ValueExp(new BoolValue(true))));
        IStmt writeHeapBad = new CompStmt(new VarDeclStmt("a", new RefType(new IntType())),
                new CompStmt(new NewStmt("a", new ValueExp(new IntValue(2))),
                        new WriteHeapStmt("a", new ValueExp(new StringValue("x")))));
        IStmt divByZero = new PrintStmt(new ArithExp(new ValueExp(new IntValue(1)), new ValueExp(new IntValue(0)), 4));

        MyList<IStmt> statementList = new MyList<IStmt>();
        statementList.add(ex1);
        statementList.add(ex2);
        statementList.add(ex3);
        statementList.add(ex4);
        statementList.add(ex5);
        statementList.add(ex6);
        statementList.add(ex7);
        statementList.add(ex8);
        statementList.add(ex9);
        statementList.add(ex10);
        statementList.add(arithBad);
        statementList.add(assignBad);
        statementList.add(writeHeapBad);
        statementList.add(divByZero);
        return statementList;
    }

    private ObservableList<Controller> getControllerList() {
        MyList<IStmt> statements = getStatementList();
        LinkedList<Controller> list = new LinkedList<Controller>();
        for (int i = 0; i < statements.size(); ++i) {
            try {
                PrgState prg = PrgState.createEmptyProgramState(statements.get(i));
                Repository repo = new Repository(prg, "log" + String.valueOf(i + 1) + ".txt");
                Controller controller = new Controller(repo);
                list.add(controller);
            }
            catch (MyException e) {
                e.printStackTrace();
            }
        }
        return FXCollections.observableArrayList(list);
    }
}