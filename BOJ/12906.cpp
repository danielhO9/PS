#include <bits/stdc++.h>
using namespace std;

unordered_map<string, unordered_map<string, unordered_map<string, int>>> M;

void solve() {
	string hanoi[3];
	int cnt[3]; memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < 3; ++i) {
		int tmp; cin >> tmp;
		if (tmp == 0) hanoi[i] = "";
		else cin >> hanoi[i];
		for (auto j: hanoi[i]) ++cnt[j - 'A'];
	}
	queue<vector<string>> Q; Q.push({hanoi[0], hanoi[1], hanoi[2]});
	M[hanoi[0]][hanoi[1]][hanoi[2]] = 1;
	while (!Q.empty()) {
		vector<string> here = Q.front(); Q.pop();
		// for (auto i: here) cout << i << ' ';
		// cout << '\n';
		int d = M[here[0]][here[1]][here[2]];
		for (int i = 0; i < 3; ++i) {
			if (here[i] != "") {
				int ni = (i + 1) % 3;
				int nni = (ni + 1) % 3;
				here[ni].push_back(here[i].back());
				here[i].pop_back();
				if (M[here[0]][here[1]][here[2]] == 0) {
					vector<string> tmp = here;
					Q.push(tmp);
					M[here[0]][here[1]][here[2]] = d + 1;
				}
				here[nni].push_back(here[ni].back());
				here[ni].pop_back();
				if (M[here[0]][here[1]][here[2]] == 0) {
					vector<string> tmp = here;
					Q.push(tmp);
					M[here[0]][here[1]][here[2]] = d + 1;
				}
				here[i].push_back(here[nni].back());
				here[nni].pop_back();
			}
		}
	}
	string ans[3];
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < cnt[i]; ++j) {
			ans[i].push_back('A' + i);
		}
	}
	cout << M[ans[0]][ans[1]][ans[2]] - 1;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}