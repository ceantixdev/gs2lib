/*
 * include/IEnums.h
 *
 * Copyright 2007-2019 OpenGraal
 *
 * This file is part of GS2Emu.
 *
 * GS2Emu is free software : you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * GS2Emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GS2Emu. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef IENUMS_H
#define IENUMS_H

/*
	Player
*/
// PLI_UNKNOWN## are packets sent by the client whose
// purpose is unknown.
typedef enum PlayerToServer
{
	PLI_LEVELWARP		= 0,
	PLI_BOARDMODIFY		= 1,
	PLI_PLAYERPROPS		= 2,
	PLI_NPCPROPS		= 3,
	PLI_BOMBADD			= 4,
	PLI_BOMBDEL			= 5,
	PLI_TOALL			= 6,
	PLI_HORSEADD		= 7,
	PLI_HORSEDEL		= 8,
	PLI_ARROWADD		= 9,
	PLI_FIRESPY			= 10,
	PLI_THROWCARRIED	= 11,
	PLI_ITEMADD			= 12,
	PLI_ITEMDEL			= 13,
	PLI_CLAIMPKER		= 14,
	PLI_BADDYPROPS		= 15,
	PLI_BADDYHURT		= 16,
	PLI_BADDYADD		= 17,
	PLI_FLAGSET			= 18,
	PLI_FLAGDEL			= 19,
	PLI_OPENCHEST		= 20,
	PLI_PUTNPC			= 21,
	PLI_NPCDEL			= 22,
	PLI_WANTFILE		= 23,
	PLI_SHOWIMG			= 24,
	PLI_UNKNOWN25		= 25,
	PLI_HURTPLAYER		= 26,
	PLI_EXPLOSION		= 27,
	PLI_PRIVATEMESSAGE	= 28,
	PLI_NPCWEAPONDEL	= 29,
	PLI_LEVELWARPMOD	= 30,
	PLI_PACKETCOUNT		= 31,
	PLI_ITEMTAKE		= 32,
	PLI_WEAPONADD		= 33,
	PLI_UPDATEFILE		= 34,
	PLI_ADJACENTLEVEL	= 35,
	PLI_HITOBJECTS		= 36,
	PLI_LANGUAGE		= 37,
	PLI_TRIGGERACTION	= 38,
	PLI_MAPINFO			= 39,
	PLI_SHOOT			= 40,
	PLI_SERVERWARP		= 41,
	PLI_MUTEPLAYER		= 43,	// Triggered via playerlist -> mute, looks like {GSHORT playerId}{GBYTE 1/0}
	PLI_PROCESSLIST		= 44,
	PLI_UNKNOWN46		= 46,	// Always is 1.  Might be a player count for the gmap level.
	PLI_VERIFYWANTSEND	= 47,	// {47}{GINT5:CRC32 Checksum]{GSTRING: Filename} - Check if the file is out of date, and if so send it
	PLI_SHOOT2			= 48,
	PLI_RAWDATA			= 50,
	PLI_RC_SERVEROPTIONSGET		= 51,
	PLI_RC_SERVEROPTIONSSET		= 52,
	PLI_RC_FOLDERCONFIGGET		= 53,
	PLI_RC_FOLDERCONFIGSET		= 54,
	PLI_RC_RESPAWNSET			= 55,
	PLI_RC_HORSELIFESET			= 56,
	PLI_RC_APINCREMENTSET		= 57,
	PLI_RC_BADDYRESPAWNSET		= 58,
	PLI_RC_PLAYERPROPSGET		= 59,
	PLI_RC_PLAYERPROPSSET		= 60,
	PLI_RC_DISCONNECTPLAYER		= 61,
	PLI_RC_UPDATELEVELS			= 62,
	PLI_RC_ADMINMESSAGE			= 63,
	PLI_RC_PRIVADMINMESSAGE		= 64,
	PLI_RC_LISTRCS				= 65,
	PLI_RC_DISCONNECTRC			= 66,
	PLI_RC_APPLYREASON			= 67,
	PLI_RC_SERVERFLAGSGET		= 68,
	PLI_RC_SERVERFLAGSSET		= 69,
	PLI_RC_ACCOUNTADD			= 70,
	PLI_RC_ACCOUNTDEL			= 71,
	PLI_RC_ACCOUNTLISTGET		= 72,
	PLI_RC_PLAYERPROPSGET2		= 73,	// Gets by player ID
	PLI_RC_PLAYERPROPSGET3		= 74,	// Gets by player account name.
	PLI_RC_PLAYERPROPSRESET		= 75,
	PLI_RC_PLAYERPROPSSET2		= 76,
	PLI_RC_ACCOUNTGET			= 77,
	PLI_RC_ACCOUNTSET			= 78,
	PLI_RC_CHAT					= 79,
	PLI_PROFILEGET				= 80,
	PLI_PROFILESET				= 81,
	PLI_RC_WARPPLAYER			= 82,
	PLI_RC_PLAYERRIGHTSGET		= 83,
	PLI_RC_PLAYERRIGHTSSET		= 84,
	PLI_RC_PLAYERCOMMENTSGET	= 85,
	PLI_RC_PLAYERCOMMENTSSET	= 86,
	PLI_RC_PLAYERBANGET			= 87,
	PLI_RC_PLAYERBANSET			= 88,
	PLI_RC_FILEBROWSER_START	= 89,
	PLI_RC_FILEBROWSER_CD		= 90,
	PLI_RC_FILEBROWSER_END		= 91,
	PLI_RC_FILEBROWSER_DOWN		= 92,
	PLI_RC_FILEBROWSER_UP		= 93,
	PLI_NPCSERVERQUERY			= 94,
	PLI_RC_FILEBROWSER_MOVE		= 96,
	PLI_RC_FILEBROWSER_DELETE	= 97,
	PLI_RC_FILEBROWSER_RENAME	= 98,
	PLI_NC_NPCGET				= 103,	// {103}{INT id}
	PLI_NC_NPCDELETE			= 104,	// {104}{INT id}
	PLI_NC_NPCRESET				= 105,	// {105}{INT id}
	PLI_NC_NPCSCRIPTGET			= 106,	// {106}{INT id}
	PLI_NC_NPCWARP				= 107,	// {107}{INT id}{CHAR x*2}{CHAR y*2}{level}
	PLI_NC_NPCFLAGSGET			= 108,	// {108}{INT id}
	PLI_NC_NPCSCRIPTSET			= 109,	// {109}{INT id}{GSTRING script}
	PLI_NC_NPCFLAGSSET			= 110,	// {110}{INT id}{GSTRING flags}
	PLI_NC_NPCADD				= 111,	// {111}{GSTRING info}  - (info) name,id,type,scripter,starting level,x,y
	PLI_NC_CLASSEDIT			= 112,	// {112}{class}
	PLI_NC_CLASSADD				= 113,	// {113}{CHAR name length}{name}{GSTRING script}
	PLI_NC_LOCALNPCSGET			= 114,	// {114}{level}
	PLI_NC_WEAPONLISTGET		= 115,	// {115}
	PLI_NC_WEAPONGET			= 116,	// {116}{weapon}
	PLI_NC_WEAPONADD			= 117,	// {117}{CHAR weapon length}{weapon}{CHAR image length}{image}{code}
	PLI_NC_WEAPONDELETE			= 118,	// {118}{weapon}
	PLI_NC_CLASSDELETE			= 119,	// {119}{class}

	PLI_REQUESTUPDATEBOARD		= 130,  // {130}{CHAR level length}{level}{INT5 modtime}{SHORT x}{SHORT y}{SHORT width}{SHORT height}

	PLI_NC_LEVELLISTGET			= 150,	// {150}
	PLI_NC_LEVELLISTSET			= 151,	// {151}{GSTRING levels}

	PLI_REQUESTTEXT				= 152,	// Gets a value from the server.
	PLI_SENDTEXT				= 154,	// Sets a value on the server.

	PLI_RC_LARGEFILESTART		= 155,
	PLI_RC_LARGEFILEEND			= 156,

	PLI_UPDATEGANI				= 157,	// Something to do with ganis.		-- Likely: PLI_UPDATEGANI [similar to UPDATECLASS], replies with 253? multiple replies in one
	PLI_UPDATESCRIPT			= 158,	// {158}{script} Requests a script from the server.
	PLI_UPDATEPACKAGEREQUESTFILE= 159,	// {159]{(char)order?]{packagefilename}{modtime}
	PLI_RC_FOLDERDELETE			= 160,
	PLI_UPDATECLASS				= 161,	// {161}{INT5 modtime}{name} Class request.
	PLI_RC_UNKNOWN162			= 162	// Blank packet, sent by RC3 beta.
} PlayerToServer;

