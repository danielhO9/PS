#include <bits/stdc++.h>
using namespace std;

int main() {
    string n;
    while (true) {
        cin >> n;
        if (n == "0") break;
        while (n != "") {
            if (n.front() == n.back()) {
                n.pop_back();
                if (n == "") break;
                else n = n.substr(1, n.size() - 1);
            }
            else break;
        }
        if (n == "") cout << "yes" << "\n";
        else cout << "no" << "\n";
    }

    return 0;
}