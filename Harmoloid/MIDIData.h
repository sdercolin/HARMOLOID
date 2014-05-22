/******************************************************************************/
/*                                                                            */
/*　MIDIData.h - MIDIDataヘッダーファイル                  (C)2002-2013 くず  */
/*                                                                            */
/******************************************************************************/

/* このモジュールは普通のＣ言語で書かれている。 */
/* このライブラリは、GNU 劣等一般公衆利用許諾契約書(LGPL)に基づき配布される。 */
/* プロジェクトホームページ："http://openmidiproject.sourceforge.jp/index.html" */
/* MIDIイベントの取得・設定・生成・挿入・削除 */
/* MIDIトラックの取得・設定・生成・挿入・削除 */
/* MIDIデータの生成・削除・SMFファイル(*.mid)入出力 */

/* This library is free software; you can redistribute it and/or */
/* modify it under the terms of the GNU Lesser General Public */
/* License as published by the Free Software Foundation; either */
/* version 2.1 of the License, or (at your option) any later version. */

/* This library is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/* Lesser General Public License for more details. */

/* You should have received a copy of the GNU Lesser General Public */
/* License along with this library; if not, write to the Free Software */
/* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA */

#ifndef _MIDIData_H_
#define _MIDIData_H_

/* C++からも使用可能とする */
#ifdef __cplusplus
extern "C" {
#endif

/* __stdcallの定義 */
/*
#ifndef __stdcall
#if defined(WINDOWS) || defined(_WINDOWS) || defined(__WINDOWS) || \
	defined(WIN32) || defined(_WIN32) || defined(__WIN32) || \
	defined(WIN64) || defined(_WIN64) || defined(__WIN64)
#define __stdcall __stdcall
#else
#define __stdcall
#endif
#endif
*/

/* MIDIEvent構造体 */
/* 双方向ダブルリンクリスト構造 */
/* ノード順序は絶対時刻で決定されます */
typedef struct tagMIDIEvent {
	long m_lTempIndex;                  /* このイベントの一時的なインデックス(0から始まる) */
	long m_lTime;                       /* 絶対時刻[Tick]又はSMPTEサブフレーム単位 */
	long m_lKind;                       /* イベントの種類(0x00～0xFF) */
	long m_lLen;                        /* イベントのデータ長さ[バイト] */
	unsigned char* m_pData;             /* イベントのデータバッファへのポインタ */
	unsigned long m_lData;              /* イベントのデータバッファ(MIDIチャンネルイベントのとき使う) */
	struct tagMIDIEvent* m_pNextEvent;  /* 次のイベントへのポインタ(なければNULL) */
	struct tagMIDIEvent* m_pPrevEvent;  /* 前のイベントへのポインタ(なければNULL) */
	struct tagMIDIEvent* m_pNextSameKindEvent; /* 次の同じ種類のイベントへのポインタ(なければNULL) */
	struct tagMIDIEvent* m_pPrevSameKindEvent; /* 前の同じ種類のイベントへのポインタ(なければNULL) */
	struct tagMIDIEvent* m_pNextCombinedEvent; /* 次の結合イベント保持用ポインタ(なければNULL) */
	struct tagMIDIEvent* m_pPrevCombinedEvent; /* 前の結合イベント保持用ポインタ(なければNULL) */
	void* m_pParent;                    /* 親(MIDITrackオブジェクト)へのポインタ(なければNULL) */
	long m_lUser1;                      /* ユーザー用自由領域1(未使用) */
	long m_lUser2;                      /* ユーザー用自由領域2(未使用) */
	long m_lUser3;                      /* ユーザー用自由領域3(未使用) */
	long m_lUserFlag;                   /* ユーザー用自由領域4(未使用) */
} MIDIEvent;

/* MIDITrack構造体 */
/* 双方向リンクリスト構造 */
typedef struct tagMIDITrack {
	long m_lTempIndex;                  /* このトラックの一時的なインデックス(0から始まる) */
	long m_lNumEvent;                   /* トラック内のイベント数 */
	struct tagMIDIEvent* m_pFirstEvent; /* 最初のイベントへのポインタ(なければNULL) */
	struct tagMIDIEvent* m_pLastEvent;  /* 最後のイベントへのポインタ(なければNULL) */
	struct tagMIDITrack* m_pPrevTrack;  /* 前のトラックへのポインタ(なければNULL) */
	struct tagMIDITrack* m_pNextTrack;  /* 次のトラックへのポインタ(なければNULL) */
	void*  m_pParent;                   /* 親(MIDIDataオブジェクト)へのポインタ */
	long m_lInputOn;                    /* 入力(0=OFF, 1=On) */
	long m_lInputPort;                  /* 入力ポート(-1=n/a, 0～15=ポート番号) */
	long m_lInputChannel;               /* 入力チャンネル(-1=n/1, 0～15=チャンネル番号) */
	long m_lOutputOn;                   /* 出力(0=OFF, 1=On) */
	long m_lOutputPort;                 /* 出力ポート(-1=n/a, 0～15=ポート番号) */
	long m_lOutputChannel;              /* 出力チャンネル(-1=n/1, 0～15=チャンネル番号) */
	long m_lTimePlus;                   /* タイム+ */
	long m_lKeyPlus;                    /* キー+ */
	long m_lVelocityPlus;               /* ベロシティ+ */
	long m_lViewMode;                   /* 表示モード(0=通常、1=ドラム) */
	long m_lForeColor;                  /* 前景色 */
	long m_lBackColor;                  /* 背景色 */
	long m_lReserved1;                  /* 予約領域1(使用禁止) */
	long m_lReserved2;                  /* 予約領域2(使用禁止) */
	long m_lReserved3;                  /* 予約領域3(使用禁止) */
	long m_lReserved4;                  /* 予約領域4(使用禁止) */
	long m_lUser1;                      /* ユーザー用自由領域1(未使用) */
	long m_lUser2;                      /* ユーザー用自由領域2(未使用) */
	long m_lUser3;                      /* ユーザー用自由領域3(未使用) */
	long m_lUserFlag;                   /* ユーザー用自由領域4(未使用) */
} MIDITrack;

/* MIDIData構造体 */
/* 双方向リンクリスト構造 */
typedef struct tagMIDIData {
	unsigned long m_lFormat;            /* SMFフォーマット(0/1) */
	unsigned long m_lNumTrack;          /* トラック数(0～∞) */
	unsigned long m_lTimeBase;          /* タイムベース(例：120) */
	struct tagMIDITrack* m_pFirstTrack; /* 最初のトラックへのポインタ(なければNULL) */
	struct tagMIDITrack* m_pLastTrack;  /* 最後のトラックへのポインタ(なければNULL) */
	struct tagMIDITrack* m_pNextSeq;    /* 次のシーケンスへのポインタ(なければNULL) */
	struct tagMIDITrack* m_pPrevSeq;    /* 前のシーケンスへのポインタ(なければNULL) */
	void*  m_pParent;                   /* 親(常にNULL。将来ソングリストをサポート) */
	long m_lReserved1;                  /* 予約領域1(使用禁止) */
	long m_lReserved2;                  /* 予約領域2(使用禁止) */
	long m_lReserved3;                  /* 予約領域3(使用禁止) */
	long m_lReserved4;                  /* 予約領域4(使用禁止) */
	long m_lUser1;                      /* ユーザー用自由領域1(未使用) */
	long m_lUser2;                      /* ユーザー用自由領域2(未使用) */
	long m_lUser3;                      /* ユーザー用自由領域3(未使用) */
	long m_lUserFlag;                   /* ユーザー用自由領域4(未使用) */
} MIDIData;

/* その他のマクロ */
#define MIDIEVENT_MAXLEN       65536

/* フォーマットに関するマクロ */
#define MIDIDATA_FORMAT0       0x00 /* フォーマット0 */
#define MIDIDATA_FORMAT1       0x01 /* フォーマット1 */
#define MIDIDATA_FORMAT2       0x02 /* フォーマット2 */

/* テンポに関するマクロ */
/* 注意：テンポの単位はすべて[マイクロ秒/tick]とする。 */
#define MIDIEVENT_MAXTEMPO     (60000000)
#define MIDIEVENT_MINTEMPO     (1)
#define MIDIEVENT_DEFTEMPO     (60000000/120)

/* トラック数に関するマクロ */
#define MIDIDATA_MAXMIDITRACKNUM 65535

/* タイムモードに関するマクロ */
#define MIDIDATA_TPQNBASE      0  /* TPQNベース */
#define MIDIDATA_SMPTE24BASE   24 /* 24フレーム/秒 */
#define MIDIDATA_SMPTE25BASE   25 /* 25フレーム/秒 */
#define MIDIDATA_SMPTE29BASE   29 /* 29.97フレーム/秒 */
#define MIDIDATA_SMPTE30BASE   30 /* 30フレーム/秒 */

/* タイムレゾリューション(分解能)に関するマクロ */
/* TPQNベースの場合：4分音符あたりの分解能 */
/* ★注意：普通TPQNの分解能は、24,48,72,96,120,144,168,192,216,240,360,384,480,960である */
#define MIDIDATA_MINTPQNRESOLUTION   1   /* TPQNレゾリューション最小値=1 */
#define MIDIDATA_MAXTPQNRESOLUTION   32767 /* TPQNレゾリューション最大値=32767 */
#define MIDIDATA_DEFTPQNRESOLUTION   120 /* TPQNレゾリューション標準値=120 */

/* SMPTEベースの場合：1フレームあたりの分解能 */
/* ★注意：普通SMPTEの分解能は、10,40,80などが代表的である */
#define MIDIDATA_MINSMPTERESOLUTION  1   /* SMPTEレゾリューション最小値=1 */
#define MIDIDATA_MAXSMPTERESOLUTION  255 /* SMPTEレゾリューション最大値=255 */
#define MIDIDATA_DEFSMPTERESOLUTION  10  /* SMPTEレゾリューション標準値=10 */

/* 最大ポート数 */
#define MIDIDATA_MAXNUMPORT         256

/* SMPTEオフセットに関するマクロ */
#define MIDIEVENT_SMPTE24           0x00 /* 24フレーム／秒 */
#define MIDIEVENT_SMPTE25           0x01 /* 25フレーム／秒 */
#define MIDIEVENT_SMPTE30D          0x02 /* 30フレーム／秒(ドロップ) */
#define MIDIEVENT_SMPTE30N          0x03 /* 30フレーム／秒(ノンドロップ) */

/* 調性に関するマクロ */
#define MIDIEVENT_MAJOR             0x00 /* 長調 */
#define MIDIEVENT_MINOR             0x01 /* 短調 */

/* MIDIEVENT_KINDマクロ (コメントのカッコ内はデータ部の長さを示す) */
#define MIDIEVENT_SEQUENCENUMBER    0x00 /* シーケンスナンバー(2バイト) */
#define MIDIEVENT_TEXTEVENT         0x01 /* テキスト(可変長文字列) */
#define MIDIEVENT_COPYRIGHTNOTICE   0x02 /* 著作権(可変長文字列) */
#define MIDIEVENT_TRACKNAME         0x03 /* トラック名・シーケンサ名(可変長文字列) */
#define MIDIEVENT_INSTRUMENTNAME    0x04 /* インストゥルメント(可変長文字列) */
#define MIDIEVENT_LYRIC             0x05 /* 歌詞(可変長文字列) */
#define MIDIEVENT_MARKER            0x06 /* マーカー(可変長文字列) */
#define MIDIEVENT_CUEPOINT          0x07 /* キューポイント(可変長文字列) */
#define MIDIEVENT_PROGRAMNAME       0x08 /* プログラム名(可変長文字列) */
#define MIDIEVENT_DEVICENAME        0x09 /* デバイス名(可変長文字列) */
#define MIDIEVENT_CHANNELPREFIX     0x20 /* チャンネルプレフィックス(1バイト) */
#define MIDIEVENT_PORTPREFIX        0x21 /* ポートプレフィックス(1バイト) */
#define MIDIEVENT_ENDOFTRACK        0x2F /* エンドオブトラック(0バイト) */
#define MIDIEVENT_TEMPO             0x51 /* テンポ(3バイト) */
#define MIDIEVENT_SMPTEOFFSET       0x54 /* SMPTEオフセット(5バイト) */
#define MIDIEVENT_TIMESIGNATURE     0x58 /* 拍子記号(4バイト) */
#define MIDIEVENT_KEYSIGNATURE      0x59 /* 調性記号(2バイト) */
#define MIDIEVENT_SEQUENCERSPECIFIC 0x7F /* シーケンサー独自のイベント(可変長バイナリ) */
#define MIDIEVENT_NOTEOFF           0x80 /* ノートオフ(3バイト) */
#define MIDIEVENT_NOTEON            0x90 /* ノートオン(3バイト) */
#define MIDIEVENT_KEYAFTERTOUCH     0xA0 /* キーアフター(3バイト) */
#define MIDIEVENT_CONTROLCHANGE     0xB0 /* コントローラー(3バイト) */
#define MIDIEVENT_PROGRAMCHANGE     0xC0 /* プログラムチェンジ(2バイト) */
#define MIDIEVENT_CHANNELAFTERTOUCH 0xD0 /* チャンネルアフター(2バイト) */
#define MIDIEVENT_PITCHBEND         0xE0 /* ピッチベンド(3バイト) */
#define MIDIEVENT_SYSEXSTART        0xF0 /* システムエクスクルーシヴ(可変長バイナリ) */
#define MIDIEVENT_SYSEXCONTINUE     0xF7 /* システムエクスクルーシヴの続き(可変長バイナリ) */

/* MIDIEVENT_KINDマクロ (以下の4つはMIDIData_SetKindの引数に使われる) */
#define MIDIEVENT_NOTEONNOTEOFF     0x180 /* ノート(0x9n+0x8n) */
#define MIDIEVENT_NOTEONNOTEON0     0x190 /* ノート(0x9n+0x9n(vel==0)) */
#define MIDIEVENT_PATCHCHANGE       0x1C0 /* パッチチェンジ(CC#32+CC#0+プログラムチェンジ) */
#define MIDIEVENT_RPNCHANGE         0x1A0 /* RPNチェンジ(CC#101+CC#100+CC#6) */
#define MIDIEVENT_NRPNCHANGE        0x1B0 /* NRPNチェンジ(CC#99+CC#98+CC#6) */

/* MIDIEVENT_DUMPマクロ */
#define MIDIEVENT_DUMPALL           0x0000FFFF
#define MIDIEVENT_DUMPTIME          0x00000001
#define MIDIEVENT_DUMPKIND          0x00000010
#define MIDIEVENT_DUMPLEN           0x00000020
#define MIDIEVENT_DUMPDATA          0x00000040
#define MIDIEVENT_DUMPUSER1         0x00000100
#define MIDIEVENT_DUMPUSER2         0x00000200
#define MIDIEVENT_DUMPUSERFLAG      0x00000400

/* forEachTrackマクロ */
#define forEachTrack(pMIDIData, pTrack) \
for((pTrack)=(pMIDIData)->m_pFirstTrack;(pTrack);(pTrack)=(pTrack)->m_pNextTrack)

/* forEachTrackInverseマクロ */
#define forEachTrackInverse(pMIDIData, pTrack) \
for((pTrack)=(pMIDIData)->m_pLastTrack;(pTrack);(pTrack)=(pTrack)->m_pPrevTrack)


/* forEachEventマクロ */
#define forEachEvent(pTrack,pEvent) \
for((pEvent)=(pTrack)->m_pFirstEvent;(pEvent);(pEvent)=(pEvent)->m_pNextEvent)

/* forEachEventInverseマクロ */
#define forEachEventInverse(pTrack,pEvent) \
for((pEvent)=(pTrack)->m_pLastEvent;(pEvent);(pEvent)=(pEvent)->m_pPrevEvent)

/******************************************************************************/
/*                                                                            */
/*　MIDIDataLibクラス関数                                                     */
/*                                                                            */
/******************************************************************************/

/* ロケールの設定 */
char* __stdcall MIDIDataLib_SetLocaleA (int nCategory, const char *pszLocale);
wchar_t* __stdcall MIDIDataLib_SetLocaleW (int nCategory, const wchar_t* pszLocale);
#ifdef UNICODE
#define MIDIDataLib_SetLocale MIDIDataLib_SetLocaleW
#else
#define MIDIDataLib_SetLocale MIDIDataLib_SetLocaleA
#endif

/******************************************************************************/
/*                                                                            */
/*　MIDIEventクラス関数                                                       */
/*                                                                            */
/******************************************************************************/

/* 注：__stdcallはWindows専用です。Linuxの場合は__stdcallを消してください */

/* 結合イベントの最初のイベントを返す。 */
/* 結合イベントでない場合、pEvent自身を返す。*/
MIDIEvent* __stdcall MIDIEvent_GetFirstCombinedEvent (MIDIEvent* pEvent);

/* 結合イベントの最後のイベントを返す。 */
/* 結合イベントでない場合、pEvent自身を返す。*/
MIDIEvent* __stdcall MIDIEvent_GetLastCombinedEvent (MIDIEvent* pEvent);

/* 単体イベントを結合する */
long __stdcall MIDIEvent_Combine (MIDIEvent* pEvent);

/* 結合イベントを切り離す */
long __stdcall MIDIEvent_Chop (MIDIEvent* pEvent);

/* MIDIイベントの削除(結合している場合でも単一のMIDIイベントを削除) */
long __stdcall MIDIEvent_DeleteSingle (MIDIEvent* pMIDIEvent);

/* MIDIイベントの削除(結合している場合、結合しているMIDIイベントも削除) */
long __stdcall MIDIEvent_Delete (MIDIEvent* pMIDIEvent);

/* MIDIイベント(任意)を生成し、MIDIイベントへのポインタを返す(失敗時NULL、以下同様) */
MIDIEvent* __stdcall MIDIEvent_Create 
(long lTime, long lKind, unsigned char* pData, long lLen);

/* 指定イベントと同じMIDIイベントを生成し、MIDIイベントへのポインタを返す(失敗時NULL、以下同様) */
MIDIEvent* __stdcall MIDIEvent_CreateClone (MIDIEvent* pMIDIEvent);

/* シーケンス番号イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateSequenceNumber
(long lTime, long lNum);

/* テキストイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateTextEventA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateTextEventW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateTextEvent MIDIEvent_CreateTextEventW
#else
#define MIDIEvent_CreateTextEvent MIDIEvent_CreateTextEventA
#endif

/* 著作権イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateCopyrightNoticeA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateCopyrightNoticeW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateCopyrightNotice MIDIEvent_CreateCopyrightNoticeW
#else
#define MIDIEvent_CreateCopyrightNotice MIDIEvent_CreateCopyrightNoticeA
#endif

/* トラック名イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateTrackNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateTrackNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateTrackName MIDIEvent_CreateTrackNameW
#else
#define MIDIEvent_CreateTrackName MIDIEvent_CreateTrackNameA
#endif

/* インストゥルメント名イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateInstrumentNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateInstrumentNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateInstrumentName MIDIEvent_CreateInstrumentNameW
#else
#define MIDIEvent_CreateInstrumentName MIDIEvent_CreateInstrumentNameA
#endif

/* 歌詞イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateLyricA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateLyricW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateLyric MIDIEvent_CreateLyricW
#else
#define MIDIEvent_CreateLyric MIDIEvent_CreateLyricA
#endif

/* マーカーイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateMarkerA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateMarkerW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateMarker MIDIEvent_CreateMarkerW
#else
#define MIDIEvent_CreateMarker MIDIEvent_CreateMarkerA
#endif

/* キューポイントイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateCuePointA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateCuePointW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateCuePoint MIDIEvent_CreateCuePointW
#else
#define MIDIEvent_CreateCuePoint MIDIEvent_CreateCuePointA
#endif

/* プログラム名イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateProgramNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateProgramNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateProgramName MIDIEvent_CreateProgramNameW
#else
#define MIDIEvent_CreateProgramName MIDIEvent_CreateProgramNameA
#endif

/* デバイス名イベント生成 */
MIDIEvent* __stdcall MIDIEvent_CreateDeviceNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateDeviceNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateDeviceName MIDIEvent_CreateDeviceNameW
#else
#define MIDIEvent_CreateDeviceName MIDIEvent_CreateDeviceNameA
#endif

/* チャンネルプレフィックスイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateChannelPrefix (long lTime, long lCh);

/* ポートプレフィックスイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreatePortPrefix (long lTime, long lNum);

/* エンドオブトラックイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateEndofTrack (long lTime);

/* テンポイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateTempo (long lTime, long lTempo);

/* SMPTEオフセットイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateSMPTEOffset
(long lTime, long lMode, long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* 拍子記号イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateTimeSignature
(long lTime, long lnn, long ldd, long lcc, long lbb);

/* 調性記号イベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateKeySignature
(long lTime, long lsf, long lmi);

/* シーケンサー独自のイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateSequencerSpecific
(long lTime, char* pData, long lLen);

/* ノートオフイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOff 
(long lTime, long lCh, long lKey, long lVel);

/* ノートオンイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOn
(long lTime, long lCh, long lKey, long lVel);

/* ノートイベントの生成(MIDIEvent_CreateNoteOnNoteOn0と同じ) */
/* (ノートオン・ノートオン(0x9n(vel==0))の2イベントを生成し、*/
/* ノートオンイベントへのポインタを返す。) */
MIDIEvent* __stdcall MIDIEvent_CreateNote 
(long lTime, long lCh, long lKey, long lVel, long lDur);

/* ノートイベントの生成(0x8n離鍵型) */
/* (ノートオン(0x9n)・ノートオフ(0x8n)の2イベントを生成し、*/
/* NoteOnへのポインタを返す) */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOnNoteOff
(long lTime, long lCh, long lKey, long lVel1, long lVel2, long lDur);

/* ノートイベントの生成(0x9n離鍵型) */
/* (ノートオン(0x9n)・ノートオン(0x9n(vel==0))の2イベントを生成し、*/
/* NoteOnへのポインタを返す) */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOnNoteOn0
(long lTime, long lCh, long lKey, long lVel, long lDur);

/* キーアフタータッチイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateKeyAftertouch 
(long lTime, long lCh, long lKey, long lVal);

/* コントローラーイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateControlChange 
(long lTime, long lCh, long lNum, long lVal);

/* RPNイベントの生成 */
/* (CC#101+CC#100+CC#6の3イベントを生成し、CC#101へのポインタを返す) */
MIDIEvent* __stdcall MIDIEvent_CreateRPNChange
(long lTime, long lCh, long lCC101, long lCC100, long lVal);

/* NRPNイベントの生成 */
/* (CC#99+CC#98+CC#6の3イベントを生成し、CC#99へのポインタを返す) */
MIDIEvent* __stdcall MIDIEvent_CreateNRPNChange 
(long lTime, long lCh, long lCC99, long lCC98, long lVal);

/* プログラムチェンジイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateProgramChange 
(long lTime, long lCh, long lNum);

/* バンク・パッチイベントの生成 */
/* (CC#0+CC#32+PCの3イベントを生成し、CC#0へのポインタを返す) */
MIDIEvent* __stdcall MIDIEvent_CreatePatchChange 
(long lTime, long lCh, long lCC0, long lCC32, long lNum);

/* チャンネルアフタータッチイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateChannelAftertouch 
(long lTime, long lCh, long lVal);

/* ピッチベンドイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreatePitchBend 
(long lTime, long lCh, long lVal);

/* システムエクスクルーシヴイベントの生成 */
MIDIEvent* __stdcall MIDIEvent_CreateSysExEvent 
(long lTime, unsigned char* pBuf, long lLen);




/* メタイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsMetaEvent (MIDIEvent* pMIDIEvent);

/* シーケンス番号であるかどうかを調べる */
long __stdcall MIDIEvent_IsSequenceNumber (MIDIEvent* pMIDIEvent);

/* テキストイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsTextEvent (MIDIEvent* pMIDIEvent);

/* 著作権イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsCopyrightNotice (MIDIEvent* pMIDIEvent);

/* トラック名イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsTrackName (MIDIEvent* pMIDIEvent);

/* インストゥルメント名イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsInstrumentName (MIDIEvent* pMIDIEvent);

/* 歌詞イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsLyric (MIDIEvent* pMIDIEvent);

/* マーカーイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsMarker (MIDIEvent* pMIDIEvent);

/* キューポイントイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsCuePoint (MIDIEvent* pMIDIEvent);

/* プログラム名イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsProgramName (MIDIEvent* pEvent);

/* デバイス名イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsDeviceName (MIDIEvent* pEvent);

/* チャンネルプレフィックスイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsChannelPrefix (MIDIEvent* pEvent);

/* ポートプレフィックスイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsPortPrefix (MIDIEvent* pEvent);

/* エンドオブトラックイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsEndofTrack (MIDIEvent* pMIDIEvent);

/* テンポイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsTempo (MIDIEvent* pMIDIEvent);

/* SMPTEオフセットイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsSMPTEOffset (MIDIEvent* pMIDIEvent);

/* 拍子記号イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsTimeSignature (MIDIEvent* pMIDIEvent);

/* 調性記号イベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsKeySignature (MIDIEvent* pMIDIEvent);

/* シーケンサ独自のイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsSequencerSpecific (MIDIEvent* pMIDIEvent);


/* MIDIイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsMIDIEvent (MIDIEvent* pMIDIEvent);

/* ノートオンイベントであるかどうかを調べる */
/* (ノートオンイベントでベロシティ0のものはノートオフイベントとみなす。以下同様) */
long __stdcall MIDIEvent_IsNoteOn (MIDIEvent* pMIDIEvent);

/* ノートオフイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsNoteOff (MIDIEvent* pMIDIEvent);

/* ノートイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsNote (MIDIEvent* pMIDIEvent);

/* NOTEONOTEOFFイベントであるかどうかを調べる */
/* これはノートオン(0x9n)とノートオフ(0x8n)が結合イベントしたイベントでなければならない。 */
long __stdcall MIDIEvent_IsNoteOnNoteOff (MIDIEvent* pEvent);

/* NOTEONNOTEON0イベントであるかどうかを調べる */
/* これはノートオン(0x9n)とノートオフ(0x9n,vel==0)が結合イベントしたイベントでなければならない。 */
long __stdcall MIDIEvent_IsNoteOnNoteOn0 (MIDIEvent* pEvent);

/* キーアフタータッチイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsKeyAftertouch (MIDIEvent* pEvent);

/* コントロールチェンジイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsControlChange (MIDIEvent* pEvent);

/* RPNチェンジイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsRPNChange (MIDIEvent* pEvent);

/* NRPNチェンジイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsNRPNChange (MIDIEvent* pEvent);

/* プログラムチェンジイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsProgramChange (MIDIEvent* pEvent);

/* パッチチェンジイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsPatchChange (MIDIEvent* pEvent);

/* チャンネルアフタータッチイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsChannelAftertouch (MIDIEvent* pEvent);

/* ピッチベンドイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsPitchBend (MIDIEvent* pEvent);

/* システムエクスクルーシヴイベントであるかどうかを調べる */
long __stdcall MIDIEvent_IsSysExEvent (MIDIEvent* pMIDIEvent);

/* 浮遊イベントであるかどうか調べる */
long __stdcall MIDIEvent_IsFloating (MIDIEvent* pEvent);

/* 結合イベントであるかどうか調べる */
long __stdcall MIDIEvent_IsCombined (MIDIEvent* pEvent);


/* イベントの種類を取得 */
long __stdcall MIDIEvent_GetKind (MIDIEvent* pEvent);

/* イベントの種類を設定 */
long __stdcall MIDIEvent_SetKind (MIDIEvent* pEvent, long lKind);

/* イベントの長さ取得 */
long __stdcall MIDIEvent_GetLen (MIDIEvent* pEvent);

/* イベントのデータ部を取得 */
long __stdcall MIDIEvent_GetData (MIDIEvent* pEvent, unsigned char* pBuf, long lLen);

/* イベントのデータ部を設定(この関数は大変危険です。整合性のチェキはしません) */
long __stdcall MIDIEvent_SetData (MIDIEvent* pEvent, unsigned char* pBuf, long lLen);

/* イベントのテキストを取得(テキスト・著作権・トラック名・インストゥルメント名・ */
/* 歌詞・マーカー・キューポイント・プログラム名・デバイス名のみ) */
char* __stdcall MIDIEvent_GetTextA (MIDIEvent* pEvent, char* pBuf, long lLen);
wchar_t* __stdcall MIDIEvent_GetTextW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDIEvent_GetText MIDIEvent_GetTextW
#else
#define MIDIEvent_GetText MIDIEvent_GetTextA
#endif

/* イベントのテキストを設定(テキスト・著作権・トラック名・インストゥルメント名・ */
/* 歌詞・マーカー・キューポイント・プログラム名・デバイス名のみ) */
long __stdcall MIDIEvent_SetTextA (MIDIEvent* pEvent, const char* pszText);
long __stdcall MIDIEvent_SetTextW (MIDIEvent* pEvent, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_SetText MIDIEvent_SetTextW
#else
#define MIDIEvent_SetText MIDIEvent_SetTextA
#endif

/* SMPTEオフセットの取得(SMPTEオフセットイベントのみ) */
long __stdcall MIDIEvent_GetSMPTEOffset 
(MIDIEvent* pEvent, long* pMode, long* pHour, long* pMin, long* pSec, long* pFrame, long* pSubFrame);

/* SMPTEオフセットの設定(SMPTEオフセットイベントのみ) */
long __stdcall MIDIEvent_SetSMPTEOffset 
(MIDIEvent* pEvent, long lMode, long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* テンポ取得(テンポイベントのみ) */
long __stdcall MIDIEvent_GetTempo (MIDIEvent* pEvent);

/* テンポ設定(テンポイベントのみ) */
long __stdcall MIDIEvent_SetTempo (MIDIEvent* pEvent, long lTempo);

/* 拍子記号取得(拍子記号イベントのみ) */
long __stdcall MIDIEvent_GetTimeSignature 
(MIDIEvent* pEvent, long* lnn, long* ldd, long* lcc, long* bb);

/* 拍子記号の設定(拍子記号イベントのみ) */
long __stdcall MIDIEvent_SetTimeSignature 
(MIDIEvent* pEvent, long lnn, long ldd, long lcc, long lbb);

/* 調性記号の取得(調性記号イベントのみ) */
long __stdcall MIDIEvent_GetKeySignature (MIDIEvent* pEvent, long* psf, long* pmi);

/* 調性記号の設定(調性記号イベントのみ) */
long __stdcall MIDIEvent_SetKeySignature (MIDIEvent* pEvent, long lsf, long lmi);

/* イベントのメッセージ取得(MIDIチャンネルイベント及びシステムエクスクルーシヴのみ) */
long __stdcall MIDIEvent_GetMIDIMessage (MIDIEvent* pEvent, char* pMessage, long lLen);

/* イベントのメッセージ設定(MIDIチャンネルイベント及びシステムエクスクルーシヴのみ) */
long __stdcall MIDIEvent_SetMIDIMessage (MIDIEvent* pEvent, char* pMessage, long lLen);

/* イベントのチャンネル取得(MIDIチャンネルイベントのみ) */
long __stdcall MIDIEvent_GetChannel (MIDIEvent* pEvent);

/* イベントのチャンネル設定(MIDIチャンネルイベントのみ) */
long __stdcall MIDIEvent_SetChannel (MIDIEvent* pEvent, long lCh);

/* イベントの時刻取得 */
long __stdcall MIDIEvent_GetTime (MIDIEvent* pEvent);

/* イベントの時刻設定 */
long __stdcall MIDIEvent_SetTimeSingle (MIDIEvent* pEvent, long lTime);

/* イベントの時刻設定 */
long __stdcall MIDIEvent_SetTime (MIDIEvent* pEvent, long lTime);

/* イベントのキー取得(ノートオフ・ノートオン・チャンネルアフターのみ) */
long __stdcall MIDIEvent_GetKey (MIDIEvent* pEvent);

/* イベントのキー設定(ノートオフ・ノートオン・チャンネルアフターのみ) */
long __stdcall MIDIEvent_SetKey (MIDIEvent* pEvent, long lKey);

/* イベントのベロシティ取得(ノートオフ・ノートオンのみ) */
long __stdcall MIDIEvent_GetVelocity (MIDIEvent* pEvent);

/* イベントのベロシティ設定(ノートオフ・ノートオンのみ) */
long __stdcall MIDIEvent_SetVelocity (MIDIEvent* pEvent, long cVel);

/* 結合イベントの音長さ取得(ノートのみ) */
long __stdcall MIDIEvent_GetDuration (MIDIEvent* pEvent);

/* 結合イベントの音長さ設定(ノートのみ) */
long __stdcall MIDIEvent_SetDuration (MIDIEvent* pEvent, long lDuration);

/* 結合イベントのバンク取得(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_GetBank (MIDIEvent* pEvent);

/* 結合イベントのバンク上位(MSB)取得(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_GetBankMSB (MIDIEvent* pEvent);

/* 結合イベントのバンク下位(LSB)取得(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_GetBankLSB (MIDIEvent* pEvent);

/* 結合イベントのバンク設定(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_SetBank (MIDIEvent* pEvent, long lBank);

/* 結合イベントのバンク上位(MSB)設定(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_SetBankMSB (MIDIEvent* pEvent, long lBankMSB);

/* 結合イベントのバンク下位(LSB)設定(RPNチェンジ・NRPNチェンジ・パッチチェンジのみ) */
long __stdcall MIDIEvent_SetBankLSB (MIDIEvent* pEvent, long lBankLSB);

/* イベントの番号取得(コントロールチェンジ・プログラムチェンジのみ) */
long __stdcall MIDIEvent_GetNumber (MIDIEvent* pEvent);

/* イベントの番号設定(コントロールチェンジ・プログラムチェンジのみ) */
long __stdcall MIDIEvent_SetNumber (MIDIEvent* pEvent, long cNum);

/* イベントの値取得(キーアフター・コントローラー・チャンネルアフター・ピッチベンド) */
long __stdcall MIDIEvent_GetValue (MIDIEvent* pEvent);

/* イベントの値設定(キーアフター・コントローラー・チャンネルアフター・ピッチベンド) */
long __stdcall MIDIEvent_SetValue (MIDIEvent* pEvent, long nVal);

/* 次のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDIEvent_GetNextEvent (MIDIEvent* pMIDIEvent);

/* 前のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDIEvent_GetPrevEvent (MIDIEvent* pMIDIEvent);

/* 次の同種のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDIEvent_GetNextSameKindEvent (MIDIEvent* pMIDIEvent);

/* 前の同種のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDIEvent_GetPrevSameKindEvent (MIDIEvent* pMIDIEvent);

/* 親トラックへのポインタを取得(なければNULL) */
MIDITrack* __stdcall MIDIEvent_GetParent (MIDIEvent* pMIDIEvent);

/* イベントの内容を文字列表現に変換 */
char* __stdcall MIDIEvent_ToStringExA (MIDIEvent* pEvent, char* pBuf, long lLen, long lFlags);
wchar_t* __stdcall MIDIEvent_ToStringExW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen, long lFlags);
#ifdef UNICODE
#define MIDIEvent_ToStringEx MIDIEvent_ToStringExW
#else
#define MIDIEvent_ToStringEx MIDIEvent_ToStringExA
#endif

/* イベンの内容トを文字列表現に変換 */
char* __stdcall MIDIEvent_ToStringA (MIDIEvent* pEvent, char* pBuf, long lLen);
wchar_t* __stdcall MIDIEvent_ToStringW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDIEvent_ToString MIDIEvent_ToStringW
#else
#define MIDIEvent_ToString MIDIEvent_ToStringA
#endif


/******************************************************************************/
/*                                                                            */
/*　MIDITrackクラス関数                                                       */
/*                                                                            */
/******************************************************************************/

/* トラック内のイベントの総数を取得 */
long __stdcall MIDITrack_GetNumEvent (MIDITrack* pMIDITrack);

/* トラックの最初のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDITrack_GetFirstEvent (MIDITrack* pMIDITrack);

/* トラックの最後のイベントへのポインタを取得(なければNULL) */
MIDIEvent* __stdcall MIDITrack_GetLastEvent (MIDITrack* pMIDITrack);

/* トラック内の指定種類の最初のイベント取得(なければNULL) */
MIDIEvent* __stdcall MIDITrack_GetFirstKindEvent (MIDITrack* pTrack, long lKind);

/* トラック内の指定種類の最後のイベント取得(なければNULL) */
MIDIEvent* __stdcall MIDITrack_GetLastKindEvent (MIDITrack* pTrack, long lKind);

/* 次のMIDIトラックへのポインタ取得(なければNULL)(20080715追加) */
MIDITrack* __stdcall MIDITrack_GetNextTrack (MIDITrack* pTrack);

/* 前のMIDIトラックへのポインタ取得(なければNULL)(20080715追加) */
MIDITrack* __stdcall MIDITrack_GetPrevTrack (MIDITrack* pTrack);

/* トラックの親MIDIデータへのポインタを取得(なければNULL) */
MIDIData* __stdcall MIDITrack_GetParent (MIDITrack* pMIDITrack);

/* トラック内のイベント数をカウントし、各イベントのインデックスと総イベント数を更新し、イベント数を返す。 */
long __stdcall MIDITrack_CountEvent (MIDITrack* pMIDITrack);

/* トラックの開始時刻(最初のイベントの時刻)[Tick]を取得(20081101追加) */
long __stdcall MIDITrack_GetBeginTime (MIDITrack* pMIDITrack);

/* トラックの終了時刻(最後のイベントの時刻)[Tick]を取得(20081101追加) */
long __stdcall MIDITrack_GetEndTime (MIDITrack* pMIDITrack);

/* トラックの名前を簡易に取得 */
char* __stdcall MIDITrack_GetNameA (MIDITrack* pMIDITrack, char* pBuf, long lLen);
wchar_t* __stdcall MIDITrack_GetNameW (MIDITrack* pMIDITrack, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDITrack_GetName MIDITrack_GetNameW
#else
#define MIDITrack_GetName MIDITrack_GetNameA
#endif

/* 入力取得(0=OFF, 1=On) */
long __stdcall MIDITrack_GetInputOn (MIDITrack* pTrack);

/* 入力ポート取得(-1=n/a, 0～15=ポート番号) */
long __stdcall MIDITrack_GetInputPort (MIDITrack* pTrack);

/* 入力チャンネル取得(-1=n/a, 0～15=チャンネル番号) */
long __stdcall MIDITrack_GetInputChannel (MIDITrack* pTrack);

/* 出力取得(0=OFF, 1=On) */
long __stdcall MIDITrack_GetOutputOn (MIDITrack* pTrack);

/* 出力ポート(-1=n/a, 0～15=ポート番号) */
long __stdcall MIDITrack_GetOutputPort (MIDITrack* pTrack);

/* 出力チャンネル(-1=n/a, 0～15=チャンネル番号) */
long __stdcall MIDITrack_GetOutputChannel (MIDITrack* pTrack);

/* タイム+取得 */
long __stdcall MIDITrack_GetTimePlus (MIDITrack* pTrack);

/* キー+取得 */
long __stdcall MIDITrack_GetKeyPlus (MIDITrack* pTrack);

/* ベロシティ+取得 */
long __stdcall MIDITrack_GetVelocityPlus (MIDITrack* pTrack);

/* 表示モード取得(0=通常、1=ドラム) */
long __stdcall MIDITrack_GetViewMode (MIDITrack* pTrack);

/* 前景色取得 */
long __stdcall MIDITrack_GetForeColor (MIDITrack* pTrack);

/* 背景色取得 */
long __stdcall MIDITrack_GetBackColor (MIDITrack* pTrack);


/* トラックの名前を簡易に設定 */
long __stdcall MIDITrack_SetNameA (MIDITrack* pMIDITrack, const char* pszText);
long __stdcall MIDITrack_SetNameW (MIDITrack* pMIDITrack, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_SetName MIDITrack_SetNameW
#else
#define MIDITrack_SetName MIDITrack_SetNameA
#endif

/* 入力設定(0=OFF, 1=On) */
long __stdcall MIDITrack_SetInputOn (MIDITrack* pTrack, long lInputOn);

/* 入力ポート設定(-1=n/a, 0～15=ポート番号) */
long __stdcall MIDITrack_SetInputPort (MIDITrack* pTrack, long lInputPort);

/* 入力チャンネル設定(-1=n/a, 0～15=チャンネル番号) */
long __stdcall MIDITrack_SetInputChannel (MIDITrack* pTrack, long lInputChannel);

/* 出力設定(0=OFF, 1=On) */
long __stdcall MIDITrack_SetOutputOn (MIDITrack* pTrack, long lOutputOn);

/* 出力ポート(-1=n/a, 0～15=ポート番号) */
long __stdcall MIDITrack_SetOutputPort (MIDITrack* pTrack, long lOutputPort);

/* 出力チャンネル(-1=n/a, 0～15=チャンネル番号) */
long __stdcall MIDITrack_SetOutputChannel (MIDITrack* pTrack, long lOutputChannel);

/* タイム+設定 */
long __stdcall MIDITrack_SetTimePlus (MIDITrack* pTrack, long lTimePlus);

/* キー+設定 */
long __stdcall MIDITrack_SetKeyPlus (MIDITrack* pTrack, long lKeyPlus);

/* ベロシティ+設定 */
long __stdcall MIDITrack_SetVelocityPlus (MIDITrack* pTrack, long lVelocityPlus);

/* 表示モード設定(0=通常、1=ドラム) */
long __stdcall MIDITrack_SetViewMode (MIDITrack* pTrack, long lMode);

/* 前景色設定 */
long __stdcall MIDITrack_SetForeColor (MIDITrack* pTrack, long lForeColor);

/* 背景色設定 */
long __stdcall MIDITrack_SetBackColor (MIDITrack* pTrack, long lBackColor);

/* XFであるとき、XFのヴァージョンを取得(XFでなければ0) */
long __stdcall MIDITrack_GetXFVersion (MIDITrack* pMIDITrack);

/* トラックの削除(含まれるイベントオブジェクトも削除されます) */
void __stdcall MIDITrack_Delete (MIDITrack* pMIDITrack);

/* トラックを生成し、トラックへのポインタを返す(失敗時NULL) */
MIDITrack* __stdcall MIDITrack_Create ();

/* MIDIトラックのクローンを生成 */
MIDITrack* __stdcall MIDITrack_CreateClone (MIDITrack* pTrack);

/* トラックにイベントを挿入(イベントはあらかじめ生成しておく) */
long __stdcall MIDITrack_InsertSingleEventAfter 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* トラックにイベントを挿入(イベントはあらかじめ生成しておく) */
long __stdcall MIDITrack_InsertSingleEventBefore 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* トラックにイベントを挿入(イベントはあらかじめ生成しておく) */
long __stdcall MIDITrack_InsertEventAfter 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* トラックにイベントを挿入(イベントはあらかじめ生成しておく) */
long __stdcall MIDITrack_InsertEventBefore 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* トラックにイベントを挿入(イベントはあらかじめ生成しておく) */
long __stdcall MIDITrack_InsertEvent (MIDITrack* pMIDITrack, MIDIEvent* pEvent);

/* トラックにシーケンス番号イベントを生成して挿入 */
long __stdcall MIDITrack_InsertSequenceNumber
(MIDITrack* pMIDITrack, long lTime, long lNum);

/* トラックにテキストイベントを生成して挿入 */
long __stdcall MIDITrack_InsertTextEventA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertTextEventW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertTextEvent MIDITrack_InsertTextEventW
#else
#define MIDITrack_InsertTextEvent MIDITrack_InsertTextEventA
#endif

/* トラックに著作権イベントを生成して挿入 */
long __stdcall MIDITrack_InsertCopyrightNoticeA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertCopyrightNoticeW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertCopyrightNotice MIDITrack_InsertCopyrightNoticeW
#else
#define MIDITrack_InsertCopyrightNotice MIDITrack_InsertCopyrightNoticeA
#endif

/* トラックにトラック名イベントを生成して挿入 */
long __stdcall MIDITrack_InsertTrackNameA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertTrackNameW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertTrackName MIDITrack_InsertTrackNameW
#else
#define MIDITrack_InsertTrackName MIDITrack_InsertTrackNameA
#endif

/* トラックにインストゥルメント名イベントを生成して挿入 */
long __stdcall MIDITrack_InsertInstrumentNameA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertInstrumentNameW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertInstrumentName MIDITrack_InsertInstrumentNameW
#else
#define MIDITrack_InsertInstrumentName MIDITrack_InsertInstrumentNameA
#endif

/* トラックに歌詞イベントを生成して挿入 */
long __stdcall MIDITrack_InsertLyricA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertLyricW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertLyric MIDITrack_InsertLyricW
#else
#define MIDITrack_InsertLyric MIDITrack_InsertLyricA
#endif

/* トラックにマーカーイベントを生成して挿入 */
long __stdcall MIDITrack_InsertMarkerA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertMarkerW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertMarker MIDITrack_InsertMarkerW
#else
#define MIDITrack_InsertMarker MIDITrack_InsertMarkerA
#endif

/* トラックにキューポイントイベントを生成して挿入 */
long __stdcall MIDITrack_InsertCuePointA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertCuePointW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertCuePoint MIDITrack_InsertCuePointW
#else
#define MIDITrack_InsertCuePoint MIDITrack_InsertCuePointA
#endif

/* トラックにプログラム名イベントを生成して挿入 */
long __stdcall MIDITrack_InsertProgramNameA
(MIDITrack* pTrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertProgramNameW
(MIDITrack* pTrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertProgramName MIDITrack_InsertProgramNameW
#else
#define MIDITrack_InsertProgramName MIDITrack_InsertProgramNameA
#endif

/* トラックにデバイス名イベントを生成して挿入 */
long __stdcall MIDITrack_InsertDeviceNameA
(MIDITrack* pTrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertDeviceNameW
(MIDITrack* pTrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertDeviceName MIDITrack_InsertDeviceNameW
#else
#define MIDITrack_InsertDeviceName MIDITrack_InsertDeviceNameA
#endif

/* トラックにチャンネルプレフィックスイベントを生成して挿入 */
long __stdcall MIDITrack_InsertChannelPrefix (MIDITrack* pTrack, long lTime, long lCh);

/* トラックにポートプレフィックスイベントを生成して挿入 */
long __stdcall MIDITrack_InsertPortPrefix (MIDITrack* pTrack, long lTime, long lPort);

/* トラックにエンドオブトラックイベントを生成して挿入 */
long __stdcall MIDITrack_InsertEndofTrack
(MIDITrack* pMIDITrack, long lTime);

/* トラックにテンポイベントを生成して挿入 */
long __stdcall MIDITrack_InsertTempo
(MIDITrack* pMIDITrack, long lTime, long lTempo);

/* トラックにSMPTEオフセットイベントを生成して挿入 */
long MIDITrack_InsertSMPTEOffset 
(MIDITrack* pTrack, long lTime, long lMode, 
 long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* トラックに拍子記号イベントを生成して挿入 */
long __stdcall MIDITrack_InsertTimeSignature
(MIDITrack* pMIDITrack, long lTime, long lnn, long ldd, long lcc, long lbb);

/* トラックに調性記号イベントを生成して挿入 */
long __stdcall MIDITrack_InsertKeySignature
(MIDITrack* pMIDITrack, long lTime, long lsf, long lmi);

/* トラックにシーケンサー独自のイベントを生成して挿入 */
long __stdcall MIDITrack_InsertSequencerSpecific
(MIDITrack* pMIDITrack, long lTime, char* pBuf, long lLen);

/* トラックにノートオフイベントを生成して挿入 */
long __stdcall MIDITrack_InsertNoteOff 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel);

/* トラックにノートオンイベントを生成して挿入 */
long __stdcall MIDITrack_InsertNoteOn 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel);

/* トラックにノートイベントを生成して挿入 */
long __stdcall MIDITrack_InsertNote
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel, long lDur);

/* トラックにキーアフタータッチイベントを生成して挿入 */
long __stdcall MIDITrack_InsertKeyAftertouch
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVal);

/* トラックにコントロールチェンジイベントを生成して挿入 */
long __stdcall MIDITrack_InsertControlChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lNum, long lVal);

/* トラックにRPNチェンジイベントを生成して挿入 */
long __stdcall MIDITrack_InsertRPNChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC101, long lCC100, long lVal);

/* トラックにNRPNチェンジイベントを生成して挿入 */
long __stdcall MIDITrack_InsertNRPNChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC99, long lCC98, long lVal);

/* トラックにプログラムチェンジイベントを生成して挿入 */
long __stdcall MIDITrack_InsertProgramChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lNum);

/* トラックにパッチチェンジイベントを生成して挿入 */
long __stdcall MIDITrack_InsertPatchChange 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC0, long lCC32, long lNum);

