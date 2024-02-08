#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL n, d, temp, ans;
vector<LL> arr;

void solution() {
    ans = 0;
    cin >> n >> d;
    priority_queue<LL> Q;
    for (LL i = 0; i < n; ++i) {
        cin >> temp; arr.push_back(temp);
    }
    sort(arr.begin(), arr.end());
    for (LL i = 0; i < n; ++i) {
        temp = (n - i) * d + arr[i];

        if (!Q.empty() && temp < Q.top()) {
            ans += Q.top() - temp;
            Q.pop();
            if (temp < n * d) { Q.push(n * d); Q.push(n * d);}
            else { Q.push(temp); Q.push(temp); }
        } else {
            Q.push(temp);
        }
        
    }
    cout << ans << "\n";
    arr.clear();
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int z; cin >> z;
    for (int i = 0; i < z; ++i) {
        solution();
    }
}