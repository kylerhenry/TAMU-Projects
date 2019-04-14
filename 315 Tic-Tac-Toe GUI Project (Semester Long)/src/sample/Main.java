package sample;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.effect.DropShadow;
import javafx.scene.layout.Pane;
import javafx.scene.layout.StackPane;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.text.Font;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.scene.canvas.Canvas;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.control.TextField;
import javafx.geometry.HPos;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

public class Main extends Application {

    String currPlayer = "";

    boolean userTurn = true;
    Button button;

    Stage window;
    Scene splash; //initial screen
    Scene initials;
    Scene instr;
    Scene score;
    Scene game;
    Scene win;
    Scene lose;
    Scene exit;



    public native int updateUser(ArrayList<Integer> user, int move) ;
    public native int checkWin(ArrayList<ArrayList<ArrayList<String>>> board, int index);  // changing original function to just pass back size of list instead of entire arrayList
    public ArrayList<Integer> user;
    char symb_usr = 'X';
    //boolean playerWin = true;

    public static void main(String[] args) {
        launch(args);
    }

    /**
     * Read/Display Helper function
     * */
    public static String readDisplay(String filename) {
        // filename will be the complete file path
        //String scoresFile = "H:\\cs_315\\Project4-IntelliJ\\out\\production\\Project4\\src\\sample\\scores.txt";
        int i = 0;
        String display = "";
        File file = new File(filename);
        try {

            Scanner input = new Scanner(file);
            // Only displays the first 5 scores in the file
            if(filename.equals("..\\GUI1\\src\\sample\\scores.txt")) {
                System.out.println(filename);
                while(input.hasNext() && i < 5) {
                    String line = input.nextLine();
                    display += line + "\n";
                    i++;
                }
            }
            else {
                while(input.hasNext()) {
                    String line = input.nextLine();
                    display += line + "\n";
                }
            }
        }
        catch(Exception e) {

        }
        return display;
    }

    /**
     * Write Helper function
     * */
    public static void writeFile (String input) {
        String filename = "..\\GUI1\\src\\sample\\scores.txt";
        BufferedWriter bw = null;
        FileWriter fw = null;

        try {

            File file = new File(filename);

            // true = append file
            fw = new FileWriter(file.getAbsoluteFile(), true);
            bw = new BufferedWriter(fw);

            bw.write("\n");
            bw.write(input);
            bw.write(" 0");
            //bw.write("\n");

        } catch (IOException e) {

            e.printStackTrace();

        } finally {

            try {

                if (bw != null)
                    bw.close();

                if (fw != null)
                    fw.close();

            } catch (IOException ex) {

                ex.printStackTrace();

            }
        }
    }

    /**
     * Scores Adding/Sorting Helper function
     * */
    public static void scoresUpdate(String currPlayer) {

        String filename = "..\\GUI1\\src\\sample\\scores.txt";
        BufferedWriter bw = null;
        FileWriter fw = null;

        List<Integer> scores = new ArrayList<>();
        ArrayList<String> init = new ArrayList<>();

        try {
            File file = new File(filename);

            Scanner input = new Scanner(file);

            while(input.hasNext()) {
                String line = input.nextLine();

                // Separates initials and corresponding scores
                String[] noSpaces = line.split(" ");

                for (int i = 0; i < noSpaces.length - 1; i += 2) {
                    // Creates list of scores
                    scores.add(Integer.parseInt(noSpaces[i + 1]));

                    // Creates list of initials
                    init.add(noSpaces[i]);
                }
            }

            // Updates currScore for currPlayer
            for(int i = 0; i < init.size() - 1; i++) {
                if(init.get(i).equals(currPlayer)) {
                    int currScore = scores.get(i);
                    currScore += 1;
                    scores.set(i, currScore);
                }
            }


            // Sorts scores
            for(int i = 0; i < scores.size() - 1; i++) {
                if(scores.get(i) < scores.get(i + 1)) {
                    // Resorting scores
                    int tempScore = scores.get(i + 1);
                    scores.set(i + 1, scores.get(i));
                    scores.set(i, tempScore);
                    // Resorting initials corresponding to scores
                    String tempInitials = init.get(i + 1);
                    init.set(i + 1, init.get(i));
                    init.set(i, tempInitials);
                }
            }

            // Updates scores.txt file
            // If false, then clears file and write to it again
            fw = new FileWriter(file.getAbsoluteFile(), false);
            bw = new BufferedWriter(fw);
            for(int i = 0; i < init.size() - 1; i++) {
                bw.write(init.get(i) + " " + scores.get(i) + "\n");
            }

        } catch (IOException e) {

            e.printStackTrace();

        } finally {

            try {

                if (bw != null)
                    bw.close();

                if (fw != null)
                    fw.close();

            } catch (IOException ex) {

                ex.printStackTrace();

            }
        }
    }

