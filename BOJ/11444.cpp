#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N;
map<LL, LL> dic;

LL solution(LL n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	LL& ret = dic[n];
	if (ret != 0) return ret;
	if (n % 2 == 0) ret = solution(n / 2) * solution(n / 2) + 2 * solution(n / 2) * solution(n / 2 - 1);
	else ret = solution(n / 2) * solution(n / 2) + solution((n / 2) + 1) * solution((n / 2) + 1);
	ret %= 1000000007;
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N; cout << solution(N);
}