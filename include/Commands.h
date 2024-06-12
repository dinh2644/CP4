#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;

// Dependencies
#include "BST.h"

/**
    Helpers
 **/

string convertSecToMins(string duration)
{
    int seconds = stoi(duration);
    int minutes = seconds / 60;
    return to_string(minutes);
}

int getNumOfWords(string input)
{
    stringstream iss(input);
    string word;
    int count = 0;
    bool inQuotes = false;
    //???
    while (iss >> word)
    {
        // if the first character is a quotation, set inQuotes to true
        if (word[0] == '"')
        {
            inQuotes = true;
        }
        // if the last character is a quote, set inquotes to false because??
        if (word[word.length() - 1] == '"')
        {
            inQuotes = false;
        }
        // if we have a regular word, just increment counter
        if (!inQuotes)
        {
            ++count;
        }
    }
    return count;
}

// checking if string is a number
bool isNumber(string str)
{
    // check isdigit for every character
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            // return false if even one of them is a digit?
            return false;
    return true;
}

void checkForQuotes(string &input, stringstream &iss, string &songId, string &artist, string &duration, string &songTitle)
{
    int openingQuoteIndex = input.find('"');
    int closingQuoteIndex = input.find('"', openingQuoteIndex + 1);

    // Check if there's at least two quotes in input
    if (openingQuoteIndex != string::npos && closingQuoteIndex != string::npos)
    {
        string temp;
        iss >> songId;

        // Handle artist enclosed in double quotes
        // Check first to see if this string starts with a quote
        iss >> temp;

        if (temp[0] == '"')
        {
            string temp2 = temp.substr(1) + " ";

            // keep getting next string while building temp2 w/ that string until a string has a closing quote
            while (temp[temp.length() - 1] != '"')
            {

                iss >> temp;
                temp2 += temp + " ";
            }
            // removes extra space + closing quotes
            temp2 = temp2.substr(0, temp2.length() - 2);
            artist = temp2;
        }
        else
        {
            artist = temp;
        }

        iss >> duration;

        // Handle song title enclosed in double quotes
        iss >> temp;

        if (temp[0] == '"')
        {
            string temp2 = temp.substr(1) + " ";
            // build temp 2 until theres a closing quote
            while (temp[temp.length() - 1] != '"')
            {
                iss >> temp;
                temp2 += temp + " ";
            }

            temp2 = temp2.substr(0, temp2.length() - 2);
            songTitle = temp2;
        }
        else
        {
            songTitle = temp;
        }
    }
    else
    {
        iss >> songId >> artist >> duration >> songTitle;
    }
}

void checkForQuotesForRemoveCommand(string &input, stringstream &iss, string &songTitle)
{
    int openingQuoteIndex = input.find('"');
    int closingQuoteIndex = input.find('"', openingQuoteIndex + 1);

    // Check if there's at least two quotes in input
    if (openingQuoteIndex != string::npos && closingQuoteIndex != string::npos)
    {
        string temp;

        // Handle song title enclosed in double quotes
        iss >> temp;

        if (temp[0] == '"')
        {
            string temp2 = temp.substr(1) + " ";
            // build temp 2 until theres a closing quote
            while (temp[temp.length() - 1] != '"')
            {
                iss >> temp;
                temp2 += temp + " ";
            }

            temp2 = temp2.substr(0, temp2.length() - 2);
            songTitle = temp2;
        }
        else
        {
            songTitle = temp;
        }
    }
    else
    {
        iss >> songTitle;
    }
    cout << songTitle << endl;
}

void checkForQuotesForListenCommand(string &input, stringstream &iss, string &songTitle, string &listenTime)
{
    int openingQuoteIndex = input.find('"');
    int closingQuoteIndex = input.find('"', openingQuoteIndex + 1);

    // Check if there's at least two quotes in input
    if (openingQuoteIndex != string::npos && closingQuoteIndex != string::npos)
    {
        string temp;

        // Handle song title enclosed in double quotes
        iss >> temp;

        if (temp[0] == '"')
        {
            string temp2 = temp.substr(1) + " ";
            // build temp 2 until theres a closing quote
            while (temp[temp.length() - 1] != '"')
            {
                iss >> temp;
                temp2 += temp + " ";
            }

            temp2 = temp2.substr(0, temp2.length() - 2);
            songTitle = temp2;
        }
        else
        {
            songTitle = temp;
        }
        iss >> listenTime;
    }
    else
    {
        iss >> songTitle >> listenTime;
    }
    cout << songTitle << endl;
}

// void sortSongId(vector<Song *> &songVector)
// {
//     removeNullPtrs(songVector);s
//
//     auto compareBySongId = [](Song *a, Song *b)
//     {
//         // Handle nullptr cases
//         if (a == nullptr && b == nullptr)
//         {
//             return false; // both nullptrs, consider them equal
//         }
//         else if (a == nullptr)
//         {
//             return false; // nullptr should go after non-nullptr
//         }
//         else if (b == nullptr)
//         {
//             return true; // non-nullptr should go before nullptr
//         }
//         else
//         {
//             return a->getSongId() < b->getSongId(); // Compare songIds for non-nullptr cases
//         }
//     };

//     // Sort the song pointers vector using the custom comparison function
//     sort(songVector.begin(), songVector.end(), compareBySongId);

//     // Move nullptr elements to the back of the vector
//     auto it = partition(songVector.begin(), songVector.end(), [](Song *s)
//                         { return s != nullptr; });
//     songVector.erase(it, songVector.end());
// }

