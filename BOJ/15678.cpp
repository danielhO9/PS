#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, D;
LL arr[200000], tree[524288];

void init(int node, int start, int end) {
	if (start == end) tree[node] = arr[start];
	else {
		init(node * 2, start, (start + end) / 2);
		init(node * 2 + 1, (start + end) / 2 + 1, end);
		tree[node] = tree[node * 2] + tree[node * 2 + 1];
	}
}

void update(int node, int start, int end, int index, LL val) {
	if (index < start || index > end) return;
	if (start == end) {
		arr[index] = val;
		tree[node] = val;
		return;
	}
	update(node * 2, start, (start + end) / 2, index, val);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = max(tree[node * 2], tree[node * 2 + 1]);
}

LL query(int node, int start, int end, int left, int right) {
	if (end < left || right < start) return LLONG_MIN;
	if (left <= start && end <= right) return tree[node];
	LL l = query(node * 2, start, (start + end) / 2, left, right);
	LL r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	return max(l, r);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N >> D; LL temp;
	for (int i = 0; i < N; ++i) {
		cin >> temp;
		if (i == 0) update(1, 0, N - 1, i, temp);
		else {
			LL a = query(1, 0, N - 1, max(0, i - D), i - 1);
			update(1, 0, N - 1, i, max(temp, temp + a));
		}
	}
	cout << *max_element(arr, arr + N);
}