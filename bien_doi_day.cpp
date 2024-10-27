/*
     /\_/\    /\_/\
    ( o.o )  ( -.- )
     > ^ <    (")(")
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int SIZE = 1e5 + 9;
const ll MOD = 1e9 + 7;

int n, m, b[SIZE];
ll MAX_STEP, prefix[2 * SIZE], cnt[2 * SIZE], step[2 * SIZE];

void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    return;
}

void solve() {
    // B1: Tinh MAX_STEP
    for (int i = 1; i < n; i++) {
        if (b[i] < b[i + 1]) {
            MAX_STEP += b[i + 1] - b[i];
        }
        else {
            MAX_STEP += m + b[i + 1] - b[i];
        }
    }

    // B2: Tinh tong so buoc cua moi doan bao lay b[i] (su dung tong cong don)
    for (int i = 1; i < n; i++) {
        if (b[i] < b[i + 1]) {
            prefix[b[i]] += b[i + 1] - b[i];
            prefix[b[i + 1] + 1] -= b[i + 1] - b[i];
        }
        else {
            prefix[b[i]] += m + b[i + 1] - b[i];
            prefix[m + b[i + 1] + 1] -= m + b[i + 1] - b[i];
        }
    }

    for (int i = 1; i <= 2 * m - 1; i++) {
        prefix[i] += prefix[i - 1];
    }

    // B3 Tinh tong so buoc tu b[i] den dich cac doan bao lay b[i] (su dung tong bac thang)
    for (int i = 1; i < n; i++) {
        if (b[i] < b[i + 1]) {
            cnt[b[i] + 1] += 1;
            cnt[b[i + 1] + 1] -= 1;
            step[b[i]] += b[i + 1] - b[i];
        }
        else {
            cnt[b[i] + 1] += 1;
            cnt[m + b[i + 1] + 1] -= 1;
            step[b[i]] += m + b[i + 1] - b[i];
        }
    }

    for (int i = 1; i <= 2 * m - 1; i++) {
        cnt[i] += cnt[i - 1];
    }

    step[0] -= cnt[0];
    for (int i = 1; i <= 2 * m - 1; i++) {
        step[i] += step[i - 1];
        step[i] -= cnt[i];
    }

    // B4 Tim so buoc nho nhat khi chon X thuoc doan [0, m - 1] cho pbd 2 (Gap mang)
    ll ans = 1e18;
    for (int X = 0; X <= m - 1; X++) {
        prefix[X] += prefix[X + m];
        cnt[X] += cnt[X + m];
        step[X] += step[X + m];
        ans = min(ans, MAX_STEP - prefix[X] + cnt[X] + step[X]);
    }
    cout << ans;
    return;
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    input();
    solve();
    return 0;
}
/*
     /\_/\    /\_/\
    ( o.o )  ( -.- )
     > ^ <    (")(")
*/
