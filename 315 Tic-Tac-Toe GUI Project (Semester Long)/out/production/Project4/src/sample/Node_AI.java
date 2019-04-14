package sample;

import jdk.management.cmm.SystemResourcePressureMXBean;

import java.util.ArrayList;

public class Node_AI {
    private int value;
    private Node_AI parent;
    private String piece;
    private String computerPiece;
    private ArrayList<ArrayList<ArrayList<String>>> AIboard;
    private ArrayList<Integer> lastMove;
    private ArrayList<Node_AI> children;

    Node_AI(Node_AI p, String p2, String cPiece, ArrayList<ArrayList<ArrayList<String>>> b, ArrayList<Integer> m){
        parent = (p);
        piece = new String(p2);
        AIboard = new ArrayList<ArrayList<ArrayList<String>>>(b);
        lastMove = new ArrayList<Integer>(m);
        computerPiece = "O";
        children = new ArrayList<Node_AI>();
        for(int i = 0; i < 5; i++){
           children.add(new Node_AI());
        }
        AIboard.get(m.get(0)).get(m.get(1)).set(m.get(2),piece);
        value = new Integer(score(AIboard));
    }
    Node_AI(){}


    Node_AI getParent(){
        return parent;
    }
    int getValue(){
        return value;
    }
    void setValue(int val){
        value = new Integer(val);
    }
    ArrayList<Integer> getMove(){
        return lastMove;
    }
    ArrayList<ArrayList<ArrayList<String>>> getBoard(){
        return AIboard;
    }
    ArrayList<Node_AI> getChildren(){
        return children;
    }
    void removeChild(int index){
        children.remove(index);
    }


    void insertChild(Node_AI c){
        children.add(c);
    }
    int score(ArrayList<ArrayList<ArrayList<String>>> bd){
        //Store number of rows/columns/diagonals with number of X or O at index in appropriate vector
        ArrayList<ArrayList<ArrayList<String>>> board = new ArrayList<ArrayList<ArrayList<String>>> (bd);
        ArrayList<Integer> Xs = new ArrayList<Integer>();
        ArrayList<Integer> Os = new ArrayList<Integer>();
        for(int i =0; i<=4;i++){
            Xs.add(0);
            Os.add(0);
        }

        //Check all Rows
        for (int k = 0; k < 4; k++) {
            for (int j = 0; j < 4; j++) {
                int numX = 0;
                int numO = 0;
                for (int i = 0; i < 4; i++) {
                    if (board.get(i).get(j).get(k).equals("X")) numX++;
                    else if (board.get(i).get(j).get(k).equals("O")) numO++;
                }

                //only increment vector if none of other piece
                if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
                else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
            }
        }

        //Check all Columns
        for (int k = 0; k < 4; k++) {
            for (int i = 0; i < 4; i++) {
                int numX = 0;
                int numO = 0;
                for (int j = 0; j < 4; j++) {
                    if (board.get(i).get(j).get(k).equals("X")) numX++;
                    else if (board.get(i).get(j).get(k).equals("O")) numO++;
                }

                //only increment vector if none of other piece
                if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
                else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
            }
        }

        //Check all Z's
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                int numX = 0;
                int numO = 0;
                for (int k = 0; k < 4; k++) {
                    if (board.get(i).get(j).get(k).equals("X")) numX++;
                    else if (board.get(i).get(j).get(k).equals("O")) numO++;
                }

                //only increment vector if none of other piece
                if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
                else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
            }
        }

        //Check XY Diagonals
        for (int k = 0; k < 4; k++) {
            int numX = 0;
            int numO = 0;
            for (int i = 0; i < 4; i++) {

                if (board.get(i).get(i).get(k).equals("X")) numX++;
                else if (board.get(i).get(i).get(k).equals("O")) numO++;
            }
            //only increment vector if none of other piece
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

            //check reverse diagonal
            numX = 0;
            numO = 0;
            for (int i = 0; i < 4; i++) {
                if (board.get(i).get(3 - i).get(k).equals("X")) numX++;
                else if (board.get(i).get(3 - i).get(k).equals("O")) numO++;
            }
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
        }

        //Check XZ Diagonals
        for (int j = 0; j < 4; j++) {

            int numX = 0;
            int numO = 0;
            for (int i = 0; i < 4; i++) {
                if (board.get(i).get(j).get(i).equals("X")) numX++;
                else if (board.get(i).get(j).get(i).equals("O")) numO++;
            }
            //only increment vector if none of other piece
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

            //check reverse diagonal
            numX = 0;
            numO = 0;
            for (int i = 0; i < 4; i++) {
                if (board.get(i).get(j).get(3-i).equals("X")) numX++;
                else if (board.get(i).get(j).get(3-i).equals("O")) numO++;
            }
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
        }

        //Check YZ Diagonals
        for (int i = 0; i < 4; i++) {
            int numX = 0;
            int numO = 0;
            for (int j = 0; j < 4; j++) {
                if (board.get(i).get(j).get(j).equals("X")) numX++;
                else if (board.get(i).get(j).get(j).equals("O")) numO++;
            }
            //only increment vector if none of other piece
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

            //check reverse diagonal
            numX = 0;
            numO = 0;
            for (int j = 0; j < 4; j++) {
                if (board.get(i).get(j).get(3-j).equals("X")) numX++;
                else if (board.get(i).get(j).get(3-j).equals("O")) numO++;
            }
            if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
            else if (numX == 0) Os.set(numO, Os.get(numO) + 1);
        }

        //Check True Diagonals
        int numX = 0;
        int numO = 0;
        for (int i = 0; i < 4; i++) {

            if (board.get(i).get(i).get(i).equals("X")) numX++;
            else if (board.get(i).get(i).get(i).equals("O")) numO++;
        }
        //only increment vector if none of other piece
        if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
        else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

        //check reverse diagonal
        numX = 0;
        numO = 0;
        for (int i = 0; i < 4; i++) {
            if (board.get(i).get(i).get(3-i).equals("X")) numX++;
            else if (board.get(i).get(i).get(3-i).equals("O")) numO++;
        }
        if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
        else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

        //check other diagonal
        numX = 0;
        numO = 0;
        for (int i = 0; i < 4; i++) {
            if (board.get(i).get(3-i).get(i).equals("X")) numX++;
            else if (board.get(i).get(3-i).get(i).equals("O")) numO++;
        }
        if (numO == 0) Xs.add(numX, Xs.get(numX) + 1);
        else if (numX == 0) Os.add(numO, Os.get(numO) + 1);

        //check other reverse diagonal
        numX = 0;
        numO = 0;
        for (int i = 0; i < 4; i++) {
            if (board.get(i).get(3-i).get(3-i).equals("X")) numX++;
            else if (board.get(i).get(3-i).get(3-i).equals("O")) numO++;
        }
        if (numO == 0) Xs.set(numX, Xs.get(numX) + 1);
        else if (numX == 0) Os.set(numO, Os.get(numO) + 1);

        //depending on computer piece, change formula
        int score = 0;
        if (computerPiece.equals("O")) {
            score = 1000 * (Xs.get(4) - Os.get(4)) + 100 * (Xs.get(3) - Os.get(3)) + 10 * (Xs.get(2) - Os.get(2)) + (Xs.get(1) - Os.get(1));
        }
        else {
            score = -1000 * (Xs.get(4) - Os.get(4)) - 100 * (Xs.get(3) - Os.get(3)) - 10 * (Xs.get(2) - Os.get(2)) - (Xs.get(1) - Os.get(1));
        }
        return score;
    }
}
