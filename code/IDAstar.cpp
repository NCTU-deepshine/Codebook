int search(STATE& now, int g, int bound) {
    int f = g + now.heuri;
    if (f > bound) return f;
    if (is_goal(now)) return FOUND;

    int min = INF;
    for next in successors(now):
        int t = search(state, g+cost(now,next), bound);
        if (t == FOUND) return FOUND;
        if (t < min) min = t;
    }
    return min;
}

void IDAStar() {
    STATE init(input);
    int bound = init.heuri;
    while (bound <= MAXI) {
        int t = search(init, 0, bound);
        if (t == FOUND) return FOUND;
        if (t == INF) return NOT_FOUND;
        bound = t;
    }
}
