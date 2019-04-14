using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Collections;

namespace TicTacToeGUI
{
    public partial class Form5 : Form
    {
        public Form5()
        {
            InitializeComponent();
        }

        private void Form5_Load(object sender, EventArgs e)
        {
            Console.WriteLine(GlobalClass.pl_in);

        }

        private void Form5_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        //defines all board squares (changed in form designer)
        private void diamond_Button_Click(object sender, EventArgs e)
        {
            //only activates on player's turn
            if (GlobalClass.pTurn)
            {
                var button = (Button)sender;
                //checks if position has been played already
                if ((button.BackgroundImage != TicTacToeGUI.Properties.Resources.X) || (button.BackgroundImage != TicTacToeGUI.Properties.Resources.O))
                {
                    //display valid move
                    label1.Text = "Valid";
                    label1.BackColor = Color.Green;
                    //set tile to X
                    button.BackgroundImage = TicTacToeGUI.Properties.Resources.X;
                    int index = button.TabIndex;    //TabIndex is a default button property
                    Console.WriteLine(index);       //FIXME: USED FOR DEBUGGING (DELETE)
                    //disable button from further clicking
                    button.Enabled = false;
                   
                    //update player board (binary)
                    GlobalClass.pGame.Set(index, true);
                    //update player unsigned int
                    GlobalClass.pUint = GlobalClass.GetIntFromBitArray(GlobalClass.pGame);
                    
                    //check if player just won
                    int winner = GlobalClass.checkWin();




                    //***************FIXME: USED FOR DEBUGGING (DELETE)
                    for (int i = 0; i< GlobalClass.pGame.Length; ++i)
                    {
                        long tempInt = Convert.ToInt64(GlobalClass.pGame.Get(i));
                        Console.Write(tempInt);
                    }






                    if (winner > 0)
                    {
                        //player just won or draw
                        if (winner == 1)
                        {
                            //player won
                            this.BackgroundImage = TicTacToeGUI.Properties.Resources.game_won;
                            button1.BackgroundImage = TicTacToeGUI.Properties.Resources.splashbutton1;
                           // GlobalClass.whoWON = true;

                            GlobalClass.whoWON = true; 
                        }
                        else
                        {
                            //draw
                            this.BackgroundImage = TicTacToeGUI.Properties.Resources.game_draw;
                            button1.BackgroundImage = TicTacToeGUI.Properties.Resources.splashbutton1;
                        }
                        //disable all buttons
                        foreach (Control c in Controls)
                        {
                            Button b = c as Button;
                        }
                        //enable continue button
                        button1.Enabled = true;
                    }
                    else
                    {
                        
                        //********CALL AI HERE********
                         GlobalClass.pTurn = false;
                         if (!GlobalClass.pTurn)
                         {
                             // call bestMoveFinder
                             // set int obtained from bestMoveFinder to true in the cGame BitArray
                             int best = GlobalClass.BestMoveFinder();
                             Console.WriteLine(best);
                            // Actually play the corresponding tile
                             play_AI(best);
                            //update comp board (binary)
                            GlobalClass.cGame.Set(best, true);
                            //update comp unsigned int
                            GlobalClass.cUint = GlobalClass.GetIntFromBitArray(GlobalClass.cGame);
                         }

                        int win = GlobalClass.checkWin();
                        // Checks AI moves now (so does not check player's moves)
                        if (win > 0)
                        {
                            if (win == 2)
                            {
                                //comp won
                                this.BackgroundImage = TicTacToeGUI.Properties.Resources.game_lost;
                                button1.BackgroundImage = TicTacToeGUI.Properties.Resources.splashbutton1;
                            }
                            else
                            {
                                //draw
                                this.BackgroundImage = TicTacToeGUI.Properties.Resources.game_draw;
                                button1.BackgroundImage = TicTacToeGUI.Properties.Resources.splashbutton1;
                            }

                            //disable all buttons
                            foreach (Control c in Controls)
                            {
                                Button b = c as Button;
                            }
                            //enable continue button
                            button1.Enabled = true;
                        }
                        else
                        {
                            //***************FIXME: USED FOR DEBUGGING (DELETE)
                            for (int i = 0; i < GlobalClass.pGame.Length; ++i)
                            {
                                long tempInt = Convert.ToInt64(GlobalClass.pGame.Get(i));
                                Console.Write(tempInt);
                            }
                            // Now it is the players turn again
                            GlobalClass.pTurn = true;
                        }
                    }

                }
                else
                {
                    //display invalid move
                    label1.BackColor = Color.Maroon;
                    label1.Text = "Invalid";
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            //existing player 
            string[] lines = System.IO.File.ReadAllLines(Directory.GetCurrentDirectory() + "\\scores.txt");
            int i = 0;
            Boolean found = false; 
            foreach (string line in lines) {
                
                    if (line.Contains(GlobalClass.pl_in)) {
                    found = true;
                    Console.WriteLine("found"); 
                        if (GlobalClass.whoWON)
                        {
                            int index = GlobalClass.IN.IndexOf(GlobalClass.IN.Where(p => p == GlobalClass.pl_in).FirstOrDefault());
                            Console.WriteLine("at index" + index);

                            GlobalClass.DV[index]++; 
                
                            lines[i] = GlobalClass.pl_in + " " + GlobalClass.DV[index];
                            Console.WriteLine(lines[i]);


                    }
                }
                i++; 
            }
            System.IO.File.WriteAllLines(Directory.GetCurrentDirectory() + "\\scores.txt", lines);
            if (!found)
            {
                string path = Directory.GetCurrentDirectory() + "\\scores.txt";
                if (!File.Exists(path))
                {
                    Console.WriteLine("file doesn't exist for some reason");
                    // Create a file to write to.
                    using (StreamWriter sw = File.CreateText(path))
                    {
                        string score = "0";
                        if (GlobalClass.whoWON)
                        {
                            score = "1";
                        }
                        sw.WriteLine(GlobalClass.pl_in + " " + score);
                    }
                }
                using (StreamWriter sw = File.AppendText(path))
                {
                    Console.WriteLine("new player");
                    string score = "0";
                    if (GlobalClass.whoWON)
                    {
                        score = "1";
                    }
                    sw.WriteLine(GlobalClass.pl_in + " " + score);
                }

            }

            
            if (GlobalClass.whoWON)
            {//player won
                Form7 form7 = new Form7();
                this.Hide();
                form7.ShowDialog();
            }
            else { //player lost
                Form8 form8 = new Form8();
                this.Hide();
                form8.ShowDialog();
            }

            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }


 private void play_AI(int index)
        {
            //display AI MOVE
            label1.Text = "AI MOVE";
            label1.BackColor = Color.Aqua;

            switch (index)
            {
                case 0 :
                    diamond_Button1.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button1.Enabled = false;
                    break;
                case 1 :
                    diamond_Button2.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button2.Enabled = false;
                    break;
                case 2 :
                    diamond_Button3.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button3.Enabled = false;
                    break;
                case 3 :
                    diamond_Button4.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button4.Enabled = false;
                    break;
                case 4 :
                    diamond_Button5.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button5.Enabled = false;
                    break;
                case 5 :
                    diamond_Button6.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button6.Enabled = false;
                    break;
                case 6 :
                    diamond_Button7.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button7.Enabled = false;
                    break;
                case 7 :
                    diamond_Button8.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button8.Enabled = false;
                    break;
                case 8 :
                    diamond_Button9.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button9.Enabled = false;
                    break;
                case 9 :
                    diamond_Button10.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button10.Enabled = false;
                    break;
                case 10 :
                    diamond_Button11.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button11.Enabled = false;
                    break;
                case 11 :
                    diamond_Button12.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button12.Enabled = false;
                    break;
                case 12 :
                    diamond_Button13.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button13.Enabled = false;
                    break;
                case 13 :
                    diamond_Button14.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button14.Enabled = false;
                    break;
                case 14 :
                    diamond_Button15.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button15.Enabled = false;
                    break;
                case 15 :
                    diamond_Button16.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button16.Enabled = false;
                    break;
                case 16 :
                    diamond_Button17.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button17.Enabled = false;
                    break;
                case 17 :
                    diamond_Button18.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button18.Enabled = false;
                    break;
                case 18 :
                    diamond_Button19.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button19.Enabled = false;
                    break;
                case 19 :
                    diamond_Button20.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button20.Enabled = false;
                    break;
                case 20 :
                    diamond_Button21.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button21.Enabled = false;
                    break;
                case 21 :
                    diamond_Button22.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button22.Enabled = false;
                    break;
                case 22 :
                    diamond_Button23.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button23.Enabled = false;
                    break;
                case 23 :
                    diamond_Button24.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button24.Enabled = false;
                    break;
                case 24 :
                    diamond_Button25.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button25.Enabled = false;
                    break;
                case 25 :
                    diamond_Button26.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button26.Enabled = false;
                    break;
                case 26 :
                    diamond_Button27.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button27.Enabled = false;
                    break;
                case 27 :
                    diamond_Button28.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button28.Enabled = false;
                    break;
                case 28 :
                    diamond_Button29.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button29.Enabled = false;
                    break;
                case 29 :
                    diamond_Button30.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button30.Enabled = false;
                    break;
                case 30 :
                    diamond_Button31.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button31.Enabled = false;
                    break;
                case 31 :
                    diamond_Button32.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button32.Enabled = false;
                    break;
                case 32 :
                    diamond_Button33.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button33.Enabled = false;
                    break;
                case 33 :
                    diamond_Button34.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button34.Enabled = false;
                    break;
                case 34 :
                    diamond_Button35.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button35.Enabled = false;
                    break;
                case 35 :
                    diamond_Button36.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button36.Enabled = false;
                    break;
                case 36 :
                    diamond_Button37.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button37.Enabled = false;
                    break;
                case 37 :
                    diamond_Button38.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button38.Enabled = false;
                    break;
                case 38 :
                    diamond_Button39.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button39.Enabled = false;
                    break;
                case 39 :
                    diamond_Button40.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button40.Enabled = false;
                    break;
                case 40 :
                    diamond_Button41.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button41.Enabled = false;
                    break;
                case 41 :
                    diamond_Button42.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button42.Enabled = false;
                    break;
                case 42 :
                    diamond_Button43.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button43.Enabled = false;
                    break;
                case 43 :
                    diamond_Button44.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button44.Enabled = false;
                    break;
                case 44 :
                    diamond_Button45.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button45.Enabled = false;
                    break;
                case 45 :
                    diamond_Button46.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button46.Enabled = false;
                    break;
                case 46 :
                    diamond_Button47.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button47.Enabled = false;
                    break;
                case 47 :
                    diamond_Button48.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button48.Enabled = false;
                    break;
                case 48 :
                    diamond_Button49.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button49.Enabled = false;
                    break;
                case 49 :
                    diamond_Button50.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button50.Enabled = false;
                    break;
                case 50 :
                    diamond_Button51.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button51.Enabled = false;
                    break;
                case 51 :
                    diamond_Button52.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button52.Enabled = false;
                    break;
                case 52 :
                    diamond_Button53.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button53.Enabled = false;
                    break;
                case 53 :
                    diamond_Button54.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button54.Enabled = false;
                    break;
                case 54 :
                    diamond_Button55.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button55.Enabled = false;
                    break;
                case 55 :
                    diamond_Button56.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button56.Enabled = false;
                    break;
                case 56 :
                    diamond_Button57.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button57.Enabled = false;
                    break;
                case 57 :
                    diamond_Button58.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button58.Enabled = false;
                    break;
                case 58 :
                    diamond_Button59.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button59.Enabled = false;
                    break;
                case 59 :
                    diamond_Button60.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button60.Enabled = false;
                    break;
                case 60 :
                    diamond_Button61.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button61.Enabled = false;
                    break;
                case 61 :
                    diamond_Button62.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button62.Enabled = false;
                    break;
                case 62 :
                    diamond_Button63.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button63.Enabled = false;
                    break;
                case 63 :
                    diamond_Button64.BackgroundImage = TicTacToeGUI.Properties.Resources.O;
                    diamond_Button64.Enabled = false;
                    break;
            }
        }

        
    }
}
