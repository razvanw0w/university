package view;
import exceptions.*;
import controller.*;
import model.PrgState;
import repository.*;
import model.ADT.*;
import model.expression.*;
import model.statement.*;
import model.type.*;
import model.value.*;

import javafx.application.Application;
import javafx.stage.Stage;
import javafx.scene.Scene;
import javafx.scene.layout.StackPane;
import javafx.fxml.FXMLLoader;


public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        try {
            StackPane root = (StackPane)FXMLLoader.load(getClass().getResource("ProgramChooser.fxml"));
            Scene scene = new Scene(root,1000,511);
            primaryStage.setScene(scene);
            primaryStage.setTitle("Program Chooser");
            primaryStage.show();
        } catch(Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        launch(args);
    }
}
