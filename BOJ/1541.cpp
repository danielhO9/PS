#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    string goal; cin >> goal;
    vector<int> plus, minus;
    int temp = 0;
    bool changer = false;
    for (int i = 0; i < goal.size(); ++i) {
        if (int(goal[i]) == 43) {
            if (changer) minus.push_back(temp);
            else plus.push_back(temp);
            temp = 0;
        }else if (int(goal[i] == 45)) {
            if (changer) minus.push_back(temp);
            else plus.push_back(temp);
            temp = 0;
            changer = true;
        } else {
            temp = 10 * temp + int(goal[i]) - 48;
        }
    }
    if (changer) minus.push_back(temp);
    else plus.push_back(temp);
    int sum = 0;
    for (int i: plus) sum += i;
    for (int i: minus) sum -= i;
    cout << sum;
    return 0;
}