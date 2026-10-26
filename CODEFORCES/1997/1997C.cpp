#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
string s;

void solve() {
	cin >> n;
	cin >> s;
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') ++cnt;
		else if (s[i] == ')') --cnt;
		else {
			if (cnt > 0) {
				s[i] = ')';
				--cnt;
			} else {
				s[i] = '(';
				++cnt;
			}
		}
	}
	stack<ll> st;
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == '(') {
			st.push(i);
		} else {
			ans += i - st.top();
			st.pop();
		}
	}
	cout << ans << '\n';
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}