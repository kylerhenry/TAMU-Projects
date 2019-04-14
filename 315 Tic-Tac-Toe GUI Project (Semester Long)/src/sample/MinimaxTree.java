package sample;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Region;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class MinimaxTree {
    private Node_AI root;
    private String computerPiece;
    private String playerPiece;
    ArrayList<ArrayList<ArrayList<String>>> b;

    //assumes blank board and constructs minimax tree
    MinimaxTree(ArrayList<ArrayList<ArrayList<String>>> board, String piece) {
        computerPiece = "O";
        playerPiece = "X";

        b = new ArrayList<ArrayList<ArrayList<String>>>(board);
        //create first layer
        ArrayList<Integer> temp = new ArrayList<>();
        temp.add(0);
        temp.add(0);
        temp.add(0);
        root = new Node_AI(null, " ", computerPiece, b, temp);
        //System.out.println("Board after first layer:");
        //System.out.println(Controller.board);

        //create second layer
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                for (int i = 0; i < 4; i++) {
                    temp.set(0, i);
                    temp.set(1, j);
                    temp.set(2, k);
                    Node_AI child = new Node_AI(root, "X", computerPiece, b, temp); //X always moves first
                    System.out.println("Board after new Node_AI creation:");
                    System.out.println(Controller.board); //FIXME
                    root.insertChild(child);
                }
            }
        }
        //System.out.println("Board after 2nd layer:");
        //System.out.println(Controller.board); //FIXME

        //create 3rd layer
        for (Node_AI child : root.getChildren()) {
            for (int k = 0; k < 4; k++) {
                for (int j = 0; j < 4; j++) {
                    for (int i = 0; i < 4; i++) {
                        //Only make move if blank
                        if (child.getBoard().get(i).get(j).get(k).equals(" ")) {
                            temp.set(0, i);
                            temp.set(1, j);
                            temp.set(2, k);
                            child.insertChild(new Node_AI(child, "O", computerPiece, child.getBoard(), temp));
                        }
                    }
                }
            }
        }
        //System.out.println("Board after 3rd layer:");
        //System.out.println(Controller.board); //FIXME

    }

    ArrayList<Integer> move(){
        Node_AI bestMove = root.getChildren().get(0);
        //find move wil smallest minimax value
        for(Node_AI child : root.getChildren()){
            for(Node_AI child2 : child.getChildren()){
                if(child2.getValue()<bestMove.getValue()){
                    bestMove = child2.getParent();
                }
            }
        }
        return bestMove.getMove();
    }

    //traverses down tree once and createes a new layer
    void update(String piece, ArrayList<Integer> lastMove){
        Node_AI lastRoot = root;

        //set root to child matching last move
        for(int i = 0; i < root.getChildren().size(); i++){
            Node_AI child = root.getChildren().get(i);
            if(lastMove.equals(child.getMove())){
                root = child;
                lastRoot.removeChild(i);
                break;
            }
        }
        //create new layer
        for(Node_AI child :root.getChildren()){
            for (int k = 0; k < 4; k++) {
                for (int j = 0; j < 4; j++) {
                    for (int i = 0; i < 4; i++) {
                        //Only make move if blank
                        if (child.getBoard().get(i).get(j).get(k).equals(" ")) {
                            ArrayList<Integer> temp = new ArrayList<>();
                            temp.add(i);
                            temp.add(j);
                            temp.add(k);
                            child.insertChild(new Node_AI(child, piece, computerPiece, child.getBoard(), temp));
                        }
                    }
                }
            }
        }
    }
}
