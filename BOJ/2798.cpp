#include <bits/stdc++.h>
using namespace std;

int main() {
    int N, M; cin >> N >> M;
    vector<int> card(N);
    for (int i = 0; i < N; ++i) cin >> card[i];
    sort(card.begin(), card.end());
    int answer = 0;
    for (int i = 0; i < N - 2; ++i) {
        for (int j = i + 1; j < N - 1; ++j) {
            for (int k = j + 1; k < N; ++k) {
                if ((card[i] + card[j] + card[k]) <= M && (card[i] + card[j] + card[k]) > answer ) answer = (card[i] + card[j] + card[k]);
                else if ((card[i] + card[j] + card[k]) > M) break;
            }
        }
    }
    cout << answer << endl;
    
    return 0;
}