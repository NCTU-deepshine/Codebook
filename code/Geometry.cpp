#include <iostream>
#include <cmath>
#include <vector>
#include <cstdio>
#include <algorithm>
#define EPS 1e-10
#define LEFT_TOP POS(1000, 1000)
#define NO_INTERSECT POS(-1234, -1234)
#define PARALLEL POS(-1001, -1001)
#define COLINE POS(1234, 1234)

using namespace std;

typedef double T;

class POS {
public:
    T x, y;
    POS(const T& x = 0, const T& y = 0) : x(x), y(y) {}
    POS(const POS& x) : x(x.x), y(x.y) {}

    bool operator==(const POS& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    POS& operator+=(const POS& rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    POS operator -() {
        POS tmp(-x, -y);
        return tmp;
    }

    double dist(const POS& rhs) const {
        T tmp_x = x-rhs.x, tmp_y = y-rhs.y;
        return sqrt(tmp_x*tmp_x+tmp_y*tmp_y);
    }

    friend ostream& operator<<(ostream& out, const POS& pos) {
        out << pos.x << " " << pos.y;
        return out;
    }
};

POS const operator+(const POS& lhs, const POS& rhs) {
    return POS(lhs) += rhs;
}

POS const operator-(const POS& lhs, const POS& rhs) {
    POS tmp = rhs;
    tmp = -tmp;
    return POS(lhs) += (tmp);
}

bool cmp(const POS& lhs, const POS& rhs) {
    return (lhs.x < rhs.x) || ( (lhs.x == rhs.x)&&(lhs.y < rhs.y) );
}

T cross(POS& o, POS& a, POS& b) {
    return (a.x-o.x)*(b.y-o.y) - (a.y-o.y)*(b.x-o.x);
}

void convex_hull(POS* points, POS* need, int n) {
    sort(points, points+n, cmp);
    int index = 0;
    for (int i = 0; i < n; ++i) {
        while (index >= 2 && cross(need[index-2], need[index-1], points[i]) <= 0) index--;
        need[index++] = points[i];
    }
    int half_point = index+1;
    for (int i = n-2; i >= 0; --i) {
        while (index >= half_point && cross(need[index-2], need[index-1], points[i]) <= 0) index--;
        need[index++] = points[i];
    } /* be careful that start point will appear in fisrt and last in need array */
}

class LINE {
public:
    POS start, end, vec;
    LINE(const T& st_x, const T& st_y, const T& ed_x, const T& ed_y) :
        start(st_x, st_y), end(ed_x, ed_y), vec(end - start) {}

    LINE(const POS& start, const POS& end) :
        start(start), end(end), vec(end - start) {}

    LINE(const POS& end) : /* start point is origin */
        start(0, 0), end(end), vec(end) {}

    LINE(const T a, const T b, const T c) : /* given line by ax+by+c = 0 */
        start(0, 0), end(0, 0), vec(-b, a) {
        if (a == 0) {
            start.y = end.y = -c/b;
            end.x = -b;
        }
        else if (b == 0) {
            start.x = end.x = -c/a;
            end.y = a;
        }
        else if (c == 0) {
            end.x = -b; end.y = a;
        }
        else {
            start.y = -c/b; end.x = -c/a;
            vec.x = -c/a; vec.y = c/b;
        }
    }

    LINE build_orthogonal(const POS& point) const {
        T c = -(vec.x*point.x + vec.y*point.y);
        return LINE(vec.x, vec.y, c);
    }

    T length2() const { /* square */
        T x = start.x - end.x, y = start.y - end.y;
        return x*x + y*y;
    }

    void modify(T x, T y) {
        this->end.x += x;
        this->end.y += y;
        this->vec.x += x;
        this->vec.y += y;
    }

    bool on_line(const POS& a) const {
        if (vec.x == 0) {
            if (start.x != a.x) return false;
            return true;
        }
        if (vec.y == 0) {
            if (start.y != a.y) return false;
            return true;
        }
        return ( (a.x-start.x)/vec.x*vec.y + start.y ) == a.y;
    }

    bool operator/(const LINE& rhs) const { /* to see if this line parallel to LINE rhs */
        return (vec.x*rhs.vec.y == vec.y*rhs.vec.x);
    }

    bool operator==(const LINE& rhs) const { /* to see if they are same line */
        return (*this/rhs) && (rhs.on_line(start));
    }

    POS intersect(const LINE& rhs) const {
        if (*this==rhs) return COLINE; /* return co-line */
        if (*this/rhs) return PARALLEL; /* return parallel */

        double A1 = vec.y, B1 = -vec.x, C1 = end.x*start.y - start.x*end.y;
        double A2 = rhs.vec.y, B2 = -rhs.vec.x, C2 = rhs.end.x*rhs.start.y - rhs.start.x*rhs.end.y;
        return POS( (B2*C1-B1*C2)/(A2*B1-A1*B2), (A1*C2-A2*C1)/(A2*B1-A1*B2) ); /* sometimes has -0 */
    }

    double dist(const POS& a) const {
        return fabs(vec.y*a.x - vec.x*a.y + vec.x*start.y - vec.y*start.x)/sqrt(vec.y*vec.y+vec.x*vec.x);
    }

    double dist(const LINE& rhs) const {
        POS intersect_point = intersect(rhs);
        if (intersect_point == PARALLEL) {
            return dist(rhs.start);
        }
        return 0;
    }

    friend ostream& operator<<(ostream& out, const LINE& line) {
        out << line.start << "-->" << line.end << " vec: " << line.vec << endl;
        return out;
    }
};

class LINESEG : public LINE {
public:
    LINESEG() : LINE(POS(0, 0)) {}
    LINESEG(const LINE& input) : LINE(input) {}
    LINESEG(const POS& start, const POS& end) : LINE(start, end) {}

    bool on_lineseg(const POS& a) const {
        if (!on_line(a)) return false;
        bool first, second;
        if (vec.x >= 0) first = (a.x >= start.x)&&(a.x <= end.x);
        else first = (a.x <= start.x)&&(a.x >= end.x);
        if (vec.y >= 0) second = (a.y >= start.y)&&(a.y <= end.y);
        else second = (a.y <= start.y)&&(a.y >= end.y);
        return first&&second;
    }

    bool operator==(const LINESEG& rhs) const {
        return ( (rhs.start == start && rhs.end == end) ||
              (rhs.start == end && rhs.end == start) );
    }

    bool operator==(const LINE& rhs) const {
        return this->LINE::operator==(rhs);
    }

    T dot(const LINESEG& rhs) const {
        return vec.x*rhs.vec.x + vec.y*rhs.vec.y;
    }
    
    T cross(const LINESEG& rhs) const {
        return vec.x*rhs.vec.y - vec.y*rhs.vec.x;
    }

    bool clockwise(const LINE& a) const { /* to see if LINE a is in b's clockwise way */
        return cross(a) > 0;
    }

    double dist(const POS& a) const {
        double ortho_dist = this->LINE::dist(a);
        LINE ortho_line = build_orthogonal(a);
        POS intersect_point = this->LINE::intersect(ortho_line);
        if (on_lineseg(intersect_point)) return ortho_dist;
        else return min(a.dist(this->start), a.dist(this->end));
    }

    double dist(const LINE& line) const {
        POS intersect_point = this->LINE::intersect(line);
        if (intersect_point == COLINE) return 0;
        if (intersect_point == PARALLEL) return dist(line.start);
        if (on_lineseg(intersect_point)) return 0;
        return min(line.dist(start), line.dist(end));
    }

    double dist(const LINESEG& line) const {
        return min( min(dist(line.start), dist(line.end)),
                    min(line.dist(start), line.dist(end)) );
    }

    POS intersect(const LINESEG& rhs) const {
        LINE a1b1(start, rhs.start);
        LINE a1b2(start, rhs.end);
        LINE b1a1(rhs.start, start);
        LINE b1a2(rhs.start, end);

        POS tmp(this->LINE::intersect(rhs));

        if (tmp == COLINE) { 
            if ( (start==rhs.start) && (!rhs.on_lineseg(end)) && (!on_lineseg(rhs.end)) ) return start;
            if ( (start==rhs.end) && (!rhs.on_lineseg(end)) && (!on_lineseg(rhs.start)) ) return start;
            if ( (end==rhs.start) && (!rhs.on_lineseg(start)) && (!on_lineseg(rhs.end)) ) return end;
            if ( (end==rhs.end) && (!rhs.on_lineseg(start)) && (!on_lineseg(rhs.start)) ) return end;
            if (on_lineseg(rhs.start) || on_lineseg(rhs.end) || rhs.on_lineseg(start) || rhs.on_lineseg(end)) return COLINE;
            return NO_INTERSECT;
        }

        bool intersected =  ( (cross(a1b1)*cross(a1b2)<0) && (rhs.cross(b1a1)*rhs.cross(b1a2)<0) );
        if (!intersected) return NO_INTERSECT;
        if (!on_lineseg(tmp) || !rhs.on_lineseg(tmp)) return NO_INTERSECT;
        return tmp;
    }
};

class POLYGON {
public:
    vector<POS> point;
    vector<LINE> line;

    void add_points(const POS& x) {
        point.push_back(x);
    }

    void add_points(const int& x, const int& y) {
        point.push_back(POS(x,y));
    }

    void build_line() {
        if (line.size() != 0) return; /* if it has build */
        for (int i = 1; i < point.size(); ++i) {
            line.push_back(LINE(point[i], point[i-1]));
        }
        line.push_back(LINE(point[0], point[point.size()-1]));
    }

    double area() {
        double ans = 0;

        vector<LINESEG> tmp;
        for (int i = 0; i < point.size(); ++i) {
            tmp.push_back(LINESEG(point[i]));
        }
        tmp.push_back(LINESEG(point[0]));

        for (int i = 1; i < tmp.size(); ++i) {
            ans += tmp[i-1].cross(tmp[i]);
        }
        return 0.5*fabs(ans);
    }

    bool in_polygon(const POS& a, const POS& left_top = LEFT_TOP) {
        
        for (int i = 0; i < point.size(); ++i) {
            if (a == point[i]) return true; /* a is polygon's point */
        }

        build_line();
        for (int i = 0; i < line.size(); ++i) {
            if (line[i].on_line(a)) {
                return true; /* a is on polygon's line */
            }
        }

        POS endpoint(left_top); /* should be modified according to problem */
        LINESEG ray(a, endpoint);
        bool touch_endpoint = false;
        do {
            touch_endpoint = false;
            for (int i = 0; i < point.size(); ++i) {
                if (ray.on_lineseg(point[i])) {
                    touch_endpoint = true;
                    break;
                }
            }
            if (touch_endpoint) ray.modify(-1, 0); /* should be modified according to problem */
        } while (touch_endpoint);

        int times = 0;
        for (int i = 0; i < line.size(); ++i) {
            POS tmp(ray.intersect(line[i]));
            if (tmp == NO_INTERSECT || tmp == PARALLEL) {
                continue;
            }
            ++times;
        }
        return (times&1);
    }
};

int main() {
    return 0;
}
