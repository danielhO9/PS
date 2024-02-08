#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	priority_queue<LL, vector<LL>, greater<>> Q;
	for (int i = 0; i < N; ++i) {
		LL temp; cin >> temp;
		Q.push(temp);
	}
	LL ans = 0;
	while (Q.size() > 1) {
		LL a = Q.top(); Q.pop();
		LL b = Q.top(); Q.pop();
		ans += a + b;
		Q.push(a + b);
	}
	cout << ans;
}