#include <iostream>
#include <queue>
#include <cstring>
#include <cstdio>

using namespace std;

struct AC_Automaton {
    static const int MAX_N = 1e6+10;
    static const int MAX_CHILD = 52;

    int n;
    int fail[MAX_N];
    int trie[MAX_N][MAX_CHILD];

    void clean(int target) {
        for (int i = 0; i < MAX_CHILD; ++i) {
            trie[target][i] = -1;
        }
    }

    void reset () {
        clean(0);
        n = 1;
    }

    void add(char* s) {
        int p = 0;
        while (*s) {
            int id = get_id(s[0]);
            if (trie[p][id] == -1) {
                clean(n);
                trie[p][id] = n++;
            }
            p = trie[p][id];
            ++s;
        }
    }

    void construct() {
        queue<int> que;
        fail[0] = 0;

        for (int i = 0; i < MAX_CHILD; ++i) {
            if (trie[0][i] != -1) {
                fail[trie[0][i]] = 0;
                que.push(trie[0][i]);
            }
            else {
                trie[0][i] = 0;
            }
        }

        while (que.size()) {
            int now = que.front();
            que.pop();

            for (int i = 0; i < MAX_CHILD; ++i) {
                int target = trie[now][i];
                if (target != -1) {
                    que.push(target);
                    fail[target] = trie[fail[now]][i];
                }
                else {
                    trie[now][i] = trie[fail[now]][i];
                }
            }
        }
    }

    int solve() {
        int ans = fail[n-1];
        while (ans > n/2-1) ans = fail[ans];
        return ans;
    }

    int get_id(const char& ch) {
        if (ch <= 'z' && ch >= 'a') return ch-'a';
        else return ch-'A'+26;
    }
} ac;

char input[1000010];

int main () {
    int tcase;
    scanf("%d", &tcase);
    while (tcase--) {
        ac.reset();
        scanf("%s", input);
        ac.add(input);
        ac.construct();
        printf("%d\n", ac.solve());
    }
}
