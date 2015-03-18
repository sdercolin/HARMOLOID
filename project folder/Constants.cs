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
        static public int HARMONY_TYPE_MAX = 7;
        static public int UST_BAR_TIME = 1920;
        //算法使用的常数值及数组
        static public double VALID_LENGTH_PERCENT_THRESHOLD = 0.25; //判定小节为有效的音符时长占总时长比例的阈值
        static public double MAXPROB_VALID_THRESHOLD = 0.1;//判定概率最大的调性有效的概率阈值
        static public double PROB_SIMILAR_THRESHOLD = 0.03;//判定几个调性的概率相近的概率差阈值
        static public double UNCERTAIN_THRESHOLD = 3;//判定分析结果是否有效的不确定度阈值
        static public double ADAPTING_THRESHOLD = 0.5;//判定小节是否适配乐段的概率阈值
        static public string[] Harmonic_Type = { "0", "3rd", "-3rd", "6th", "-6th", "8th", "-8th" };//和声类型的int型和字符串型表示的转换
        static public string[] Harmonic_Type_inChinese = { "零度和声", "上三度和声", "下三度和声", "上六度和声", "下六度和声", "上八度和声", "下八度和声" };//中文写法
        static public string[] Tonality_Type = { "C", "C#", "D", "Eb", "E", "F", "F#", "G", "G#", "A", "Bb", "B", "无调","待分析" };//调号或音名的int型和字符串型表示的转换
        static public string[] Tonality_Type2 = { "B#", "Db", "D", "D#", "Fb", "E#", "Gb", "G", "Ab", "A", "A#", "Cb", "无调", "待分析" };//调号或音名的int型和字符串型表示的转换
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
		        if (TonalityType == Tonality_Type[i])
		        {
			        return i;
		        }
	        }
	        for (int i = 0; i < 13; i++)
	        {
		        if (TonalityType == Tonality_Type2[i])
		        {
			        return i;
		        }
	        }
	        return 13;
        }//实现调号/音名的字符串型→int型的转换

        static public int SortArrayByGreatness( double[] data, int greatness )
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
			        databuf[i+j+1] = datacopy[i+j];
			        orderbuf[i+j+1] = order[i+j];
		        }
		        for (int j = 0; j <= numbuf - i; j++)
		        {
			        datacopy[i+j] = databuf[i+j];
			        order[i+j] = orderbuf[i+j];
		        }
	        }
	        return order[greatness - 1];
        }//查找一个double型数组里第n位大的数据在数组中的序号
    }
}
