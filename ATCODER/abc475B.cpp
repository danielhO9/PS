#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
ll A[1000];
ll cnt[3];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> A[i];
    for (int i = 0; i < N; ++i) {
        ll d = (A[i] + 999) / 1000 * 1000;
        ll dif = d - A[i];
        for (int j = 0; j < 3; ++j) {
            cnt[j] += dif % 10;
            dif /= 10;
        }
    }
    for (int i = 0; i < 3; ++i) cout << cnt[i] << ' ';
}