#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int N; cin >> N;
	int people[N]; for (int i = 0; i < N; ++i) cin >> people[i];
	vector<int> S;
	LL ans = 0;
	unordered_map<int, LL> M;
	for (int i = 0; i < N; ++i) {
		if (!S.empty() && S.back() < people[i]) {
			while (!S.empty() && S.back() < people[i]) {
				--M[S.back()];
				S.pop_back();
				++ans;
			}
		}
		if (!S.empty()) ans += M[people[i]];
		if (!S.empty() && S.front() != people[i]) ++ans;
		S.push_back(people[i]);
		++M[people[i]];
	}
	cout << ans;
}