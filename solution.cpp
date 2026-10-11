#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
private:
    int n;
    vector<int> tree;
    
public:
    FenwickTree(int size) : n(size), tree(size + 1, 0) {}
    
    void update(int idx, int delta) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] += delta;
        }
    }
    
    int query(int idx) {
        int sum = 0;
        for (; idx > 0; idx -= idx & -idx) {
            sum += tree[idx];
        }
        return sum;
    }
    
    int range_query(int l, int r) {
        if (l > r) return 0;
        return query(r) - query(l - 1);
    }
};

struct Point {
    int x, y;
    
    bool operator<(const Point& other) const {
        return x < other.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    if (!(cin >> n)) return 0;
    
    vector<Point> points(n);
    vector<int> y_coords(n);
    
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
        y_coords[i] = points[i].y;
    }
    
    // Compress y-coordinates
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());
    
    unordered_map<int, int> y_to_idx;
    for (size_t i = 0; i < y_coords.size(); i++) {
        y_to_idx[y_coords[i]] = static_cast<int>(i) + 1; // 1-indexed for BIT
    }
    
    // Sort points by x-coordinate
    sort(points.begin(), points.end());
    
    long long total_rectangles = 0;
    
    // Simple O(n^2) solution - check all pairs
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int y1 = points[i].y;
            int y2 = points[j].y;
            
            if (y2 > y1) {
                // Check if there are any points inside or on the boundary of the rectangle
                // formed by (x1,y1) and (x2,y2), excluding the corners themselves
                bool has_blocking = false;
                for (int k = i + 1; k < j; k++) {
                    int yk = points[k].y;
                    // Point k is inside or on boundary if y1 <= yk <= y2
                    if (y1 <= yk && yk <= y2) {
                        has_blocking = true;
                        break;
                    }
                }
                if (!has_blocking) {
                    total_rectangles++;
                }
            }
        }
    }
    
    cout << total_rectangles << endl;
    
    return 0;
}