typedef enum ServerToPlayer
{
	PLO_LEVELBOARD				= 0,
	PLO_LEVELLINK				= 1,
	PLO_BADDYPROPS				= 2,
	PLO_NPCPROPS				= 3,
	PLO_LEVELCHEST				= 4,
	PLO_LEVELSIGN				= 5,
	PLO_LEVELNAME				= 6,
	PLO_BOARDMODIFY				= 7,
	PLO_OTHERPLPROPS			= 8,
	PLO_PLAYERPROPS				= 9,
	PLO_ISLEADER				= 10,
	PLO_BOMBADD					= 11,
	PLO_BOMBDEL					= 12,
	PLO_TOALL					= 13,
	PLO_PLAYERWARP				= 14,
	PLO_WARPFAILED				= 15,
	PLO_DISCMESSAGE				= 16,
	PLO_HORSEADD				= 17,
	PLO_HORSEDEL				= 18,
	PLO_ARROWADD				= 19,
	PLO_FIRESPY					= 20,
	PLO_THROWCARRIED			= 21,
	PLO_ITEMADD					= 22,
	PLO_ITEMDEL					= 23,
	PLO_NPCMOVED				= 24,	// What does this do? Joey: Apparently just hides the npc ... for level warps??
	PLO_SIGNATURE				= 25,
	PLO_NPCACTION				= 26,	// What does this do?  Codr note: Unhandled by 6.037.
	PLO_BADDYHURT				= 27,
	PLO_FLAGSET					= 28,
	PLO_NPCDEL					= 29,
	PLO_FILESENDFAILED			= 30,
	PLO_FLAGDEL					= 31,
	PLO_SHOWIMG					= 32,
	PLO_NPCWEAPONADD			= 33,
	PLO_NPCWEAPONDEL			= 34,
	PLO_RC_ADMINMESSAGE			= 35,
	PLO_EXPLOSION				= 36,
	PLO_PRIVATEMESSAGE			= 37,
	PLO_PUSHAWAY				= 38,	// What does this do?
	PLO_LEVELMODTIME			= 39,
	PLO_HURTPLAYER				= 40,
	PLO_STARTMESSAGE			= 41,	// Unhandled by 6.037. -Codr
	PLO_NEWWORLDTIME			= 42,
	PLO_DEFAULTWEAPON			= 43,
	PLO_HASNPCSERVER			= 44,	// If sent, the client won't update npc props.  Codr note: Unhandled by 5.07+.
	PLO_FILEUPTODATE			= 45,
	PLO_HITOBJECTS				= 46,
	PLO_STAFFGUILDS				= 47,
	PLO_TRIGGERACTION			= 48,
	PLO_PLAYERWARP2				= 49,	// Bytes 1-3 are x/y/z. 4 = level x in gmap, 5 = level y in gmap.
	PLO_RC_ACCOUNTADD			= 50,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_ACCOUNTSTATUS		= 51,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_ACCOUNTNAME			= 52,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_ACCOUNTDEL			= 53,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_ACCOUNTPROPS			= 54,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_ADDPLAYER				= 55,	// Unhandled by 5.07+. -Codr
	PLO_DELPLAYER				= 56,	// Unhandled by 5.07+. -Codr
	PLO_RC_ACCOUNTPROPSGET		= 57,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_ACCOUNTCHANGE		= 58,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_PLAYERPROPSCHANGE	= 59,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_UNKNOWN60				= 60,	// Unhandled by 5.07+. -Codr
	PLO_RC_SERVERFLAGSGET		= 61,	// Unhandled by 5.07+. -Codr
	PLO_RC_PLAYERRIGHTSGET		= 62,	// Unhandled by 5.07+. -Codr
	PLO_RC_PLAYERCOMMENTSGET	= 63,	// Unhandled by 5.07+. -Codr
	PLO_RC_PLAYERBANGET			= 64,	// Unhandled by 5.07+. -Codr
	PLO_RC_FILEBROWSER_DIRLIST	= 65,	// Unhandled by 5.07+. -Codr
	PLO_RC_FILEBROWSER_DIR		= 66,	// Unhandled by 5.07+. -Codr
	PLO_RC_FILEBROWSER_MESSAGE	= 67,
	PLO_LARGEFILESTART			= 68,
	PLO_LARGEFILEEND			= 69,
	PLO_RC_ACCOUNTLISTGET		= 70,	// Unhandled by 5.07+. -Codr
	PLO_RC_PLAYERPROPS			= 71,	// Deprecated.  Codr note: Unhandled by 6.037.
	PLO_RC_PLAYERPROPSGET		= 72,	// Unhandled by 5.07+. -Codr
	PLO_RC_ACCOUNTGET			= 73,	// Unhandled by 5.07+. -Codr
	PLO_RC_CHAT					= 74,
	PLO_PROFILE					= 75,	// Unhandled by 6.037. -Codr
	PLO_RC_SERVEROPTIONSGET		= 76,	// Unhandled by 5.07+. -Codr
	PLO_RC_FOLDERCONFIGGET		= 77,	// Unhandled by 5.07+. -Codr
	PLO_NC_CONTROL				= 78,	// HIJACKED BY GR!  No clue as to its official purpose.  Codr note: Unhandled by 5.07+.
	PLO_NPCSERVERADDR			= 79,	// Bytes 1-2 are 0 and 2, followed by a string formatted as <ipaddr>,<port>.  Codr note: Unhandled by 5.07+.
	PLO_NC_LEVELLIST			= 80,	// {80}{GSTRING levels}  Codr note: Unhandled by 5.07+.
	PLO_UNKNOWN81				= 81,	// Unhandled by 5.07+. -Codr
	PLO_SERVERTEXT				= 82,	// Answer to PLI_REQUESTTEXT and PLI_SENDTEXT.
	PLO_UNKNOWN83				= 83,	// Unhandled by 5.07+. -Codr
	PLO_LARGEFILESIZE			= 84,
	PLO_RAWDATA					= 100,	// {100}{INT3 length}  Codr note: Unhandled by 5.07+.
	PLO_BOARDPACKET				= 101,
	PLO_FILE					= 102,
	PLO_RC_MAXUPLOADFILESIZE	= 103,	// {GINT5} - Upload file size limit in bytes. Default to 20 mebibytes
	PLO_UNKNOWN104				= 104,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_UPDATEPACKAGESIZE		= 105,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_UPDATEPACKAGEDONE		= 106,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_BOARDLAYER				= 107,	// Basically PLO_LEVELBOARD for extra level layers.
	PLO_UNKNOWN109				= 109,	// Valid message in 6.037. -Codr
	PLO_UNKNOWN111				= 111,	// Valid message in 6.037. -Codr
	PLO_UNKNOWN124				= 124,	// 5/26/2019: RC3 receives this, only hint I seen was regarding receiving player flags? Didn't try to test it though
	PLO_NPCBYTECODE				= 131,	// Compiled Torque-script for an NPC. {131}{INT3 id}{code}
	PLO_UNKNOWN132				= 132,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	PLO_UNKNOWN133				= 133,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	PLO_GANISCRIPT				= 134,	// Might be used for package downloads. Looks to send gani scripts to client
	PLO_NPCWEAPONSCRIPT			= 140,	// {140}{INT2 info_length}{script}
	PLO_NPCDEL2					= 150,	// {150}{CHAR level_length}{level}{INT3 npcid}
	PLO_HIDENPCS				= 151,
	PLO_SAY2					= 153,	// Also used for signs. {153}{text}
	PLO_FREEZEPLAYER2			= 154,	// Blank.
	PLO_UNFREEZEPLAYER			= 155,	// Blank.
	PLO_SETACTIVELEVEL			= 156,	// Sets the level to receive chests, baddies, NPCs, etc.
	PLO_NC_NPCATTRIBUTES		= 157,	// {157}{GSTRING attributes}  Codr note: Unhandled by 5.07+.
	PLO_NC_NPCADD				= 158,	// {158}{INT id}{CHAR 50}{CHAR name length}{name}{CHAR 51}{CHAR type length}{type}{CHAR 52}{CHAR level length}{level}  Codr note: Unhandled by 5.07+.
	PLO_NC_NPCDELETE			= 159,	// {159}{INT id}  Codr note: Unhandled by 5.07+.
	PLO_NC_NPCSCRIPT			= 160,	// {160}{INT id}{GSTRING script}  Codr note: Unhandled by 5.07+.
	PLO_NC_NPCFLAGS				= 161,	// {161}{INT id}{GSTRING flags}  Codr note: Unhandled by 5.07+.
	PLO_NC_CLASSGET				= 162,	// {162}{CHAR name length}{name}{GSTRING script}  Codr note: Unhandled by 5.07+.
	PLO_NC_CLASSADD				= 163,	// {163}{class}  Codr note: Unhandled by 5.07+.
	PLO_NC_LEVELDUMP			= 164,	// Unhandled by 5.07+. -Codr
	PLO_MOVE					= 165,	// Unhandled by 6.037. -Codr
	PLO_UNKNOWN166				= 166,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_NC_WEAPONLISTGET		= 167,	// {167}{CHAR name1 length}{name1}{CHAR name2 length}{name2}...  Codr note: Unhandled by 5.07+.
	PLO_UNKNOWN168				= 168,	// Login server sends this.  Blank packet.
	PLO_UNKNOWN169				= 169,	// Valid message in 5.07.  It's strange... the parameter seems to be a direct pointer value which would be difficult for the server to know about unless the client actually sends that information.  I don't know what purpose that could serve, however.  Unhandled by 6.037. -Codr
	PLO_GHOSTMODE				= 170,
	PLO_BIGMAP					= 171,	// Unhandled by 6.037. -Codr
	PLO_MINIMAP					= 172,	// [172] zodiacminimap.txt,zodiacworldminimap3.png,10,10
	PLO_GHOSTTEXT				= 173,	// {173}{text}  Shows static text in lower-right corner of screen only when in ghost mode.
	PLO_GHOSTICON				= 174,	// Pass 1 to enable the ghost icon
	PLO_SHOOT					= 175,	// Unhandled by 6.037. -Codr
	PLO_FULLSTOP				= 176,	// Sending this causes the entire client to not respond to normal input and it hides the HUD.
	PLO_FULLSTOP2				= 177,	// Sending this causes the entire client to not respond to normal input and it hides the HUD.  Codr note: Unhandled by 5.07+.
	PLO_SERVERWARP				= 178,
	PLO_RPGWINDOW				= 179,
	PLO_STATUSLIST				= 180,
	PLO_UNKNOWN181				= 181,	// Valid message in 5.07.  The code it uses is unique.  Unhandled by 6.037. -Codr
	PLO_LISTPROCESSES			= 182,
	PLO_UNKNOWN183				= 183,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_UNKNOWN184				= 184,	// Valid message in 5.07.  The code it uses is unique.  The string "screenshots" is present in the code.  I didn't look in detail.  Unhandled by 6.037. -Codr
	PLO_UNKNOWN185				= 185,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_UNKNOWN186				= 186,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_UPDATEPACKAGEISUPDATED	= 187,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_NC_CLASSDELETE			= 188,	// {188}{class}  Codr note: Unhandled by 5.07+.
	PLO_MOVE2					= 189,	// {189}{INT id}...
	PLO_UNKNOWN190				= 190,	// Was blank.  Sent before weapon list. NOTE: Sending this packet makes the client login to irc, request bantypes, pmguilds, pmservers, globalpms, buddytracking and stuff... Mainly tied to setTex
	PLO_SHOOT2					= 191,	// Valid message in 5.07 and 6.037.  The code it uses is unique. -Codr
	PLO_NC_WEAPONGET			= 192,	// {192}{CHAR name length}{name}{CHAR image length}{image}{script}  Codr note: Unhandled by 5.07+.
	PLO_UNKNOWN193				= 193,	// Valid message in 5.07.  The code it uses is unique.  The first parameter is likely a 5-byte integer.  There may be more.  Unhandled by 6.037. -Codr
	PLO_CLEARWEAPONS			= 194,	// Was blank.  Sent before weapon list.
	PLO_UNKNOWN195				= 195,	// Something to do with ganis.  [195] )twiz-icon"SETBACKTO "

	// Seems to register NPCs or something on the client.
	// Also is related to PLI_UPDATESCRIPT as it sends the last modification time of the NPC/weapon.  The v5 client stores weapon scripts offline.
	PLO_UNKNOWN197				= 197,	// Seems to register npcs on the client.  Also is used by client to see if it needs to get a newer version of the offline cache of the NPC.
	PLO_UNKNOWN198				= 198,	// Valid message in 6.037. -Codr
} ServerToPlayer;

