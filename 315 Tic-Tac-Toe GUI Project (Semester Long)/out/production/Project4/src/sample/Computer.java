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


public class Computer {
    private ArrayList<ArrayList<ArrayList<String>>> Compboard;
    private MinimaxTree tree;
    private String computerPiece;
    private String playerPiece;

    Computer(String piece, ArrayList<ArrayList<ArrayList<String>>> b){
        ArrayList<ArrayList<ArrayList<String>>> newB = new ArrayList<ArrayList<ArrayList<String>>> (b); //ensures the board is not being changed on accident
        Compboard = newB;
        computerPiece = "O";
        playerPiece = "X";
        System.out.println("Board before minimax tree:");
        System.out.println(Controller.board); //FIXME
        tree = new MinimaxTree(Compboard,"O");
        System.out.println("Board after minimax tree:");
        System.out.println(Controller.board); //FIXME
    }
    int pointToIndex(ArrayList<Integer> v){
        return v.get(0) + v.get(1) *4 + v.get(2) *16;
    }
    void update(ArrayList<Integer> move){
        System.out.println("new board before AI moves \n" + Compboard);
        tree.update(playerPiece, move);

    }
    int computerMove(){
        ArrayList<Integer> move = tree.move();
        tree.update(computerPiece, move);
        return pointToIndex(move);
    }
}
