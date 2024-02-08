#include <bits/stdc++.h>
using namespace std;

int N, arr[100000], tree[262144], M;

void init(int node, int start, int end) {
	if (start == end) tree[node] = arr[start];
	else {
		init(node * 2, start, (start + end) / 2);
		init(node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = min(tree[node * 2], tree[node * 2 + 1]);
	}
}

int query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 1e9 + 1;
	if (left <= start && end <= right) return tree[node];
	int l = query(node * 2, start, (start + end) / 2, left, right);
	int r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return min(l, r);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> N >> M;
	for (int i = 0; i < N; ++i) cin >> arr[i];
	init(1, 0, N - 1);
	int a, b;
	for (int i = 0; i < M; ++i) {
		cin >> a >> b;
		cout << query(1, 0, N - 1, a - 1, b - 1) << '\n';
	}
}