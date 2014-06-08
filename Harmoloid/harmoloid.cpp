#include <stdio.h>
#include "MIDIdata.h"
#include "harmoloid.h"
#include <iostream>
#include <string>
using namespace std;

/*主界面和主要模块函数的实现。*/

//类的静态数据成员初始化
long TRACK::TrackNumTotal = 0;
long TRACK::HarmoNumTotal = 0;

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

	//打印程序信息
	wcout<<"HARMOLOID Beta 0.2"<<endl<<"sdercolin (C) 2014"<<endl<<endl;
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
				LoadMIDI( TrackList, HarmoList, pIsLoaded, pFilePath, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
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
			SaveMIDI( TrackList, HarmoList, FilePath, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
		}
		else if( MainCommand == L"5" && IsLoaded )
		{
			SaveAsMIDI( TrackList, HarmoList, pMIDIData, pMIDITrack, npMIDITrack, pMIDIEvent, npMIDIEvent );
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
			wcout<<i<<". "<<TrackList[i].GetTrackName()<<endl;
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
	*pIsLoaded = false;
	*pIsTonalized = false;
	*pFilePath = DEFAULT_STR;
	MIDIData_Delete(pMIDIData);
	pMIDIData = NULL;
	pMIDITrack = NULL;
	npMIDITrack = NULL;
	pMIDIEvent = NULL;
	npMIDIEvent = NULL;
	return;
}//初始化函数
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
	wstring SavingPath = DEFAULT_STR;
	while( IsSaved != 1 )
	{
		if( IsSaved != -1 )
		{
			wcout<<"Saving Failed. Please check if your path is accessible."<<endl;
		}
		wcout<<endl<<"Please enter the path and file name you want to save as(...\\*.mid):";
		wcin>>SavingPath;
		IsSaved = MIDIData_SaveAsSMF( pMIDIData, SavingPath.c_str() );
	}
	wcout<<"File is successfully saved."<<endl;
	system("pause");
	return;
}//另存为MIDI函数

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