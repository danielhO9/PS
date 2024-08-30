#include <bits/stdc++.h>
using namespace std;

int p;
int dig[1000];
deque<int> idx[10];
int start[10];
int acnt[10];
int ccnt[10];
int aMatch[10];
int cMatch[10];
int ansa = 10, ansb = 10, ansc = 10, ansn = -1, ansm = -1, anss = 1000;

bool check(int a, int b, int c, int n, int m) {
	for (int i = 0; i < p - n - m; ++i) {
		if (dig[i] == a && dig[i + n + m] == c && dig[i + n] != b) return false; 
	}
	return true;
}

void solve() {
	cin >> p;
	int lim = ceil(p / 40.0) + 1;
	for (int i = 0; i < p; ++i) cin >> dig[i];
	for (int i = 0; i < p; ++i) idx[dig[i]].push_back(i);
	for (int i = 0; i < 10; ++i) start[i] = INT32_MAX;

	for (int n = 1; n < p; ++n) for (int m = 1; m < p - n; ++m) {
		for (int b = 0; b < 10; ++b) {
			memset(aMatch, -1, sizeof(aMatch));
			memset(cMatch, -1, sizeof(cMatch));
			memset(acnt, 0, sizeof(acnt));
			memset(ccnt, 0, sizeof(ccnt));

			while (!idx[b].empty() && idx[b].front() - n < 0) idx[b].pop_front();
			for (auto i: idx[b]) {
				if (i + m >= p) break;
				int a = dig[i - n], c = dig[i + m];

				if (aMatch[a] == -1 && cMatch[c] == -1) {
					aMatch[a] = c;
					cMatch[c] = a;
					start[a] = min(start[a], i - n);
					++acnt[a];
					++ccnt[c];
				} else if (aMatch[a] == c && cMatch[c] == a) {
					++acnt[a]; ++ccnt[c];
				} else {
					if (aMatch[a] != c) {
						acnt[a] = INT32_MIN;
					}
					if (cMatch[c] != a) {
						ccnt[c] = INT32_MIN;
					}
				}

			}
			for (int a = 0; a < 10; ++a) {
				int c = aMatch[a];
				if (c != -1 && acnt[a] >= lim && ccnt[c] >= lim && check(a, b, c, n, m)) {
					if ((anss > start[a]) || (anss == start[a] && ansn > n) || (anss == start[a] && ansn == n && ansm > m)) {
						ansa = a, ansb = b, ansc = c, ansm = m, ansn = n, anss = start[a];
					}
				}
				start[a] = INT32_MAX;
			}

		}
	}
	// cout << anss << '\n';
	if (ansa != 10) cout << "triple correlation " << ansa << '(' << ansn << ')' << ansb << '(' << ansm << ')' << ansc << " found";
	else cout << "random sequence";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}