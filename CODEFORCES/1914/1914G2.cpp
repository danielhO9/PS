#include<bits/stdc++.h>
using namespace std;
typedef long long LL;

const int MOD = 998244353;

int add(int x, int y) {
	return (((x + y) % MOD) + MOD) % MOD;
}
 
int mul(int x, int y) {
	return (x * 1ll * y) % MOD;
}
 
mt19937_64 rnd(1);
 
LL gen() {
	LL x = 0;
	while(x == 0) x = rnd();
	return x;
}
 
vector<int> c;
vector<int> g;
 
int process_block(int l, int r) {
	int ans = 0;
	while (l < r) {
		if(g[l] != -1) l = g[l];
		else {
			++ans; ++l;
		}
	}
	return ans;
}
 
void solve() {
	int n; cin >> n;
	int size = 0, cnt = 1;
	c.resize(n * 2);
	g.resize(n * 2, -1);
	for(int i = 0; i < 2 * n; ++i) {
		cin >> c[i];
		--c[i];
	}
	vector<LL> val(n);
	for(int i = 0; i < n; i++) val[i] = gen();
	
	map<LL, int> last;
	LL cur = 0;
	last[0] = 0;
	for(int i = 0; i < n * 2; i++) {
		cur ^= val[c[i]];
		if (cur == 0) {
			++size;
			cnt = mul(cnt, process_block(last[0], i + 1));
			last.clear();
		}
		else if (last.count(cur)) g[last[cur]] = i + 1;
		last[cur] = i + 1;
	}
	cout << size << ' ' << cnt << '\n';
	c.clear();
	g.clear();
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) solve();
}