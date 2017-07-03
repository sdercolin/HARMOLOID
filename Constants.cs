using System;
using System.Collections.Generic;
using System.Text;

namespace HARMOLOID_Csharp
{
    class MyException : Exception
    {
        public MyException()
        {
        }
    }

    class Constants
    {
        static public double VERSION = 1.3;
        static public int HARMONY_TYPE_MAX = 7;
        static public int UST_BAR_TIME = 1920;
        //算法使用的常数值及数组
        static public double VALID_LENGTH_PERCENT_THRESHOLD = 0.25; //判定小节为有效的音符时长占总时长比例的阈值
        static public double MAXPROB_VALID_THRESHOLD = 0.1;//判定概率最大的调性有效的概率阈值
        static public double PROB_SIMILAR_THRESHOLD = 0.03;//判定几个调性的概率相近的概率差阈值
        static public double UNCERTAIN_THRESHOLD = 3;//判定分析结果是否有效的不确定度阈值
        static public double ADAPTING_THRESHOLD = 0.5;//判定小节是否适配乐段的概率阈值
        static public string[] Harmonic_Type = { "0", "3rd", "-3rd", "6th", "-6th", "8th", "-8th" };//和声类型的int型和字符串型表示的转换
        static public string Harmonic_Type_inWords(int i)
        {
            switch (i)
            {
                case 0:
                    return ProgramTexts.GetProgramText("chorus0");
                case 1:
                    return ProgramTexts.GetProgramText("chorus+3");
                case 2:
                    return ProgramTexts.GetProgramText("chorus-3");
                case 3:
                    return ProgramTexts.GetProgramText("chorus+6");
                case 4:
                    return ProgramTexts.GetProgramText("chorus-6");
                case 5:
                    return ProgramTexts.GetProgramText("chorus+8");
                case 6:
                    return ProgramTexts.GetProgramText("chorus-8");
                default:
                    return "";
            }
        }
            //= { "零度和声", "上三度和声", "下三度和声", "上六度和声", "下六度和声", "上八度和声", "下八度和声" };//中文写法
        static public string[] Tonality_Type_list = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};//调号或音名的int型和字符串型表示的转换
        static public string Tonality_Type(int i)
        {
            if(i>=0 && i<=13)
            {
                if(i==12)
                {
                    return ProgramTexts.GetProgramText("atonal");
                }
                if(i==13)
                {
                    return ProgramTexts.GetProgramText("foranalysis");
                }
                return Tonality_Type_list[i];
            }
            else
            {
                return "";
            }
        }
        static public string[] Tonality_Type2_list = { "B#", "Db", "D", "D#", "Fb", "E#", "Gb", "G", "Ab", "A", "A#", "Cb" };//调号或音名的int型和字符串型表示的转换
        static public string Tonality_Type2(int i)
        {
            if (i >= 0 && i <= 13)
            {
                if (i == 12)
                {
                    return ProgramTexts.GetProgramText("atonal");
                }
                if (i == 13)
                {
                    return ProgramTexts.GetProgramText("foranalysis");
                }
                return Tonality_Type2_list[i];
            }
            else
            {
                return "";
            }
        }
        static public int[] thirdup_keyshift = { 4, 3, 5, 4, 3, 4, 3, 5, 4, 3, 4, 3 }; //上三度和声的计算参数
        static public int[] thirddown_keyshift = { -5, -2, -3, -3, -4, -3, -4, -3, -4, -4, -3, -4 };//下三度和声的计算参数，0~11分别代表do, do# ...
        static public double[,] Tonality_KeyName_Prob =
        { {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1},
          {1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0},
          {0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
          {1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0},
          {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},
          {1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0},
          {0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1},
          {1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
          {1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0},
          {0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1},
          {1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0},
          {0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1}
        };//调性内音名有效与否的判定

        static public int ConvertTonalityType(string TonalityType)
        {
            for (int i = 0; i < 13; i++)
            {
                if (TonalityType == Tonality_Type(i))
                {
                    return i;
                }
            }
            for (int i = 0; i < 13; i++)
            {
                if (TonalityType == Tonality_Type2(i))
                {
                    return i;
                }
            }
            return 13;
        }//实现调号/音名的字符串型→int型的转换

        static public int SortArrayByGreatness(double[] data, int greatness)
        {
            double[] datacopy = new double[12];
            for (int i = 0; i < 12; i++)
            {
                datacopy[i] = data[i];
            }
            int[] order = new int[12];
            for (int i = 0; i < 12; i++)
            {
                order[i] = i;
            }
            double[] databuf = new double[12];
            int[] orderbuf = new int[12];
            for (int i = 0; i < greatness; i++)
            {
                int numbuf = i;
                for (int j = i; j < 12; j++)
                {
                    if (datacopy[j] > datacopy[numbuf])
                    {
                        numbuf = j;
                    }
                }
                databuf[i] = datacopy[numbuf];
                orderbuf[i] = order[numbuf];
                for (int j = 0; j < numbuf - i; j++)
                {
                    databuf[i + j + 1] = datacopy[i + j];
                    orderbuf[i + j + 1] = order[i + j];
                }
                for (int j = 0; j <= numbuf - i; j++)
                {
                    datacopy[i + j] = databuf[i + j];
                    order[i + j] = orderbuf[i + j];
                }
            }
            return order[greatness - 1];
        }//查找一个double型数组里第n位大的数据在数组中的序号
    }

    class ProgramTexts
    {
        static string Language = "zh";
        static Dictionary<string, string> zh = new Dictionary<string, string>()
        {
            { "about","关于HARMOLOID"},
            { "about_text","HARMOLOID "+Constants.VERSION+"\r\nsdercolin.com/akatsuki/harmoloid\r\n\r\nlogo设计：断面\r\n科林/sdercolin © 2015-2016 All Rights Reserved." },
            { "loading_success","载入成功。" },
            { "loading_failure","载入失败，请检查文件格式。" },
            { "load", "载入" },
            { "saving_removeparameters","音轨及参数过多时有可能导致工程文件难以打开。" + Environment.NewLine + "是否要保留和声轨的参数？" },
            { "saveas","另存为"},
            { "save","保存"},
            { "saving_success","保存成功。"},
            { "saving_failure","保存失败。"},
            { "saving_ust1","保存UST时，请勿覆盖原文件。"},
            { "atonal", "无调性" },
            { "tonality_notset", "未标记" },
            { "passage", "乐段" },
            { "bar", "小节" },
            { "track", "音轨" },
            { "tonalization_success","分析成功，调性为：" },
            { "tonalization_failure1","分析失败，请自行填写调性，或者选择“无调”忽略该乐段。" },
            { "tonalization_failure2","分析失败，建议您从以下选项中选择调性：" },
            { "tonalization_analysis" , "调性分析"},
            { "tonalization_shorttrack", "音轨过短，无法进行自动分析" },
            { "file", "文件"},
            { "help", "帮助" },
            { "userguide", "用户手册" },
            { "getupdates", "获取更新" },
            { "summitbugs", "提交错误" },
            { "fileinfo", "文件信息"},
            { "filenotloaded", "文件未载入。"},
            { "choosetrack", "选择音轨"},
            { "trackinfo", "音轨信息"},
            { "choosetrack_text", "请选择音轨。"},
            { "tonalization", "调性标记"},
            { "harmolization", "和声生成"},
            { "reload", "文件已经载入，是否载入新文件？"},
            { "format_text", "文件格式：" },
            { "filepath_text", "文件路径：" },
            { "filename_text", "文件名：" },
            { "projectname_text", "工程名： " },
            { "trackno_text", "音轨编号： " },
            { "trackname_text", "音轨名： " },
            { "tonalizationresult_text", "调性标记结果： " },
            { "existingchorus_text", "已生成的和声种类： " },
            { "notetotal_text", "音符总数： " },
            { "bartotal_text", "小节总数： " },
            { "emptytrack_text", "该音轨为空，无法进行调性标记。" },
            { "deletechorus-and-tonalize", "该音轨已含有生成的和声轨，是否清空所有和声轨并重新标记调性？" },
            { "choosetrack_text2", "请在左侧的音轨列表中选择音轨。"},
            { "do-tonalization-first","该音轨尚未完成调性标记，无法生成和声。" },
            { "cannot-save-ust1","尚未有和声轨生成，无法保存为UST。"},
            { "tonality_text","调性：" },
            { "trackname", "音轨名" },
            { "trackbeingprocessed_text", "音轨：" },
            { "tonality","调性" },
            { "chorustypes_text","和声种类：" },
            { "chorus0","零度和声" },
            { "chorus+3","上三度和声" },
            { "chorus-3","下三度和声" },
            { "chorus+6","上六度和声" },
            { "chorus-6","下六度和声" },
            { "chorus+8","上八度和声" },
            { "chorus-8","下八度和声" },
            { "confirm","确定" },
            { "chorusgenerated_text","轨已生成。" },
            { "chorusdeleted_text","轨已删除。" },
            { "passagelist_text","乐段列表：" },
            { "passageno", "乐段编号" },
            { "barno", "小节数" },
            { "barstart", "起始小节数" },
            { "barend", "结束小节数" },
            { "content", "内容" },
            { "passageedit_text", "乐段编辑：" },
            { "status", "状态" },
            { "tonalizationstatus_text", "调性标记状态：" },
            { "reset", "重置" },
            { "autotonalize1", "自动计算调性（按照乐段划分）" },
            { "autotonalize2", "自动计算调性（全自动/慎用）" },
            { "barlist_text","小节列表：" },
            { "foranalysis","待分析" },
            { "inputerror_barend","输入错误。请输入正整数的小节号或“-”以表示“至音轨末尾”。" },
            { "inputerror_passageno","乐段编号输入错误。" },
            { "exittonalization","有至少一个乐段未被标记调性，当前信息将不会被保存。" },
            { "helptonalization","关于“乐段”：由于制作和声的需要，HARMOLOID将会把音轨划分成一个或多个“乐段”，每个乐段内部的乐句需要满足单一调性，即不出现转调。\r\n\r\n　·　若您能够自己确定转调的位置和各部分的调性，请手动设置乐段，这样可以最大程度上地避免误差。\r\n　·　若您能够确定转调的位置，而不能确定各部分的调性，则请手动设置乐段的划分，并将调性选项置于“待分析”，然后按下“自动计算调性（按照乐段划分）”按钮。\r\n　·　若您对乐理完全不了解，且无法确定是否存在转调，请直接按下“自动计算调性（全自动/慎用）”按钮，但是这个功能将可能带来较大的误差，请在后续制作中进行较仔细的调整。\r\n\r\n　　由于不同编辑器的小节显示和音高标识的差异，请以本界面右边的小节列表中的内容为准。" },
            { "selecttrackstosaveust","选择您要保存的和声轨：" },
            { "saveust_text1","若选择“全部保存”，则全部和声轨都将以默认文件名格式保存到原文件的目录下。\r\n" },
            { "cancel","取消" },
            { "saveallust","全部保存" },
        };
        static Dictionary<string, string> jp = new Dictionary<string, string>()
        {
            { "about","HARMOLOIDについて"},
            { "about_text","HARMOLOID "+Constants.VERSION+"\r\nsdercolin.com/akatsuki/harmoloid\r\n\r\nlogoデザイン：断面\r\n科林/sdercolin © 2015-2016 All Rights Reserved." },
            { "loading_success","ファイルをインポートしました。" },
            { "loading_failure","不正なファイルまたは空なファイルです。" },
            { "load", "インポート" },
            { "saving_removeparameters","多数のトラックや大量なパラメーターを含むファイルを開くとき、長い時間がかかる可能性があります。" + Environment.NewLine + "コーラストラックのパラメーターを保留しますか？" },
            { "saveas","名前を付けて保存"},
            { "save","保存"},
            { "saving_success","ファイルを保存した。"},
            { "saving_failure","ファイルの保存は失敗しました。"},
            { "saving_ust1","USTを保存する場合、元のファイルを上書き保存しないでください。"},
            { "atonal", "無調" },
            { "tonality_notset", "未定義" },
            { "passage", "楽段" },
            { "bar", "小節" },
            { "track", "トラック" },
            { "tonalization_success","の解析は成功しました：" },
            { "tonalization_failure1","の解析は失敗しました。調性を自分の判断で定義するか、またはこの楽段を無視するよう「無調」を選択してください。" },
            { "tonalization_failure2","の解析は失敗しました。以下の選択肢を参考にして調性を自分の判断で定義してください。" },
            { "tonalization_analysis" , "調性解析"},
            { "tonalization_shorttrack", "このトラックは短すぎるので、解析はできません。" },
            { "file", "ファイル"},
            { "help", "ヘルプ" },
            { "userguide", "ユーザーマニュアル" },
            { "getupdates", "アップデートを獲得" },
            { "summitbugs", "バグ報告" },
            { "fileinfo", "ファイルの情報"},
            { "filenotloaded", "インポートしたファイルはありません。"},
            { "choosetrack", "トラックを選択"},
            { "trackinfo", "トラックの情報"},
            { "choosetrack_text", "まずトラックを選んでください。"},
            { "tonalization", "調性を定義する"},
            { "harmolization", "コーラスを生成する"},
            { "reload", "ファイルが既にインポートされました。新しいファイルをインポートしますか？"},
            { "format_text", "ファイルのフォーマット：" },
            { "filepath_text", "ファイルのパス：" },
            { "filename_text", "ファイル名：" },
            { "projectname_text", "プロジェクト名： " },
            { "trackno_text", "トラック番号： " },
            { "trackname_text", "トラック名： " },
            { "tonalizationresult_text", "定義した調性：" },
            { "existingchorus_text", "生成したコーラス： " },
            { "notetotal_text", "ノート数： " },
            { "bartotal_text", "小節数： " },
            { "emptytrack_text", "このトラックは空であるため、調性の定義はできません。" },
            { "deletechorus-and-tonalize", "このトラックは既にコーラスを持っています。すべてのコーラスを削除し、新たに調性を定義しますか？" },
            { "choosetrack_text2", "左側のリストでトラックを選んでおいてください。"},
            { "do-tonalization-first","このトラックにはまだ調性が定義されていないため、コーラスを生成することができません。" },
            { "cannot-save-ust1","生成されたコーラスはありませんので、USTとして保存はできません。"},
            { "tonality_text","調性：" },
            { "trackname", "トラック名" },
            { "trackbeingprocessed_text", "トラック：" },
            { "tonality","調性" },
            { "chorustypes_text","コーラスの種類：" },
            { "chorus0","０度ハモリ" },
            { "chorus+3","上３度ハモリ" },
            { "chorus-3","下３度ハモリ" },
            { "chorus+6","上６度ハモリ" },
            { "chorus-6","下６度ハモリ" },
            { "chorus+8","上オクターブハモリ" },
            { "chorus-8","下オクターブハモリ" },
            { "confirm","OK" },
            { "chorusgenerated_text","トラックが生成されました。" },
            { "chorusdeleted_text","トラックが削除されました。" },
            { "passagelist_text","楽段リスト：" },
            { "passageno", "楽段番号" },
            { "barno", "小節番号" },
            { "barstart", "開始小節番号" },
            { "barend", "終了小節番号" },
            { "content", "内容" },
            { "passageedit_text", "楽段設定：" },
            { "status", "状態" },
            { "tonalizationstatus_text", "調性定義状態：" },
            { "reset", "リセット" },
            { "autotonalize1", "調性分析（楽段設定依存）" },
            { "autotonalize2", "調性分析（オートマチック）" },
            { "barlist_text","小節リスト：" },
            { "foranalysis","未分析" },
            { "inputerror_barend","入力エラー。自然数の番号を入力するか、またはこのトラックの末まで選択するよう「-」を入力してください。" },
            { "inputerror_passageno","入力エラー。楽段番号を正しく入力してください。" },
            { "exittonalization","調性が定義されていない楽段は存在します。すべての調性定義の結果は保存されません。" },
            { "helptonalization","「楽段」について：コーラスを生成するには、事前にトラックをいくつか単一調性を持つ「楽段」に分ける必要があります。それぞれの「楽段」に転調がないようお気をつけてください。\r\n\r\n　·　転調の位置と各部分の調性が分かる場合、誤差を抑えるよう、「楽段」の位置と各自の調性を予めご自分で設定してください。\r\n\r\n　·　転調の位置しか分からない場合、「楽段」の開始と終了位置だけをご自分で設定し、調性を「未分析」にしてから、「調性分析（楽段設定依存）」をお使いください。\r\n\r\n　·　転調があるかどうか判断できない場合、「調性分析（オートマチック）」をお使いください。しかしこの場合、大きな誤差が生じる可能性もあります。ご利用の際はご注意ください。\r\n\r\nエディタにより小節番号とキーの表記が異なる場合があるため、右の小節リストに基づいて設定してください。" },
            { "selecttrackstosaveust","保存したいコーラストラックを選択してください：" },
            { "saveust_text1","「すべて」を選択した場合は、すべてのコーラストラックは元のファイルと同じディレクトリに保存されます。\r\n" },
            { "cancel","取り消し" },
            { "saveallust","すべて" },
        };
        static Dictionary<string, string> en = new Dictionary<string, string>()
        {
            { "about","About HARMOLOID"},
            { "about_text","HARMOLOID "+Constants.VERSION+"\r\nsdercolin.com/akatsuki/harmoloid\r\n\r\nlogo design: 断面\r\n科林/sdercolin © 2015-2016 All Rights Reserved." },
            { "loading_success","You have successfully loaded the file." },
            { "loading_failure","The file is not valid or is empty." },
            { "load", "Load" },            
            { "saving_removeparameters","It may take a long time to open a project with too many tracks or too much parameters." + Environment.NewLine + "Do you want to keep the parameters of the chorus tracks?" },
            { "saveas","Save As"},
            { "save","Save"},
            { "saving_success","You have successfully saved the file."},
            { "saving_failure","You failed saving the file."},
            { "saving_ust1","Please do not save over the original file when you are processing a UST."},
            { "atonal", "Atonal" },
            { "tonality_notset", "Not Marked" },
            { "passage", "Passage" },
            { "bar", "Bar" },
            { "track", "Track" },
            { "tonalization_success"," is successfully analyzed. Tonality: " },
            { "tonalization_failure1","is not successfully analyzed. Please mark the tonality by yourself, or choose 'Atonal' to omit this Passage." },
            { "tonalization_failure2","is not successfully analyzed. Please mark the tonality by choosing one of the following: " },
            { "tonalization_analysis" , "Tonality analysis"},
            { "tonalization_shorttrack", "This track is too short for analysis." },
            { "file", "File"},
            { "help", "Help" },
            { "userguide", "User guide" },
            { "getupdates", "Get updates" },
            { "summitbugs", "Summit bugs" },
            { "fileinfo", "File information"},
            { "filenotloaded", "No file has been loaded."},
            { "choosetrack", "Choose Track"},
            { "trackinfo", "Track information"},
            { "choosetrack_text", "Please choose a track first."},
            { "tonalization", "Tonality Marking"},
            { "harmolization", "Chorus Generation"},
            { "reload", "You have already loaded a file. Are you sure to load a new file?"},
            { "format_text", "File format: " },
            { "filepath_text", "File path: " },
            { "filename_text", "Filename: " },
            { "projectname_text", "Project name: " },
            { "trackno_text", "Track number: " },
            { "trackname_text", "Trackname: " },
            { "tonalizationresult_text", "Tonality: " },
            { "existingchorus_text", "Generated chorus: " },
            { "notetotal_text", "Total of notes: " },
            { "bartotal_text", "Total of bars: " },
            { "emptytrack_text", "You cannot mark tonality on an empty track." },
            { "deletechorus-and-tonalize", "There are already chorus tracks for this track. Are you sure to delete all those chorus tracks and mark the tonality again?" },
            { "choosetrack_text2", "Please choose a track from the list in the left."},
            { "do-tonalization-first","You cannot generate chorus for a track without tonality marked." },
            { "cannot-save-ust1","You cannot save a UST without any chorus tracks generated."},
            { "tonality_text","Tonality: " },
            { "trackname", "Trackname" },
            { "trackbeingprocessed_text", "Track: " },
            { "tonality","Tonality" },
            { "chorustypes_text","Type of chorus: " },
            { "chorus0","original" },
            { "chorus+3","3rd harmony" },
            { "chorus-3","-3rd harmony" },
            { "chorus+6","6th harmony" },
            { "chorus-6","-6th harmony" },
            { "chorus+8","8th harmony" },
            { "chorus-8","-8th harmony" },
            { "confirm","OK" },
            { "chorusgenerated_text"," is generated." },
            { "chorusdeleted_text"," is deleted." },
            { "passagelist_text","Passage list: " },
            { "passageno", "Passage No. " },
            { "barno", "Bar" },
            { "barstart", "From Bar" },
            { "barend", "To Bar" },
            { "content", "Contents" },
            { "passageedit_text", "Passage edition" },
            { "status", "status" },
            { "tonalizationstatus_text", "Tonality marking status" },
            { "reset", "Reset" },
            { "autotonalize1", "Tonality analysis (with Passage division)" },
            { "autotonalize2", "Tonality analysis (Automatic)" },
            { "barlist_text","Bar list: " },
            { "foranalysis","For Analysis" },
            { "inputerror_barend","Input error. The bar number should be a natural number. You can also input '-' to set the passage to the end of the track." },
            { "inputerror_passageno","Input error of Passage number." },
            { "exittonalization","Not all Passgaes are marked with tonality, thus the result will not be saved." },
            { "helptonalization","About \"Passage\": Before generating chorus, HARMOLOID needs to devide a track into \"Passages\". In a Passage, there should be only one tonality, that is to say, there should not be any modulation.\r\n\r\n　·　If you know the position of modulation and the tonality of each part, please set them by yourself as this will reach the least error. \r\n　·　If you only know the position of modulation, please devide Passages by yourself and set the tonality to \"For Analysis\", then click \"Tonality analysis (with Passage division)\".\r\n　·　If you know nothing about modulation, please click \"Tonality analysis (Automatic)\". However, please note that the result may not be correct. \r\n\r\nAs the Bar number and key of note may be written differently in other editors, please set the Passage based on the Bar list given in the right side of this window. " },
            { "selecttrackstosaveust","Please select the chorus tracks that you want to save: " },
            { "saveust_text1","If you choose \"All\", all chorus tracks will be saved in the same directory as the original file with default filenames.\r\n" },
            { "cancel","Cancel" },
            { "saveallust","All" },
        };

        static public string GetProgramText(string key)
        {
            switch (Language)
            {
                case "jp":
                    return jp[key];
                case "en":
                    return en[key];
                default:
                    return zh[key];
            }
        }
    }
}