/* トラックにチャンネルアフターイベントを生成して挿入 */
long __stdcall MIDITrack_InsertChannelAftertouch 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lVal);

/* トラックにピッチベンドイベントを生成して挿入 */
long __stdcall MIDITrack_InsertPitchBend 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lVal);

/* トラックにシステムエクスクルーシヴイベントを生成して挿入 */
long __stdcall MIDITrack_InsertSysExEvent 
	(MIDITrack* pMIDITrack, long lTime, unsigned char* pBuf, long lLen);

/* トラックからイベントを1つ取り除く(イベントオブジェクトは削除しません) */
long __stdcall MIDITrack_RemoveSingleEvent (MIDITrack* pTrack, MIDIEvent* pEvent);

/* トラックからイベントを取り除く(イベントオブジェクトは削除しません) */
long __stdcall MIDITrack_RemoveEvent (MIDITrack* pMIDITrack, MIDIEvent* pEvent);


/* MIDIトラックが浮遊トラックであるかどうかを調べる */
long __stdcall MIDITrack_IsFloating (MIDITrack* pMIDITrack);


/* MIDIトラックがセットアップトラックとして正しいことを確認する */
long __stdcall MIDITrack_CheckSetupTrack (MIDITrack* pMIDITrack);

/* MIDIトラックがノンセットアップトラックとして正しいことを確認する */
long __stdcall MIDITrack_CheckNonSetupTrack (MIDITrack* pMIDITrack);

