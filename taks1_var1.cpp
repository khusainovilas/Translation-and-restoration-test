/*Отсортировать сортировкой выбором только элементы массива с нечётными значениями.
Элементы с чётными значениями должны остаться на своих местах.*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

// return the generated array with a range of numbers between 1 and 1000.
vector<int> generateArray(const int size){
    vector<int> array(size);
    for (int i = 0; i < size; i++){
        array[i] = 1 + rand() % 1000; 
    }
    return array;
}

// realization selection sort.
void selectionSort(vector<int>& array){
    const int n = array.size();
    for (int i = 0; i < n - 1; i++){
        int min = i;
        for (int j = i + 1; j < n; j++){
            if (array[j] < array[min]) {
                min = j;
            }
        }
        swap(array[i], array[min]);
    }
}

// realization of sorting of odd elements
void selectionSortOdd(vector<int>& array){
    // separating all odd values from the array for sorting.
    vector<int> oddValues;
    for (int x : array) {
        if (x % 2 != 0) {
            oddValues.push_back(x);
        }
    }

    selectionSort(oddValues);

    // the already sorted odd elements are inserted back into the array.
    int i = 0;
    for (int& x : array){
        if (x % 2 != 0) {
            x = oddValues[i];
            i++;
        }
    }
}

// The function of checking whether the array is sorted in ascending order
bool arraySortedCheck(const vector<int>& array) {
    for (int i = 1; i < array.size(); i++) {
        if (array[i] < array[i - 1]) {
            return false;
        }
    }
    return true;
}

// A function to check whether the odd values of an array are sorted in ascending order.
bool arraySortedCheckOdd(const vector<int> array) {
    int prevOdd = -1;
    for (int x : array) {
        if (x % 2 != 0) {
            if (prevOdd != -1 && x < prevOdd) {
                return false;
            }
            prevOdd = x;
        }
    }
    return true;
}

// A function with a message output
bool checkSort(const vector<int> array, string message) {
    if (!arraySortedCheckOdd(array)) {
        cout << "Test failed on " << message << endl;
        return false;
    }
    return true;
}

// 
void printArray(const vector<int> array) {
    for (int x : array) {
        cout << x << " ";
    }
}


// test for correctness of select sort.
bool testSelectionCorrect() {

    // test1: check the sorting of odd numbers when in an array
    vector<int> array_test1 = {5, 2, 9, 1, 5};
    selectionSortOdd(array_test1);
    vector<int> expected_test1 = {1, 2, 5, 5, 9};
    if (array_test1 != expected_test1) {
        cout << "Test 1 failed: expected 1 2 5 5 9, got ";
        printArray(array_test1);
        return false;
    }

    // test2: 
    vector<int> array_test2 = {10, 3, 6, 7, 8, 1};
    selectionSortOdd(array_test2);
    vector<int> expected_test2 = {10, 1, 6, 3, 8, 7};
    if (array_test2 != expected_test2) {
        cout << "Test 2 failed: expected 10 1 6 3 8 7, got ";
        printArray(array_test1);
        return false;
    }
    
    // test3: Checking on the generated array of size 20.
    srand(time(nullptr));
    int size_test3 = 20;
    vector<int> array_test3 = generateArray(size_test3);

    selectionSortOdd(array_test3);
    if (!arraySortedCheckOdd(array_test3)) {
        cout << "Test 3 failed: odd elements are not sorted in a random array\n";
        return false;
    }

    cout << "All tests passed successfully\n";
    return true;
}


int main() {
    testSelectionCorrect();
    return 0;
}