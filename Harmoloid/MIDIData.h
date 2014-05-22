/******************************************************************************/
/*                                                                            */
/*�@MIDIData.h - MIDIData�w�b�_�[�t�@�C��                  (C)2002-2013 ����  */
/*                                                                            */
/******************************************************************************/

/* ���̃��W���[���͕��ʂ̂b����ŏ�����Ă���B */
/* ���̃��C�u�����́AGNU �򓙈�ʌ��O���p�����_��(LGPL)�Ɋ�Â��z�z�����B */
/* �v���W�F�N�g�z�[���y�[�W�F"http://openmidiproject.sourceforge.jp/index.html" */
/* MIDI�C�x���g�̎擾�E�ݒ�E�����E�}���E�폜 */
/* MIDI�g���b�N�̎擾�E�ݒ�E�����E�}���E�폜 */
/* MIDI�f�[�^�̐����E�폜�ESMF�t�@�C��(*.mid)���o�� */

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

/* C++������g�p�\�Ƃ��� */
#ifdef __cplusplus
extern "C" {
#endif

/* __stdcall�̒�` */
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

/* MIDIEvent�\���� */
/* �o�����_�u�������N���X�g�\�� */
/* �m�[�h�����͐�Ύ����Ō��肳��܂� */
typedef struct tagMIDIEvent {
	long m_lTempIndex;                  /* ���̃C�x���g�̈ꎞ�I�ȃC���f�b�N�X(0����n�܂�) */
	long m_lTime;                       /* ��Ύ���[Tick]����SMPTE�T�u�t���[���P�� */
	long m_lKind;                       /* �C�x���g�̎��(0x00�`0xFF) */
	long m_lLen;                        /* �C�x���g�̃f�[�^����[�o�C�g] */
	unsigned char* m_pData;             /* �C�x���g�̃f�[�^�o�b�t�@�ւ̃|�C���^ */
	unsigned long m_lData;              /* �C�x���g�̃f�[�^�o�b�t�@(MIDI�`�����l���C�x���g�̂Ƃ��g��) */
	struct tagMIDIEvent* m_pNextEvent;  /* ���̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pPrevEvent;  /* �O�̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pNextSameKindEvent; /* ���̓�����ނ̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pPrevSameKindEvent; /* �O�̓�����ނ̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pNextCombinedEvent; /* ���̌����C�x���g�ێ��p�|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pPrevCombinedEvent; /* �O�̌����C�x���g�ێ��p�|�C���^(�Ȃ����NULL) */
	void* m_pParent;                    /* �e(MIDITrack�I�u�W�F�N�g)�ւ̃|�C���^(�Ȃ����NULL) */
	long m_lUser1;                      /* ���[�U�[�p���R�̈�1(���g�p) */
	long m_lUser2;                      /* ���[�U�[�p���R�̈�2(���g�p) */
	long m_lUser3;                      /* ���[�U�[�p���R�̈�3(���g�p) */
	long m_lUserFlag;                   /* ���[�U�[�p���R�̈�4(���g�p) */
} MIDIEvent;

/* MIDITrack�\���� */
/* �o���������N���X�g�\�� */
typedef struct tagMIDITrack {
	long m_lTempIndex;                  /* ���̃g���b�N�̈ꎞ�I�ȃC���f�b�N�X(0����n�܂�) */
	long m_lNumEvent;                   /* �g���b�N���̃C�x���g�� */
	struct tagMIDIEvent* m_pFirstEvent; /* �ŏ��̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDIEvent* m_pLastEvent;  /* �Ō�̃C�x���g�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDITrack* m_pPrevTrack;  /* �O�̃g���b�N�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDITrack* m_pNextTrack;  /* ���̃g���b�N�ւ̃|�C���^(�Ȃ����NULL) */
	void*  m_pParent;                   /* �e(MIDIData�I�u�W�F�N�g)�ւ̃|�C���^ */
	long m_lInputOn;                    /* ����(0=OFF, 1=On) */
	long m_lInputPort;                  /* ���̓|�[�g(-1=n/a, 0�`15=�|�[�g�ԍ�) */
	long m_lInputChannel;               /* ���̓`�����l��(-1=n/1, 0�`15=�`�����l���ԍ�) */
	long m_lOutputOn;                   /* �o��(0=OFF, 1=On) */
	long m_lOutputPort;                 /* �o�̓|�[�g(-1=n/a, 0�`15=�|�[�g�ԍ�) */
	long m_lOutputChannel;              /* �o�̓`�����l��(-1=n/1, 0�`15=�`�����l���ԍ�) */
	long m_lTimePlus;                   /* �^�C��+ */
	long m_lKeyPlus;                    /* �L�[+ */
	long m_lVelocityPlus;               /* �x���V�e�B+ */
	long m_lViewMode;                   /* �\�����[�h(0=�ʏ�A1=�h����) */
	long m_lForeColor;                  /* �O�i�F */
	long m_lBackColor;                  /* �w�i�F */
	long m_lReserved1;                  /* �\��̈�1(�g�p�֎~) */
	long m_lReserved2;                  /* �\��̈�2(�g�p�֎~) */
	long m_lReserved3;                  /* �\��̈�3(�g�p�֎~) */
	long m_lReserved4;                  /* �\��̈�4(�g�p�֎~) */
	long m_lUser1;                      /* ���[�U�[�p���R�̈�1(���g�p) */
	long m_lUser2;                      /* ���[�U�[�p���R�̈�2(���g�p) */
	long m_lUser3;                      /* ���[�U�[�p���R�̈�3(���g�p) */
	long m_lUserFlag;                   /* ���[�U�[�p���R�̈�4(���g�p) */
} MIDITrack;

/* MIDIData�\���� */
/* �o���������N���X�g�\�� */
typedef struct tagMIDIData {
	unsigned long m_lFormat;            /* SMF�t�H�[�}�b�g(0/1) */
	unsigned long m_lNumTrack;          /* �g���b�N��(0�`��) */
	unsigned long m_lTimeBase;          /* �^�C���x�[�X(��F120) */
	struct tagMIDITrack* m_pFirstTrack; /* �ŏ��̃g���b�N�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDITrack* m_pLastTrack;  /* �Ō�̃g���b�N�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDITrack* m_pNextSeq;    /* ���̃V�[�P���X�ւ̃|�C���^(�Ȃ����NULL) */
	struct tagMIDITrack* m_pPrevSeq;    /* �O�̃V�[�P���X�ւ̃|�C���^(�Ȃ����NULL) */
	void*  m_pParent;                   /* �e(���NULL�B�����\���O���X�g���T�|�[�g) */
	long m_lReserved1;                  /* �\��̈�1(�g�p�֎~) */
	long m_lReserved2;                  /* �\��̈�2(�g�p�֎~) */
	long m_lReserved3;                  /* �\��̈�3(�g�p�֎~) */
	long m_lReserved4;                  /* �\��̈�4(�g�p�֎~) */
	long m_lUser1;                      /* ���[�U�[�p���R�̈�1(���g�p) */
	long m_lUser2;                      /* ���[�U�[�p���R�̈�2(���g�p) */
	long m_lUser3;                      /* ���[�U�[�p���R�̈�3(���g�p) */
	long m_lUserFlag;                   /* ���[�U�[�p���R�̈�4(���g�p) */
} MIDIData;

/* ���̑��̃}�N�� */
#define MIDIEVENT_MAXLEN       65536

/* �t�H�[�}�b�g�Ɋւ���}�N�� */
#define MIDIDATA_FORMAT0       0x00 /* �t�H�[�}�b�g0 */
#define MIDIDATA_FORMAT1       0x01 /* �t�H�[�}�b�g1 */
#define MIDIDATA_FORMAT2       0x02 /* �t�H�[�}�b�g2 */

/* �e���|�Ɋւ���}�N�� */
/* ���ӁF�e���|�̒P�ʂ͂��ׂ�[�}�C�N���b/tick]�Ƃ���B */
#define MIDIEVENT_MAXTEMPO     (60000000)
#define MIDIEVENT_MINTEMPO     (1)
#define MIDIEVENT_DEFTEMPO     (60000000/120)

/* �g���b�N���Ɋւ���}�N�� */
#define MIDIDATA_MAXMIDITRACKNUM 65535

/* �^�C�����[�h�Ɋւ���}�N�� */
#define MIDIDATA_TPQNBASE      0  /* TPQN�x�[�X */
#define MIDIDATA_SMPTE24BASE   24 /* 24�t���[��/�b */
#define MIDIDATA_SMPTE25BASE   25 /* 25�t���[��/�b */
#define MIDIDATA_SMPTE29BASE   29 /* 29.97�t���[��/�b */
#define MIDIDATA_SMPTE30BASE   30 /* 30�t���[��/�b */

/* �^�C�����]�����[�V����(����\)�Ɋւ���}�N�� */
/* TPQN�x�[�X�̏ꍇ�F4������������̕���\ */
/* �����ӁF����TPQN�̕���\�́A24,48,72,96,120,144,168,192,216,240,360,384,480,960�ł��� */
#define MIDIDATA_MINTPQNRESOLUTION   1   /* TPQN���]�����[�V�����ŏ��l=1 */
#define MIDIDATA_MAXTPQNRESOLUTION   32767 /* TPQN���]�����[�V�����ő�l=32767 */
#define MIDIDATA_DEFTPQNRESOLUTION   120 /* TPQN���]�����[�V�����W���l=120 */

/* SMPTE�x�[�X�̏ꍇ�F1�t���[��������̕���\ */
/* �����ӁF����SMPTE�̕���\�́A10,40,80�Ȃǂ���\�I�ł��� */
#define MIDIDATA_MINSMPTERESOLUTION  1   /* SMPTE���]�����[�V�����ŏ��l=1 */
#define MIDIDATA_MAXSMPTERESOLUTION  255 /* SMPTE���]�����[�V�����ő�l=255 */
#define MIDIDATA_DEFSMPTERESOLUTION  10  /* SMPTE���]�����[�V�����W���l=10 */

/* �ő�|�[�g�� */
#define MIDIDATA_MAXNUMPORT         256

/* SMPTE�I�t�Z�b�g�Ɋւ���}�N�� */
#define MIDIEVENT_SMPTE24           0x00 /* 24�t���[���^�b */
#define MIDIEVENT_SMPTE25           0x01 /* 25�t���[���^�b */
#define MIDIEVENT_SMPTE30D          0x02 /* 30�t���[���^�b(�h���b�v) */
#define MIDIEVENT_SMPTE30N          0x03 /* 30�t���[���^�b(�m���h���b�v) */

/* �����Ɋւ���}�N�� */
#define MIDIEVENT_MAJOR             0x00 /* ���� */
#define MIDIEVENT_MINOR             0x01 /* �Z�� */

/* MIDIEVENT_KIND�}�N�� (�R�����g�̃J�b�R���̓f�[�^���̒���������) */
#define MIDIEVENT_SEQUENCENUMBER    0x00 /* �V�[�P���X�i���o�[(2�o�C�g) */
#define MIDIEVENT_TEXTEVENT         0x01 /* �e�L�X�g(�ϒ�������) */
#define MIDIEVENT_COPYRIGHTNOTICE   0x02 /* ���쌠(�ϒ�������) */
#define MIDIEVENT_TRACKNAME         0x03 /* �g���b�N���E�V�[�P���T��(�ϒ�������) */
#define MIDIEVENT_INSTRUMENTNAME    0x04 /* �C���X�g�D�������g(�ϒ�������) */
#define MIDIEVENT_LYRIC             0x05 /* �̎�(�ϒ�������) */
#define MIDIEVENT_MARKER            0x06 /* �}�[�J�[(�ϒ�������) */
#define MIDIEVENT_CUEPOINT          0x07 /* �L���[�|�C���g(�ϒ�������) */
#define MIDIEVENT_PROGRAMNAME       0x08 /* �v���O������(�ϒ�������) */
#define MIDIEVENT_DEVICENAME        0x09 /* �f�o�C�X��(�ϒ�������) */
#define MIDIEVENT_CHANNELPREFIX     0x20 /* �`�����l���v���t�B�b�N�X(1�o�C�g) */
#define MIDIEVENT_PORTPREFIX        0x21 /* �|�[�g�v���t�B�b�N�X(1�o�C�g) */
#define MIDIEVENT_ENDOFTRACK        0x2F /* �G���h�I�u�g���b�N(0�o�C�g) */
#define MIDIEVENT_TEMPO             0x51 /* �e���|(3�o�C�g) */
#define MIDIEVENT_SMPTEOFFSET       0x54 /* SMPTE�I�t�Z�b�g(5�o�C�g) */
#define MIDIEVENT_TIMESIGNATURE     0x58 /* ���q�L��(4�o�C�g) */
#define MIDIEVENT_KEYSIGNATURE      0x59 /* �����L��(2�o�C�g) */
#define MIDIEVENT_SEQUENCERSPECIFIC 0x7F /* �V�[�P���T�[�Ǝ��̃C�x���g(�ϒ��o�C�i��) */
#define MIDIEVENT_NOTEOFF           0x80 /* �m�[�g�I�t(3�o�C�g) */
#define MIDIEVENT_NOTEON            0x90 /* �m�[�g�I��(3�o�C�g) */
#define MIDIEVENT_KEYAFTERTOUCH     0xA0 /* �L�[�A�t�^�[(3�o�C�g) */
#define MIDIEVENT_CONTROLCHANGE     0xB0 /* �R���g���[���[(3�o�C�g) */
#define MIDIEVENT_PROGRAMCHANGE     0xC0 /* �v���O�����`�F���W(2�o�C�g) */
#define MIDIEVENT_CHANNELAFTERTOUCH 0xD0 /* �`�����l���A�t�^�[(2�o�C�g) */
#define MIDIEVENT_PITCHBEND         0xE0 /* �s�b�`�x���h(3�o�C�g) */
#define MIDIEVENT_SYSEXSTART        0xF0 /* �V�X�e���G�N�X�N���[�V��(�ϒ��o�C�i��) */
#define MIDIEVENT_SYSEXCONTINUE     0xF7 /* �V�X�e���G�N�X�N���[�V���̑���(�ϒ��o�C�i��) */

/* MIDIEVENT_KIND�}�N�� (�ȉ���4��MIDIData_SetKind�̈����Ɏg����) */
#define MIDIEVENT_NOTEONNOTEOFF     0x180 /* �m�[�g(0x9n+0x8n) */
#define MIDIEVENT_NOTEONNOTEON0     0x190 /* �m�[�g(0x9n+0x9n(vel==0)) */
#define MIDIEVENT_PATCHCHANGE       0x1C0 /* �p�b�`�`�F���W(CC#32+CC#0+�v���O�����`�F���W) */
#define MIDIEVENT_RPNCHANGE         0x1A0 /* RPN�`�F���W(CC#101+CC#100+CC#6) */
#define MIDIEVENT_NRPNCHANGE        0x1B0 /* NRPN�`�F���W(CC#99+CC#98+CC#6) */

/* MIDIEVENT_DUMP�}�N�� */
#define MIDIEVENT_DUMPALL           0x0000FFFF
#define MIDIEVENT_DUMPTIME          0x00000001
#define MIDIEVENT_DUMPKIND          0x00000010
#define MIDIEVENT_DUMPLEN           0x00000020
#define MIDIEVENT_DUMPDATA          0x00000040
#define MIDIEVENT_DUMPUSER1         0x00000100
#define MIDIEVENT_DUMPUSER2         0x00000200
#define MIDIEVENT_DUMPUSERFLAG      0x00000400

/* forEachTrack�}�N�� */
#define forEachTrack(pMIDIData, pTrack) \
for((pTrack)=(pMIDIData)->m_pFirstTrack;(pTrack);(pTrack)=(pTrack)->m_pNextTrack)

/* forEachTrackInverse�}�N�� */
#define forEachTrackInverse(pMIDIData, pTrack) \
for((pTrack)=(pMIDIData)->m_pLastTrack;(pTrack);(pTrack)=(pTrack)->m_pPrevTrack)


/* forEachEvent�}�N�� */
#define forEachEvent(pTrack,pEvent) \
for((pEvent)=(pTrack)->m_pFirstEvent;(pEvent);(pEvent)=(pEvent)->m_pNextEvent)

/* forEachEventInverse�}�N�� */
#define forEachEventInverse(pTrack,pEvent) \
for((pEvent)=(pTrack)->m_pLastEvent;(pEvent);(pEvent)=(pEvent)->m_pPrevEvent)

/******************************************************************************/
/*                                                                            */
/*�@MIDIDataLib�N���X�֐�                                                     */
/*                                                                            */
/******************************************************************************/

/* ���P�[���̐ݒ� */
char* __stdcall MIDIDataLib_SetLocaleA (int nCategory, const char *pszLocale);
wchar_t* __stdcall MIDIDataLib_SetLocaleW (int nCategory, const wchar_t* pszLocale);
#ifdef UNICODE
#define MIDIDataLib_SetLocale MIDIDataLib_SetLocaleW
#else
#define MIDIDataLib_SetLocale MIDIDataLib_SetLocaleA
#endif

/******************************************************************************/
/*                                                                            */
/*�@MIDIEvent�N���X�֐�                                                       */
/*                                                                            */
/******************************************************************************/

/* ���F__stdcall��Windows��p�ł��BLinux�̏ꍇ��__stdcall�������Ă������� */

/* �����C�x���g�̍ŏ��̃C�x���g��Ԃ��B */
/* �����C�x���g�łȂ��ꍇ�ApEvent���g��Ԃ��B*/
MIDIEvent* __stdcall MIDIEvent_GetFirstCombinedEvent (MIDIEvent* pEvent);

/* �����C�x���g�̍Ō�̃C�x���g��Ԃ��B */
/* �����C�x���g�łȂ��ꍇ�ApEvent���g��Ԃ��B*/
MIDIEvent* __stdcall MIDIEvent_GetLastCombinedEvent (MIDIEvent* pEvent);

/* �P�̃C�x���g���������� */
long __stdcall MIDIEvent_Combine (MIDIEvent* pEvent);

/* �����C�x���g��؂藣�� */
long __stdcall MIDIEvent_Chop (MIDIEvent* pEvent);

/* MIDI�C�x���g�̍폜(�������Ă���ꍇ�ł��P���MIDI�C�x���g���폜) */
long __stdcall MIDIEvent_DeleteSingle (MIDIEvent* pMIDIEvent);

/* MIDI�C�x���g�̍폜(�������Ă���ꍇ�A�������Ă���MIDI�C�x���g���폜) */
long __stdcall MIDIEvent_Delete (MIDIEvent* pMIDIEvent);

/* MIDI�C�x���g(�C��)�𐶐����AMIDI�C�x���g�ւ̃|�C���^��Ԃ�(���s��NULL�A�ȉ����l) */
MIDIEvent* __stdcall MIDIEvent_Create 
(long lTime, long lKind, unsigned char* pData, long lLen);

/* �w��C�x���g�Ɠ���MIDI�C�x���g�𐶐����AMIDI�C�x���g�ւ̃|�C���^��Ԃ�(���s��NULL�A�ȉ����l) */
MIDIEvent* __stdcall MIDIEvent_CreateClone (MIDIEvent* pMIDIEvent);

/* �V�[�P���X�ԍ��C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateSequenceNumber
(long lTime, long lNum);

/* �e�L�X�g�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateTextEventA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateTextEventW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateTextEvent MIDIEvent_CreateTextEventW
#else
#define MIDIEvent_CreateTextEvent MIDIEvent_CreateTextEventA
#endif

/* ���쌠�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateCopyrightNoticeA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateCopyrightNoticeW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateCopyrightNotice MIDIEvent_CreateCopyrightNoticeW
#else
#define MIDIEvent_CreateCopyrightNotice MIDIEvent_CreateCopyrightNoticeA
#endif

/* �g���b�N���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateTrackNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateTrackNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateTrackName MIDIEvent_CreateTrackNameW
#else
#define MIDIEvent_CreateTrackName MIDIEvent_CreateTrackNameA
#endif

/* �C���X�g�D�������g���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateInstrumentNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateInstrumentNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateInstrumentName MIDIEvent_CreateInstrumentNameW
#else
#define MIDIEvent_CreateInstrumentName MIDIEvent_CreateInstrumentNameA
#endif

/* �̎��C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateLyricA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateLyricW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateLyric MIDIEvent_CreateLyricW
#else
#define MIDIEvent_CreateLyric MIDIEvent_CreateLyricA
#endif

/* �}�[�J�[�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateMarkerA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateMarkerW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateMarker MIDIEvent_CreateMarkerW
#else
#define MIDIEvent_CreateMarker MIDIEvent_CreateMarkerA
#endif

/* �L���[�|�C���g�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateCuePointA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateCuePointW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateCuePoint MIDIEvent_CreateCuePointW
#else
#define MIDIEvent_CreateCuePoint MIDIEvent_CreateCuePointA
#endif

/* �v���O�������C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateProgramNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateProgramNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateProgramName MIDIEvent_CreateProgramNameW
#else
#define MIDIEvent_CreateProgramName MIDIEvent_CreateProgramNameA
#endif

/* �f�o�C�X���C�x���g���� */
MIDIEvent* __stdcall MIDIEvent_CreateDeviceNameA
(long lTime, const char* pszText);
MIDIEvent* __stdcall MIDIEvent_CreateDeviceNameW
(long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_CreateDeviceName MIDIEvent_CreateDeviceNameW
#else
#define MIDIEvent_CreateDeviceName MIDIEvent_CreateDeviceNameA
#endif

/* �`�����l���v���t�B�b�N�X�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateChannelPrefix (long lTime, long lCh);

/* �|�[�g�v���t�B�b�N�X�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreatePortPrefix (long lTime, long lNum);

/* �G���h�I�u�g���b�N�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateEndofTrack (long lTime);

/* �e���|�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateTempo (long lTime, long lTempo);

/* SMPTE�I�t�Z�b�g�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateSMPTEOffset
(long lTime, long lMode, long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* ���q�L���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateTimeSignature
(long lTime, long lnn, long ldd, long lcc, long lbb);

/* �����L���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateKeySignature
(long lTime, long lsf, long lmi);

/* �V�[�P���T�[�Ǝ��̃C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateSequencerSpecific
(long lTime, char* pData, long lLen);

/* �m�[�g�I�t�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOff 
(long lTime, long lCh, long lKey, long lVel);

/* �m�[�g�I���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOn
(long lTime, long lCh, long lKey, long lVel);

/* �m�[�g�C�x���g�̐���(MIDIEvent_CreateNoteOnNoteOn0�Ɠ���) */
/* (�m�[�g�I���E�m�[�g�I��(0x9n(vel==0))��2�C�x���g�𐶐����A*/
/* �m�[�g�I���C�x���g�ւ̃|�C���^��Ԃ��B) */
MIDIEvent* __stdcall MIDIEvent_CreateNote 
(long lTime, long lCh, long lKey, long lVel, long lDur);

/* �m�[�g�C�x���g�̐���(0x8n�����^) */
/* (�m�[�g�I��(0x9n)�E�m�[�g�I�t(0x8n)��2�C�x���g�𐶐����A*/
/* NoteOn�ւ̃|�C���^��Ԃ�) */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOnNoteOff
(long lTime, long lCh, long lKey, long lVel1, long lVel2, long lDur);

/* �m�[�g�C�x���g�̐���(0x9n�����^) */
/* (�m�[�g�I��(0x9n)�E�m�[�g�I��(0x9n(vel==0))��2�C�x���g�𐶐����A*/
/* NoteOn�ւ̃|�C���^��Ԃ�) */
MIDIEvent* __stdcall MIDIEvent_CreateNoteOnNoteOn0
(long lTime, long lCh, long lKey, long lVel, long lDur);

/* �L�[�A�t�^�[�^�b�`�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateKeyAftertouch 
(long lTime, long lCh, long lKey, long lVal);

/* �R���g���[���[�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateControlChange 
(long lTime, long lCh, long lNum, long lVal);

/* RPN�C�x���g�̐��� */
/* (CC#101+CC#100+CC#6��3�C�x���g�𐶐����ACC#101�ւ̃|�C���^��Ԃ�) */
MIDIEvent* __stdcall MIDIEvent_CreateRPNChange
(long lTime, long lCh, long lCC101, long lCC100, long lVal);

/* NRPN�C�x���g�̐��� */
/* (CC#99+CC#98+CC#6��3�C�x���g�𐶐����ACC#99�ւ̃|�C���^��Ԃ�) */
MIDIEvent* __stdcall MIDIEvent_CreateNRPNChange 
(long lTime, long lCh, long lCC99, long lCC98, long lVal);

/* �v���O�����`�F���W�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateProgramChange 
(long lTime, long lCh, long lNum);

/* �o���N�E�p�b�`�C�x���g�̐��� */
/* (CC#0+CC#32+PC��3�C�x���g�𐶐����ACC#0�ւ̃|�C���^��Ԃ�) */
MIDIEvent* __stdcall MIDIEvent_CreatePatchChange 
(long lTime, long lCh, long lCC0, long lCC32, long lNum);

/* �`�����l���A�t�^�[�^�b�`�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateChannelAftertouch 
(long lTime, long lCh, long lVal);

/* �s�b�`�x���h�C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreatePitchBend 
(long lTime, long lCh, long lVal);

/* �V�X�e���G�N�X�N���[�V���C�x���g�̐��� */
MIDIEvent* __stdcall MIDIEvent_CreateSysExEvent 
(long lTime, unsigned char* pBuf, long lLen);




/* ���^�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsMetaEvent (MIDIEvent* pMIDIEvent);

/* �V�[�P���X�ԍ��ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsSequenceNumber (MIDIEvent* pMIDIEvent);

/* �e�L�X�g�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsTextEvent (MIDIEvent* pMIDIEvent);

/* ���쌠�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsCopyrightNotice (MIDIEvent* pMIDIEvent);

/* �g���b�N���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsTrackName (MIDIEvent* pMIDIEvent);

/* �C���X�g�D�������g���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsInstrumentName (MIDIEvent* pMIDIEvent);

/* �̎��C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsLyric (MIDIEvent* pMIDIEvent);

/* �}�[�J�[�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsMarker (MIDIEvent* pMIDIEvent);

/* �L���[�|�C���g�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsCuePoint (MIDIEvent* pMIDIEvent);

/* �v���O�������C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsProgramName (MIDIEvent* pEvent);

/* �f�o�C�X���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsDeviceName (MIDIEvent* pEvent);

/* �`�����l���v���t�B�b�N�X�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsChannelPrefix (MIDIEvent* pEvent);

/* �|�[�g�v���t�B�b�N�X�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsPortPrefix (MIDIEvent* pEvent);

/* �G���h�I�u�g���b�N�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsEndofTrack (MIDIEvent* pMIDIEvent);

/* �e���|�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsTempo (MIDIEvent* pMIDIEvent);

/* SMPTE�I�t�Z�b�g�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsSMPTEOffset (MIDIEvent* pMIDIEvent);

/* ���q�L���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsTimeSignature (MIDIEvent* pMIDIEvent);

/* �����L���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsKeySignature (MIDIEvent* pMIDIEvent);

/* �V�[�P���T�Ǝ��̃C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsSequencerSpecific (MIDIEvent* pMIDIEvent);


/* MIDI�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsMIDIEvent (MIDIEvent* pMIDIEvent);

/* �m�[�g�I���C�x���g�ł��邩�ǂ����𒲂ׂ� */
/* (�m�[�g�I���C�x���g�Ńx���V�e�B0�̂��̂̓m�[�g�I�t�C�x���g�Ƃ݂Ȃ��B�ȉ����l) */
long __stdcall MIDIEvent_IsNoteOn (MIDIEvent* pMIDIEvent);

/* �m�[�g�I�t�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsNoteOff (MIDIEvent* pMIDIEvent);

/* �m�[�g�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsNote (MIDIEvent* pMIDIEvent);

/* NOTEONOTEOFF�C�x���g�ł��邩�ǂ����𒲂ׂ� */
/* ����̓m�[�g�I��(0x9n)�ƃm�[�g�I�t(0x8n)�������C�x���g�����C�x���g�łȂ���΂Ȃ�Ȃ��B */
long __stdcall MIDIEvent_IsNoteOnNoteOff (MIDIEvent* pEvent);

/* NOTEONNOTEON0�C�x���g�ł��邩�ǂ����𒲂ׂ� */
/* ����̓m�[�g�I��(0x9n)�ƃm�[�g�I�t(0x9n,vel==0)�������C�x���g�����C�x���g�łȂ���΂Ȃ�Ȃ��B */
long __stdcall MIDIEvent_IsNoteOnNoteOn0 (MIDIEvent* pEvent);

/* �L�[�A�t�^�[�^�b�`�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsKeyAftertouch (MIDIEvent* pEvent);

/* �R���g���[���`�F���W�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsControlChange (MIDIEvent* pEvent);

/* RPN�`�F���W�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsRPNChange (MIDIEvent* pEvent);

/* NRPN�`�F���W�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsNRPNChange (MIDIEvent* pEvent);

/* �v���O�����`�F���W�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsProgramChange (MIDIEvent* pEvent);

/* �p�b�`�`�F���W�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsPatchChange (MIDIEvent* pEvent);

/* �`�����l���A�t�^�[�^�b�`�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsChannelAftertouch (MIDIEvent* pEvent);

/* �s�b�`�x���h�C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsPitchBend (MIDIEvent* pEvent);

/* �V�X�e���G�N�X�N���[�V���C�x���g�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDIEvent_IsSysExEvent (MIDIEvent* pMIDIEvent);

/* ���V�C�x���g�ł��邩�ǂ������ׂ� */
long __stdcall MIDIEvent_IsFloating (MIDIEvent* pEvent);

/* �����C�x���g�ł��邩�ǂ������ׂ� */
long __stdcall MIDIEvent_IsCombined (MIDIEvent* pEvent);


/* �C�x���g�̎�ނ��擾 */
long __stdcall MIDIEvent_GetKind (MIDIEvent* pEvent);

/* �C�x���g�̎�ނ�ݒ� */
long __stdcall MIDIEvent_SetKind (MIDIEvent* pEvent, long lKind);

/* �C�x���g�̒����擾 */
long __stdcall MIDIEvent_GetLen (MIDIEvent* pEvent);

/* �C�x���g�̃f�[�^�����擾 */
long __stdcall MIDIEvent_GetData (MIDIEvent* pEvent, unsigned char* pBuf, long lLen);

/* �C�x���g�̃f�[�^����ݒ�(���̊֐��͑�ϊ댯�ł��B�������̃`�F�L�͂��܂���) */
long __stdcall MIDIEvent_SetData (MIDIEvent* pEvent, unsigned char* pBuf, long lLen);

/* �C�x���g�̃e�L�X�g���擾(�e�L�X�g�E���쌠�E�g���b�N���E�C���X�g�D�������g���E */
/* �̎��E�}�[�J�[�E�L���[�|�C���g�E�v���O�������E�f�o�C�X���̂�) */
char* __stdcall MIDIEvent_GetTextA (MIDIEvent* pEvent, char* pBuf, long lLen);
wchar_t* __stdcall MIDIEvent_GetTextW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDIEvent_GetText MIDIEvent_GetTextW
#else
#define MIDIEvent_GetText MIDIEvent_GetTextA
#endif

/* �C�x���g�̃e�L�X�g��ݒ�(�e�L�X�g�E���쌠�E�g���b�N���E�C���X�g�D�������g���E */
/* �̎��E�}�[�J�[�E�L���[�|�C���g�E�v���O�������E�f�o�C�X���̂�) */
long __stdcall MIDIEvent_SetTextA (MIDIEvent* pEvent, const char* pszText);
long __stdcall MIDIEvent_SetTextW (MIDIEvent* pEvent, const wchar_t* pszText);
#ifdef UNICODE
#define MIDIEvent_SetText MIDIEvent_SetTextW
#else
#define MIDIEvent_SetText MIDIEvent_SetTextA
#endif

/* SMPTE�I�t�Z�b�g�̎擾(SMPTE�I�t�Z�b�g�C�x���g�̂�) */
long __stdcall MIDIEvent_GetSMPTEOffset 
(MIDIEvent* pEvent, long* pMode, long* pHour, long* pMin, long* pSec, long* pFrame, long* pSubFrame);

/* SMPTE�I�t�Z�b�g�̐ݒ�(SMPTE�I�t�Z�b�g�C�x���g�̂�) */
long __stdcall MIDIEvent_SetSMPTEOffset 
(MIDIEvent* pEvent, long lMode, long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* �e���|�擾(�e���|�C�x���g�̂�) */
long __stdcall MIDIEvent_GetTempo (MIDIEvent* pEvent);

/* �e���|�ݒ�(�e���|�C�x���g�̂�) */
long __stdcall MIDIEvent_SetTempo (MIDIEvent* pEvent, long lTempo);

/* ���q�L���擾(���q�L���C�x���g�̂�) */
long __stdcall MIDIEvent_GetTimeSignature 
(MIDIEvent* pEvent, long* lnn, long* ldd, long* lcc, long* bb);

/* ���q�L���̐ݒ�(���q�L���C�x���g�̂�) */
long __stdcall MIDIEvent_SetTimeSignature 
(MIDIEvent* pEvent, long lnn, long ldd, long lcc, long lbb);

/* �����L���̎擾(�����L���C�x���g�̂�) */
long __stdcall MIDIEvent_GetKeySignature (MIDIEvent* pEvent, long* psf, long* pmi);

/* �����L���̐ݒ�(�����L���C�x���g�̂�) */
long __stdcall MIDIEvent_SetKeySignature (MIDIEvent* pEvent, long lsf, long lmi);

/* �C�x���g�̃��b�Z�[�W�擾(MIDI�`�����l���C�x���g�y�уV�X�e���G�N�X�N���[�V���̂�) */
long __stdcall MIDIEvent_GetMIDIMessage (MIDIEvent* pEvent, char* pMessage, long lLen);

/* �C�x���g�̃��b�Z�[�W�ݒ�(MIDI�`�����l���C�x���g�y�уV�X�e���G�N�X�N���[�V���̂�) */
long __stdcall MIDIEvent_SetMIDIMessage (MIDIEvent* pEvent, char* pMessage, long lLen);

/* �C�x���g�̃`�����l���擾(MIDI�`�����l���C�x���g�̂�) */
long __stdcall MIDIEvent_GetChannel (MIDIEvent* pEvent);

/* �C�x���g�̃`�����l���ݒ�(MIDI�`�����l���C�x���g�̂�) */
long __stdcall MIDIEvent_SetChannel (MIDIEvent* pEvent, long lCh);

/* �C�x���g�̎����擾 */
long __stdcall MIDIEvent_GetTime (MIDIEvent* pEvent);

/* �C�x���g�̎����ݒ� */
long __stdcall MIDIEvent_SetTimeSingle (MIDIEvent* pEvent, long lTime);

/* �C�x���g�̎����ݒ� */
long __stdcall MIDIEvent_SetTime (MIDIEvent* pEvent, long lTime);

/* �C�x���g�̃L�[�擾(�m�[�g�I�t�E�m�[�g�I���E�`�����l���A�t�^�[�̂�) */
long __stdcall MIDIEvent_GetKey (MIDIEvent* pEvent);

/* �C�x���g�̃L�[�ݒ�(�m�[�g�I�t�E�m�[�g�I���E�`�����l���A�t�^�[�̂�) */
long __stdcall MIDIEvent_SetKey (MIDIEvent* pEvent, long lKey);

/* �C�x���g�̃x���V�e�B�擾(�m�[�g�I�t�E�m�[�g�I���̂�) */
long __stdcall MIDIEvent_GetVelocity (MIDIEvent* pEvent);

/* �C�x���g�̃x���V�e�B�ݒ�(�m�[�g�I�t�E�m�[�g�I���̂�) */
long __stdcall MIDIEvent_SetVelocity (MIDIEvent* pEvent, long cVel);

/* �����C�x���g�̉������擾(�m�[�g�̂�) */
long __stdcall MIDIEvent_GetDuration (MIDIEvent* pEvent);

/* �����C�x���g�̉������ݒ�(�m�[�g�̂�) */
long __stdcall MIDIEvent_SetDuration (MIDIEvent* pEvent, long lDuration);

/* �����C�x���g�̃o���N�擾(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_GetBank (MIDIEvent* pEvent);

/* �����C�x���g�̃o���N���(MSB)�擾(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_GetBankMSB (MIDIEvent* pEvent);

/* �����C�x���g�̃o���N����(LSB)�擾(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_GetBankLSB (MIDIEvent* pEvent);

/* �����C�x���g�̃o���N�ݒ�(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_SetBank (MIDIEvent* pEvent, long lBank);

/* �����C�x���g�̃o���N���(MSB)�ݒ�(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_SetBankMSB (MIDIEvent* pEvent, long lBankMSB);

/* �����C�x���g�̃o���N����(LSB)�ݒ�(RPN�`�F���W�ENRPN�`�F���W�E�p�b�`�`�F���W�̂�) */
long __stdcall MIDIEvent_SetBankLSB (MIDIEvent* pEvent, long lBankLSB);

/* �C�x���g�̔ԍ��擾(�R���g���[���`�F���W�E�v���O�����`�F���W�̂�) */
long __stdcall MIDIEvent_GetNumber (MIDIEvent* pEvent);

/* �C�x���g�̔ԍ��ݒ�(�R���g���[���`�F���W�E�v���O�����`�F���W�̂�) */
long __stdcall MIDIEvent_SetNumber (MIDIEvent* pEvent, long cNum);

/* �C�x���g�̒l�擾(�L�[�A�t�^�[�E�R���g���[���[�E�`�����l���A�t�^�[�E�s�b�`�x���h) */
long __stdcall MIDIEvent_GetValue (MIDIEvent* pEvent);

/* �C�x���g�̒l�ݒ�(�L�[�A�t�^�[�E�R���g���[���[�E�`�����l���A�t�^�[�E�s�b�`�x���h) */
long __stdcall MIDIEvent_SetValue (MIDIEvent* pEvent, long nVal);

/* ���̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDIEvent_GetNextEvent (MIDIEvent* pMIDIEvent);

/* �O�̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDIEvent_GetPrevEvent (MIDIEvent* pMIDIEvent);

/* ���̓���̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDIEvent_GetNextSameKindEvent (MIDIEvent* pMIDIEvent);

/* �O�̓���̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDIEvent_GetPrevSameKindEvent (MIDIEvent* pMIDIEvent);

/* �e�g���b�N�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDITrack* __stdcall MIDIEvent_GetParent (MIDIEvent* pMIDIEvent);

/* �C�x���g�̓��e�𕶎���\���ɕϊ� */
char* __stdcall MIDIEvent_ToStringExA (MIDIEvent* pEvent, char* pBuf, long lLen, long lFlags);
wchar_t* __stdcall MIDIEvent_ToStringExW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen, long lFlags);
#ifdef UNICODE
#define MIDIEvent_ToStringEx MIDIEvent_ToStringExW
#else
#define MIDIEvent_ToStringEx MIDIEvent_ToStringExA
#endif

/* �C�x���̓��e�g�𕶎���\���ɕϊ� */
char* __stdcall MIDIEvent_ToStringA (MIDIEvent* pEvent, char* pBuf, long lLen);
wchar_t* __stdcall MIDIEvent_ToStringW (MIDIEvent* pEvent, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDIEvent_ToString MIDIEvent_ToStringW
#else
#define MIDIEvent_ToString MIDIEvent_ToStringA
#endif


/******************************************************************************/
/*                                                                            */
/*�@MIDITrack�N���X�֐�                                                       */
/*                                                                            */
/******************************************************************************/

/* �g���b�N���̃C�x���g�̑������擾 */
long __stdcall MIDITrack_GetNumEvent (MIDITrack* pMIDITrack);

/* �g���b�N�̍ŏ��̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDITrack_GetFirstEvent (MIDITrack* pMIDITrack);

/* �g���b�N�̍Ō�̃C�x���g�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDITrack_GetLastEvent (MIDITrack* pMIDITrack);

/* �g���b�N���̎w���ނ̍ŏ��̃C�x���g�擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDITrack_GetFirstKindEvent (MIDITrack* pTrack, long lKind);

/* �g���b�N���̎w���ނ̍Ō�̃C�x���g�擾(�Ȃ����NULL) */
MIDIEvent* __stdcall MIDITrack_GetLastKindEvent (MIDITrack* pTrack, long lKind);

/* ����MIDI�g���b�N�ւ̃|�C���^�擾(�Ȃ����NULL)(20080715�ǉ�) */
MIDITrack* __stdcall MIDITrack_GetNextTrack (MIDITrack* pTrack);

/* �O��MIDI�g���b�N�ւ̃|�C���^�擾(�Ȃ����NULL)(20080715�ǉ�) */
MIDITrack* __stdcall MIDITrack_GetPrevTrack (MIDITrack* pTrack);

/* �g���b�N�̐eMIDI�f�[�^�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDIData* __stdcall MIDITrack_GetParent (MIDITrack* pMIDITrack);

/* �g���b�N���̃C�x���g�����J�E���g���A�e�C�x���g�̃C���f�b�N�X�Ƒ��C�x���g�����X�V���A�C�x���g����Ԃ��B */
long __stdcall MIDITrack_CountEvent (MIDITrack* pMIDITrack);

/* �g���b�N�̊J�n����(�ŏ��̃C�x���g�̎���)[Tick]���擾(20081101�ǉ�) */
long __stdcall MIDITrack_GetBeginTime (MIDITrack* pMIDITrack);

/* �g���b�N�̏I������(�Ō�̃C�x���g�̎���)[Tick]���擾(20081101�ǉ�) */
long __stdcall MIDITrack_GetEndTime (MIDITrack* pMIDITrack);

/* �g���b�N�̖��O���ȈՂɎ擾 */
char* __stdcall MIDITrack_GetNameA (MIDITrack* pMIDITrack, char* pBuf, long lLen);
wchar_t* __stdcall MIDITrack_GetNameW (MIDITrack* pMIDITrack, wchar_t* pBuf, long lLen);
#ifdef UNICODE
#define MIDITrack_GetName MIDITrack_GetNameW
#else
#define MIDITrack_GetName MIDITrack_GetNameA
#endif

/* ���͎擾(0=OFF, 1=On) */
long __stdcall MIDITrack_GetInputOn (MIDITrack* pTrack);

/* ���̓|�[�g�擾(-1=n/a, 0�`15=�|�[�g�ԍ�) */
long __stdcall MIDITrack_GetInputPort (MIDITrack* pTrack);

/* ���̓`�����l���擾(-1=n/a, 0�`15=�`�����l���ԍ�) */
long __stdcall MIDITrack_GetInputChannel (MIDITrack* pTrack);

/* �o�͎擾(0=OFF, 1=On) */
long __stdcall MIDITrack_GetOutputOn (MIDITrack* pTrack);

/* �o�̓|�[�g(-1=n/a, 0�`15=�|�[�g�ԍ�) */
long __stdcall MIDITrack_GetOutputPort (MIDITrack* pTrack);

/* �o�̓`�����l��(-1=n/a, 0�`15=�`�����l���ԍ�) */
long __stdcall MIDITrack_GetOutputChannel (MIDITrack* pTrack);

/* �^�C��+�擾 */
long __stdcall MIDITrack_GetTimePlus (MIDITrack* pTrack);

/* �L�[+�擾 */
long __stdcall MIDITrack_GetKeyPlus (MIDITrack* pTrack);

/* �x���V�e�B+�擾 */
long __stdcall MIDITrack_GetVelocityPlus (MIDITrack* pTrack);

/* �\�����[�h�擾(0=�ʏ�A1=�h����) */
long __stdcall MIDITrack_GetViewMode (MIDITrack* pTrack);

/* �O�i�F�擾 */
long __stdcall MIDITrack_GetForeColor (MIDITrack* pTrack);

/* �w�i�F�擾 */
long __stdcall MIDITrack_GetBackColor (MIDITrack* pTrack);


/* �g���b�N�̖��O���ȈՂɐݒ� */
long __stdcall MIDITrack_SetNameA (MIDITrack* pMIDITrack, const char* pszText);
long __stdcall MIDITrack_SetNameW (MIDITrack* pMIDITrack, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_SetName MIDITrack_SetNameW
#else
#define MIDITrack_SetName MIDITrack_SetNameA
#endif

/* ���͐ݒ�(0=OFF, 1=On) */
long __stdcall MIDITrack_SetInputOn (MIDITrack* pTrack, long lInputOn);

/* ���̓|�[�g�ݒ�(-1=n/a, 0�`15=�|�[�g�ԍ�) */
long __stdcall MIDITrack_SetInputPort (MIDITrack* pTrack, long lInputPort);

/* ���̓`�����l���ݒ�(-1=n/a, 0�`15=�`�����l���ԍ�) */
long __stdcall MIDITrack_SetInputChannel (MIDITrack* pTrack, long lInputChannel);

/* �o�͐ݒ�(0=OFF, 1=On) */
long __stdcall MIDITrack_SetOutputOn (MIDITrack* pTrack, long lOutputOn);

/* �o�̓|�[�g(-1=n/a, 0�`15=�|�[�g�ԍ�) */
long __stdcall MIDITrack_SetOutputPort (MIDITrack* pTrack, long lOutputPort);

/* �o�̓`�����l��(-1=n/a, 0�`15=�`�����l���ԍ�) */
long __stdcall MIDITrack_SetOutputChannel (MIDITrack* pTrack, long lOutputChannel);

/* �^�C��+�ݒ� */
long __stdcall MIDITrack_SetTimePlus (MIDITrack* pTrack, long lTimePlus);

/* �L�[+�ݒ� */
long __stdcall MIDITrack_SetKeyPlus (MIDITrack* pTrack, long lKeyPlus);

/* �x���V�e�B+�ݒ� */
long __stdcall MIDITrack_SetVelocityPlus (MIDITrack* pTrack, long lVelocityPlus);

/* �\�����[�h�ݒ�(0=�ʏ�A1=�h����) */
long __stdcall MIDITrack_SetViewMode (MIDITrack* pTrack, long lMode);

/* �O�i�F�ݒ� */
long __stdcall MIDITrack_SetForeColor (MIDITrack* pTrack, long lForeColor);

/* �w�i�F�ݒ� */
long __stdcall MIDITrack_SetBackColor (MIDITrack* pTrack, long lBackColor);

/* XF�ł���Ƃ��AXF�̃��@�[�W�������擾(XF�łȂ����0) */
long __stdcall MIDITrack_GetXFVersion (MIDITrack* pMIDITrack);

/* �g���b�N�̍폜(�܂܂��C�x���g�I�u�W�F�N�g���폜����܂�) */
void __stdcall MIDITrack_Delete (MIDITrack* pMIDITrack);

/* �g���b�N�𐶐����A�g���b�N�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDITrack* __stdcall MIDITrack_Create ();

/* MIDI�g���b�N�̃N���[���𐶐� */
MIDITrack* __stdcall MIDITrack_CreateClone (MIDITrack* pTrack);

/* �g���b�N�ɃC�x���g��}��(�C�x���g�͂��炩���ߐ������Ă���) */
long __stdcall MIDITrack_InsertSingleEventAfter 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* �g���b�N�ɃC�x���g��}��(�C�x���g�͂��炩���ߐ������Ă���) */
long __stdcall MIDITrack_InsertSingleEventBefore 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* �g���b�N�ɃC�x���g��}��(�C�x���g�͂��炩���ߐ������Ă���) */
long __stdcall MIDITrack_InsertEventAfter 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* �g���b�N�ɃC�x���g��}��(�C�x���g�͂��炩���ߐ������Ă���) */
long __stdcall MIDITrack_InsertEventBefore 
(MIDITrack* pMIDITrack, MIDIEvent* pEvent, MIDIEvent* pTarget);

/* �g���b�N�ɃC�x���g��}��(�C�x���g�͂��炩���ߐ������Ă���) */
long __stdcall MIDITrack_InsertEvent (MIDITrack* pMIDITrack, MIDIEvent* pEvent);

/* �g���b�N�ɃV�[�P���X�ԍ��C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertSequenceNumber
(MIDITrack* pMIDITrack, long lTime, long lNum);

/* �g���b�N�Ƀe�L�X�g�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertTextEventA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertTextEventW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertTextEvent MIDITrack_InsertTextEventW
#else
#define MIDITrack_InsertTextEvent MIDITrack_InsertTextEventA
#endif

/* �g���b�N�ɒ��쌠�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertCopyrightNoticeA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertCopyrightNoticeW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertCopyrightNotice MIDITrack_InsertCopyrightNoticeW
#else
#define MIDITrack_InsertCopyrightNotice MIDITrack_InsertCopyrightNoticeA
#endif

/* �g���b�N�Ƀg���b�N���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertTrackNameA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertTrackNameW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertTrackName MIDITrack_InsertTrackNameW
#else
#define MIDITrack_InsertTrackName MIDITrack_InsertTrackNameA
#endif

/* �g���b�N�ɃC���X�g�D�������g���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertInstrumentNameA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertInstrumentNameW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertInstrumentName MIDITrack_InsertInstrumentNameW
#else
#define MIDITrack_InsertInstrumentName MIDITrack_InsertInstrumentNameA
#endif

/* �g���b�N�ɉ̎��C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertLyricA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertLyricW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertLyric MIDITrack_InsertLyricW
#else
#define MIDITrack_InsertLyric MIDITrack_InsertLyricA
#endif

/* �g���b�N�Ƀ}�[�J�[�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertMarkerA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertMarkerW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertMarker MIDITrack_InsertMarkerW
#else
#define MIDITrack_InsertMarker MIDITrack_InsertMarkerA
#endif

/* �g���b�N�ɃL���[�|�C���g�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertCuePointA
(MIDITrack* pMIDITrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertCuePointW
(MIDITrack* pMIDITrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertCuePoint MIDITrack_InsertCuePointW
#else
#define MIDITrack_InsertCuePoint MIDITrack_InsertCuePointA
#endif

/* �g���b�N�Ƀv���O�������C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertProgramNameA
(MIDITrack* pTrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertProgramNameW
(MIDITrack* pTrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertProgramName MIDITrack_InsertProgramNameW
#else
#define MIDITrack_InsertProgramName MIDITrack_InsertProgramNameA
#endif

/* �g���b�N�Ƀf�o�C�X���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertDeviceNameA
(MIDITrack* pTrack, long lTime, const char* pszText);
long __stdcall MIDITrack_InsertDeviceNameW
(MIDITrack* pTrack, long lTime, const wchar_t* pszText);
#ifdef UNICODE
#define MIDITrack_InsertDeviceName MIDITrack_InsertDeviceNameW
#else
#define MIDITrack_InsertDeviceName MIDITrack_InsertDeviceNameA
#endif

/* �g���b�N�Ƀ`�����l���v���t�B�b�N�X�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertChannelPrefix (MIDITrack* pTrack, long lTime, long lCh);

/* �g���b�N�Ƀ|�[�g�v���t�B�b�N�X�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertPortPrefix (MIDITrack* pTrack, long lTime, long lPort);

/* �g���b�N�ɃG���h�I�u�g���b�N�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertEndofTrack
(MIDITrack* pMIDITrack, long lTime);

/* �g���b�N�Ƀe���|�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertTempo
(MIDITrack* pMIDITrack, long lTime, long lTempo);

/* �g���b�N��SMPTE�I�t�Z�b�g�C�x���g�𐶐����đ}�� */
long MIDITrack_InsertSMPTEOffset 
(MIDITrack* pTrack, long lTime, long lMode, 
 long lHour, long lMin, long lSec, long lFrame, long lSubFrame);

/* �g���b�N�ɔ��q�L���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertTimeSignature
(MIDITrack* pMIDITrack, long lTime, long lnn, long ldd, long lcc, long lbb);

/* �g���b�N�ɒ����L���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertKeySignature
(MIDITrack* pMIDITrack, long lTime, long lsf, long lmi);

/* �g���b�N�ɃV�[�P���T�[�Ǝ��̃C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertSequencerSpecific
(MIDITrack* pMIDITrack, long lTime, char* pBuf, long lLen);

/* �g���b�N�Ƀm�[�g�I�t�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertNoteOff 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel);

/* �g���b�N�Ƀm�[�g�I���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertNoteOn 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel);

/* �g���b�N�Ƀm�[�g�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertNote
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVel, long lDur);

/* �g���b�N�ɃL�[�A�t�^�[�^�b�`�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertKeyAftertouch
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lKey, long lVal);

/* �g���b�N�ɃR���g���[���`�F���W�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertControlChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lNum, long lVal);

/* �g���b�N��RPN�`�F���W�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertRPNChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC101, long lCC100, long lVal);

/* �g���b�N��NRPN�`�F���W�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertNRPNChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC99, long lCC98, long lVal);

/* �g���b�N�Ƀv���O�����`�F���W�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertProgramChange
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lNum);

/* �g���b�N�Ƀp�b�`�`�F���W�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertPatchChange 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lCC0, long lCC32, long lNum);

/* �g���b�N�Ƀ`�����l���A�t�^�[�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertChannelAftertouch 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lVal);

/* �g���b�N�Ƀs�b�`�x���h�C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertPitchBend 
	(MIDITrack* pMIDITrack, long lTime, long lCh, long lVal);

/* �g���b�N�ɃV�X�e���G�N�X�N���[�V���C�x���g�𐶐����đ}�� */
long __stdcall MIDITrack_InsertSysExEvent 
	(MIDITrack* pMIDITrack, long lTime, unsigned char* pBuf, long lLen);

/* �g���b�N����C�x���g��1��菜��(�C�x���g�I�u�W�F�N�g�͍폜���܂���) */
long __stdcall MIDITrack_RemoveSingleEvent (MIDITrack* pTrack, MIDIEvent* pEvent);

/* �g���b�N����C�x���g����菜��(�C�x���g�I�u�W�F�N�g�͍폜���܂���) */
long __stdcall MIDITrack_RemoveEvent (MIDITrack* pMIDITrack, MIDIEvent* pEvent);


/* MIDI�g���b�N�����V�g���b�N�ł��邩�ǂ����𒲂ׂ� */
long __stdcall MIDITrack_IsFloating (MIDITrack* pMIDITrack);


/* MIDI�g���b�N���Z�b�g�A�b�v�g���b�N�Ƃ��Đ��������Ƃ��m�F���� */
long __stdcall MIDITrack_CheckSetupTrack (MIDITrack* pMIDITrack);

/* MIDI�g���b�N���m���Z�b�g�A�b�v�g���b�N�Ƃ��Đ��������Ƃ��m�F���� */
long __stdcall MIDITrack_CheckNonSetupTrack (MIDITrack* pMIDITrack);

/* �^�C���R�[�h���~���b�����ɕϊ�(�w��g���b�N���̃e���|�C�x���g����Ɍv�Z) */
long __stdcall MIDITrack_TimeToMillisec (MIDITrack* pMIDITrack, long lTime);

/* �~���b�������^�C���R�[�h�ɕϊ�(�w��g���b�N���̃e���|�C�x���g����Ɍv�Z) */
long __stdcall MIDITrack_MillisecToTime (MIDITrack* pMIDITrack, long lMillisec);

/* �^�C���R�[�h�����߁F���F�e�B�b�N�ɕ���(�w��g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDITrack_BreakTimeEx
	(MIDITrack* pMIDITrack, long lTime, long* pMeasure, long* pBeat, long* pTick,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* �^�C���R�[�h�����߁F���F�e�B�b�N�ɕ���(�w��g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDITrack_BreakTime 
	(MIDITrack* pMIDITrack, long lTime, long* pMeasure, long* pBeat, long* pTick);

/* ���߁F���F�e�B�b�N����^�C���R�[�h�𐶐�(�w��g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDITrack_MakeTimeEx 
	(MIDITrack* pMIDITrack, long lMeasure, long lBeat, long lTick, long* pTime,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* ���߁F���F�e�B�b�N����^�C���R�[�h�𐶐�(�w��g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDITrack_MakeTime 
	(MIDITrack* pMIDITrack, long lMeasure, long lBeat, long lTick, long* pTime);

/* �w��ʒu�ɂ�����e���|���擾 */
long __stdcall MIDITrack_FindTempo
(MIDITrack* pMIDITrack, long lTime, long* pTempo);

/* �w��ʒu�ɂ����锏�q�L�����擾 */
long __stdcall MIDITrack_FindTimeSignature 
(MIDITrack* pMIDITrack, long lTime, long* pnn, long* pdd, long* pcc, long* pbb);

/* �w��ʒu�ɂ����钲���L�����擾 */
long __stdcall MIDITrack_FindKeySignature 
(MIDITrack* pMIDITrack, long lTime, long* psf, long* pmi);




/******************************************************************************/
/*                                                                            */
/*�@MIDIData�N���X�֐�                                                        */
/*                                                                            */
/******************************************************************************/

/* MIDI�f�[�^�̎w��g���b�N�̒��O�Ƀg���b�N��}�� */
long __stdcall MIDIData_InsertTrackBefore 
(MIDIData* pMIDIData, MIDITrack* pMIDITrack, MIDITrack* pTarget);

/* MIDI�f�[�^�̎w��g���b�N�̒���Ƀg���b�N��}�� */
long __stdcall MIDIData_InsertTrackAfter 
(MIDIData* pMIDIData, MIDITrack* pMIDITrack, MIDITrack* pTarget);

/* MIDI�f�[�^�Ƀg���b�N��ǉ�(�g���b�N�͗\�ߐ������Ă���) */
long __stdcall MIDIData_AddTrack (MIDIData* pMIDIData, MIDITrack* pMIDITrack);

/* MIDI�f�[�^���̃g���b�N�𕡐����� */
long __stdcall MIDIData_DuplicateTrack (MIDIData* pMIDIData, MIDITrack* pTrack);

/* MIDI�f�[�^����g���b�N������(�g���b�N���̋y�уg���b�N���̃C�x���g�͍폜���Ȃ�) */
long __stdcall MIDIData_RemoveTrack (MIDIData* pMIDIData, MIDITrack* pMIDITrack);

/* MIDI�f�[�^�̍폜(�܂܂��g���b�N�y�уC�x���g�����ׂč폜) */
void __stdcall MIDIData_Delete (MIDIData* pMIDIData);

/* MIDI�f�[�^�𐶐����AMIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_Create (long lFormat, long lNumTrack, long lTimeMode, long lResolution);

/* MIDI�f�[�^�̃t�H�[�}�b�g0/1/2���擾 */
long __stdcall MIDIData_GetFormat (MIDIData* pMIDIData);

/* MIDI�f�[�^�̃t�H�[�}�b�g0/1/2��ݒ�(�ύX���R���o�[�g�@�\���܂�) */
long __stdcall MIDIData_SetFormat (MIDIData* pMIDIData, long lFormat);

/* MIDI�f�[�^�̃^�C���x�[�X�擾 */
long __stdcall MIDIData_GetTimeBase (MIDIData* pMIDIData, long* pMode, long* pResolution);

/* MIDI�f�[�^�̃^�C���x�[�X�̃^�C�����[�h�擾 */
long __stdcall MIDIData_GetTimeMode (MIDIData* pMIDIData);

/* MIDI�f�[�^�̃^�C���x�[�X�̃��]�����[�V�����擾 */
long __stdcall MIDIData_GetTimeResolution (MIDIData* pMIDIData);

/* MIDI�f�[�^�̃^�C���x�[�X�ݒ� */
long __stdcall MIDIData_SetTimeBase (MIDIData* pMIDIData, long lMode, long lResolution);

/* MIDI�f�[�^�̃g���b�N���擾 */
long __stdcall MIDIData_GetNumTrack (MIDIData* pMIDIData);

/* �g���b�N�����J�E���g���A�e�g���b�N�̃C���f�b�N�X�Ƒ��g���b�N�����X�V���A�g���b�N����Ԃ��B */
long __stdcall MIDIData_CountTrack (MIDIData* pMIDIData);

/* XF�ł���Ƃ��AXF�̃��@�[�W�������擾(XF�łȂ����0) */
long __stdcall MIDIData_GetXFVersion (MIDIData* pMIDIData);

/* MIDI�f�[�^�̍ŏ��̃g���b�N�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDITrack* __stdcall MIDIData_GetFirstTrack (MIDIData* pMIDIData);

/* MIDI�f�[�^�̍Ō�̃g���b�N�ւ̃|�C���^���擾(�Ȃ����NULL) */
MIDITrack* __stdcall MIDIData_GetLastTrack (MIDIData* pMIDIData);

/* �w��C���f�b�N�X��MIDI�g���b�N�ւ̃|�C���^���擾����(�Ȃ����NULL) */
MIDITrack* __stdcall MIDIData_GetTrack (MIDIData* pMIDIData, long lTrackIndex);

/* MIDI�f�[�^�̊J�n����[Tick]���擾 */
long __stdcall MIDIData_GetBeginTime (MIDIData* pMIDIData);

/* MIDI�f�[�^�̏I������[Tick]���擾 */
long __stdcall MIDIData_GetEndTime (MIDIData* pMIDIData);

/* MIDI�f�[�^�̃^�C�g�����ȈՎ擾 */
char* __stdcall MIDIData_GetTitleA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetTitleW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetTitle MIDIData_GetTitleW
#else
#define MIDIData_GetTitle MIDIData_GetTitleA
#endif

/* MIDI�f�[�^�̃^�C�g�����ȈՐݒ� */
long __stdcall MIDIData_SetTitleA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetTitleW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetTitle MIDIData_SetTitleW
#else
#define MIDIData_SetTitle MIDIData_SetTitleA
#endif

/* MIDI�f�[�^�̃T�u�^�C�g�����ȈՎ擾 */
char* __stdcall MIDIData_GetSubTitleA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetSubTitleW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetSubTitle MIDIData_GetSubTitleW
#else
#define MIDIData_GetSubTitle MIDIData_GetSubTitleA
#endif

/* MIDI�f�[�^�̃T�u�^�C�g�����ȈՐݒ� */
long __stdcall MIDIData_SetSubTitleA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetSubTitleW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetSubTitle MIDIData_SetSubTitleW
#else
#define MIDIData_SetSubTitle MIDIData_SetSubTitleA
#endif

/* MIDI�f�[�^�̒��쌠���ȈՎ擾 */
char* __stdcall MIDIData_GetCopyrightA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetCopyrightW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetCopyright MIDIData_GetCopyrightW
#else
#define MIDIData_GetCopyright MIDIData_GetCopyrightA
#endif

/* MIDI�f�[�^�̒��쌠���ȈՐݒ� */
long __stdcall MIDIData_SetCopyrightA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetCopyrightW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetCopyright MIDIData_SetCopyrightW
#else
#define MIDIData_SetCopyright MIDIData_SetCopyrightA
#endif

/* MIDI�f�[�^�̃R�����g���ȈՎ擾 */
char* __stdcall MIDIData_GetCommentA (MIDIData* pMIDIData, char* pData, long lLen);
wchar_t* __stdcall MIDIData_GetCommentW (MIDIData* pMIDIData, wchar_t* pData, long lLen);
#ifdef UNICODE
#define MIDIData_GetComment MIDIData_GetCommentW
#else
#define MIDIData_GetComment MIDIData_GetCommentA
#endif

/* MIDI�f�[�^�̃R�����g���ȈՐݒ� */
long __stdcall MIDIData_SetCommentA (MIDIData* pMIDIData, const char* pszData);
long __stdcall MIDIData_SetCommentW (MIDIData* pMIDIData, const wchar_t* pszData);
#ifdef UNICODE
#define MIDIData_SetComment MIDIData_SetCommentW
#else
#define MIDIData_SetComment MIDIData_SetCommentA
#endif

/* �^�C���R�[�h���~���b�ɕϊ�(�t�H�[�}�b�g0/1�̏ꍇ�̂�) */
long __stdcall MIDIData_TimeToMillisec (MIDIData* pMIDIData, long lTime);

/* �~���b���^�C���R�[�h�ɕϊ�(�t�H�[�}�b�g0/1�̏ꍇ�̂�) */
long __stdcall MIDIData_MillisecToTime (MIDIData* pMIDIData, long lMillisec);

/* �^�C���R�[�h�����߁F���F�e�B�b�N�ɕ���(�ŏ��̃g���b�N���̔��q�L������v�Z) */
long __stdcall MIDIData_BreakTime 
	(MIDIData* pMIDIData, long lTime, long* pMeasure, long* pBeat, long* pTick);

/* �^�C���R�[�h�����߁F���F�e�B�b�N�ɕ���(�ŏ��̃g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDIData_BreakTimeEx
	(MIDIData* pMIDIData, long lTime, long* pMeasure, long* pBeat, long* pTick,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* ���߁F���F�e�B�b�N����^�C���R�[�h�𐶐�(�ŏ��̃g���b�N���̔��q�L������v�Z) */
long __stdcall MIDIData_MakeTime
	(MIDIData* pMIDIData, long lMeasure, long lBeat, long lTick, long* pTime);

/* ���߁F���F�e�B�b�N����^�C���R�[�h�𐶐�(�ŏ��̃g���b�N���̔��q�L������Ɍv�Z) */
long __stdcall MIDIData_MakeTimeEx
	(MIDIData* pMIDIData, long lMeasure, long lBeat, long lTick, long* pTime,
	long* pnn, long* pdd, long* pcc, long* pbb);

/* �w��ʒu�ɂ�����e���|���擾 */
long __stdcall MIDIData_FindTempo
	(MIDIData* pMIDIData, long lTime, long* pTempo);

/* �w��ʒu�ɂ����锏�q�L�����擾 */
long __stdcall MIDIData_FindTimeSignature 
	(MIDIData* pMIDIData, long lTime, long* pnn, long* pdd, long* pcc, long* pbb);

/* �w��ʒu�ɂ����钲���L�����擾 */
long __stdcall MIDIData_FindKeySignature 
	(MIDIData* pMIDIData, long lTime, long* psf, long* pmi);

/* ����MIDI�f�[�^�ɕʂ�MIDI�f�[�^���}�[�W����(20080715�p�~) */
/*long __stdcall MIDIData_Merge (MIDIData* pMIDIData, MIDIData* pMergeData, */
/*	long lTime, long lFlags, long* pInsertedEventCount, long* pDeletedEventCount);*/

/* �ۑ��E�ǂݍ��ݗp�֐� */

/* MIDIData���X�^���_�[�hMIDI�t�@�C��(SMF)����ǂݍ��݁A*/
/* �V����MIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_LoadFromSMFA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromSMFW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromSMF MIDIData_LoadFromSMFW
#else
#define MIDIData_LoadFromSMF MIDIData_LoadFromSMFA
#endif

/* MIDI�f�[�^���X�^���_�[�hMIDI�t�@�C��(SMF)�Ƃ��ĕۑ� */
long __stdcall MIDIData_SaveAsSMFA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsSMFW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsSMF MIDIData_SaveAsSMFW
#else
#define MIDIData_SaveAsSMF MIDIData_SaveAsSMFA
#endif

/* MIDIData���e�L�X�g�t�@�C������ǂݍ��݁A */
/* �V����MIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_LoadFromTextA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromTextW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromText MIDIData_LoadFromTextW
#else
#define MIDIData_LoadFromText MIDIData_LoadFromTextA
#endif

/* MIDIData���e�L�X�g�t�@�C���Ƃ��ĕۑ� */
long __stdcall MIDIData_SaveAsTextA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsTextW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsText MIDIData_SaveAsTextW
#else
#define MIDIData_SaveAsText MIDIData_SaveAsTextA
#endif

/* MIDIData���o�C�i���t�@�C������ǂݍ��݁A*/
/* �V����MIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_LoadFromBinaryA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromBinaryW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromBinary MIDIData_LoadFromBinaryW
#else
#define MIDIData_LoadFromBinary MIDIData_LoadFromBinaryA
#endif

/* MIDIData���o�C�i���t�@�C���ɕۑ� */
long __stdcall MIDIData_SaveAsBinaryA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsBinaryW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsBinary MIDIData_SaveAsBinaryW
#else
#define MIDIData_SaveAsBinary MIDIData_SaveAsBinaryA
#endif

/* MIDIData��Cherrry�t�@�C��(*.chy)����ǂݍ��݁A */
/* �V����MIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_LoadFromCherryA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromCherryW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromCherry MIDIData_LoadFromCherryW
#else
#define MIDIData_LoadFromCherry MIDIData_LoadFromCherryA
#endif

/* MIDI�f�[�^��Cherry�t�@�C��(*.chy)�ɕۑ� */
long __stdcall MIDIData_SaveAsCherryA (MIDIData* pMIDIData, const char* pszFileName);
long __stdcall MIDIData_SaveAsCherryW (MIDIData* pMIDIData, const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_SaveAsCherry MIDIData_SaveAsCherryW
#else
#define MIDIData_SaveAsCherry MIDIData_SaveAsCherryA
#endif

/* MIDI�f�[�^��MIDICSV�t�@�C��(*.csv)����ǂݍ��� */
/* �V����MIDI�f�[�^�ւ̃|�C���^��Ԃ�(���s��NULL) */
MIDIData* __stdcall MIDIData_LoadFromMIDICSVA (const char* pszFileName);
MIDIData* __stdcall MIDIData_LoadFromMIDICSVW (const wchar_t* pszFileName);
#ifdef UNICODE
#define MIDIData_LoadFromMIDICSV MIDIData_LoadFromMIDICSVW
#else
#define MIDIData_LoadFromMIDICSV MIDIData_LoadFromMIDICSVA
#endif

/* MIDI�f�[�^��MIDICSV�t�@�C��(*.csv)�Ƃ��ĕۑ� */
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
