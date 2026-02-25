#include <bits/stdc++.h>
using namespace std;

string zero = "0000000";
string number[10] = {
    "1111110", 
    "0110000",
    "1101101",
    "1111001",
    "0110011",
    "1011011",
    "1011111",
    "1110000",
    "1111111",
    "1111011"
};

string previous_time[4];
string current_time[4];
int answer[4];
vector<pair<string, string>> hour_state;
vector<string> min_state_first;
vector<string> min_state_second;

void get_state(const string& real, const string& clock, string& ret) {
    ret.resize(7);
    
    for (int i = 0; i < 7; ++i) {
        if (real[i] == '0' && clock[i] == '1') {
            ret[0] = '3';
            return;
        }
        else if (clock[i] == '1') ret[i] = '1';
        else ret[i] = '0';
    }
}

bool match(const string& real, const string& clock, const string& state) {
    for (int i = 0; i < 7; ++i) {
        if (real[i] == '0' && clock[i] == '1') return false;
        if (state[i] == '1' && real[i] != clock[i]) return false; 
    }
    return true;
}

void solve() {
    for (int i = 0; i < 4; ++i) cin >> previous_time[i];
    for (int i = 0; i < 4; ++i) cin >> current_time[i];
    
    hour_state.clear();
    min_state_first.clear();
    min_state_second.clear();

    for (int hour = 0; hour < 13; ++hour) {
        int hour_first = hour / 10;
        int hour_second = hour % 10;
        if (hour_first == 0) swap(zero, number[0]);
        
        string state[2];
        get_state(number[hour_first], previous_time[0], state[0]);
        get_state(number[hour_second], previous_time[1], state[1]);

        if (state[0][0] <= '1' && state[1][0] <= '1') hour_state.push_back(make_pair(state[0], state[1]));
        
        if (hour_first == 0) swap(zero, number[0]);
    }

    for (int num = 0; num < 6; ++num) {
        string state;
        get_state(number[num], previous_time[2], state);
        if (state[0] != '3') min_state_first.push_back(state);
    }

    for (int num = 0; num < 10; ++num) {
        string state;
        get_state(number[num], previous_time[3], state);
        if (state[0] != '3') min_state_second.push_back(state);
    }

    for (int hour = 0; hour < 13; ++hour) {
        int hour_first = hour / 10;
        int hour_second = hour % 10;
        if (hour_first == 0) swap(zero, number[0]);

        for (auto state: hour_state) {
            if (
                match(number[hour_first], current_time[0], state.first) &&
                match(number[hour_second], current_time[1], state.second)
            ) {
                answer[0] = hour_first;
                answer[1] = hour_second;
            }
        }
        
        if (hour_first == 0) swap(zero, number[0]);
    }

    for (int num = 0; num < 6; ++num) {

        for (auto state: min_state_first) {
            if (
                match(number[num], current_time[2], state)
            ) {
                answer[2] = num;
            }
        }
    }

    for (int num = 0; num < 10; ++num) {

        for (auto state: min_state_second) {
            if (
                match(number[num], current_time[3], state)
            ) {
                answer[3] = num;
            }
        }
    }
    if (answer[0]) cout << answer[0];
    cout << answer[1] << ':' << answer[2] << answer[3] << "\n";


}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int t; cin >> t;
    while (t--) solve();
}