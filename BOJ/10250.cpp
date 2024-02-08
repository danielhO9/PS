#include <bits/stdc++.h>
using namespace std;
int H, W, N, ans;

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        cin >> H >> W >> N;
        ans = (N % H == 0 ? H : N % H) * 100;
        ans += N % H == 0 ? N / H : N / H + 1;
        cout << ans << "\n";
    }
}