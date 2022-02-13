#include <iostream>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    int max = INT16_MIN, min = INT16_MAX;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (max < a[i]) {
            max = a[i];
        }
    }
#pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (min > a[i]) {
            min = a[i];
        }
    }
    cout << max << endl;
    cout << min << endl;
}
