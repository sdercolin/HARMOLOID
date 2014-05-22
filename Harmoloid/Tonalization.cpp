#include <stdio.h>
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

void Tonalization( TRACK* &TrackList, bool* pIsTonalized )
{
	long TrackNum;
	wstring TonalizeCommand = DEFAULT_STR;
	while( true ) 
	{
		wcout<<endl<<"**************** TONALIZATION ****************"<<endl;
		wcout<<"Determing the tonalities of your tracks."<<endl;
		Tonalization_PrintTrackList( TrackList );
		wcout<<endl<<"Please enter a Track number listed above, or enter \"Q\" to quit Tonalization:";
		wcin>>TonalizeCommand; 
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
				TonalizeCommand = L"tonalize";
				if (TrackList[TrackNum].TrackIsTonalized())
				{
					while (true)
					{
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
}
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
}
bool AutoTonalize( TRACK* pTrack )
{
	(*pTrack).CreatePassageList((*pTrack).GetBarNumTotal());
	(*pTrack).SetPassageNumTotal(0);
	wstring AutoTonalizeCommand = DEFAULT_STR;
	while (true)
	{
		wcout<<endl<<"Does your track contain transpositions?"<<endl;
		wcout<<"1.Yes"<<endl;
		wcout<<"2.No"<<endl;
		wcout<<"3.I'm not sure."<<endl;
		wcout<<"Please enter \"1\", \"2\" or \"3\": ";
		wcin>>AutoTonalizeCommand;
		if (AutoTonalizeCommand == L"2")
		{
			PrintHelpforAutoTonalization1();
			(*pTrack).PassageList[0].SetPassageNum(0);
			(*pTrack).PassageList[0].FirstBarNum = 0;
			(*pTrack).PassageList[0].LastBarNum = (*pTrack).GetBarNumTotal() - 1;
			(*pTrack).PassageList[0].ParentTrack = pTrack;
			(*pTrack).SetPassageNumTotal(1);
			(*pTrack).PassageList[0].CalculateTonalityOptions();
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
						break;
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
						break;
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
		else if (AutoTonalizeCommand == L"2" ||  AutoTonalizeCommand == L"3")
		{
			continue;
		}
		else
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		if (AutoTonalizeCommand == L"Q")
		{
			return false;
		}
		(*pTrack).CombinePassages();
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
		while (true)
		{
			wstring SaveCommand = DEFAULT_STR;
			wcout<<endl<<endl<<"Do you want to save this result?"<<endl<<"1.Yes"<<endl<<"2.No"<<endl;
			wcout<<"Please enter \"1\" or \"2\":";
			wcin>>SaveCommand;
			if (SaveCommand == L"1")
			{
				(*pTrack).SetIsTonalized( true );
				return true;
			}
			else if (SaveCommand == L"2")
			{
				return false;
			}
			else
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
		}
	}
}
bool ManuTonalize( TRACK* pTrack )
{
	PrintHelpforManuTonalization();
	(*pTrack).CreatePassageList((*pTrack).GetBarNumTotal());
	(*pTrack).SetPassageNumTotal(0);
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
				break;
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
		if (ManuTonalizeCommand == L"Q")
		{
			break;
		}
		while (true)
		{
			wcout<<"Tonality: ";
			wcin>>ManuTonalizeCommand;
			if (ManuTonalizeCommand == L"Q")
			{
				break;
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
		if (ManuTonalizeCommand == L"Q")
		{
			break;
		}
		(*pTrack).PassageList[PassageNum].SetPassageNum(PassageNum);
		(*pTrack).PassageList[PassageNum].LastBarNum = EndingBarNum;
		(*pTrack).PassageList[PassageNum].SetTonality(Tonality);
		(*pTrack).PassageList[PassageNum].ParentTrack = pTrack;
		(*pTrack).SetPassageNumTotal((*pTrack).GetPassageNumTotal()+1);
	}
	if (ManuTonalizeCommand == L"Q")
	{
		return false;
	}
	(*pTrack).CombinePassages();
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
	while (true)
	{
		wstring SaveCommand = DEFAULT_STR;
		wcout<<endl<<endl<<"Do you want to save this result?"<<endl<<"1.Yes"<<endl<<"2.No"<<endl;
		wcout<<"Please enter \"1\" or \"2\":";
		wcin>>SaveCommand;
		if (SaveCommand == L"1")
		{
			(*pTrack).SetIsTonalized( true );
			return true;
		}
		else if (SaveCommand == L"2")
		{
			return false;
		}
		else
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
	}
}
void PrintHelpforAutoTonalization1()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Automatic Mode (without transposition) is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID is now going to analysis the tonality of your track."<<endl;
	wcout<<"  If the tonality is not clear, you may be asked to enter the tonality by yourself."<<endl;
	wcout<<"* When you are asked to enter a Tonality, please enter as \"C\",\"Eb\",\"F#\" etc."<<endl;
	wcout<<"  - You can also enter \"Atonal\" to set this Passage as an invalid one. It will not be Harmolized."<<endl;
	wcout<<"  - HARMOLOID is only applicable to MAJOR scales at present."<<endl;
	wcout<<"* You can also enter \"help\" to read this guide again."<<endl;
	wcout<<"* To quit Tonalization, you can enter \"Q\"."<<endl<<endl;
	return;
}
void PrintHelpforManuTonalization()
{
	wcout<<endl<<"*****************************************************"<<endl;
	wcout<<"* Manual Mode is chosen."<<endl;
	wcout<<endl<<"* HARMOLOID uses \"Passage\" to divide a track into parts with different tonalities."<<endl;
	wcout<<"  Please follow the instructions to set passages of this track."<<endl<<endl;
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
}
void TRACK::DeletePassageFromPassageList(long PassageNum)
{
	for (int i = PassageNum; i < PassageNumTotal - 1; i++)
	{
		PassageList[i] = PassageList[i + 1];
		PassageList[i].SetPassageNum(PassageList[i].GetPassageNum() - 1);
	}
	PassageNumTotal --;

}
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
}
long PASSAGE::GetNoteTimeTotal()
{
	long sum = 0;
	for (int i = GetFirstNoteNum(); i <= GetLastNoteNum(); i++)
	{
		sum += (*ParentTrack).NoteList[i].GetNoteLength();
	}
	return sum;
}
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
}

