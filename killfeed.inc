#tryinclude <open.mp>

#if !defined _INC_open_mp
    #include <a_samp>
#endif

#if !defined FEED_MAX_LINES
	#define FEED_MAX_LINES (6)
#endif

#if !defined FEED_TIME
	#define FEED_TIME (5000)
#endif

#if !defined FEED_SIZE
	#define FEED_SIZE (64 * FEED_MAX_LINES)
#endif

#if !defined FEED_PRIMARY_COLOR
	#define FEED_PRIMARY_COLOR "~w~~h~"
#endif

#if !defined FEED_SECONDARY_COLOR
	#define FEED_SECONDARY_COLOR "~r~~h~"
#endif

new
	bool:g_FeedEnabled = true,
	bool:p_FeedEnabled[MAX_PLAYERS] = {true, ...},

	bool:g_FeedRandomMsgs = false,
	bool:p_FeedRandomMsgs[MAX_PLAYERS] = {false, ...},

	PlayerText:KillFeedTd[MAX_PLAYERS],

	KillFeedLines[MAX_PLAYERS],
	KillFeedTimer[MAX_PLAYERS],
	KillFeedString[MAX_PLAYERS][FEED_MAX_LINES][FEED_SIZE]
;

new FeedMsgs[10][FEED_SIZE] = 
{
	 {""FEED_PRIMARY_COLOR"You killed "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You fucked "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You smeared "FEED_SECONDARY_COLOR"%s "FEED_PRIMARY_COLOR"in shit~n~"},
	 {""FEED_PRIMARY_COLOR"You sent "FEED_SECONDARY_COLOR"%s "FEED_PRIMARY_COLOR"to cemetery~n~"},
	 {""FEED_PRIMARY_COLOR"You murdered "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You owned "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You decapitated "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You raped "FEED_SECONDARY_COLOR"%s~n~"},
	 {""FEED_PRIMARY_COLOR"You sent "FEED_SECONDARY_COLOR"%s "FEED_PRIMARY_COLOR"to heaven~n~"},
	 {""FEED_PRIMARY_COLOR"You ate "FEED_SECONDARY_COLOR"%s's "FEED_PRIMARY_COLOR"ass~n~"}
};

public OnPlayerConnect(playerid)
{
	CreateFeedTD(playerid);

    #if defined _______OnPlayerConnect
        return _______OnPlayerConnect(playerid);
    #else
        return true;
    #endif
}

public OnPlayerDisconnect(playerid, reason)
{
	DestroyFeedTD(playerid);

	for(new i; i < FEED_MAX_LINES; i ++)
		KillFeedString[playerid][i] = "_";

	KillFeedLines[playerid] = 0;

    #if defined _______OnPlayerDisconnect
        return _______OnPlayerDisconnect(playerid, reason);
    #else
        return true;
    #endif
}

public OnPlayerDeath(playerid, killerid, WEAPON:reason)
{
	if(killerid == INVALID_PLAYER_ID || playerid == INVALID_PLAYER_ID)
		return false;

	UpdateKillFeed(killerid, playerid);

    #if defined _______OnPlayerDeath
        return _______OnPlayerDeath(playerid, killerid, WEAPON:reason);
    #else
        return true;
    #endif
}

UpdateKillFeed(killerid, playerid)
{
	if(!p_FeedEnabled[killerid])
		return false;

	new killLine[FEED_SIZE], killLine2[FEED_SIZE], killedName[MAX_PLAYER_NAME];

	GetPlayerName(playerid, killedName, MAX_PLAYER_NAME);

	if(KillFeedLines[killerid] == FEED_MAX_LINES)
	{
		for(new i; i < FEED_MAX_LINES; i ++)
			KillFeedString[killerid][i] = "_";

		KillFeedLines[killerid] = 0;
	}

	if(p_FeedRandomMsgs[killerid])
		format(killLine, sizeof killLine, FeedMsgs[random(sizeof(FeedMsgs))], killedName);
	else
		format(killLine, sizeof killLine, FeedMsgs[0], killedName);

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

stock SetKillFeed(playerid = INVALID_PLAYER_ID, bool:enable)
{
	if(playerid == INVALID_PLAYER_ID){
		for(new i; i != MAX_PLAYERS; i ++)
			p_FeedEnabled[i] = enable;

		g_FeedEnabled = enable;
	}
	else
		p_FeedEnabled[playerid] = enable;

	return enable;
}

stock bool:GetKillFeed(playerid = INVALID_PLAYER_ID)
{
	if(playerid == INVALID_PLAYER_ID)
		return g_FeedEnabled;

	return p_FeedEnabled[playerid];
}

stock SetFeedRandomMsgs(playerid = INVALID_PLAYER_ID, bool:enable)
{
	if(playerid == INVALID_PLAYER_ID)
	{
		for(new i; i != MAX_PLAYERS; i ++)
			p_FeedRandomMsgs[i] = enable;

		g_FeedRandomMsgs = enable;
	}
	else
		p_FeedRandomMsgs[playerid] = enable;

	return enable;
}

stock bool:GetFeedRandomMsgs(playerid = INVALID_PLAYER_ID)
{
	if(playerid == INVALID_PLAYER_ID)
		return g_FeedRandomMsgs;

	return p_FeedRandomMsgs[playerid];
}

#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect _______OnPlayerConnect
#if defined _______OnPlayerConnect
    forward _______OnPlayerConnect(playerid);
#endif

#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect _______OnPlayerDisconnect
#if defined _______OnPlayerDisconnect
    forward _______OnPlayerDisconnect(playerid);
#endif

#if defined _ALS_OnPlayerDeath
    #undef OnPlayerDeath
#else
    #define _ALS_OnPlayerDeath
#endif
#define OnPlayerDeath _______OnPlayerDeath
#if defined _______OnPlayerDeath
    forward _______OnPlayerDeath(playerid, killerid, WEAPON:reason);
#endif
