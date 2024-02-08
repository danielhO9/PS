#include <bits/stdc++.h>
using namespace std;

int main() {
    int N; cin >> N; int sum = 0;
    vector<int> array; int temp;
    vector<int> counter(80001);
    vector<int> answer;
    for (int i = 0; i < N; ++i) {
        cin >> temp; array.push_back(temp);
        sum += temp; counter[temp + 4000] += 1;
    }
    sort(array.begin(), array.end());
    if (round(sum / static_cast<double>(N)) == 0) cout << 0 << "\n";
    else cout << round(sum / static_cast<double>(N)) << "\n";
    cout << array[N / 2] << "\n";
    int max_value = *max_element(counter.begin(), counter.end());
    for (int i = 0; i <= 8000; ++i) {
        if (counter[i] == max_value) answer.push_back(i - 4000);
    }
    sort(answer.begin(), answer.end());
    if (answer.size() == 1) cout << answer[0] << "\n";
    else cout << answer[1] << "\n";
    cout << *max_element(array.begin(), array.end()) - *min_element(array.begin(), array.end());


    return 0;
}