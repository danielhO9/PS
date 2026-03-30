#include <iostream>
using namespace std;

int N;
int arr[1000];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> arr[i];
    sort(arr, arr + N);
    vector<int> v;
    for (int i = 0; i < N; ++i) {
        int mn = INT32_MAX;
        for (int j: v) mn = min(mn, j);
        if (mn > arr[i]) v.push_back(1);
        else {
            for (int& j: v) if (j == mn) {
                ++j;
                break;
            }
        }
    }
    cout << v.size();
}