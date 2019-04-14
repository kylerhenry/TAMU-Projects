using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeGUI
{
    public partial class Form1 : Form
    {

        public Form1()
        {
            InitializeComponent();

        }
        
          
       
        private void Form1_Load(object sender, EventArgs e)
        {
            GlobalClass.changeText = "TRIAL";

        }

        private void button1_Click(object sender, EventArgs e)
        {
           
            Form2 form2 = new Form2();
            this.Hide();
            form2.ShowDialog(); 


        }


        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

       
    }
}
