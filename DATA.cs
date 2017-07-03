using System;
using System.Collections.Generic;
using System.Text;
using System.Xml;
using System.IO;
using System.Windows.Forms;

namespace HARMOLOID_Csharp
{
    public class DATA
    {
        public DATA(string _FilePath, string _FileName)
        {
            FilePath = _FilePath;
            FileName = _FileName;
        }
        public string ProjectName;
        public string FileName; //文件名
        public string FilePath; //绝对路径
        public int FileFormat = 0; //1 for vsqx3, 2 for vsqx4, 3 for ust, 4 for ccs
        public int TrackNumTotal = 0;
        public int HarmoNumTotal = 0;
        public TRACK[] TrackList;
        public HARMOTRACK[] HarmoList;
        public void DATALoad()
        {
            //分析文件格式
            if (FileName.Remove(0, FileName.Length - 5) == ".vsqx")
            {
                string readbuf = File.ReadAllText(FilePath);
                if (readbuf.Contains("vsq3 xmlns=\"http://www.yamaha.co.jp/vocaloid/schema/vsq3/\""))
                {
                    FileFormat = 1;
                }
                else if (readbuf.Contains("vsq4 xmlns=\"http://www.yamaha.co.jp/vocaloid/schema/vsq4/\""))
                {
                    FileFormat = 2;
                }
            }
            else if (FileName.Remove(0, FileName.Length - 4) == ".ust")
            {
                FileFormat = 3;
            }
            else if (FileName.Remove(0, FileName.Length - 4) == ".ccs")
            {
                FileFormat = 4;
            }
            //按照格式对应载入
            switch (FileFormat)
            {
                case 1: // load vsqx for VOCALOID3
                    {
                        int TrackNum = 0;
                        XmlDocument vsq3 = new XmlDocument();
                        vsq3.Load(FilePath);
                        //建立音轨列表
                        XmlNode root = vsq3.FirstChild.NextSibling;
                        XmlNode MasterTrack = null;
                        if (root.HasChildNodes)
                        {
                            int count = 0;
                            for (int i = 0; i < root.ChildNodes.Count; i++)
                            {
                                if (root.ChildNodes[i].Name == "vsTrack")
                                {
                                    count++;
                                }
                            }
                            TrackList = new TRACK[count];
                            HarmoList = new HARMOTRACK[count * 7];
                        }
                        for (int i = 0; i < root.ChildNodes.Count; i++)
                        {
                            if (root.ChildNodes[i].Name == "masterTrack")
                            {
                                MasterTrack = root.ChildNodes[i];
                                break;
                            }
                        }
                        if (root.HasChildNodes)
                        {
                            for (int i = 0; i < root.ChildNodes.Count; i++)
                            {
                                if (root.ChildNodes[i].Name == "vsTrack")
                                {
                                    int NoteNum = 0;
                                    XmlNode thisTrack = root.ChildNodes[i];
                                    TrackList[TrackNum] = new TRACK();
                                    TrackList[TrackNum].TrackNum = TrackNum;
                                    for (int k = 0; k < 7; k++)
                                    {
                                        TrackList[TrackNum].ChildHarmoTrackNum[k] = -1;
                                    }
                                    TrackList[TrackNum].IsTonalized = false;
                                    //建立每个音轨的音符列表，读取音符信息
                                    int NoteCount = 0;
                                    for (int j = 0; j < thisTrack.ChildNodes.Count; j++)
                                    {
                                        if (thisTrack.ChildNodes[j].Name == "musicalPart")
                                        {
                                            XmlNode thisPart = thisTrack.ChildNodes[j];
                                            for (int k = 0; k < thisPart.ChildNodes.Count; k++)
                                            {
                                                if (thisPart.ChildNodes[k].Name == "note")
                                                {
                                                    NoteCount++;
                                                }
                                            }
                                        }
                                    }
                                    TrackList[TrackNum].NoteList = new NOTE[NoteCount];
                                    for (int j = 0; j < thisTrack.ChildNodes.Count; j++)
                                    {
                                        if (thisTrack.ChildNodes[j].Name == "trackName")
                                        {
                                            TrackList[TrackNum].TrackName = thisTrack.ChildNodes[j].FirstChild.Value;
                                        }
                                        if (thisTrack.ChildNodes[j].Name == "musicalPart")
                                        {
                                            XmlNode thisPart = thisTrack.ChildNodes[j];
                                            int PartStartTime = Convert.ToInt32(thisPart.FirstChild.FirstChild.Value);
                                            for (int k = 0; k < thisPart.ChildNodes.Count; k++)
                                            {
                                                if (thisPart.ChildNodes[k].Name == "note")
                                                {
                                                    TrackList[TrackNum].NoteList[NoteNum] = new NOTE();
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteNum = NoteNum;
                                                    XmlNode thisNote = thisPart.ChildNodes[k];
                                                    XmlNode inThisNote = thisNote.FirstChild;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn = Convert.ToInt32(inThisNote.FirstChild.Value) + PartStartTime;
                                                    inThisNote = inThisNote.NextSibling;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteTimeOff = TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn + Convert.ToInt32(inThisNote.FirstChild.Value);
                                                    inThisNote = inThisNote.NextSibling;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteKey = Convert.ToInt32(inThisNote.FirstChild.Value) - 12;
                                                    NoteNum++;
                                                }
                                            }
                                        }
                                    }
                                    TrackList[TrackNum].NoteNumTotal = NoteNum;
                                    //建立小节列表，读取小节信息
                                    TrackList[TrackNum].BarList = new BAR[1000];
                                    if (NoteNum == 0)
                                    {
                                        TrackList[TrackNum].TrackEmptiness = true;
                                    }
                                    else
                                    {
                                        TrackList[TrackNum].TrackEmptiness = false;
                                        int resolution = 0;
                                        int preMeasure = 0;
                                        XmlNode timeSig = null;
                                        int pos_timgSig = 0;
                                        int nume = 4;
                                        int denomi = 4;
                                        int BarTime = 0;
                                        for (int j = 0; j < MasterTrack.ChildNodes.Count; j++)
                                        {
                                            if (MasterTrack.ChildNodes[j].Name == "resolution")
                                            {
                                                resolution = Convert.ToInt32(MasterTrack.ChildNodes[j].FirstChild.Value);
                                            }
                                            if (MasterTrack.ChildNodes[j].Name == "preMeasure")
                                            {
                                                preMeasure = Convert.ToInt32(MasterTrack.ChildNodes[j].FirstChild.Value);
                                            }
                                            if (MasterTrack.ChildNodes[j].Name == "timeSig")
                                            {
                                                timeSig = MasterTrack.ChildNodes[j];
                                            }
                                        }
                                        XmlNode InTimeSig;
                                        for (int BarNum = 0, j = 0; j < TrackList[TrackNum].NoteNumTotal; BarNum++)
                                        {
                                            TrackList[TrackNum].BarList[BarNum] = new BAR();
                                            TrackList[TrackNum].BarList[BarNum].BarNum = BarNum;
                                            InTimeSig = timeSig.FirstChild;
                                            pos_timgSig = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            InTimeSig = InTimeSig.NextSibling;
                                            nume = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            InTimeSig = InTimeSig.NextSibling;
                                            denomi = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            if (pos_timgSig == BarNum)
                                            {
                                                BarTime = nume * 4 * resolution / denomi;
                                                XmlNode ntimeSig = timeSig.NextSibling;
                                                while (ntimeSig != null && ntimeSig.Name != "timeSig")
                                                {
                                                    ntimeSig = ntimeSig.NextSibling;
                                                }
                                                if (ntimeSig != null)
                                                {
                                                    timeSig = ntimeSig;
                                                }
                                            }
                                            if (BarNum == 0)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarTimeOn = 0;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarTimeOn = TrackList[TrackNum].BarList[BarNum - 1].BarTimeOff;
                                            }
                                            TrackList[TrackNum].BarList[BarNum].BarTimeOff = TrackList[TrackNum].BarList[BarNum].BarTimeOn + BarTime;
                                            TrackList[TrackNum].BarList[BarNum].ParentTrackNum = TrackNum;
                                            if (TrackList[TrackNum].NoteList[j].NoteTimeOn >= TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarEmptiness = true;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarEmptiness = false;
                                                TrackList[TrackNum].BarList[BarNum].FirstNoteNum = j;
                                                j++;
                                            }
                                            while (j <= TrackList[TrackNum].NoteNumTotal - 1 && TrackList[TrackNum].NoteList[j].NoteTimeOn < TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                            {
                                                j++;
                                            }
                                            if (!TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].LastNoteNum = j - 1;
                                            }
                                            if (TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                            }
                                            else if (Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetValidLength(TrackList[TrackNum])) / Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetBarLength()) < Constants.VALID_LENGTH_PERCENT_THRESHOLD)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = true;
                                            }
                                            TrackList[TrackNum].BarNumTotal++;
                                        }
                                        TrackList[TrackNum].PassageList = new PASSAGE[1];
                                        TrackList[TrackNum].PassageList[0] = new PASSAGE();
                                        TrackList[TrackNum].PassageList[0].PassageNum = 0;
                                        TrackList[TrackNum].PassageList[0].ParentTrackNum = TrackNum;
                                        TrackList[TrackNum].PassageList[0].FirstBarNum = 0;
                                        TrackList[TrackNum].PassageList[0].LastBarNum = TrackList[TrackNum].BarNumTotal - 1;
                                        TrackList[TrackNum].PassageList[0].Tonality = 13;
                                        TrackList[TrackNum].PassageNumTotal = 1;
                                    }
                                    TrackNum++;
                                    TrackNumTotal = TrackNum;
                                }
                            }
                        }
                        break;
                    }
                case 2: // load vsqx for VOCALOID4
                    {
                        int TrackNum = 0;
                        XmlDocument vsq4 = new XmlDocument();
                        vsq4.Load(FilePath);
                        //建立音轨列表
                        XmlNode root = vsq4.FirstChild.NextSibling;
                        XmlNode MasterTrack = null;
                        if (root.HasChildNodes)
                        {
                            int count = 0;
                            for (int i = 0; i < root.ChildNodes.Count; i++)
                            {
                                if (root.ChildNodes[i].Name == "vsTrack")
                                {
                                    count++;
                                }
                            }
                            TrackList = new TRACK[count];
                            HarmoList = new HARMOTRACK[count * 7];
                        }
                        for (int i = 0; i < root.ChildNodes.Count; i++)
                        {
                            if (root.ChildNodes[i].Name == "masterTrack")
                            {
                                MasterTrack = root.ChildNodes[i];
                                break;
                            }
                        }
                        if (root.HasChildNodes)
                        {
                            for (int i = 0; i < root.ChildNodes.Count; i++)
                            {
                                if (root.ChildNodes[i].Name == "vsTrack")
                                {
                                    int NoteNum = 0;
                                    XmlNode thisTrack = root.ChildNodes[i];
                                    TrackList[TrackNum] = new TRACK();
                                    TrackList[TrackNum].TrackNum = TrackNum;
                                    for (int k = 0; k < 7; k++)
                                    {
                                        TrackList[TrackNum].ChildHarmoTrackNum[k] = -1;
                                    }
                                    TrackList[TrackNum].IsTonalized = false;
                                    //建立每个音轨的音符列表，读取音符信息
                                    int NoteCount = 0;
                                    for (int j = 0; j < thisTrack.ChildNodes.Count; j++)
                                    {
                                        if (thisTrack.ChildNodes[j].Name == "vsPart")
                                        {
                                            XmlNode thisPart = thisTrack.ChildNodes[j];
                                            for (int k = 0; k < thisPart.ChildNodes.Count; k++)
                                            {
                                                if (thisPart.ChildNodes[k].Name == "note")
                                                {
                                                    NoteCount++;
                                                }
                                            }
                                        }
                                    }
                                    TrackList[TrackNum].NoteList = new NOTE[NoteCount];
                                    for (int j = 0; j < thisTrack.ChildNodes.Count; j++)
                                    {
                                        if (thisTrack.ChildNodes[j].Name == "name")
                                        {
                                            TrackList[TrackNum].TrackName = thisTrack.ChildNodes[j].FirstChild.Value;
                                        }
                                        if (thisTrack.ChildNodes[j].Name == "vsPart")
                                        {
                                            XmlNode thisPart = thisTrack.ChildNodes[j];
                                            int PartStartTime = Convert.ToInt32(thisPart.FirstChild.FirstChild.Value);
                                            for (int k = 0; k < thisPart.ChildNodes.Count; k++)
                                            {
                                                if (thisPart.ChildNodes[k].Name == "note")
                                                {
                                                    TrackList[TrackNum].NoteList[NoteNum] = new NOTE();
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteNum = NoteNum;
                                                    XmlNode thisNote = thisPart.ChildNodes[k];
                                                    XmlNode inThisNote = thisNote.FirstChild;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn = Convert.ToInt32(inThisNote.FirstChild.Value) + PartStartTime;
                                                    inThisNote = inThisNote.NextSibling;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteTimeOff = TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn + Convert.ToInt32(inThisNote.FirstChild.Value);
                                                    inThisNote = inThisNote.NextSibling;
                                                    TrackList[TrackNum].NoteList[NoteNum].NoteKey = Convert.ToInt32(inThisNote.FirstChild.Value) - 12;
                                                    NoteNum++;
                                                }
                                            }
                                        }
                                    }
                                    TrackList[TrackNum].NoteNumTotal = NoteNum;
                                    //建立小节列表，读取小节信息
                                    TrackList[TrackNum].BarList = new BAR[1000];
                                    if (NoteNum == 0)
                                    {
                                        TrackList[TrackNum].TrackEmptiness = true;
                                    }
                                    else
                                    {
                                        TrackList[TrackNum].TrackEmptiness = false;
                                        int resolution = 0;
                                        int preMeasure = 0;
                                        XmlNode timeSig = null;
                                        int pos_timgSig = 0;
                                        int nume = 4;
                                        int denomi = 4;
                                        int BarTime = 0;
                                        for (int j = 0; j < MasterTrack.ChildNodes.Count; j++)
                                        {
                                            if (MasterTrack.ChildNodes[j].Name == "resolution")
                                            {
                                                resolution = Convert.ToInt32(MasterTrack.ChildNodes[j].FirstChild.Value);
                                            }
                                            if (MasterTrack.ChildNodes[j].Name == "preMeasure")
                                            {
                                                preMeasure = Convert.ToInt32(MasterTrack.ChildNodes[j].FirstChild.Value);
                                            }
                                            if (MasterTrack.ChildNodes[j].Name == "timeSig")
                                            {
                                                timeSig = MasterTrack.ChildNodes[j];
                                            }
                                        }
                                        XmlNode InTimeSig;
                                        for (int BarNum = 0, j = 0; j < TrackList[TrackNum].NoteNumTotal; BarNum++)
                                        {
                                            TrackList[TrackNum].BarList[BarNum] = new BAR();
                                            TrackList[TrackNum].BarList[BarNum].BarNum = BarNum;
                                            InTimeSig = timeSig.FirstChild;
                                            pos_timgSig = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            InTimeSig = InTimeSig.NextSibling;
                                            nume = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            InTimeSig = InTimeSig.NextSibling;
                                            denomi = Convert.ToInt32(InTimeSig.FirstChild.Value);
                                            if (pos_timgSig == BarNum)
                                            {
                                                BarTime = nume * 4 * resolution / denomi;
                                                XmlNode ntimeSig = timeSig.NextSibling;
                                                while (ntimeSig != null && ntimeSig.Name != "timeSig")
                                                {
                                                    ntimeSig = ntimeSig.NextSibling;
                                                }
                                                if (ntimeSig != null)
                                                {
                                                    timeSig = ntimeSig;
                                                }
                                            }
                                            if (BarNum == 0)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarTimeOn = 0;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarTimeOn = TrackList[TrackNum].BarList[BarNum - 1].BarTimeOff;
                                            }
                                            TrackList[TrackNum].BarList[BarNum].BarTimeOff = TrackList[TrackNum].BarList[BarNum].BarTimeOn + BarTime;
                                            TrackList[TrackNum].BarList[BarNum].ParentTrackNum = TrackNum;
                                            if (TrackList[TrackNum].NoteList[j].NoteTimeOn >= TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarEmptiness = true;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarEmptiness = false;
                                                TrackList[TrackNum].BarList[BarNum].FirstNoteNum = j;
                                                j++;
                                            }
                                            while (j <= TrackList[TrackNum].NoteNumTotal - 1 && TrackList[TrackNum].NoteList[j].NoteTimeOn < TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                            {
                                                j++;
                                            }
                                            if (!TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].LastNoteNum = j - 1;
                                            }
                                            if (TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                            }
                                            else if (Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetValidLength(TrackList[TrackNum])) / Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetBarLength()) < Constants.VALID_LENGTH_PERCENT_THRESHOLD)
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                            }
                                            else
                                            {
                                                TrackList[TrackNum].BarList[BarNum].BarValidity = true;
                                            }
                                            TrackList[TrackNum].BarNumTotal++;
                                        }
                                        TrackList[TrackNum].PassageList = new PASSAGE[1];
                                        TrackList[TrackNum].PassageList[0] = new PASSAGE();
                                        TrackList[TrackNum].PassageList[0].PassageNum = 0;
                                        TrackList[TrackNum].PassageList[0].ParentTrackNum = TrackNum;
                                        TrackList[TrackNum].PassageList[0].FirstBarNum = 0;
                                        TrackList[TrackNum].PassageList[0].LastBarNum = TrackList[TrackNum].BarNumTotal - 1;
                                        TrackList[TrackNum].PassageList[0].Tonality = 13;
                                        TrackList[TrackNum].PassageNumTotal = 1;
                                    }
                                    TrackNum++;
                                    TrackNumTotal = TrackNum;
                                }
                            }
                        }
                        break;
                    }
                case 3: // load ust for UTAU
                    {
                        bool USTValid = false;
                        StreamReader USTReader = new StreamReader(FilePath, Encoding.GetEncoding("Shift-JIS"));
                        int NoteNum = 0;
                        int BarNum = 0;
                        int Time = 0;
                        //建立音轨列表
                        TrackNumTotal = 1;
                        TrackList = new TRACK[TrackNumTotal];
                        long HarmoNumMax = TrackNumTotal * Constants.HARMONY_TYPE_MAX;
                        HarmoList = new HARMOTRACK[HarmoNumMax];
                        TrackList[0] = new TRACK();
                        TrackList[0].TrackNum = 0;
                        TrackList[0].TrackName = FileName.Remove(FileName.Length - 4, 4);
                        for (int i = 0; i < 7; i++)
                        {
                            TrackList[0].ChildHarmoTrackNum[i] = -1;
                        }
                        TrackList[0].IsTonalized = false;
                        TrackNumTotal = 1;
                        //建立音符列表，读取音符信息
                        this.ProjectName = "";
                        for (string ReadBuf = "Starting"; ReadBuf != "[#TRACKEND]" && ReadBuf != null; ReadBuf = USTReader.ReadLine())
                        {
                            if (ReadBuf.Contains("ProjectName="))
                            {
                                this.ProjectName = ReadBuf.Remove(0, 12);
                            }
                            if (ReadBuf.Contains("[#0000]"))
                            {
                                USTValid = true;
                                TrackList[0].NoteList = new NOTE[10000];
                                TrackList[0].NoteList[NoteNum] = new NOTE();
                                TrackList[0].NoteList[NoteNum].NoteNum = NoteNum;
                                TrackList[0].NoteList[NoteNum].NoteID = ReadBuf.Substring(2, 4);
                                bool NoteIsValid = false;
                                for (ReadBuf = USTReader.ReadLine(); ReadBuf != "[#TRACKEND]"; ReadBuf = USTReader.ReadLine())
                                {
                                    if (ReadBuf.Contains("[#"))
                                    {
                                        TrackList[0].NoteList[NoteNum] = new NOTE();
                                        TrackList[0].NoteList[NoteNum].NoteNum = NoteNum;
                                        TrackList[0].NoteList[NoteNum].NoteID = ReadBuf.Substring(2, 4);
                                        NoteIsValid = false;
                                    }
                                    if (ReadBuf.Contains("Length="))
                                    {
                                        TrackList[0].NoteList[NoteNum].NoteTimeOn = Time;
                                        Time += Convert.ToInt32(ReadBuf.Substring(7, ReadBuf.Length - 7));
                                        TrackList[0].NoteList[NoteNum].NoteTimeOff = Time;
                                    }
                                    if (ReadBuf.Contains("Lyric="))
                                    {
                                        if (ReadBuf.Substring(6, ReadBuf.Length - 6) != "R" && TrackList[0].NoteList[NoteNum].GetNoteLength() != 0)
                                        {
                                            NoteIsValid = true;
                                        }
                                    }
                                    if (ReadBuf.Contains("NoteNum="))
                                    {
                                        TrackList[0].NoteList[NoteNum].NoteKey = Convert.ToInt32(ReadBuf.Substring(8, ReadBuf.Length - 8));
                                        if (NoteIsValid)
                                        {
                                            NoteNum++;
                                        }
                                    }
                                }
                                TrackList[0].NoteNumTotal = NoteNum;
                                //建立小节列表，读取小节信息
                                int MaxBarNum = Convert.ToInt32(Time / Constants.UST_BAR_TIME) + 1;
                                TrackList[0].BarList = new BAR[MaxBarNum];
                                if (TrackList[0].NoteNumTotal == 0)
                                {
                                    TrackList[0].TrackEmptiness = true;
                                }
                                else
                                {
                                    TrackList[0].TrackEmptiness = false;
                                    for (int i = 0, j = 0; i < MaxBarNum && j < TrackList[0].NoteNumTotal; i++, BarNum++)
                                    {
                                        TrackList[0].BarList[i] = new BAR();
                                        TrackList[0].BarList[i].BarNum = i;
                                        TrackList[0].BarList[i].BarTimeOn = i * Constants.UST_BAR_TIME;
                                        TrackList[0].BarList[i].BarTimeOff = (i + 1) * Constants.UST_BAR_TIME;
                                        TrackList[0].BarList[i].ParentTrackNum = 0;
                                        if (TrackList[0].NoteList[j].NoteTimeOn >= TrackList[0].BarList[i].BarTimeOff)
                                        {
                                            TrackList[0].BarList[i].BarEmptiness = true;
                                        }
                                        else
                                        {
                                            TrackList[0].BarList[i].BarEmptiness = false;
                                            TrackList[0].BarList[i].FirstNoteNum = j;
                                            j++;
                                        }
                                        while (j <= TrackList[0].NoteNumTotal - 1 && TrackList[0].NoteList[j].NoteTimeOn < TrackList[0].BarList[i].BarTimeOff)
                                        {
                                            j++;
                                        }
                                        if (!TrackList[0].BarList[i].BarEmptiness)
                                        {
                                            TrackList[0].BarList[i].LastNoteNum = j - 1;
                                        }
                                        if (TrackList[0].BarList[i].BarEmptiness)
                                        {
                                            TrackList[0].BarList[i].BarValidity = true;
                                        }
                                        else if ((Convert.ToDouble(TrackList[0].BarList[i].GetValidLength(TrackList[0])) / Convert.ToDouble(TrackList[0].BarList[i].GetBarLength())) < Constants.VALID_LENGTH_PERCENT_THRESHOLD)
                                        {
                                            TrackList[0].BarList[i].BarValidity = false;
                                        }
                                        else
                                        {
                                            TrackList[0].BarList[i].BarValidity = true;
                                        }
                                    }
                                    TrackList[0].BarNumTotal = BarNum;
                                }
                            }
                        }
                        TrackList[0].PassageList = new PASSAGE[1];
                        TrackList[0].PassageList[0] = new PASSAGE();
                        TrackList[0].PassageList[0].PassageNum = 0;
                        TrackList[0].PassageList[0].ParentTrackNum = 0;
                        TrackList[0].PassageList[0].FirstBarNum = 0;
                        TrackList[0].PassageList[0].LastBarNum = TrackList[0].BarNumTotal - 1;
                        TrackList[0].PassageList[0].Tonality = 13;
                        TrackList[0].PassageNumTotal = 1;
                        if (!USTValid)
                        {
                            MessageBox.Show(ProgramTexts.GetProgramText("loading_failure"),ProgramTexts.GetProgramText("load"));
                            Exception LoadingFailure = new MyException();
                            throw LoadingFailure;
                        }
                        break;
                    }
                case 4: // load ccs for CeVIO
                    {
                        int TrackNum = 0;
                        XmlDocument ccs = new XmlDocument();
                        ccs.Load(FilePath);
                        //建立音轨列表
                        XmlNode root = ccs.FirstChild.NextSibling;
                        XmlNode sequence = null;
                        XmlNode scene = null;
                        XmlNode groups = null;
                        XmlNode units = null;
                        if (root.HasChildNodes)
                        {
                            for (int i = 0; i < root.ChildNodes.Count; i++)
                            {
                                if (root.ChildNodes[i].Name == "Sequence")
                                {
                                    sequence = root.ChildNodes[i];
                                    break;
                                }
                            }
                        }
                        if (sequence.HasChildNodes)
                        {
                            for (int i = 0; i < sequence.ChildNodes.Count; i++)
                            {
                                if (sequence.ChildNodes[i].Name == "Scene")
                                {
                                    scene = sequence.ChildNodes[i];
                                    break;
                                }
                            }
                        }
                        if (scene.HasChildNodes)
                        {
                            for (int i = 0; i < scene.ChildNodes.Count; i++)
                            {
                                if (scene.ChildNodes[i].Name == "Groups")
                                {
                                    groups = scene.ChildNodes[i];
                                    break;
                                }
                            }
                        }
                        if (groups.HasChildNodes)
                        {
                            int count = 0;
                            for (int i = 0; i < groups.ChildNodes.Count; i++)
                            {
                                if (groups.ChildNodes[i].Name == "Group")
                                {
                                    count++;
                                }
                            }
                            TrackList = new TRACK[count];
                            HarmoList = new HARMOTRACK[count * 7];
                        }
                        if (scene.HasChildNodes)
                        {
                            for (int i = 0; i < scene.ChildNodes.Count; i++)
                            {
                                if (scene.ChildNodes[i].Name == "Units")
                                {
                                    units = scene.ChildNodes[i];
                                    break;
                                }
                            }
                        }
                        if (groups.HasChildNodes)
                        {
                            for (int i = 0; i < groups.ChildNodes.Count; i++)
                            {
                                if (groups.ChildNodes[i].Name == "Group")
                                {
                                    XmlElement group = (XmlElement)groups.ChildNodes[i];
                                    XmlElement unit = null;
                                    TrackList[TrackNum] = new TRACK();
                                    TrackList[TrackNum].TrackNum = TrackNum;
                                    TrackList[TrackNum].TrackName = group.GetAttribute("Name");
                                    for (int k = 0; k < 7; k++)
                                    {
                                        TrackList[TrackNum].ChildHarmoTrackNum[k] = -1;
                                    }
                                    TrackList[TrackNum].IsTonalized = false;
                                    TrackList[TrackNum].TrackIDforCeVIO = group.GetAttribute("Id");
                                    if (group.GetAttribute("Category") != "SingerSong")
                                    {
                                        TrackList[TrackNum].TrackEmptiness = true;
                                    }
                                    else
                                    {
                                        if (units.HasChildNodes)
                                        {
                                            for (int j = 0; j < units.ChildNodes.Count; j++)
                                            {
                                                if (units.ChildNodes[j].Name == "Unit")
                                                {
                                                    if (((XmlElement)units.ChildNodes[j]).GetAttribute("Group") == TrackList[TrackNum].TrackIDforCeVIO)
                                                    {
                                                        unit = (XmlElement)units.ChildNodes[j];
                                                        break;
                                                    }
                                                }
                                            }
                                        }
                                        int NoteNum = 0;
                                        //建立每个音轨的音符列表，读取音符信息
                                        int NoteCount = 0;
                                        XmlElement score = null;
                                        XmlNode song = null;
                                        for (int j = 0; j < unit.ChildNodes.Count; j++)
                                        {
                                            if (unit.ChildNodes[j].Name == "Song")
                                            {
                                                song = unit.ChildNodes[j];
                                                for (int k = 0; k < song.ChildNodes.Count; k++)
                                                {
                                                    if (song.ChildNodes[k].Name == "Score")
                                                    {
                                                        score = (XmlElement)song.ChildNodes[k];
                                                        break;
                                                    }
                                                }
                                                for (int k = 0; k < score.ChildNodes.Count; k++)
                                                {
                                                    if (score.ChildNodes[k].Name == "Note")
                                                    {
                                                        NoteCount++;
                                                    }
                                                }
                                                break;
                                            }
                                        }
                                        TrackList[TrackNum].NoteList = new NOTE[NoteCount];
                                        for (int k = 0; k < score.ChildNodes.Count; k++)
                                        {
                                            if (score.ChildNodes[k].Name == "Note")
                                            {
                                                XmlElement note = (XmlElement)score.ChildNodes[k];
                                                TrackList[TrackNum].NoteList[NoteNum] = new NOTE();
                                                TrackList[TrackNum].NoteList[NoteNum].NoteNum = NoteNum;
                                                TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn = Convert.ToInt32(note.GetAttribute("Clock"));
                                                TrackList[TrackNum].NoteList[NoteNum].NoteTimeOff = TrackList[TrackNum].NoteList[NoteNum].NoteTimeOn + Convert.ToInt32(note.GetAttribute("Duration"));
                                                TrackList[TrackNum].NoteList[NoteNum].NoteKey = Convert.ToInt32(note.GetAttribute("PitchStep")) + (Convert.ToInt32(note.GetAttribute("PitchOctave")) + 1) * 12;
                                                NoteNum++;
                                            }
                                        }
                                        TrackList[TrackNum].NoteNumTotal = NoteNum;
                                        //建立小节列表，读取小节信息
                                        TrackList[TrackNum].BarList = new BAR[1000];
                                        if (NoteNum == 0)
                                        {
                                            TrackList[TrackNum].TrackEmptiness = true;
                                        }
                                        else
                                        {
                                            TrackList[TrackNum].TrackEmptiness = false;
                                            int resolution = 480;
                                            XmlNode beat = null;
                                            XmlElement TimeSig = null;
                                            int pos_timgSig = 0;
                                            int nume = 4;
                                            int denomi = 4;
                                            int BarTime = 0;
                                            for (int k = 0; k < song.ChildNodes.Count; k++)
                                            {
                                                if (song.ChildNodes[k].Name == "Beat")
                                                {
                                                    beat = (XmlElement)song.ChildNodes[k];
                                                    for (int l = 0; l < beat.ChildNodes.Count; l++)
                                                    {
                                                        if (beat.ChildNodes[l].Name == "Time")
                                                        {
                                                            TimeSig = (XmlElement)beat.ChildNodes[l];
                                                            break;
                                                        }
                                                    }
                                                }
                                            }
                                            for (int BarNum = 0, j = 0; j < TrackList[TrackNum].NoteNumTotal; BarNum++)
                                            {
                                                TrackList[TrackNum].BarList[BarNum] = new BAR();
                                                TrackList[TrackNum].BarList[BarNum].BarNum = BarNum;
                                                pos_timgSig = Convert.ToInt32(TimeSig.GetAttribute("Clock"));
                                                nume = Convert.ToInt32(TimeSig.GetAttribute("Beats"));
                                                denomi = Convert.ToInt32(TimeSig.GetAttribute("BeatType"));
                                                if (pos_timgSig / resolution == BarNum)
                                                {
                                                    BarTime = nume * 4 * resolution / denomi;
                                                    XmlElement nTimeSig = (XmlElement)TimeSig.NextSibling;
                                                    while (nTimeSig != null && nTimeSig.Name != "Time")
                                                    {
                                                        nTimeSig = (XmlElement)TimeSig.NextSibling;
                                                    }
                                                    if (nTimeSig != null)
                                                    {
                                                        TimeSig = nTimeSig;
                                                    }
                                                }
                                                if (BarNum == 0)
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarTimeOn = 0;
                                                }
                                                else
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarTimeOn = TrackList[TrackNum].BarList[BarNum - 1].BarTimeOff;
                                                }
                                                TrackList[TrackNum].BarList[BarNum].BarTimeOff = TrackList[TrackNum].BarList[BarNum].BarTimeOn + BarTime;
                                                TrackList[TrackNum].BarList[BarNum].ParentTrackNum = TrackNum;
                                                if (TrackList[TrackNum].NoteList[j].NoteTimeOn >= TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarEmptiness = true;
                                                }
                                                else
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarEmptiness = false;
                                                    TrackList[TrackNum].BarList[BarNum].FirstNoteNum = j;
                                                    j++;
                                                }
                                                while (j <= TrackList[TrackNum].NoteNumTotal - 1 && TrackList[TrackNum].NoteList[j].NoteTimeOn < TrackList[TrackNum].BarList[BarNum].BarTimeOff)
                                                {
                                                    j++;
                                                }
                                                if (!TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].LastNoteNum = j - 1;
                                                }
                                                if (TrackList[TrackNum].BarList[BarNum].BarEmptiness)
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                                }
                                                else if (Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetValidLength(TrackList[TrackNum])) / Convert.ToDouble(TrackList[TrackNum].BarList[BarNum].GetBarLength()) < Constants.VALID_LENGTH_PERCENT_THRESHOLD)
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarValidity = false;
                                                }
                                                else
                                                {
                                                    TrackList[TrackNum].BarList[BarNum].BarValidity = true;
                                                }
                                                TrackList[TrackNum].BarNumTotal++;
                                            }
                                            TrackList[TrackNum].PassageList = new PASSAGE[1];
                                            TrackList[TrackNum].PassageList[0] = new PASSAGE();
                                            TrackList[TrackNum].PassageList[0].PassageNum = 0;
                                            TrackList[TrackNum].PassageList[0].ParentTrackNum = TrackNum;
                                            TrackList[TrackNum].PassageList[0].FirstBarNum = 0;
                                            TrackList[TrackNum].PassageList[0].LastBarNum = TrackList[TrackNum].BarNumTotal - 1;
                                            TrackList[TrackNum].PassageList[0].Tonality = 13;
                                            TrackList[TrackNum].PassageNumTotal = 1;
                                        }
                                    }
                                    TrackNum++;
                                    TrackNumTotal = TrackNum;
                                }
                            }
                        }
                        break;
                    }
                default:
                    {
                        break;
                    }
            }
        }
        public void DATASave(string SavingPath)
        {
            bool RemoveParameters = DialogResult.Yes != MessageBox.Show(ProgramTexts.GetProgramText("saving_removeparameters"), ProgramTexts.GetProgramText("saveas"), MessageBoxButtons.YesNo);
            switch (FileFormat)
            {
                case 1: // save vsqx for VOCALOID3
                    {
                        XmlDocument vsqx = new XmlDocument();
                        vsqx.Load(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        for (int HarmoNum = 0; HarmoNum < HarmoNumTotal; HarmoNum++)
                        {
                            if (!HarmoList[HarmoNum].IsSaved)
                            {
                                XmlNode root = vsqx.FirstChild.NextSibling;
                                XmlNode mixer = null;
                                XmlNode vsUnit = null;
                                XmlNode vsTrack = null;
                                XmlNode seUnit = null;
                                XmlNode seTrack = null;
                                //定位各节点
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "mixer")
                                    {
                                        mixer = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < mixer.ChildNodes.Count; i++)
                                {
                                    if (mixer.ChildNodes[i].Name == "vsUnit" && mixer.ChildNodes[i].FirstChild.FirstChild.Value == HarmoList[HarmoNum].ParentTrackNum.ToString())
                                    {
                                        vsUnit = mixer.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < mixer.ChildNodes.Count; i++)
                                {
                                    if (mixer.ChildNodes[i].Name == "seUnit")
                                    {
                                        seUnit = mixer.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "vsTrack" && root.ChildNodes[i].FirstChild.FirstChild.Value == HarmoList[HarmoNum].ParentTrackNum.ToString())
                                    {
                                        vsTrack = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "seTrack")
                                    {
                                        seTrack = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                //拷贝节点
                                XmlNode HarmoUnit = vsUnit.Clone();
                                mixer.InsertBefore(HarmoUnit, seUnit);
                                XmlNode HarmoTrack = vsTrack.Clone();
                                root.InsertBefore(HarmoTrack, seTrack);
                                //修改节点的内容
                                int ExistingTrackNum = TrackNumTotal;
                                for (int j = 0; j < HarmoNumTotal; j++)
                                {
                                    if (HarmoList[j].IsSaved)
                                    {
                                        ExistingTrackNum++;
                                    }
                                }
                                HarmoUnit.FirstChild.FirstChild.Value = (ExistingTrackNum + HarmoNum).ToString();
                                int NoteNum = 0;
                                for (int i = 0; i < HarmoTrack.ChildNodes.Count; i++)
                                {
                                    if (HarmoTrack.ChildNodes[i].Name == "vsTrackNo")
                                    {
                                        HarmoTrack.ChildNodes[i].FirstChild.Value = (ExistingTrackNum + HarmoNum).ToString();
                                    }
                                    if (HarmoTrack.ChildNodes[i].Name == "trackName")
                                    {
                                        HarmoTrack.ChildNodes[i].FirstChild.Value = HarmoList[HarmoNum].TrackName; //CDATA
                                    }
                                    if (HarmoTrack.ChildNodes[i].Name == "musicalPart")
                                    {
                                        XmlNode musicalPart = HarmoTrack.ChildNodes[i];
                                        for (int j = 0; j < musicalPart.ChildNodes.Count && NoteNum < HarmoList[HarmoNum].NoteNumTotal; j++)
                                        {
                                            //移除参数
                                            if (RemoveParameters)
                                            {
                                                if (musicalPart.ChildNodes[j].Name == "mCtrl")
                                                {
                                                    musicalPart.RemoveChild(musicalPart.ChildNodes[j]);
                                                    j--;
                                                }
                                            }
                                            //修改音高
                                            if (musicalPart.ChildNodes[j].Name == "note")
                                            {
                                                XmlNode note = musicalPart.ChildNodes[j];
                                                if (HarmoList[HarmoNum].NoteList[NoteNum].NoteValidity == false)
                                                {
                                                    musicalPart.RemoveChild(note);
                                                    j--;
                                                }
                                                else
                                                {
                                                    note.FirstChild.NextSibling.NextSibling.FirstChild.Value = (HarmoList[HarmoNum].NoteList[NoteNum].NoteKey + 12).ToString();
                                                }
                                                NoteNum++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        try
                        {
                            File.Copy(FilePath, FilePath + ".bak", true);
                            vsqx.Save(SavingPath);
                            vsqx.Save(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        }
                        catch
                        {
                            MessageBox.Show(ProgramTexts.GetProgramText("saving_failure"), ProgramTexts.GetProgramText("save"));
                            File.Copy(FilePath + ".bak", FilePath, true);
                            break;
                        }
                        File.Delete(FilePath + ".bak");
                        for (int i = 0; i < HarmoNumTotal; i++)
                        {
                            HarmoList[i].IsSaved = true;
                        }
                        MessageBox.Show(ProgramTexts.GetProgramText("saving_success"), ProgramTexts.GetProgramText("save"));
                        break;
                    }
                case 2: // save vsqx for VOCALOID4
                    {
                        XmlDocument vsqx = new XmlDocument();
                        vsqx.Load(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        for (int HarmoNum = 0; HarmoNum < HarmoNumTotal; HarmoNum++)
                        {
                            if (!HarmoList[HarmoNum].IsSaved)
                            {
                                XmlNode root = vsqx.FirstChild.NextSibling;
                                XmlNode mixer = null;
                                XmlNode vsUnit = null;
                                XmlNode vsTrack = null;
                                XmlNode seUnit = null;
                                XmlNode seTrack = null;
                                //定位各节点
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "mixer")
                                    {
                                        mixer = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < mixer.ChildNodes.Count; i++)
                                {
                                    if (mixer.ChildNodes[i].Name == "vsUnit" && mixer.ChildNodes[i].FirstChild.FirstChild.Value == HarmoList[HarmoNum].ParentTrackNum.ToString())
                                    {
                                        vsUnit = mixer.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < mixer.ChildNodes.Count; i++)
                                {
                                    if (mixer.ChildNodes[i].Name == "monoUnit")
                                    {
                                        seUnit = mixer.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "vsTrack" && root.ChildNodes[i].FirstChild.FirstChild.Value == HarmoList[HarmoNum].ParentTrackNum.ToString())
                                    {
                                        vsTrack = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                for (int i = 0; i < root.ChildNodes.Count; i++)
                                {
                                    if (root.ChildNodes[i].Name == "monoTrack")
                                    {
                                        seTrack = root.ChildNodes[i];
                                        break;
                                    }
                                }
                                //拷贝节点
                                XmlNode HarmoUnit = vsUnit.Clone();
                                mixer.InsertBefore(HarmoUnit, seUnit);
                                XmlNode HarmoTrack = vsTrack.Clone();
                                root.InsertBefore(HarmoTrack, seTrack);

                                //修改节点的内容
                                int ExistingTrackNum = TrackNumTotal;
                                for (int j = 0; j < HarmoNumTotal; j++)
                                {
                                    if (HarmoList[j].IsSaved)
                                    {
                                        ExistingTrackNum++;
                                    }
                                }
                                HarmoUnit.FirstChild.FirstChild.Value = (ExistingTrackNum + HarmoNum).ToString();
                                int NoteNum = 0;
                                for (int i = 0; i < HarmoTrack.ChildNodes.Count; i++)
                                {
                                    if (HarmoTrack.ChildNodes[i].Name == "tNo")
                                    {
                                        HarmoTrack.ChildNodes[i].FirstChild.Value = (ExistingTrackNum + HarmoNum).ToString();
                                    }
                                    if (HarmoTrack.ChildNodes[i].Name == "name")
                                    {
                                        HarmoTrack.ChildNodes[i].FirstChild.Value = HarmoList[HarmoNum].TrackName; //CDATA
                                    }
                                    if (HarmoTrack.ChildNodes[i].Name == "vsPart")
                                    {
                                        XmlNode musicalPart = HarmoTrack.ChildNodes[i];
                                        for (int j = 0; j < musicalPart.ChildNodes.Count && NoteNum < HarmoList[HarmoNum].NoteNumTotal; j++)
                                        {
                                            //移除参数
                                            if (RemoveParameters)
                                            {
                                                if (musicalPart.ChildNodes[j].Name == "cc")
                                                {
                                                    musicalPart.RemoveChild(musicalPart.ChildNodes[j]);
                                                    j--;
                                                }
                                            }
                                            //修改音高
                                            if (musicalPart.ChildNodes[j].Name == "note")
                                            {
                                                XmlNode note = musicalPart.ChildNodes[j];
                                                if (HarmoList[HarmoNum].NoteList[NoteNum].NoteValidity == false)
                                                {
                                                    musicalPart.RemoveChild(note);
                                                    j--;
                                                }
                                                else
                                                {
                                                    note.FirstChild.NextSibling.NextSibling.FirstChild.Value = (HarmoList[HarmoNum].NoteList[NoteNum].NoteKey + 12).ToString();
                                                }
                                                NoteNum++;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        try
                        {
                            File.Copy(FilePath, FilePath + ".bak", true);
                            vsqx.Save(SavingPath);
                            vsqx.Save(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        }
                        catch
                        {
                            MessageBox.Show(ProgramTexts.GetProgramText("saving_failure"), ProgramTexts.GetProgramText("save"));
                            File.Copy(FilePath + ".bak", FilePath, true);
                            break;
                        }
                        File.Delete(FilePath + ".bak");
                        for (int i = 0; i < HarmoNumTotal; i++)
                        {
                            HarmoList[i].IsSaved = true;
                        }
                        MessageBox.Show(ProgramTexts.GetProgramText("saving_success"), ProgramTexts.GetProgramText("save"));
                        break;
                    }
                case 4: // save ccs
                    {
                        XmlDocument ccs = new XmlDocument();
                        ccs.Load(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        for (int HarmoNum = 0; HarmoNum < HarmoNumTotal; HarmoNum++)
                        {
                            if (!HarmoList[HarmoNum].IsSaved)
                            {
                                XmlNode root = ccs.FirstChild.NextSibling;
                                XmlNode unit = null;
                                XmlNode group = null;
                                //定位各节点
                                XmlNode sequence = null;
                                XmlNode scene = null;
                                XmlNode groups = null;
                                XmlNode units = null;
                                if (root.HasChildNodes)
                                {
                                    for (int i = 0; i < root.ChildNodes.Count; i++)
                                    {
                                        if (root.ChildNodes[i].Name == "Sequence")
                                        {
                                            sequence = root.ChildNodes[i];
                                            break;
                                        }
                                    }
                                }
                                if (sequence.HasChildNodes)
                                {
                                    for (int i = 0; i < sequence.ChildNodes.Count; i++)
                                    {
                                        if (sequence.ChildNodes[i].Name == "Scene")
                                        {
                                            scene = sequence.ChildNodes[i];
                                            break;
                                        }
                                    }
                                }
                                if (scene.HasChildNodes)
                                {
                                    for (int i = 0; i < scene.ChildNodes.Count; i++)
                                    {
                                        if (scene.ChildNodes[i].Name == "Groups")
                                        {
                                            groups = scene.ChildNodes[i];
                                            break;
                                        }
                                    }
                                }
                                if (scene.HasChildNodes)
                                {
                                    for (int i = 0; i < scene.ChildNodes.Count; i++)
                                    {
                                        if (scene.ChildNodes[i].Name == "Units")
                                        {
                                            units = scene.ChildNodes[i];
                                            break;
                                        }
                                    }
                                }
                                if (units.HasChildNodes)
                                {
                                    for (int i = 0; i < units.ChildNodes.Count; i++)
                                    {
                                        if (units.ChildNodes[i].Name == "Unit")
                                        {
                                            if (((XmlElement)units.ChildNodes[i]).GetAttribute("Group") == HarmoList[HarmoNum].TrackIDforCeVIO)
                                            {
                                                unit = (XmlElement)units.ChildNodes[i];
                                                break;
                                            }
                                        }
                                    }
                                }
                                if (groups.HasChildNodes)
                                {
                                    for (int i = 0; i < groups.ChildNodes.Count; i++)
                                    {
                                        if (groups.ChildNodes[i].Name == "Group")
                                        {
                                            if (((XmlElement)groups.ChildNodes[i]).GetAttribute("Id") == HarmoList[HarmoNum].TrackIDforCeVIO)
                                            {
                                                group = (XmlElement)groups.ChildNodes[i];
                                                break;
                                            }
                                        }
                                    }
                                }

                                //拷贝节点
                                XmlElement HarmoUnit = (XmlElement)unit.Clone();
                                units.InsertAfter(HarmoUnit, units.LastChild);
                                XmlElement HarmoTrack = (XmlElement)group.Clone();
                                groups.InsertAfter(HarmoTrack, groups.LastChild);
                                //修改节点的内容
                                string new_id = HarmoList[HarmoNum].TrackIDforCeVIO;
                                if (new_id[1] == '0')
                                {
                                    new_id = HarmoList[HarmoNum].HarmonicType.ToString() + "1" + new_id.Substring(2);
                                }
                                else
                                {
                                    new_id = HarmoList[HarmoNum].HarmonicType.ToString() + "0" + new_id.Substring(2);
                                }
                                int NoteNum = 0;
                                HarmoTrack.SetAttribute("Id", new_id);
                                HarmoTrack.SetAttribute("Name", HarmoList[HarmoNum].TrackName);
                                HarmoUnit.SetAttribute("Group", new_id);
                                XmlNode HarmoScore = null;
                                XmlNode HarmoParameter = null;
                                if (HarmoUnit.HasChildNodes)
                                {
                                    for (int i = 0; i < HarmoUnit.ChildNodes.Count; i++)
                                    {
                                        if (HarmoUnit.ChildNodes[i].Name == "Song")
                                        {
                                            XmlNode HarmoSong = HarmoUnit.ChildNodes[i];
                                            if (HarmoSong.HasChildNodes)
                                            {
                                                for (int j = 0; j < HarmoSong.ChildNodes.Count; j++)
                                                {
                                                    if (HarmoSong.ChildNodes[j].Name == "Score")
                                                    {
                                                        HarmoScore = HarmoSong.ChildNodes[j];
                                                    }
                                                    if (HarmoSong.ChildNodes[j].Name == "Parameter")
                                                    {
                                                        HarmoParameter = HarmoSong.ChildNodes[j];
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                                for (int j = 0; j < HarmoScore.ChildNodes.Count && NoteNum < HarmoList[HarmoNum].NoteNumTotal; j++)
                                {
                                    if (HarmoScore.ChildNodes[j].Name == "Note")
                                    {
                                        XmlNode note = HarmoScore.ChildNodes[j];
                                        if (HarmoList[HarmoNum].NoteList[NoteNum].NoteValidity == false)
                                        {
                                            HarmoScore.RemoveChild(note);
                                            j--;
                                        }
                                        else
                                        {
                                            ((XmlElement)note).SetAttribute("PitchStep", (HarmoList[HarmoNum].NoteList[NoteNum].NoteKey % 12).ToString());
                                            ((XmlElement)note).SetAttribute("PitchOctave", (HarmoList[HarmoNum].NoteList[NoteNum].NoteKey / 12 - 1).ToString());
                                        }
                                        NoteNum++;
                                    }
                                }
                                if (HarmoParameter != null)
                                {
                                    for (int j = 0; j < HarmoParameter.ChildNodes.Count; j++)
                                    {
                                        if (HarmoParameter.ChildNodes[j].Name == "LogF0" || RemoveParameters)
                                        {
                                            HarmoParameter.RemoveChild(HarmoParameter.ChildNodes[j]);
                                        }
                                    }
                                }
                            }
                        }
                        try
                        {
                            File.Copy(FilePath, FilePath + ".bak", true);
                            ccs.Save(SavingPath);
                            ccs.Save(FilePath.Remove(this.FilePath.Length - 5, 5) + ".temp");
                        }
                        catch
                        {
                            MessageBox.Show(ProgramTexts.GetProgramText("saving_failure"), ProgramTexts.GetProgramText("save"));
                            File.Copy(FilePath + ".bak", FilePath, true);
                            break;
                        }
                        File.Delete(FilePath + ".bak");
                        for (int i = 0; i < HarmoNumTotal; i++)
                        {
                            HarmoList[i].IsSaved = true;
                        }
                        MessageBox.Show(ProgramTexts.GetProgramText("saving_success"), ProgramTexts.GetProgramText("save"));
                        break;
                    }
            }
        }
        public void DATASave(string SavingPath, int HarmoNum) // save ust for UTAU
        {
            if (SavingPath == FilePath)
            {
                MessageBox.Show(ProgramTexts.GetProgramText("saving_ust1"), ProgramTexts.GetProgramText("save"));
                return;
            }
            string UstContent = File.ReadAllText(FilePath, Encoding.GetEncoding("Shift-JIS"));
            int pos = 0, pos2 = 0;
            for (int i = 0; i < HarmoList[HarmoNum].NoteNumTotal; i++)
            {
                if (HarmoList[HarmoNum].NoteList[i].NoteValidity)
                {
                    pos = UstContent.IndexOf("[#" + HarmoList[HarmoNum].NoteList[i].NoteID + "]", pos);
                    pos = UstContent.IndexOf("NoteNum=", pos);
                    pos2 = UstContent.IndexOf('\r', pos);
                    UstContent = UstContent.Remove(pos + 8, pos2 - pos - 8);
                    UstContent = UstContent.Insert(pos + 8, (HarmoList[HarmoNum].NoteList[i].NoteKey).ToString());
                }
                else
                {
                    pos = UstContent.IndexOf("[#" + HarmoList[HarmoNum].NoteList[i].NoteID + "]", pos);
                    pos = UstContent.IndexOf("Lyric=", pos);
                    pos2 = UstContent.IndexOf('\r', pos);
                    UstContent = UstContent.Remove(pos + 6, pos2 - pos - 6);
                    UstContent = UstContent.Insert(pos + 6, "R");
                }
            }
            File.WriteAllText(SavingPath, UstContent, Encoding.GetEncoding("Shift-JIS"));
        }
        public void DeleteHarmoTrack(int HarmoNum)
        {
            for (int i = HarmoNum; i < HarmoNumTotal - 1; i++)
            {
                HarmoList[i] = new HARMOTRACK(HarmoList[i + 1]);
                HarmoList[i].TrackNum = HarmoList[i].TrackNum - 1;
            }
            HarmoList[HarmoNumTotal - 1] = null;
            HarmoNumTotal--;
        }
    }

    public class NOTE
    {
        public NOTE() { }
        public NOTE(NOTE OriNote)
        {
            NoteNum = OriNote.NoteNum;
            NoteKey = OriNote.NoteKey;
            NoteTimeOn = OriNote.NoteTimeOn;
            NoteTimeOff = OriNote.NoteTimeOff;
            NoteValidity = OriNote.NoteValidity;
            NoteID = OriNote.NoteID;
        }
        public int NoteNum;
        public int NoteKey;
        public int NoteTimeOn;
        public int NoteTimeOff;
        public bool NoteValidity = true;
        public string NoteID; //only for UST mode
        public string GetNoteKeyAsString()
        {
            return Constants.Tonality_Type((int)(NoteKey % 12)) + Convert.ToString(NoteKey / 12 - 1);
        }
        public int GetNoteLength()
        {
            return NoteTimeOff - NoteTimeOn;
        }
    }
    public class BAR
    {
        public BAR() { }
        public BAR(BAR OriBar)
        {
            BarNum = OriBar.BarNum;
            BarTimeOn = OriBar.BarTimeOn;
            BarTimeOff = OriBar.BarTimeOff;
            BarEmptiness = OriBar.BarEmptiness;
            BarValidity = OriBar.BarValidity;
            ParentTrackNum = OriBar.ParentTrackNum;
            FirstNoteNum = OriBar.FirstNoteNum;
            LastNoteNum = OriBar.LastNoteNum;
        }
        public int BarNum;
        public int BarTimeOn;
        public int BarTimeOff;
        public bool BarEmptiness;
        public bool BarValidity;
        public int ParentTrackNum;
        public int FirstNoteNum;
        public int LastNoteNum;
        public int GetBarLength()
        {
            return BarTimeOff - BarTimeOn;
        }
        public string GetContentAsString(TRACK ParentTrack)
        {
            string tmp = "";
            if (!BarEmptiness)
            {
                for (int i = FirstNoteNum; i <= LastNoteNum; i++)
                {
                    tmp += ParentTrack.NoteList[i].GetNoteKeyAsString() + " ";
                }
                return tmp.Remove(tmp.Length - 1, 1);
            }
            else
            {
                return "";
            }
        }
        public int GetValidLength(TRACK ParentTrack)
        {
            int lenbuf = 0;
            for (int i = FirstNoteNum; i <= LastNoteNum; i++)
            {
                lenbuf += (ParentTrack.NoteList[i]).GetNoteLength();
            }
            return lenbuf;
        }
        public bool AdaptWithPassage(TRACK ParentTrack, PASSAGE nPassage)
        {
            if (BarEmptiness)
            {
                return true;
            }
            else if (!BarValidity)
            {
                return true;
            }
            else if (nPassage.IsAtonal())
            {
                return true;
            }
            else
            {
                double[] NoteNameProb = new double[12];
                int NoteTimeTotal = GetValidLength(ParentTrack);
                for (int i = 0; i < 12; i++)
                {
                    int sum = 0;
                    for (int j = FirstNoteNum; j <= LastNoteNum; j++)
                    {
                        if (ParentTrack.NoteList[j].NoteKey % 12 == i)
                        {
                            sum += ParentTrack.NoteList[j].GetNoteLength();
                        }
                    }
                    NoteNameProb[i] = ((double)(sum)) / ((double)(NoteTimeTotal));
                }
                if (nPassage.IsSure())
                {
                    int Tonality = Constants.ConvertTonalityType(nPassage.GetTonalityOptionAsString());
                    double prob = 0;
                    for (int i = 0; i < 12; i++)
                    {
                        prob += Constants.Tonality_KeyName_Prob[Tonality, i] * NoteNameProb[i];
                    }
                    if (prob >= Constants.ADAPTING_THRESHOLD)
                    {
                        return true;
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    for (int i = 0; i < 12; i++)
                    {
                        if (nPassage.TonalityOption[i] > 0)
                        {
                            double prob = 0;
                            for (int j = 0; j < 12; j++)
                            {
                                prob += Constants.Tonality_KeyName_Prob[i, j] * NoteNameProb[j];
                            }
                            if (prob >= Constants.ADAPTING_THRESHOLD)
                            {
                                return true;
                            }
                        }
                    }
                    return false;
                }
            }
        }
    }

    public class PASSAGE
    {
        public PASSAGE() { }
        public PASSAGE(PASSAGE OriPassage)
        {
            PassageNum = OriPassage.PassageNum;
            TonalityOption = OriPassage.TonalityOption;
            Tonality = OriPassage.Tonality;
            ParentTrackNum = OriPassage.ParentTrackNum;
            FirstBarNum = OriPassage.FirstBarNum;
            LastBarNum = OriPassage.LastBarNum;
        }
        public int PassageNum;
        public int[] TonalityOption = new int[12];
        public int Tonality;
        public int ParentTrackNum;
        public int FirstBarNum;
        public int LastBarNum;
        public bool IsAtonal()
        {
            for (int i = 0; i < 12; i++)
            {
                if (TonalityOption[i] != 0)
                {
                    return false;
                }
            }
            return true;
        }
        public bool IsSure()
        {
            for (int i = 0; i < 12; i++)
            {
                if (TonalityOption[i] == 3)
                {
                    return true;
                }
            }
            return false;
        }
        public bool PassageIsEmpty(TRACK ParentTrack)
        {
            for (int i = FirstBarNum; i <= LastBarNum; i++)
            {
                if (!ParentTrack.BarList[i].BarEmptiness)
                {
                    return false;
                }
            }
            return true;
        }
        public int GetFirstNoteNum(TRACK ParentTrack)
        {
            for (int i = FirstBarNum; i <= LastBarNum; i++)
            {
                if (ParentTrack.BarList[i].BarEmptiness == false)
                {
                    return ParentTrack.BarList[i].FirstNoteNum;
                }
            }
            throw new Exception("The Bar is empty.");
        }
        public int GetLastNoteNum(TRACK ParentTrack)
        {
            for (int i = LastBarNum; i >= FirstBarNum; i--)
            {
                if (ParentTrack.BarList[i].BarEmptiness == false)
                {
                    return ParentTrack.BarList[i].LastNoteNum;
                }
            }
            throw new Exception("The Bar is empty.");
        }
        public int GetNoteTimeTotal(TRACK ParentTrack)
        {
            int sum = 0;
            for (int i = GetFirstNoteNum(ParentTrack); i <= GetLastNoteNum(ParentTrack); i++)
            {
                sum += ParentTrack.NoteList[i].GetNoteLength();
            }
            return sum;
        }
        public void CalculateTonalityOptions(TRACK ParentTrack)
        {
            double[] NoteNameProb = new double[12];
            double[] Tonality_Prob = new double[12];
            int NoteTimeTotal = GetNoteTimeTotal(ParentTrack);
            for (int i = 0; i < 12; i++)
            {
                int sum = 0;
                for (int j = GetFirstNoteNum(ParentTrack); j <= GetLastNoteNum(ParentTrack); j++)
                {
                    if (ParentTrack.NoteList[j].NoteKey % 12 == i)
                    {
                        sum += ParentTrack.NoteList[j].GetNoteLength();
                    }
                }
                NoteNameProb[i] = ((double)(sum)) / ((double)(NoteTimeTotal));
            }
            for (int i = 0; i < 12; i++)
            {
                double prob = 0;
                for (int j = 0; j < 12; j++)
                {
                    prob += NoteNameProb[j] * Constants.Tonality_KeyName_Prob[i, j];
                }
                Tonality_Prob[i] = prob;
            }
            int ProbMaxNum = Constants.SortArrayByGreatness(Tonality_Prob, 1);
            for (int i = 0; i < 12; i++)
            {
                TonalityOption[i] = 0;
            }
            if (Tonality_Prob[ProbMaxNum] >= Constants.MAXPROB_VALID_THRESHOLD)
            {
                int uncertainty = -1;
                for (int i = 0; i < 12; i++)
                {
                    if (Tonality_Prob[ProbMaxNum] == Tonality_Prob[i])
                    {
                        TonalityOption[i] = 2;
                        uncertainty++;
                    }
                    else if (Tonality_Prob[ProbMaxNum] - Tonality_Prob[i] <= Constants.PROB_SIMILAR_THRESHOLD)
                    {
                        TonalityOption[i] = 1;
                        uncertainty++;
                    }
                }
                if (uncertainty == 0)
                {
                    TonalityOption[ProbMaxNum] = 3;
                }
                else if (uncertainty >= Constants.UNCERTAIN_THRESHOLD)
                {
                    for (int i = 0; i < 12; i++)
                    {
                        TonalityOption[i] = 0;
                    }
                }
                else
                {
                    int ProbSecondMax = Constants.SortArrayByGreatness(Tonality_Prob, 2);
                    int ProbThirdMax = Constants.SortArrayByGreatness(Tonality_Prob, 3);
                    int delta1 = ProbMaxNum - ProbSecondMax;
                    int delta2 = ProbMaxNum - ProbThirdMax;
                    int delta3 = ProbSecondMax - ProbMaxNum;
                    int delta4 = ProbSecondMax - ProbThirdMax;
                    int delta5 = ProbThirdMax - ProbMaxNum;
                    int delta6 = ProbThirdMax - ProbSecondMax;
                    if ((delta1 == -5 && delta2 == -7) || (delta1 == -7 && delta2 == -5) || (delta1 == 5 && delta2 == -5) || (delta1 == -5 && delta2 == 5) || (delta1 == 7 && delta2 == 5) || (delta1 == 5 && delta2 == 7))
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            TonalityOption[i] = 0;
                        }
                        TonalityOption[ProbMaxNum] = 3;
                    }
                    else if ((delta3 == -5 && delta4 == -7) || (delta3 == -7 && delta4 == -5) || (delta3 == 5 && delta4 == -5) || (delta3 == -5 && delta4 == 5) || (delta3 == 7 && delta4 == 5) || (delta3 == 5 && delta4 == 7))
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            TonalityOption[i] = 0;
                        }
                        TonalityOption[ProbSecondMax] = 3;
                    }
                    else if ((delta5 == -5 && delta6 == -7) || (delta5 == -7 && delta6 == -5) || (delta5 == 5 && delta6 == -5) || (delta5 == -5 && delta6 == 5) || (delta5 == 7 && delta6 == 5) || (delta5 == 5 && delta6 == 7))
                    {
                        for (int i = 0; i < 12; i++)
                        {
                            TonalityOption[i] = 0;
                        }
                        TonalityOption[ProbThirdMax] = 3;
                    }
                }
            }
            return;
        }
        public string GetTonalityOptionAsString()
        {
            if (IsAtonal())
            {
                return ProgramTexts.GetProgramText("atonal");
            }
            else if (IsSure())
            {
                for (int i = 0; i < 12; i++)
                {
                    if (TonalityOption[i] == 3)
                    {
                        return Constants.Tonality_Type(i);
                    }
                }
                return ProgramTexts.GetProgramText("atonal");
            }
            else
            {
                string strbuf = "";
                int count = 0;
                for (int i = 0; i < 12; i++)
                {
                    if (TonalityOption[i] == 2)
                    {
                        if (count > 0)
                        {
                            strbuf += "/";
                        }
                        count++;
                        strbuf += Constants.Tonality_Type(i);
                    }
                }
                count = 0;
                for (int i = 0; i < 12; i++)
                {
                    if (TonalityOption[i] == 1)
                    {
                        if (count == 0)
                        {
                            strbuf += "(";
                        }
                        else
                        {
                            strbuf += "/";
                        }
                        count++;
                        strbuf += Constants.Tonality_Type(i);
                    }
                }
                if (count > 0)
                {
                    strbuf += ")";
                }
                return strbuf;
            }
        }
    }

    public class TRACK
    {
        public TRACK() { }
        public TRACK(TRACK OriTrack)
        {
            TrackNum = OriTrack.TrackNum;
            TrackName = OriTrack.TrackName;
            NoteNumTotal = OriTrack.NoteNumTotal;
            BarNumTotal = OriTrack.BarNumTotal;
            PassageNumTotal = OriTrack.PassageNumTotal;
            TrackEmptiness = OriTrack.TrackEmptiness;
            IsTonalized = OriTrack.IsTonalized;
            NoteList = new NOTE[NoteNumTotal];
            for (int i = 0; i < NoteNumTotal; i++)
            {
                NoteList[i] = new NOTE(OriTrack.NoteList[i]);
            }
            BarList = new BAR[BarNumTotal];
            for (int i = 0; i < BarNumTotal; i++)
            {
                BarList[i] = new BAR(OriTrack.BarList[i]);
            }
            PassageList = new PASSAGE[PassageNumTotal];
            for (int i = 0; i < PassageNumTotal; i++)
            {
                PassageList[i] = new PASSAGE(OriTrack.PassageList[i]);
            }
            ChildHarmoTrackNum = OriTrack.ChildHarmoTrackNum;
        }
        public int TrackNum;
        public string TrackName;
        public int NoteNumTotal;
        public int BarNumTotal;
        public int PassageNumTotal;
        public bool TrackEmptiness;
        public bool IsTonalized;
        public NOTE[] NoteList;
        public BAR[] BarList;
        public PASSAGE[] PassageList;
        public int[] ChildHarmoTrackNum = new int[7]; //-1表示无
        public void CombinePassages()
        {
            while (PassageList[0].PassageIsEmpty(this))
            {
                DeletePassageFromPassageList(0);
                PassageList[0].FirstBarNum = 0;
            }
            for (int i = 1; i < PassageNumTotal; i++)
            {
                if (PassageList[i].PassageIsEmpty(this))
                {
                    PassageList[i - 1].LastBarNum = PassageList[i].LastBarNum;
                    DeletePassageFromPassageList(i);
                    i--;
                }
            }
            for (int i = 0; i < PassageNumTotal - 1; i++)
            {
                if (PassageList[i].Tonality == PassageList[i + 1].Tonality)
                {
                    PassageList[i].LastBarNum = PassageList[i + 1].LastBarNum;
                    DeletePassageFromPassageList(i + 1);
                }
            }
        }
        public void PreCombinePassages()
        {
            for (int i = 0; i < PassageNumTotal - 1; i++)
            {
                if (PassageList[i].GetTonalityOptionAsString() == PassageList[i + 1].GetTonalityOptionAsString())
                {
                    PassageList[i].LastBarNum = PassageList[i + 1].LastBarNum;
                    DeletePassageFromPassageList(i + 1);
                }
            }
        }
        public void DeletePassageFromPassageList(int PassageNum)
        {
            for (int i = PassageNum; i < PassageNumTotal - 1; i++)
            {
                PassageList[i] = PassageList[i + 1];
                PassageList[i].PassageNum--;
            }
            PassageNumTotal--;
        }
        public string GetTonalityAsString()
        {
            if (!IsTonalized)
            {
                return ProgramTexts.GetProgramText("tonality_notset");
            }
            else
            {
                string tmp = "";
                for (int i = 0; i < PassageNumTotal; i++)
                {
                    if (i != 0)
                    {
                        tmp += " - ";
                    }
                    tmp += Constants.Tonality_Type(PassageList[i].Tonality);
                }
                return tmp;
            }
        }
        public bool AutoTonalize1()
        {
            string OptionsGiven = "";
            bool AllTonalized = true;
            for (int PassageNum = 0; PassageNum < PassageNumTotal; PassageNum++)
            {
                PassageList[PassageNum].CalculateTonalityOptions(this);
                //给出分析结果，提供选项
                if (PassageList[PassageNum].IsSure())
                {
                    for (int i = 0; i < 12; i++)
                    {
                        if (PassageList[PassageNum].TonalityOption[i] == 3)
                        {
                            PassageList[PassageNum].Tonality = i;
                            OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" +ProgramTexts.GetProgramText("bar")+ PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）"+ProgramTexts.GetProgramText("tonalization_success") + Constants.Tonality_Type(PassageList[PassageNum].Tonality) + "。\r\n";
                        }
                    }
                }
                else if (PassageList[PassageNum].IsAtonal())
                {
                    AllTonalized = false;
                    OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）"+ProgramTexts.GetProgramText("tonalization_failure1") +"\r\n";
                }
                else
                {
                    AllTonalized = false;
                    OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）" + ProgramTexts.GetProgramText("tonalization_failure2") + PassageList[PassageNum].GetTonalityOptionAsString() + "\r\n";
                }
            }
            MessageBox.Show(OptionsGiven.Remove(OptionsGiven.Length - 2), ProgramTexts.GetProgramText("tonalization_analysis"));
            return AllTonalized;
        }
        public bool AutoTonalize2()
        {
            string OptionsGiven = "";
            //扫描小节列表，匹配乐段
            int pBarNum = -1;
            PassageList = new PASSAGE[BarNumTotal];
            PassageNumTotal = 0;
            for (int i = 0; i < BarNumTotal; i++)
            {
                PassageList[i] = new PASSAGE();
                PassageList[i].PassageNum = i;
                PassageList[i].ParentTrackNum = TrackNum;
                PassageNumTotal = PassageNumTotal + 1;
                pBarNum++;
                PassageList[i].FirstBarNum = pBarNum;
                if (pBarNum > 0 && !BarList[pBarNum - 1].BarValidity)
                {
                    PassageList[i].FirstBarNum--;
                    PassageList[i - 1].LastBarNum--;
                    pBarNum--;
                }
                if (pBarNum + 4 >= BarNumTotal)
                {
                    PassageList[i].LastBarNum = BarNumTotal - 1;
                    PassageList[i].CalculateTonalityOptions(this);
                    break;
                }
                while (BarList[pBarNum].BarEmptiness || (!BarList[pBarNum].BarValidity))
                {
                    pBarNum++;
                }
                if (pBarNum + 3 >= BarNumTotal)
                {
                    MessageBox.Show(ProgramTexts.GetProgramText("tonalization_shorttrack"), ProgramTexts.GetProgramText("tonalization_analysis"));
                    return false;
                }
                pBarNum += 3;
                PassageList[i].LastBarNum = pBarNum;
                while (pBarNum < BarNumTotal - 1)
                {
                    pBarNum++;
                    PassageList[i].CalculateTonalityOptions(this);
                    bool IsAdapted = BarList[pBarNum].AdaptWithPassage(this, PassageList[i]);
                    if (IsAdapted)
                    {
                        PassageList[i].LastBarNum++;
                    }
                    else
                    {
                        pBarNum--;
                        break;
                    }
                }
                if (pBarNum == BarNumTotal - 1)
                {
                    break;
                }
            }
            //合并具有相同调性选项的乐段
            PreCombinePassages();
            //给出分析结果，提供选项
            bool AllTonalized = true;
            for (int PassageNum = 0; PassageNum < PassageNumTotal; PassageNum++)
            {
                if (PassageList[PassageNum].IsSure())
                {
                    for (int i = 0; i < 12; i++)
                    {
                        if (PassageList[PassageNum].TonalityOption[i] == 3)
                        {
                            PassageList[PassageNum].Tonality = i;
                            OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）" + ProgramTexts.GetProgramText("tonalization_success") + Constants.Tonality_Type(PassageList[PassageNum].Tonality) + "。\r\n";
                        }
                    }
                }
                else if (PassageList[PassageNum].IsAtonal())
                {
                    AllTonalized = false;
                    OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）" + ProgramTexts.GetProgramText("tonalization_failure1") + "\r\n";
                }
                else
                {
                    AllTonalized = false;
                    OptionsGiven += ProgramTexts.GetProgramText("passage") + PassageNum + "（" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].FirstBarNum + "~" + ProgramTexts.GetProgramText("bar") + PassageList[PassageNum].LastBarNum + "）" + ProgramTexts.GetProgramText("tonalization_failure2") + PassageList[PassageNum].GetTonalityOptionAsString() + "\r\n";
                }
            }
            MessageBox.Show(OptionsGiven.Remove(OptionsGiven.Length - 2), ProgramTexts.GetProgramText("tonalization_analysis"));
            return AllTonalized;
        }
        public bool IsHarmonized()
        {
            bool tmp = false;
            for (int i = 0; i < 7; i++)
            {
                if (ChildHarmoTrackNum[i] != -1)
                {
                    tmp = true;
                }
            }
            return tmp;
        }
        public string TrackIDforCeVIO;
    }
    public class HARMOTRACK : TRACK
    {
        public int ParentTrackNum;
        public int HarmonicType;
        public bool IsSaved = false;
        public HARMOTRACK(HARMOTRACK OriTrack)
        {
            TrackNum = OriTrack.TrackNum;
            TrackName = OriTrack.TrackName;
            NoteNumTotal = OriTrack.NoteNumTotal;
            BarNumTotal = OriTrack.BarNumTotal;
            PassageNumTotal = OriTrack.PassageNumTotal;
            TrackEmptiness = OriTrack.TrackEmptiness;
            ParentTrackNum = OriTrack.ParentTrackNum;
            HarmonicType = OriTrack.HarmonicType;
            IsTonalized = OriTrack.IsTonalized;
            NoteList = new NOTE[NoteNumTotal];
            for (int i = 0; i < NoteNumTotal; i++)
            {
                NoteList[i] = new NOTE(OriTrack.NoteList[i]);
            }
            BarList = new BAR[BarNumTotal];
            for (int i = 0; i < BarNumTotal; i++)
            {
                BarList[i] = new BAR(OriTrack.BarList[i]);
            }
            PassageList = new PASSAGE[PassageNumTotal];
            for (int i = 0; i < PassageNumTotal; i++)
            {
                PassageList[i] = new PASSAGE(OriTrack.PassageList[i]);
            }
            TrackIDforCeVIO = OriTrack.TrackIDforCeVIO;
        }
        public HARMOTRACK(int HarmoNum, TRACK ParentTrack, int ParentTrackNum, int _HarmonyType)
        {
            TrackNum = HarmoNum;
            TrackName = ParentTrack.TrackName + " " + Constants.Harmonic_Type[_HarmonyType];
            NoteNumTotal = ParentTrack.NoteNumTotal;
            BarNumTotal = ParentTrack.BarNumTotal;
            PassageNumTotal = ParentTrack.PassageNumTotal;
            TrackEmptiness = ParentTrack.TrackEmptiness;
            this.ParentTrackNum = ParentTrackNum;
            HarmonicType = _HarmonyType;
            NoteList = new NOTE[NoteNumTotal];
            for (int i = 0; i < NoteNumTotal; i++)
            {
                NoteList[i] = new NOTE(ParentTrack.NoteList[i]);
            }
            BarList = new BAR[BarNumTotal];
            for (int i = 0; i < BarNumTotal; i++)
            {
                BarList[i] = new BAR(ParentTrack.BarList[i]);
            }
            PassageList = new PASSAGE[PassageNumTotal];
            for (int i = 0; i < PassageNumTotal; i++)
            {
                PassageList[i] = new PASSAGE(ParentTrack.PassageList[i]);
            }
            ShiftKey();
            TrackIDforCeVIO = ParentTrack.TrackIDforCeVIO;
        }
        public void ShiftKey()
        {
            switch (HarmonicType)
            {
                case 0:
                    break;
                case 1:
                    for (int i = 0; i < PassageNumTotal; i++)
                    {
                        if (PassageList[i].Tonality == 12)
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                NoteList[j].NoteValidity = false;
                            }
                        }
                        else
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                int sol_fa_syl = NoteList[j].NoteKey % 12 - PassageList[i].Tonality;
                                if (sol_fa_syl < 0)
                                {
                                    sol_fa_syl += 12;
                                }
                                NoteList[j].NoteKey = NoteList[j].NoteKey + Constants.thirdup_keyshift[sol_fa_syl];
                            }
                        }
                    }
                    break;
                case 2:
                    for (int i = 0; i < PassageNumTotal; i++)
                    {
                        if (PassageList[i].Tonality == 12)
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                NoteList[j].NoteValidity = false;
                            }
                        }
                        else
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                int sol_fa_syl = NoteList[j].NoteKey % 12 - PassageList[i].Tonality;
                                if (sol_fa_syl < 0)
                                {
                                    sol_fa_syl += 12;
                                }
                                NoteList[j].NoteKey = NoteList[j].NoteKey + Constants.thirddown_keyshift[sol_fa_syl];
                            }
                        }
                    }
                    break;
                case 3:
                    for (int i = 0; i < PassageNumTotal; i++)
                    {
                        if (PassageList[i].Tonality == 12)
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                NoteList[j].NoteValidity = false;
                            }
                        }
                        else
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                int sol_fa_syl = NoteList[j].NoteKey % 12 - PassageList[i].Tonality;
                                if (sol_fa_syl < 0)
                                {
                                    sol_fa_syl += 12;
                                }
                                NoteList[j].NoteKey = NoteList[j].NoteKey + Constants.thirddown_keyshift[sol_fa_syl] + 12;
                            }
                        }
                    }
                    break;
                case 4:
                    for (int i = 0; i < PassageNumTotal; i++)
                    {
                        if (PassageList[i].Tonality == 12)
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                NoteList[j].NoteValidity = false;
                            }
                        }
                        else
                        {
                            for (int j = PassageList[i].GetFirstNoteNum(this); j <= PassageList[i].GetLastNoteNum(this); j++)
                            {
                                int sol_fa_syl = NoteList[j].NoteKey % 12 - PassageList[i].Tonality;
                                if (sol_fa_syl < 0)
                                {
                                    sol_fa_syl += 12;
                                }
                                NoteList[j].NoteKey = NoteList[j].NoteKey + Constants.thirdup_keyshift[sol_fa_syl] - 12;
                            }
                        }
                    }
                    break;
                case 5:
                    for (int i = 0; i < NoteNumTotal; i++)
                    {
                        NoteList[i].NoteKey += 12;
                    }
                    break;
                case 6:
                    for (int i = 0; i < NoteNumTotal; i++)
                    {
                        NoteList[i].NoteKey -= 12;
                    }
                    break;
                default:
                    break;
            }
            for (int i = 0; i < NoteNumTotal; i++)
            {
                if (NoteList[i].NoteKey < 0 || NoteList[i].NoteKey > 127)
                {
                    throw new Exception("NoteKey goes over the limit.");
                }
            }
        }
    }
}
