#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int n, m, cache[501][501], choice[501][501];
LL A[501], B[501];
unordered_map <int, vector<int>> M;

int matchCache(int indexA, int indexB) {
    int& ret = cache[indexA][indexB];
    if (ret != -1) return ret;
    ret = 1;
	int& choose = choice[indexA][indexB];
    for (int i = indexA + 1; i <= n; ++i) if (A[i] > A[indexA]) for (auto j: M[A[i]]) {
		if (j > indexB) {
			if (ret < matchCache(i, j) + 1) {
				ret = matchCache(i, j) + 1;
				choose = 501 * i + j;
			}
			break;
		}
	}
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
	A[0] = LLONG_MIN; B[0] = LLONG_MIN;
    cin >> n; for (int i = 1; i <= n; ++i) cin >> A[i];
	cin >> m; for (int i = 1; i <= m; ++i) {
		cin >> B[i];
		M[B[i]].push_back(i);
	}
	memset(cache, -1, sizeof(cache));
	cout << matchCache(0, 0) - 1 << "\n";
	int a = 0, b = 0, c;
	while (choice[a][b] != 0) {
		cout << A[choice[a][b] / 501] << " ";
		c = choice[a][b];
		a = c / 501; b = c % 501;
	}
}