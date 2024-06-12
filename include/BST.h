#include <iostream>
#include "Song.h"
#include "MaxHeap.h"
#include "vector"
using namespace std;

class Node
{
public:
    Song *song;
    Node *left;
    Node *right;
    Node *par;
};

class BST
{
private:
    Node *root;
    int songsRemovedInVector = 0;

public:
    BST() : root(nullptr){};
    ~BST() { destroyBST(root); }
    bool destroyBST(Node *&root);

    // Methods
    Node *insert(Node *root, Song *newSong);
    Node *remove(Node *root, string songTitle, vector<Song *> &songVect, MaxHeap &heap, bool heapNodeNotRemoved);
    bool findAndUpdateListenTime(Node *root, string songTitle, int listenTime, MaxHeap &heap);
    void swapOriginalIndices(int i, MaxHeap &heap);

    // FOR DEBUGGING
    int countNodes(Node *root);
    void inorderPrint(Node *root);

    // GETTERS
    Node *getRoot() { return this->root; }
    int getActualVectorIndex(vector<Song *> &songVect, int originalIndex);
};