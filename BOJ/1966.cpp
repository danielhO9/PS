#include <bits/stdc++.h>
using namespace std;

deque<int> temp;

int solution(int N, int find) {
    int value; int answer = 1;
    while (true) {
        if (temp.front() < *max_element(temp.begin(), temp.end())) {
            value = temp.front(); temp.pop_front(); temp.push_back(value);
            if (find == 0) find = temp.size() - 1;
            else --find;
        } else {
            if (find != 0) {
                --find; temp.pop_front(); answer += 1;
            } else break;
        }
    }
    return answer;
}

int main() {
    int T, print; cin >> T;
    for (int i = 0; i < T;  ++i) {
        int N, answer; cin >> N >> answer;
        temp.clear();
        for (int j = 0; j < N; ++j) {
            cin >> print; temp.push_back(print);
        }
        cout << solution(N, answer) << "\n";
    }

    return 0;
}