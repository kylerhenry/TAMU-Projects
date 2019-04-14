using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeGUI
{
    public partial class Form4 : Form
    {

        //        private const string DllFilePath = @"C:\\Users\\Sakshi\Documents\\2018\\csce315\\TTT_GUI2\\t1\\GUI1\\Dll\\TicTacToe_Gui2\\Debug\\TicTacToe_Gui2.dll";

        //   [DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
        //private extern static void readScores(string filename, int size1, int size2, ref string[] initials, ref int[] scores);
        //private extern static void readScores([Out] IntPtr[] initials, int size1,[Out] IntPtr[] scores, int size);


        //[DllImport("AudioPluginSpecDelay")]
        //private static extern void getArray(out int length, out IntPtr array);
        /*private const string DllFilePath = @"C:\\Users\\Sakshi\Documents\\2018\\csce315\\TTT_GUI2\\t1\\GUI1\\Dll\\TicTacToe_Gui2\\Debug\\TicTacToe_Gui2.dll";

        [DllImport(DllFilePath, CallingConvention = CallingConvention.Cdecl)]
        private static extern void getArray(out int length, out IntPtr array);*/


        public Form4()
        {
            InitializeComponent();
            textBox1.Enabled = false;
            textBox2.Enabled = false;
            textBox3.Enabled = false;
            textBox4.Enabled = false;
            textBox5.Enabled = false;
            textBox6.Enabled = false;
            textBox7.Enabled = false;
            textBox9.Enabled = false;
            textBox10.Enabled = false;
            textBox11.Enabled = false;

            if (GlobalClass.IN.Count >= 1)
            {
                textBox1.Text = GlobalClass.IN[0];
            }
            else
            {
                textBox1.Text = "No Player Yet";
            }

            if (GlobalClass.IN.Count >= 2)
            {
                textBox2.Text = GlobalClass.IN[1];
            }
            else
            {
                textBox2.Text = "No Player Yet";
            }

            if (GlobalClass.IN.Count >= 3)
            {
                textBox3.Text = GlobalClass.IN[2];
            }
            else
            {
                textBox3.Text = "No Player Yet";
            }

            if (GlobalClass.IN.Count >= 4)
            {
                textBox4.Text = GlobalClass.IN[3];
            }
            else
            {
                textBox4.Text = "No Player Yet";
            }

            if (GlobalClass.IN.Count >= 5)
            {
                textBox5.Text = GlobalClass.IN[4];
            }
            else
            {
                textBox5.Text = "No Player Yet";
            }

            if (GlobalClass.DV.Count >= 1)
            {
                textBox6.Text = Convert.ToString(GlobalClass.DV[0]);
            }
            else
            {
                textBox6.Text = "No Player Yet";
            }

            if (GlobalClass.DV.Count >= 2)
            {
                textBox7.Text = Convert.ToString(GlobalClass.DV[1]);
            }
            else
            {
                textBox7.Text = "No Player Yet";
            }

            if (GlobalClass.DV.Count >= 3)
            {
                textBox9.Text = Convert.ToString(GlobalClass.DV[2]);
            }
            else
            {
                textBox9.Text = "No Player Yet";
            }

            if (GlobalClass.DV.Count >= 4)
            {
                textBox10.Text = Convert.ToString(GlobalClass.DV[3]);
            }
            else
            {
                textBox10.Text = "No Player Yet";
            }

            if (GlobalClass.DV.Count >= 5)
            {
                textBox11.Text = Convert.ToString(GlobalClass.DV[4]);
            }
            else
            {
                textBox11.Text = "No Player Yet";
            }
            label1.Text = "Current Player : " + GlobalClass.pl_in; 
        }

      

       

        private void Form4_Load(object sender, EventArgs e)
        {
          
            //read_data(); 
            //string filename = "C:\\Users\\Sakshi\\Documents\\2018\\csce315\\GUI2\\GUI1\\Dll\\TicTacToe_Gui2\\TicTacToe_Gui2\\scores.txt";
            //Console.WriteLine(GlobalClass.IN[0] + "," + GlobalClass.IN[1] + "form4");
            //Console.WriteLine(GlobalClass.DV[0] + "," + GlobalClass.DV[1] + "form4");

        }

        private void Form4_FormClosed(object sender, FormClosedEventArgs e)
        {

            Application.Exit(); 
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form5 form5 = new Form5();
            this.Hide();
            form5.ShowDialog();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox5_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox6_TextChanged(object sender, EventArgs e)
        {
           
        }

        private void textBox7_TextChanged(object sender, EventArgs e)
        {
     
        }

        private void textBox9_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox10_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox11_TextChanged(object sender, EventArgs e)
        {
            
        }

        private void textBox3_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged_1(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }
    }
}
