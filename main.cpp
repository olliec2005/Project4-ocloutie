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

    ofstream bubble_out;
    ofstream heap_out;
    ofstream selection_out;
    ofstream merge_out;

    bubble_out.open("../data/bubble.csv");
    heap_out.open("../data/heap.csv");
    selection_out.open("../data/select.csv");
    merge_out.open("../data/merge.csv");

    bubble_out<<"Size, Reads, Allocations"<<endl;
    heap_out<<"Size, Reads, Allocations"<<endl;
    selection_out<<"Size, Reads, Allocations"<<endl;
    merge_out<<"Size, Reads, Allocations"<<endl;

    for(int i = 1000; i > 0; i -= 100) {
        pizzas.resize(i);

        //bubble sort
        bubbleSort(pizzas, reads, allocations);
        bubble_out<<i<<", "<<reads<<", "<<allocations<<endl;

        //heap sort
        heapSort(pizzas, reads, allocations);
        heap_out<<i<<", "<<reads<<", "<<allocations<<endl;

        //merge sort
        mergeSort(pizzas, reads, allocations);
        merge_out<<i<<", "<<reads<<", "<<allocations<<endl;

        //selection sort
        selectionSort(pizzas, reads, allocations);
        selection_out<<i<<", "<<reads<<", "<<allocations<<endl;
    }

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

    cout << endl << "Merge Sort" << endl;
    people.sortAndPrint(mergeSort<contact>);

    cout << endl << "Heap Sort" << endl;
    people.sortAndPrint(heapSort<contact>);

    cout << endl << "Selection Sort" << endl;
    people.sortAndPrint(selectionSort<contact>);
}