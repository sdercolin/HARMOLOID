#include <stdio.h>
#include "MIDIdata.h"
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

/*类的大部分成员函数实现。*/
/*少数复杂的、功能明确的函数归置在其他几个源文件中。*/
/*本文件中的函数功能在设计说明书中写明*/

//NOTE类实现
long NOTE::GetNoteNum()
{
	return NoteNum;
}
long NOTE::GetNoteKey()
{
	return NoteKey;
}
wstring NOTE::GetNoteKeyAsString()
{
	return Tonality_Type[static_cast <int>(NoteKey%12)] + to_wstring(NoteKey/12 - 1);
}
long NOTE::GetNoteTimeOn()
{
	return NoteTimeOn;
}
long NOTE::GetNoteTimeOff()
{
	return NoteTimeOff;
}
long NOTE::GetNoteLength()
{
	return NoteTimeOff-NoteTimeOn;
}
bool NOTE::NoteIsValid()
{
	return NoteValidity;
}
void NOTE::SetNoteNum(long nNoteNum)
{
	NoteNum=nNoteNum;
}
void NOTE::SetNoteKey(long nNoteKey)
{
	NoteKey=nNoteKey;
}
void NOTE::SetNoteTimeOn(long nNoteTimeOn)
{
	NoteTimeOn=nNoteTimeOn;
}
void NOTE::SetNoteTimeOff(long nNoteTimeOff)
{
	NoteTimeOff=nNoteTimeOff;
}
void NOTE::DeleteNote()
{
	NoteValidity = false;
}

//BAR类实现
long BAR::GetBarNum()
{
	return BarNum;
}
long BAR::GetBarTimeOn()
{
	return BarTimeOn;
}
long BAR::GetBarTimeOff()
{
	return BarTimeOff;
}
long BAR::GetBarLength()
{
	return BarTimeOff-BarTimeOn;
}
bool BAR::BarIsEmpty()
{
	return Emptiness;
}
bool BAR::BarIsValid()
{
	return Validity;
}
void BAR::SetBarNum(long nBarNum)
{
	BarNum=nBarNum;
}
void BAR::SetBarTimeOn(long nBarTimeOn)
{
	BarTimeOn=nBarTimeOn;
}
void BAR::SetBarTimeOff(long nBarTimeOff)
{
	BarTimeOff=nBarTimeOff;
}
long BAR::GetValidLength()
{
	long lenbuf = 0;
	for( int i=FirstNoteNum; i<=LastNoteNum; i++)
	{
		lenbuf += (ParentTrack->NoteList[i]).GetNoteLength();
	}
	return lenbuf;
}
void BAR::SetValidity(bool nValidity)
{
	Validity=nValidity;
}
void BAR::SetEmptiness(bool nEmptiness)
{
	Emptiness=nEmptiness;
}
void BAR::PrintBar()
{
	wcout<<"Bar "<<BarNum<<endl;
	if( Emptiness )
	{
		wcout<<"Empty";
	}
	else
	{
		for( long i=FirstNoteNum, count=0; i<=LastNoteNum; i++)
		{
			if( count%5 == 0 && count != 0 )
			{
				wcout<<endl;
			}
			count++;
			wcout<<(ParentTrack->NoteList[i].GetNoteKeyAsString())<<" ";
		}
	}
	wcout<<endl;
}

//PASSAGE类实现
long PASSAGE::GetPassageNum()
{
	return PassageNum;
}
long PASSAGE::GetTonalityOption(long Tonality)
{
	return TonalityOption[Tonality];
}
long PASSAGE::GetTonality()
{
	return Tonality;
}
long PASSAGE::GetFirstNoteNum()
{
	for (int i = FirstBarNum; i <= LastBarNum; i++)
	{
		if (!(*ParentTrack).BarList[i].BarIsEmpty())
		{
			return (*ParentTrack).BarList[i].FirstNoteNum;
		}
	}
}
long PASSAGE::GetLastNoteNum()
{
	for (int i = LastBarNum; i >= FirstBarNum; i--)
	{
		if (!(*ParentTrack).BarList[i].BarIsEmpty())
		{
			return (*ParentTrack).BarList[i].LastNoteNum;
		}
	}
}
void PASSAGE::SetPassageNum( long nPassageNum )
{
	PassageNum=nPassageNum;
}
void PASSAGE::SetTonality( long nTonality )
{
	Tonality = nTonality;
}
bool PASSAGE::IsAtonal()
{
	for( int i=0; i<12; i++ )
	{
		if( TonalityOption[i] != 0 )
		{
			return false;
		}
	}
	return true;
}
bool PASSAGE::IsSure()
{
	for( int i=0; i<12; i++ )
	{
		if( TonalityOption[i] == 3 )
		{
			return true;
		}
	}
	return false;
}
wstring PASSAGE::GetTonalityOptionAsString()
{
	if(IsAtonal())
	{
		return L"Atonal";
	}
	else if(IsSure())
	{
		for( int i=0; i<12; i++ )
		{
			if( TonalityOption[i] == 3 )
			{
				return Tonality_Type[i];
			}
		}
	}
	else
	{
		wstring strbuf = L"";
		int count = 0;
		for( int i=0; i<12; i++ )
		{
			if( TonalityOption[i] == 2 )
			{
				if(count>0)
				{
					strbuf += L"/";
				}
				count++;
				strbuf += Tonality_Type[i];
			}
		}
		count = 0;
		for( int i=0; i<12; i++ )
		{
			if( TonalityOption[i] == 1 )
			{
				if(count == 0)
				{
					strbuf += L"(";
				}
				else
				{
					strbuf += L"/";
				}
				count++;
				strbuf += Tonality_Type[i];
			}
		}
		if (count > 0)
		{
			strbuf += L")";
		}
		return strbuf;
	}
}

