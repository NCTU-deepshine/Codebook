struct POS {
    int x, y;
    POS(){}
    POS(int x, int y):x(x), y(y) {}
	bool operator<(const POS &rhs) const {
		return this->y < rhs.y;
	}
} pos[10005];

bool cmp(const POS& x, const POS& y) {
    return x.x==y.x? x.y<y.y: x.x<y.x;
}

struct rangeTree2D {
    POS **container, *input;
    int rank, capacity, length;
    int *idx;
    void init(POS* input, int length) {
        sort(input, input+length, cmp);
        this->input = input;
        this->length = length;
        rank = 1;
        while ( (1<<rank++) < length) ;
        capacity = 1<<(rank-1);
        container = new POS*[rank];
        idx = new int[length];
        POS tmp;
        tmp.x = input[length-1].x+1, tmp.y = input[length-1].y+1;
        for (int i = 0; i < rank; ++i) container[i] = new POS[capacity];
        for (int i = 0; i < length; ++i) {
            container[0][i] = input[i];
            idx[i] = input[i].x;
        }
        for (int i = length; i < capacity; ++i) container[0][i] = tmp;
        sort(idx, idx+length);

        // build
        for (int height = 0; height < rank-1; ++height) {
            for (int i = 0; i < capacity; i += (2<<height)) {
                merge(container[height]+i, container[height]+i+(1<<height),
                      container[height]+i+(1<<height), container[height]+i+(2<<height),
                      container[height+1]+i);
            }
        }
    }
    int range_query(int left, int right, int bottum, int top) {
        left = lower_bound(idx, idx+length, left)-idx;
        right = upper_bound(idx, idx+length, right)-idx;

        POS _bottum(0, bottum), _top(0, top);
        return range_query(rank-1, 0, left, right, _bottum, _top);
    }
    int range_query(int height, int start, int left, int right, const POS& bottum, const POS& top) {
        if (start >= right || start+(1<<height) <= left) return 0;
        if (start >= left && start+(1<<height)<= right) {
            return upper_bound(container[height]+start, container[height]+start+(1<<height), top)
                   -lower_bound(container[height]+start, container[height]+start+(1<<height), bottum);
        }
        --height;
        return range_query(height, start, left, right, bottum, top)+range_query(height, start+(1<<height), left, right, bottum, top);
    }
};
