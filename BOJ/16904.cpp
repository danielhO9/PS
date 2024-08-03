#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct num {
	int x, l, r;
};

int N;
unordered_map<int, int> m;
vector<vector<num>> tree;
int l[500000];
int r[500000];
int x[500000];

template<size_t n>
void rref(vector<bitset<n>>& A) {
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
}

void solve() {
	cin >> N;
	int idx = 0;
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
	
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}	