package sample;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Modality;
import javafx.stage.Stage;

public class PlayAgain
{

    public static void display(String title, String message)
    {
        Stage window = new Stage();

        //window.initModality(Modality.APPLICATION_MODAL);
        //window.setTitle("Warning");
        //window.setMinWidth(250);

        Label label = new Label();
        label.setText(message);
        HBox hbox = new HBox(20);
        hbox.getChildren().addAll(label);
        Scene scene = new Scene(hbox, 350, 150);

        // Play again screen
        //button3 =  new Button();
        //button3.setText("New Game");
        //button2.setOnAction(e->window.setScene(scene1));

        // Layout 2
        //HBox hbox = new HBox(20);
        //hbox.getChildren().addAll(button3);
        //scene2 = new Scene( hbox, 350, 250);
        window.setScene(scene);
        window.showAndWait();



    }
}
