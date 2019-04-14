package sample;

import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.Pane;
import javafx.scene.layout.Region;
import javafx.scene.layout.StackPane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;

import javax.naming.ldap.Control;
import java.lang.reflect.Array;
import java.net.Inet4Address;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.BitSet;
import java.util.Random;

public class Controller {

    //global board can be used by user and computer
    static ArrayList<ArrayList<ArrayList<String>>> board = new ArrayList<ArrayList<ArrayList<String>>>();


    //main AI initialization
    //static int counter = 0; commented this out because it was never used

    public static void example(Stage window, Scene scene){
        window.setScene(scene);
    }

    /*****************************************************************************************************************************************/
            /// IGNORE
    /*****************************************************************************************************************************************/
    // update board
//    public static void updateBoard(ArrayList<Integer> location, String symbol){
//        board.get(location.get(0)).get(location.get(1)).set(location.get(2),symbol);
//    }
//    public static ArrayList<Integer> indexToPoint(int index) {
//        ArrayList<Integer> v = new ArrayList<Integer>();
//        Integer z = index / 16;
//        index = index % 16;
//        Integer y = index / 4;
//        index = index % 4;
//        Integer x = index;
//        v.add(x);
//        v.add(y);
//        v.add(z);
//
//        return v;
//    }
//    public static ArrayList<ArrayList<Integer>> checkWin(ArrayList<ArrayList<ArrayList<String>>> board, ArrayList<Integer> point){
//        ArrayList<ArrayList<Integer>> empty  = new ArrayList<ArrayList<Integer>>();
//
//        Integer x = point.get(0);
//        Integer y = point.get(1);
//        Integer z = point.get(2);
//        String piece = board.get(x).get(y).get(z);
//        if(piece.equals(" ")){
//            //System.out.println("EMPTY?");
//            return empty;
//        }
//        int matches = 0;
//        ArrayList<ArrayList<Integer> > v = new ArrayList<ArrayList<Integer>>();
//        //check row
//        for(Integer i = 0; i < 4; i++){
//            if(board.get(i).get(y).get(z).equals(piece)){
//                matches ++;
//            }
//            if(matches == 4){
//                //check row
//                for(Integer j = 0; j < 4; j++){
//                    ArrayList<Integer> winning_point = new ArrayList<Integer>();
//                    winning_point.add(j);
//                    winning_point.add(y);
//                    winning_point.add(z);
//                    v.add(winning_point);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        //check column
//        for(Integer i = 0; i < 4; i++){
//            if(board.get(i).get(y).get(z) .equals( piece)){
//                matches ++;
//            }
//            if(matches == 4){
//                //check row
//                for(Integer j = 0; j < 4; j++){
//                    ArrayList<Integer> winning_point = new ArrayList<Integer>();
//                    winning_point.add(x);
//                    winning_point.add(j);
//                    winning_point.add(z);
//                    v.add(winning_point);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        //check down z
//        for(Integer i = 0; i < 4; i++){
//            if(board.get(i).get(y).get(z) .equals( piece)){
//                matches ++;
//            }
//            if(matches == 4){
//                for(Integer j = 0; j < 4; j++){
//                    ArrayList<Integer> winning_point = new ArrayList<Integer>();
//                    winning_point.add(x);
//                    winning_point.add(y);
//                    winning_point.add(j);
//                    v.add(winning_point);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        //Check XY Diagonals
//        for(Integer i = 0; i < 4; i++){
//            if(board.get(i).get(y).get(z) .equals( piece)){
//                matches ++;
//            }
//            if(matches == 4){
//                //check row
//                for(Integer j = 0; j < 4; j++){
//                    ArrayList<Integer> winning_point = new ArrayList<Integer>();
//                    winning_point.add(j);
//                    winning_point.add(j);
//                    winning_point.add(z);
//                    v.add(winning_point);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        //Check XY Diagonals
//        for(Integer i = 0; i < 4; i++){
//            if(board.get(i).get(y).get(z) .equals( piece)){
//                matches ++;
//            }
//            if(matches == 4){
//                //check row
//                for(Integer j = 0; j < 4; j++){
//                    ArrayList<Integer> winning_point = new ArrayList<Integer>();
//                    winning_point.add(j);
//                    winning_point.add(j);
//                    winning_point.add(z);
//                    v.add(winning_point);
//                }
//                return v;
//            }
//        }
//        matches = 0;
//        for (Integer i = 0; i < 4; i++) {
//            if (board.get(i).get(3 - i).get(z) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (Integer j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(j);
//                    winningPoint.add(3);
//                    winningPoint.add(z);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//        //Check XZ Diagonals
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(i).get(y).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(j);
//                    winningPoint.add(y);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(i).get(y).get(3-i) .equals( piece) )matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//
//                    winningPoint.add(j);
//                    winningPoint.add(y);
//                    winningPoint.add(3-j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//
//
//
//        //Check YZ Diagonals
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(x).get(i).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(x);
//                    winningPoint.add(j);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(x).get(i).get(3-i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(x);
//                    winningPoint.add(j);
//                    winningPoint.add(3-j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//
//
//        //Check True Diagonals
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(i).get(i).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(j);
//                    winningPoint.add(j);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(3 - i).get(i).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(3-j);
//                    winningPoint.add(j);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(i).get(3 - i).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(j);
//                    winningPoint.add(3-j);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//
//                }
//                return v;
//            }
//        }
//
//        matches = 0;
//        for (int i = 0; i < 4; i++) {
//            if (board.get(3 - i).get(3 - i).get(i) .equals( piece)) matches++;
//            if (matches == 4) {
//                //return indices
//                for (int j = 0; j < 4; j++) {
//
//                    ArrayList<Integer> winningPoint = new ArrayList<Integer>();
//                    winningPoint.add(3-j);
//                    winningPoint.add(3-j);
//                    winningPoint.add(j);
//                    v.add(winningPoint);
//
//                }
//                return v;
//            }
//        }
//        return empty;
//    }
    /*****************************************************************************************************************************************/


