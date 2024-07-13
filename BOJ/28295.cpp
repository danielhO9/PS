#include <bits/stdc++.h>
using namespace std;

vector<char> way = {'N', 'E', 'S', 'W'};

void solve() {
	int now = 0;
	for (int i = 0; i < 10; ++i) {
		int tmp; cin >> tmp;
		if (tmp == 1) ++now;
		else if (tmp == 2) now += 2;
		else --now;
		if (now < 0) now += 4;
		now %= 4;
	}
	cout << way[now];
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}