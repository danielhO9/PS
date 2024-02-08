#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll n;
vector<pair<ll, ll>> tree_stack;
vector<ll> a(200001);
vector<ll> children[200001];
vector<ll> parents(200001);
// {a[i], (-parent) * a[i]}
vector<ll> graph(200001);
vector<ll> answer(200001);
ll lenght = 1;

double meetPoint(ll x, ll y) { return (a[y] * (-parents[y]) - a[x] * (-parents[x])) / static_cast<double>(a[x] - a[y]); }

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
            if (a[graph[mid]] == a[child]) end = mid - 1;
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
        if (meetPoint(graph[mid], graph[mid + 1]) <= child) start = mid + 1;
        else end = mid;
        mid = (start + end) / 2;
    }
    answer[child] = max(answer[child - 1], a[graph[mid]] * child - a[graph[mid]] * parents[graph[mid]]);
    cout << answer[child] << "\n";

    for (ll element: children[child]) dfs(child, element);

    graph[value_temp.first] = value_temp.second;
    lenght = lenght_temp;
}


int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> n;

    // {i, a[i]}
    tree_stack.push_back({0, 0});
    for (ll i = 1; i <= n; ++i) {
        cin >> a[i];
        while (tree_stack.back().second >= a[i]) tree_stack.pop_back();
        children[tree_stack.back().first].push_back(i);
        parents[i] = tree_stack.back().first;
        tree_stack.push_back({i, a[i]});
    }
    for (ll element: children[0]) dfs(0, element);
    return 0;
}