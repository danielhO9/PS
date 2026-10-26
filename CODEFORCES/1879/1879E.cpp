#include <bits/stdc++.h>
using namespace std;
vector<int> children[101];
vector<int> parent(101);
int n;

void oneColor() {
	cout << 1 << '\n';
	for (int i = 0; i < n - 1; ++i) cout << 1 << ' ';
	cout << endl;
	int _; cin >> _ >> _;
	cout << 1 << endl;
	cin >> _; return;
}

void upDfs(int v, vector<int>& c, int t) {
	if (c[v] != -1) return;
	c[v] = t;
	if (v != 1) upDfs(parent[v], c, 3 - t);
}

void downDfs(int v, vector<int>& c, int t) {
	if (c[v] != -1) return;
	c[v] = t;
	for (auto i: children[v]) downDfs(i, c, 3 - t);
}

void threeDfs(int v, vector<int>& c, int t) {
	c[v] = t;
	for (auto i: children[v]) threeDfs(i, c, t + 1 == 4 ? 1 : t + 1);
}

bool checkDfs(int v, vector<int>& c) {
	bool ret = true;
	for (auto i: children[v]) if (c[i] == -1) downDfs(i, c, 3 - c[v]);
	if (v != 1) {
		for (auto i: children[v]) if (c[v] == c[i]) ret = false;
		if (children[v].size() == 1 && c[v] != 1) ret = false;
	}
	for (auto i: children[v]) ret &= checkDfs(i, c);
	return ret;
}

bool twoColors() {
	vector<int> c(n + 1, -1);
	for (int i = 2; i <= n; ++i) if (children[i].size() == 1 && c[i] == -1) {
		upDfs(i, c, 1);
		for (auto j: children[i]) downDfs(j, c, 2);
	}
	if (c[1] == -1) c[1] = 1;
	if (checkDfs(1, c) == false) return false;
	cout << 2 << '\n';
	for (int i = 2; i <= n; ++i) cout << c[i] << ' '; cout << endl;
	int end; vector<int> e(3);
	while (true) {
		cin >> end; if (end) break;
		cin >> e[1] >> e[2];
		if (e[1] == 1) cout << 1 << endl;
		else cout << 2 << endl;
	}
	return true;
}

void solve() {
	cin >> n;
	for (int i = 2; i <= n; ++i) {
		int p; cin >> p;
		parent[i] = p;
		children[p].push_back(i);
	}
	if (children[1].size() == n - 1) { oneColor(); return; }
	if (twoColors()) return;
	vector<int> c(n + 1);
	threeDfs(1, c, 3);
	cout << 3 << '\n';
	for (int i = 2; i <= n; ++i) cout << c[i] << ' '; cout << endl;
	int end; vector<int> e(4);
	while (true) {
		cin >> end; if (end) break;
		cin >> e[1] >> e[2] >> e[3];
		vector<int> notZero; int sumZero = 0;
		for (int i = 1; i <= 3; ++i) if (e[i] != 0) {
			notZero.push_back(i);
			sumZero += i;
		}
		if (notZero.size() == 1) cout << notZero[0] << endl;
		else {
			if (sumZero == 3) cout << 1 << endl;
			else if (sumZero == 4) cout << 3 << endl;
			else cout << 2 << endl;
		}
	}
}

int main() {
	solve();
}