//TRACK类实现
TRACK::TRACK()
{
	NoteList = NULL;
	BarList = NULL;
	PassageList = NULL;
}
TRACK::~TRACK()
	{
		void DeleteNoteList();
		void DeleteBarList();
		void DeletePassageList();
	}
void TRACK::CopyFrom( TRACK OriTrack )
{
	TrackNum = OriTrack.GetTrackNum();
	TrackName = OriTrack.GetTrackName();
	NoteNumTotal = OriTrack.GetNoteNumTotal();
	BarNumTotal = OriTrack.GetBarNumTotal();
	PassageNumTotal = OriTrack.GetPassageNumTotal();
	Emptiness = OriTrack.TrackIsEmpty();
	Harmonic = OriTrack.TrackIsHarmonic();
	ParentTrackNum = OriTrack.GetParentTrackNum();
	HarmonicType = OriTrack.GetHarmonicType();
	if (NoteList != NULL)
	{
		DeleteNoteList();
	}
	NoteList = new NOTE[NoteNumTotal];
	for( long i=0; i<NoteNumTotal; i++ )
	{
		NoteList[i] = OriTrack.NoteList[i];
	}
	if (BarList != NULL)
	{
		DeleteBarList();
	}
	BarList = new BAR[BarNumTotal];
	for( long i=0; i<BarNumTotal; i++ )
	{
		BarList[i] = OriTrack.BarList[i];
	}
	if (PassageList != NULL)
	{
		DeletePassageList();
	}
	PassageList = new PASSAGE[PassageNumTotal];
	for( long i=0; i<PassageNumTotal; i++ )
	{
		PassageList[i] = OriTrack.PassageList[i];
	}
}
long TRACK::GetTrackNum()
{
	return TrackNum;
}
wstring TRACK::GetTrackName()
{
	return TrackName;
}
long TRACK::GetNoteNumTotal()
{
	return NoteNumTotal;
}
long TRACK::GetBarNumTotal()
{
	return BarNumTotal;
}
long TRACK::GetPassageNumTotal()
{
	return PassageNumTotal;
}
bool TRACK::TrackIsEmpty()
{
	return Emptiness;
}
bool TRACK::TrackIsHarmonic()
{
	return Harmonic;
}
long TRACK::GetParentTrackNum()
{
	return ParentTrackNum;
}
wstring TRACK::GetHarmonicType()
{
	return HarmonicType;
}
bool TRACK::TrackIsTonalized()
{
	return IsTonalized;
}
bool TRACK::TrackIsSaved()
{
	return IsSaved;
}
void TRACK::SetTrackNum(long nTrackNum)
{
	TrackNum=nTrackNum;
}
void TRACK::SetTrackName(wstring nTrackName)
{
	TrackName=nTrackName;
}
void TRACK::CreateNoteList(long NoteNumMax)
{
	NoteList=new NOTE[NoteNumMax];
}
void TRACK::CreateBarList(long BarNumMax)
{
	BarList=new BAR[BarNumMax];
}
void TRACK::CreatePassageList(long PassageNumMax)
{
	PassageList=new PASSAGE[PassageNumMax];
}
void TRACK::SetNoteNumTotal(long nNoteNumTotal)
{
	NoteNumTotal=nNoteNumTotal;
}
void TRACK::SetBarNumTotal(long nBarNumTotal)
{
	BarNumTotal=nBarNumTotal;
}
void TRACK::SetPassageNumTotal(long nPassageNumTotal)
{
	PassageNumTotal=nPassageNumTotal;
}
void TRACK::SetEmptiness(bool nEmptiness)
{
	Emptiness=nEmptiness;
}
void TRACK::SetHarmonic(bool nHarmonic)
{
	Harmonic=nHarmonic;
}
void TRACK::SetParentTrackNum(long nParentTrackNum)
{
	ParentTrackNum=nParentTrackNum;
}
void TRACK::SetHarmonicType(long nHarmonicType)
{
	HarmonicType = Harmonic_Type[nHarmonicType];
}
void TRACK::SetIsTonalized(bool nIsTonalized)
{
	IsTonalized = nIsTonalized;
}
void TRACK::SetIsSaved(bool nIsSaved)
{
	IsSaved = nIsSaved;
}
void TRACK::DeleteNoteList()
{
	delete[] NoteList;
	NoteNumTotal = 0;
}
void TRACK::DeleteBarList()
{
	delete[] BarList;
	BarNumTotal = 0;
}
void TRACK::DeletePassageList()
{
	delete[] PassageList;
	PassageNumTotal = 0;
}