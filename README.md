- ABOUT:

The code can easily be altered/modified to the user's liking.

The functionality is similar to the damage feed in include weaponconfig.

- USE:

Place the killfeed.inc file in: pawno/includes in your gamemode folder and then include it in your gamemode and include in your gamemode script.

#define FEED_MAX_LINES (number of lines in the kill feed)

#define FEED_TIME (time to hide kill feed)

- FUNCTIONS:

SetKillFeed(playerid, true or false); // Enable or Disable kill feed for player

GetKillFeed(playerid); // Get player kill feed state.
