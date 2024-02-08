#include <bits/stdc++.h>
using namespace std;
int main() {
    int L; cin >> L;
    string str; cin >> str;
    vector<long long> array; array.push_back(1);
    // 97 ... 122
    for (int i = 1; i < 50; ++i) array.push_back((array.back() * 31) % 1234567891);
    long long answer = 0;
    for (int i = 0; i < L; ++i) {
        answer += (int(str[i]) - 96) * array[i];
        answer %= 1234567891;
    }
    cout << answer;
}