#include <stdio.h>
#include "MIDIdata.h"
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

//NOTE类
long NOTE::GetNoteKey()
{
	return NoteKey;
}
wstring NOTE::GetNoteKeyAsString()
{
	return Tonality_Type[static_cast <int>(NoteKey%12)] + to_wstring(NoteKey/12);
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

//BAR类
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
//void AdaptWithPassage(PASSAGE nPassage);
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

//PASSAGE类
long PASSAGE::GetPassageNum()
{
	return PassageNum;
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

//TRACK类
TRACK::TRACK()
{
	NoteList = NULL;
	BarList = NULL;
	PassageList = NULL;
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
bool TRACK::CombinePassagesForAuto(long PassageNumber1, long PassageNumber2, bool IsSurelyTonalized)
{
	bool IsCombined;
	if (IsSurelyTonalized)
	{
		if (PassageList[PassageNumber1].GetTonality() == PassageList[PassageNumber2].GetTonality())
		{
			IsCombined = true;
		}
		else
		{
			IsCombined = false;
		}
	}
	else
	{
		if (PassageList[PassageNumber1].GetTonalityOptionAsString() == PassageList[PassageNumber2].GetTonalityOptionAsString())
		{
			IsCombined = true;
		}
		else
		{
			IsCombined = false;
		}
	}
	if (IsCombined)
	{
		PassageList[PassageNumber1].LastBarNum = PassageList[PassageNumber2].LastBarNum;
		for (int i = PassageNumber2; i < PassageNumTotal; i++)
		{
			PassageList[i] = PassageList[i+1];
			PassageList[i].SetPassageNum(i);
		}
		PassageNumTotal--;
	}
	return IsCombined;
}
void TRACK::DeleteNoteList()
{
	delete[] NoteList;
}
void TRACK::DeleteBarList()
{
	delete[] BarList;
}
void TRACK::DeletePassageList()
{
	delete[] PassageList;
}