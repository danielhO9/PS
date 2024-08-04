#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int N;
int idx = 0;
unordered_map<int, int> m;
vector<vector<int>> tree;

int l[500000];
int r[500000];
int x[500000];

void rref(vector<int>& a) {
	const int n = 31;
	vector<bitset<n>> A;
	for (auto i: a) A.push_back(bitset<n>(i));
    int m = (int)A.size();
    for (int j = n - 1, r = 0; j >= 0 && r < m; --j) {
        for (int i = r; i < m; i++) {
            if (A[i][j]) {
                swap(A[r], A[i]);
                break;
            }
        }
        if (A[r][j]) {
            for (int i = 0; i < m; i++) if (i != r) {
                if (A[i][j]) {
                    A[i] ^= A[r];
                }
            }
            ++r;
        }
    }
	a.clear();
	for (auto i: A) {
		int tmp = i.to_ulong();
		if (tmp == 0) break;
		a.push_back(tmp);
	}
}

void update(int node, int start, int end, int idx) {
    if (l[idx] > end || r[idx] < start) return;
    if (l[idx] <= start && end <= r[idx]) {
        tree[node].push_back(x[idx]);
        return;
    }
	int mid = (start + end) / 2;
    update(node * 2, start, mid, idx);
    update(node * 2 + 1, mid + 1, end, idx);
}

void dnq(int node, int start, int end) {
	rref(tree[node]);
	if (start == end) {
		int ans = 0;
		for (auto i: tree[node]) ans ^= i;
		cout << ans << '\n';
	} else {
		for (auto i: tree[node]) {
			tree[node * 2].push_back(i);
			tree[node * 2 + 1].push_back(i);
		}
		int mid = (start + end) / 2;
		dnq(node * 2, start, mid);
		dnq(node * 2 + 1, mid + 1, end);
	}
}

void solve() {
	cin >> N;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		if (s[0] == '-') {
			int tmp = stoi(s.substr(1, (int)s.size() - 1));
			r[m[tmp]] = i - 1;
		} else {
			int tmp = stoi(s);
			m[tmp] = idx;
			x[idx] = tmp;
			l[idx] = i;
			r[idx] = N - 1;
			++idx;
		}
	}
	int h = (int)ceil(log2(N));
	int tree_size = (1 << (h + 1));
	tree = vector<vector<int>> (tree_size);
	for (int i = 0; i < idx; ++i) {
		update(1, 0, N - 1, i);
	}
	dnq(1, 0, N - 1);
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}	