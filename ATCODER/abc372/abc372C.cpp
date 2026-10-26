#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N, Q;
string S;

void solve() {
	cin >> N >> Q;
	cin >> S;
	int cnt = 0;
	for (int i = 0; i < N - 2; ++i) {
		if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C') ++cnt;
	}
	while (Q--) {
		int X; char C; cin >> X >> C; --X;
		for (int i = X - 2; i <= X; ++i) {
			if (i + 2 <= N - 1) {
				if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C') --cnt;
			}
		}
		S[X] = C;
		for (int i = X - 2; i <= X; ++i) {
			if (i + 2 <= N - 1) {
				if (S[i] == 'A' && S[i + 1] == 'B' && S[i + 2] == 'C') ++cnt;
			}
		}
		cout << cnt << "\n";
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}