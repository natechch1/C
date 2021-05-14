#include <stdio.h>
#include <stdlib.h>
#include "PlaylistNode.h"
void PrintMenu(char playlistTitle[]);
// Main Function
int main(int argc, char* argv[])
{
char playlistTitle[50];
//prompt user for playlist title
//eliminate the end of line char
printf("Enter playlist's title:\n");
fgets(playlistTitle, 50, stdin);
playlistTitle[strlen(playlistTitle)-1]= '\0';
printf("\n");
//2) output playlist menu options
PrintMenu(playlistTitle); //this will be a big function
return 0;
}
// Function Definitions
//
void PrintMenu(char playlistTitle[])
{
//PlaylistNode * song[MAX];
PlaylistNode *songHead = NULL;
PlaylistNode *songTail = NULL;
PlaylistNode *songCurrent = NULL;
PlaylistNode *songLast = NULL;
// PlaylistNode *songNext = NULL; //really should be named last
PlaylistNode temp;
//create a bunch of temp variables: chars, ints, and PlaylistNode(pointers)
char menuOp=' ';
int tempLength = 0;
int songQuant = 0;
// char dummyVal = '0';
//output menu option
//create a loop to print your options
while(menuOp != 'q')
{
start:
printf("%s PLAYLIST MENU\n", playlistTitle);
//check for valid choices
PrintMenuOptions();
fflush(stdin);
//getchar();
menuOp='-';
scanf(" %c%*c", &menuOp);
printf("\n");
switch(menuOp)
{
//set corresponding menu actions
//switch menuOP
case 'a' :// Add a song
printf("ADD SONG\n");
printf("Enter song's unique ID:\n");
fgets(temp.uniqueID, 50, stdin);
temp.uniqueID[strlen(temp.uniqueID)-1]='\0';
printf("Enter song's name:\n");
fgets(temp.songName, 50, stdin);
temp.songName[strlen(temp.songName)-1]='\0';
printf("Enter artist's name:\n");
fgets(temp.artistName, 50, stdin);
temp.artistName[strlen(temp.artistName)-1]='\0';
printf("Enter song's length (in seconds):\n");
scanf("%d", &temp.songLength);
printf("\n");
// Set head pointer
songCurrent=(PlaylistNode*)malloc(sizeof(PlaylistNode));
CreatePlaylistNode(songCurrent, temp.uniqueID,
temp.songName, temp.artistName, temp.songLength, NULL);
if(songQuant == 0)
{
songHead = songCurrent;
songLast = songHead;
}
else
{
InsertPlaylistNodeAfter(songLast, songCurrent);
songLast = songCurrent;
}

songQuant++;
fflush(stdin);
getchar();
goto start;

case 'r' :// output playlist message
printf("REMOVE SONG\n");
printf("Enter song's unique ID:\n");
fflush(stdin);
fgets(temp.uniqueID, 50, stdin);
temp.uniqueID[strlen(temp.uniqueID)-1]='\0';
songCurrent=songHead;
if(strcmp(temp.uniqueID, songHead->uniqueID)==0)
{
printf("\"%s\" removed.\n\n", songHead->songName);
songHead=GetNextPlaylistNode(songHead);

}
else
{
while(songCurrent!=NULL)
{
if(strcmp(songCurrent->uniqueID, temp.uniqueID)==0)
{
strcpy(temp.songName,songCurrent->songName);
}
songCurrent=GetNextPlaylistNode(songCurrent);
}
songHead=delete_item(songHead, temp.uniqueID);

//while(songCurrent != NULL)
// {

printf("\"%s\" removed.\n\n", temp.songName);
}
songQuant--;

// goto exitwhile
// songNext=songCurrent;
// songCurrent=GetNextPlaylistNode(songCurrent);
// }
goto start;
//exitwhile:
case 'c' :// Prompt user for new song location
printf("CHANGE POSITION OF SONG\n");
int thissong = 0;
int nextsong = 0;
int numsongs = 0;
int difference = 0;
PlaylistNode* changer=NULL;
PlaylistNode* prechanger=NULL;
PlaylistNode* another=NULL;
printf("Enter song's current position:");
scanf(" %d", &thissong);
printf("Enter new position for song:");
scanf(" %d", &nextsong);
difference= nextsong-thissong;

songCurrent=songHead;
while(songCurrent!=NULL)
{
numsongs++;
songCurrent=GetNextPlaylistNode(songCurrent);
if(GetNextPlaylistNode(songCurrent)==NULL)
{
songTail=songCurrent;
}
}
// printf("number of sungs: %d\n", numsongs);
if(nextsong>numsongs)
{
nextsong=numsongs;
}

// difference=nextsong-thissong;
songCurrent=songHead;
for(int j=1; j<thissong; j++)
{
if(j+1==thissong)
{
prechanger=songCurrent;
}
songCurrent=GetNextPlaylistNode(songCurrent);
}
changer = songCurrent;
//PrintPlaylistNode(songCurrent);
if(nextsong==0)
{
prechanger->nextNodeptr=songCurrent->nextNodeptr;
changer=songHead;
songHead=songCurrent;
songHead->nextNodeptr=changer;
}
else if(difference>0)
{
if(songCurrent==songHead)
{
  
for(int p =1; p<nextsong; p++)
{
songCurrent=GetNextPlaylistNode(songCurrent);
}
another=GetNextPlaylistNode(songHead);
InsertPlaylistNodeAfter(songCurrent, songHead);
songHead=another;
}
}
else if(difference<0)
{
}
goto start;
case 's' :// search by artist
// fflush(stdin);
//getchar();
printf("OUTPUT SONGS BY SPECIFIC ARTIST\n");
printf("Enter artist's name:");
int k = 1;
fgets(temp.uniqueID, 50, stdin);
temp.uniqueID[strlen(temp.uniqueID)-1]='\0';
songCurrent=songHead;
printf("\n");
while(songCurrent != NULL)
{
if(strcmp(temp.uniqueID, songCurrent->artistName)==0)
{
printf("%d.\n", k);
PrintPlaylistNode(songCurrent);
printf("\n");
}
//printf("%d", k);
k++;
songCurrent=GetNextPlaylistNode(songCurrent);
}
goto start;
case 't' :// Output the total time of all songs of your playlist in seconds
printf("OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)\n");
songCurrent=songHead;
while(songCurrent!=NULL)
{
tempLength=tempLength+songCurrent->songLength;
songCurrent=GetNextPlaylistNode(songCurrent);
}
printf("Total time: %d seconds\n\n", tempLength);
goto start;
case 'o' :// output full playlist
printf("%s - OUTPUT FULL PLAYLIST\n", playlistTitle);
int i = 1;
if(songQuant==0)
{
printf("Playlist is empty\n\n");
}
else
{
songCurrent=songHead;
while(songCurrent != NULL)
{
printf("%d.\n", i);
PrintPlaylistNode(songCurrent);
printf("\n");
songCurrent=GetNextPlaylistNode(songCurrent);
i++;
}
}
case 'q' :// to quit/exit of loop
break;
default :
scanf(" %c", &menuOp);
printf("\n");
}
}
return;
}
