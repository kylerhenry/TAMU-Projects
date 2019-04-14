using System;
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
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit(); 
        }

        private void button2_Click_1(object sender, EventArgs e)
        {
            Form3 high_scores = new Form3();
            this.Hide();
            high_scores.ShowDialog();

        }

        private void Form2_Load(object sender, EventArgs e)
        {
        }
    }
}
