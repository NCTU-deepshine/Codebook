#include <bits/stdc++.h>
using namespace std;

struct COORDINATE {
    int x, y;
};

bool cmp(const COORDINATE& x, const COORDINATE& y) {
    return x.x > y.x;
}

/* x: data, y: index */
struct RangeTree2D {
    COORDINATE **container;
    bool **is_left;
    int **left, **right;
    int *input;
    int length, rank, capacity;
    void init(int *input, int length) {
        this->input = input;
        this->length = length;
        rank = 1;
        while ( (1<<rank++) < length );
        capacity = 1<<(rank-1);
        container = new COORDINATE*[rank], left = new int*[rank], right = new int*[rank];
        is_left = new bool*[rank];
        for (int i = 0; i < rank; ++i) {
            container[i] = new COORDINATE[length];
            left[i] = new int[length];
            right[i] = new int[length];
            is_left[i] = new bool[length];
        }
        for (int i = 0; i < length; ++i) {
            container[0][i].x = input[i];
            container[0][i].y = i;
        }
        for (int i = length; i < capacity; ++i) {
            container[0][i].x = 0;
            container[0][i].y = capacity;
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
        int now = start;
        int l_index = start, r_index = middle;
        while (now <= finish) {

            left[height][now] = l_index;
            right[height][now] = r_index;

            if (l_index < middle && (r_index > finish || container[height-1][l_index].y < container[height-1][r_index].y)) {
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

    int query(int start, int finish, int k) {
        return query(rank-1, start, finish, k);
    }

    int query(int height, int start, int finish, int k) {
        if (height == 0) return container[height][start].x;
        int size = left[height][finish] - left[height][start];
        if (is_left[height][finish]) ++size;
        if (size >= k) return query(height-1, left[height][start], min(left[height][finish], left[height][start]/(1<<(height-1))*(1<<(height-1))+(1<<(height-1))-1), k);
        else return query(height-1, right[height][start], min(right[height][finish], right[height][start]/(1<<(height-1))*(1<<(height-1))+(1<<(height-1))-1), k-size);
    }

    void print() {
        for (int i = rank-1; i >= 0; --i) {
            for (int j = 0; j < capacity; ++j) {
                cout << this->container[i][j].x << ":" << this->container[i][j].y << " ";
            }
            cout << endl;
        }
        cout << "====" << endl;
        for (int i = rank-1; i >= 0; --i) {
            for (int j = 0; j < capacity; ++j) {
                cout << this->left[i][j] << ":" << this->right[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main () {
    int input[] = {1, 2, 3, 4, 5, 6, 7};
    RangeTree2D range;
    range.init(input, 7);
    range.print();
    //for (int i = 0; i < 7; ++i) {
    //    for (int j = i+1; j < 7; ++j) {
    //        cout << i << " " << j << " " << 2 << ": " << range.query(i, j, 2) << endl;
    //    }
    //}
    //cout << range.query(0, 3, 3) << endl;
    return 0;
}
