#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N;
LL ans, dif[500001];
priority_queue<LL> Q;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; LL a, b;
	for (int i = 1; i <= N; ++i) {
		cin >> a >> b;
		dif[i] = dif[i -1] + a - b;
	}
	for (int i = 1; i <= N; ++i) {
		if (dif[i] < 0) {
			ans += abs(dif[i]);
			dif[i] = 0;
		}
		if (!Q.empty() && Q.top() > dif[i]) {
			ans += Q.top() - dif[i];
		}
		Q.push(dif[i]); Q.push(dif[i]); Q.pop();
	}
	while (!Q.empty() && Q.top() > dif[N]) {
		ans += Q.top() - dif[N];
		Q.pop();
	}
	cout << ans;
}