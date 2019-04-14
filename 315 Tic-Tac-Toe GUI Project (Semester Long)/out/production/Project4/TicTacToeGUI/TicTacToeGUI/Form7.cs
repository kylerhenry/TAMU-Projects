using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeGUI
{
    public partial class Form7 : Form
    {
        public Form7()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            GlobalClass.whoWON = false;
            GlobalClass.pGame = new BitArray(64);
            GlobalClass.cGame = new BitArray(64);
            GlobalClass.pUint = 0;
            GlobalClass.cUint = 0;
            GlobalClass.playerTurn = true;

            Form5 playagain= new Form5();
            this.Hide();
            playagain.ShowDialog(); 

        }

        private void button2_Click(object sender, EventArgs e)
        {
 
            Application.Exit();
        }

        private void Form7_Load(object sender, EventArgs e)
        {

        }

        private void Form7_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit(); 
        }
    }
}