enum
{
	PLFLAG_NOMASSMESSAGE	= 0x01,
	PLFLAG_ONLYSHOWONELEVEL	= 0x02,
	PLFLAG_NOTOALL			= 0x04,
	PLFLAG_VOICEDISABLED	= 0x08
};

enum
{
	PLSTATUS_PAUSED			= 0x01,
	PLSTATUS_HIDDEN			= 0x02,
	PLSTATUS_MALE			= 0x04,
	PLSTATUS_DEAD			= 0x08,
	PLSTATUS_ALLOWWEAPONS	= 0x10,
	PLSTATUS_HIDESWORD		= 0x20,
	PLSTATUS_HASSPIN		= 0x40,
};

enum
{
	PLTYPE_AWAIT		= (int)(-1),
	PLTYPE_CLIENT		= (int)(1 << 0),
	PLTYPE_RC			= (int)(1 << 1),
	PLTYPE_NPCSERVER	= (int)(1 << 2),
	PLTYPE_NC			= (int)(1 << 3),
	PLTYPE_CLIENT2		= (int)(1 << 4),
	PLTYPE_CLIENT3		= (int)(1 << 5),
	PLTYPE_RC2			= (int)(1 << 6),
	PLTYPE_EXTERNAL		= (int)(1 << 7),	// IRC client?
	PLTYPE_WEB			= (int)(1 << 8),

