#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

vector<pair<int, int>> edge;
int N, M, K;
deque<ll> dq;

void solve() {
	cin >> N >> M >> K;
	for (int i = 0; i < M; ++i) {
		int X, Y; cin >> X >> Y; --X; --Y;
		edge.push_back({X, Y});
	}
	for (int i = 0; i < N; ++i) dq.push_back(0);
	dq[0] = 1;
	stack<pair<int, ll>> todo;
	for (int i = 0; i < K; ++i) {
		for (auto& j: edge) {
			todo.push({j.second, dq[j.first]});
		}
		dq.push_front(dq.back()); dq.pop_back();
		while (!todo.empty()) {
			auto q = todo.top(); todo.pop();
			dq[q.first] += q.second;
			dq[q.first] %= MOD;
		}
	}
	ll ans = 0ll;
	for (auto i: dq) {
		ans += i;
		ans %= MOD;
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}