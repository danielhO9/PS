#include <bits/stdc++.h>
using namespace std;
vector<int> answer(11, 0);

int solution(int x) {
    if (answer[x] != 0 || x == 0) return answer[x];
    if (x == 1) { answer[x] = 1;}
    else if (x == 2) { answer[x] = 2;}
    else if (x == 3) { answer[x] = 4;}
    else { answer[x] = solution(x - 3) + solution(x - 2) + solution(x - 1);}
    return answer[x];
}

int main() {
    int T; cin >> T;
    int temp;
    for (int i = 0; i < T; ++i) {
        cin >> temp; cout << solution(temp) << "\n";
    }
}