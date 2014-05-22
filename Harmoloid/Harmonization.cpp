#include <stdio.h>
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

void Harmonization( TRACK* &TrackList, TRACK* &HarmoList )
{
	long TrackNum;
	wstring HarmonizeCommand = DEFAULT_STR;
	while( true )
	{
		wcout<<endl<<"**************** HARMONIZATION ****************"<<endl;
		wcout<<"Create harmonies for your tracks."<<endl;
		Harmonization_PrintTrackList( TrackList );
		wcout<<endl<<"Please enter a Track number listed above, or enter \"Q\" to quit Harmonization:";
		wcin>>HarmonizeCommand; 
		if (HarmonizeCommand == L"Q")
		{
			break;
		}
		else if ( !StrIsDigit(HarmonizeCommand) )
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		else
		{
			TrackNum = stol(HarmonizeCommand);
			if (TrackNum < 0 || TrackNum >= TRACK::TrackNumTotal)
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else if (TrackList[TrackNum].TrackIsEmpty() || !TrackList[TrackNum].TrackIsTonalized())
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else
			{
				wstring HarmoTypeChooseCommand = DEFAULT_STR;
				while (true)
				{
					wcout<<endl<<"Track "<<TrackNum<<" "<<TrackList[TrackNum].GetTrackName()<<endl;
					for (int i = 0; i < 7; i++)
					{
						if (TrackList[TrackNum].HarmoTrackNum[i] == -1)
						{
							wcout<<i<<". "<<Harmonic_Type[i]<<endl;
						}
					}
					wcout<<endl<<"Please enter a number listed above to choose the type of harmony you want, or enter \"Q\" to quit:";
					wcin>>HarmoTypeChooseCommand;
					if (HarmoTypeChooseCommand == L"Q")
					{
						break;
					}
					else if (StrIsDigit(HarmoTypeChooseCommand))
					{
						long HarmonyType = stol(HarmoTypeChooseCommand);
						if (HarmonyType < 0 || HarmonyType > 6)
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
						else if (TrackList[TrackNum].HarmoTrackNum[HarmonyType] != -1)
						{
							wcout<<"The option you input is wrong, please try again."<<endl;
							continue;
						}
						else
						{
							HarmoList[TRACK::HarmoNumTotal].CopyFrom(TrackList[TrackNum]);
							bool ShiftKeySuccessful = HarmoList[TRACK::HarmoNumTotal].ShiftKey(HarmonyType);
							if (ShiftKeySuccessful)
							{
								HarmoList[TRACK::HarmoNumTotal].SetTrackNum(TRACK::HarmoNumTotal);
								HarmoList[TRACK::HarmoNumTotal].SetTrackName(TrackList[TrackNum].GetTrackName() + L" " + Harmonic_Type[HarmonyType]);
								HarmoList[TRACK::HarmoNumTotal].SetHarmonic(true);
								HarmoList[TRACK::HarmoNumTotal].SetHarmonicType(HarmonyType);
								HarmoList[TRACK::HarmoNumTotal].SetParentTrackNum(TrackNum);
								TrackList[TrackNum].HarmoTrackNum[HarmonyType] = TRACK::HarmoNumTotal;
								TRACK::HarmoNumTotal ++;
								wcout<<"Harmonization is successful."<<endl;
								wcout<<"A "<<Harmonic_Type[HarmonyType]<<" harmony for Track "<<TrackNum<<" "<<TrackList[TrackNum].GetTrackName()<<" is created."<<endl;
							}
							else
							{
								wcout<<"Error: Key limit exceeded."<<endl;
								wcout<<"Harmonization failed."<<endl;
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
				continue;
			}
		}
	}
	return;
}
void Harmonization_PrintTrackList( TRACK* TrackList )
{
	wcout<<endl<<"Track List"<<endl;
	for( long i=0; i<TRACK::TrackNumTotal; i++)
		{
			if(!TrackList[i].TrackIsEmpty() && TrackList[i].TrackIsTonalized())
			{
				wcout<<i<<". "<<TrackList[i].GetTrackName();
				wcout<<endl;
			}
		}
}
bool TRACK::ShiftKey(long Harmonic_Type)
{
	switch (Harmonic_Type)
	{
	case 0:
		break;
	case 1:
		for (int i = 0; i < PassageNumTotal; i++)
		{
			for (int j = PassageList[i].GetFirstNoteNum(); j <= PassageList[i].GetLastNoteNum(); j++)
			{
				long sol_fa_syl = NoteList[j].GetNoteKey() % 12 - PassageList[i].GetTonality();
				if (sol_fa_syl < 0)
				{
					sol_fa_syl += 12;
				}
				NoteList[j].SetNoteKey(NoteList[j].GetNoteKey() + thirdup_keyshift[sol_fa_syl]);
			}
		}
		break;
	case 2:
		for (int i = 0; i < PassageNumTotal; i++)
		{
			for (int j = PassageList[i].GetFirstNoteNum(); j <= PassageList[i].GetLastNoteNum(); j++)
			{
				long sol_fa_syl = NoteList[j].GetNoteKey() % 12 - PassageList[i].GetTonality();
				if (sol_fa_syl < 0)
				{
					sol_fa_syl += 12;
				}
				NoteList[j].SetNoteKey(NoteList[j].GetNoteKey() + thirddown_keyshift[sol_fa_syl]);
			}
		}
		break;
	case 3:
		for (int i = 0; i < PassageNumTotal; i++)
		{
			for (int j = PassageList[i].GetFirstNoteNum(); j <= PassageList[i].GetLastNoteNum(); j++)
			{
				long sol_fa_syl = NoteList[j].GetNoteKey() % 12 - PassageList[i].GetTonality();
				if (sol_fa_syl < 0)
				{
					sol_fa_syl += 12;
				}				
				NoteList[j].SetNoteKey(NoteList[j].GetNoteKey() + thirddown_keyshift[sol_fa_syl] + 12);
			}
		}
		break;
	case 4:
		for (int i = 0; i < PassageNumTotal; i++)
		{
			for (int j = PassageList[i].GetFirstNoteNum(); j <= PassageList[i].GetLastNoteNum(); j++)
			{
				long sol_fa_syl = NoteList[j].GetNoteKey() % 12 - PassageList[i].GetTonality();
				if (sol_fa_syl < 0)
				{
					sol_fa_syl += 12;
				}				
				NoteList[j].SetNoteKey(NoteList[j].GetNoteKey() + thirdup_keyshift[sol_fa_syl] - 12);
			}
		}
		break;
	case 5:
		for (int i = 0; i < NoteNumTotal; i++)
		{
			NoteList[i].SetNoteKey(NoteList[i].GetNoteKey() + 12);
		}
		break;
	case 6:
		for (int i = 0; i < NoteNumTotal; i++)
		{
			NoteList[i].SetNoteKey(NoteList[i].GetNoteKey() - 12);
		}
		break;
	default:
		break;
	}
	for (int i = 0; i < NoteNumTotal; i++)
	{
		if (NoteList[i].GetNoteKey() < 0 || NoteList[i].GetNoteKey() > 127)
		{
			return false;
		}
	}
	return true;
}
void DeleteHarmoTrack(TRACK* &HarmoList, long HarmoNum)
{
	for (int i = HarmoNum; i < TRACK::HarmoNumTotal - 1; i++)
	{
		HarmoList[i].CopyFrom(HarmoList[i+1]);
		HarmoList[i].SetTrackNum(HarmoList[i].GetTrackNum() - 1);
	}
	HarmoList[TRACK::HarmoNumTotal - 1].DeleteNoteList();
	HarmoList[TRACK::HarmoNumTotal - 1].DeleteBarList();
	HarmoList[TRACK::HarmoNumTotal - 1].DeletePassageList();
	TRACK::HarmoNumTotal --;
}
