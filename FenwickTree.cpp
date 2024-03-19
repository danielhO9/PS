#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll sum(vector<ll> &tree, int i) {
    ll ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<ll> &tree, int i, ll diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}

void solve() {
	int n;
	// 1 ~ n
    vector<ll> a(n + 1);
    vector<ll> tree(n + 1);
    // for (int i = 1; i <= n; i++) update(tree, i, a[i]);
	// sum(tree, i)
}