    /*
     *
     * NEW DATA STRUCTURES
     *
     * */
    static Pane root;
    static boolean playerWin;
    static boolean userTurn =  true;
    static BitSet human ;
    static BitSet comp ;
    static BitSet game_board = new BitSet(64);
    static double MIN = Double.NEGATIVE_INFINITY;
    static double MAX = Double.POSITIVE_INFINITY;
    static Text end_message;
    static boolean gameOver = false;
    static Utility utility = new Utility();


    public static BitSet convertLong(long val) {
        long value = new Long(val);
        BitSet bits = new BitSet();
        int index = 0;
        while (value != 0L) {
            if (value % 2L != 0) {
                bits.set(index);
            }
            ++index;
            value = value >>> 1;
        }
        return bits;
    }

    public static long convertBit(BitSet bits) {

        long value = 0L;
        for (int i = 0; i < bits.length(); ++i) {
            value += bits.get(i) ? (1L << i) : 0L;
        }
        return value;
    }

    public static void view_Bit(BitSet bit){
        String s = "";
        for( int i = 0; i < bit.size();  i++ )
        {
          if(bit.get(i) == true){
              s+="1";
          }
          else{
              s+="0";
          }

        }

        System.out.println( s );
    }

    /* GAME TILE CLASS
    * */
    private static class GameTile extends StackPane {
        public Text text = new Text() ;
        public boolean taken =  false;
        int index ;

        ArrayList<Integer> location ;
        //draw X/O on tile
        public void drawSymbol(String symbol){
            text.setText(symbol);
            text.setFont(Font.font("Arial Black", 30));
            text.setFill(Color.PLUM);
        }

