#include <iostream>
using namespace std;

//1
template <typename T>
T fibonacci(T n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}


//2
template <typename T>
bool member(const T arr[], int n, const T& x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return true;
    }
    return false;
}


//3
template <typename T>
bool member(const T arr[], int n, const T& x) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == x)
            return true;
    }
    return false;
}


//4
template <typename T>
void reverseArray(T arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        T temp = arr[i];
        arr[i] = arr[n - i - 1];
        arr[n - i - 1] = temp;
    }
}


//5
template <typename T>
bool isSorted(const T arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1])
            return false;
    }
    return true;
}


//6
template <typename T>
bool isPalindrome(T arr[], int size) {
    int left = 0;
    int right = size - 1;

    while (left < right) {
        if (arr[left] != arr[right])
            return false;
        left++;
        right--;
    }
    return true;
}


//7
template <typename T, typename Predicate>
int removeIf(T arr[], int size, Predicate pred) {
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        if (!pred(arr[i])) {
            arr[newSize++] = arr[i];
        }
    }

    return newSize;
}

bool isEven(int x) {
    return x % 2 == 0;
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int size = 7;

    cout << "Original array: ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;

    size = removeIf(arr, size, isEven);

    cout << "After removeIf (removing evens): ";
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}


//8
template <typename T>
T mostFrequent(T arr[], int size) {
    int maxCount = 0;
    T mostFreq = arr[0];

    for (int i = 0; i < size; i++) {
        int count = 0;

        for (int j = 0; j < size; j++) {
            if (arr[i] == arr[j])
                count++;
        }

        if (count > maxCount) {
            maxCount = count;
            mostFreq = arr[i];
        }
    }

    return mostFreq;
}


// 9
template <typename T>
void sortArray(T arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[i]) {
                T temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
