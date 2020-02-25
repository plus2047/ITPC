#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#define MAXN 1001000
using namespace std;
queue<int> que;
int n, ml, md, tot;
int vis[MAXN], dis[MAXN], cnt[MAXN];
int to[MAXN], net[MAXN], cap[MAXN], head[MAXN];
void add(int u, int v, int w) {
    to[++tot] = v;
    cap[tot] = w;
    net[tot] = head[u];
    head[u] = tot;
}
void spfa() {
    memset(vis, 0, sizeof(vis));
    memset(dis, 0x7f, sizeof(dis));
    dis[1] = 0;
    vis[1] = 1;
    cnt[1]++;
    que.push(1);
    while (!que.empty()) {
        int now = que.front();
        que.pop();
        vis[now] = 0;
        for (int i = head[now]; i; i = net[i])
            if (dis[to[i]] > dis[now] + cap[i]) {
                dis[to[i]] = dis[now] + cap[i];
                if (!vis[to[i]]) {
                    if (++cnt[to[i]] > n) {
                        printf("-1");
                        exit(0);
                    }
                    vis[to[i]] = 1;
                    que.push(to[i]);
                }
            }
    }
    if (dis[n] == 2139062143)
        printf("-2");
    else
        printf("%d", dis[n]);
    exit(0);
}
int main() {
    scanf("%d%d%d", &n, &ml, &md);
    for (int i = 1; i <= ml; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        add(a, b, d);
    }
    for (int i = 1; i <= md; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        add(b, a, -d);
    }
    for (int i = 1; i <= n; i++) add(i, i - 1, 0);
    spfa();
}