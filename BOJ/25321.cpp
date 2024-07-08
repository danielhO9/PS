#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 1000000007;
ll fac[1000001],inverse[1000001];

ll pow(ll x, ll y) {
    if(y == 0) return 1ll;
    if(y % 2) return (pow(x, y - 1) * x) % MOD;
    ll half = pow(x, y / 2) % MOD;
    return half * half % MOD;
}

void init() {
	fac[0]=1;
    for(int i = 1;i <= 1000000; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    inverse[1000000] = pow(fac[1000000], MOD - 2);
    for(int i = 1000000 - 1; i >= 0; i--) {
        inverse[i] = inverse[i+1] * (i + 1) % MOD;
    }
}

ll calc(int n) { return fac[2 * n] * ((inverse[n + 1] * inverse[n]) % MOD) % MOD; }

void solve() {
	string S; cin >> S;
	stack<char> st;
	ll ans = 1;
	for (int i = 0; i < S.size(); ++i) {
		if (i + 1 != S.size() && S[i] != '?' && S[i] != ':') continue;
		if (i + 1 == S.size() || (S[i] == ':' && st.top() == ':')) {
			int cnt = 0;
			while (st.size() >= 2) {
				char prv = st.top(); st.pop();
				char pprv = st.top(); st.pop();
				if (pprv == '?' && prv == ':') ++cnt;
				else {
					st.push(pprv);
					st.push(prv);
					break;
				}
			}
			if (cnt != 0) ans *= calc(cnt);
			ans %= MOD;
		}
		st.push(S[i]);
	}
	cout << ans;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	init();
	solve();
}