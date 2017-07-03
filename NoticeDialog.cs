using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace HARMOLOID_Csharp
{
    public partial class NoticeDialog : Form
    {
        string notice;
        public NoticeDialog(string title, string notice)
        {
            this.Text = title;
            this.notice = notice;
            InitializeComponent();
        }

        private void button_Confirm_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void NoticeDialog_Load(object sender, EventArgs e)
        {
            textBox_Notice.Text = notice;
        }
    }
}
