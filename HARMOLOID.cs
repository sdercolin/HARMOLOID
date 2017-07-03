using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.IO;
using System.Collections;
using System.Windows.Forms;
using HARMOLOID_Csharp;

namespace HARMOLOID_Csharp
{
    public partial class HARMOLOID : Form
    {
        public HARMOLOID()
        {
            InitializeComponent();
        }
        public DATA data;

        private void c_Load(object sender, EventArgs e)
        {
            //throw new Exception();
        }

        private void 载入ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (data != null)
            {
                if (MessageBox.Show(ProgramTexts.GetProgramText("reload"), ProgramTexts.GetProgramText("load"), MessageBoxButtons.YesNo) == DialogResult.No)
                {
                    return;
                }
                else
                {
                    File.Delete(data.FilePath.Remove(data.FilePath.Length - 5, 5) + ".temp");
                }
            }
            OpenFileDialog Load_dialog = new OpenFileDialog();
            Load_dialog.Filter = "VOCALOID3/4 Project(.vsqx)|*.vsqx|UTAU Project(.ust)|*.ust|CeVIO Project(.ccs)|*.ccs";
            Load_dialog.ShowDialog();
            if (Load_dialog.FileName != "")
            {
                data = new DATA(Load_dialog.FileName, Load_dialog.SafeFileName);
                try
                {
                    data.DATALoad();
                }
                catch (MyException)
                {
                    data = null;
                }
                if (data != null)
                {
                    //更新文件信息
                    string FileInfoTmp = "";
                    FileInfoTmp += ProgramTexts.GetProgramText("format_text");
                    switch (data.FileFormat)
                    {
                        case 1:
                            FileInfoTmp += "VOCALOID3 Project(vsqx/vsq3)\r\n";
                            break;
                        case 2:
                            FileInfoTmp += "VOCALOID4 Project(vsqx/vsq4)\r\n";
                            break;
                        case 3:
                            FileInfoTmp += "UTAU Project(ust)\r\n";
                            break;
                        case 4:
                            FileInfoTmp += "CeVIO Project(ccs)\r\n";
                            break;
                    }
                    FileInfoTmp += ProgramTexts.GetProgramText("filepath_text") + data.FilePath.Remove(data.FilePath.Length - data.FileName.Length) + "\r\n";
                    FileInfoTmp += ProgramTexts.GetProgramText("filename_text") + data.FileName;
                    if (data.FileFormat == 3)
                    {
                        FileInfoTmp += "\r\n" + ProgramTexts.GetProgramText("projectname_text") + data.ProjectName;
                    }
                    textBox_FileInfo.Text = FileInfoTmp;
                    //更新音轨列表框
                    listBox_TrackList.SelectedIndex = -1;
                    listBox_TrackList_Renew(data);
                    //使能按钮
                    button_调性标记.Enabled = true;
                    button_和声生成.Enabled = true;
                    if (data.FileFormat != 3)
                    {
                        保存ToolStripMenuItem.Enabled = true;
                    }
                    else
                    {
                        保存ToolStripMenuItem.Enabled = false;
                    }
                    另存为ToolStripMenuItem.Enabled = true;
                    //作成临时拷贝
                    if (data.FileFormat != 3)
                    {
                        File.Copy(data.FilePath, data.FilePath.Remove(data.FilePath.Length - 5, 5) + ".temp", true);
                    }
                }
                MessageBox.Show(ProgramTexts.GetProgramText("loading_success"), ProgramTexts.GetProgramText("load"));
            }
        }

        //更新音轨列表框
        private void listBox_TrackList_Renew(DATA data)
        {
            listBox_TrackList.Items.Clear();
            for (int i = 0; i < data.TrackNumTotal; i++)
            {
                listBox_TrackList.Items.Add(i.ToString() + "." + data.TrackList[i].TrackName);
            }
        }

        //更新音轨信息
        private void listBox_TrackInfo_Renew()
        {
            int TrackNum = listBox_TrackList.SelectedIndex;
            if (TrackNum > -1)
            {
                string TrackInfoTmp = "";
                TrackInfoTmp += ProgramTexts.GetProgramText("trackno_text") + TrackNum + "\r\n";
                TrackInfoTmp += ProgramTexts.GetProgramText("trackname_text") + data.TrackList[TrackNum].TrackName + "\r\n";
                TrackInfoTmp += ProgramTexts.GetProgramText("tonalizationresult_text") + data.TrackList[TrackNum].GetTonalityAsString() + "\r\n";
                TrackInfoTmp += ProgramTexts.GetProgramText("existingchorus_text");
                bool harmonized = false;
                for (int i = 0; i < 7; i++)
                {
                    if (data.TrackList[TrackNum].ChildHarmoTrackNum[i] != -1)
                    {
                        harmonized = true;
                        TrackInfoTmp += Constants.Harmonic_Type_inWords(i) + "、";
                    }
                }
                if (harmonized)
                {
                    TrackInfoTmp = TrackInfoTmp.Remove(TrackInfoTmp.Length - 1);
                }
                else
                {
                    TrackInfoTmp += "-";
                }
                TrackInfoTmp += "\r\n";
                TrackInfoTmp += ProgramTexts.GetProgramText("notetotal_text") + data.TrackList[TrackNum].NoteNumTotal + "\r\n";
                TrackInfoTmp += ProgramTexts.GetProgramText("bartotal_text") + data.TrackList[TrackNum].BarNumTotal;
                textBox_TrackInfo.Text = TrackInfoTmp;
            }
            else
            {
                textBox_TrackInfo.Text = ProgramTexts.GetProgramText("choosetrack_text");
            }
        }

