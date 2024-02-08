#include <bits/stdc++.h>
using namespace std;
int cache[10002];
string nums;

int level(int start, int end) {
    string temp = nums.substr(start, end - start + 1);
    if (temp == string(temp.size(), temp[0])) return 1;
    bool progressive = true;
    for (int i = 0; i < temp.size() - 1; ++i) if (temp[i + 1] - temp[i] != temp[1] - temp[0]) progressive = false;
    if (progressive && abs(temp[1] - temp[0]) == 1) return 2;
    bool alternating = true;
    for (int i = 0; i < temp.size(); ++i) if (temp[i] != temp[i % 2]) alternating = false;
    if (alternating) return 4;
    if (progressive) return 5;
    return 10;
}

int memorize(int begin) {
    if (begin == nums.size()) return 0;
    int& ret = cache[begin];
    if (ret != -1) return ret;
    ret = 987654321;
    for (int L = 3; L <= 5; ++L) if (begin + L <= nums.size()) {
        ret = min(ret, memorize(begin + L) + level(begin, begin + L - 1));
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int C; cin >> C;
    for (int i = 0; i < C; ++i) {
        cin >> nums;
        memset(cache, -1, sizeof(cache));
        cout << memorize(0) << "\n";
    }
    return 0;
}