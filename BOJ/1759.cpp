#include <bits/stdc++.h>
using namespace std;

vector<char> pass;
vector<char> avail;
int L, C;

void generator() {
	if (pass.size() == L) {
		int jcnt = 0, mcnt = 0;
		for (auto i: pass) {
			if (i == 'a' || i == 'e' || i =='i' || i == 'o' || i == 'u') ++mcnt;
			else ++jcnt;
		}
		if (jcnt >= 2 && mcnt >= 1) {
			for (auto i: pass) cout << i;
			cout << '\n';
		}
		return;
	}
	for (auto i: avail) {
		if (!pass.empty() && pass.back() >= i) continue;
		pass.push_back(i);
		generator();
		pass.pop_back();
	}
}

void solve() {
	cin >> L >> C;
	avail.resize(C);
	for (int i = 0; i < C; ++i) cin >> avail[i];
	sort(avail.begin(), avail.end());
	generator();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}