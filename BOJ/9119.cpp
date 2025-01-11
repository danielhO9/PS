#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll p[2] = {17, 53};
const ll MOD = 1e9 + 9;

ll pow_p[2][15];
ll pow_inv[2][15];

ll lpow(ll a, ll b) {
	if (b == 0) return 1;
	ll half = lpow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2) return (half * a) % MOD;
	else return half;
}

ll hashing(vector<int> &s, int idx) {
	int n = s.size();
	ll ret = 0;
	for (int i = 0; i < s.size(); ++i) {
		ret += pow_p[idx][i] * (ll) s[i];
		ret %= MOD;
	}
	return ret;
}

struct Transposition {
	int i, j, k;
	bool s;
	ll h1, h2;
};

int n;

void init() {
	pow_p[0][0] = 1; pow_p[1][0] = 1;
	for (int i = 0; i < 2; ++i) {
		for (int j = 1; j < 15; ++j) {
			pow_p[i][j] = (pow_p[i][j - 1] * p[i]) % MOD;
		}
		for (int j = 0; j < 15; ++j) {
			pow_inv[i][j] = lpow(pow_p[i][j], MOD - 2);
		}
	}
}

void solve() {
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; ++i) cin >> arr[i];
	

	bool flag = true;
	for (int l = 0; l < n; ++l) if (arr[l] != l + 1) {
		flag = false;
		break;
	}
	if (flag) {
		cout << 0 << '\n';
		return;
	}

	queue< pair< int, Transposition > > q;
	Transposition arrt = {0, 0, 0, true, hashing(arr, 0), hashing(arr, 1)};
	q.push(make_pair(1, arrt));
	unordered_map<ll, int> m;
	m[arrt.h1 * arrt.h2] = 1;

	vector<int> srt(n);
	for (int i = 0; i < n; ++i) srt[i] = i + 1;
	Transposition srtt = {0, 0, 0, false, hashing(srt, 0), hashing(srt, 1)};
	q.push(make_pair(-1, srtt));
	m[srtt.h1 * srtt.h2] = -1;

	while (!q.empty()) {
		auto [val, curt] = q.front();
		q.pop();
		vector<int> cur;
		vector< vector<ll> > sum(2, vector<ll>(n));

		if (curt.s) cur = arr;
		else cur = srt;

		if (curt.k != 0) {
			vector<int> nxt = cur;
			vector<int> f, b;
			for (int l = curt.i; l < curt.j; ++l) f.push_back(cur[l]);
			for (int l = curt.j; l <= curt.k; ++l) b.push_back(cur[l]);
			for (int l = 0; l < curt.k - curt.j + 1; ++l) cur[curt.i + l] = b[l];
			for (int l = 0; l < curt.j - curt.i; ++l) cur[curt.i + curt.k - curt.j + l + 1] = f[l];
		}
		for (int i = 0; i < 2; ++i) {
			sum[i][0] = cur[0];
			for (int j = 1; j < n; ++j) {
				sum[i][j] = sum[i][j - 1];
				sum[i][j] += (cur[j] * pow_p[i][j]) % MOD;
				sum[i][j] %= MOD;
			}
		}

		for (int i = 0; i < n; ++i) for (int j = i + 1; j < n; ++j) for (int k = j; k < n; ++k) {

			ll nh[2] = {curt.h1, curt.h2};
			for (int l = 0; l < 2; ++l) {
				ll sij = sum[l][j - 1] - (i == 0 ? 0 : sum[l][i - 1]);
				sij += MOD; sij %= MOD;
				ll sjk = sum[l][k] - sum[l][j - 1];
				sjk += MOD; sjk %= MOD;
				nh[l] -= sij + sjk;
				nh[l] += 2 * MOD;
				nh[l] %= MOD;
				nh[l] += (sij * pow_p[l][k - j + 1]) % MOD;
				nh[l] %= MOD;
				nh[l] += (sjk * pow_inv[l][j - i]) % MOD;
			}

			int nval = val > 0 ? val + 1 : val - 1;
			ll h = nh[0] * nh[1];
			if (m.find(h) != m.end() && nval * m[h] < 0) {
				cout << abs(nval) + abs(m[h]) - 2 << '\n';
				return;
			}
			Transposition nxtt = {i, j, k, curt.s, nh[0], nh[1]};
			if (m.find(h) == m.end()) {
				if (abs(nval) <= 2) q.push(make_pair(nval, nxtt));
				m[h] = nval;
			}
		}
	}
	cout << "5 or more\n";
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	init();
	int t;
	cin >> t;
	while (t--) solve();
}