#include <iostream>
#include <random>
#include <chrono>

using namespace std;
using namespace chrono;

void quicksort(int arr[], int left, int right)
{
    int i = left, j = right;
    int pivot = arr[(left + right) / 2];

    //partition
    while (i <= j) {
        while (arr[i] < pivot)
            i++;
        while (arr[j] > pivot)
            j--;
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    };

    //recursion
    if (left < j)
        quicksort(arr, left, j);
    if (i < right)
        quicksort(arr, i, right);
}

void countingSort(int arr[], int n)
{
    //find max value
    int max = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (arr[i] > max)
            max = arr[i];
    }

    //fill count array with zeros
    int* count = new int[max + 1];
    for (int i = 0; i <= max; i++)
    {
        count[i] = 0;
    }

    //count the numbers
    for (int i = 0; i < n; i++)
    {
        count[arr[i]]++;
    }

    //set count of i to the actual position of i in the output array
    for (int i = 1; i <= max; i++)
    {
        count[i] += count[i - 1];
    }

    //create output array
    int* output = new int[n];
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    //put back the numbers
    for (int i = 0; i < n; i++)
    {
        arr[i] = output[i];
    }

    delete[] count;
    delete[] output;
}

int main()
{
    int n = 10;
    int m = 10;
    srand(time(0));
    int arr[n];
    bool sorted;

    //Problem 1

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % m;
    }

    auto start = high_resolution_clock::now();

    quicksort(arr, 0, n - 1);

    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Quicksort: " << duration.count() << " microseconds" << endl;

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % m;
    }

    start = high_resolution_clock::now();

    countingSort(arr, n);

    stop = high_resolution_clock::now();

    duration = duration_cast<microseconds>(stop - start);

    cout << "Counting Sort: " << duration.count() << " microseconds" <<endl;

    //n = 10000, m = 5
    //Quicksort: 404 microseconds
    //Counting Sort: 87 microseconds
    //n = 100, m = 10000
    //Quicksort: 5 microseconds
    //Counting Sort: 35 microseconds
    //n = 100. m = 100
    //Quicksort: 4 microseconds
    //Counting Sort: 4 microseconds

    //based on this, it seems that when the number of inputs is larger then the range of numbers, than counting sort does a lot better.
    //when the inputs are small then quicksort does better than counting sort, but as the number of inputs increases, then counting sort
    //performs better and better than quicksort.

    //Problem 2

    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % m;
    }

    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    int p[n];
    for (int i = 0; i < n; i++)
    {
        p[i] = i;
    }

    do
    {
        sorted = false;
        for (int i = 0; i < n-1; i++)
        {
            if (arr[p[i]] > arr[p[i+1]])
            {
                swap(p[i], p[i+1]);
                sorted = true;
            }
        }
    }while(sorted);

    int newArr[n];

    for (int i = 0; i < n; i++)
    {
        newArr[i] = arr[p[i]];
    }

    for (int i = 0; i < n; i++)
    {
        cout << newArr[i] << " ";
    }
    cout << endl;

    return 0;
}


