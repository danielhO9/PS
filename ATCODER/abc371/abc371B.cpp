#include <bits/stdc++.h>
using namespace std;

int N, M;
bool vis[101];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		int a; char b; cin >> a >> b;
		if (b == 'M') {
			if (vis[a]) {
				cout << "No\n";
			} else {
				cout << "Yes\n";
				vis[a] = true;
			}
		} else cout << "No\n";
	}
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}