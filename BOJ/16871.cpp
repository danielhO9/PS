#include <bits/stdc++.h>
using namespace std;

int p;
int dig[1000];
vector<int> idx[10];

void solve() {
	cin >> p;
	for (int i = 0; i < p; ++i) cin >> dig[i];
	for (int i = 0; i < p; ++i) idx[dig[i]].push_back(i);
	for (int n = 1; n < p; ++n) for (int m = 1; m < p; ++m) {
		for (int b = 0; b = 10; ++b) {
			
		}
	}

}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}