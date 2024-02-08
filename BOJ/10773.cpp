#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> numbers;
    int K; cin >> K;
    int temp;
    for (int i = 0; i < K; ++i) {
        cin >> temp;
        if (temp == 0) numbers.pop_back();
        else numbers.push_back(temp);
    }
    long long sum = 0;
    for (int i: numbers) sum += i;
    cout << sum;

    return 0;
}