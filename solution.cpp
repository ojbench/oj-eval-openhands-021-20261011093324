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
    int original_idx;
    
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
        points[i].original_idx = i;
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
    
    // Map original index to sorted position
    vector<int> pos_in_sorted(n);
    for (int i = 0; i < n; i++) {
        pos_in_sorted[points[i].original_idx] = i;
    }
    
    long long total_rectangles = 0;
    
    // Process each point as potential bottom-left corner
    for (int i = 0; i < n; i++) {
        int y1 = points[i].y;
        int y1_idx = y_to_idx[y1];
        
        FenwickTree bit(y_coords.size());
        
        // Add all points to the right of current point
        for (int j = i + 1; j < n; j++) {
            int y2 = points[j].y;
            int y2_idx = y_to_idx[y2];
            
            if (y2 > y1) {
                // Check if there are any points between y1 and y2
                int points_between = bit.range_query(y1_idx + 1, y2_idx - 1);
                
                if (points_between == 0) {
                    // This forms a valid rectangle
                    total_rectangles++;
                }
            }
            
            // Add current point to BIT
            bit.update(y2_idx, 1);
        }
    }
    
    cout << total_rectangles << endl;
    
    return 0;
}