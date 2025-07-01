#include <bits/stdc++.h>
using namespace std;

bool radixSort(vector<int>& rk, int k) {
    const int n = rk.size();
    int m = *max_element(rk.begin(), rk.end());
    if (n == m) return false;
    vector<int> sr(n), srk(n);
    vector<int> cnt(m + 1);

    vector<int> rkk(n);
    for (int i = 0; i < n; ++i) {
        if (i + k < n) rkk[i] = rk[i + k];
        else rkk[i] = 0;
    }

    for (auto i: rkk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) srk[--cnt[rkk[i]]] = i;
    reverse(srk.begin(), srk.end());

    for (auto& i: cnt) i = 0;
    for (auto i: rk) ++cnt[i];
    for (int i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (int i = 0; i < n; ++i) {
        int j = srk[i];
        sr[--cnt[rk[j]]] = j;
    }

    vector<int> nrk(n);
    m = 1; nrk[sr[0]] = m;
    for (int i = 1; i < n; ++i) {
        int cur = sr[i], prv = sr[i - 1];
        if (rk[cur] != rk[prv] || rkk[cur] != rkk[prv]) ++m;
        nrk[cur] = m;
    }
    swap(nrk, rk);
    return true;
}

vector<int> getSuffixArray(const vector<int>& s) {
    const int n = s.size();
    const int m = 200001;
    vector<int> cnt(m);
    for (auto i: s) cnt[i] = 1;
    for (int i = 1; i < m; ++i) cnt[i] += cnt[i - 1];

    vector<int> rk(n);
    for (int i = 0; i < n; ++i) rk[i] = cnt[s[i]];
    int k = 1;
    while (radixSort(rk, k)) k *= 2;

    vector<int> sfx(n);
    for (int i = 0; i < n; ++i) sfx[rk[i] - 1] = i;
    return sfx;
}

int N, K;

void solve() {
    cin >> N >> K;
	vector<int> S(N);
    for (int i = 0; i < N; ++i) cin >> S[i];
    reverse(S.begin(), S.end());
    vector<int> SS(2 * N);
    for (int i = 0; i < 2 * N; ++i) SS[i] = S[i % N];
	vector<int> sfx = getSuffixArray(SS);
    for (auto i: sfx) if (1 <= i && i < N) {
        --K;
        if (K == 0) {
            for (int j = 0; j < N; ++j) cout << SS[i + j] << ' ';
            return;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}