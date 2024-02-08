#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; cin >> n;
    vector<int> stack; vector<string> answer;
    int goal; int number = 1; bool available = true;
    for (int i = 1; i <= n; ++i) {
        cin >> goal;
        while (true) {
            if (stack.empty() || stack.back() < goal) {
                stack.push_back(number);
                ++number;
                answer.push_back("+");
            } else if (stack.back() == goal) {
                stack.pop_back();
                answer.push_back("-");
                break;
            } else if (stack.back() > goal) {
                available = false;
                break;
            }
        }
        if (!available) break;
    }
    if (!available) cout << "NO";
    else {
        for (string element: answer) {
            cout << element << "\n";
        }
    }
    return 0;
}