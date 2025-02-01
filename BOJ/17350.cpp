#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	bool ans = false;
	for (int i = 0; i < N; ++i) {
		string s; cin >> s;
		if (s == "anj") ans = true;
	}
	if (ans) cout << "뭐야;";
	else cout << "뭐야?";
}