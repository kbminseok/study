﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace pasteurizer
{
    public partial class Insert : Form
    {
        public Insert()
        {
            InitializeComponent();
        }

        private void modinsert_Click(object sender, EventArgs e)
        {
            DBHelper.InsertPasteurizerData(textBox1.Text, textBox2.Text, textBox3.Text, textBox4.Text, textBox5.Text, comboBox1.Text);
            Close();
        }
    }
}
