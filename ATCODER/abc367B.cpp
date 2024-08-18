#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	string X; cin >> X;
	while (X.back() == '0') X.pop_back();
	if (X.back() == '.') X.pop_back();
	cout << X;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}