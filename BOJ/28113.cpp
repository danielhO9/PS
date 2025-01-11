#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N, A, B; cin >> N >> A >> B;
	int sub = N <= B ? B : INT32_MAX;
	if (sub > A) cout << "Bus";
	else if (sub < A) cout << "Subway";
	else cout << "Anything";
}