	PLTYPE_ANYCLIENT	= (int)(PLTYPE_CLIENT | PLTYPE_CLIENT2 | PLTYPE_CLIENT3 | PLTYPE_WEB ),
	PLTYPE_ANYRC		= (int)(PLTYPE_RC | PLTYPE_RC2),
	PLTYPE_ANYNC		= (int)(PLTYPE_NC),
	PLTYPE_ANYCONTROL	= (int)(PLTYPE_ANYRC | PLTYPE_ANYNC),
	PLTYPE_ANYPLAYER	= (int)(PLTYPE_ANYCLIENT | PLTYPE_ANYRC),
	PLTYPE_NONITERABLE	= (int)(PLTYPE_NPCSERVER | PLTYPE_ANYNC | PLTYPE_EXTERNAL)
};

/*
	Serverlist Enumerators
*/
typedef enum ServerToListServer
{
	SVO_SETNAME			= 0,
	SVO_SETDESC			= 1,
	SVO_SETLANG			= 2,
	SVO_SETVERS			= 3,
	SVO_SETURL			= 4,
	SVO_SETIP			= 5,
	SVO_SETPORT			= 6,
	SVO_SETPLYR			= 7,
	SVO_VERIACC			= 8,	// deprecated
	SVO_VERIGUILD		= 9,
	SVO_GETFILE			= 10,	// deprecated
	SVO_NICKNAME		= 11,
	SVO_GETPROF			= 12,
	SVO_SETPROF			= 13,
	SVO_PLYRADD			= 14,
	SVO_PLYRREM			= 15,
	SVO_PING			= 16,
	SVO_VERIACC2		= 17,
	SVO_SETLOCALIP		= 18,
	SVO_GETFILE2		= 19,	// deprecated
	SVO_UPDATEFILE		= 20,
	SVO_GETFILE3		= 21,
	SVO_NEWSERVER		= 22,
	SVO_SERVERHQPASS	= 23,
	SVO_SERVERHQLEVEL	= 24,
	SVO_SERVERINFO		= 25,
	SVO_REQUESTLIST		= 26,
	SVO_REQUESTSVRINFO	= 27,
	SVO_REQUESTBUDDIES	= 28,
	SVO_PMPLAYER		= 29,
	SVO_REGISTERV3		= 30,
	SVO_SENDTEXT		= 31,
	SVO_PACKETCOUNT,
} ServerToListServer;

