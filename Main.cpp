#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

// Dependencies
#include "./include/Commands.h"

#include <cstdlib>
#include <ctime>

int main()
{
    // Create pointer based BST (organized by song titles)
    BST bst;
    Node *rootptr = bst.getRoot();

    // Create array-based Max Heap (organized by song listen time)
    MaxHeap heap;

    // Create song object based Vector (organized song id)
    vector<Song *> songVect;

    string input;
    string command;

    seeCommands();
    while (true)
    {

        cout << ": ";

        getline(cin, input);
        stringstream iss(input);
        iss >> command;

        if (command == "song")
        {
            string songId, artist, duration, songTitle;

            // Handle quotes in input
            checkForQuotes(input, iss, songId, artist, duration, songTitle);

            // Other input handling
            if (getNumOfWords(input) != 5)
            {
                cout << "missing/extra arguments" << endl;
            }
            else if (!isNumber(songId))
            {
                cout << "song id " << songId << " is not an integer" << endl;
            }
            else if (!isNumber(duration))
            {
                cout << "duration " << duration << " is not an integer" << endl;
            }
            else
            {
                createSong(bst, rootptr, songVect, heap, songId, artist, duration, songTitle, 0, false);
            }
        }
        else if (command == "remove")
        {
            string songTitle;

            checkForQuotesForRemoveCommand(input, iss, songTitle);

            if (getNumOfWords(input) != 2)
            {
                cout << "missing/extra arguments" << endl;
            }
            else if (isNumber(songTitle))
            {
                cout << "song title " << songTitle << " can't be an int" << endl;
            }
            else
            {

                removeSong(bst, rootptr, songVect, heap, songTitle);
            }
        }
        else if (command == "listen")
        {
            string songTitle, listenTime;

            checkForQuotesForListenCommand(input, iss, songTitle, listenTime);

            if (getNumOfWords(input) != 3)
            {
                cout << "missing/extra arguments" << endl;
            }
            else if (!isNumber(listenTime))
            {
                cout << "listenTime " << command << " must be int" << endl;
            }
            else
            {
                listen(bst, rootptr, songVect, heap, songTitle, listenTime);
            }
        }
        else if (command == "show_listen_time")
        {
            if (getNumOfWords(input) != 1)
            {
                cout << "missing/extra arguments" << endl;
            }
            else
            {
                show_listen_time(songVect);
            }
        }
        else if (command == "favorite")
        {
            if (getNumOfWords(input) != 1)
            {
                cout << "missing/extra arguments" << endl;
            }
            else
            {
                favorite(bst, rootptr, songVect, heap);
            }
        }
        else if (command == "quit")
        {
            break;
        }
        else
        {
            cout << "Command not recognized, please try again." << endl;
        }
    }

    cout << "BST: " << endl;
    bst.inorderPrint(rootptr);

    cout << endl;

    cout << "Max Heap: " << endl;
    heap.printHeap(); // failed with remove

    cout << endl;

    cout << "Vector: " << endl;
    for (int i = 0; i < songVect.size(); i++)
    {
        if (songVect[i] != nullptr)
        {
            cout << songVect[i]->getListenTime() << " " << songVect[i]->getTitle() << endl;
        }
    }

    cout << endl;

    // Free memory
    bst.destroyBST(rootptr);
    return 0;
}