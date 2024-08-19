#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 접미사 배열의 정렬
// https://gist.github.com/koosaga/44532e5dec947132ee55da0458255e05
vector<ll> getSuffixArray(string& s) {
	ll m = 255;
	const ll n = s.size();
	ll t = 1;
	vector<ll> group(n + 1), sfx(n), newGroup(n + 1), nxtord(n + 1);
	ll cnt[max(m, n) + 1];
	
	for(ll i = 0; i < n; ++i) group[i] = s[i];
	
	ll pt = 1;
	while (true) {
		// nxtord: i를 group[i + t]로 정렬
		memset(cnt, 0, sizeof(cnt));
		for (ll i = 0; i < n; ++i) ++cnt[group[min(i + t, n)]];
		for (ll i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (ll i = 0; i < n; ++i) nxtord[--cnt[group[min(i + t, n)]]] = i;

		// nxtord가 큰 i부터 뒤에서 채움
		memset(cnt, 0, sizeof(cnt));
		for (ll i = 0; i < n; ++i) ++cnt[group[i]];
		for (ll i = 1; i <= n || i <= m; ++i) cnt[i] += cnt[i - 1];
		for (ll i = n - 1; i >= 0; --i) sfx[--cnt[group[nxtord[i]]]] = nxtord[i];

		if(pt == n) break;
		pt = 1; newGroup[sfx[0]] = 1;
		for(ll i = 1; i < n; ++i){
			if(group[sfx[i - 1]] != group[sfx[i]] || group[min(sfx[i - 1] + t, n)] != group[min(sfx[i] + t, n)]) ++pt;
			newGroup[sfx[i]] = pt;
		}
		group = vector<ll>(newGroup.begin(), newGroup.end());
		t *= 2;
	}
	return sfx;
}

vector<ll> getLcp(const string& s, const vector<ll>& sfx) {
	const ll n = s.size();
	vector<ll> inv(n), lcp(n);
	for (ll i = 0; i < n; ++i) inv[sfx[i]] = i;
	ll h = 0;
	for(ll i = 0; i < n; ++i){
		if(inv[i]){
			ll prv = sfx[inv[i] - 1];
			while(s[prv + h] == s[i + h]) ++h;
			lcp[inv[i]] = h;
		}
		h = max(h - 1, 0ll);
	}
	return lcp;
}

void solve() {
	string T; cin >> T;
	ll n = T.size();
	vector<ll> sfx = getSuffixArray(T);
	vector<ll> lcp = getLcp(T, sfx);
    stack<pair<ll, ll>> st;
	ll ans = T.size();
    for (ll i = 0; i < T.size(); ++i) {
		ll idx = i;
		while (!st.empty() && st.top().second > lcp[i]) {
			ans = max(ans, st.top().second * (i - st.top().first + 1));
			idx = st.top().first;
			st.pop();
		}
		st.push({idx, lcp[i]});
    }
	while (!st.empty()) {
		ans = max(ans, st.top().second * (n - st.top().first + 1));
		st.pop();
	}
	cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    solve();
}