#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1000005;
int tree[MAXN << 2];
int lazy[MAXN << 2];

void push_up(int node) {
    tree[node] = max(tree[node << 1], tree[node << 1 | 1]);
}

void push_down(int node) {
    if (lazy[node]) {
        tree[node << 1] += lazy[node];
        lazy[node << 1] += lazy[node];
        tree[node << 1 | 1] += lazy[node];
        lazy[node << 1 | 1] += lazy[node];
        lazy[node] = 0;
    }
}

void update(int node, int start, int end, int l, int r, int val) {
    if (l <= start && end <= r) {
        tree[node] += val;
        lazy[node] += val;
        return;
    }
    push_down(node);
    int mid = (start + end) >> 1;
    if (l <= mid) update(node << 1, start, mid, l, r, val);
    if (r > mid) update(node << 1 | 1, mid + 1, end, l, r, val);
    push_up(node);
}

int query(int node, int start, int end, int l, int r) {
    if (l <= start && end <= r) {
        return tree[node];
    }
    push_down(node);
    int mid = (start + end) >> 1;
    int res = 0;
    if (l <= mid) res = max(res, query(node << 1, start, mid, l, r));
    if (r > mid) res = max(res, query(node << 1 | 1, mid + 1, end, l, r));
    return res;
}

// Fast I/O
inline int read() {
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

int main() {
    int x = read();
    int k = read();
    int p = read();

    for (int i = 0; i < p; ++i) {
        int u = read();
        int v = read();
        int n = read();
        
        if (u > v) swap(u, v);
        
        if (u == v) {
            putchar('T');
            putchar('\n');
            continue;
        }

        int max_booked = query(1, 1, x - 1, u, v - 1);
        if (max_booked + n <= k) {
            update(1, 1, x - 1, u, v - 1, n);
            putchar('T');
            putchar('\n');
        } else {
            putchar('N');
            putchar('\n');
        }
    }

    return 0;
}