void removeNullPtrs(vector<Song *> &songVect)
{
    for (int i = 0; i < songVect.size(); i++)
    {
        while (songVect[songVect.size() - 1] == NULL && songVect.size() > 0)
        {
            songVect.pop_back();
        }

        if (songVect[i] == nullptr && songVect.size() != 0 && i < songVect.size())
        {
            // swap
            Song *tmp = songVect[songVect.size() - 1];
            songVect[songVect.size() - 1] = songVect[i];
            songVect[i] = tmp;

            songVect.pop_back();
        }
    }
}

void sortSongId(vector<Song *> &songVect)
{
    // remove nullptrs before sorting
    removeNullPtrs(songVect); // O(n)
    sort(songVect.begin(), songVect.end(), [](Song *a, Song *b)
         { return a->getSongId() < b->getSongId(); }); // O(n)
}

void setOriginalIndex(vector<Song *> &songVect)
{
    // Loop through sorted vector to set original index for inserted song
    for (int i = 0; i < songVect.size(); i++)
    {
        if (songVect[i] != nullptr)
        {
            songVect[i]->setOriginalIndex(i);
        }
    }
}

void setOriginalHeapIndex(MaxHeap &heap)
{
    // Loop through sorted vector to set original index for inserted song

    vector<Song *> heapVect = heap.getHeap();
    for (int i = 0; i < heap.heap.size(); i++)
    {
        if (heapVect.at(i) != nullptr)
        {
            heapVect.at(i)->setOriginalHeapIndex(i);
        }
    }
}

/**
    Required
 **/
void createSong(BST &bst, Node *&rootptr, vector<Song *> &songVect, MaxHeap &heap, string songId, string artist, string duration, string songTitle, int listenTime, bool isFavorite)
{
    // quit

    // string to int conversion
    int id = stoi(songId);
    int dur = stoi(duration);

    // Create new song object on heap, storing it in song ptr
    Song *song = new Song(id, artist, dur, songTitle, listenTime, isFavorite);

    // Add to vector
    songVect.push_back(song);
    sortSongId(songVect);

    setOriginalIndex(songVect);

    // Add to BST
    rootptr = bst.insert(rootptr, song);

    // Add to Max Heap
    heap.insert(song);
    setOriginalHeapIndex(heap);

    // For sake of printing message
    string minutes = convertSecToMins(duration);
    string seconds = to_string(stoi(duration) % 60);

    cout << "new song " << songId << " " << songTitle << " by " << artist << " " << minutes << ":" << setw(2) << setfill('0') << seconds << endl;
}

void removeSong(BST &bst, Node *&rootptr, vector<Song *> &songVect, MaxHeap &heap, string songTitle)
{
    // remove must work in O(log N) time - you may need to get creative here!
    if (rootptr == nullptr)
    {
        return;
    }
    else if (rootptr->song->getIsFavorite() == true)
    {
        cout << "Removed " << songTitle << " from your favorites" << endl;
    }
    else
    {
        cout << "Removed " << songTitle << " from your songs" << endl;
    }

    // 1. remove from BST (might not need this if we just need to remove from song vector)
    rootptr = bst.remove(rootptr, songTitle, songVect, heap, true); // O(logN)
}

void listen(BST &bst, Node *rootptr, vector<Song *> &songVect, MaxHeap &heap, string songTitle, string listenTime)
{
    // listen must work in O(log N) time where N is the number of songs

    // string to int conversion
    int ListenTime = stoi(listenTime);

    // Find and update listening time in BST in O(logN))
    if (rootptr == nullptr)
    {
        return;
    }
    else
    {
        bool foundAndNotAFavorite = bst.findAndUpdateListenTime(rootptr, songTitle, ListenTime, heap); // logN
        if (foundAndNotAFavorite == true)
        {
            cout << "Listened to " << songTitle << " for " << listenTime << " seconds" << endl;
        }
        else
        {
            cout << "Song " << songTitle << " is a favorite" << endl;
        }
    }
}

void favorite(BST &bst, Node *rootptr, vector<Song *> &songVect, MaxHeap &heap)
{
    // favorite must work in O(log N) time

    if (rootptr == nullptr)
    {
        return;
    }
    else
    {
        if (heap.heap.size() == 0)
        {
            cout << "No song to favorite" << endl;
            return;
        }
        else
        {

            Song *extractedSong = heap.extractMax();
            // BELOW CAUSES SEG FAULT (not anymore as of 5/1/2023 lol)
            if (extractedSong)
            {
                extractedSong->setFavorite(true);
                cout << "Song " << extractedSong->getTitle() << " added to list of favorites (Listened for " << extractedSong->getListenTime() << " seconds)" << endl;
            }
        }
    }
}

void show_listen_time(vector<Song *> &songVect)
{
    // This command should show all songs, ordered by song id, along with their listening times, as follows:
    // O(N)

    // remove any remaining nullptrs
    removeNullPtrs(songVect);
    setOriginalIndex(songVect);

    // Display all songs in song vector
    if (songVect.size() == 0)
    {
        cout << "VECTOR EMPTY" << endl;
    }
    else
    {
        for (int i = 0; i < songVect.size(); i++)
        {
            cout << songVect[i]->getSongId() << " " << songVect[i]->getTitle() << " listened to for " << songVect[i]->getListenTime() << " seconds" << endl;
        }
    }
}

void seeCommands()
{
    cout << "Enter [";
    cout << "\"song <songid> <artist> <duration> <title>\"" << endl;
    cout << "       \"remove <songid>\"" << endl;
    cout << "       \"listen <song-title> <seconds>\"" << endl;
    cout << "       \"favorite\"" << endl;
    cout << "       \"show_listen_time\"" << endl;
    cout << "       \"quit\""
         << "]" << endl;
}
