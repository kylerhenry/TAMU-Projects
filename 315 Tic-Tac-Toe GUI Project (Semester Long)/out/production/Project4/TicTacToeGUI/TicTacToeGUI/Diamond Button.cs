using System;
using System.Collections.Generic;
using System.Drawing.Drawing2D;
using System.Windows.Forms;
using System.Linq;
using System.Text;


namespace TicTacToeGUI
{
    class Diamond_Button : Button
    {
        protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
        {
            GraphicsPath path = new GraphicsPath();
            path.AddLine(45, 25, 97, 55);
            path.AddLine(97, 55, 53, 80);
            path.AddLine(53, 80, 0, 50);
            path.AddLine(0, 50, 45, 25);
            this.Region = new System.Drawing.Region(path);
            base.OnPaint(e);
        }
    }
}
