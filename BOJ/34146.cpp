#include <bits/stdc++.h>
using namespace std;

int N, M;
int A[100][100];
int cnt[10001];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
        cin >> A[i][j];
        ++cnt[A[i][j]];
    }
    int odd = 0;
    for (int i = 1; i <= 10000; ++i) {
        if (cnt[i] % 2) ++odd;
    }
    int even = N * M - odd;
    int mid = 0;
    if (M % 2) mid = N;
    if (odd > mid) {
        cout << "NO";
        return 0;
    }
    int rem = mid - odd;
    if (rem % 2 == 0) {
        cout << "YES";
    } else cout << "NO";
}