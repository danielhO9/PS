#include <bits/stdc++.h>
using namespace std;

int k;
map<pair<int, int>, int> m;
int len[26];
int cnt;

struct UF {
	vector<int> par, rk;

	UF(int _sz) {
		par.resize(_sz);
		rk.resize(_sz);
		for (int i = 0; i < _sz; ++i) par[i] = i;
	}
	int find(int x) {
		if (par[x] == x) return x;
		par[x] = find(par[x]);
		return par[x];
	}
	void merge(int x, int y) {
		x = find(x); y = find(y);
		if (x == y) return;
		if (rk[x] > rk[y]) swap(x, y);
		par[x] = y;
		if (rk[x] == rk[y]) ++rk[y];
	}
};

void solve() {
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> len[i];
    int n; cin >> n;
    string s[2]; cin >> s[0] >> n >> s[1];
    vector<int> v[2];

    cnt = 0; m.clear();
    m[make_pair('0', 0)] = cnt++;
    m[make_pair('1', 0)] = cnt++;

    for (int i = 0; i < 2; ++i) {
        for (auto c: s[i]) {
            if (c == '0' || c == '1') v[i].push_back(m[make_pair(c, 0)]);
            else {
                for (int j = 0; j < len[c - 'a']; ++j) {
                    if (m.find(make_pair(c, j)) == m.end()) m[make_pair(c, j)] = cnt++;
                    v[i].push_back(m[make_pair(c, j)]);
                }
            }
        }
    }

    UF uf {cnt};
    for (int i = 0; i < v[0].size(); ++i) uf.merge(v[0][i], v[1][i]);

    long long ans = 0;
    for (int i = 0; i < cnt; ++i) if (uf.find(i) == i) ++ans;
    ans -= 2;
    cout << pow(2, ans) << '\n';

}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}