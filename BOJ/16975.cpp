#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL sum(vector<LL> &tree, int i) {
    LL ans = 0;
    while (i > 0) {
        ans += tree[i];
        i -= (i & -i);
    }
    return ans;
}
void update(vector<LL> &tree, int i, LL diff) {
    while (i < tree.size()) {
        tree[i] += diff;
        i += (i & -i);
    }
}
int main() {
	ios::sync_with_stdio(0); cin.tie(0);
    int N; cin >> N;
    vector<LL> a(N + 1), b(N + 1); a[0] = 0;
    vector<LL> tree(N + 1);
	for (int i = 1; i <= N; ++i) {
		cin >> a[i];
		b[i] = a[i] - a[i - 1];
		update(tree, i, b[i]);
	}
	int M; cin >> M;
	while (M--) {
		int t; cin >> t;
		if (t == 1) {
			int i, j, k; cin >> i >> j >> k;
			b[i] += k;
			update(tree, i, k);
			if (j < N) {
				b[j + 1] -= k;
				update(tree, j + 1, -k);
			}
		} else {
			int x; cin >> x;
			cout << sum(tree, x) << '\n';
		}
	}
    return 0;
}