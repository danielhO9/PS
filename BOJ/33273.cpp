#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, M;
ll x[500], c[500];
ll cache[500][501];

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> M;
	for (ll i = 0; i < M; ++i) cin >> x[i] >> c[i];
	vector<pair<int, int>> v;
	for (int i = 0; i < M; ++i) v.push_back({-x[i], i});
	sort(v.begin(), v.end());
	vector<int> idx;
	for (int i = 0; i < M; ++i) idx.push_back(v[i].second);
	memset(cache, -1, sizeof(cache));
	for (ll i = 0; i <= min(c[idx[0]], N); ++i) cache[0][i] = x[idx[0]] * i;
	for (int i = 1; i < M; ++i) {
		for (int j = 0; j < i; ++j) if (x[idx[j]] % x[idx[i]] == 0) {
			
		}
	}
}