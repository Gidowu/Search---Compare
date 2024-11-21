#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

// Sequential search
int seq_search(vector<int> &keys, int key, int &numCmp)
{
    numCmp = 0;
    for (int i = 0; i < keys.size(); i++)
    {
        numCmp++;
        if (keys[i] == key)
        {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Sequential search with start and stop range
int seq_search(vector<int> &keys, int key, int start, int stop, int &numCmp)
{
    numCmp = 0;
    for (int i = start; i <= stop; i++)
    {
        numCmp++;
        if (keys[i] == key)
        {
            return i; // Return the index if found
        }
    }
    return -1; // Return -1 if not found
}

// Binary search
int bin_search(vector<int> &keys, int key, int &numCmp)
{
    int low = 0, high = keys.size() - 1;
    numCmp = 0;

    while (low <= high)
    {
        numCmp++;
        int mid = low + (high - low) / 2;

        if (keys[mid] == key)
        {
            return mid; // Return the index if found
        }
        if (keys[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // Return -1 if not found
}

// Enhanced binary search: switches to sequential search if remaining range is < 15
int bin2_search(vector<int> &keys, int key, int &numCmp)
{
    int low = 0, high = keys.size() - 1;
    numCmp = 0;

    while (low <= high)
    {
        if (high - low < 15)
        { // Switch to sequential search
            return seq_search(keys, key, low, high, numCmp);
        }
        numCmp++;
        int mid = low + (high - low) / 2;

        if (keys[mid] == key)
        {
            return mid; // Return the index if found
        }
        if (keys[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return -1; // Return -1 if not found
}

// Test the search algorithms
int main()
{
    // Initialize random seed
    srand(time(NULL));

    // Create a vector of 100,000 integers
    vector<int> keys(100000);
    for (int i = 0; i < 100000; i++)
    {
        keys[i] = rand() % 10000000; // Random numbers between 0 and 10,000,000
    }

    // Sort the vector using STL sort
    sort(keys.begin(), keys.end());

    // Generate 50 random numbers from the data (guaranteed to be in the array)
    vector<int> presentKeys(50);
    for (int i = 0; i < 50; i++)
    {
        presentKeys[i] = keys[rand() % 100000];
    }

    // Generate 50 random numbers (may or may not be in the array)
    vector<int> absentKeys(50);
    for (int i = 0; i < 50; i++)
    {
        absentKeys[i] = rand() % 10000000;
    }

    // Open a file to write the output
    ofstream outputFile("output.txt");
    if (!outputFile)
    {
        cerr << "Error: Could not open the file for writing." << endl;
        return 1;
    }

    // Write the header
    outputFile << "Search Key\tFound\tSeq. Search\tBin. Search\tEnhanced Bin. Search\n";

    // Test with present keys
    for (int i = 0; i < 50; i++)
    {
        int key = presentKeys[i];
        int numCmpSeq = 0, numCmpBin = 0, numCmpEnh = 0;

        int indexSeq = seq_search(keys, key, numCmpSeq);
        int indexBin = bin_search(keys, key, numCmpBin);
        int indexEnh = bin2_search(keys, key, numCmpEnh);

        outputFile << key << "\t" << key << "\t" << numCmpSeq << "\t\t" << numCmpBin << "\t\t" << numCmpEnh << "\n";
    }

    // Test with absent keys
    for (int i = 0; i < 50; i++)
    {
        int key = absentKeys[i];
        int numCmpSeq = 0, numCmpBin = 0, numCmpEnh = 0;

        int indexSeq = seq_search(keys, key, numCmpSeq);
        int indexBin = bin_search(keys, key, numCmpBin);
        int indexEnh = bin2_search(keys, key, numCmpEnh);

        outputFile << key << "\t-1\t" << numCmpSeq << "\t\t" << numCmpBin << "\t\t" << numCmpEnh << "\n";
    }

    // Close the file
    outputFile.close();

    cout << "Search results have been written to 'output.txt'." << endl;

    return 0;
}
