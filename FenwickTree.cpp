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
    int n, m, k;
    vector<LL> a(n + 1);
    vector<LL> tree(n + 1);
    // for (int i = 1; i <= n; i++) {
    //     scanf("%lld",&a[i]);
    //     update(tree, i, a[i]);
    // }
    // printf("%lld\n",sum(tree, t3) - sum(tree, t2-1));
    return 0;
}