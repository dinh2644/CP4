#include <iostream>
using namespace std;
#include "./include/BST.h"

bool BST::destroyBST(Node *&root)
{
    if (root == NULL)
    {
        return true;
    }

    destroyBST(root->left);
    destroyBST(root->right);

    delete root->song;
    delete root;

    return true;
}

Node *BST::insert(Node *root, Song *newSong)
{
    // Handle empty tree
    if (root == NULL)
    {
        Node *newNode = new Node();
        newNode->song = newSong;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }

    // Insert song by comparing title
    if (newSong->getTitle() < root->song->getTitle())
    {
        root->left = insert(root->left, newSong);
    }
    else
    {
        root->right = insert(root->right, newSong);
    }
    return root;
}

Node *FindMin(Node *root)
{
    while (root->left != NULL)
    {
        root = root->left;
    }

    return root;
}

// MAYBE DELETE LATER??????
int BST::getActualVectorIndex(vector<Song *> &songVect, int originalIndex)
{
    if (originalIndex != 0 && originalIndex != (songVect.size() - 1))
    {
        songsRemovedInVector++;
        return originalIndex - songsRemovedInVector;
    }
    else
    {
        return originalIndex;
    }
}

void BST::swapOriginalIndices(int i, MaxHeap &heap)
{
    int tmp = heap.heap[i]->getOriginalIndexFromHeap();         // 0
    heap.heap[i]->setOriginalHeapIndex(heap.heap.size() - 1);   // 6
    heap.heap[heap.heap.size() - 1]->setOriginalHeapIndex(tmp); // 0
}

Node *BST::remove(Node *root, string songTitle, vector<Song *> &songVect, MaxHeap &heap, bool heapNodeNotRemoved)
{

    // Base cases
    if (root == NULL)
    {
        return root;
    }
    else if (songTitle < root->song->getTitle())
    {
        root->left = remove(root->left, songTitle, songVect, heap, true);
    }
    else if (songTitle > root->song->getTitle())
    {
        root->right = remove(root->right, songTitle, songVect, heap, true);
    }
    else
    {
        if (heapNodeNotRemoved == true && root->song->getIsFavorite() == false)
        {
            if (root->song->getOriginalIndexFromHeap() == heap.heap.size() - 1)
            {
                heap.heap.pop_back();
            }
            else if (heap.heap.size() != 0)
            {
                // keep track of root's og originalIndex
                int idxToBeSwappedAndRemove = root->song->getOriginalIndexFromHeap();
                // this will swap root's original idx to last idx (since it will be deleted)
                swapOriginalIndices(root->song->getOriginalIndexFromHeap(), heap);
                // heap.heap.at(idxToBeNull) = nullptr;
                int newHeapSize = heap.removeHeapNullPtrs(idxToBeSwappedAndRemove);
                heap.heapify((newHeapSize / 2) - 1);
            }
        }
        // Case 1:  No child
        if (root->left == NULL && root->right == NULL)
        {
            // remove song from vector in O(1)
            // songVect.erase(songVect.begin() + root->song->getOriginalIndex());
            // songVect.erase(songVect.begin() + getActualVectorIndex(songVect, root->song->getOriginalIndex()));
            // songVect.at(getActualVectorIndex(songVect, root->song->getOriginalIndex())) = nullptr;
            songVect.at(root->song->getOriginalIndex()) = nullptr;

            // heap.decrementSize();

            delete root->song;
            delete root;
            root = NULL;
        }
        // Case 2: One child
        // if left
        else if (root->left == NULL)
        {
            // remove song from vector in O(logN)

            // also increament a global variable and
            // change global variable location if works!!!!!!!!!!!!!!!!

            // songVect.erase(songVect.begin() + root->song->getOriginalIndex());
            // songVect.erase(songVect.begin() + getActualVectorIndex(songVect, root->song->getOriginalIndex()));
            // songVect.at(getActualVectorIndex(songVect, root->song->getOriginalIndex())) = nullptr;
            songVect.at(root->song->getOriginalIndex()) = nullptr;

            // heap.decrementSize();

            Node *tmp = root;
            root = root->right;
            delete tmp->song;
            delete tmp;
        }
        // if right
        else if (root->right == NULL)
        {
            // remove song from vector in O(logN)
            // songVect.erase(songVect.begin() + root->song->getOriginalIndex());
            // songVect.erase(songVect.begin() + getActualVectorIndex(songVect, root->song->getOriginalIndex()));
            // songVect.at(getActualVectorIndex(songVect, root->song->getOriginalIndex())) = nullptr;
            songVect.at(root->song->getOriginalIndex()) = nullptr;

            // heap.decrementSize();

            Node *tmp = root;
            root = root->left;
            delete tmp->song;
            delete tmp;
        }
        // case 3: 2 children
        else
        {
            songVect.at(root->song->getOriginalIndex()) = nullptr;

            Node *tmpCurrent = root;                   // D
            Node *tmpSuccessor = FindMin(root->right); // E

            root = tmpSuccessor; // set D to E

            root->left = tmpCurrent->left;
            delete tmpCurrent->song;
            delete tmpCurrent;

            // root->right = remove(root->right, tmp->song->getTitle(), songVect, heap, false);
        }
    }
    return root;
}

bool BST::findAndUpdateListenTime(Node *root, string songTitle, int listenTime, MaxHeap &heap)
{
    if (root == NULL)
    {
        return false;
    }
    // Don't update listen time if it's marked as a favorite
    else if (root->song->getTitle() == songTitle)
    {
        // Check first if its a favorite, if so dont add listen time to song
        if (root->song->getIsFavorite() == true)
        {
            return false;
        }
        else
        {

            // update listen time
            root->song->setListenTime(listenTime);
            // then percolate up in the heap if needed
            heap.percolateUp(root->song->getOriginalIndexFromHeap(), heap);
            return true;
        }
    }
    else if (songTitle < root->song->getTitle())
    {
        return findAndUpdateListenTime(root->left, songTitle, listenTime, heap);
    }
    else
    {
        return findAndUpdateListenTime(root->right, songTitle, listenTime, heap);
    }
}

// For debugging
void BST::inorderPrint(Node *root)
{
    if (root != nullptr)
    {
        inorderPrint(root->left);
        cout << root->song->getTitle() << " " << root->song->getListenTime() << endl;
        inorderPrint(root->right);
    }
}

int BST::countNodes(Node *root)
{
    if (!root)
    {
        return 0;
    }
    // Count nodes in left and right subtrees
    int leftCount = countNodes(root->left);
    int rightCount = countNodes(root->right);
    // Return total count (including current node)
    return 1 + leftCount + rightCount;
}