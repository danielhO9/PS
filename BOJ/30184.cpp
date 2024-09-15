#include <bits/stdc++.h>
using namespace std;

int N;
string T;
int now = 0;

vector<char> ans;

void f(int l, int r) {
	// cout << l << ' ' << r << '\n';
	if (l > r) return;
	if (T[l + 1] != T[l]) {
		ans.push_back(T[l]);
		now += 2;
		f(l + 2, r);
		return;
	}
	int pos = now;
	int cnt = 0;
	int nr = r;
	while (cnt != 0 || T[nr] == T[l]) {
		if (T[nr] == 'S') ++cnt;
		else --cnt;
        --nr;
	}
	f(nr + 1, r);
	while (now > pos) {
		--now;
		ans.push_back('N');
	}
	ans.push_back(T[l]);
	ans.push_back('N');
	++now;
	return f(l + 1, nr - 1);
}

void solve() {
	cin >> N >> T;
	f(0, N - 1);
    cout << ans.size() << '\n';
	for (auto i: ans) cout << i;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}