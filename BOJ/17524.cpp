#include <bits/stdc++.h>
using namespace std;
/*
옷은 61개를 생각하면 된다. 가장 낮은 온도가 건조기 중 하나가 된다.
어떤 건조기에 시간이 x만큼 걸리는 옷이 들어왔다면 x보다 적게 걸리는 옷은 다 넣어버린다.
즉, 걸리는 시간대로 있을 때 중간에서 빼는 건 의미가 없다.
NlogN + N * NlogN * N
정렬하고 위에서부터 빼낸다.

각 건조기의 온도를 정하고, 옷을 탐색하며 가장 적은 시간이 걸리는 방향으로 할 수 있다.
문제점 -> 해당 옷에 대하여 가장 적은 시간이 걸리는 건조기로 해당 옷을 넣자. 그 건조기에서 이 옷이 가장 오래 걸린다.
하지만 다른 건조기로 갔더라면 다른 옷이 더 오래 걸려 값이 증가하지 않는 경우가 생길 수 있다.


*/
int n, k;
vector<int> clothes(61, -1);

int k1(vector<int>& left) {
    if (left.empty()) return 0;
    int temp = *min_element(left.begin(), left.end());
    int ret = 30;
    for (int t: left) ret = max(30 + (t - temp) * clothes[t], ret);
    return ret;
}

int k2(vector<int>& left) {
    if (left.empty()) return 0;
    vector<pair<int, int>> dryer;
    int temp = *min_element(left.begin(), left.end());
    for (int t: left) dryer.push_back({30 + (t - temp) * clothes[t], t});
    sort(dryer.begin(), dryer.end());
    vector<int> send;
    int ret = 14000;
    while (!dryer.empty()) {
        ret = min(ret, dryer.back().first + k1(send));
        send.push_back(dryer.back().second);
        dryer.pop_back();
    }
    return ret;
}

int k3(vector<int>& left) {
    vector<pair<int, int>> dryer;
    int temp = *min_element(left.begin(), left.end());
    for (int t: left) dryer.push_back({30 + (t - temp) * clothes[t], t});
    sort(dryer.begin(), dryer.end());
    vector<int> send;
    int ret = 21000;
    while (!dryer.empty()) {
        ret = min(ret, dryer.back().first + k2(send));
        send.push_back(dryer.back().second);
        dryer.pop_back();
    }
    return ret;
}

int main() {
    cin >> n >> k;
    int t,w;
    for (int i = 0; i < n; ++i) {
        cin >> t >> w;
        clothes[t - 40] = max(clothes[t - 40], w);
    }
    vector<int> todo;
    for (int i = 0; i < 61; ++i) if (clothes[i] != -1) todo.push_back(i);
    if (k == 1) cout << k1(todo);
    else if (k == 2) cout << k2(todo);
    else cout << k3(todo);
    return 0;
}