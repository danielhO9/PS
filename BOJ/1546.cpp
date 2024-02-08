#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    int sum = 0;
    vector<int> score(n);
    for (int i = 0; i < n; ++i) {
        cin >> score[i];
        sum += score[i];
    }
    cout << sum * 100 / static_cast<double>(n * *max_element(score.begin(), score.end()));
}