#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;

DWORD WINAPI min_max(LPVOID lpParam) {
    vector<int>* arr = (vector<int>*)lpParam;
    int min = (*arr)[0];
    int max = (*arr)[0];
    for (int i = 1; i < arr->size(); i++) {
        if ((*arr)[i] < min) {
            min = (*arr)[i];
        }
        Sleep(7);
        if ((*arr)[i] > max) {
            max = (*arr)[i];
        }
        Sleep(7);
    }
    cout << "Min: " << min << endl;
    cout << "Max: " << max << endl;
    return 0;
}
DWORD WINAPI average(LPVOID lpParam) {
    vector<int>* arr = (vector<int>*)lpParam;
    int sum = 0;
    for (int i = 0; i < arr->size(); i++) {
        sum += (*arr)[i];
        Sleep(12);
    }
    cout << "Average: " << sum / arr->size() << endl;
    return 0;
}

int main() {
    int n;
    cout << "Enter array size: ";
    cin >> n;
    vector<int> arr(n);
    cout << "Enter array elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, &arr, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, &arr, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    int sum = 0;
    int min = arr[0];
    int max = arr[0];
    for (int i = 0; i < n; i++) {
        sum += arr[i];
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    double avg = sum / n;

    for (int i = 0; i < n; i++) {
        if (arr[i] == min || arr[i] == max) {
            arr[i] = avg;
        }
        cout << arr[i] << " ";
    }
    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    arr.clear();
    return 0;
}