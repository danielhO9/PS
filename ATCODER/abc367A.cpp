#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve() {
	int A, B, C; cin >> A >> B >> C;
	if (B > C) C += 24;
	if (B > A) A += 24;
	if (B <= A && A <= C) cout << "No";
	else cout << "Yes";
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	solve();
}