typedef enum ListServerToServer
{
	SVI_VERIACC			= 0,	// deprecated
	SVI_VERIGUILD		= 1,
	SVI_FILESTART		= 2,	// deprecated
	SVI_FILEEND			= 3,	// deprecated
	SVI_FILEDATA		= 4,	// deprecated
	SVI_VERSIONOLD		= 5,
	SVI_VERSIONCURRENT	= 6,
	SVI_PROFILE			= 7,
	SVI_ERRMSG			= 8,
	SVI_NULL4			= 9,
	SVI_NULL5			= 10,
	SVI_VERIACC2		= 11,
	SVI_FILESTART2		= 12,	// deprecated
	SVI_FILEDATA2		= 13,	// deprecated
	SVI_FILEEND2		= 14,	// deprecated
	SVI_FILESTART3		= 15,
	SVI_FILEDATA3		= 16,
	SVI_FILEEND3		= 17,
	SVI_SERVERINFO		= 18,
	SVI_REQUESTTEXT		= 19,
	SVI_SENDTEXT		= 20,
	SVI_PMPLAYER		= 29,
	SVI_ASSIGNPCID		= 30,
	SVI_PING			= 99,
	SVI_RAWDATA			= 100,
	SVI_PACKETCOUNT
} ListServerToServer;

#endif
