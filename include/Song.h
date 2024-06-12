#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <stdlib.h>
using namespace std;

class Song
{
public:
    // CONSTRUCTOR
    Song() : songId(0), artist(""), duration(0), songTitle(""), listenTime(0), isFavorite(false), originalIndex(0), originalHeapIndex(0) {}
    Song(int songId, string artist, int duration, string songTitle, int listenTime, bool isFavorite)
        : songId(songId), artist(artist), duration(duration), songTitle(songTitle), listenTime(listenTime), isFavorite(isFavorite), originalIndex(originalIndex), originalHeapIndex(originalHeapIndex){};

    // Getters
    int getSongId() { return songId; }
    string getArtist() { return artist; }
    int getDuration() { return duration; }
    string getTitle() { return songTitle; }
    int getListenTime() { return listenTime; }
    bool getIsFavorite() { return isFavorite; }
    int getOriginalIndex() { return originalIndex; }
    int getOriginalIndexFromHeap() { return originalHeapIndex; }

    // SETTERS
    void setTitle(string newTitle);
    void setListenTime(int newListenTime);
    void setFavorite(bool newFavorite);
    void setOriginalIndex(int orginalIdx);
    void setOriginalHeapIndex(int originalHeapIdx);

private:
    int songId;
    string artist;
    int duration;
    string songTitle;
    int listenTime;
    bool isFavorite;
    int originalIndex;
    int originalHeapIndex;
};

#endif // SONG_H