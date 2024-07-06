#include <bits/stdc++.h>
using namespace std;
string S;

bool check(string T) {
	// cout << T << ' ' << S.size() << ' ' << T.size() << '\n';
	if (S.size() == T.size()) return S == T;
	bool ret = false;
	if (T.back() == 'A') {
		T.pop_back();
		ret |= check(T);
		if (ret) return ret;
		T.push_back('A');
	}
	if (T.front() == 'B') {
		reverse(T.begin(), T.end());
		T.pop_back();
		ret |= check(T);
		if (ret) return ret;
		T.push_back('B');
		reverse(T.begin(), T.end());
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	string T; cin >> S >> T;
	cout << check(T);
}