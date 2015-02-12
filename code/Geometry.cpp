#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#define EPS 1e-10

using namespace std;

struct POS {
    int x, y;

    POS(const int& x, const int& y) : x(x), y(y) {}
    POS(const POS& x) : x(x.x), y(x.y) {}

    bool operator==(const POS& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

struct LINE {
    POS start, end, vec;

    LINE(const int& st_x, const int& st_y, const int& ed_x, const int& ed_y) :
        start(st_x, st_y), end(ed_x, ed_y), vec(end.x - start.x, end.y - start.y) {}

    LINE(const POS& start, const POS& end) :
        start(start), end(end), vec(end.x - start.x, end.y - start.y) {}

    LINE(const POS& end) : /* start point is origin */
        start(0, 0), end(end), vec(end.x - start.x, end.y - start.y) {}

    int length2() { /* square */
        int x = start.x - end.x, y = start.y - end.y;
        return x*x + y*y;
    }

    void modify(int x, int y) {
        this->end.x += x;
        this->end.y += y;
    }

};

struct POLYGON {
    vector<POS> point;
    vector<LINE> line;

    void add_points(const POS& x) {
        point.push_back(x);
    }

    void build_line() {
        if (line.size() != 0) return; /* if it has build */
        for (int i = 1; i < point.size(); ++i) {
            line.push_back(LINE(point[i], point[i-1]));
        }
        line.push_back(LINE(point[0], point[point.size()-1]));
    }
};

inline int A_dot_B(const LINE& a, const LINE& b) {
    return a.vec.x*b.vec.x + a.vec.y*b.vec.y;
}

inline int A_cross_B(const LINE& a, const LINE& b) {
    return a.vec.x*b.vec.y - a.vec.y*b.vec.x;
}

inline bool clockwise(const LINE& a, const LINE& b) { /* to see if LINE a is in b's clockwise way */
    return A_cross_B(a, b) > 0;
}

bool A_intersect_B(const LINE& a, const LINE& b) { /* if is intersect on end point, it will return false */
    LINE a1b1(a.start, b.start);
    LINE a1b2(a.start, b.end);
    LINE b1a1(b.start, a.start);
    LINE b1a2(b.start, a.end);
    return ( (A_cross_B(a, a1b1)*A_cross_B(a, a1b2)<0) && (A_cross_B(b, b1a1)*A_cross_B(b, b1a2)<0) );
}

double polygon_area(const POLYGON& polygon) {
    double ans = 0;

    vector<LINE> tmp;
    for (int i = 0; i < polygon.point.size(); ++i) {
        tmp.push_back(LINE(polygon.point[i]));
    }
    tmp.push_back(LINE(polygon.point[0]));

    for (int i = 1; i < tmp.size(); ++i) {
        ans += A_cross_B(tmp[i-1], tmp[i]);
    }
    return 0.5*fabs(ans);
}

bool on_line(const POS& a, LINE& b) {
    int ab1 = (a.x-b.start.x)*(a.x-b.start.x) + (a.y-b.start.y)*(a.y-b.start.y);
    int ab2 = (a.x-b.end.x)*(a.x-b.end.x) + (a.y-b.end.y)*(a.y-b.end.y);
    int b1b2 = b.length2();
    return ab1+ab2 == b1b2;
}

bool in_polygon(const POS& a, POLYGON& polygon) {
    for (int i = 0; i < polygon.point.size(); ++i) {
        if (a == polygon.point[i]) return false; /* a is polygon's point */
    }

    polygon.build_line();
    for (int i = 0; i < polygon.line.size(); ++i) {
        if (on_line(a, polygon.line[i])) return false; /* a is on polygon's line */
    }

    POS endpoint(100, 100); /* should be modified according to problem */
    LINE ray(a, endpoint);
    bool touch_endpoint = false;
    do {
        touch_endpoint = false;
        for (int i = 0; i < polygon.point.size(); ++i) {
            if (on_line(polygon.point[i], ray)) {
                touch_endpoint = true;
                break;
            }
        }
        if (touch_endpoint) ray.modify(1, 0); /* should be modified according to problem */
    } while (touch_endpoint);

    int times = 0;
    for (int i = 0; i < polygon.line.size(); ++i) {
        if (A_intersect_B(ray, polygon.line[i])) ++times;
    }

    return (times&1);
}

int main() {
    return 0;
}
