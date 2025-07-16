#include <bits/stdc++.h>
using namespace std;

int N;
int board[32][32];

int ans = INT32_MAX;
double k = 10;
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dist(0.0, 1.0);

int getE() {
    int ret = 0, cnt;
    for (int j = 0; j < N; ++j) {
        cnt = 0;
        for (int i = 0; i < N; ++i) if (board[i][j]) ++cnt;
        cnt = min(cnt, N - cnt);
        ret += cnt;
    }
    return ret;
}

void simulated_annealing() {
    for (int i = 0; i < 10000; ++i) {
        double tt = (1.0 - i / 10000.0);
        int e1 = getE();
        ans = min(ans, e1);
        int idx = gen() % N;
        for (int j = 0; j < N; ++j) board[idx][j] ^= 1;
        int e2 = getE();
        ans = min(ans, e2);
        double p = exp((double)(e1 - e2) / (k * tt));
        if (p < dist(gen)) for (int j = 0; j < N; ++j) board[idx][j] ^= 1;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        string s; cin >> s;
        for (int j = 0; j < N; ++j) board[i][j] = (s[j] == 'H');
    }
    simulated_annealing();
    cout << ans;
}