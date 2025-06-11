#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 998244353;

void manacher(vector<ll>& s, vector<ll>& A) {
	const ll n = s.size();
	ll r = -1, p = -1;
	for (ll i = 0; i < n; ++i) {
		if (i < r) A[i] = min(A[2 * p - i], r - i);
		while (i - A[i] - 1 >= 0 && i + A[i] + 1 < n && s[i - A[i] - 1] == s[i + A[i] + 1]) ++A[i];
		if (r < i + A[i]) {
			r = i + A[i]; p = i;
		}
	}
}

// 각 지점을 중심으로 하는 반지름의 최댓값 = palindrome 길이
ll palindrome(vector<ll>& S) {
	vector<ll> ts;
	for (auto i: S) {
		ts.push_back(MOD);
		ts.push_back(i);
	}
	ts.push_back(MOD);
	const ll n = ts.size();
	vector<ll> A(n, 0);
	manacher(ts, A);
	ll ret = 0;
	for (int i = 0; i < n; ++i) ret += A[i] / 2;
	return ret;
}

ll pow(ll a, ll b) {
	if (b == 0) return 1;
	ll h = pow(a, b / 2);
	h = (h * h) % MOD;
	if (b % 2) return (a * h) % MOD;
	else return h;
}

int N;
string S;
ll hashed[3000];
ll pmod[3000];
ll p = 17;
ll inv;

ll hashing(int i, int j) {
	ll ret = 0;
	ll curp = 1;
	for (int k = i; k < j; ++k) {
		ret += (curp * S[k]) % MOD;
		ret %= MOD;
		curp *= p;
		curp %= MOD;
	}
	return ret;
}

void solve() {
    cin >> N >> S;
	inv = pow(p, MOD - 2);
	pmod[0] = 1;
	for (ll i = 1; i < 3000; ++i) {
		pmod[i] = pmod[i - 1] * p;
		pmod[i] %= MOD;
	}
    for (int len = 1; len <= N; ++len) {
        ll ans = 0;
		hashed[0] = hashing(0, len);
		for (int i = 1; i < N; ++i) {
			hashed[i] = hashed[i - 1] - (ll) S[i - 1] + MOD;

			hashed[i] %= MOD;
			hashed[i] *= inv; hashed[i] %= MOD;
			if (i + len - 1 < N) {
				hashed[i] += (pmod[len - 1] * (ll)S[i + len - 1]) % MOD;
				hashed[i] %= MOD;
			}
		}
		vector<ll> tmp;
        for (int i = 0; i < len; ++i) {
            tmp.clear();
            for (int j = i; j < N; j += len) tmp.push_back(hashed[j]);
            ans += palindrome(tmp);
            
        }
        ans += N - len + 1;
        cout << ans << '\n';
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    solve();
}