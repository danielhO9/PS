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
	// 1 ~ MAX_N
	int MAX_N;
    vector<ll> a(MAX_N + 1);
    vector<ll> tree(MAX_N + 1);
    // for (int i = 1; i <= MAX_N; i++) update(tree, i, a[i]);
	// sum(tree, i)
}