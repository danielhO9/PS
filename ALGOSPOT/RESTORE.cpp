#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 15;
int k;
string word[MAX_N];
int cache[MAX_N][1 << MAX_N], overlap[MAX_N][MAX_N];

int restore(int last, int used) {
	if (used == (1 << k) - 1) return 0;
	int& ret = cache[last][used];
	if (ret != -1) return ret;
	ret = 0;
	for (int next = 0; next < k; ++next) {
		if ((used & (1 << next)) == 0) {
			int cand = overlap[last][next] + restore(next, used + (1 << next));
			ret = max(ret, cand);
		}
	}
	return ret;
}

string reconstruct(int last, int used) {
	if (used == (1 << k) - 1) return "";
	for (int next = 0; next < k; ++next) {
		if (used & (1 << next)) continue;
		int ifUsed = restore(next, used + (1 << next)) + overlap[last][next];
		if (restore(last, used) == ifUsed) return (word[next].substr(overlap[last][next]) + reconstruct(next, used + (1 << next)));
	}
	return "error";
}

void solve() {
	cin >> k;
	memset(cache, -1, sizeof(cache));
	memset(overlap, 0, sizeof(overlap));
	vector<string> V;
	for (int i = 0; i < k; ++i) {
		string temp; cin >> temp;
		V.push_back(temp);
	}
	k = 0;
	for (int f = 0; f < V.size(); ++f) {
		string a = V[f];
		bool flag = false;
		for (int l = 0; l < V.size(); ++l) if (l != f) {
			string b = V[l];
			if (flag) break;
			if (a.size() > b.size()) continue;
			for (int i = 0; i < b.size(); ++i) {
				bool tflag = true;
				for (int j = 0; j < a.size(); ++j) {
					if (i + j >= b.size() || b[i + j] != a[j]) {
						tflag = false;
						break;
					}
				}
				if (tflag) {
					flag = true;
					break;
				}
			}
		}
		if (!flag) {
			word[k] = a;
			++k;
		}
	}
	for (int i = 0; i < k; ++i) for (int j = 0; j < k; ++j) {
		string a = word[i], b = word[j];
		int an = a.size(), bn = b.size();
		for (int l = min(an, bn); l >= 0; --l) {
			bool flag = true;
			for (int m = 0; m < l; ++m) {
				if (a[m + an - l] != b[m]) {
					flag = false; break;
				}
			}
			if (flag) {
				overlap[i][j] = l;
				break;
			}
		}
	}
	int start = -1, ans = -1;
	for (int i = 0; i < k; ++i) {
		if (ans < restore(i, 1 << i)) {
			start = i;
			ans = restore(i, 1 << i);
		}
	}
	cout << word[start];
	cout << reconstruct(start, 1 << start) << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}