    @Override
    public void start(Stage primaryStage) throws Exception{
        //Parent root = FXMLLoader.load(getClass().getResource("sample.fxml"));
        window = primaryStage;

        /*
         *
         * SPLASH SCREEN
         *
         * */
        Label l1 = new Label("TEAM 9: ");
        l1.setTextFill(Color.BLACK);
        l1.setFont(Font.font("Bodoni MT Black", 14));
        DropShadow dsTeam = new DropShadow();
        dsTeam.setOffsetY(3.0);
        dsTeam.setOffsetX(3.0);
        dsTeam.setColor(Color.LIGHTPINK);
        l1.setEffect(dsTeam);

        // positive is L and negative is R
        l1.setTranslateX(-300);
        // Negative is up and positive is down
        l1.setTranslateY(-145);

        Label l3 = new Label("Bethany Cole");
        // positive is L and negative is R
        l3.setTranslateX(-300);
        // Negative is up and positive is down
        l3.setTranslateY(-120);

        Label l7 = new Label("Sakshi Choudary");
        // positive is L and negative is R
        l7.setTranslateX(-300);
        // Negative is up and positive is down
        l7.setTranslateY(-100);

        Label l8 = new Label("Kyle Henry");
        // positive is L and negative is R
        l8.setTranslateX(-300);
        // Negative is up and positive is down
        l8.setTranslateY(-80);

        Label l9 = new Label("Roby Nkwamo");
        // positive is L and negative is R
        l9.setTranslateX(-300);
        // Negative is up and positive is down
        l9.setTranslateY(-60);

        //create first button
        button = new Button("Add Player");
        button.setTranslateX(0);
        button.setTranslateY(250);

        button.setStyle(" -fx-background-color: \n" +
                "        #090a0c,\n" +
                "        linear-gradient(#38424b 0%, #1f2429 20%, #191d22 100%),\n" +
                "        linear-gradient(#20262b, #191d22),\n" +
                "        radial-gradient(center 50% 0%, radius 100%, rgba(114,131,148,0.9), rgba(255,255,255,0));\n" +
                "    -fx-background-radius: 5,4,3,5;\n" +
                "    -fx-background-insets: 0,1,2,0;\n" +
                "    -fx-text-fill: white;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 5, 0.0 , 0 , 1 );\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: linear-gradient(white, #d0d0d0);\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( one-pass-box , rgba(0,0,0,0.9) , 1, 0.0 , 0 , 1 );");

        // Call readDisplay function to print high scores to console
        // This System.out.println path works on console, now to just switch it to screen
        // System.out.println("calling function " + readDisplay("..\\GUI1\\src\\sample\\scores.txt"));
        Label lHigh = new Label("High Scores: " + "\n");
        lHigh.setTranslateX(-300);
        lHigh.setTranslateY(35);
        lHigh.setTextFill(Color.BLACK);
        lHigh.setFont(Font.font("Bodoni MT Black", 14));
        DropShadow dsHigh = new DropShadow();
        dsHigh.setOffsetY(3.0);
        dsHigh.setOffsetX(3.0);
        dsHigh.setColor(Color.YELLOW);
        lHigh.setEffect(dsHigh);

        String scoreOut = readDisplay("..\\GUI1\\src\\sample\\scores.txt");
        Label l4 = new Label(scoreOut);
        l4.setTranslateX(-300);
        l4.setTranslateY(100);

        final ImageView selectedImage = new ImageView();
        Image image1 = new Image(new FileInputStream("..\\GUI1\\titlev2.png"));
        selectedImage.setImage(image1);

        button.setOnAction(e->Controller.example(window, initials));

        StackPane layout1 = new StackPane(); //a type of layout where children are laid out in vertical column;
        layout1.setStyle("-fx-background-color: linear-gradient(to bottom, #000000, #290f17, #4c1224, #710f31, #98003b);");
        layout1.getChildren().addAll(selectedImage, l1, l3, lHigh, l4, l7, l8, l9, button);

        splash = new Scene(layout1, 850,700);

//////////////Initials screen
        /*
         *
         * INITIALS SCREEN
         *
         * */

        GridPane rootNode = new GridPane();
        rootNode.setPadding(new Insets(15));
        rootNode.setHgap(5);
        rootNode.setVgap(5);
        rootNode.setAlignment(Pos.CENTER);

        rootNode.setStyle("-fx-background-color: linear-gradient(to bottom, #000000, #290f17, #4c1224, #710f31, #98003b);");

        Text title = new Text("Please Enter your Initials: ");
        title.relocate(700,300);
        title.setFont(Font.font("Bodoni MT Black", 30));
        title.setFill(Color.WHITE);
        rootNode.getChildren().add(title);

        DropShadow ds = new DropShadow();
        ds.setOffsetY(3.0);
        ds.setOffsetX(3.0);
        ds.setColor(Color.GRAY);
        title.setEffect(ds);

        Button button3 = new Button("Game Instructions");
        button3.setStyle("-fx-background-color:\n" +
                "        #090a0c,\n" +
                "        linear-gradient(#38424b 0%, #1f2429 20%, #191d22 100%),\n" +
                "        linear-gradient(#20262b, #191d22),\n" +
                "        radial-gradient(center 50% 0%, radius 100%, rgba(114,131,148,0.9), rgba(255,255,255,0));\n" +
                "    -fx-background-radius: 5,4,3,5;\n" +
                "    -fx-background-insets: 0,1,2,0;\n" +
                "    -fx-text-fill: white;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 5, 0.0 , 0 , 1 );\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: linear-gradient(white, #d0d0d0);\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( one-pass-box , rgba(0,0,0,0.9) , 1, 0.0 , 0 , 1 );");

        TextField firstValue = new TextField();
        //rootNode.add(new Label("Please Enter your Initials: "), 0, 0);
        rootNode.add(firstValue, 1, 0);
        rootNode.add(button3, 1, 2);
        GridPane.setHalignment(button3, HPos.LEFT);
        initials = new Scene(rootNode, 850,700);

        button3.setOnAction(e-> {
            String value1 = String.valueOf(firstValue.getText());
            writeFile(value1);
            currPlayer = value1;
            Controller.example(window, instr);
        });
///////////////////

        /*
         *
         * INSTRUCTION SCREEN
         *
         * */


        // transition to instruction scene
        GridPane rootNode1 = new GridPane();
        rootNode1.setPadding(new Insets(15));
        rootNode1.setHgap(5);
        rootNode1.setVgap(5);
        rootNode1.setAlignment(Pos.CENTER);
        rootNode1.setStyle("-fx-background-color: linear-gradient(to bottom, #000000, #290f17, #4c1224, #710f31, #98003b);");

        String instructions = readDisplay("..\\GUI1\\src\\sample\\instruc.txt");

        Text title2 = new Text(instructions);
        //title2.relocate(5,30);
        title2.setFont(Font.font("Bodoni MT Black", 17));
        title2.setFill(Color.WHITE);
        rootNode1.add(title2, 0, 5);

        DropShadow ds1 = new DropShadow();
        ds1.setOffsetY(3.0);
        ds1.setOffsetX(3.0);
        ds1.setColor(Color.GRAY);
        title2.setEffect(ds);

        Button button2 = new Button("Play Game");
        button2.setStyle("-fx-background-color:\n" +
                "        linear-gradient(#f0ff35, #a9ff00),\n" +
                "        radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%);\n" +
                "    -fx-background-radius: 6, 5;\n" +
                "    -fx-background-insets: 0, 1;\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-size: 14px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );\n" +
                "    -fx-text-fill: black;");

        rootNode1.add(button2, 5, 7);

        // Add Instructions labels and asking for initials
        // Get initials with Java code and then implement C++ for updating file

        //CURRENTLY TRANSITIONS TO game-- NEEDS TO BE CHANGED ONCE THERE IS A BUTTON FOR GAME.

        button2.setOnAction(e->window.setScene(game));

        // CURRENTLY TRANSITIONS TO game-- NEEDS TO BE CHANGED ONCE THERE IS A BUTTON FOR GAME.

        instr = new Scene(rootNode1, 850,700);


        /*
         *
         * GAME
         *
         * */

        //game = new Scene(Controller.createBoard());

        // end_game button ends game if person clicks it when the game isnt over yet
        // otherwise, it will go to win/lose screen dependent upon if the player won or lost
        Button end_game = new Button("End Game");
        //end_game.setAlignment(Pos.BOTTOM_LEFT);
        end_game.setStyle("-fx-background-color: linear-gradient(#ff5400, #be1d00);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0;\n" +
                "    -fx-text-fill: white;\n" +
                "     -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: white;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        end_game.setTranslateX(-500);
        end_game.setTranslateY(300);

        end_game.setOnAction(e->{
            if(Controller.gameOver){
                Controller.gameOver = false;
                System.out.println(Controller.playerWin);
                if(Controller.playerWin) {
                    scoresUpdate(currPlayer);
                    window.setScene(win);
                }
                else {
                    window.setScene(lose);
                }
            }
            else {
                // Exit game screen to make sure they would like to exit
                window.setScene(exit);
            }
        });

        StackPane layout_end = new StackPane();
        layout_end.getChildren().addAll(Controller.createBoard(), end_game);

        game = new Scene(layout_end);



        /*
         *
         * PLAY AGAIN/WIN screen
         *
         * */
        GridPane rootWin = new GridPane();
        rootWin.setPadding(new Insets(15));
        rootWin.setHgap(5);
        rootWin.setVgap(5);
        rootWin.setAlignment(Pos.CENTER);

        rootWin.setStyle("-fx-background-color: black;");

        final ImageView winImage = new ImageView();
        Image imageWin = new Image(new FileInputStream("..\\GUI1\\src\\sample\\youwin.jpg"));
        winImage.setImage(imageWin);

        winImage.setFitWidth(500);
        winImage.setPreserveRatio(true);
        winImage.setSmooth(true);
        winImage.setCache(true);

        rootWin.getChildren().add(winImage);

        String endScores = readDisplay("..\\GUI1\\src\\sample\\scores.txt");

        Label lWinScores = new Label("High Scores: " + "\n" + endScores);
        lWinScores.setTranslateX(600);
        lWinScores.setTranslateY(0);
        lWinScores.setTextFill(Color.WHITE);
        lWinScores.setFont(Font.font("Bodoni MT Black", 17));
        DropShadow dsWin = new DropShadow();
        dsWin.setOffsetY(3.0);
        dsWin.setOffsetX(3.0);
        dsWin.setColor(Color.YELLOW);
        lWinScores.setEffect(dsWin);
        rootWin.getChildren().add(lWinScores);

        Button buttonEnd = new Button("Exit");
        Button playAgain = new Button("Play Again");
        Button newPlayer = new Button("New Player");

        // Shiny orange button
        playAgain.setStyle("-fx-background-color:\n" +
                "        linear-gradient(#ffd65b, #e68400),\n" +
                "        linear-gradient(#ffef84, #f2ba44),\n" +
                "        linear-gradient(#ffea6a, #efaa22),\n" +
                "        linear-gradient(#ffe657 0%, #f8c202 50%, #eea10b 100%),\n" +
                "        linear-gradient(from 0% 0% to 15% 50%, rgba(255,255,255,0.9), rgba(255,255,255,0));\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        buttonEnd.setStyle("-fx-background-color: linear-gradient(#ff5400, #be1d00);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-text-fill: white;\n" +
                "     -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        newPlayer.setStyle("-fx-background-color:\n" +
                "        #c3c4c4,\n" +
                "        linear-gradient(#d6d6d6 50%, white 100%),\n" +
                "        radial-gradient(center 50% -40%, radius 200%, #e6e6e6 45%, rgba(230,230,230,0) 50%);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,1;\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 3, 0.0 , 0 , 1 );");

        rootWin.add(buttonEnd, 0, 2);
        GridPane.setHalignment(buttonEnd, HPos.LEFT);

        rootWin.add(playAgain, 2, 2);
        GridPane.setHalignment(playAgain, HPos.LEFT);

        rootWin.add(newPlayer, 5, 2);
        GridPane.setHalignment(newPlayer, HPos.LEFT);

        buttonEnd.setOnAction(e-> {
            window.hide();
        });

        playAgain.setOnAction(e->{window.setScene(game);});

        newPlayer.setOnAction(e->Controller.example(window, initials));

        win = new Scene(rootWin, 850,700);


        /*
         *
         * PLAY AGAIN/LOSE screen
         *
         * */
        // Exactly same as win screen except says lose and doesnt update scores file
        // so only needs to display scores
        GridPane rootLose = new GridPane();
        rootLose.setPadding(new Insets(15));
        rootLose.setHgap(5);
        rootLose.setVgap(5);
        rootLose.setAlignment(Pos.CENTER);

        // Need to change to pop more
        rootLose.setStyle("-fx-background-color: black;");

        final ImageView loseImage = new ImageView();
        Image imageLose = new Image(new FileInputStream("..\\GUI1\\src\\sample\\ha-ha-you-lose.jpg"));
        loseImage.setImage(imageLose);

        loseImage.setFitWidth(500);
        loseImage.setPreserveRatio(true);
        loseImage.setSmooth(true);
        loseImage.setCache(true);

        rootLose.getChildren().add(loseImage);

        Label lLoseScores = new Label("High Scores: " + "\n" + endScores);
        lLoseScores.setTranslateX(600);
        lLoseScores.setTranslateY(0);
        lLoseScores.setTextFill(Color.WHITE);
        lLoseScores.setFont(Font.font("Bodoni MT Black", 17));
        DropShadow dsLose = new DropShadow();
        dsLose.setOffsetY(3.0);
        dsLose.setOffsetX(3.0);
        dsLose.setColor(Color.RED);
        lLoseScores.setEffect(dsLose);
        rootLose.getChildren().add(lLoseScores);

        Button buttonEnd2 = new Button("Exit");
        Button playAgain2 = new Button("Play Again");
        Button newPlayer2 = new Button("New Player");

        // Shiny orange button
        playAgain2.setStyle("-fx-background-color:\n" +
                "        linear-gradient(#ffd65b, #e68400),\n" +
                "        linear-gradient(#ffef84, #f2ba44),\n" +
                "        linear-gradient(#ffea6a, #efaa22),\n" +
                "        linear-gradient(#ffe657 0%, #f8c202 50%, #eea10b 100%),\n" +
                "        linear-gradient(from 0% 0% to 15% 50%, rgba(255,255,255,0.9), rgba(255,255,255,0));\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        buttonEnd2.setStyle("-fx-background-color: linear-gradient(#ff5400, #be1d00);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-text-fill: white;\n" +
                "     -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        newPlayer2.setStyle("-fx-background-color:\n" +
                "        #c3c4c4,\n" +
                "        linear-gradient(#d6d6d6 50%, white 100%),\n" +
                "        radial-gradient(center 50% -40%, radius 200%, #e6e6e6 45%, rgba(230,230,230,0) 50%);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,1;\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-family: \"Old English Text MT\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-weight: bold;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 3, 0.0 , 0 , 1 );");


        rootLose.add(buttonEnd2, 0, 2);
        GridPane.setHalignment(buttonEnd2, HPos.LEFT);

        rootLose.add(playAgain2, 2, 2);
        GridPane.setHalignment(playAgain2, HPos.CENTER);

        rootLose.add(newPlayer2, 5, 2);
        GridPane.setHalignment(newPlayer2, HPos.RIGHT);

        buttonEnd2.setOnAction(e-> {
            window.hide();
        });

        playAgain2.setOnAction(e->window.setScene(game));

        newPlayer2.setOnAction(e->Controller.example(window, initials));

        lose = new Scene(rootLose, 850,700);

        /*
         *
         * Exit Game screen
         *
         **/
        GridPane rootExit = new GridPane();
        rootExit.setPadding(new Insets(15));
        rootExit.setHgap(5);
        rootExit.setVgap(5);
        rootExit.setAlignment(Pos.CENTER);

        Label lEnd = new Label("YOU HAVE ENDED" + "\n");
        rootExit.setStyle("-fx-background-color: linear-gradient(to bottom, #000000, #290f17, #4c1224, #710f31, #98003b);");
        lEnd.setTranslateX(20);
        lEnd.setTranslateY(-100);
        lEnd.setTextFill(Color.WHITE);
        lEnd.setFont(Font.font("Bodoni MT Black", 70));
        DropShadow dsEnd = new DropShadow();
        dsEnd.setOffsetY(3.0);
        dsEnd.setOffsetX(3.0);
        dsEnd.setColor(Color.RED);
        lEnd.setEffect(dsEnd);

        Label lEnd2 = new Label("THE GAME");
        lEnd2.setTranslateX(170);
        lEnd2.setTranslateY(50);
        lEnd2.setTextFill(Color.WHITE);
        lEnd2.setFont(Font.font("Bodoni MT Black", 70));
        DropShadow dsEnd2 = new DropShadow();
        dsEnd2.setOffsetY(3.0);
        dsEnd2.setOffsetX(3.0);
        dsEnd2.setColor(Color.RED);
        lEnd2.setEffect(dsEnd2);

        rootExit.getChildren().addAll(lEnd, lEnd2);

        Button buttonEnd3 = new Button("Exit");
        Button playAgain3 = new Button("New Game");
        Button newPlayer3 = new Button("New Player");

        // Shiny orange button
        playAgain3.setStyle("-fx-background-color:\n" +
                "        linear-gradient(#f0ff35, #a9ff00),\n" +
                "        radial-gradient(center 50% -40%, radius 200%, #b8ee36 45%, #80c800 50%);\n" +
                "    -fx-background-radius: 6, 5;\n" +
                "    -fx-background-insets: 0, 1;\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.4) , 5, 0.0 , 0 , 1 );\n" +
                "    -fx-text-fill: black;");

        buttonEnd3.setStyle("-fx-background-color: linear-gradient(#ff5400, #be1d00);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-text-fill: white;\n" +
                "     -fx-background-insets: 0,1,2,3,0;\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;");

        newPlayer3.setStyle("-fx-background-color:\n" +
                "        #c3c4c4,\n" +
                "        linear-gradient(#d6d6d6 50%, white 100%),\n" +
                "        radial-gradient(center 50% -40%, radius 200%, #e6e6e6 45%, rgba(230,230,230,0) 50%);\n" +
                "    -fx-background-radius: 30;\n" +
                "    -fx-background-insets: 0,1,1;\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-family: \"Bodoni MT Black\";\n" +
                "    -fx-text-fill: black;\n" +
                "    -fx-font-size: 18px;\n" +
                "    -fx-padding: 10 20 10 20;\n" +
                "    -fx-effect: dropshadow( three-pass-box , rgba(0,0,0,0.6) , 3, 0.0 , 0 , 1 );");

        rootExit.add(buttonEnd3, 0, 25);
        //GridPane.setHalignment(buttonEnd3, HPos.LEFT);

        rootExit.add(playAgain3, 0, 30);
        //GridPane.setHalignment(playAgain3, HPos.CENTER);

        rootExit.add(newPlayer3, 0, 35);
        //GridPane.setHalignment(newPlayer3, HPos.RIGHT);

        buttonEnd3.setOnAction(e-> {
            window.hide();
        });

        playAgain3.setOnAction(e->window.setScene(game));

        newPlayer3.setOnAction(e->Controller.example(window, initials));

        exit = new Scene(rootExit, 1000,700);

        // Just ask if they would really like to exit or not

        //start window
        window.setScene(splash);
        window.show();



    }




}
