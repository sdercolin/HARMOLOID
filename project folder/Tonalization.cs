using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace HARMOLOID_Csharp
{
    public partial class Tonalization : Form
    {
        DATA data;
        int TrackNum;
        TRACK TrackTmp;
        bool TonalizationFinished;
        public Tonalization(DATA data, int TrackNum)
        {
            this.data = data;
            this.TrackNum = TrackNum;
            TrackTmp = new TRACK(data.TrackList[TrackNum]);
            InitializeComponent();
        }

        private void Tonalization_Load(object sender, EventArgs e)
        {
            label_TonalizingTrack.Text = TrackNum.ToString() + "." + data.TrackList[TrackNum].TrackName;
            if (data.TrackList[TrackNum].IsTonalized)
            {
                label_IsTonalized.Text = "完成";
                TonalizationFinished = true;
            }
            else
            {
                label_IsTonalized.Text = "未完成";
                TonalizationFinished = false;
            }
            //读取乐段列表
            PassageListRenew();
            //读取小节列表
            for (int BarNum = 0; BarNum < data.TrackList[TrackNum].BarNumTotal; BarNum++)
            {
                string[] tmp = new string[] { BarNum.ToString(), data.TrackList[TrackNum].BarList[BarNum].GetContentAsString(data.TrackList[TrackNum]) };
                ListViewItem tmpItem = new ListViewItem(tmp);
                listView_BarList.Items.Add(tmpItem);
            }
        }

        private void PassageListRenew()
        {
            comboBox_PassageNum.Items.Clear();
            ListViewItem[] PassageViewItems = new ListViewItem[data.TrackList[TrackNum].PassageNumTotal];
            for (int i = 0; i < data.TrackList[TrackNum].PassageNumTotal; i++)
            {
                string[] PassageTmp = new string[] { i.ToString(), data.TrackList[TrackNum].PassageList[i].FirstBarNum.ToString(), data.TrackList[TrackNum].PassageList[i].LastBarNum.ToString(), Constants.Tonality_Type[data.TrackList[TrackNum].PassageList[i].Tonality] };
                if (PassageTmp[2] == (data.TrackList[TrackNum].BarNumTotal - 1).ToString())
                {
                    PassageTmp[2] = "-";
                }
                PassageViewItems[i] = new ListViewItem(PassageTmp);
                comboBox_PassageNum.Items.Add(i.ToString());
            }
            listView_PassageList.Items.Clear();
            listView_PassageList.Items.AddRange(PassageViewItems);
            comboBox_PassageNum.SelectedIndex = 0;
        }

        private void PassageListRenew(TRACK TrackTmp)
        {
            comboBox_PassageNum.Items.Clear();
            ListViewItem[] PassageViewItems = new ListViewItem[TrackTmp.PassageNumTotal];
            for (int i = 0; i < TrackTmp.PassageNumTotal; i++)
            {
                string[] PassageTmp = new string[] { i.ToString(), TrackTmp.PassageList[i].FirstBarNum.ToString(), TrackTmp.PassageList[i].LastBarNum.ToString(), Constants.Tonality_Type[TrackTmp.PassageList[i].Tonality] };
                if (PassageTmp[2] == (TrackTmp.BarNumTotal - 1).ToString())
                {
                    PassageTmp[2] = "-";
                }
                PassageViewItems[i] = new ListViewItem(PassageTmp);
                comboBox_PassageNum.Items.Add(i.ToString());
            }
            listView_PassageList.Items.Clear();
            listView_PassageList.Items.AddRange(PassageViewItems);
            comboBox_PassageNum.SelectedIndex = 0;
        }

        private void comboBox_PassageNum_SelectedIndexChanged(object sender, EventArgs e)
        {
            ListViewItem[] PassageViewItems = new ListViewItem[comboBox_PassageNum.Items.Count];
            listView_PassageList.Items.CopyTo(PassageViewItems, 0);
            textBox_StartBarNum.Text = PassageViewItems[comboBox_PassageNum.SelectedIndex].SubItems[1].Text;
            textBox_EndBarNum.Text = PassageViewItems[comboBox_PassageNum.SelectedIndex].SubItems[2].Text;
            comboBox_TonalityInput.SelectedIndex = comboBox_TonalityInput.FindStringExact(PassageViewItems[comboBox_PassageNum.SelectedIndex].SubItems[3].Text);
        }

        private void button_PassageEditConfirm_Click(object sender, EventArgs e)
        {
            //检验错误输入
            if (textBox_EndBarNum.Text != "-")
            {
                try
                {
                    if (Convert.ToInt32(textBox_EndBarNum.Text) < 0)
                    {
                        MessageBox.Show("输入错误。请输入正整数的小节号或“-”以表示“至音轨末尾”。", this.Text);
                        return;
                    }
                }
                catch
                {
                    MessageBox.Show("输入错误。请输入正整数的小节号或“-”以表示“至音轨末尾”。", this.Text);
                    return;
                }
            }
            ListViewItem[] PassageViewItems = new ListViewItem[comboBox_PassageNum.Items.Count];
            listView_PassageList.Items.CopyTo(PassageViewItems, 0);
            bool ResetNeeded = false;
            int PassageNum = comboBox_PassageNum.SelectedIndex;
            if (PassageViewItems.Length <= PassageNum)
            {
                MessageBox.Show("乐段编号输入错误。", this.Text);
                return;
            }
                if (PassageViewItems[PassageNum].SubItems[2].Text != textBox_EndBarNum.Text)
            {
                ResetNeeded = true;
                PassageViewItems[PassageNum].SubItems[2].Text = textBox_EndBarNum.Text;
            }
            PassageViewItems[PassageNum].SubItems[3].Text = comboBox_TonalityInput.Text;
            if (PassageNum == comboBox_PassageNum.Items.Count - 1)
            {
                if (PassageViewItems[PassageNum].SubItems[2].Text != "-")
                {
                    if (Convert.ToInt32(PassageViewItems[PassageNum].SubItems[2].Text) < data.TrackList[TrackNum].BarNumTotal - 1)
                    {
                        ListViewItem[] newPassageViewItems = new ListViewItem[comboBox_PassageNum.Items.Count + 1];
                        for (int i = 0; i < comboBox_PassageNum.Items.Count; i++)
                        {
                            newPassageViewItems[i] = PassageViewItems[i];
                        }
                        string[] PassageTmp = new string[] { (PassageNum + 1).ToString(), (Convert.ToInt32(newPassageViewItems[PassageNum].SubItems[2].Text) + 1).ToString(), "-", "待分析" };
                        newPassageViewItems[PassageNum + 1] = new ListViewItem(PassageTmp);
                        listView_PassageList.Items.Clear();
                        listView_PassageList.Items.AddRange(newPassageViewItems);
                        comboBox_PassageNum.Items.Add((PassageNum + 1).ToString());
                        comboBox_PassageNum.SelectedIndex++;
                    }
                    else
                    {
                        PassageViewItems[PassageNum].SubItems[2].Text = "-";
                        listView_PassageList.Items.Clear();
                        listView_PassageList.Items.AddRange(PassageViewItems);
                    }
                }
                else
                {
                    listView_PassageList.Items.Clear();
                    listView_PassageList.Items.AddRange(PassageViewItems);
                }
            }
            else if (ResetNeeded)
            {
                if (PassageViewItems[PassageNum].SubItems[2].Text != "-")
                {
                    if (Convert.ToInt32(PassageViewItems[PassageNum].SubItems[2].Text) < data.TrackList[TrackNum].BarNumTotal - 1)
                    {
                        PassageViewItems[PassageNum + 1].SubItems[1].Text = (Convert.ToInt32(PassageViewItems[PassageNum].SubItems[2].Text) + 1).ToString();
                        PassageViewItems[PassageNum + 1].SubItems[2].Text = "-";
                        PassageViewItems[PassageNum + 1].SubItems[3].Text = "待分析";
                        listView_PassageList.Items.Clear();
                        listView_PassageList.Items.AddRange(PassageViewItems);
                        for (int i = PassageNum + 2; i < listView_PassageList.Items.Count; i++)
                        {
                            listView_PassageList.Items.RemoveAt(i);
                            comboBox_PassageNum.Items.RemoveAt(i);
                        }
                        comboBox_PassageNum.SelectedIndex++;
                    }
                    else
                    {
                        PassageViewItems[PassageNum].SubItems[2].Text = "-";
                        listView_PassageList.Items.Clear();
                        listView_PassageList.Items.AddRange(PassageViewItems);
                        for (int i = PassageNum + 1; i < listView_PassageList.Items.Count; i++)
                        {
                            listView_PassageList.Items.RemoveAt(i);
                            comboBox_PassageNum.Items.RemoveAt(i);
                        }
                    }
                }
                else
                {
                    listView_PassageList.Items.Clear();
                    listView_PassageList.Items.AddRange(PassageViewItems);
                    for (int i = PassageNum + 1; i < listView_PassageList.Items.Count; i++)
                    {
                        listView_PassageList.Items.RemoveAt(i);
                        comboBox_PassageNum.Items.RemoveAt(i);
                    }
                }
            }
            else
            {
                listView_PassageList.Items.Clear();
                listView_PassageList.Items.AddRange(PassageViewItems);
            }
            label_IsTonalized_Renew();
        }

        private void label_IsTonalized_Renew()
        {
            TonalizationFinished = true;
            label_IsTonalized.Text = "完成";
            for (int i = 0; i < listView_PassageList.Items.Count; i++)
            {
                if (listView_PassageList.Items[i].SubItems[3].Text == "待分析")
                {
                    TonalizationFinished = false;
                    label_IsTonalized.Text = "未完成";
                }
            }
        }

        private void button_SaveTonality_Click(object sender, EventArgs e)
        {
            if (TonalizationFinished)
            {
                ListViewItem[] PassageViewItems = new ListViewItem[listView_PassageList.Items.Count];
                listView_PassageList.Items.CopyTo(PassageViewItems, 0);
                data.TrackList[TrackNum].PassageList = new PASSAGE[listView_PassageList.Items.Count];
                for (int i = 0; i < listView_PassageList.Items.Count; i++)
                {
                    data.TrackList[TrackNum].PassageList[i] = new PASSAGE();
                    data.TrackList[TrackNum].PassageList[i].PassageNum = i;
                    data.TrackList[TrackNum].PassageList[i].ParentTrackNum = TrackNum;
                    data.TrackList[TrackNum].PassageList[i].FirstBarNum = Convert.ToInt32(listView_PassageList.Items[i].SubItems[1].Text);
                    if (listView_PassageList.Items[i].SubItems[2].Text == "-")
                    {
                        data.TrackList[TrackNum].PassageList[i].LastBarNum = data.TrackList[TrackNum].BarNumTotal - 1;
                    }
                    else
                    {
                        data.TrackList[TrackNum].PassageList[i].LastBarNum = Convert.ToInt32(listView_PassageList.Items[i].SubItems[2].Text);
                    }
                    data.TrackList[TrackNum].PassageList[i].Tonality = Constants.ConvertTonalityType(listView_PassageList.Items[i].SubItems[3].Text);
                }
                data.TrackList[TrackNum].PassageNumTotal = listView_PassageList.Items.Count;
                data.TrackList[TrackNum].IsTonalized = true;
                this.Close();
            }
            else
            {
                //提示未完成
                MessageBox.Show("有至少一个乐段未被标记调性，当前信息将不会被保存。", this.Text);
                this.Close();
            }
            
        }

        private void button_ResetTonality_Click(object sender, EventArgs e)
        {
            PassageListRenew();
            label_IsTonalized_Renew();
        }

        private void button_AutoTonalize1_Click(object sender, EventArgs e)
        {
            ListViewItem[] PassageViewItems = new ListViewItem[listView_PassageList.Items.Count];
            listView_PassageList.Items.CopyTo(PassageViewItems, 0);
            TrackTmp.PassageList = new PASSAGE[listView_PassageList.Items.Count];
            for (int i = 0; i < listView_PassageList.Items.Count; i++)
            {
                TrackTmp.PassageList[i] = new PASSAGE();
                TrackTmp.PassageList[i].PassageNum = i;
                TrackTmp.PassageList[i].ParentTrackNum = TrackNum;
                TrackTmp.PassageList[i].FirstBarNum = Convert.ToInt32(listView_PassageList.Items[i].SubItems[1].Text);
                if (listView_PassageList.Items[i].SubItems[2].Text == "-")
                {
                    TrackTmp.PassageList[i].LastBarNum = TrackTmp.BarNumTotal - 1;
                }
                else
                {
                    TrackTmp.PassageList[i].LastBarNum = Convert.ToInt32(listView_PassageList.Items[i].SubItems[2].Text);
                }
            }
            TrackTmp.PassageNumTotal = listView_PassageList.Items.Count;
            TrackTmp.AutoTonalize1();
            PassageListRenew(TrackTmp);
            label_IsTonalized_Renew();
        }

        private void button_AutoTonalize2_Click(object sender, EventArgs e)
        {
            TrackTmp.AutoTonalize2();
            PassageListRenew(TrackTmp);
            label_IsTonalized_Renew();
        }

        private void button_TonalizaionHelp_Click(object sender, EventArgs e)
        {
            MessageBox.Show(　　"关于“乐段”：由于制作和声的需要，HARMOLOID将会把音轨划分成一个或多个“乐段”，每个乐段内部的乐句需要满足单一调性，即不出现转调。\r\n\r\n　·　若您能够自己确定转调的位置和各部分的调性，请手动设置乐段，这样可以最大程度上地避免误差。\r\n　·　若您能够确定转调的位置，而不能确定各部分的调性，则请手动设置乐段的划分，并将调性选项置于“待分析”，然后按下“自动计算调性（按照乐段划分）”按钮。\r\n　·　若您对乐理完全不了解，且无法确定是否存在转调，请直接按下“自动计算调性（全自动/慎用）”按钮，但是这个功能将可能带来较大的误差，请在后续制作中进行较仔细的调整。\r\n\r\n　　由于不同编辑器的小节显示和音高标识的差异，请以本界面右边的小节列表中的内容为准。", "关于调性分析"); 
        }
    }
}
