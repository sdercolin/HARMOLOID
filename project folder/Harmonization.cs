using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace HARMOLOID_Csharp
{
    public partial class Harmonization : Form
    {
        DATA data;
        int TrackNum;
        bool[] checkedHarmonies = new bool[7];
        public Harmonization(DATA data, int TrackNum)
        {
            this.data = data;
            this.TrackNum = TrackNum;
            InitializeComponent();
        }

        private void Harmonization_Load(object sender, EventArgs e)
        {
            label_HarmonizingTrack.Text = TrackNum.ToString() + "." + data.TrackList[TrackNum].TrackName;
            label_Tonality.Text = data.TrackList[TrackNum].GetTonalityAsString();
            for (int i = 0; i < 7; i++)
            {
                if (data.TrackList[TrackNum].ChildHarmoTrackNum[i] != -1)
                {
                    checkedListBox_HarmonyOptions.SetItemChecked(i, true);
                    checkedHarmonies[i] = true;
                }
                else
                {
                    checkedListBox_HarmonyOptions.SetItemChecked(i, false);
                    checkedHarmonies[i] = false;
                }
            }
        }

        private void button_SaveHarmony_Click(object sender, EventArgs e)
        {
            string NoticeContents = "";
            for (int i = 0; i < 7; i++)
            {
                if (checkedHarmonies[i] != checkedListBox_HarmonyOptions.GetItemChecked(i))
                {
                    //若原来未选中，此时已选中，则增加和声轨
                    if (!checkedHarmonies[i])
                    {
                        data.HarmoList[data.HarmoNumTotal] = new HARMOTRACK(data.HarmoNumTotal, data.TrackList[TrackNum], TrackNum, i);
                        data.TrackList[TrackNum].ChildHarmoTrackNum[i] = data.HarmoNumTotal;
                        data.HarmoNumTotal++;
                        NoticeContents += "音轨"+TrackNum+"的"+Constants.Harmonic_Type_inChinese[i]+"轨已生成。\r\n";
                    }
                    //若原来已选中，此时未选中，则删除和声轨
                    else
                    {
                        data.DeleteHarmoTrack(data.TrackList[TrackNum].ChildHarmoTrackNum[i]);
                        data.TrackList[TrackNum].ChildHarmoTrackNum[i] = -1;
                        NoticeContents += "音轨" + TrackNum + "的" + Constants.Harmonic_Type_inChinese[i] + "轨已删除。\r\n";
                    }
                }
            }
            if (NoticeContents != "")
            {
                MessageBox.Show(NoticeContents.Remove(NoticeContents.Length - 2), "和声生成结果");
            }
            this.Close();
        }
    }
}