/* タイムコードをミリ秒時刻に変換(指定トラック内のテンポイベントを基に計算) */
long __stdcall MIDITrack_TimeToMillisec (MIDITrack* pMIDITrack, long lTime);

/* ミリ秒時刻をタイムコードに変換(指定トラック内のテンポイベントを基に計算) */
long __stdcall MIDITrack_MillisecToTime (MIDITrack* pMIDITrack, long lMillisec);

/* タイムコードを小節：拍：ティックに分解(指定トラック内の拍子記号を基に計算) */
long __stdcall MIDITrack_BreakTimeEx
	(MIDITrack* pMIDITrack, long lTime, long* pMeasure, long* pBeat, long* pTick,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* タイムコードを小節：拍：ティックに分解(指定トラック内の拍子記号を基に計算) */
long __stdcall MIDITrack_BreakTime 
	(MIDITrack* pMIDITrack, long lTime, long* pMeasure, long* pBeat, long* pTick);

/* 小節：拍：ティックからタイムコードを生成(指定トラック内の拍子記号を基に計算) */
long __stdcall MIDITrack_MakeTimeEx 
	(MIDITrack* pMIDITrack, long lMeasure, long lBeat, long lTick, long* pTime,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* 小節：拍：ティックからタイムコードを生成(指定トラック内の拍子記号を基に計算) */
long __stdcall MIDITrack_MakeTime 
	(MIDITrack* pMIDITrack, long lMeasure, long lBeat, long lTick, long* pTime);

/* 指定位置におけるテンポを取得 */
long __stdcall MIDITrack_FindTempo
(MIDITrack* pMIDITrack, long lTime, long* pTempo);

/* 指定位置における拍子記号を取得 */
long __stdcall MIDITrack_FindTimeSignature 
(MIDITrack* pMIDITrack, long lTime, long* pnn, long* pdd, long* pcc, long* pbb);

/* 指定位置における調性記号を取得 */
long __stdcall MIDITrack_FindKeySignature 
(MIDITrack* pMIDITrack, long lTime, long* psf, long* pmi);




/******************************************************************************/
/*                                                                            */
/*　MIDIDataクラス関数                                                        */
/*                                                                            */
/******************************************************************************/

/* MIDIデータの指定トラックの直前にトラックを挿入 */
long __stdcall MIDIData_InsertTrackBefore 
(MIDIData* pMIDIData, MIDITrack* pMIDITrack, MIDITrack* pTarget);

/* MIDIデータの指定トラックの直後にトラックを挿入 */
long __stdcall MIDIData_InsertTrackAfter 
(MIDIData* pMIDIData, MIDITrack* pMIDITrack, MIDITrack* pTarget);

/* MIDIデータにトラックを追加(トラックは予め生成しておく) */
long __stdcall MIDIData_AddTrack (MIDIData* pMIDIData, MIDITrack* pMIDITrack);

/* MIDIデータ内のトラックを複製する */
long __stdcall MIDIData_DuplicateTrack (MIDIData* pMIDIData, MIDITrack* pTrack);

/* MIDIデータからトラックを除去(トラック自体及びトラック内のイベントは削除しない) */
long __stdcall MIDIData_RemoveTrack (MIDIData* pMIDIData, MIDITrack* pMIDITrack);

/* MIDIデータの削除(含まれるトラック及びイベントもすべて削除) */
void __stdcall MIDIData_Delete (MIDIData* pMIDIData);

/* MIDIデータを生成し、MIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_Create (long lFormat, long lNumTrack, long lTimeMode, long lResolution);

/* MIDIデータのフォーマット0/1/2を取得 */
long __stdcall MIDIData_GetFormat (MIDIData* pMIDIData);

/* MIDIデータのフォーマット0/1/2を設定(変更時コンバート機能を含む) */
long __stdcall MIDIData_SetFormat (MIDIData* pMIDIData, long lFormat);

/* MIDIデータのタイムベース取得 */
long __stdcall MIDIData_GetTimeBase (MIDIData* pMIDIData, long* pMode, long* pResolution);

/* MIDIデータのタイムベースのタイムモード取得 */
long __stdcall MIDIData_GetTimeMode (MIDIData* pMIDIData);

/* MIDIデータのタイムベースのレゾリューション取得 */
long __stdcall MIDIData_GetTimeResolution (MIDIData* pMIDIData);

/* MIDIデータのタイムベース設定 */
long __stdcall MIDIData_SetTimeBase (MIDIData* pMIDIData, long lMode, long lResolution);

/* MIDIデータのトラック数取得 */
long __stdcall MIDIData_GetNumTrack (MIDIData* pMIDIData);

/* トラック数をカウントし、各トラックのインデックスと総トラック数を更新し、トラック数を返す。 */
long __stdcall MIDIData_CountTrack (MIDIData* pMIDIData);

/* XFであるとき、XFのヴァージョンを取得(XFでなければ0) */
long __stdcall MIDIData_GetXFVersion (MIDIData* pMIDIData);

/* MIDIデータの最初のトラックへのポインタを取得(なければNULL) */
MIDITrack* __stdcall MIDIData_GetFirstTrack (MIDIData* pMIDIData);

/* MIDIデータの最後のトラックへのポインタを取得(なければNULL) */
MIDITrack* __stdcall MIDIData_GetLastTrack (MIDIData* pMIDIData);

/* 指定インデックスのMIDIトラックへのポインタを取得する(なければNULL) */
MIDITrack* __stdcall MIDIData_GetTrack (MIDIData* pMIDIData, long lTrackIndex);

/* MIDIデータの開始時刻[Tick]を取得 */
long __stdcall MIDIData_GetBeginTime (MIDIData* pMIDIData);

/* MIDIデータの終了時刻[Tick]を取得 */
long __stdcall MIDIData_GetEndTime (MIDIData* pMIDIData);

/* MIDIデータのタイトルを簡易取得 */
char* __stdcall MIDIData_GetTitleA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetTitleW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetTitle MIDIData_GetTitleW
#else
#define MIDIData_GetTitle MIDIData_GetTitleA
#endif

/* MIDIデータのタイトルを簡易設定 */
long __stdcall MIDIData_SetTitleA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetTitleW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetTitle MIDIData_SetTitleW
#else
#define MIDIData_SetTitle MIDIData_SetTitleA
#endif

/* MIDIデータのサブタイトルを簡易取得 */
char* __stdcall MIDIData_GetSubTitleA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetSubTitleW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetSubTitle MIDIData_GetSubTitleW
#else
#define MIDIData_GetSubTitle MIDIData_GetSubTitleA
#endif

/* MIDIデータのサブタイトルを簡易設定 */
long __stdcall MIDIData_SetSubTitleA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetSubTitleW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetSubTitle MIDIData_SetSubTitleW
#else
#define MIDIData_SetSubTitle MIDIData_SetSubTitleA
#endif

/* MIDIデータの著作権を簡易取得 */
char* __stdcall MIDIData_GetCopyrightA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetCopyrightW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetCopyright MIDIData_GetCopyrightW
#else
#define MIDIData_GetCopyright MIDIData_GetCopyrightA
#endif

/* MIDIデータの著作権を簡易設定 */
long __stdcall MIDIData_SetCopyrightA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetCopyrightW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetCopyright MIDIData_SetCopyrightW
#else
#define MIDIData_SetCopyright MIDIData_SetCopyrightA
#endif

/* MIDIデータのコメントを簡易取得 */
char* __stdcall MIDIData_GetCommentA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetCommentW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetComment MIDIData_GetCommentW
#else
#define MIDIData_GetComment MIDIData_GetCommentA
#endif

/* MIDIデータのコメントを簡易設定 */
long __stdcall MIDIData_SetCommentA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetCommentW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetComment MIDIData_SetCommentW
#else
#define MIDIData_SetComment MIDIData_SetCommentA
#endif

/* タイムコードをミリ秒に変換(フォーマット0/1の場合のみ) */
long __stdcall MIDIData_TimeToMillisec (MIDIData* pMIDIData, long lTime);

/* ミリ秒をタイムコードに変換(フォーマット0/1の場合のみ) */
long __stdcall MIDIData_MillisecToTime (MIDIData* pMIDIData, long lMillisec);

/* タイムコードを小節：拍：ティックに分解(最初のトラック内の拍子記号から計算) */
long __stdcall MIDIData_BreakTime 
	(MIDIData* pMIDIData, long lTime, long* pMeasure, long* pBeat, long* pTick);

/* タイムコードを小節：拍：ティックに分解(最初のトラック内の拍子記号を基に計算) */
long __stdcall MIDIData_BreakTimeEx
	(MIDIData* pMIDIData, long lTime, long* pMeasure, long* pBeat, long* pTick,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* 小節：拍：ティックからタイムコードを生成(最初のトラック内の拍子記号から計算) */
long __stdcall MIDIData_MakeTime
	(MIDIData* pMIDIData, long lMeasure, long lBeat, long lTick, long* pTime);

/* 小節：拍：ティックからタイムコードを生成(最初のトラック内の拍子記号を基に計算) */
long __stdcall MIDIData_MakeTimeEx
	(MIDIData* pMIDIData, long lMeasure, long lBeat, long lTick, long* pTime,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* 指定位置におけるテンポを取得 */
long __stdcall MIDIData_FindTempo
	(MIDIData* pMIDIData, long lTime, long* pTempo);

/* 指定位置における拍子記号を取得 */
long __stdcall MIDIData_FindTimeSignature 
	(MIDIData* pMIDIData, long lTime, long* pnn, long* pdd, long* pcc, long* pbb);

/* 指定位置における調性記号を取得 */
long __stdcall MIDIData_FindKeySignature 
	(MIDIData* pMIDIData, long lTime, long* psf, long* pmi);

/* このMIDIデータに別のMIDIデータをマージする(20080715廃止) */
/*long __stdcall MIDIData_Merge (MIDIData* pMIDIData, MIDIData* pMergeData, */
/*	long lTime, long lFlags, long* pInsertedEventCount, long* pDeletedEventCount);*/

/* 保存・読み込み用関数 */

/* MIDIDataをスタンダードMIDIファイル(SMF)から読み込み、*/
/* 新しいMIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_LoadFromSMFA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromSMFW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromSMF MIDIData_LoadFromSMFW
#else
#define MIDIData_LoadFromSMF MIDIData_LoadFromSMFA
#endif

/* MIDIデータをスタンダードMIDIファイル(SMF)として保存 */
long __stdcall MIDIData_SaveAsSMFA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsSMFW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsSMF MIDIData_SaveAsSMFW
#else
#define MIDIData_SaveAsSMF MIDIData_SaveAsSMFA
#endif

/* MIDIDataをテキストファイルから読み込み、 */
/* 新しいMIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_LoadFromTextA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromTextW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromText MIDIData_LoadFromTextW
#else
#define MIDIData_LoadFromText MIDIData_LoadFromTextA
#endif

/* MIDIDataをテキストファイルとして保存 */
long __stdcall MIDIData_SaveAsTextA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsTextW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsText MIDIData_SaveAsTextW
#else
#define MIDIData_SaveAsText MIDIData_SaveAsTextA
#endif

/* MIDIDataをバイナリファイルから読み込み、*/
/* 新しいMIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_LoadFromBinaryA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromBinaryW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromBinary MIDIData_LoadFromBinaryW
#else
#define MIDIData_LoadFromBinary MIDIData_LoadFromBinaryA
#endif

/* MIDIDataをバイナリファイルに保存 */
long __stdcall MIDIData_SaveAsBinaryA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsBinaryW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsBinary MIDIData_SaveAsBinaryW
#else
#define MIDIData_SaveAsBinary MIDIData_SaveAsBinaryA
#endif

/* MIDIDataをCherrryファイル(*.chy)から読み込み、 */
/* 新しいMIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_LoadFromCherryA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromCherryW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromCherry MIDIData_LoadFromCherryW
#else
#define MIDIData_LoadFromCherry MIDIData_LoadFromCherryA
#endif

/* MIDIデータをCherryファイル(*.chy)に保存 */
long __stdcall MIDIData_SaveAsCherryA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsCherryW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsCherry MIDIData_SaveAsCherryW
#else
#define MIDIData_SaveAsCherry MIDIData_SaveAsCherryA
#endif

/* MIDIデータをMIDICSVファイル(*.csv)から読み込み */
/* 新しいMIDIデータへのポインタを返す(失敗時NULL) */
MIDIData* __stdcall MIDIData_LoadFromMIDICSVA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromMIDICSVW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromMIDICSV MIDIData_LoadFromMIDICSVW
#else
#define MIDIData_LoadFromMIDICSV MIDIData_LoadFromMIDICSVA
#endif

/* MIDIデータをMIDICSVファイル(*.csv)として保存 */
long __stdcall MIDIData_SaveAsMIDICSVA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsMIDICSVW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsMIDICSV MIDIData_SaveAsMIDICSVW
#else
#define MIDIData_SaveAsMIDICSV MIDIData_SaveAsMIDICSVA
#endif

#ifdef __cplusplus
}
#endif


#endif
