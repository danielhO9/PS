#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL ans = LLONG_MAX;
int n = 100001;

void update_lazy(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end) {
    if (lazy[node] != 0) {
        tree[node] += (end - start + 1) * lazy[node];
        if (start != end) {
            lazy[node * 2] += lazy[node];
            lazy[node * 2 + 1] += lazy[node];
        }
        lazy[node] = 0;
    }
}

void update_range(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right, LL diff) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return;
    }
    if (left <= start && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }
    update_range(tree, lazy, node * 2, start, (start + end) / 2, left, right, diff);
    update_range(tree, lazy, node * 2 + 1, (start + end) / 2 + 1, end, left, right, diff);
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

LL query(vector<LL> &tree, vector<LL> &lazy, int node, int start, int end, int left, int right) {
    update_lazy(tree, lazy, node, start, end);
    if (left > end || right < start) {
        return 0;
    }
    if (left <= start && end <= right) {
        return tree[node];
    }
    LL lsum = query(tree, lazy, node * 2, start, (start+end) / 2, left, right);
    LL rsum = query(tree, lazy, node * 2 + 1, (start+end) / 2 + 1, end, left, right);
    return lsum + rsum;
}

LL getVal(vector<LL>& tree, vector<LL>& lazy) {
	int lo = 0, hi = 100000;
    while(hi-lo >= 3){
        int p = (lo*2 + hi)/3, q = (lo + hi*2)/3;
        if(query(tree, lazy, 1, 0, n - 1, 0, p) <= query(tree, lazy, 1, 0, n - 1, 0, q)) hi = q;
        else lo = p;
    }
 
    // 최종 구간 [lo, hi] 안에서 최솟값을 찾아냄
    long long result = LLONG_MAX;
    for(int i = lo; i <= hi; ++i)
        result = min(query(tree, lazy, 1, 0, n - 1, 0, i), result);
	return result;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
	int N, K; cin >> N >> K;
	vector<LL> H(N); for (int i = 0; i < N; ++i) cin >> H[i];
	vector<LL> A(N); for (int i = 0; i < N; ++i) cin >> A[i];
	vector<LL> B(N); for (int i = 0; i < N; ++i) cin >> B[i];

    int h = (int)ceil(log2(n));
    int tree_size = (1 << (h + 1));

    vector<LL> tree(tree_size);
    vector<LL> lazy(tree_size);

	for (int i = 0; i < K; ++i) {
		update_range(tree, lazy, 1, 0, n - 1, 0, 0, B[i] * H[i]);
		update_range(tree, lazy, 1, 0, n - 1, 1, H[i], -B[i]);
		if (H[i] + 1 <= n - 1) update_range(tree, lazy, 1, 0, n - 1, H[i] + 1, n - 1, A[i]);
	}
	// cout << query(tree, lazy, 1, 0, n - 1, 0, 1);
	ans = min(ans, getVal(tree, lazy));
	for (int i = K; i < N; ++i) {
		update_range(tree, lazy, 1, 0, n - 1, 0, 0, B[i] * H[i]);
		update_range(tree, lazy, 1, 0, n - 1, 1, H[i], -B[i]);
		if (H[i] + 1 <= n - 1) update_range(tree, lazy, 1, 0, n - 1, H[i] + 1, n - 1, A[i]);
		int j = i - K;
		update_range(tree, lazy, 1, 0, n - 1, 0, 0, -B[j] * H[j]);
		update_range(tree, lazy, 1, 0, n - 1, 1, H[j], B[j]);
		if (H[j] + 1 <= n - 1) update_range(tree, lazy, 1, 0, n - 1, H[j] + 1, n - 1, -A[j]);
		ans = min(ans, getVal(tree, lazy));
	}
	cout << ans;
}