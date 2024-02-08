#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

struct Line {
    int slope;
    long long y_value;
    double intersection;
};

double meetPoint(tuple<int, long long, double>& line1, const tuple<int, long long>& line2) {
    return (double)(get<1>(line2) - get<1>(line1)) / (get<0>(line1) - get<0>(line2));
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // n 입력
    int n;
    cin >> n;
    // a, b 입력
    int a[n], b[n];
    for(int i=0; i<n; i++) cin >> a[i];
    for(int i=0; i<n; i++) cin >> b[i];

    vector<tuple<int, long long, double>> deque;
    deque.emplace_back(b[0], 0LL, 0.0);
    int index = 0;
    for (int i = 1; i < n; i++) {
        while (index != deque.size() - 1 && get<2>(deque[index + 1]) < a[i]) {
            index++;
        }
        while (get<2>(deque.back()) >= meetPoint(deque.back(), tuple<int, long long> (b[i], (long long) get<0>(deque[index]) * a[i] + get<1>(deque[index])))) {
            if (index == deque.size() - 1) {
                index -= 1;
            }
            deque.pop_back();
        }
        deque.push_back({b[i], (long long) get<0>(deque[index]) * a[i] + get<1>(deque[index]), meetPoint(deque.back(), tuple<int, long long> (b[i], (long long) get<0>(deque[index]) * a[i] + get<1>(deque[index])))});
        if (i == n - 1) cout << (long long) get<0>(deque[index]) * a[i] + get<1> (deque[index]) << "\n";
    }
    if (n == 1) cout << 0 << "\n";
    return 0;
}