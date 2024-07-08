#include <bits/stdc++.h>
using namespace std;

int N, M;
vector<pair<int, int>> query;
bool used[200001];

void solve() {
	cin >> N >> M;
	for (int i = 0; i < M; ++i) {
		string t, tmp; cin >> t >> tmp;
		int num; cin >> num;
		used[num] = 1;
		if (t == "A") query.push_back({1, num});
		else query.push_back({0, num});
	}
	vector<int> left;
	for (int i = 1; i <= 2 * N; ++i) {
		if (!used[i]) left.push_back(i);
	}
	if (!used[1]) {
		cout << "NO";
		return;
	}
	int nums[M]; memset(nums, 0, sizeof(nums));
	priority_queue<pair<int, int>> todo;
	for (int i = 0; i < M - 1; ++i) {
		if (query[i].first == query[i + 1].first) todo.push({query[i].second, i});
	}
	if (todo.size() % 2 != (2 * N - M) % 2) todo.push({query[M - 1].second, M - 1});
	while (!todo.empty()) {
		int block = todo.top().first, idx = todo.top().second; todo.pop();
		if (left.empty() || left.back() < block) {
			cout << "NO";
			return;
		}
		nums[idx] = left.back();
		left.pop_back();
	}
	cout << "YES\n";
	char now = 'A';
	for (int i = 0; i < M; ++i) {
		cout << now << " BLOCK " << query[i].second << '\n';
		now = 'A' + 'B' - now;
		if (query[i].second == 1) {
			for (auto j: left) {
				cout << now << " CHAIN " << j << '\n';
				now = 'A' + 'B' - now;
			}
		}
		if (nums[i] != 0) {
			cout << now << " CHAIN " << nums[i] << '\n';
			now = 'A' + 'B' - now;
		}
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}