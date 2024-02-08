#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL N, times[11];

LL solution(LL n) {
	LL ret = 0; LL d = 0;
	while (true) {
		if (n * times[d] > N) break;
		if (n == 0 && N / times[d + 1] == 0) break;
		LL temp = (N - n * times[d]) / times[d + 1];
		if (n != 0) ++temp;
		if (d == 0) ret += temp;
		else if ((N / times[d]) % 10 == n) {
			ret += (N % times[d] + 1);
			ret += (temp - 1) * times[d];
		}
		else ret += temp * times[d];
		++d;
	}
	return ret;
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cin >> N;
	times[0] = 1;
	for (int i = 1; i < 11; ++i) times[i] = times[i - 1] * 10;
	for (LL i = 0; i < 10; ++i) cout << solution(i) << " ";
}

/*
429904664 541008121 540917467 540117067 533117017 473117011 429904664 429904664 429904664 429904664
*/