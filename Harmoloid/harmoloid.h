#ifndef HARMOLOID_H
#define HARMOLOID_H

#include <stdio.h>
#include "MIDIdata.h"
#include <iostream>
#include <string>
using namespace std;

#define DEFAULT_STR L""
#define HARMONY_TYPE_MAX 7
#define VALID_LENGTH_PERCENT_THRESHOLD 0.25
#define MAXPROB_VALID_THRESHOLD 0.8
#define PROB_SIMILAR_THRESHOLD 0.05
#define UNCERTAIN_THRESHOLD 3

const wstring Harmonic_Type[7] = { L"0", L"3rd", L"-3rd", L"6th", L"-6th", L"8th", L"-8th" };
const wstring Tonality_Type[13] = { L"C", L"C#", L"D", L"Eb", L"E", L"F", L"F#", L"G", L"G#", L"A", L"Bb", L"B", L"Atonal" };
const wstring Tonality_Type2[13] = { L"B#", L"Db", L"D", L"D#", L"Fb", L"E#", L"Gb", L"G", L"Ab", L"A", L"A#", L"Cb", L"Atonal" };
const long thirdup_keyshift[12] = { 4, 3, 5, 4, 3, 4, 3, 5, 4, 3, 4, 3 }; 
const long thirddown_keyshift[12] = { -5, -2, -3, -3, -4, -3, -4, -3, -4, -4, -3, -4};//0~11分别代表do, do# ...
const double Tonality_KeyName_Prob[12][12] = 
{ 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 
  1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0,
  0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1,
  1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0,
  0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1,
  1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0,
  0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1,
  1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1,
  1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0,
  0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1,
  1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0,
  0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1,
};
class PASSAGE;
class TRACK;

class NOTE
{
private:
	long NoteKey;
	long NoteTimeOn;
	long NoteTimeOff;
public:
	long GetNoteKey();
	wstring GetNoteKeyAsString();
	long GetNoteTimeOn();
	long GetNoteTimeOff();
	long GetNoteLength();
	void SetNoteKey(long nNoteKey);
	void SetNoteTimeOn(long nNoteTimeOn);
	void SetNoteTimeOff(long nNoteTimeOff);
};
class BAR
{
private:
	long BarNum;
	long BarTimeOn;
	long BarTimeOff;
	bool Emptiness;
	bool Validity;
public:
	TRACK *ParentTrack;
	long FirstNoteNum;
	long LastNoteNum;
	long GetBarNum();
	long GetBarTimeOn();
	long GetBarTimeOff();
	long GetBarLength();
	bool BarIsEmpty();
	bool BarIsValid();
	void SetBarNum(long nBarNum);
	void SetBarTimeOn(long nBarTimeOn);
	void SetBarTimeOff(long nBarTimeOff);
	long GetValidLength();
	void SetValidity(bool nValidity);
	void SetEmptiness(bool nEmptiness);
	void AdaptWithPassage(PASSAGE nPassage);
	void PrintBar();
};
class PASSAGE
{
private:
	long PassageNum;
	long TonalityOption[12];
	long Tonality;
public:
	TRACK *ParentTrack;
	long FirstBarNum;
	long LastBarNum;
	long GetPassageNum();
	long GetTonality();
	long GetFirstNoteNum();
	long GetLastNoteNum();
	bool PassageIsEmpty();
	void SetPassageNum( long nPassageNum );
	void SetTonality( long nTonality );
	bool IsAtonal();
	bool IsSure();
	long GetNoteTimeTotal();
	void CalculateTonalityOptions();
	wstring GetTonalityOptionAsString();
};
class TRACK
{
private:
	long TrackNum;
	wstring TrackName;
	long NoteNumTotal;
	long BarNumTotal;
	long PassageNumTotal;
	bool Emptiness;
	bool Harmonic;
	long ParentTrackNum;
	wstring HarmonicType;
	bool IsTonalized;
public:
	TRACK();
	~TRACK()
	{
		void DeleteNoteList();
		void DeleteBarList();
		void DeletePassageList();
	}
	static long TrackNumTotal;
	static long HarmoNumTotal;
	NOTE *NoteList;
	BAR *BarList;
	PASSAGE *PassageList;
	long HarmoTrackNum[7];
	void CopyFrom( TRACK OriTrack );
	long GetTrackNum();
	wstring GetTrackName();
	long GetNoteNumTotal();
	long GetBarNumTotal();
	long GetPassageNumTotal();
	bool TrackIsEmpty();
	bool TrackIsHarmonic();
	long GetParentTrackNum();
	wstring GetHarmonicType();
	bool TrackIsTonalized();
	void SetTrackNum(long nTrackNum);
	void SetTrackName(wstring nTrackName);
	void CreateNoteList(long NoteNumMax);
	void CreateBarList(long BarNumMax);
	void CreatePassageList(long PassageNumMax);
	void SetNoteNumTotal(long nNoteNumTotal);
	void SetBarNumTotal(long nBarNumTotal);
	void SetPassageNumTotal(long nPassageNumTotal);
	void SetEmptiness(bool nEmptiness);
	void SetHarmonic(bool nHarmonic);
	void SetParentTrackNum(long nParentTrackNum);
	void SetHarmonicType(long nHarmonicType);
	void SetIsTonalized(bool nIsTonalized);
	void CombinePassages();
	bool CombinePassagesForAuto(long PassageNumber1, long PassageNumber2, bool IsSurelyTonalized);
	bool ShiftKey(long Harmonic_Type);
	void DeleteNoteList();
	void DeleteBarList();
	void DeletePassageList();
	void DeletePassageFromPassageList(long PassageNum);
};
bool StrIsDigit(wstring str);
long ConvertTonalityType(wstring TonalityType);
long SortArrayByGreatness( double data[], long greatness );

wstring ReceiveMainCommand( bool* pIsLoaded, bool* pIsTonalized, wstring* pFilePath, TRACK* TrackList, TRACK* HarmoList );
void PrintTrackList( TRACK* TrackList, TRACK* HarmoList );
void LoadMIDI( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent );
void Renew( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent, bool* pIsTonalized );
void SaveMIDI( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent );
void SaveAsMIDI( TRACK* &TrackList, TRACK* &HarmoList, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent );
void Tonalization( TRACK* &TrackList, bool* pIsTonalized );
void Tonalization_PrintTrackList( TRACK* TrackList );
bool AutoTonalize( TRACK* Track );
bool ManuTonalize( TRACK* Track );
void PrintHelpforAutoTonalization1();
void PrintHelpforManuTonalization();
void Harmonization( TRACK* &TrackList, TRACK* &HarmoList );
void Harmonization_PrintTrackList( TRACK* TrackList );
void DeleteHarmoTrack( TRACK* &HarmoList, long HarmoNum );

#endif