#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<int> p;
bool isPrime[10000], ter;
int ctoi[256];
bool used[10];
string S;

void init() {
    for (int i = 2; i < 10000; ++i) isPrime[i] = true;
    for (int i = 2; i < 10000; ++i) if (isPrime[i]) {
        p.push_back(i);
        for (int j = i * 2; j < 10000; j += i) isPrime[j] = false;
    }
    memset(ctoi, -1, sizeof(ctoi));
}

void dfs(int i) {
    if (ter) return;

    if (i == S.size()) {
        int val = 0;
        if (ctoi[S[0]] == 0) return;
        for (int i = 0; i < S.size(); ++i) {
            val += ctoi[S[i]];
            val *= 10;
        }
        val /= 10;
        if (val < 10000) {
            if (isPrime[val]) {
                cout << val;
                ter = true;
            }
            return;
        }
        for (auto j: p) {
            if (j * j > val) break;
            if (val % j == 0) return;
        }
        cout << val;
        ter = true;
        return;
    }
    
    if (ctoi[S[i]] != -1) {
        dfs(i + 1);
        return;
    }

    for (int j = 0; j < 10; ++j) if (!used[j]) {
        ctoi[S[i]] = j;
        used[j] = true;
        dfs(i + 1);
        ctoi[S[i]] = -1;
        used[j] = false;
    }
    
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    init();
    cin >> S;
    dfs(0);
    if (!ter) cout << -1;
}