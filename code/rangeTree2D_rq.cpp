struct POS {
    int x, y, value, cost, segid;
    POS(){}
    POS(int x, int y, int value, int cost):x(x), y(y), value(value), cost(cost) {}
	bool operator<(const POS &rhs) const {
		return this->y < rhs.y;
	}
} pos[100005];

struct SegmentTree{

    unordered_map<int, int> trans;
	int rank, capacity, length;
	POS *input;
    int *tree;

    SegmentTree() {}
	void init(POS* input, int length){
        trans.clear();
		this->input = input;
		this->length = length;
		rank = 1;
		while((1<<rank++) < length);
		capacity = 1<<(rank-1);
		tree = new int[capacity << 1];
		build(1, capacity, capacity<<1);
	}

	~SegmentTree(){
        delete[] tree;
	}

	int build(int index, int left, int right){
		if(index >= left){
			tree[index] = getInput(index);
            trans[tree[index]] = index;
            return tree[index];
		}
		int middle = (left+right) >> 1;
		int left_value = build(lc(index), left, middle);
		int right_value = build(rc(index), middle, right);
		return tree[index] = max(left_value, right_value);
	}

    void update(int origin_value, int value) {
        int index = trans[origin_value];
        tree[index] = value;
        maintain(index>>1);
    }

	void maintain(int index){
        tree[index] = max(tree[lc(index)], tree[rc(index)]);
		if(index == 1) return;
        maintain(index>>1);
	}

	int query(int start, int finish){
		return query(1, capacity, capacity<<1, capacity+start, capacity+finish+1);
	}

	int query(int index, int left, int right, int start, int finish){
		if(left == start && right == finish) return tree[index];
		int middle = (left+right) >> 1;
		if(finish <= middle) return query(lc(index), left, middle, start, finish);
		if(start >= middle) return query(rc(index), middle, right, start, finish);
		int left_value = query(lc(index), left, middle, start, middle);
		int right_value = query(rc(index), middle, right, middle, finish);
		return max(left_value, right_value);
	}

	int getInput(int index){
		index -= capacity;
		if(index < length) return input[index].value;
		return 0;
	}

	int lc(int x){
		return x<<1;
	}

	int rc(int x){
		return (x<<1)+1;
	}
};

bool cmp(const POS& x, const POS& y) {
    return x.x==y.x? x.y<y.y: x.x<y.x;
}

struct rangeTree2D {
    unordered_map<int, int> trans;
    POS **container, *input;
    SegmentTree *seg;
    int rank, capacity, length;
    int *idx;
    void init(POS* input, int length) {
        trans.clear();
        sort(input, input+length, cmp);
        for (int i = 0; i < length; ++i) this->trans[input[i].value] = i;
        this->input = input;
        this->length = length;
        rank = 1;
        while ( (1<<rank++) < length) ;
        capacity = 1<<(rank-1);
        container = new POS*[rank];
        seg = new SegmentTree[capacity<<1];
        idx = new int[length];
        POS tmp(input[length-1].x+1, input[length-1].y+1, 0, 0);
        for (int i = 0; i < rank; ++i) {
            container[i] = new POS[capacity];
        }
        for (int i = 0; i < length; ++i) {
            container[0][i] = input[i];
            idx[i] = input[i].x;
        }
        for (int i = length; i < capacity; ++i) container[0][i] = tmp;
        sort(idx, idx+length);

        // build
        int segid = 0;
        for (int height = 0; height < rank-1; ++height) {
            for (int i = 0; i < capacity; i += (2<<height)) {
                merge(container[height]+i, container[height]+i+(1<<height),
                      container[height]+i+(1<<height), container[height]+i+(2<<height),
                      container[height+1]+i);
                container[height+1][i].segid = segid;
                seg[segid++].init(container[height+1]+i, (2<<height));
            }
        }
    }

    void decrease(int value) {
        int index = trans[value];
        container[0][index].value = 0;
        maintain(1, (index>>1)<<1, value);
    }

    int range_query(int left, int right, int bottum, int top) {
        left = lower_bound(idx, idx+length, left)-idx;
        right = upper_bound(idx, idx+length, right)-idx;

        POS _bottum(0, bottum, 0, 0), _top(0, top, 0, 0);
        int ans = range_query(rank-1, 0, left, right, _bottum, _top);
        if (ans != 0) decrease(ans);
        if (ans == 0) return 0;
        return container[0][trans[ans]].cost;
    }

    void maintain(int height, int start, int value) {
        if (height == rank) return;
        int myId = container[height][start].segid;
        seg[myId].update(value, 0);
        maintain(height+1, (start>>(height+1))<<(height+1), value);
    }

    int range_query(int height, int start, int left, int right, const POS& bottum, const POS& top) {
        if (start >= right || start+(1<<height) <= left) return 0;
        if (start >= left && start+(1<<height)<= right) {
            int st = lower_bound(container[height]+start, container[height]+start+(1<<height), bottum)-container[height]-start;
            int ed = upper_bound(container[height]+start, container[height]+start+(1<<height), top)-container[height]-start;
            --ed;
            if (ed < st) return 0;
            if (height == 0) return container[0][start].value;
            int myId = container[height][start].segid;
            return seg[myId].query(st, ed);
        }
        --height;
        return max(range_query(height, start, left, right, bottum, top),
                range_query(height, start+(1<<height), left, right, bottum, top));
    }
};
