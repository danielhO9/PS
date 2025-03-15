#include <bits/stdc++.h>
using namespace std;

int N;
int arr[10][10];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N; for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) cin >> arr[i][j];
    for (int j = 0; j < N; ++j) {
        int cur = 0, cnt = 0;
        for (int i = 0; i < N; ++i) if (cur < arr[i][j]) {
            ++cnt;
            cur = arr[i][j];
        }
        cout << cnt << ' ';
    }
    cout << '\n';
    for (int i = 0; i < N; ++i) {
        int cur = 0, cnt = 0;
        for (int j = 0; j < N; ++j) if (cur < arr[i][j]) {
            ++cnt;
            cur = arr[i][j];
        }
        cout << cnt << '\n';
    }
}