        public void setColor(){
            end_message = new Text("GAME OVER! CLICK END GAME TO VIEW SCORE");
            end_message.setFill(Color.WHITE);
            root.setStyle("-fx-background-color: linear-gradient(black, blue);");
            end_message.relocate(250,700);
            end_message.setFont(Font.font("Bodoni MT Black", 30));
            end_message.setFill(Color.WHITE);
            Controller.root.getChildren().add(end_message);

            DropShadow ds = new DropShadow();
            ds.setOffsetY(3.0);
            ds.setOffsetX(3.0);
            ds.setColor(Color.GRAY);
            end_message.setEffect(ds);

        }



        public static int minimax(BitSet hp, BitSet cp, int level,boolean isComp, double alpha, double beta ){

            BitSet currentboard = new BitSet(64);
            currentboard.or(hp);
            currentboard.or(cp);

            long hmp = hp.toLongArray()[0];
            long cmp;
            if(cp.length() == 0){
                cmp = new Long(0);
            }
            else{
                cmp = cp.toLongArray()[0];
            }

            if(level == 2){
                return utility.utilityFunction(hmp,cmp);
            }
            if(utility.Winner(hmp,cmp) == 1){
                return utility.utilityFunction(hmp,cmp);
            }
            if(utility.Winner(hmp,cmp) == 2){
                return utility.utilityFunction(hmp,cmp);
            }
//            if(currentboard.cardinality() == 64){
//                return 0;
//            }
            if(isComp){
                int bestMove = Integer.MIN_VALUE;

                for(int i = 0; i < currentboard.size(); i++){
                    if(!currentboard.get(i)) {
                        cp.set(i, true);
                        bestMove = Math.max(bestMove, minimax(hp, cp, level + 1, !isComp, alpha, beta));
                        alpha = Math.max(alpha, bestMove);
                        if (beta <= alpha) {
                            break;
                        }
                        cp.set(i, false);
                    }
                }
                return bestMove;

            }
           else{
                int bestMove = Integer.MAX_VALUE;
                for(int i = 0; i < currentboard.size(); i++){
                    if(!currentboard.get(i)) {
                        hp.set(i);
                        bestMove = Math.min(bestMove, minimax(hp, cp, level + 1, !isComp, alpha, beta));
                        alpha = Math.min(alpha, bestMove);
                        if (beta <= alpha) {
                            break;
                        }
                        hp.set(i,false);
                    }

                }
                return bestMove;

            }




        }
        public static int move_finder(BitSet hp, BitSet cp){

            BitSet currentboard = new BitSet(64);
            currentboard.or(hp);
            currentboard.or(cp);
           // System.out.println(currentboard);

            int bestMove = Integer.MIN_VALUE;
            //System.out.println(bestMove);
            int bestMoveAI = -1;
            for(int i = 0; i < currentboard.size(); i++){
                if(currentboard.get(i) == false){
                   //System.out.println("move is available");
                    currentboard.set(i,true);
                   // System.out.println(currentboard);

                    int move = minimax(hp, cp, 0,false, Integer.MIN_VALUE, Integer.MAX_VALUE);
                    //System.out.println(move);
                    currentboard.set(i,false);
                    //System.out.println(currentboard);

                    if(move > bestMove){
                        bestMove = move;
                        bestMoveAI = i;
                    }
                }
            }
            //System.out.println("bestMoveAI : " + bestMoveAI);
            return (bestMoveAI);
        }
        public static void clearBoard(){
            end_message.setText(" ");
            human = new BitSet(64);
            comp = new BitSet(64);
            for(int i = 0; i < root.getChildren().size(); i ++) {
                Node nodeOut = root.getChildren().get(i);
                if (nodeOut instanceof GameTile) {
                        ((GameTile) nodeOut).drawSymbol(" ");
                        ((GameTile) nodeOut).taken = false;
                        userTurn = true;
                        //gameOver = false;
                }
            }
        }

