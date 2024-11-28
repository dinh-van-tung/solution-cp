/*
     /\_/\    /\_/\
    ( o.o )  ( -.- )
     > ^ <    (")(")
*/
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pii pair<int, int>
#define pil pair<int, long long>
#define pli pair<long long, int>
#define pll pair<long long, long long>
#define ff(i, a, b, j) for (int i = (a), bb = (b), jj = (j); i <= bb; i += jj)
#define rf(i, a, b, j) for (int i = (a), bb = (b), jj = (j); i >= bb; i -= jj)
#define lshift(x, i) ((x) << (i))
#define rshift(x, i) ((x) >> (i))
#define checkbit(x, i) (((x) >> (i)) & 1ll)
#define cnt_bit1(x) __builtin_popcountll((x))
#define clz(x) __builtin_clzll((x)) // count leading zeros
#define ctz(x) __builtin_ctzll((x)) // count trailing zeros
#define ll long long
#define ull unsigned long long
#define ld long double
#define db double
#define maxsize 500005
#define mod 1000000007

struct node {
    int sz;
    int res1, l1, r1;
    int res2, l2, r2;
    char cl, cr;
    bool lazy;

    node() {
        sz = 0;
        res1 = l1 = r1 = 0;
        res2 = l2 = r2 = 0;
        cl = cr = 0;
        lazy = 0;
    }
};

node segment[4 * maxsize];
int n, q;
char a[maxsize];

node merge_node (node a, node b) {
    if (!a.sz) return b;
    if (!b.sz) return a;
 
    node res;
    res.sz = a.sz + b.sz;
    res.res1 = max(a.res1, b.res1);
    res.l1 = a.l1;
    res.r1 = b.r1;
    if (!(a.cr == '<' && b.cl == '>')) {
        res.res1 = max(res.res1, a.r1 + b.l1);
        if (res.r1 == b.sz) res.r1 += a.r1;
        if (res.l1 == a.sz) res.l1 += b.l1;
    }

    res.res2 = max(a.res2, b.res2);
    res.l2 = a.l2;
    res.r2 = b.r2;
    if (!(a.cr == '>' && b.cl == '<')) {
        res.res2 = max(res.res2, a.r2 + b.l2);
        if (res.r2 == b.sz) res.r2 += a.r2;
        if (res.l2 == a.sz) res.l2 += b.l2;
    }
    res.cl = a.cl, res.cr = b.cr;
 
    return res;
}

void build(int id, int l, int r) {
    if (r - l == 1) {
        segment[id].sz = 1;
        segment[id].res1 = segment[id].l1 = segment[id].r1 = 1;
        segment[id].res2 = segment[id].l2 = segment[id].r2 = 1;
        segment[id].cl = segment[id].cr = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * id, l, m);
    build(2 * id + 1, m, r);
    segment[id] = merge_node(segment[2 * id], segment[2 * id + 1]);
    return;
}

void flip(int id) {
    swap(segment[id].res1, segment[id].res2);
    swap(segment[id].l1, segment[id].l2);
    swap(segment[id].r1, segment[id].r2);
    segment[id].cl = '<' + '>' - segment[id].cl;
    segment[id].cr = '<' + '>' - segment[id].cr;
    segment[id].lazy ^= 1;
    return;
}

void shift(int id) {
    if (!segment[id].lazy) {
        return;
    }
    flip(2 * id);
    flip(2 * id + 1);
    segment[id] = merge_node(segment[2 * id], segment[2 * id + 1]);
    segment[id].lazy = 0;
    return;
}

void change(int id, int l, int r, int u, int v) {
    if (v <= l || r <= u) {
        return;
    }
    if (u <= l && r <= v) {
        flip(id);
        return;
    }
    shift(id);
    int m = (l + r) / 2;
    change(2 * id, l, m, u, v);
    change(2 * id + 1, m, r, u, v);
    segment[id] = merge_node(segment[2 * id], segment[2 * id + 1]);
    return;
}

node get_ans(int id, int l, int r, int u, int v) {
    if (v <= l || r <= u) {
        return node();
    }
    if (u <= l && r <= v) {
        return segment[id];
    }
    int m = (l + r) / 2;
    return merge_node(get_ans(2 * id, l, m, u, v), get_ans(2 * id + 1, m, r, u, v));
}

void input() {
    cin >> n >> q;
    ff (i, 0, n - 1, 1) {
        cin >> a[i];
    }
    return;
}

void solve() {
    build(1, 0, n);
    while (q--) {
        int l, r;
        cin >> l >> r;
        l -= 1;
        change(1, 0, n, l, r);
        cout << get_ans(1, 0, n, l, r).res1 << '\n';
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    
    int cnt_test = 1;
    // cin >> cnt_test;
    while (cnt_test--) {
        input();
        solve();
    }
    return 0;
}
/*
     /\_/\    /\_/\
    ( o.o )  ( -.- )
     > ^ <    (")(")
*/
