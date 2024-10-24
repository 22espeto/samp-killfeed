#include <YSI_Coding\y_hooks>

#define FEED_MAX_LINES 6
#define FEED_TIME 5000
#define FEED_SIZE 64 * FEED_MAX_LINES

new
	PlayerText:KillFeedTd[MAX_PLAYERS],
	KillFeedLines[MAX_PLAYERS],
	KillFeedTimer[MAX_PLAYERS],
	KillFeedString[MAX_PLAYERS][FEED_MAX_LINES][FEED_SIZE]
;

hook OnPlayerConnect(playerid)
{
	CreateFeedTD(playerid);
	return true;
}

hook OnPlayerDisconnect(playerid)
{
	DestroyFeedTD(playerid);

	for(new i; i < FEED_MAX_LINES; i ++)
		KillFeedString[playerid][i] = "_";

	KillFeedLines[playerid] = 0;
	return true;
}

hook OnPlayerDeath(playerid, killerid, WEAPON:reason)
{
	if(killerid == INVALID_PLAYER_ID || playerid == INVALID_PLAYER_ID)
		return false;

	UpdateKillFeed(killerid, playerid);
	return true;
}

UpdateKillFeed(killerid, playerid)
{
	new killLine[FEED_SIZE], killLine2[FEED_SIZE], killedName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, killedName, MAX_PLAYER_NAME);

	if(KillFeedLines[killerid] == FEED_MAX_LINES)
	{
		for(new i; i < FEED_MAX_LINES; i ++)
			KillFeedString[killerid][i] = "_";

		KillFeedLines[killerid] = 0;
	}

	format(killLine, sizeof killLine, "~w~~h~You sent ~r~~h~%s ~w~~h~to heaven~n~", killedName);
	format(KillFeedString[killerid][KillFeedLines[killerid]], FEED_SIZE, killLine);
	
	for(new i; i < FEED_MAX_LINES; i ++)
		strcat(killLine2, KillFeedString[killerid][i]);

	KillFeedLines[killerid] ++;

	PlayerTextDrawSetString(killerid, KillFeedTd[killerid], killLine2);
	PlayerTextDrawShow(killerid, KillFeedTd[killerid]);

	KillTimer(KillFeedTimer[killerid]);
	KillFeedTimer[killerid] = SetTimerEx("UpdateKillFeedLine", FEED_TIME, false, "d", killerid);
	return true;
}

forward UpdateKillFeedLine(playerid);
public UpdateKillFeedLine(playerid)
{
	if(KillFeedLines[playerid] > 0)
	{
		new tmp[FEED_SIZE];

		for(new i; i < KillFeedLines[playerid]; i++){
			if(i+1 <= FEED_MAX_LINES)
				KillFeedString[playerid][i] = KillFeedString[playerid][i+1];
		}

		KillFeedString[playerid][KillFeedLines[playerid]] = "_";
		KillFeedLines[playerid]--;
		
		for(new i; i < KillFeedLines[playerid]; i++)
			strcat(tmp, KillFeedString[playerid][i]);
		
		PlayerTextDrawSetString(playerid, KillFeedTd[playerid], tmp);
		PlayerTextDrawShow(playerid, KillFeedTd[playerid]);

		KillTimer(KillFeedTimer[playerid]);
		KillFeedTimer[playerid] = SetTimerEx("UpdateKillFeedLine", FEED_TIME / 2, false, "d", playerid);
	}
	else
	{
		for(new i; i < FEED_MAX_LINES; i ++){
			KillFeedString[playerid][i] = "_";
		}
		KillFeedLines[playerid] = 0;
		PlayerTextDrawHide(playerid, KillFeedTd[playerid]);
	}

	return true;
}























CreateFeedTD(playerid)
{
    KillFeedTd[playerid] = CreatePlayerTextDraw(playerid, 319.000000, 389.000000, "");
    PlayerTextDrawLetterSize(playerid, KillFeedTd[playerid], 0.250000, 0.800000);
    PlayerTextDrawAlignment(playerid, KillFeedTd[playerid], 2);
    PlayerTextDrawColor(playerid, KillFeedTd[playerid], -1);
    PlayerTextDrawSetShadow(playerid, KillFeedTd[playerid], 0);
    PlayerTextDrawSetOutline(playerid, KillFeedTd[playerid], 1);
    PlayerTextDrawBackgroundColor(playerid, KillFeedTd[playerid], 80);
    PlayerTextDrawFont(playerid, KillFeedTd[playerid], 1);
    PlayerTextDrawSetProportional(playerid, KillFeedTd[playerid], 1);
}

DestroyFeedTD(playerid)
{
	PlayerTextDrawDestroy(playerid, KillFeedTd[playerid]);
}