#include <stdio.h>
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

/*调性分析模块的函数实现。*/

void Tonalization( TRACK* &TrackList, bool* pIsTonalized )
{
	long TrackNum;
	wstring TonalizeCommand = DEFAULT_STR;
	//循环本模块界面
	while( true ) 
	{
		//输出提示文字
		wcout<<endl<<"**************** TONALIZATION ****************"<<endl;
		wcout<<"Determing the tonalities of your tracks."<<endl;
		Tonalization_PrintTrackList( TrackList );
		wcout<<endl<<"Please enter a Track number listed above, or enter \"Q\" to quit Tonalization:";
		//读取命令
		wcin>>TonalizeCommand;
		//判断命令类型，进入分支
		if (TonalizeCommand == L"Q")
		{
			break;
		}
		else if ( !StrIsDigit(TonalizeCommand) )
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		else
		{
			TrackNum = stol(TonalizeCommand);
			if (TrackNum < 0 || TrackNum >= TRACK::TrackNumTotal)
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else if (TrackList[TrackNum].TrackIsEmpty())
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else
			{
				//选择了可用的音轨后执行后续操作
				TonalizeCommand = L"tonalize";
				if (TrackList[TrackNum].TrackIsTonalized())
				{
					while (true)
					{
						//判定是否已经确定调性，并询问是否重新确定调性
						wcout<<endl<<"This Track has already been tonalized."<<endl<<"Do you want to conduct retonalization?"<<endl;
						wcout<<"1. Yes"<<endl<<"2. No"<<endl;
						wcout<<"Please enter \"1\" or \"2\":";
						wcin>>TonalizeCommand;
						if (TonalizeCommand == L"1")
						{
							TrackList[TrackNum].SetIsTonalized(false);
							TrackList[TrackNum].DeletePassageList();
							TonalizeCommand = L"tonalize";
							break;
						}
						else if (TonalizeCommand == L"2")
						{
							TonalizeCommand = L"do_not_tonalize";
							break;
						}
						else
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
					}
				}
				if (TonalizeCommand == L"tonalize")
				{
					//确定执行调性分析后，选择模式
					wstring ModeChooseCommand = DEFAULT_STR;
					while (true)
					{
						wcout<<endl<<"Track "<<TrackNum<<" "<<TrackList[TrackNum].GetTrackName()<<endl;
						wcout<<"1.Automatic Mode"<<endl;
						wcout<<"2.Manual Mode"<<endl;
						wcout<<endl<<"Please enter \"1\" or \"2\" to choose a mode, or enter \"Q\" to quit:";
						wcin>>ModeChooseCommand;
						if (ModeChooseCommand == L"Q")
						{
							break;
						}
						else if (ModeChooseCommand == L"1")
						{
							bool IsSuccessful = AutoTonalize( &TrackList[TrackNum] );
							if (IsSuccessful)
							{
								break;
							}
							else
							{
								if (TrackList[TrackNum].PassageList != NULL)
								{
									TrackList[TrackNum].DeletePassageList();
								}
								continue;
							}
						}
						else if (ModeChooseCommand == L"2")
						{
							bool IsSuccessful = ManuTonalize( &TrackList[TrackNum] );
							if (IsSuccessful)
							{
								break;
							}
							else
							{
								if (TrackList[TrackNum].PassageList != NULL)
								{
									TrackList[TrackNum].DeletePassageList();
								}
								continue;
							}
						}
						else
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
					}
				}
			}
		}
		//判定是否至少有一个音轨已经确定了调性（如有，则开启主界面的Harmonize选项）
		*pIsTonalized = false;
		for (int i = 0; i < TRACK::TrackNumTotal; i++)
		{
			if (TrackList[i].TrackIsTonalized())
			{
				*pIsTonalized = true;
			}
		}
	}
	return;
}//调性分析模块的总函数
void Tonalization_PrintTrackList( TRACK* TrackList )
{
	wcout<<endl<<"Track List"<<endl;
	for( long i=0; i<TRACK::TrackNumTotal; i++)
		{
			if(!TrackList[i].TrackIsEmpty())
			{
				wcout<<i<<". "<<TrackList[i].GetTrackName();
				if (TrackList[i].TrackIsTonalized())
				{
					wcout<<"  Tonalized: ";
					for (int j = 0; j < TrackList[i].GetPassageNumTotal(); j++)
					{
						if (j != 0)
						{
							wcout<<" -- ";
						}
						wcout<<Tonality_Type[TrackList[i].PassageList[j].GetTonality()];
					}
				}
				wcout<<endl;
			}
		}
}//打印可用的音轨信息
bool AutoTonalize( TRACK* pTrack )
{
	//创建乐段列表
	(*pTrack).CreatePassageList((*pTrack).GetBarNumTotal());
	(*pTrack).SetPassageNumTotal(0);
	wstring AutoTonalizeCommand = DEFAULT_STR;
	while (true)
	{
		//询问信息，进一步选择模式
		wcout<<endl<<"Does your track contain transpositions?"<<endl;
		wcout<<"1.Yes"<<endl;
		wcout<<"2.No"<<endl;
		wcout<<"3.I'm not sure."<<endl;
		wcout<<"Please enter \"1\", \"2\" or \"3\": ";
		wcin>>AutoTonalizeCommand;
		//模式分支
		if (AutoTonalizeCommand == L"2")
		{
			//单调性模式
			//初始化乐段，输出提示信息
			PrintHelpforAutoTonalization1();
			(*pTrack).PassageList[0].SetPassageNum(0);
			(*pTrack).PassageList[0].FirstBarNum = 0;
			(*pTrack).PassageList[0].LastBarNum = (*pTrack).GetBarNumTotal() - 1;
			(*pTrack).PassageList[0].ParentTrack = pTrack;
			(*pTrack).SetPassageNumTotal(1);
			//计算调性概率
			(*pTrack).PassageList[0].CalculateTonalityOptions();
			//根据调性的确定度不同，采取不同的策略让用户进行修正
			if ((*pTrack).PassageList[0].IsAtonal())
			{
				while (true)
				{
					AutoTonalizeCommand = DEFAULT_STR;
					wcout<<endl<<"HARMOLOID cannot identify the tonality of this track."<<endl;
					wcout<<"Please enter the tonality by yourself:";
					wcin>>AutoTonalizeCommand;
					if (AutoTonalizeCommand == L"help")
					{
						PrintHelpforAutoTonalization1();
						continue;
					}
					else if (AutoTonalizeCommand == L"Q")
					{
						return false;
					}
					else if (ConvertTonalityType(AutoTonalizeCommand) == 13)
					{
						wcout<<"The option you input is wrong, please try again."<<endl;
						continue;
					}
					else
					{
						(*pTrack).PassageList[0].SetTonality(ConvertTonalityType(AutoTonalizeCommand));
						break;
					}
				}
			}
			else if ((*pTrack).PassageList[0].IsSure())
			{
				(*pTrack).PassageList[0].SetTonality(ConvertTonalityType((*pTrack).PassageList[0].GetTonalityOptionAsString()));
			}
			else
			{
				while (true)
				{
					AutoTonalizeCommand = DEFAULT_STR;
					wcout<<endl<<"HARMOLOID cannot surely determine the tonality of this track."<<endl;
					wcout<<"Tonality possilble: "<<(*pTrack).PassageList[0].GetTonalityOptionAsString()<<endl;
					wcout<<"Please enter the tonality by yourself:";
					wcin>>AutoTonalizeCommand;
					if (AutoTonalizeCommand == L"help")
					{
						PrintHelpforAutoTonalization1();
						continue;
					}
					else if (AutoTonalizeCommand == L"Q")
					{
						return false;
					}
					else if (ConvertTonalityType(AutoTonalizeCommand) == 13)
					{
						wcout<<"The option you input is wrong, please try again."<<endl;
						continue;
					}
					else
					{
						(*pTrack).PassageList[0].SetTonality(ConvertTonalityType(AutoTonalizeCommand));
						break;
					}
				}
			}
		}
		else if (AutoTonalizeCommand == L"3")
		{
			//自动探测模式
			//输出提示信息
			PrintHelpforAutoTonalization2();
			//扫描小节列表，匹配乐段
			long pBarNum = -1;
			for (int i = 0; i < (*pTrack).GetBarNumTotal(); i++)
			{
				(*pTrack).PassageList[i].SetPassageNum(i);
				(*pTrack).PassageList[i].ParentTrack = pTrack;
				(*pTrack).SetPassageNumTotal((*pTrack).GetPassageNumTotal() + 1);
				pBarNum ++;
				(*pTrack).PassageList[i].FirstBarNum = pBarNum;
				if (pBarNum>0 && !(*pTrack).BarList[pBarNum-1].BarIsValid())
				{
					(*pTrack).PassageList[i].FirstBarNum --;
					(*pTrack).PassageList[i-1].LastBarNum --;
					pBarNum --;
				}
				if (pBarNum + 4 >= (*pTrack).GetBarNumTotal())
				{
					(*pTrack).PassageList[i].LastBarNum = (*pTrack).GetBarNumTotal() - 1;
					(*pTrack).PassageList[i].CalculateTonalityOptions();
					break;
				}
				while (!(*pTrack).BarList[pBarNum].BarIsValid())
				{
					pBarNum ++;
				}
				if (pBarNum + 3 >= (*pTrack).GetBarNumTotal())
				{
					wcout<<"Error: This track does not contain sufficient notes for this mode."<<endl;
					wcout<<"Tonalization failed."<<endl;
					system("pause");
					return false;
				}
				pBarNum += 3;
				(*pTrack).PassageList[i].LastBarNum = pBarNum;
				while (pBarNum < (*pTrack).GetBarNumTotal()-1)
				{
					pBarNum++;
					if (pBarNum == 102)
					{
						wcout<<endl;
					}
					(*pTrack).PassageList[i].CalculateTonalityOptions();
					bool IsAdapted = (*pTrack).BarList[pBarNum].AdaptWithPassage((*pTrack).PassageList[i]);
					if (IsAdapted)
					{
						(*pTrack).PassageList[i].LastBarNum ++;
					}
					else
					{
						pBarNum --;
						break;
					}
				}
				if (pBarNum == (*pTrack).GetBarNumTotal()-1)
				{
					break;
				}
			}
			//合并具有相同调性选项的乐段
			(*pTrack).PreCombinePassages();
			//根据调性的确定度不同，采取不同的策略让用户进行修正
			int count = 0;
			for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
			{
				if ((*pTrack).PassageList[i].IsSure())
				{
					(*pTrack).PassageList[i].SetTonality(ConvertTonalityType((*pTrack).PassageList[i].GetTonalityOptionAsString()));
				}
				else
				{
					if (count == 0)
					{
						wcout<<endl<<"Automatic tonality analysis is finished."<<endl;
						wcout<<"Tonality:"<<endl;
						for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
						{
							if (i!=0)
							{
								wcout<<" -- ";
							}
							wcout<<(*pTrack).PassageList[i].GetTonalityOptionAsString();
						}
						wcout<<endl;
						wcout<<"HARMOLOID cannot surely determine the tonality of this track."<<endl;
						wcout<<"Please follow the instructions to enter tonalities for following passages."<<endl<<endl;
						count ++;
					}
					wcout<<"Passage "<<i<<"  Bar "<<(*pTrack).PassageList[i].FirstBarNum<<" - "<<(*pTrack).PassageList[i].LastBarNum<<endl;
					if ((*pTrack).PassageList[i].IsAtonal())
					{
						wcout<<"HARMOLOID cannot identify the tonality of this passage."<<endl;
						wcout<<"Please enter the tonality by yourself:";
					}
					else
					{
						wcout<<"HARMOLOID cannot surely determine the tonality of this passage."<<endl;
						wcout<<"Tonality possilble: "<<(*pTrack).PassageList[i].GetTonalityOptionAsString()<<endl;
						wcout<<"Please enter the tonality by yourself:";
					}
					while (true)
					{
						wcin>>AutoTonalizeCommand;
						if (AutoTonalizeCommand == L"help")
						{
							PrintHelpforAutoTonalization2();
							continue;
						}
						else if (AutoTonalizeCommand == L"Q")
						{
							return false;
						}
						else if (AutoTonalizeCommand != L"?" && AutoTonalizeCommand[0] == L'?' && StrIsDigit(AutoTonalizeCommand.erase(0,1)))
						{
							long BarNumforPrinting = stol(AutoTonalizeCommand);
							wcout<<endl;
							if (BarNumforPrinting >= 0 && BarNumforPrinting < (*pTrack).GetBarNumTotal())
							{
								(*pTrack).BarList[BarNumforPrinting].PrintBar();
								continue;
							}
							else
							{
								wcout<<"Bar "<<BarNumforPrinting<<" is not existing."<<endl;
								continue;
							}
						}
						else if (ConvertTonalityType(AutoTonalizeCommand) == 13)
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
						else
						{
							(*pTrack).PassageList[i].SetTonality(ConvertTonalityType(AutoTonalizeCommand));
							break;
						}
					}
				}
			}
		}
		else if (AutoTonalizeCommand == L"1")
		{
			//多调性模式
			//输出提示信息
			PrintHelpforAutoTonalization3();
			//接受用户输入的参数，确定乐段
			long StartingBarNum = 0;
			long EndingBarNum = 0;
			for (int PassageNum = 0; PassageNum  < (*pTrack).GetBarNumTotal() && EndingBarNum < (*pTrack).GetBarNumTotal()-1; PassageNum ++)
			{
				while (true)
				{
					wcout<<endl<<"Passage "<<PassageNum<<endl;
					wcout<<"Start from Bar: "<<StartingBarNum<<endl;
					(*pTrack).PassageList[PassageNum].FirstBarNum = StartingBarNum;
					wcout<<"End at Bar: ";
					wcin>>AutoTonalizeCommand;
					if (StrIsDigit(AutoTonalizeCommand))
					{
						if (stol(AutoTonalizeCommand) <= StartingBarNum)
						{
							wcout<<"The number you input is invalid, please try again."<<endl;
							continue;
						}
						else if (stol(AutoTonalizeCommand) >= (*pTrack).GetBarNumTotal())
						{
							EndingBarNum = (*pTrack).GetBarNumTotal()-1;
							break;
						}
						else
						{
							EndingBarNum = stol(AutoTonalizeCommand);
							StartingBarNum = EndingBarNum+1;
							break;
						}
					}
					else if (AutoTonalizeCommand == L"Q")
					{
						return false;
					}
					else if (AutoTonalizeCommand == L"end")
					{
						EndingBarNum = (*pTrack).GetBarNumTotal()-1;
						break;
					}
					else if (AutoTonalizeCommand == L"help")
					{
						PrintHelpforManuTonalization();
						continue;
					}
					else if (AutoTonalizeCommand != L"?" && AutoTonalizeCommand[0] == L'?' && StrIsDigit(AutoTonalizeCommand.erase(0,1)))
					{
						long BarNumforPrinting = stol(AutoTonalizeCommand);
						wcout<<endl;
						if (BarNumforPrinting >= 0 && BarNumforPrinting < (*pTrack).GetBarNumTotal())
						{
							(*pTrack).BarList[BarNumforPrinting].PrintBar();
							continue;
						}
						else
						{
							wcout<<"Bar "<<BarNumforPrinting<<" is not existing."<<endl;
							continue;
						}
					}
					else
					{
						wcout<<"The option you input is wrong, please try again."<<endl;
						continue;
					}
				}
				(*pTrack).PassageList[PassageNum].SetPassageNum(PassageNum);
				(*pTrack).PassageList[PassageNum].LastBarNum = EndingBarNum;
				(*pTrack).PassageList[PassageNum].ParentTrack = pTrack;
				(*pTrack).SetPassageNumTotal((*pTrack).GetPassageNumTotal()+1);
			}
			for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
			{
				//按乐段分别计算调性概率
				(*pTrack).PassageList[i].CalculateTonalityOptions();
				//根据调性的确定度不同，采取不同的策略让用户进行修正
				if ((*pTrack).PassageList[i].IsAtonal())
				{
					while (true)
					{
						AutoTonalizeCommand = DEFAULT_STR;
						wcout<<endl<<"HARMOLOID cannot identify the tonality of this track."<<endl;
						wcout<<"Please enter the tonality by yourself:";
						wcin>>AutoTonalizeCommand;
						if (AutoTonalizeCommand == L"help")
						{
							PrintHelpforAutoTonalization3();
							continue;
						}
						else if (AutoTonalizeCommand == L"Q")
						{
							return false;
						}
						else if (ConvertTonalityType(AutoTonalizeCommand) == 13)
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
						else
						{
							(*pTrack).PassageList[i].SetTonality(ConvertTonalityType(AutoTonalizeCommand));
							break;
						}
					}
				}
				else if ((*pTrack).PassageList[i].IsSure())
				{
					(*pTrack).PassageList[i].SetTonality(ConvertTonalityType((*pTrack).PassageList[i].GetTonalityOptionAsString()));
				}
				else
				{
					while (true)
					{
						AutoTonalizeCommand = DEFAULT_STR;
						wcout<<endl<<"HARMOLOID cannot surely determine the tonality of this track."<<endl;
						wcout<<"Tonality possilble: "<<(*pTrack).PassageList[i].GetTonalityOptionAsString()<<endl;
						wcout<<"Please enter the tonality by yourself:";
						wcin>>AutoTonalizeCommand;
						if (AutoTonalizeCommand == L"help")
						{
							PrintHelpforAutoTonalization3();
							continue;
						}
						else if (AutoTonalizeCommand == L"Q")
						{
							return false;
						}
						else if (ConvertTonalityType(AutoTonalizeCommand) == 13)
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
						else
						{
							(*pTrack).PassageList[i].SetTonality(ConvertTonalityType(AutoTonalizeCommand));
							break;
						}
					}
				}
			}
		}
		else
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		//调性确定完成，合并相同调性的乐段
		(*pTrack).CombinePassages();
		//输出最终信息，等待用户确认
		wcout<<endl<<"Tonalization for Track "<<(*pTrack).GetTrackNum()<<" "<<(*pTrack).GetTrackName()<<" is finished."<<endl;
		wcout<<"Tonality:"<<endl;
		for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
		{
			if (i!=0)
			{
				wcout<<" -- ";
			}
			wcout<<Tonality_Type[(*pTrack).PassageList[i].GetTonality()];
		}
		wcout<<endl;
		//询问是否需要查看详细信息
		while (true)
		{
			wstring SeeDetailsCommand = DEFAULT_STR;
			wcout<<"Do you want to see the details?"<<endl;
			wcout<<"1.Yes"<<endl<<"2.No"<<endl;
			wcout<<endl<<"Please enter \"1\" or \"2\":";
			wcin>>SeeDetailsCommand;
			if (SeeDetailsCommand == L"1")
			{
				for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
				{
					wcout<<"Passage "<<i<<"  Bar "<<(*pTrack).PassageList[i].FirstBarNum<<" - "<<(*pTrack).PassageList[i].LastBarNum<<" "<<(*pTrack).PassageList[i].GetTonalityOptionAsString()<<endl;
				}
				break;
			}
			else if (SeeDetailsCommand == L"2")
			{
				break;
			}
			else
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
		}
		//询问是否保存信息
		while (true)
		{
			wstring SaveCommand = DEFAULT_STR;
			wcout<<endl<<endl<<"Do you want to save this result?"<<endl<<"1.Yes"<<endl<<"2.No"<<endl;
			wcout<<"Please enter \"1\" or \"2\":";
			wcin>>SaveCommand;
			if (SaveCommand == L"1")
			{
				(*pTrack).SetIsTonalized( true );
				wcout<<"This track is successfully tonalized."<<endl;
				wcout<<"You are now able to harmonize this track."<<endl;
				system("pause");
				return true;
			}
			else if (SaveCommand == L"2")
			{
				wcout<<"This track is not successfully tonalized."<<endl;
				system("pause");
				return false;
			}
			else
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
		}
	}
}//自动分析模块
bool ManuTonalize( TRACK* pTrack )
{
	//输出提示信息
	PrintHelpforManuTonalization();
	//创建乐段列表
	(*pTrack).CreatePassageList((*pTrack).GetBarNumTotal());
	(*pTrack).SetPassageNumTotal(0);
	//接受用户输入的参数，确定乐段及调性
	long StartingBarNum = 0;
	long EndingBarNum = 0;
	long Tonality = 12;
	wstring ManuTonalizeCommand = DEFAULT_STR;
	for (int PassageNum = 0; PassageNum  < (*pTrack).GetBarNumTotal() && EndingBarNum < (*pTrack).GetBarNumTotal()-1; PassageNum ++)
	{
		while (true)
		{
			wcout<<endl<<"Passage "<<PassageNum<<endl;
			wcout<<"Start from Bar: "<<StartingBarNum<<endl;
			(*pTrack).PassageList[PassageNum].FirstBarNum = StartingBarNum;
			wcout<<"End at Bar: ";
			wcin>>ManuTonalizeCommand;
			if (StrIsDigit(ManuTonalizeCommand))
			{
				if (stol(ManuTonalizeCommand) <= StartingBarNum)
				{
					wcout<<"The number you input is invalid, please try again."<<endl;
					continue;
				}
				else if (stol(ManuTonalizeCommand) >= (*pTrack).GetBarNumTotal())
				{
					EndingBarNum = (*pTrack).GetBarNumTotal()-1;
					break;
				}
				else
				{
					EndingBarNum = stol(ManuTonalizeCommand);
					StartingBarNum = EndingBarNum+1;
					break;
				}
			}
			else if (ManuTonalizeCommand == L"Q")
			{
				return false;
			}
			else if (ManuTonalizeCommand == L"end")
			{
				EndingBarNum = (*pTrack).GetBarNumTotal()-1;
				break;
			}
			else if (ManuTonalizeCommand == L"help")
			{
				PrintHelpforManuTonalization();
				continue;
			}
			else if (ManuTonalizeCommand != L"?" && ManuTonalizeCommand[0] == L'?' && StrIsDigit(ManuTonalizeCommand.erase(0,1)))
			{
				long BarNumforPrinting = stol(ManuTonalizeCommand);
				wcout<<endl;
				if (BarNumforPrinting >= 0 && BarNumforPrinting < (*pTrack).GetBarNumTotal())
				{
					(*pTrack).BarList[BarNumforPrinting].PrintBar();
					continue;
				}
				else
				{
					wcout<<"Bar "<<BarNumforPrinting<<" is not existing."<<endl;
					continue;
				}
			}
			else
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
		}
		while (true)
		{
			wcout<<"Tonality: ";
			wcin>>ManuTonalizeCommand;
			if (ManuTonalizeCommand == L"Q")
			{
				return false;
			}
			else if (ManuTonalizeCommand == L"help")
			{
				PrintHelpforManuTonalization();
				continue;
			}
			else if (ManuTonalizeCommand[0] == L'?' && StrIsDigit(ManuTonalizeCommand.erase(0,1)))
			{
				long BarNumforPrinting = stol(ManuTonalizeCommand.erase(0,1));
				if (BarNumforPrinting >= 0 && BarNumforPrinting < (*pTrack).GetBarNumTotal())
				{
					(*pTrack).BarList[BarNumforPrinting].PrintBar();
					continue;
				}
				else
				{
					wcout<<"Bar "<<BarNumforPrinting<<"is not existing."<<endl;
					continue;
				}
			}
			else if (ConvertTonalityType(ManuTonalizeCommand) == 13)
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else
			{
				Tonality = ConvertTonalityType(ManuTonalizeCommand);
				break;
			}
		}
		(*pTrack).PassageList[PassageNum].SetPassageNum(PassageNum);
		(*pTrack).PassageList[PassageNum].LastBarNum = EndingBarNum;
		(*pTrack).PassageList[PassageNum].SetTonality(Tonality);
		(*pTrack).PassageList[PassageNum].ParentTrack = pTrack;
		(*pTrack).SetPassageNumTotal((*pTrack).GetPassageNumTotal()+1);
	}
	//调性确定完成，合并相同调性的乐段
	(*pTrack).CombinePassages();
	//输出最终信息，等待用户确认
	wcout<<endl<<"Tonalization for Track "<<(*pTrack).GetTrackNum()<<" "<<(*pTrack).GetTrackName()<<" is finished."<<endl;
	wcout<<"Tonality:"<<endl;
	for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
	{
		if (i!=0)
		{
			wcout<<" -- ";
		}
		wcout<<Tonality_Type[(*pTrack).PassageList[i].GetTonality()];
	}
	wcout<<endl;
	//询问是否需要查看详细信息
	while (true)
		{
			wstring SeeDetailsCommand = DEFAULT_STR;
			wcout<<"Do you want to see the details?"<<endl;
			wcout<<"1.Yes"<<endl<<"2.No"<<endl;
			wcout<<endl<<"Please enter \"1\" or \"2\":";
			wcin>>SeeDetailsCommand;
			if (SeeDetailsCommand == L"1")
			{
				for (int i = 0; i < (*pTrack).GetPassageNumTotal(); i++)
				{
					wcout<<"Passage "<<i<<"  Bar "<<(*pTrack).PassageList[i].FirstBarNum<<" - "<<(*pTrack).PassageList[i].LastBarNum<<" "<<(*pTrack).PassageList[i].GetTonalityOptionAsString()<<endl;
				}
				break;
			}
			else if (SeeDetailsCommand == L"2")
			{
				break;
			}
			else
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
		}
	//询问是否保存信息
	while (true)
	{
		wstring SaveCommand = DEFAULT_STR;
		wcout<<endl<<endl<<"Do you want to save this result?"<<endl<<"1.Yes"<<endl<<"2.No"<<endl;
		wcout<<"Please enter \"1\" or \"2\":";
		wcin>>SaveCommand;
		if (SaveCommand == L"1")
		{
			(*pTrack).SetIsTonalized( true );
			wcout<<"This track is successfully tonalized."<<endl;
			wcout<<"You are now able to harmonize this track."<<endl;
			system("pause");
			return true;
		}
		else if (SaveCommand == L"2")
		{
			wcout<<"This track is not successfully tonalized."<<endl;
			system("pause");
			return false;
		}
		else
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
	}
}//手动确定模块
//打印提示文字的函数
void PrintHelpforAutoTonalization1()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Automatic Mode (without transposition) is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID is now going to analyze the tonality of your track."<<endl;
	wcout<<"  If the tonality is not clear, you may be asked to enter the tonality by yourself."<<endl;
	wcout<<"* When you are asked to enter a Tonality, please enter as \"C\",\"Eb\",\"F#\" etc."<<endl;	
	wcout<<"  - HARMOLOID is only applicable to MAJOR scales at present."<<endl;
	wcout<<"* You can also enter \"help\" to read this guide again."<<endl;
	wcout<<"* To quit Tonalization, you can enter \"Q\"."<<endl<<endl;
	return;
}
void PrintHelpforAutoTonalization2()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Automatic Mode (transposition searching) is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID is now going to analyze the tonality of your track."<<endl;
	wcout<<"* HARMOLOID uses \"Passage\" to divide a track into parts with different tonalities."<<endl;
	wcout<<"  - If your track contains transpositions, it will be devided into passages with different tonalities."<<endl;
	wcout<<"  - If the tonality is not clear, you may be asked to enter the tonality by yourself."<<endl;
	wcout<<"* When you are asked to enter a Tonality, please enter as \"C\",\"Eb\",\"F#\" etc."<<endl;
	wcout<<"  - You can also enter \"Atonal\" to set this Passage as an invalid one. It will not be Harmolized."<<endl;
	wcout<<"  - HARMOLOID is only applicable to MAJOR scales at present."<<endl;
	wcout<<"* Due to differences between MIDI editors, you can enter \"?x\" to check the content of Bar x."<<endl;
	wcout<<"* You can also enter \"help\" to read this guide again."<<endl;
	wcout<<"* To quit Tonalization, you can enter \"Q\"."<<endl<<endl;
	return;
}
void PrintHelpforAutoTonalization3()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Automatic Mode (with transposition) is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID uses \"Passage\" to divide a track into parts with different tonalities."<<endl;
	wcout<<"  Please follow the instructions to set passages of this track."<<endl;
	wcout<<"  - HARMOLOID will give a tonalization result for each passage you set."<<endl;
	wcout<<"  - If the tonality is not clear, you may be asked to enter the tonality by yourself."<<endl;
	wcout<<"* Due to differences between MIDI editors, you can enter \"?x\" to check the content of Bar x."<<endl;
	wcout<<"* You can also enter \"help\" to read this guide again."<<endl;
	wcout<<"* When you are asked to enter a Bar number, please enter a positive integer."<<endl;
	wcout<<"  - When you enter a Bar number that is larger than the number of last Bar, it is taken as the last one."<<endl;
	wcout<<"  - You can also enter \"end\", which will be taken as the number of the last Bar."<<endl;
	wcout<<"* When you are asked to enter a Tonality, please enter as \"C\",\"Eb\",\"F#\" etc."<<endl;
	wcout<<"  - You can also enter \"Atonal\" to set this Passage as an invalid one. It will not be Harmolized."<<endl;
	wcout<<"  - HARMOLOID is only applicable to MAJOR scales at present."<<endl;
	wcout<<"* To quit Tonalization, you can enter \"Q\"."<<endl<<endl;
	return;
}
void PrintHelpforManuTonalization()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Manual Mode is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID uses \"Passage\" to divide a track into parts with different tonalities."<<endl;
	wcout<<"  Please follow the instructions to set passages of this track."<<endl;
	wcout<<"* Due to differences between MIDI editors, you can enter \"?x\" to check the content of Bar x."<<endl;
	wcout<<"* You can also enter \"help\" to read this guide again."<<endl;
	wcout<<"* When you are asked to enter a Bar number, please enter a positive integer."<<endl;
	wcout<<"  - When you enter a Bar number that is larger than the number of last Bar, it is taken as the last one."<<endl;
	wcout<<"  - You can also enter \"end\", which will be taken as the number of the last Bar."<<endl;
	wcout<<"* When you are asked to enter a Tonality, please enter as \"C\",\"Eb\",\"F#\" etc."<<endl;
	wcout<<"  - You can also enter \"Atonal\" to set this Passage as an invalid one. It will not be Harmolized."<<endl;
	wcout<<"  - HARMOLOID is only applicable to MAJOR scales at present."<<endl;
	wcout<<"* To quit Tonalization, you can enter \"Q\"."<<endl<<endl;
	return;
}

