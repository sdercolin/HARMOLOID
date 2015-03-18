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
                if (MessageBox.Show("文件已经载入，是否载入新文件？", "载入", MessageBoxButtons.YesNo) == DialogResult.No)
                {
                    return;
                }
                else
                {
                    File.Delete(data.FilePath.Remove(data.FilePath.Length - 5, 5) + ".temp");
                }
            }
            OpenFileDialog Load_dialog = new OpenFileDialog();
            Load_dialog.Filter = "VOCALOID3/4工程文件(.vsqx)|*.vsqx|UTAU工程文件(.ust)|*.ust";
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
                    FileInfoTmp += "文件格式：";
                    switch (data.FileFormat)
                    {
                        case 1:
                            FileInfoTmp += "VOCALOID3工程文件(vsqx/vsq3)\r\n";
                            break;
                        case 2:
                            FileInfoTmp += "VOCALOID4工程文件(vsqx/vsq4)\r\n";
                            break;
                        case 3:
                            FileInfoTmp += "UTAU工程文件(ust)\r\n";
                            break;
                    }
                    FileInfoTmp += "文件路径：" + data.FilePath.Remove(data.FilePath.Length - data.FileName.Length) + "\r\n";
                    FileInfoTmp += "文件名：" + data.FileName;
                    if (data.FileFormat == 3)
                    {
                        FileInfoTmp += "\r\n" + "工程名：" + data.ProjectName;
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
                TrackInfoTmp += "音轨编号：" + TrackNum + "\r\n";
                TrackInfoTmp += "音轨名：" + data.TrackList[TrackNum].TrackName + "\r\n";
                TrackInfoTmp += "调性标记结果：" + data.TrackList[TrackNum].GetTonalityAsString() + "\r\n";
                TrackInfoTmp += "已生成的和声种类：";
                bool harmonized = false;
                for (int i = 0; i < 7; i++)
                {
                    if (data.TrackList[TrackNum].ChildHarmoTrackNum[i] != -1)
                    {
                        harmonized = true;
                        TrackInfoTmp += Constants.Harmonic_Type_inChinese[i] + "、";
                    }
                }
                if (harmonized)
                {
                    TrackInfoTmp = TrackInfoTmp.Remove(TrackInfoTmp.Length - 1);
                }
                else
                {
                    TrackInfoTmp += "无";
                }
                TrackInfoTmp += "\r\n";
                TrackInfoTmp += "音符总数：" + data.TrackList[TrackNum].NoteNumTotal + "\r\n";
                TrackInfoTmp += "小节总数：" + data.TrackList[TrackNum].BarNumTotal;
                textBox_TrackInfo.Text = TrackInfoTmp;
            }
            else
            {
                textBox_TrackInfo.Text = "请选择音轨。";
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
                    MessageBox.Show("该音轨为空，无法进行调性标记。", "调性标记");
                    return;
                }
                if (data.TrackList[TrackNum].IsHarmonized())
                {
                    if (MessageBox.Show("该音轨已含有生成的和声轨，是否清空所有和声轨并重新标记调性？", "调性标记", MessageBoxButtons.YesNo) == DialogResult.Yes)
                    {
                        for (int i = 0; i < 7; i++)
                        {
                            if (data.TrackList[TrackNum].ChildHarmoTrackNum[i] != -1)
                            {
                                data.DeleteHarmoTrack(data.TrackList[TrackNum].ChildHarmoTrackNum[i]);
                                data.TrackList[TrackNum].ChildHarmoTrackNum[i] = -1;
                            }
                        }
                    }
                    else
                    {
                        return;
                    }
                }
                Tonalization TonalizationDlg = new Tonalization(data, TrackNum);
                TonalizationDlg.Text = "调性标记[音轨" + TrackNum + "." + data.TrackList[TrackNum].TrackName + "]";
                TonalizationDlg.ShowDialog();
                listBox_TrackInfo_Renew();
            }
            else
            {
                MessageBox.Show("请在左侧的音轨列表中选择音轨。", "调性标记");
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
                    MessageBox.Show("该音轨尚未完成调性标记，无法生成和声。", "和声生成");
                }
            }
            else
            {
                MessageBox.Show("请在左侧的音轨列表中选择音轨。", "和声生成");
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
                        MessageBox.Show("尚未有和声轨生成，无法保存为UST。", "保存");
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
                        Save_dialog.Filter = "VOCALOID3工程文件(.vsqx)|*.vsqx";
                        break;
                    case 2:
                        Save_dialog.Filter = "VOCALOID4工程文件(.vsqx)|*.vsqx";
                        break;
                    case 3:
                        Save_dialog.Filter = "UTAU工程文件|*.ust";
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
                        MessageBox.Show("保存成功。", "保存");
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
                System.Diagnostics.Process.Start("用户手册.html");
            }
            catch
            {
                MessageBox.Show("找不到文件“用户手册.html”。", "帮助");
            }
        }
    }
}
