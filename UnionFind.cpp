#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 100001;
int par[MAX_N];

int find(int x) {
	if (par[x] == x) return x;
	par[x] = find(par[x]);
	return par[x];
}

void union_path(int x, int y) {
	x = find(x); y = find(y);
	par[x] = y;
}

void solve() {
	for (int i = 0; i < MAX_N; ++i) par[i] = i;
}