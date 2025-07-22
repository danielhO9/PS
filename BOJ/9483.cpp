#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

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
    const int m = 4;
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

vector<int> getLcp(const vector<int>& s, const vector<int>& sfx) {
	const int n = s.size();
	vector<int> inv(n), lcp(n);
	for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
	int h = 0;
	for(int i = 0; i < n; ++i) if (inv[i]) {
		int prv = sfx[inv[i] - 1];
		while (prv + h < n && i + h < n && s[prv + h] == s[i + h]) ++h;
		lcp[inv[i]] = h;
		h = max(h - 1, 0);
	}
	return lcp;
}

struct SparseTable {
    vector<vector<int>> f;

    SparseTable(const vector<int>& a) {
        const int n = a.size();
        int h = (int)ceil(log2(n));
        f.resize(n);
        for (int i = 0; i < n; ++i) f[i] = vector<int>(h, INT32_MAX);
        for (int j = 0; j < h; ++j) {
            for (int i = 0; i < n; ++i) {
                if (j == 0) f[i][j] = a[i];
                else {
                    if (i + (1 << (j - 1)) >= n) break;
                    f[i][j] = min(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
                }
            }
        }
    }
    int query(int l, int r) {
        int len = log2(r - l + 1);
        return min(f[l][len], f[r - (1 << len) + 1][len]);
    }
};

string SS;
int n;

int query(SparseTable& seg, vector<int>& inv, int i, int j, bool rev = false) {
    if (rev) {
        i = n - 1 - i;
        j = n - 1 - j;
    }
    i = inv[i]; j = inv[j];
    if (i > j) swap(i, j);
    return seg.query(i + 1, j);
}

void solve() {
    n = SS.size();
    vector<int> S(n);
    for (int i = 0; i < n; ++i) {
        if (SS[i] == 'A') S[i] = 0;
        else if (SS[i] == 'T') S[i] = 1;
        else if (SS[i] == 'G') S[i] = 2;
        else S[i] = 3;
    }
    vector<int> sfx = getSuffixArray(S);
    vector<int> lcp = getLcp(S, sfx);
    vector<int> inv(n); for (int i = 0; i < n; ++i) inv[sfx[i]] = i;
    SparseTable seg {lcp};

    auto rS = S;
    reverse(rS.begin(), rS.end());
    vector<int> rsfx = getSuffixArray(rS);
    vector<int> rlcp = getLcp(rS, rsfx);
    vector<int> rinv(n); for (int i = 0; i < n; ++i) rinv[rsfx[i]] = i;
    SparseTable rseg {rlcp};

    ll ans = 0;
    vector<pair<int, int>> v;
    for (int len = 2; len * 2 <= n; ++len) {
        v.clear();
        for (int i = 0; i < n; i += len) v.push_back(make_pair(i, min(i + len - 1, n - 1)));
        for (int i = 1; i < v.size(); ++i) {
            int lcl = query(rseg, rinv, v[i].second, v[i - 1].second, true);
            lcl = min(lcl, v[i].second - v[i].first + 1);
            if (lcl == len) ++ans;
            if (i + 1 < v.size()) {
                int lcr = query(seg, inv, v[i].first, v[i + 1].first);
                lcr = min(lcr, v[i + 1].second - v[i + 1].first + 1);
                if (lcl == len) --ans;
                if (lcr == len) --ans;
                if (len - lcl <= lcr) ans += lcr + lcl - len + 1;
            }
        }
    }
    for (int i = 0; i < n - 1; ++i) if (S[i] == S[i + 1]) ++ans;
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    while (true) {
        cin >> SS;
        if (SS[0] == '0') break;
        solve();
    }
}