        private void listBox_TrackList_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (data != null)
            {
                listBox_TrackInfo_Renew();
            }
        }

        private void button_标记调性_Click(object sender, EventArgs e)
        {
            if (listBox_TrackList.SelectedIndex != -1)
            {
                int TrackNum = listBox_TrackList.SelectedIndex;
                if (data.TrackList[TrackNum].TrackEmptiness == true)
                {
                    MessageBox.Show(ProgramTexts.GetProgramText("emptytrack_text"), ProgramTexts.GetProgramText("tonalization"));
                    return;
                }
                if (data.TrackList[TrackNum].IsHarmonized())
                {
                    if (MessageBox.Show(ProgramTexts.GetProgramText("deletechorus-and-tonalize"), ProgramTexts.GetProgramText("tonalization"), MessageBoxButtons.YesNo) == DialogResult.Yes)
                    {
                        try
                        {
                            data.DATALoad();
                        }
                        catch (MyException)
                        {
                            data = null;
                        }
                        /*
                        for (int i = 0; i < 7; i++)
                        {
                            if (data.TrackList[TrackNum].ChildHarmoTrackNum[i] != -1)
                            {
                                data.DeleteHarmoTrack(data.TrackList[TrackNum].ChildHarmoTrackNum[i]);
                                data.TrackList[TrackNum].ChildHarmoTrackNum[i] = -1;
                            }
                        }*/
                    }
                    else
                    {
                        return;
                    }
                }
                Tonalization TonalizationDlg = new Tonalization(data, TrackNum);
                TonalizationDlg.Text = ProgramTexts.GetProgramText("tonalization")+"["+ ProgramTexts.GetProgramText("track") + TrackNum + "." + data.TrackList[TrackNum].TrackName + "]";
                TonalizationDlg.ShowDialog();
                listBox_TrackInfo_Renew();
            }
            else
            {
                MessageBox.Show(ProgramTexts.GetProgramText("choosetrack_text2"), ProgramTexts.GetProgramText("tonalization"));
            }
        }

        private void button_和声生成_Click(object sender, EventArgs e)
        {
            if (listBox_TrackList.SelectedIndex != -1)
            {
                int TrackNum = listBox_TrackList.SelectedIndex;
                if (data.TrackList[TrackNum].IsTonalized)
                {
                    Harmonization Harmonization = new Harmonization(data, TrackNum);
                    Harmonization.ShowDialog();
                    listBox_TrackInfo_Renew();
                }
                else
                {
                    MessageBox.Show(ProgramTexts.GetProgramText("do-tonalization-first"), ProgramTexts.GetProgramText("harmolization"));
                }
            }
            else
            {
                MessageBox.Show(ProgramTexts.GetProgramText("choosetrack_text2"), ProgramTexts.GetProgramText("harmolization"));
            }
        }
        
        private void 另存为ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (data != null)
            {
                int HarmoToSave = 0;
                if (data.FileFormat == 3)
                {
                    if (!data.TrackList[0].IsHarmonized())
                    {
                        MessageBox.Show(ProgramTexts.GetProgramText("cannot-save-ust1"), ProgramTexts.GetProgramText("saveas"));
                        return;
                    }
                    USTSaving USTSavingDlg = new USTSaving(data);
                    USTSavingDlg.ShowDialog();
                    HarmoToSave = USTSavingDlg.HarmoToSave;
                    USTSavingDlg.Close();
                    if (HarmoToSave == data.HarmoNumTotal)
                    {
                        return;
                    }
                }
                SaveFileDialog Save_dialog = new SaveFileDialog();
                switch (data.FileFormat)
                {
                    case 1:
                        Save_dialog.Filter = "VOCALOID3 Project(.vsqx)|*.vsqx";
                        break;
                    case 2:
                        Save_dialog.Filter = "VOCALOID4 Project(.vsqx)|*.vsqx";
                        break;
                    case 3:
                        Save_dialog.Filter = "UTAU Project|*.ust";
                        break;
                    case 4:
                        Save_dialog.Filter = "CeVIO Project|*.ccs";
                        break;
                }
                Save_dialog.FilterIndex = 2;
                Save_dialog.RestoreDirectory = true;
                Save_dialog.ShowDialog();
                if (Save_dialog.FileName != "")
                {
                    if (data.FileFormat != 3)
                    {
                        data.DATASave(Save_dialog.FileName);
                    }
                    else
                    {
                        data.DATASave(Save_dialog.FileName, HarmoToSave);
                        MessageBox.Show(ProgramTexts.GetProgramText("saving_success"), ProgramTexts.GetProgramText("saveas"));
                    }
                }
            }
        }

        private void 保存ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (data != null)
            {
                data.DATASave(data.FilePath);
            }
        }

        private void HARMOLOID_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (data != null)
            {
                File.Delete(data.FilePath.Remove(data.FilePath.Length - 5, 5) + ".temp");
            }
        }

        private void 关于HARMOLOIDToolStripMenuItem_Click(object sender, EventArgs e)
        {
            About about = new About();
            about.Show();
        }

        private void 获得更新ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://sdercolin.com/akatsuki/harmoloid/");
        }

        private void BUG提交ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://sdercolin.com/akatsuki/harmoloid_bug/");
        }

        private void 用户手册ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start(ProgramTexts.GetProgramText("userguide")+".html");
            }
            catch
            {
            }
        }
    }
}
