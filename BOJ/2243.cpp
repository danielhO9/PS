#include <bits/stdc++.h>
using namespace std;

const int N = 1000000;
int n, arr[1000000], tree[2097152];

void update(int node, int start, int end, int index, int val) {
	if (index < start || index > end) return;
	if (start == end) {
		arr[index] += val;
		tree[node] = arr[index];
		return;
	}
	update(node * 2, start, (start + end) / 2, index, val);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index, val);
	tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

int query(int node, int start, int end, int rate) {
	if (start == end) {
		int ret = start;
		update(1, 0, N - 1, start, -1);
		return ret;
	}
	if (tree[node * 2] <= rate) return query(node * 2 + 1, (start + end) / 2 + 1, end, rate - tree[node * 2]);
	else return query(node * 2, start, (start + end) / 2, rate);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> n;
	int a, b, c;
	for (int i = 0; i < n; ++i) {
		cin >> a;
		if (a == 1) {
			cin >> b;
			cout << query(1, 0, N - 1, b - 1) + 1 << '\n';
		} else {
			cin >> b >> c;
			update(1, 0, N - 1, b - 1, c);
		}
	}
}