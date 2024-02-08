#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin >> n;
    vector<int> array;
    int temp;
    for (int i = 0; i < n; ++i) {
        cin >> temp;
        array.push_back(temp);
    }
    sort(array.begin(), array.end());
    int sum = 0;
    for (int i = round(n * 0.15); i < n - round(n * 0.15); ++i) sum += array[i];
    if (n != 0) cout << round(sum / static_cast<double>(n - round(n * 0.15) * 2));
    else cout << 0;
    return 0;
}