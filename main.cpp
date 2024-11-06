#include "sorting-algorithms/bubbleSort.h"
#include "sorting-algorithms/heapSort.h"
#include "sorting-algorithms/insertionSort.h"
#include "sorting-algorithms/mergeSort.h"
#include "sorting-algorithms/quickSort.h"
#include "sorting-algorithms/radixSort.h"
#include "sorting-algorithms/selectionSort.h"
#include "stability-test/contactsList.h"
#include <iomanip>
#include "Pizza.h"
#include<vector>
using namespace std;

void stabilityTest();

int main() {
    //vector of custom data type objects
    vector<Pizza> pizzas;
    if(loadData(pizzas)) {
        cout<<"Pizza data loaded"<<endl;
    }

    //loop through vector sizes from 1000 to 100 in decrements of 100
    unsigned long reads;
    unsigned long allocations;

    for(int i = 1000; i > 0; i -= 100) {
        // TODO: sort the vector in four different ways (bubble, ?, heap, ?)

        pizzas.resize(i);

        //bubble sort
        bubbleSort(pizzas, reads, allocations);
        cout<<"Bubble Sort: Reads = "<<reads<<" Allocations = "<<allocations<<
            "Size = "<<i<<endl;

        //heap sort
        heapSort(pizzas, reads, allocations);
        cout<<"Heap Sort: Reads = "<<reads<<" Allocations = "<<allocations<<
            "Size = "<<i<<endl;

        //merge sort
        mergeSort(pizzas, reads, allocations);
        cout<<"Merge Sort: Reads = "<<reads<<" Allocations = "<<allocations<<
            "Size = "<<i<<endl;

        //selection sort
        selectionSort(pizzas, reads, allocations);
        cout<<"Selection Sort: Reads = "<<reads<<" Allocations = "<<allocations<<
            "Size = "<<i<<endl;
    }
    // TODO: record the number of reads and allocations for each sort

    stabilityTest();
    return 0;
}

void stabilityTest() {
    ContactsList people;
    people.readContactsFromFile("../stability-test/names.csv");
    cout << "People (Default ordering)" << endl;
    people.printList();

    cout << endl << "Bubble Sort" << endl;
    people.sortAndPrint(bubbleSort<contact>);

    // TODO: add other stable algorithm here

    cout << endl << "Heap Sort" << endl;
    people.sortAndPrint(heapSort<contact>);

    // TODO: add other unstable algorithm here
}