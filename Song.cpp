#include <iostream>
#include "./include/Song.h"
using namespace std;

void Song::setTitle(string newTitle)
{
    this->songTitle = newTitle;
}

void Song::setListenTime(int newListenTime)
{
    this->listenTime = listenTime + newListenTime;
}

void Song::setFavorite(bool newFavorite)
{
    this->isFavorite = newFavorite;
}

void Song::setOriginalIndex(int orginalIdx)
{
    this->originalIndex = orginalIdx;
}

void Song::setOriginalHeapIndex(int originalHeapIdx)
{
    this->originalHeapIndex = originalHeapIdx;
}