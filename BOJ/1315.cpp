#include <bits/stdc++.h>
using namespace std;
int N, STR[50], INT[50], PNT[50], cache[1000][1000];

int matchCache(int str, int inte) {
    if (str >= 1000 || inte >= 1000) return N;
    int& ret = cache[str][inte];
    if (ret != -1) return ret;
    int temp = 0; ret = 0;
    for (int i = 0; i < N; ++i) if (STR[i] <= str || INT[i] <= inte) { ret += 1; temp += PNT[i]; }
    temp -= (str - 1); temp -= (inte - 1);
    for (int i = 0; i <= temp; ++i) ret = max(ret, matchCache(str + i, inte + temp - i));
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> N;
    for (int i = 0; i < N; ++i) cin >> STR[i] >> INT[i] >> PNT[i];
    memset(cache, -1, sizeof(cache));
    cout << matchCache(1, 1);
    return 0;
}