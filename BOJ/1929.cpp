#include <bits/stdc++.h>
using namespace std;

int main() {
    bool array[1000001]; array[0] = true; array[1] = true;
    int M, N; cin >> M >> N;
    for (int i = 2; i <= 1000000; ++i) {
        if (i > N) break;
        if (array[i] == false) {
            for (int j = 1; j <= 1000000 / i; ++j) array[i * j] = true;
            if (i >= M) cout << i << "\n";
        } else {
            continue;
        }
    }
    

    return 0;
}