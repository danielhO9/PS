#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll N;
vector<pair<ll, ll>> tree_stack;
vector<pair<ll, ll>> histogram, right_his;
vector<ll> children[250001];
vector<ll> parents(250001);
// {histogram[i].second, (-histogram[parents[i]].first) * histogram[i].second}
vector<ll> graph(250001);
vector<ll> dp(250001);
ll lenght = 1;

double meetPoint(ll x, ll y) {
    return (histogram[y].second * (-histogram[parents[y]].first) - histogram[x].second * (-histogram[parents[x]].first)) / static_cast<double>(histogram[x].second - histogram[y].second);
}

void dfs(ll parent, ll child) {
    pair<ll, ll> value_temp; ll lenght_temp = lenght;
    if (lenght == 1) {
        value_temp = {lenght, 0};
        lenght += 1;
        graph[lenght - 1] = child;
    }
    else {
        ll start = 0, end = lenght - 1, mid = (start + end) / 2;
        while (start < end) {
            if (histogram[graph[mid]].second == histogram[child].second) end = mid - 1;
            else if (meetPoint(graph[mid], graph[mid + 1]) < meetPoint(graph[mid], child)) start = mid + 1;
            else end = mid;
            mid = (start + end) / 2;
        }
        value_temp = {mid + 1, graph[mid + 1]};
        lenght = mid + 2;
        graph[lenght - 1] = child;
    }

    ll start = 0, end = lenght - 1, mid = (start + end) / 2;
    while (start < end) {
        if (meetPoint(graph[mid], graph[mid + 1]) <= histogram[child].first) start = mid + 1;
        else end = mid;
        mid = (start + end) / 2;
    }
    dp[child] = histogram[graph[mid]].second * histogram[child].first - histogram[parents[graph[mid]]].first * histogram[graph[mid]].second;

    for (ll element: children[child]) dfs(child, element);

    graph[value_temp.first] = value_temp.second;
    lenght = lenght_temp;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;

    ll x, y;
    vector<ll> answer(N + 1);
    for (ll i = 0; i < N; ++i) {
        cin >> x >> y;
        if (i % 2 == 0) histogram.push_back({x, y});
        else right_his.push_back({x, y});
    }

    // left
    tree_stack.push_back({0, 0});
    for (ll i = 1; i < N / 2; ++i) {
        while (tree_stack.back().second >= histogram[i].second) tree_stack.pop_back();
        children[tree_stack.back().first].push_back(i);
        parents[i] = tree_stack.back().first;
        tree_stack.push_back({i, histogram[i].second});
    }
    for (ll element: children[0]) dfs(0, element);
    for (ll i = 0; i < N / 2; ++i) {
        answer[i] = dp[i];
    }

    tree_stack.clear();
    histogram.clear();
    for (ll i = 0; i < N / 2; ++i) {
        children[i].clear();
        parents[i] = 0;
        graph[i] = 0;
    }
    lenght = 1;
    ll end_value = right_his.back().first;
    for (ll i = N / 2 - 1; i >= 0; --i) {
        histogram.push_back({end_value - right_his[i].first, right_his[i].second});
    }

    tree_stack.push_back({0, 0});
    for (ll i = 1; i < N / 2; ++i) {
        while (tree_stack.back().second >= histogram[i].second) tree_stack.pop_back();
        children[tree_stack.back().first].push_back(i);
        parents[i] = tree_stack.back().first;
        tree_stack.push_back({i, histogram[i].second});
    }
    for (ll element: children[0]) dfs(0, element);

    for (ll i = 0; i < N / 2; ++i) {
        answer[i] += dp[N / 2 - 1 - i];
    }
    cout << *max_element(answer.begin(), answer.end()) << "\n";

    return 0;
}