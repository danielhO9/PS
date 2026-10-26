#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (int i = 0; i < n; ++i)
		cin >> a[i];
	vector<int> o, e;
	for (int i = 0; i < n; ++i) {
		if (a[i] <= 2 && i % 2 == 0)
			e.push_back(i);
		if (a[i] <= 2 && i % 2 == 1)
			o.push_back(i);
	}
	deque< pair<int, int> > todo;
	int i = 0, j = 0;
	while (i < o.size() && j < e.size()) {
		int l = min(o[i], e[j]), r = max(o[i], e[j]);
		if (l == o[i]) {
			while (i + 1 < o.size() && o[i + 1] < e[j])
				++i;
		}
		if (l == e[j]) {
			while (j + 1 < e.size() && e[j + 1] < o[i])
				++j;
		}
		bool flag = true;
		for (int k = l; k <= r; ++k)
			if (a[k] > 4)
				flag = false;
		if (flag) {
			todo.push_back( make_pair(l, r) );
		}
		if (l == o[i]) {
			++i;
		}
		if (l == e[j]) {
			++j;
		}
	}
	sort(todo.begin(), todo.end());
	// for (auto i: todo) cout << i.first << ' ' << i.second << '\n';
	vector<int> ans(n);
	for (int i = 0; i < n; ++i)
		ans[i] = i + 1;
	if (a[0] == 0)
		ans[0] = 0;
	while (!todo.empty() && todo.front().first == 0) {
		int l = todo.front().second - todo.front().first;
		l = (l + 1) / 2;
		l += l - 1;
		ans[todo.front().second] = min(ans[todo.front().second], l);
		todo.pop_front();
	}
	// for (auto i: todo) cout << i.first << ' ' << i.second << '\n';
	for (int i = 1; i < n; ++i) {
		if (a[i] == 0)
			ans[i] = min(ans[i], ans[i - 1]);
		else
			ans[i] = min(ans[i], ans[i - 1] + 1);
		if (i + 1 < n && a[i] <= 2 && a[i + 1] <= 2)
			ans[i + 1] = min(ans[i - 1] + 1, ans[i + 1]);
		while (!todo.empty() && todo.front().first == i) {
			int l = todo.front().second - todo.front().first;
			l = (l + 1) / 2;
			l += l - 1;
			ans[todo.front().second] =
				min(ans[todo.front().second], l + ans[i - 1]);
			todo.pop_front();
		}
		// cout << ans[i] << '\n';
	}
	cout << ans[n - 1] << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
}