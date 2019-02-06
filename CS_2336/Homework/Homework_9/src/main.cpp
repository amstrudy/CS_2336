// Homework 9
// Anja Sheppard AMS180001

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void bubbleSort (int *);
void insertionSort (int *);
void selectionSort (int *);
void swap (int *xp, int *yp); 

int numBubbleSortComparisons = 0;
int numBubbleSortAssignments = 0;
int numInsertionSortComparisons = 0;
int numInsertionSortAssignments = 0;
int numSelectionSortComparisons = 0;
int numSelectionSortAssignments = 0;

int main ()
{
    srand(time(NULL));
    int array1[5000];
    int array2[5000];
    int array3[5000];
    for (size_t i = 0; i < 5000; ++i)
    {
        array1[i] = rand() % 5000;
        array2[i] = rand() % 5000;
        array3[i] = rand() % 5000;
    }
    bubbleSort(array1);
    insertionSort(array2);
    selectionSort(array3);
    cout << "BUBBLE:\nNUM COMPARISIONS: " << numBubbleSortComparisons << "\nNUM ASSIGNMENTS: " << numBubbleSortAssignments << std::endl;
    cout << "INSERTION:\nNUM COMPARISIONS: " << numInsertionSortComparisons << "\nNUM ASSIGNMENTS: " << numInsertionSortAssignments << std::endl;
    cout << "SELECTION:\nNUM COMPARISIONS: " << numSelectionSortComparisons << "\nNUM ASSIGNMENTS: " << numSelectionSortAssignments << std::endl;
    return 0;
}

void bubbleSort (int *arr)
{
    int i, j, n = 5000;
    numBubbleSortAssignments+=3;
    for (i = 0; i < n-1; i++)
    {
        numBubbleSortAssignments++;
        numBubbleSortComparisons++;
        for (j = 0; j < n-i-1; j++)  
        {
            numBubbleSortAssignments++;
            numBubbleSortComparisons++;
            if (arr[j] > arr[j+1]) 
            {
                swap(&arr[j], &arr[j+1]); 
                numBubbleSortComparisons++;
                numBubbleSortAssignments+=2;
            }
        }
    }
}

void insertionSort (int *arr)
{
    int i, key, j; 
    numInsertionSortAssignments+=3;
    for (i = 1; i < 5000; i++) 
    { 
        numInsertionSortComparisons++;
        numInsertionSortAssignments+=4;
        key = arr[i]; 
        j = i-1; 
  
        while (j >= 0 && arr[j] > key) 
        { 
            numInsertionSortComparisons++;
            numInsertionSortAssignments++;
            arr[j+1] = arr[j]; 
            j = j-1; 
        } 
        arr[j+1] = key; 
    } 
}

void selectionSort (int *arr)
{
	int i, j, min_idx, n = 5000; 
    numSelectionSortAssignments += 4;
  
    // One by one move boundary of unsorted subarray 
    for (i = 0; i < n-1; i++) 
    { 
        numSelectionSortAssignments++;
        numSelectionSortComparisons++;
        // Find the minimum element in unsorted array 
        min_idx = i; 
        numSelectionSortAssignments++;
        for (j = i+1; j < n; j++) 
        {
            numSelectionSortComparisons++;
            numSelectionSortAssignments++;
            if (arr[j] < arr[min_idx]) 
            {  
                min_idx = j; 
                numSelectionSortComparisons++;
                numSelectionSortAssignments++;
            }
        }
        // Swap the found minimum element with the first element 
        swap(&arr[min_idx], &arr[i]); 
        numSelectionSortAssignments+=2;
    } 
}

void swap (int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 
