- ABOUT:

The code can easily be altered/modified to the user's liking.

The functionality is similar to the damage feed in include weaponconfig.

- USE:

Place the killfeed.inc file in: pawno/includes in your gamemode folder and then include it in your gamemode and include in your gamemode script.

#define FEED_MAX_LINES (number of lines in the kill feed) default: 6

#define FEED_TIME (time to hide kill feed) default: 5000

#define FEED_PRIMARY_COLOR "~w~~h~" default: ~w~~h~

#define FEED_SECONDARY_COLOR "~r~~h~" default: ~r~~h~

- FUNCTIONS:

SetKillFeed(playerid, true or false); // Enable or Disable kill feed for player. INVALID_PLAYER_ID will set the value for all players

GetKillFeed(playerid); // Get player kill feed state.

SetFeedRandomMsgs(playerid, true or false); // Enable or Disable kill feed random messages for player. INVALID_PLAYER_ID will set the value for all players

GetFeedRandomMsgs(playerid); // Get player kill feed random messages state.


- PREVIEW:

With random messages enabled:
https://imgur.com/pEHac4h

With random messages disabled:
https://imgur.com/asCHelA
