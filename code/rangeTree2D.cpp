#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

struct COORDINATE {
    int x, y;
};

bool cmp(const COORDINATE& x, const COORDINATE& y) {
    return x.x < y.x;
}

/* x: data, y: index */
struct RangeTree2D {
    COORDINATE **container;
    bool **is_left;
    int **left, **right, *input, length, rank, capacity;
    void init(int *input, int length) {
        this->input = input;
        this->length = length;
        rank = 1;
        while ( (1<<rank++) < length );
        capacity = 1<<(rank-1);
        container = new COORDINATE*[rank], left = new int*[rank], right = new int*[rank];
        is_left = new bool*[rank];
        for (int i = 0; i < rank; ++i) {
            container[i] = new COORDINATE[capacity];
            left[i] = new int[capacity];
            right[i] = new int[capacity];
            is_left[i] = new bool[capacity];
        }
        for (int i = 0; i < capacity; ++i) {
            container[0][i].x = i>=length?0:input[i];
            container[0][i].y = i;
        }
        sort(container[0], container[0]+length, cmp);
        build(rank-1, 0, capacity-1);
    }

    void build(int height, int start, int finish) {
        if (height == 0) return;
        if (start == finish) {
            build(height-1, start, finish);
            container[height][start] = container[height-1][start];
            return;
        }

        int middle = start+(1<<(height-1));
        build(height-1, start, middle-1);
        build(height-1, middle, finish);
        int now = start, l_index = start, r_index = middle;

        while (now <= finish) {

            left[height][now] = l_index;
            right[height][now] = r_index;

            if (l_index < middle && (r_index > finish || container[height-1][l_index].y <= container[height-1][r_index].y)) {
                container[height][now] = container[height-1][l_index];
                is_left[height][now] = true;
                ++l_index;
            }
            else {
                container[height][now] = container[height-1][r_index];
                is_left[height][now] = false;
                ++r_index;
            }

            ++now;
        }
    }

    /* 0-base index, k 1-base */
    int query(int start, int finish, int k) {
        return query(rank-1, start, finish, k);
    }

    int query(int height, int start, int finish, int k) {
        if (height == 0) return container[height][start].x;
        int left_size = left[height][finish] - left[height][start];
        if (is_left[height][finish]) ++left_size;
        int right_size = finish-start+1-left_size;
        if (left_size >= k) return query(height-1, left[height][start], min(left[height][finish], left[height][start]+left_size-1), k);
        else return query(height-1, right[height][start], min(right[height][finish], right[height][start]+right_size-1), k-left_size);
    }
};

int input[100005];
int main () {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &input[i]);
    }
    RangeTree2D range;
    range.init(input, n);
    for (int i = 0; i < m; ++i) {
        int a, b, k;
        scanf("%d%d%d", &a, &b, &k);
        printf("%d\n", range.query(a-1, b-1, k));
    }
    return 0;
}
/* Pass POJ 2104 */
