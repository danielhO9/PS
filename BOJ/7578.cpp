#include <bits/stdc++.h>
using namespace std;

int N, tree[1048576];
unordered_map<int, int> M;
long long ans;

void update(int node, int start, int end, int index) {
	if (index < start || index > end) return;
	if (start == end) {
		tree[node] = 1;
		return;
	}
	update(node * 2, start, (start + end) / 2, index);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int left, int right) {
	if (end < left || right < start) return 0;
	if (left <= start && end <= right) return tree[node];
	int lsum = query(node * 2, start, (start + end) / 2, left, right);
	int rsum = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return lsum + rsum;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; int num;
	for (int i = 0; i < N; ++i) {
		cin >> num;
		M[num] = i;
	}
	for (int i = 0; i < N; ++i) {
		cin >> num;
		ans += query(1, 0, N - 1, M[num], N - 1);
		update(1, 0, N - 1, M[num]);
	}
	cout << ans;
}