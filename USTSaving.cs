using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace HARMOLOID_Csharp
{
    public partial class USTSaving : Form
    {
        DATA data;
        public int HarmoToSave;
        public USTSaving(DATA data)
        {
            this.data = data;
            InitializeComponent();
        }

        private void USTSaving_Load(object sender, EventArgs e)
        {
            for (int i = 0; i < data.HarmoNumTotal; i++)
            {
                comboBox_HarmoToSave.Items.Add(Constants.Harmonic_Type_inWords(data.HarmoList[i].HarmonicType));
            }
            comboBox_HarmoToSave.Items.Add(ProgramTexts.GetProgramText("saveallust"));
            comboBox_HarmoToSave.SelectedIndex=comboBox_HarmoToSave.Items.Count-1;
        }

        private void Cancel_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void Confirm_Click(object sender, EventArgs e)
        {
            HarmoToSave = comboBox_HarmoToSave.SelectedIndex;
            if (comboBox_HarmoToSave.SelectedIndex != comboBox_HarmoToSave.Items.Count - 1)
            {
                this.Hide();
            }
            else
            {
                for (int i = 0; i < data.HarmoNumTotal; i++)
                {
                    data.DATASave(data.FilePath.Remove(data.FilePath.Length - data.FileName.Length) + data.HarmoList[i].TrackName + ".ust", i);
                }
                MessageBox.Show(ProgramTexts.GetProgramText("saving_success"), this.Text);
                this.Hide();
            }
        }
    }
}
