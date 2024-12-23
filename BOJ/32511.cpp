#include <bits/stdc++.h>
using namespace std;

int N, Q;
vector<pair<int, int> > W, nW;
vector<vector<int> > fW(120000, vector<int>(17));
vector<pair<int, int> > w, nw;

void solve() {
	cin >> N;
	W.clear();
	for (int i = 0; i < N; ++i) {
		int s, e; cin >> s >> e;
		W.push_back(make_pair(s, e));
	}
	sort(W.begin(), W.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
		if (a.second == b.second) return a.first > b.first;
		return a.second < b.second;
	});
	w.clear();
	for (auto i: W) {
		if (!w.empty() && w.back().first >= i.first) continue;
		w.push_back(i);
	}
	swap(w, W);
	N = W.size();

	int cur = 0;
	for (int i = 0; i < N; ++i) {
		while (cur < N && W[cur].first < W[i].second) ++cur;
		fW[i][0] = cur;
	}

	for (int i = 1; i < 17; ++i) {
		for (int j = 0; j < N; ++j) {
			if (fW[j][i - 1] == N) fW[j][i] = N;
			else fW[j][i] = fW[fW[j][i - 1]][i - 1];
		}
	}

	cin >> Q;
	while (Q--) {
		nW.clear();
		int R; cin >> R;
		for (int i = 0; i < R; ++i) {
			int s, e; cin >> s >> e;
			nW.push_back({s, e});
		}
		sort(nW.begin(), nW.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
			if (a.second == b.second) return a.first > b.first;
			return a.second < b.second;
		});

		nw.clear();
		for (auto i: nW) {
			if (!nw.empty() && nw.back().first >= i.first) continue;
			nw.push_back(i);
		}
		swap(nw, nW);
		R = nW.size();
		

		int curp = 0, tm = 0, ans = 0;
		for (int curn = 0; curn < R; ++curn) {

			if (nW[curn].first < tm) continue;
			if (curp != N && W[curp].second <= nW[curn].first) {
				for (int i = 16; i >= 0; --i) {
					if (fW[curp][i] != N && W[fW[curp][i]].second <= nW[curn].first) {
						curp = fW[curp][i];
						ans += (1 << i);
					}
				}
				++ans;
				curp = fW[curp][0];
			}
			if (curp != N) {
				tm = min(nW[curn].second, W[curp].second);
				pair<int, int> tmp = {tm, INT32_MIN};
				curp = lower_bound(W.begin(), W.end(), tmp) - W.begin();
				++ans;
			} else {
				++ans;
				tm = nW[curn].second;
			}

		}
		if (curp != N) {
			for (int i = 16; i >= 0; --i) {
				if (fW[curp][i] != N) {
					curp = fW[curp][i];
					ans += (1 << i);
				}
			}
			++ans;
		}

		cout << ans << '\n';
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	int cnt = 0;
	while (t--) {
		++cnt;
		cout << "Case #" << cnt << '\n';
		solve();
		// cout.flush();
	}
}