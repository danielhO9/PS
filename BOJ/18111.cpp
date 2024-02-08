#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int N, M, B; cin >> N >> M >> B; int sum = 0;
    vector<int> ground; int temp;
    for (int i = 0; i < N * M; ++i) {
        cin >> temp; sum += temp;
        ground.push_back(temp);
    }
    int max_height = *max_element(ground.begin(), ground.end());
    int min_height = *min_element(ground.begin(), ground.end());
    pair<int, int> answer = {200000000, 0};
    int time;
    int goal;
    for (goal = min_height; goal <= max_height; ++goal) {
        if ((sum + B) < N * M * goal) break;
        time = 0;
        for (int height: ground) {
            if (height > goal) time += 2 * (height - goal);
            else if (height < goal) time += goal - height;
        }
        if (answer.first >= time) answer = {time, goal};
    }
    cout << answer.first << " " << answer.second;

    return 0;
}