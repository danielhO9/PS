#include <bits/stdc++.h>
using namespace std;

int N, K;
int ans = 0, learned = 0;
vector<string> word;

void dfs(int s) {
	if (K == 0) {
		int cnt = 0;
		for (string i: word) {
			bool flag = true;
			for (char j: i) {
				if (!((learned >> (j - 'a')) & 1)) {
					flag = false;
					break;
				} 
			}
			if (flag) ++cnt;
		}
		ans = max(ans, cnt);
		return;
	}
	if (s == 26) return;
	dfs(s + 1);
	if (!((learned >> s) & 1)) {
		learned ^= (1 << s); --K;
		dfs(s + 1);
		learned ^= (1 << s); ++K;
	}
}

void solve() {
	cin >> N >> K;
	for (int i = 0; i < N; ++i) {
		string tmp; cin >> tmp;
		word.push_back(tmp);
	}
	if (K < 5) {
		cout << 0; return;
	}
	K-= 5;
	vector<char> tmp = {'a', 'n', 't', 'i', 'c'};
	for (auto i: tmp) learned ^= (1 << (i - 'a'));
	dfs(0);
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}