        public GameTile(){
            Region border = new Region();
            border.setPrefSize(60,60);
            border.setStyle("-fx-background-color: white ; -fx-background-radius: 10 10 10 10;");


            DropShadow ds = new DropShadow();
            ds.setOffsetY(2.0);
            ds.setOffsetX(2.0);
            ds.setColor(Color.GRAY);
            border.setEffect(ds);


            //text.setFont(Font.font(20));
            location = new ArrayList<Integer>();
            setAlignment(Pos.CENTER);
            getChildren().addAll(border, text);

            setOnMouseClicked(e-> {
                if (!Controller.gameOver) {
                    if (Controller.userTurn) {
                        if (taken == false) {
                            //update player board
                            Controller.human.set(index);
                            drawSymbol("X");
                            taken = true;
                            Controller.userTurn = false;
                            //check if won
                            long hmp = human.toLongArray()[0];
                            long cmp;
                            if(comp.length() == 0){
                                cmp = new Long(0);
                            }
                            else{
                                cmp = comp.toLongArray()[0];
                            }
                            if(utility.Winner(hmp, cmp) == 1){
                                playerWin = true;
                                System.out.println("USER HAS WON!");
                                gameOver = true;
                                setColor();
                                clearBoard();
                            }
                            else{ //play AI
                               int computer_move =  move_finder(human, comp);
                               Controller.comp.set(computer_move);
                               System.out.println(comp);
                               System.out.println(human);

                                Node nodeOut = root.getChildren().get(64-computer_move);
                                if (nodeOut instanceof GameTile) {
                                    if(!((GameTile) nodeOut).taken) {
                                        ((GameTile) nodeOut).drawSymbol("O");
                                        ((GameTile) nodeOut).taken = true;
                                    }
                                }
                                hmp = human.toLongArray()[0];
                                if(comp.length() == 0){
                                    cmp = new Long(0);
                                }
                                else{
                                    cmp = comp.toLongArray()[0];
                                }
                                if(utility.Winner(hmp, cmp) == 2){
                                    playerWin = false;
                                    System.out.println("COMPUTER HAS WON!");
                                    gameOver = true;
                                    setColor();
                                    clearBoard();
                                }
                                Controller.userTurn = true ;
                            }
                        }
                    }

                }
            });
        }
    }


    public static Parent createBoard(){

        int counter = 0;
        human = new BitSet(64);
        comp  = new BitSet(64);
        System.out.println(comp.size());

        Controller.root = new Pane();
        Controller.root.setPrefSize(1260,800);
        root.setStyle("-fx-background-color: linear-gradient(to bottom, #000000, #290f17, #4c1224, #710f31, #98003b);");

        Text title = new Text(" TIC-TAC-TOE");
        title.relocate(260,200);
        title.setFont(Font.font("Bodoni MT Black", 100));
        title.setFill(Color.WHITE);
        Controller.root.getChildren().add(title);

        DropShadow ds = new DropShadow();
        ds.setOffsetY(3.0);
        ds.setOffsetX(3.0);
        ds.setColor(Color.GRAY);
        title.setEffect(ds);


        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j ++){
                GameTile g = new GameTile();
                g.setTranslateX((j+1)* 60);
                g.setTranslateY((i+5)* 60);
                g.index = counter;
                //g.drawSymbol(Integer.toString(counter));
                root.getChildren().add(g);
                counter ++;

            }
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j ++){
                GameTile g = new GameTile();
                g.setTranslateX((j+6)* 60);
                g.setTranslateY((i+5)* 60);
                g.index = counter;
                //g.drawSymbol(Integer.toString(counter));
                root.getChildren().add(g);
                counter ++;

            }
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j ++){
                GameTile g = new GameTile();
                g.setTranslateX((j+11)* 60);
                g.setTranslateY((i+5)* 60);
                g.index = counter;
                //g.drawSymbol(Integer.toString(counter));
                root.getChildren().add(g);
                counter ++;

            }
        }

        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j ++){
                GameTile g = new GameTile();
                g.setTranslateX((j+16)* 60);
                g.setTranslateY((i+5)* 60);
                g.index = counter;
               // g.drawSymbol(Integer.toString(counter));
                root.getChildren().add(g);
                counter ++;

            }
        }

        return root;
    }


}
