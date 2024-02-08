#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    vector<long long> zero, one;
    zero = {1, 0}; one = {0, 1};
    for (int i = 0; i < 39; ++i) {
        zero.push_back(zero[zero.size() - 2] + zero[zero.size() - 1]);
        one.push_back(one[one.size() - 2] + one[one.size() - 1]);
    }
    int T; cin >> T; int temp;
    for (int i = 0; i < T; ++i) {
        cin >> temp;
        cout << zero[temp] << " " << one[temp] << "\n";
    }

    return 0;
}
// 1 0
// 0 1
// 1 1
// 1 2
// 2 3
// 3 5
// 5 8
