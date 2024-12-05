#include <bits/stdc++.h>
using namespace std;

int N;
int aSorted[1000][1000];
int bPre[1000][1000];
int pt[1000];
int aMatch[1000], bMatch[1000];

void matching(int a) {
	int b;
	while (true) {
		b = aSorted[a][pt[a]++];
		if (bMatch[b] == -1) break;
		if (bPre[b][bMatch[b]] > bPre[b][a]) break;
	}
	int past = bMatch[b];
	bMatch[b] = a;
	aMatch[a] = b;
	if (past != -1) matching(past);
}

void solve() {
	memset(aMatch, -1, sizeof(aMatch));
	memset(bMatch, -1, sizeof(bMatch));
	cin >> N;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cin >> aSorted[i][j];
			--aSorted[i][j];
		}
	}
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			int tmp; cin >> tmp; --tmp;
			bPre[i][tmp] = j;
		}
	}
	for (int i = 0; i < N; ++i) matching(i);
	for (int i = 0; i < N; ++i) {
		cout << aMatch[i] + 1 << '\n';
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}