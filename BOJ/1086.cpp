#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
LL N, K, cache[100][32768], mod[15], etime[750];
string temp[15];

void getEtime() {
    etime[0] = 1 % K;
    for (int i = 1; i < 750; ++i) etime[i] = ((etime[i - 1] * 10) % K);
}

void getMod(int idx) {
    for (int i = 0; i < temp[idx].size(); ++i) {
        mod[idx] += (stoi(temp[idx].substr(i, 1)) * etime[temp[idx].size() - 1 - i] % K);
        mod[idx] %= K;
    }
}

LL matchCache(int left, int visited) {
    if (visited == 0 && left == 0) return 1;
    if (visited == 0 && left != 0) return 0;
    LL& ret = cache[left][visited];
    if (ret != -1) return ret;
    int len = 0;
    for (int i = 0; i < 15; ++i) if (visited == (visited | (1 << i))) len += temp[i].size();
    ret = 0;
    for (int i = 0; i < 15; ++i) if (visited == (visited | (1 << i))) ret += matchCache((left + K - (mod[i] * etime[len - temp[i].size()] % K)) % K, visited ^ (1 << i));
    return ret;
}

LL gcd(LL x, LL y) {
    if (x > y) return gcd(y, x);
    if (x == 0) return y;
    return gcd(x, y % x);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> temp[i];
    cin >> K;
    getEtime(); for (int i = 0; i < N; ++i) getMod(i);
    memset(cache, -1, sizeof(cache));
    LL part = matchCache(0, (1 << N) - 1);
    LL total = 1; for (int i = 1; i <= N; ++i) total *= i;
    if (part == 0) cout << "0/1";
    else {
        LL m = gcd(part, total);
        cout << part / m << "/" << total / m;
    }
    return 0;
}