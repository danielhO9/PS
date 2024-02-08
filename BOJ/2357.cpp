#include <bits/stdc++.h>
using namespace std;

int N, arr[100000], tree[262144][2], M;

void init(int node, int start, int end, int t) {
	if (start == end) tree[node][t] = arr[start];
	else {
		init(node * 2, start, (start + end) / 2, t);
		init(node * 2 + 1, (start + end) / 2 + 1, end, t);
		if (t == 0) tree[node][t] = min(tree[node * 2][t], tree[node * 2 + 1][t]);
		if (t == 1) tree[node][t] = max(tree[node * 2][t], tree[node * 2 + 1][t]);
	}
}

int query(int node, int start, int end, int left, int right, int t) {
	if (left > end || right < start) {
		if (t == 0) return 1e9 + 1;
		if (t == 1) return 0;
	}
	if (left <= start && end <= right) return tree[node][t];
	int l = query(node * 2, start, (start + end) / 2, left, right, t);
	int r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right, t);
	if (t == 0) return min(l, r);
	else return max(l, r);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> arr[i];
	for (int i = 0; i < 2; ++i) init(1, 0, N - 1, i);
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		cout << query(1, 0, N - 1, a - 1, b - 1, 0) << " " << query(1, 0, N - 1, a - 1, b - 1, 1) << '\n';
	}
}