#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
    while (a != 0 && b != 0) {
        int temp;
        if (a < b) {
            temp = a; a = b; b = temp;
        }
        a = a % b;
    }
    return a + b;
}

int main() {
    int a, b; cin >> a >> b;
    cout << gcd(a, b) << "\n";
    cout << a * b / gcd(a, b);
    
    return 0;
}