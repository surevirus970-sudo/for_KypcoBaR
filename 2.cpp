#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Введите элементы: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    int iz = 0;
    for (int i = 0; i < n; ++i) {
        if (arr[i] != 0) {
            arr[iz] = arr[i];
            iz++;
        }
    }

    while (iz < n) {
        arr[iz] = 0;
        iz++;
    }

    cout << "Результат: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;
    
    return 0;
}
