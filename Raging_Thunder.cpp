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
    int ans1, l1, r1;
    int ans2, l2, r2;
    char char_left, char_right;

    node() {
        sz = 0;
        ans1 = l1 = r1 = 0;
        ans2 = l2 = r2 = 0;
        char_left = char_right = '?';
    }
};

node segment[4 * maxsize];
int n, q, lazy[4 * maxsize];
char a[maxsize];

inline node merge_node (node left_node, node right_node) {
    if (!left_node.sz) {
        return right_node;
    }
    if (!right_node.sz) {
        return left_node;
    }

    node res;
    res.sz = left_node.sz + right_node.sz;
    res.ans1 = max(left_node.ans1, right_node.ans1);
    res.l1 = left_node.l1;
    res.r1 = right_node.r1;

    if (!(left_node.char_right == '<' && right_node.char_left == '>')) {
        res.ans1 = max(res.ans1, left_node.r1 + right_node.l1);
        if (res.l1 == left_node.sz) {
            res.l1 += right_node.l1;
        }
        if (res.r1 == right_node.sz) {
            res.r1 += left_node.r1;
        }
    }

    res.ans2 = max(left_node.ans2, right_node.ans2);
    res.l2 = left_node.l2;
    res.r2 = right_node.r2;

    if (!(left_node.char_right == '>' && right_node.char_left == '<')) {
        res.ans2 = max(res.ans2, left_node.r2 + right_node.l2);
        if (res.l2 == left_node.sz) {
            res.l2 += right_node.l2;
        }
        if (res.r2 == right_node.sz) {
            res.r2 += left_node.r2;
        }
    }

    res.char_left = left_node.char_left;
    res.char_right = right_node.char_right;
    return res;
}

void build(int id, int l, int r) {
    if (r - l == 1) {
        segment[id].sz = 1;
        segment[id].ans1 = segment[id].l1 = segment[id].r1 = 1;
        segment[id].ans2 = segment[id].l2 = segment[id].r2 = 1;
        segment[id].char_left = segment[id].char_right = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * id, l, m);
    build(2 * id + 1, m, r);
    segment[id] = merge_node(segment[2 * id], segment[2 * id + 1]);
    return;
}

inline void flip(int id) {
    swap(segment[id].ans1, segment[id].ans2);
    swap(segment[id].l1, segment[id].l2);
    swap(segment[id].r1, segment[id].r2);
    segment[id].char_left = (segment[id].char_left == '>' ? '<' : '>');
    segment[id].char_right = (segment[id].char_right == '>' ? '<' : '>');
    return;
}

inline void fix(int id, int l, int r) {
    if (!lazy[id]) {
        return;
    }
    if (lazy[id] & 1) {
        flip(id);
    }
    if (r - l > 1) {
        lazy[2 * id] += lazy[id];
        lazy[2 * id + 1] += lazy[id];
    }
    lazy[id] = 0;
    return;
}

inline void update(int id, int l, int r, int u, int v) {
    fix(id, l, r);
    if (v <= l || r <= u) {
        return;
    }
    if (u <= l && r <= v) {
        lazy[id] += 1;
        fix(id, l, r);
        return;
    }
    
    int m = (l + r) / 2;
    update(2 * id, l, m, u, v);
    update(2 * id + 1, m, r, u, v);
    segment[id] = merge_node(segment[2 * id], segment[2 * id + 1]);
    return;
}

inline node get_ans(int id, int l, int r, int u, int v) {
    fix(id, l, r);
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
    ff (i, 1, n, 1) {
        cin >> a[i];
    }
    return;
}

void solve() {
    build(1, 1, n + 1);
    while (q--) {
        int l, r;
        cin >> l >> r;
        r += 1;
        update(1, 1, n + 1, l, r);
        cout << get_ans(1, 1, n + 1, l, r).ans1 << '\n';
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
