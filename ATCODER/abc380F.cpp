#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll hashing(multiset<ll>& arr) {
	const ll MOD = 1e9 + 9;
	const ll p = 31;
	ll ans = 0ll;
	ll pp = 1;
	for (auto& i: arr) {
		ans += ((i * pp) % MOD);
		ans %= MOD;
		pp *= p; pp %= MOD;
	}
	return ans;
}

ll hashing(vector<multiset<ll>>& arr) {
	vector<ll> hashed;
	for (auto& i: arr) hashed.push_back(hashing(i));
	const ll MOD = 1e9 + 9;
	const ll p = 53;
	ll ans = 0ll;
	ll pp = 1;
	for (auto& i: hashed) {
		ans += ((i * pp) % MOD);
		ans %= MOD;
		pp *= p; pp %= MOD;
	}
	return ans;
}

vector<multiset<ll>> cards(3);
unordered_map<ll, ll> cache;

ll grundy(vector<multiset<ll>> arr) {
	ll hashed = hashing(arr);
	ll& ret = cache[hashed];
	if (ret != 0) return ret;
	if (arr[0].size() == 0) {
		ret = 1;
		return ret;
	}

	swap(arr[0], arr[1]);
	vector<ll> tmp, tmp2;
	for (auto i: arr[1]) tmp.push_back(i);
	for (auto i: arr[2]) tmp2.push_back(i);

	for (auto i: tmp) {
		arr[1].erase(arr[1].find(i));
		arr[2].insert(i);
		if (grundy(arr) == 1) {
			ret = 2;
			return ret;
		}
		for (auto j: tmp2) {
			if (j < i) {
				arr[2].erase(arr[2].find(j));
				arr[1].insert(j);
				if (grundy(arr) == 1) {
					ret = 2;
					return ret;
				}
				arr[2].insert(j);
				arr[1].erase(arr[1].find(j));
			}
		}
		if (grundy(arr) == 1) {
			ret = 2;
			return ret;
		}
		arr[1].insert(i);
		arr[2].erase(arr[2].find(i));
	}
	ret = 1;
	return ret;
}

void solve() {
	int N, M, L; cin >> N >> M >> L;
	for (int i = 0; i < N; ++i) {
		int tmp; cin >> tmp;
		cards[0].insert(tmp);
	}
	for (int i = 0; i < M; ++i) {
		int tmp; cin >> tmp;
		cards[1].insert(tmp);
	}
	for (int i = 0; i < L; ++i) {
		int tmp; cin >> tmp;
		cards[2].insert(tmp);
	}
	if (grundy(cards) == 2) cout << "Takahashi";
	else cout << "Aoki";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}