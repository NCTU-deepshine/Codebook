#include <bits/stdc++.h>

using namespace std;

typedef int T;

struct Treap {
    T key, priority, size;
    Treap *lc, *rc;
    Treap(T key): key(key), priority(rand()), size(1), lc(NULL), rc(NULL) {}
};

inline int size(Treap *target) {
    if (!target) return 0;
    return target->size;
}

inline void pull(Treap *target) {
    target->size = size(target->lc) + size(target->rc) + 1;
}

Treap* merge(Treap *lhs, Treap *rhs) {
    if (!lhs || !rhs) return lhs? lhs: rhs;
    if (lhs->priority > rhs->priority) {
        lhs->rc = merge(lhs->rc, rhs);
        pull(lhs);
        return lhs;
    }
    else {
        rhs->lc = merge(lhs, rhs->lc);
        pull(rhs);
        return rhs;
    }
}

void split(Treap *target, Treap *&lhs, Treap *&rhs, int k) {
    if (!target) lhs = rhs = NULL;
    else if (k > target->key) {
        lhs = target;
        split(target->rc, lhs->rc, rhs, k);
        pull(lhs);
    }
    else {
        rhs = target;
        split(target->lc, lhs, rhs->lc, k);
        pull(rhs);
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
    pull(target);
    return target;
}

T findK(Treap *target, int k) {
    if (size(target->lc)+1 == k) return target->key;
    else if (size(target->lc) < k) return findK(target->rc, k-size(target->lc)-1);
    else return findK(target->lc, k);
}

int main () {
    return 0;
}

/* pass POJ2761 */
