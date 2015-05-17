#include <bits/stdc++.h>

using namespace std;

typedef int T;

struct Treap {
    T key, priority;
    Treap *lc, *rc;
    Treap(T key): key(key), priority(rand()), lc(NULL), rc(NULL) {}
};

Treap* merge(Treap *lhs, Treap *rhs) {
    if (!lhs || !rhs) return lhs? lhs: rhs;
    if (lhs->priority > rhs->priority) {
        lhs->rc = merge(lhs->rc, rhs);
        return lhs;
    }
    else {
        rhs->lc = merge(lhs, rhs->lc);
        return rhs;
    }
}

void split(Treap *target, Treap *&lhs, Treap *&rhs, int k) {
    if (!target) lhs = rhs = NULL;
    else if (k > target->key) {
        lhs = target;
        split(target->rc, lhs->rc, rhs, k);
    }
    else {
        rhs = target;
        split(target->lc, lhs, rhs->lc, k);
    }
}

Treap* insert(Treap *target, int key) {
    Treap *lhs, *rhs;  
    split(target, lhs, rhs, key);
    return merge(merge(lhs, new Treap(key)), rhs);
}

/* delete singal key */
Treap* del(Treap *target, int key) {
    if (target->key == key) return merge(target->lc, target->rc);
    else if (target->key > key) target->lc = del(target->lc, key);
    else target->rc = del(target->rc, key);
    return target;
}

int main () {
    return 0;
}
