#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll MOD = 998244353;
ll inv_2;

ll pow(ll a, ll b) {
	if (b == 0) return 1ll;
	ll half = pow(a, b / 2);
	half = (half * half) % MOD;
	if (b % 2 == 0) return half;
	else return (half * a) % MOD;
}

void fwht_xor(vector<ll> &a, bool inv) {
    ll n = a.size();
    for(ll s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for(ll l = 0; l < n; l += s) {
            for(ll i = 0; i < h; i++) {
                ll t = a[l + h + i];
                a[l + h + i] = a[l + i] - t + MOD; a[l + h + i] %= MOD;
                a[l + i] += t; a[l + i] %= MOD;
                if(inv) {
					a[l + h + i] *= inv_2; a[l + h + i] %= MOD;
					a[l + i] *= inv_2; a[l + i] %= MOD;
				}
            }
        }
    }
}

int N;
const int m = 131072;
vector<ll> A(m);

vector<ll> convolute(vector<ll>& A, vector<ll>& b) {
    vector<ll> a(A.begin(), A.end());
    for (ll i = 0; i < a.size(); i++) a[i] *= b[i], a[i] %= MOD;
    fwht_xor(a, true);
    return a;
}

vector<ll> res;
vector<ll> unit(ll val) {
	vector<ll> ret; ret.push_back(val);
	return ret;
}

pair<vector<ll>, vector<ll> > dnc(int l, int r) {
	if (l + 1 == r) {
		if (A[l] == 0) {
			// cout << l << ' ' << r << '\n';
			// cout << 1;
			// cout << '\n';
			
			// cout << 0;
			// cout << '\n';
			// cout << '\n';
			return make_pair(unit(1), unit(0));
		}
		ll tmp = pow(3ll, A[l]);
		ll f = tmp;
		if (A[l] % 2) --f;
		else ++f;
		f = (f + MOD) % MOD;
		f = (f * inv_2) % MOD;
		ll s = (tmp - f + MOD) % MOD;
		// cout << l << ' ' << r << '\n';
		// cout << f;
		// cout << '\n';
		
		// cout << s;
		// cout << '\n';
		// cout << '\n';
		return make_pair(unit(f), unit(s));
	}
	ll mid = (l + r) / 2;
	pair<vector<ll>, vector<ll> > f = dnc(l, mid);
	pair<vector<ll>, vector<ll> > s = dnc(mid, r);
	vector<ll> ans_l(r - l, 0), ans_r(r - l, 0);
	fwht_xor(s.first, false);
	fwht_xor(s.second, false);
	fwht_xor(f.first, false);
	fwht_xor(f.second, false);
	
	res = convolute(f.first, s.first);
	for (int i = 0; i < res.size(); ++i) ans_l[i] += res[i], ans_l[i] %= MOD;
	
	res = convolute(f.first, s.second);
	for (int i = 0; i < res.size(); ++i) ans_r[i + mid - l] += res[i], ans_r[i + mid - l] %= MOD;

	res = convolute(f.second, s.first);
	for (int i = 0; i < res.size(); ++i) ans_r[i] += res[i], ans_r[i] %= MOD;

	res = convolute(f.second, s.second);
	for (int i = 0; i < res.size(); ++i) ans_l[i + mid - l] += res[i], ans_l[i + mid - l] %= MOD;

	// cout << l << ' ' << r << '\n';
	// for (ll i: ans_l) cout << i << ' ';
	// cout << '\n';
	
	// for (ll i: ans_r) cout << i << ' ';
	// cout << '\n';
	// cout << '\n';

	return make_pair(ans_l, ans_r);
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		ll tmp; cin >> tmp;
		++A[tmp];
	}
	inv_2 = pow(2ll, MOD - 2);
	pair<vector<ll>, vector<ll> > ans = dnc(0, m);
	cout << (ans.first[0] + ans.second[0]) % MOD;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}