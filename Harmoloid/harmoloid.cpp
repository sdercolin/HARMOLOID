#include <stdio.h>
#include "MIDIdata.h"
#include "harmoloid.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <windows.h>
#include "tinyxml.h"
#include "tinystr.h"
using namespace std;

/*主界面和主要模块函数的实现。*/

//类的静态数据成员初始化
long TRACK::TrackNumTotal = 0;
long TRACK::HarmoNumTotal = 0;
//全局变量
long FileFormat = 0; //1 = .mid; 2 = .ust

void main()
{
	//初始化
	TRACK* TrackList = NULL;
	TRACK* HarmoList = NULL;
	MIDIData* pMIDIData = NULL;
	MIDITrack* pMIDITrack = NULL;
	MIDITrack* npMIDITrack = NULL;
	MIDIEvent* pMIDIEvent = NULL;
	MIDIEvent* npMIDIEvent = NULL;

	bool IsLoaded = false, IsTonalized = false;
	bool* pIsLoaded = &IsLoaded, * pIsTonalized = &IsTonalized;
	wstring FilePath = DEFAULT_STR;
	wstring* pFilePath = &FilePath;
	wstring MainCommand = DEFAULT_STR;
	setlocale(LC_ALL,"jpn");
	//打印程序信息
	wcout<<"HARMOLOID Beta 0.5"<<endl<<"sdercolin (C) 2014"<<endl<<endl;
	//主程序界面循环
	while ( true )
	{
		//接收主控制命令
		MainCommand = ReceiveMainCommand( pIsLoaded, pIsTonalized, pFilePath, TrackList, HarmoList );
		//主选项操作分支
		if( MainCommand == L"1" )
		{
			wstring LoadingCommand = L"load";
			if ( IsLoaded == true )
			{
				while ( true )
				{
					//判定是否已有载入的文件，并询问是否重新载入
					wcout<<"File has already been loaded."<<endl;
					wcout<<"Do you want to load a new file?"<<endl;
					wcout<<"1.Yes"<<endl;
					wcout<<"2.No"<<endl;
					wcin>>LoadingCommand;
					if( LoadingCommand == L"1" )
					{
						Renew( TrackList, HarmoList, pIsLoaded, pFilePath, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent, pIsTonalized );
						LoadingCommand = L"load";
						break;
					}
					else if ( LoadingCommand == L"2" )
					{
						LoadingCommand = L"do_not_load";
						break;
					}
					else
					{
						wcout<<"The option you input is wrong, please try again:"<<endl;
					}
				}
			}
			if(LoadingCommand == L"load")
			{
				wstring FormatChoosingCommand;
				while (true)
				{
					wcout<<"Please choose the type of file you are going to load:"<<endl<<"1.MIDI(.mid)"<<endl<<"2.UTAU Project(.ust)"<<endl<<"3.VOCALOID3 Project(.vsqx)"<<endl;
					wcout<<endl<<"Please enter a number listed above, or enter \"Q\" to quit Loading:";
					wcin>>FormatChoosingCommand;
					if (FormatChoosingCommand == L"Q")
					{
						break;
					}
					else if (FormatChoosingCommand == L"1")
					{
						LoadMIDI( TrackList, HarmoList, pIsLoaded, pFilePath, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
						FileFormat = 1;
						break;
					}
					else if (FormatChoosingCommand == L"2")
					{
						LoadUST( TrackList, HarmoList, pIsLoaded, pFilePath );
						FileFormat = 2;
						break;
					}
					else if (FormatChoosingCommand == L"3")
					{
						LoadVSQX( TrackList, HarmoList, pIsLoaded, pFilePath );
						FileFormat = 3;
						break;
					}	
					else
					{
						wcout<<"The option you input is wrong, please try again."<<endl;
						continue;
					}
				}
			}
		}
		else if( MainCommand == L"2" && IsLoaded )
		{
			Tonalization( TrackList, pIsTonalized );
		}
		else if( MainCommand == L"3" && IsLoaded && IsTonalized )
		{
			Harmonization( TrackList, HarmoList );
		}
		else if( MainCommand == L"4" && IsLoaded )
		{
			switch (FileFormat)
			{
			case 1:
				SaveMIDI( TrackList, HarmoList, FilePath, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
				break;
			case 2:
				SaveUST( TrackList, HarmoList, FilePath );
				break;
			case 3:
				SaveVSQX( TrackList, HarmoList, FilePath );
				break;
			default:
				break;
			}

		}
		else if( MainCommand == L"5" && IsLoaded )
		{
			switch (FileFormat)
			{
			case 1:
				SaveAsMIDI( TrackList, HarmoList, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
				break;
			case 2:
				SaveAsUST( TrackList, HarmoList, FilePath );
				break;
			case 3:
				SaveAsVSQX( TrackList, HarmoList, FilePath );
				break;
			default:
				break;
			}
		}
		else if( MainCommand == L"6" )
		{	
			break;
		}
		else
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
		}
	}
	//程序退出
	wcout<<"Thank you for using."<<endl;
	system("pause");
	MIDIData_Delete (pMIDIData);
	return;
}//主函数
wstring ReceiveMainCommand( bool* pIsLoaded, bool* pIsTonalized, wstring* pFilePath, TRACK* TrackList, TRACK* HarmoList )
{
	wstring CommandingOpt= DEFAULT_STR;
	//根据文件状态不同输出不同的提示文字
	if ( !*pIsLoaded )
	{
		wcout<<endl<<"File has not been loaded."<<endl<<endl;
	}
	else if ( !*pIsTonalized )
	{
		wcout<<endl<<"File in process:"<<endl;
		wcout<<*pFilePath<<endl<<endl;
		PrintTrackList(TrackList, HarmoList);
		wcout<<"No track has been tonalized."<<endl;
		wcout<<"Please tonalize any track before harmonizing."<<endl<<endl;
	}
	else
	{
		wcout<<endl<<"File in process:"<<endl;
		wcout<<*pFilePath<<endl<<endl;
		PrintTrackList(TrackList, HarmoList);
		wcout<<endl<<endl;
	}
	wcout<<"1.Load"<<endl;
	if ( *pIsLoaded )
	{
		wcout<<"2.Tonalize"<<endl;
	}
	if ( *pIsLoaded == true && *pIsTonalized == true )
	{
		wcout<<"3.Harmonize"<<endl;
	}	
	if ( *pIsLoaded == true )
	{
		wcout<<"4.Save"<<endl;
	}
	if ( *pIsLoaded == true )
	{
		wcout<<"5.Save As"<<endl;
	}
	wcout<<"6.Quit"<<endl;
	wcout<<endl<<"Please enter a number listed above:";
	//读取命令
	wcin>>CommandingOpt;
	return CommandingOpt;
}//主程序界面命令函数
void PrintTrackList( TRACK* TrackList, TRACK* HarmoList )
{
	wcout<<"Track List"<<endl;
	for( long i=0; i<TRACK::TrackNumTotal; i++)
		{
			wstring TrackName = TrackList[i].GetTrackName();
			wcout<<i<<". "<<TrackName<<endl;
			for( long k=0; k<TRACK::HarmoNumTotal; k++)
			{
				if( HarmoList[k].GetParentTrackNum() == i )
				{
					wcout<<"   "<<k+TRACK::TrackNumTotal<<"."<<HarmoList[k].GetTrackName()<<endl;
				}
			}
		}
	return;
}//打印音轨信息
void LoadMIDI( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent )
{
	long Measure=0;
	long Beat=0;
	long Tick=0;
	long Time=0;
	long* pMeasure=&Measure;
	long* pBeat=&Beat;
	long* pTick=&Tick;
	long* pTime=&Time;
	wstring LoadingPath;

	//判定载入的文件是否有效，并进行格式转换
	for ( int i=0; pMIDIData == NULL; i++ )
	{
		if ( i>0 )
		{
			wcout<<"Invalid path or filename."<<endl;
		}
		wcout<<"Please enter a path to load a *.mid file:";
		wcin>>LoadingPath;
		pMIDIData = MIDIData_LoadFromSMF (LoadingPath.c_str());
	}
	if(MIDIData_GetFormat(pMIDIData)==2)
			{
				pMIDIData = NULL;
				wcout<<"Error: MIDI file(Format=2) is not valid."<<endl;
				wcout<<"Loading failed."<<endl;
				system("pause");
				return;
			}
	if(MIDIData_GetFormat(pMIDIData)==0)
			{
				MIDIData_SetFormat(pMIDIData, 1);
				pMIDITrack = MIDIData_GetFirstTrack(pMIDIData);
				MIDITrack_SetName(pMIDITrack,L"Conductor Track");
				pMIDITrack = MIDITrack_GetNextTrack(pMIDITrack);
				for( int i=1; i<17; i++ )
				{
					wstring TrackName=L"Channel "+to_wstring(i);
					MIDITrack_SetName(pMIDITrack,TrackName.c_str());
					if( MIDITrack_GetNumEvent(pMIDITrack) <3 )
					{
						npMIDITrack = MIDITrack_GetPrevTrack(pMIDITrack);
						MIDITrack_Delete(pMIDITrack);
						pMIDITrack = npMIDITrack;
					}
					pMIDITrack = MIDITrack_GetNextTrack(pMIDITrack);
				}
			}

	//建立音轨列表
	TRACK::TrackNumTotal = MIDIData_GetNumTrack(pMIDIData);
	TrackList = new TRACK[TRACK::TrackNumTotal];
	long HarmoNumMax = TRACK::TrackNumTotal * HARMONY_TYPE_MAX;
	HarmoList = new TRACK[HarmoNumMax];
	for( long i=0; i<MIDIData_GetNumTrack(pMIDIData); i++ )
	{
		wcout<<TrackList[i].GetTrackName();
	}
	long TrackNum=0;
	wchar_t szBuf[65536];
	forEachTrack (pMIDIData, pMIDITrack) 
	{
		memset(szBuf,0,sizeof(szBuf)/sizeof(wchar_t));
		wchar_t* npTrackName;
		npTrackName = MIDITrack_GetName(pMIDITrack, szBuf, sizeof(szBuf)/sizeof(wchar_t));
		if(npTrackName == NULL)
		{
			npTrackName = L"";
		}
		wstring nTrackName(npTrackName);
		TrackList[TrackNum].SetTrackNum(TrackNum);
		TrackList[TrackNum].SetTrackName(nTrackName);
		long EventNumTotal=MIDITrack_CountEvent(pMIDITrack);
		long NoteNum=0;
		long BarNum=0;
		for (int i = 0; i < 7; i++)
		{
			TrackList[TrackNum].HarmoTrackNum[i] = -1;
		}
		TrackList[TrackNum].SetHarmonic( false );
		TrackList[TrackNum].SetIsTonalized( false );
		//建立每个音轨的音符列表，读取音符信息
		TrackList[TrackNum].CreateNoteList(EventNumTotal);
		pMIDIEvent = MIDITrack_GetFirstEvent(pMIDITrack);
		npMIDIEvent = pMIDIEvent;
		forEachEvent (pMIDITrack, pMIDIEvent)
		{
			if( MIDIEvent_IsNoteOn(pMIDIEvent) )
			{
				long channelnum = MIDIEvent_GetChannel(pMIDIEvent);
				if( MIDIEvent_GetTime(pMIDIEvent) < MIDIEvent_GetTime(npMIDIEvent) )
				{
					wcout<<"Error: Overlapping notes found."<<endl;
					wcout<<"Loading failed."<<endl;
					system("pause");
					pMIDIData = NULL;
					return;
				}
				npMIDIEvent=pMIDIEvent;
				while( !MIDIEvent_IsNoteOff(npMIDIEvent) || ( MIDIEvent_IsNoteOff(npMIDIEvent) && MIDIEvent_GetChannel(npMIDIEvent)!=channelnum ) )
				{
					npMIDIEvent=MIDIEvent_GetNextEvent(npMIDIEvent);
				}
				TrackList[TrackNum].NoteList[NoteNum].SetNoteNum(NoteNum);
				TrackList[TrackNum].NoteList[NoteNum].SetNoteKey(MIDIEvent_GetKey(pMIDIEvent));
				TrackList[TrackNum].NoteList[NoteNum].SetNoteTimeOn(MIDIEvent_GetTime(pMIDIEvent));
				TrackList[TrackNum].NoteList[NoteNum].SetNoteTimeOff(MIDIEvent_GetTime(npMIDIEvent));
				NoteNum++;
			}
		}
		TrackList[TrackNum].SetNoteNumTotal(NoteNum);
		//建立每个音轨的小节列表，读取小节信息
		MIDIData_BreakTime (pMIDIData, MIDITrack_GetEndTime(pMIDITrack), pMeasure, pBeat, pTick);
		long MaxBarNum = *pMeasure + 1;
		TrackList[TrackNum].CreateBarList(MaxBarNum);
		if(NoteNum==0)
		{
			TrackList[TrackNum].SetEmptiness(true);
		}
		else
		{
			TrackList[TrackNum].SetEmptiness(false);
			for(int i=0,j=0; i<MaxBarNum && j<TrackList[TrackNum].GetNoteNumTotal(); i++, BarNum++)
			{
				TrackList[TrackNum].BarList[i].SetBarNum(i);
				MIDIData_MakeTime(pMIDIData, i, 0, 0, pTime);
				TrackList[TrackNum].BarList[i].SetBarTimeOn(*pTime);
				MIDIData_MakeTime(pMIDIData, i+1, 0, 0, pTime);
				TrackList[TrackNum].BarList[i].SetBarTimeOff(*pTime);
				TrackList[TrackNum].BarList[i].ParentTrack = &TrackList[TrackNum];
				if(TrackList[TrackNum].NoteList[j].GetNoteTimeOn() >= TrackList[TrackNum].BarList[i].GetBarTimeOff())
				{
					TrackList[TrackNum].BarList[i].SetEmptiness(true);
				}
				else
				{
					TrackList[TrackNum].BarList[i].SetEmptiness(false);
					TrackList[TrackNum].BarList[i].FirstNoteNum = j;
					j++;
				}
				while(j<=TrackList[TrackNum].GetNoteNumTotal()-1 && TrackList[TrackNum].NoteList[j].GetNoteTimeOn() < TrackList[TrackNum].BarList[i].GetBarTimeOff())
				{
					j++;
				}
				if(!TrackList[TrackNum].BarList[i].BarIsEmpty())
				{
					TrackList[TrackNum].BarList[i].LastNoteNum = j-1;
				}
				if(TrackList[TrackNum].BarList[i].BarIsEmpty())
				{
					TrackList[TrackNum].BarList[i].SetValidity(false);
				}
				else if( (static_cast <double>(TrackList[TrackNum].BarList[i].GetValidLength())/static_cast <double>(TrackList[TrackNum].BarList[i].GetBarLength())) < VALID_LENGTH_PERCENT_THRESHOLD )
				{
					TrackList[TrackNum].BarList[i].SetValidity(false);
				}
				else
				{
					TrackList[TrackNum].BarList[i].SetValidity(true);
				}
			}
			TrackList[TrackNum].SetBarNumTotal(BarNum);
		}
		TrackNum++;
	}
	*pIsLoaded = true;
	*pFilePath = LoadingPath;
	wcout<<endl<<"The MIDI file is successfully loaded."<<endl<<endl;
	system("pause");
	return;
}//载入MIDI函数
void Renew( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent, bool* pIsTonalized )
{
	delete[] TrackList;
	delete[] HarmoList;
	TRACK::TrackNumTotal = 0;
	TRACK::HarmoNumTotal = 0;
	*pIsLoaded = false;
	*pIsTonalized = false;
	*pFilePath = DEFAULT_STR;
	MIDIData_Delete(pMIDIData);
	pMIDIData = NULL;
	pMIDITrack = NULL;
	npMIDITrack = NULL;
	pMIDIEvent = NULL;
	npMIDIEvent = NULL;
	FileFormat = 0;
	return;
}//初始化函数
void LoadUST( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath )
{
	long NoteNum = 0;
	long BarNum = 0;
	long Time = 0;
	bool USTLoaded = false;
	wstring LoadingPath;
	ifstream ust;
	string strbuf;
	for ( int i = 0; USTLoaded == false; i++ )
	{
		if ( i>0 )
		{
			wcout<<"Invalid path or filename."<<endl;
		}
		wcout<<"Please enter a path to load a *.ust file:";
		wcin>>LoadingPath;
		ust.open(LoadingPath.c_str());
		USTLoaded = ust;
	}

	//建立音轨列表
	TRACK::TrackNumTotal = 1;
	TrackList = new TRACK[TRACK::TrackNumTotal];
	long HarmoNumMax = TRACK::TrackNumTotal * HARMONY_TYPE_MAX;
	HarmoList = new TRACK[HarmoNumMax];
	wstring Filename;
	string Lyricbuf;
	string childstrbuf;
	long MaxNoteNum = -2;
	int strlength;
	while( getline( ust, strbuf ) )
	{
		if(	strbuf.find("[#") != string::npos )
		{
			MaxNoteNum ++;
		}
	}
	ust.close();
	ust.open(LoadingPath.c_str());
	int pos = LoadingPath.rfind( '\\' );
	wstring TrackName;
	if (pos == wstring::npos)
	{
		TrackName = LoadingPath.substr( 0, LoadingPath.length() - 4 );
	}
	else
	{
		TrackName = LoadingPath.substr( pos + 1, LoadingPath.length() - pos - 5);
	}
	TrackList[0].SetTrackNum(0);
	TrackList[0].SetTrackName(TrackName);
	for (int i = 0; i < 7; i++)
	{
		TrackList[0].HarmoTrackNum[i] = -1;
	}
	TrackList[0].SetHarmonic( false );
	TrackList[0].SetIsTonalized( false );
	//建立音符列表，读取音符信息
	TrackList[0].CreateNoteList( MaxNoteNum );
	while( getline( ust, strbuf ) )
	{
		if(	strbuf.find("[#") != string::npos && strbuf.length() == 7 )
		{
			TrackList[0].NoteList[NoteNum].SetNoteNum(NoteNum);
			//Get ID
			TrackList[0].NoteList[NoteNum].NoteID = strbuf.substr( 0 , 7 );
			//Get Length
			getline( ust, strbuf );
			strlength = strbuf.length();
			childstrbuf.assign( strbuf, 7, strlength - 7 );
			TrackList[0].NoteList[NoteNum].SetNoteTimeOn( Time );
			Time += stol(childstrbuf);
			TrackList[0].NoteList[NoteNum].SetNoteTimeOff( Time );
			//Get Lyric
			getline( ust, strbuf );
			strlength = strbuf.length();
			childstrbuf.assign( strbuf, 6, strlength - 6 );
			Lyricbuf = childstrbuf;
			//Get Key
			getline( ust, strbuf );
			strlength = strbuf.length();
			childstrbuf.assign( strbuf, 8, strlength - 8 );
			TrackList[0].NoteList[NoteNum].SetNoteKey( stol(childstrbuf) );
			if ( Lyricbuf != "R" && TrackList[0].NoteList[NoteNum].GetNoteLength() != 0 )
			{
				NoteNum++;
			}
		}
	}
	TrackList[0].SetNoteNumTotal(NoteNum);
	//建立小节列表，读取小节信息
	long MaxBarNum = static_cast <long> ( Time / UST_BAR_TIME ) + 1;
	TrackList[0].CreateBarList(MaxBarNum);
	if(NoteNum==0)
	{
		TrackList[0].SetEmptiness(true);
	}
	else
	{
		TrackList[0].SetEmptiness(false);
		for(int i=0,j=0; i<MaxBarNum && j<TrackList[0].GetNoteNumTotal(); i++, BarNum++)
		{
			TrackList[0].BarList[i].SetBarNum( i );
			TrackList[0].BarList[i].SetBarTimeOn( i * UST_BAR_TIME );
			TrackList[0].BarList[i].SetBarTimeOff( ( i + 1 ) * UST_BAR_TIME );
			TrackList[0].BarList[i].ParentTrack = &TrackList[0];
			if(TrackList[0].NoteList[j].GetNoteTimeOn() >= TrackList[0].BarList[i].GetBarTimeOff())
			{
				TrackList[0].BarList[i].SetEmptiness(true);
			}
			else
			{
				TrackList[0].BarList[i].SetEmptiness(false);
				TrackList[0].BarList[i].FirstNoteNum = j;
				j++;
			}
			while(j<=TrackList[0].GetNoteNumTotal()-1 && TrackList[0].NoteList[j].GetNoteTimeOn() < TrackList[0].BarList[i].GetBarTimeOff())
			{
				j++;
			}
			if(!TrackList[0].BarList[i].BarIsEmpty())
			{
				TrackList[0].BarList[i].LastNoteNum = j-1;
			}
			if(TrackList[0].BarList[i].BarIsEmpty())
			{
				TrackList[0].BarList[i].SetValidity(false);
			}
			else if( (static_cast <double>(TrackList[0].BarList[i].GetValidLength())/static_cast <double>(TrackList[0].BarList[i].GetBarLength())) < VALID_LENGTH_PERCENT_THRESHOLD )
			{
				TrackList[0].BarList[i].SetValidity(false);
			}
			else
			{
				TrackList[0].BarList[i].SetValidity(true);
			}
		}
		TrackList[0].SetBarNumTotal(BarNum);
	}
	*pIsLoaded = true;
	*pFilePath = LoadingPath;
	wcout<<endl<<"The UST file is successfully loaded."<<endl<<endl;
	system("pause");
	ust.close();
	return;
}
void LoadVSQX( TRACK* &TrackList, TRACK* &HarmoList, bool* pIsLoaded, wstring* pFilePath )
{
	long NoteNum;
	long BarNum;
	long TrackNum = 0;
	long PartTimeOn = 0;
	bool VSQXLoaded = false;
	wstring LoadingPath;
	string strbuf;
	TiXmlDocument vsqx;
	for ( int i = 0; VSQXLoaded == false; i++ )
	{
		if ( i>0 )
		{
			wcout<<"Invalid path or filename."<<endl;
		}
		wcout<<"Please enter a path to load a *.vsqx file:";
		wcin>>LoadingPath;
		VSQXLoaded = vsqx.LoadFile(WStringToString(LoadingPath).c_str(),TIXML_ENCODING_UTF8);
	}

	//建立音轨列表
	TRACK::TrackNumTotal = 0;
	TiXmlElement* root = vsqx.RootElement();
	TiXmlElement* track;
	for ( track = root -> FirstChildElement("vsTrack"); track; track = track -> NextSiblingElement("vsTrack") )
	{
		TRACK::TrackNumTotal ++; 
	}
	TrackList = new TRACK[TRACK::TrackNumTotal];
	long HarmoNumMax = TRACK::TrackNumTotal * HARMONY_TYPE_MAX;
	HarmoList = new TRACK[HarmoNumMax];
	string TrackNameBuf;
	TiXmlElement* note;
	TiXmlElement* timeSig;
	for ( track = root -> FirstChildElement("vsTrack"); track; track = track -> NextSiblingElement("vsTrack") ) 
	{
		NoteNum = 0;
		BarNum = 0;
		TiXmlElement* intrack = track -> FirstChildElement("vsTrackNo");
		TrackList[TrackNum].SetTrackNum(stol(intrack->GetText()));
		intrack = intrack -> NextSiblingElement("trackName");
		vector<wchar_t> TrackNameBuf;
		wstring TrackName = L"";
		UTF8ToUnicode( TrackNameBuf, intrack -> FirstChild() -> Value(), strlen(intrack -> FirstChild() -> Value()) );
		for (int i = 0; i< TrackNameBuf.size(); i++)
		{
			TrackName += TrackNameBuf[i];
		}
		TrackList[TrackNum].SetTrackName(TrackName);
		for (int i = 0; i < 7; i++)
		{
			TrackList[TrackNum].HarmoTrackNum[i] = -1;
		}
		TrackList[TrackNum].SetHarmonic( false );
		TrackList[TrackNum].SetIsTonalized( false );
		//建立每个音轨的音符列表，读取音符信息
		long MaxNoteNum = 0;
		for ( intrack = track -> FirstChildElement("musicalPart"); intrack; intrack = intrack -> NextSiblingElement("musicalPart") ) 
		{
			for ( note = intrack -> FirstChildElement("note"); note; note = note -> NextSiblingElement("note") )
			{
				MaxNoteNum ++;
			}
		}
		TrackList[TrackNum].CreateNoteList(MaxNoteNum);
		for ( intrack = track -> FirstChildElement("musicalPart"); intrack; intrack = intrack -> NextSiblingElement("musicalPart") )
		{
			PartTimeOn = stol ( intrack -> FirstChildElement("posTick") -> GetText() );
			for ( note = intrack -> FirstChildElement("note"); note; note = note -> NextSiblingElement("note") )
			{
				TrackList[TrackNum].NoteList[NoteNum].SetNoteNum(NoteNum);
				TrackList[TrackNum].NoteList[NoteNum].SetNoteKey(stol(note->FirstChildElement("noteNum")->GetText())-12);
				TrackList[TrackNum].NoteList[NoteNum].SetNoteTimeOn(stol(note->FirstChildElement("posTick")->GetText()) + PartTimeOn );
				TrackList[TrackNum].NoteList[NoteNum].SetNoteTimeOff(stol(note->FirstChildElement("durTick")->GetText()) + TrackList[TrackNum].NoteList[NoteNum].GetNoteTimeOn() );
				NoteNum ++;
			}
		}
		TrackList[TrackNum].SetNoteNumTotal(NoteNum);

		//建立小节列表，读取小节信息
		long MaxBarNum = 1000;
		TrackList[TrackNum].CreateBarList(MaxBarNum);
		if(NoteNum==0)
		{
			TrackList[TrackNum].SetEmptiness(true);
		}
		else
		{
			TrackList[TrackNum].SetEmptiness(false);
			intrack = root -> FirstChildElement("masterTrack");
			timeSig = intrack -> FirstChildElement("timeSig");
			long preBar = stol( intrack -> FirstChildElement("preMeasure") -> GetText() );
			long pos_timgSig;
			long nume;
			long denomi;
			long BarTime;
			for(int i=0,j=0; i<MaxBarNum && j<TrackList[0].GetNoteNumTotal(); i++, BarNum++)
			{
				TrackList[TrackNum].BarList[i].SetBarNum( i );
				pos_timgSig = stol( timeSig -> FirstChildElement("posMes") -> GetText() );
				nume = stol( timeSig -> FirstChildElement("nume") -> GetText() );
				denomi = stol( timeSig -> FirstChildElement("denomi") -> GetText() );
				if ( pos_timgSig == i )
				{
					BarTime = nume * 1920 / denomi;
					if ( timeSig -> NextSiblingElement("timeSig") )
					{
						timeSig = timeSig -> NextSiblingElement("timeSig");
					}
				}
				if ( i==0 )
				{
					TrackList[TrackNum].BarList[i].SetBarTimeOn( 0 );
				}
				else 
				{
					TrackList[TrackNum].BarList[i].SetBarTimeOn( TrackList[TrackNum].BarList[i-1].GetBarTimeOff() );
				}
				TrackList[TrackNum].BarList[i].SetBarTimeOff( TrackList[TrackNum].BarList[i].GetBarTimeOn() + BarTime );
				TrackList[TrackNum].BarList[i].ParentTrack = &TrackList[TrackNum];
				if(TrackList[TrackNum].NoteList[j].GetNoteTimeOn() >= TrackList[TrackNum].BarList[i].GetBarTimeOff())
				{
					TrackList[TrackNum].BarList[i].SetEmptiness(true);
				}
				else
				{
					TrackList[TrackNum].BarList[i].SetEmptiness(false);
					TrackList[TrackNum].BarList[i].FirstNoteNum = j;
					j++;
				}
				while(j<=TrackList[TrackNum].GetNoteNumTotal()-1 && TrackList[TrackNum].NoteList[j].GetNoteTimeOn() < TrackList[TrackNum].BarList[i].GetBarTimeOff())
				{
					j++;
				}
				if(!TrackList[TrackNum].BarList[i].BarIsEmpty())
				{
					TrackList[TrackNum].BarList[i].LastNoteNum = j-1;
				}
				if(TrackList[TrackNum].BarList[i].BarIsEmpty())
				{
					TrackList[TrackNum].BarList[i].SetValidity(false);
				}
				else if( (static_cast <double>(TrackList[TrackNum].BarList[i].GetValidLength())/static_cast <double>(TrackList[TrackNum].BarList[i].GetBarLength())) < VALID_LENGTH_PERCENT_THRESHOLD )
				{
					TrackList[TrackNum].BarList[i].SetValidity(false);
				}
				else
				{
					TrackList[TrackNum].BarList[i].SetValidity(true);
				}
			}
			TrackList[TrackNum].SetBarNumTotal(BarNum);
		}
		TrackNum++;
	}
	*pIsLoaded = true;
	*pFilePath = LoadingPath;
	wcout<<endl<<"The VSQX file is successfully loaded."<<endl<<endl;
	system("pause");
	return;
}
void SaveMIDI( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent )
{
	//将本程序的数据转换成MIDI数据
	long NoteNum;
	for( long i=0; i<TRACK::HarmoNumTotal; i++ )
	{
		if (!HarmoList[i].TrackIsSaved())
		{
			npMIDITrack = MIDIData_GetTrack( pMIDIData, HarmoList[i].GetParentTrackNum() );
			pMIDITrack = MIDITrack_CreateClone( npMIDITrack );
			MIDIData_AddTrack ( pMIDIData, pMIDITrack );
			MIDITrack_SetName( pMIDITrack, HarmoList[i].GetTrackName().c_str());
			NoteNum = 0;
			forEachEvent( pMIDITrack, pMIDIEvent )
			{
				if ( MIDIEvent_IsNoteOn(pMIDIEvent) )
				{
					npMIDIEvent=pMIDIEvent;
					while( !MIDIEvent_IsNoteOff(npMIDIEvent) || MIDIEvent_GetTime(pMIDIEvent) == MIDIEvent_GetTime(npMIDIEvent) )
					{
						npMIDIEvent=MIDIEvent_GetNextEvent(npMIDIEvent);
					}
					if(HarmoList[i].NoteList[NoteNum].NoteIsValid())
					{
						MIDIEvent_SetKey(pMIDIEvent, HarmoList[i].NoteList[NoteNum].GetNoteKey());
						MIDIEvent_SetKey(npMIDIEvent, HarmoList[i].NoteList[NoteNum].GetNoteKey());
					}
					else
					{
						MIDIEvent_Delete(npMIDIEvent);
						npMIDIEvent=MIDIEvent_GetPrevEvent(pMIDIEvent);
						MIDIEvent_Delete(pMIDIEvent);
						pMIDIEvent=npMIDIEvent;
					}
					NoteNum++;
				}
			}
			HarmoList[i].SetIsSaved(true);
		}
	}
	//保存MIDI文件
	MIDIData_SaveAsSMF( pMIDIData, FilePath.c_str() );
	wcout<<"File is successfully saved."<<endl;
	system("pause");
	return;
}//保存MIDI函数
void SaveUST( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath )
{
	long HarmoNum;
	wstring SavingCommand = DEFAULT_STR;
	while (true)
	{
		wcout<<endl;
		PrintTrackList( TrackList , HarmoList );
		wcout<<endl<<"Plear enter the track number of the harmonic track you want to save, or enter \"Q\" to quit:";
		wcin>>SavingCommand;
		if (SavingCommand == L"Q")
		{
			break;
		}
		else if ( !StrIsDigit(SavingCommand) )
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		else
		{
			HarmoNum = stol(SavingCommand) - TRACK::TrackNumTotal;
			if (HarmoNum < 0 || HarmoNum >= TRACK::HarmoNumTotal)
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else if (HarmoList[HarmoNum].TrackIsEmpty())
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else
			{
				ifstream in( FilePath.c_str() ); 
				istreambuf_iterator<char> beg(in), end; 
				string strbuf(beg, end);
				in.close();
				int pos = 0, pos2 = 0;
				for (int i = 0; i < HarmoList[HarmoNum].GetNoteNumTotal(); i++)
				{
					pos = strbuf.find( HarmoList[HarmoNum].NoteList[i].NoteID, pos );
					pos = strbuf.find( "NoteNum=" , pos );
					pos2 = strbuf.find( '\n' , pos );
					strbuf.replace( pos + 8, pos2 - pos - 8, to_string(HarmoList[HarmoNum].NoteList[i].GetNoteKey()));
				}
				pos = FilePath.rfind( '\\' );
				wstring SavePath = DEFAULT_STR;
				if( pos != string::npos )
				{
					SavePath = FilePath.substr( 0, pos + 1 );
				}
				SavePath += HarmoList[HarmoNum].GetTrackName();
				SavePath += L".ust";
				ofstream out( SavePath.c_str() );
				out<<strbuf;
				out.close();
				wcout<<"File is successfully saved."<<endl;
			}
		}
	}
}
void SaveVSQX( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath )
{
	long NoteNum = 0;
	for( long i=0; i<TRACK::HarmoNumTotal; i++ )
	{
		if (!HarmoList[i].TrackIsSaved())
		{
			TiXmlDocument vsqx;
			vsqx.LoadFile(WStringToString(FilePath).c_str(),TIXML_ENCODING_UTF8);
			TiXmlElement* root = vsqx.RootElement();
			TiXmlElement* Mixer = root -> FirstChildElement("mixer");
			TiXmlElement* VsUnit;
			TiXmlElement* track;
			VsUnit = Mixer -> FirstChildElement("vsUnit");
			track = root -> FirstChildElement("vsTrack");
			while( stol ( VsUnit -> FirstChildElement("vsTrackNo") -> GetText() ) != HarmoList[i].GetParentTrackNum() )
			{
				VsUnit = VsUnit -> NextSiblingElement("vsUnit");
				if(!VsUnit)
				{
					wcout<<"Original Track cannot be found. Saving failed."<<endl;
					return;
				}
			}
			while( stol ( track -> FirstChildElement("vsTrackNo") -> GetText() ) != HarmoList[i].GetParentTrackNum() )
			{
				track = track -> NextSiblingElement("vsTrack");
				if(!track)
				{
					wcout<<"Original Track cannot be found. Saving failed."<<endl;
					return;
				}
			}
			TiXmlNode* newVsUnit = new TiXmlElement("vsUnit");
			TiXmlNode* newtrack = new TiXmlElement("vsTrack");
			TiXmlElement* intrack;
			TiXmlElement* note;
			TiXmlNode* harmoVsUnit = Mixer -> InsertAfterChild( VsUnit, *newVsUnit );
			TiXmlNode* harmotrack = root -> InsertAfterChild( track, *newtrack );
			harmoVsUnit = Mixer -> ReplaceChild( harmoVsUnit, *VsUnit );
			harmotrack = root -> ReplaceChild( harmotrack, *track );
			char* harmotracknum = new char[64];
			itoa( TRACK::TrackNumTotal + i, harmotracknum, 10);
			harmoVsUnit -> FirstChildElement("vsTrackNo")-> FirstChild() -> SetValue( harmotracknum );
			harmotrack -> FirstChildElement("vsTrackNo")-> FirstChild() -> SetValue( harmotracknum );
			vector<char> TrackNameBuf;
			UnicodeToUTF8( TrackNameBuf, HarmoList[i].GetTrackName().c_str(), wcslen(HarmoList[i].GetTrackName().c_str()));
			char* HarmoTrackName = new char[64];
			for (int i = 0; i< TrackNameBuf.size(); i++)
			{
				HarmoTrackName[i] = TrackNameBuf[i];
			}
			HarmoTrackName[TrackNameBuf.size()] = '\0';
			harmotrack -> FirstChildElement("trackName") -> FirstChild() -> SetValue( HarmoTrackName );
			for ( intrack = harmotrack -> FirstChildElement("musicalPart"), NoteNum = 0; intrack && ( NoteNum < HarmoList[i].GetNoteNumTotal() ); intrack = intrack -> NextSiblingElement("musicalPart") ) 
			{
				for ( note = intrack -> FirstChildElement("note"); note && ( NoteNum < HarmoList[i].GetNoteNumTotal() ); note = note -> NextSiblingElement("note"), NoteNum++ )
				{
					char* notekey = new char[64];
					itoa( HarmoList[i].NoteList[NoteNum].GetNoteKey() + 12, notekey, 10);
					note -> FirstChildElement("noteNum") -> FirstChild() -> SetValue( notekey );
				}
			}
			vsqx.SaveFile();
			HarmoList[i].SetIsSaved(true); 
		}
	}
	wcout<<"File is successfully saved."<<endl;
	system("pause");
	return;
}
void SaveAsMIDI( TRACK* &TrackList, TRACK* &HarmoList, MIDIData* &pMIDIData, MIDITrack* &pMIDITrack, MIDITrack* &npMIDITrack, MIDIEvent* &pMIDIEvent, MIDIEvent* &npMIDIEvent )
{
	//将本程序的数据转换成MIDI数据
	long NoteNum;
	for( long i=0; i<TRACK::HarmoNumTotal; i++ )
	{
		if (!HarmoList[i].TrackIsSaved())
		{
			npMIDITrack = MIDIData_GetTrack( pMIDIData, HarmoList[i].GetParentTrackNum() );
			pMIDITrack = MIDITrack_CreateClone( npMIDITrack );
			MIDIData_AddTrack ( pMIDIData, pMIDITrack );
			MIDITrack_SetName( pMIDITrack, HarmoList[i].GetTrackName().c_str());
			NoteNum = 0;
			forEachEvent( pMIDITrack, pMIDIEvent )
			{
				if ( MIDIEvent_IsNoteOn(pMIDIEvent) )
				{
					npMIDIEvent=pMIDIEvent;
					while( !MIDIEvent_IsNoteOff(npMIDIEvent) || MIDIEvent_GetTime(pMIDIEvent) == MIDIEvent_GetTime(npMIDIEvent) )
					{
						npMIDIEvent=MIDIEvent_GetNextEvent(npMIDIEvent);
					}
					if(HarmoList[i].NoteList[NoteNum].NoteIsValid())
					{
						MIDIEvent_SetKey(pMIDIEvent, HarmoList[i].NoteList[NoteNum].GetNoteKey());
						MIDIEvent_SetKey(npMIDIEvent, HarmoList[i].NoteList[NoteNum].GetNoteKey());
					}
					else
					{
						MIDIEvent_Delete(npMIDIEvent);
						npMIDIEvent=MIDIEvent_GetPrevEvent(pMIDIEvent);
						MIDIEvent_Delete(pMIDIEvent);
						pMIDIEvent=npMIDIEvent;
					}
					NoteNum++;
				}
			}
			HarmoList[i].SetIsSaved(true);
		}
	}
	//读取用户输入的路径，另存为MIDI
	long IsSaved = -1;
	wstring SavePath = DEFAULT_STR;
	while( IsSaved != 1 )
	{
		if( IsSaved != -1 )
		{
			wcout<<"Saving Failed. Please check if your path is accessible."<<endl;
		}
		wcout<<endl<<"Please enter the path and file name you want to save as(...\\*.mid):";
		wcin>>SavePath;
		IsSaved = MIDIData_SaveAsSMF( pMIDIData, SavePath.c_str() );
	}
	wcout<<"File is successfully saved."<<endl;
	system("pause");
	return;
}//另存为MIDI函数
void SaveAsUST( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath )
{
	long HarmoNum;
	wstring SavingCommand = DEFAULT_STR;
	while (true)
	{
		wcout<<endl;
		PrintTrackList( TrackList , HarmoList );
		wcout<<endl<<"Plear enter the track number of the harmonic track you want to save, or enter \"Q\" to quit:";
		wcin>>SavingCommand;
		if (SavingCommand == L"Q")
		{
			break;
		}
		else if ( !StrIsDigit(SavingCommand) )
		{
			wcout<<"The option you input is wrong, please try again."<<endl;
			continue;
		}
		else
		{
			HarmoNum = stol(SavingCommand) - TRACK::TrackNumTotal;
			if (HarmoNum < 0 || HarmoNum >= TRACK::HarmoNumTotal)
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else if (HarmoList[HarmoNum].TrackIsEmpty())
			{
				wcout<<"The option you input is wrong, please try again."<<endl;
				continue;
			}
			else
			{
				ifstream in( FilePath.c_str() ); 
				istreambuf_iterator<char> beg(in), end; 
				string strbuf(beg, end);
				in.close();
				int pos = 0, pos2 = 0;
				for (int i = 0; i < HarmoList[HarmoNum].GetNoteNumTotal(); i++)
				{
					pos = strbuf.find( HarmoList[HarmoNum].NoteList[i].NoteID, pos );
					pos = strbuf.find( "NoteNum=" , pos );
					pos2 = strbuf.find( '\n' , pos );
					strbuf.replace( pos + 8, pos2 - pos - 8, to_string(HarmoList[HarmoNum].NoteList[i].GetNoteKey()));
				}
				//读取用户输入的路径，另存为UST
				long IsSaved = -1;
				wstring SavePath = DEFAULT_STR;
				while( IsSaved != 1 )
				{
					if( IsSaved != -1 )
					{
						wcout<<"Saving Failed. Please check if your path is accessible."<<endl;
					}
					wcout<<endl<<"Please enter the path and file name you want to save as(...\\*.ust):";
					wcin>>SavePath;
					ofstream out( SavePath.c_str() );
					if ( out )
					{
						IsSaved = 1;
					}
					else
					{
						IsSaved = 0;
					}
					out<<strbuf;
					out.close();
					wcout<<"File is successfully saved."<<endl;
				}
			}
		}
	}
}
void SaveAsVSQX( TRACK* &TrackList, TRACK* &HarmoList, wstring FilePath )
{
	long IsSaved = -1;
	wstring SavePath = DEFAULT_STR;
	TiXmlDocument vsqx;
	vsqx.LoadFile(WStringToString(FilePath).c_str(),TIXML_ENCODING_UTF8);
	while( IsSaved != 1 )
	{
		if( IsSaved != -1 )
		{
			wcout<<"Saving Failed. Please check if your path is accessible."<<endl;
		}
		wcout<<endl<<"Please enter the path and file name you want to save as(...\\*.vsqx):";
		wcin>>SavePath;
		long NoteNum = 0;
		for( long i=0; i<TRACK::HarmoNumTotal; i++ )
		{
			if (!HarmoList[i].TrackIsSaved())
			{
				TiXmlElement* root = vsqx.RootElement();
				TiXmlElement* Mixer = root -> FirstChildElement("mixer");
				TiXmlElement* VsUnit;
				TiXmlElement* track;
				VsUnit = Mixer -> FirstChildElement("vsUnit");
				track = root -> FirstChildElement("vsTrack");
				while( stol ( VsUnit -> FirstChildElement("vsTrackNo") -> GetText() ) != HarmoList[i].GetParentTrackNum() )
				{
					VsUnit = VsUnit -> NextSiblingElement("vsUnit");
					if(!VsUnit)
					{
						wcout<<"Original Track cannot be found. Saving failed."<<endl;
						return;
					}
				}
				while( stol ( track -> FirstChildElement("vsTrackNo") -> GetText() ) != HarmoList[i].GetParentTrackNum() )
				{
					track = track -> NextSiblingElement("vsTrack");
					if(!track)
					{
						wcout<<"Original Track cannot be found. Saving failed."<<endl;
						return;
					}
				}
				TiXmlNode* newVsUnit = new TiXmlElement("vsUnit");
				TiXmlNode* newtrack = new TiXmlElement("vsTrack");
				TiXmlElement* intrack;
				TiXmlElement* note;
				TiXmlNode* harmoVsUnit = Mixer -> InsertAfterChild( VsUnit, *newVsUnit );
				TiXmlNode* harmotrack = root -> InsertAfterChild( track, *newtrack );
				harmoVsUnit = Mixer -> ReplaceChild( harmoVsUnit, *VsUnit );
				harmotrack = root -> ReplaceChild( harmotrack, *track );
				char* harmotracknum = new char[64];
				itoa( TRACK::TrackNumTotal + i, harmotracknum, 10);
				harmoVsUnit -> FirstChildElement("vsTrackNo")-> FirstChild() -> SetValue( harmotracknum );
				harmotrack -> FirstChildElement("vsTrackNo")-> FirstChild() -> SetValue( harmotracknum );
				vector<char> TrackNameBuf;
				UnicodeToUTF8( TrackNameBuf, HarmoList[i].GetTrackName().c_str(), wcslen(HarmoList[i].GetTrackName().c_str()));
				char* HarmoTrackName = new char[64];
				for (int i = 0; i< TrackNameBuf.size(); i++)
				{
					HarmoTrackName[i] = TrackNameBuf[i];
				}
				HarmoTrackName[TrackNameBuf.size()] = '\0';
				harmotrack -> FirstChildElement("trackName") -> FirstChild() -> SetValue( HarmoTrackName );
				for ( intrack = harmotrack -> FirstChildElement("musicalPart"), NoteNum = 0; intrack && ( NoteNum < HarmoList[i].GetNoteNumTotal() ); intrack = intrack -> NextSiblingElement("musicalPart") ) 
				{
					for ( note = intrack -> FirstChildElement("note"); note && ( NoteNum < HarmoList[i].GetNoteNumTotal() ); note = note -> NextSiblingElement("note"), NoteNum++ )
					{
						char* notekey = new char[64];
						itoa( HarmoList[i].NoteList[NoteNum].GetNoteKey() + 12, notekey, 10);
						note -> FirstChildElement("noteNum") -> FirstChild() -> SetValue( notekey );
					}
				}
			}
		}
		if(!vsqx.SaveFile(WStringToString(SavePath).c_str())) 
		{
			IsSaved = 0;
			continue;
		}
		IsSaved = 1;
	}
	for( long i=0; i<TRACK::HarmoNumTotal; i++ )
	{
		HarmoList[i].SetIsSaved(true);
	}
	wcout<<"File is successfully saved."<<endl;
	system("pause");
	return;
}

//其他功能函数
bool StrIsDigit(wstring str) 
{ 
	for( unsigned int i=0; i<str.size(); i++ ) 
	{   
		 if ((str.at(i)>'9') || (str.at(i)<'0') )
		 {
			return  false; 
		 } 
    } 
	return   true; 
} ;//判断字符串是否是纯数字
long ConvertTonalityType(wstring TonalityType)
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
}//实现调号/音名的字符串型→long型的转换
long SortArrayByGreatness( double data[], long greatness )
{
	double datacopy[12];
	for (int i = 0; i < 12; i++)
	{
		datacopy[i] = data[i];
	}
	long order[12];
	for (int i = 0; i < 12; i++)
	{
		order[i] = i;
	}
	double databuf[12];
	long orderbuf[12];
	for (int i = 0; i < greatness; i++)
	{
		long numbuf = i;
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
wstring StringToWString(string &str)
 {
     std::wstring wstr(str.length(),L' ');
     std::copy(str.begin(), str.end(), wstr.begin());
     return wstr; 
 }
string WStringToString(wstring &wstr)
 {
     std::string str(wstr.length(), ' ');
     std::copy(wstr.begin(), wstr.end(), str.begin());
     return str; 
 }
bool UTF8ToUnicode(vector<wchar_t>& pun, const char* pu8, int utf8Len)    
{    
    // convert an UTF8 string to widechar     
    int nLen = MultiByteToWideChar(CP_UTF8, 0, pu8, utf8Len, NULL, 0);    
    if (nLen <=0)    
    {    
        return false;    
    }    
    pun.resize(nLen);    
    int nRtn = MultiByteToWideChar(CP_UTF8, 0, pu8, utf8Len, &*pun.begin(), nLen);    
  
    if(nRtn != nLen)    
    {    
        pun.clear();    
        return false;    
    }    
  
    return true;    
}    
bool UnicodeToUTF8(vector<char>& pu8, const wchar_t* pun, int uLen)    
{    
    // convert an widechar string to utf8    
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, pun, uLen, NULL, 0, NULL, NULL);    
    if (utf8Len<=0)    
    {    
        return false;    
    }    
    pu8.resize(utf8Len);    
    int nRtn = WideCharToMultiByte(CP_UTF8, 0, pun, uLen, &*pu8.begin(), utf8Len, NULL, NULL);    
  
    if (nRtn != utf8Len)    
    {    
        pu8.clear();    
        return false;    
    }    
    return true;    
}    