/* O(V^2) */
#include <iostream>
#include <cstdio>
#define MAX 10000

using namespace std;

/* p for dfs, parent for tree */
int p[MAX], parent[MAX];
int lca[MAX][MAX];
int num, root;
bool visit[MAX];

int dis_find(int x) {
    if (x == p[x]) return x;
    return p[x] = dis_find(p[x]);
}

void dfs(int x) {
    if (visit[x]) return;
    visit[x] = true;

    for (int i = 0; i < num; ++i) {
        if (visit[x]) {
            lca[x][i] = lca[i][x] = dis_find(i);
        }
    }

    for (int i = 0; i < num; ++i) {
        if (parent[i] == x) {
            dfs(i);
            p[i] = x;
        }
    }
}

int main () {
    /* init */
    for (int i = 0; i < num; ++i) {
        p[i] = i;
        visit[i] = false;
        parent[i] = -1;
    }

    /* build tree first */
    /* use parent[x] = px to build tree */
    dfs(root);
    cin >> x >> y;
    cout << lca[x][y] << endl;
}
