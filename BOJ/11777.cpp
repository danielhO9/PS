#include <bits/stdc++.h>
using namespace std;

int N;
int P[100][100];
int rk[100][100];
bool elim[100][100];
int pt[100], from[100], to[100];

// index
int f[100], s[100], l[100];

int fcor[100];
bool vis[100];

bool matching(int x) {
	int y;
	while (true) {
		if (pt[x] == N)
			return false;
		y = P[x][pt[x]++];
		if (from[y] == -1 || rk[y][from[y]] > rk[y][x])
			break;
	}
	int px = from[y];
	to[x] = y;
	from[y] = x;
	if (px != -1)
		return matching(px);
	return true;
}

void eliminate(int q, int x) {
	elim[q][x] = true;
	if (f[q] == x) {
		f[q] = -1;
		for (int i = x + 1; i < N - 1; ++i) {
			if (!elim[q][i]) {
				f[q] = i;
				fcor[P[q][i]] = q;
				break;
			}
		}
	}
	if (l[q] == x) {
		for (int i = x - 1; i >= 0; --i) {
			if (!elim[q][i]) {
				l[q] = i;
				break;
			}
		}
	}
	if (s[q] == x || f[q] >= s[q] || s[q] > l[q]) {
		int start;
		if (s[q] == x) start = x + 1;
		else start = f[q] + 1;
		s[q] = -1;
		for (int i = start; i < N - 1; ++i) {
			if (!elim[q][i]) {
				s[q] = i;
				break;
			}
		}
	}
}

bool rotation(int y) {
	int x = fcor[y];
	if (f[x] == -1) return false;
	if (f[x] == l[x]) return true;
	deque< pair<int, int> > r;
	vector<int> visited;
	r.push_back(make_pair(x, y));
	vis[x] = true;
	visited.push_back(x);
	int tri;
	while (true) {
		int ny = P[r.back().first][s[r.back().first]];
		int nx = fcor[ny];
		if (vis[nx]) {
			tri = nx;
			break;
		}
		r.push_back(make_pair(nx, ny));
		vis[nx] = true;
		visited.push_back(nx);
	}
	// for (auto j: r) cout << j.first << ' ' << j.second << '\n';
	while (r.front().first != tri) r.pop_front();
	// cout << r.size() << ' ';
	// cout << "rotation\n";
	// for (auto j: r) cout << j.first << ' ' << j.second << '\n';
	for (auto j: visited) vis[j] = false;
	for (int j = 0; j < r.size(); ++j) {
		int p = r[j].first, q = r[(j + 1) % r.size()].second;
		int idx = rk[q][p];
		for (int j = idx + 1; j < N - 1; ++j) {
			eliminate(q, j);
			int num = P[q][j];
			eliminate(num, rk[num][q]);
		}
	}
	return rotation(r.back().second);
}

void solve() {
	memset(from, -1, sizeof(from));
	memset(to, -1, sizeof(to));
	memset(pt, 0, sizeof(pt));
	memset(f, -1, sizeof(f));
	memset(s, -1, sizeof(s));
	memset(l, -1, sizeof(l));
	memset(elim, 0, sizeof(elim));

	cin >> N;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N - 1; ++j) {
			cin >> P[i][j];
			--P[i][j];
			rk[i][P[i][j]] = j;
		}
	for (int i = 0; i < N; ++i) {
		if (!matching(i)) {
			cout << "NO SOLUTION\n";
			return;
		}
	}
	for (int i = 0; i < N; ++i) {
		int p = i, q = to[i];
		int idx = rk[q][p];
		for (int j = idx + 1; j < N - 1; ++j) {
			elim[q][j] = true;
			int num = P[q][j];
			elim[num][rk[num][q]] = true;
		}
	}
	// for (int i = 0; i < N; ++i) {
	// 	for (int j = 0; j < N - 1; ++j) cout << elim[i][j] << ' ';
	// 	cout << '\n';
	// }
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N - 1; ++j)
			if (!elim[i][j]) {
				if (f[i] == -1)
					f[i] = j;
				else if (s[i] == -1)
					s[i] = j;
				l[i] = j;
			}
	}
	for (int i = 0; i < N; ++i) {
		if (f[i] == -1) {
			cout << "NO SOLUTION\n";
			return;
		} else fcor[P[i][f[i]]] = i;
	}

	for (int i = 0; i < N; ++i) {
		if (!rotation(P[i][f[i]])) {
			cout << "NO SOLUTION\n";
			return;
		}
		// cout << "elim\n";
		// for (int i = 0; i < N; ++i) {
		// 	for (int j = 0; j < N - 1; ++j) cout << elim[i][j] << ' ';
		// 	cout << '\n';
		// }
		// for (int i = 0; i < N; ++i) {
		// 	cout << i << ' ' << f[i] << ' ' << s[i] << ' ' << l[i] << '\n';
		// }
		// cout << "fcor\n";
		// for (int i = 0; i < N; ++i) {
		// 	cout << fcor[i] << '\n';
		// }
	}
	for (int i = 0; i < N; ++i) {
		if (P[i][f[i]] > i) {
			cout << i + 1 << ":" << P[i][f[i]] + 1 << ' ';
		}
	}
	cout << '\n';
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--) solve();
}