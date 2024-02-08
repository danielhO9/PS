#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int N, MOD = 1000000007;
pair<int, int> A[1000000];
pair<int, int> arr[1000000], tree[2097152];

void update(int node, int start, int end, int index, int val1, int val2) {
	if (index < start || index > end) return;
	if (start == end) {
		arr[index] = make_pair(val1, val2);
		tree[node] = make_pair(val1, val2);
		return;
	}
	update(node * 2, start, (start + end) / 2, index, val1, val2);
	update(node * 2 + 1, (start + end) / 2 + 1, end, index, val1, val2);

	tree[node].first = max(tree[node * 2].first, tree[node * 2 + 1].first);
	if (tree[node * 2].first == tree[node * 2 + 1].first) tree[node].second = tree[node * 2].second + tree[node * 2 + 1].second;
	else if (tree[node * 2].first > tree[node * 2 + 1].first) tree[node].second = tree[node * 2].second;
	else tree[node].second = tree[node * 2 + 1].second;
	tree[node].second %= MOD;
}

pair<int, int> query(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return {-1, 0};
	if (left <= start && end <= right) return tree[node];
	pair<int, int> l = query(node * 2, start, (start + end) / 2, left, right);
	pair<int, int> r = query(node * 2 + 1, (start + end) / 2 + 1, end, left, right);
	if (l.first == r.first) return make_pair(l.first, (l.second + r.second) % MOD);
	else if (l.first > r.first) return l;
	else return r;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	for (int i = 0; i < N; ++i) {
		cin >> A[i].first;
		A[i].second = i;
	}
	sort(A, A + N, [](const pair<int, int> &a, const pair<int, int> &b) {
		if (a.first == b.first) return a.second > b.second;
		return a.first < b.first;
	});
	pair<int, int> temp;
	for (int i = 0; i < N; ++i) {
		temp = query(1, 0, N - 1, 0, A[i].second);
		if (temp.first == 0) temp.second = 1;
		update(1, 0, N - 1, A[i].second, temp.first + 1, temp.second);
		for (int i = 0; i < 2 * N; ++i) cout << tree[i].second << " ";
		cout << '\n';
	}
	temp = query(1, 0, N - 1, 0, N - 1);
	cout << temp.first << " " << temp.second;
}