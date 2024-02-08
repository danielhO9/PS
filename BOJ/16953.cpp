#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL A, B;
map<LL, int> M;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> A >> B;
	deque<pair<LL, int>> Q;
	Q.push_back({A, 1}); M[A] = 1;
	bool answered = false;
	while (!Q.empty()) {
		if (Q.front().first == B) { cout << Q.front().second; answered = 1; break; }
		if (Q.front().first * 2 <= 1e9 && !M[Q.front().first * 2]) { Q.push_back({Q.front().first * 2, Q.front().second + 1}); M[Q.front().first * 2] = 1; }
		if (Q.front().first * 10 + 1 <= 1e9 && !M[Q.front().first * 10 + 1]) { Q.push_back({Q.front().first * 10 + 1, Q.front().second + 1}); M[Q.front().first * 10 + 1] = 1; }
		Q.pop_front();
	}
	if (!answered) cout << -1;
}