bool PASSAGE::PassageIsEmpty()
{
	for (int i = FirstBarNum; i <= LastBarNum; i++)
	{
		if (!(*ParentTrack).BarList[i].BarIsEmpty())
		{
			return false;
		}
	}
	return true;
}//判断乐段是否为空
void TRACK::DeletePassageFromPassageList(long PassageNum)
{
	for (int i = PassageNum; i < PassageNumTotal - 1; i++)
	{
		PassageList[i] = PassageList[i + 1];
		PassageList[i].SetPassageNum(PassageList[i].GetPassageNum() - 1);
	}
	PassageNumTotal --;

}//删除乐段
void TRACK::CombinePassages()
{
	bool EmptyPassageDeleted = false;
	while (PassageList[0].PassageIsEmpty())
	{
		DeletePassageFromPassageList(0);
		PassageList[0].FirstBarNum = 0;
		EmptyPassageDeleted = true;
	}
	for (int i = 1; i < PassageNumTotal; i++)
	{
		if (PassageList[i].PassageIsEmpty())
		{
			PassageList[i-1].LastBarNum = PassageList[i].LastBarNum;
			DeletePassageFromPassageList(i);
			EmptyPassageDeleted = true;
			i--;
		}
	}
	if (EmptyPassageDeleted == true)
	{
		wcout<<endl<<"* Empty Passage deleted."<<endl;
	}
	bool PassageCombined = false;
	for (int i = 0; i < PassageNumTotal - 1; i++)
	{
		if (PassageList[i].GetTonality() == PassageList[i+1].GetTonality())
		{
			PassageList[i].LastBarNum = PassageList[i+1].LastBarNum;
			DeletePassageFromPassageList(i+1);
			PassageCombined = true;
		}
	}
	if (PassageCombined == true)
	{
		wcout<<endl<<"* Passages with same tonalities merged."<<endl;
	}
}//合并相同调性的乐段
void TRACK::PreCombinePassages()
{
	for (int i = 0; i < PassageNumTotal - 1; i++)
	{
		if (PassageList[i].GetTonalityOptionAsString() == PassageList[i+1].GetTonalityOptionAsString())
		{
			PassageList[i].LastBarNum = PassageList[i+1].LastBarNum;
			DeletePassageFromPassageList(i+1);
		}
	}
}//合并相同调性选项的乐段
long PASSAGE::GetNoteTimeTotal()
{
	long sum = 0;
	for (int i = GetFirstNoteNum(); i <= GetLastNoteNum(); i++)
	{
		sum += (*ParentTrack).NoteList[i].GetNoteLength();
	}
	return sum;
}//返回乐段中音符总时长
void PASSAGE::CalculateTonalityOptions()
{
	double NoteNameProb[12];
	double Tonality_Prob[12];
	long NoteTimeTotal = GetNoteTimeTotal();
	for (int i = 0; i < 12; i++)
	{
		long sum = 0;
		for (int j = GetFirstNoteNum(); j <= GetLastNoteNum(); j++)
		{
			if ((*ParentTrack).NoteList[j].GetNoteKey() % 12 == i)
			{
				sum += (*ParentTrack).NoteList[j].GetNoteLength();
			}
		}
		NoteNameProb[i] = (static_cast <double>(sum)) / (static_cast <double>(NoteTimeTotal));
	}
	for (int i = 0; i < 12; i++)
	{
		double prob = 0;
		for (int j = 0; j < 12; j++)
		{
			prob += NoteNameProb[j] * Tonality_KeyName_Prob[i][j];
		}
		Tonality_Prob[i] = prob;
	}
	long ProbMaxNum = SortArrayByGreatness(Tonality_Prob, 1);
	for (int i = 0; i < 12; i++)
	{
		TonalityOption[i] = 0;
	}
	if (Tonality_Prob[ProbMaxNum] >= MAXPROB_VALID_THRESHOLD )
	{
		long uncertainty = -1;
		for (int i = 0; i < 12; i++)
		{
			if (Tonality_Prob[ProbMaxNum] == Tonality_Prob[i])
			{
				TonalityOption[i] = 2;
				uncertainty ++;
			}
			else if (Tonality_Prob[ProbMaxNum] - Tonality_Prob[i] <= PROB_SIMILAR_THRESHOLD)
			{
				TonalityOption[i] = 1;
				uncertainty ++;
			}
		}
		if (uncertainty == 0)
		{
			TonalityOption[ProbMaxNum] = 3;
		}
		else if (uncertainty >= UNCERTAIN_THRESHOLD)
		{
			for (int i = 0; i < 12; i++)
			{
				TonalityOption[i] = 0;
			}
		}
		else
		{
			long ProbSecondMax = SortArrayByGreatness(Tonality_Prob, 2);
			long ProbThirdMax = SortArrayByGreatness(Tonality_Prob, 3);
			long delta1 = ProbMaxNum - ProbSecondMax;
			long delta2 = ProbMaxNum - ProbThirdMax;
			long delta3 = ProbSecondMax - ProbMaxNum;
			long delta4 = ProbSecondMax - ProbThirdMax;
			long delta5 = ProbThirdMax - ProbMaxNum;
			long delta6 = ProbThirdMax - ProbSecondMax;
			if ((delta1 == -5 && delta2 == -7)||(delta1 == -7 && delta2 == -5)||(delta1 == 5 && delta2 == -5)||(delta1 == -5 && delta2 == 5)||(delta1 == 7 && delta2 == 5)||(delta1 == 5 && delta2 == 7))
			{
				for (int i = 0; i < 12; i++)
				{
					TonalityOption[i] = 0;
				}
				TonalityOption[ProbMaxNum] = 3;
			}
			else if ((delta3 == -5 && delta4 == -7)||(delta3 == -7 && delta4 == -5)||(delta3 == 5 && delta4 == -5)||(delta3 == -5 && delta4 == 5)||(delta3 == 7 && delta4 == 5)||(delta3 == 5 && delta4 == 7))
			{
				for (int i = 0; i < 12; i++)
				{
					TonalityOption[i] = 0;
				}
				TonalityOption[ProbSecondMax] = 3;
			}
			else if ((delta5 == -5 && delta6 == -7)||(delta5 == -7 && delta6 == -5)||(delta5 == 5 && delta6 == -5)||(delta5 == -5 && delta6 == 5)||(delta5 == 7 && delta6 == 5)||(delta5 == 5 && delta6 == 7))
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
}//计算调性概率的函数
bool BAR::AdaptWithPassage(PASSAGE nPassage)
{
	if (BarIsEmpty())
	{
		return true;
	}
	else if (!BarIsValid())
	{
		return true;
	}
	else if (nPassage.IsAtonal())
	{
		return true;
	}
	else
	{
		double NoteNameProb[12];
		long NoteTimeTotal = GetValidLength();
		for (int i = 0; i < 12; i++)
		{
			long sum = 0;
			for (int j = FirstNoteNum; j <= LastNoteNum; j++)
			{
				if ((*ParentTrack).NoteList[j].GetNoteKey() % 12 == i)
				{
					sum += (*ParentTrack).NoteList[j].GetNoteLength();
				}
			}
			NoteNameProb[i] = (static_cast <double>(sum)) / (static_cast <double>(NoteTimeTotal));
		}
		if (nPassage.IsSure())
		{
			long Tonality = ConvertTonalityType(nPassage.GetTonalityOptionAsString());
			double prob = 0;
			for (int i = 0; i < 12; i++)
			{
				prob += Tonality_KeyName_Prob[Tonality][i]*NoteNameProb[i];
			}
			if (prob >= ADAPTING_THRESHOLD)
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
				if (nPassage.GetTonalityOption(i)>0)
				{
					double prob = 0;
					for (int j = 0; j < 12; j++)
					{
						prob += Tonality_KeyName_Prob[i][j]*NoteNameProb[j];
					}
					if (prob >= ADAPTING_THRESHOLD)
					{
						return true;
					}
				}
			}
			return false;
		}
	}
}//判断小节是否匹配于乐段的函数
