using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace TicTacToeGUI
{
    public partial class Form3 : Form
    {
        private string path;

        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_FormClosed(object sender, FormClosedEventArgs e)
        {
            Application.Exit();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if((textBox1.Text.Length > 0) && (textBox1.Text.Length < 4))
            {
                Form4 form4 = new Form4();
                this.Hide();
                form4.ShowDialog();
            }
            else
            {
                label1.Text = "Invalid Initials";
            }
        }

        public void readData()
        {
            string[] lines = System.IO.File.ReadAllLines(Directory.GetCurrentDirectory() + "\\scores.txt");

            List<string> temp_initials = new List<string>();
            List<double> temp_scores = new List<double>();

            foreach (string line in lines)
            {
                StringReader reader = new StringReader(line);
                string[] data = reader.ReadToEnd().Split(' ');
                Console.WriteLine(data[0] + "," + data[1]);

                temp_initials.Add(data[0]);
                temp_scores.Add(Convert.ToDouble(data[1]));

            }
            GlobalClass.IN = temp_initials;
            GlobalClass.DV = temp_scores;

        }

        public void sortData()
        {

            if (GlobalClass.IN.Count == 1 || GlobalClass.DV.Count == 0)
            {
                return;
            }

            //bubble sort
            for (int i = 0; i < GlobalClass.DV.Count - 1; i++)
            {
                for (int j = 0; j < GlobalClass.DV.Count - 1 - i; j++)
                {
                    if (GlobalClass.DV[j] < GlobalClass.DV[j + 1])
                    {
                        //swap
                        double tempScore = GlobalClass.DV[j + 1];
                        string tempInitials = GlobalClass.IN[j + 1];

                        GlobalClass.DV[j + 1] = GlobalClass.DV[j];
                        GlobalClass.IN[j + 1] = GlobalClass.IN[j];

                        GlobalClass.DV[j] = tempScore;
                        GlobalClass.IN[j] = tempInitials;
                    }
                }
            }
        }
        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            readData();
            GlobalClass.pl_in = textBox1.Text;

            //verify initials and add to global variables. 
            if (GlobalClass.pl_in.Length > 3) {
                GlobalClass.pl_in = GlobalClass.pl_in.Substring(0, 2);
               // Console.WriteLine(GlobalClass.pl_in);
            }
            else if(GlobalClass.pl_in.Length == 0)
            {
                GlobalClass.pl_in = "N/A"; 
            }
            //new player add to list
            if (!GlobalClass.IN.Contains(GlobalClass.pl_in))
            {
                GlobalClass.IN.Add(GlobalClass.pl_in);
                GlobalClass.DV.Add(0);
                //Console.WriteLine(GlobalClass.IN.Count);
            }
            sortData();
        }

        
    }
}