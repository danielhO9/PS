#include <bits/stdc++.h>
using namespace std;
int person[1000] = {0};

int main() {
    int N; cin >> N;
    for (int i = 0; i < N; ++i) cin >> person[i];
    sort(person, person + N);
    int answer = 0;
    for (int i = 0; i < N; ++i) {
        if (i != 0) person[i] = person[i] + person[i - 1];
        answer += person[i];
    }
    cout << answer;
    return 0;
}