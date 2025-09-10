#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1;
    }
    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        double y = -c / b;
        if (y < 0) return 0;
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;

    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);

    int count = 0;
    if (y1 >= 0) {
        x[count++] = sqrt(y1);
        x[count++] = -sqrt(y1);
    }
    if (y2 >= 0 && y2 != y1) {
        x[count++] = sqrt(y2);
        x[count++] = -sqrt(y2);
    }
    return count;
}

static const double EPS = 1e-9;

struct Case {
    double a,b,c;
    int expectedN;                 // -1, 0, 1, 2, 4
    vector<double> expectedRoots;  // used only when expectedN > 0
    const char* name;
};

bool equalD(double u, double v){
    if (fabs(u) < EPS) u = 0;  // normalize -0
    if (fabs(v) < EPS) v = 0;
    return fabs(u - v) <= 1e-7;
}

int main(){
    vector<Case> tests = {
        {0,0,0,  -1, {},            "T1 infinite"},
        {0,0,1,   0,  {},           "T2 no-solution"},
        {0,2,-8,  2,  {-2,2},       "T3 linear y>0"},
        {0,2,0,   1,  {0},          "T4 linear y=0  (should be 1)"},
        {0,2,8,   0,  {},           "T5 linear y<0"},
        {1,0,1,   0,  {},           "T6 quad Δ<0"},
        {1,2,1,   0,  {},           "T7 Δ=0 but y<0"},
        {1,-2,1,  2,  {-1,1},       "T8 Δ=0 y=1"},
        {1,0,0,   1,  {0},          "T9 y1=y2=0 (should be 1)"},
        {1,-5,4,  4,  {-2,-1,1,2},  "T10 two y>0"},
        {1,1,-2,  2,  {-1,1},       "T11 one y>0"},
        {1,3,2,   0,  {},           "T12 both y<0"}
    };

    int passed = 0;
    for (auto& tc : tests){
        double out[4] = {0,0,0,0};
        int n = solveQuartic(tc.a, tc.b, tc.c, out);

        bool ok = (n == tc.expectedN);

        if (n > 0) {
            // normalize and sort returned roots
            vector<double> got(out, out + n);
            for (double &v : got) if (fabs(v) < EPS) v = 0;
            sort(got.begin(), got.end());

            auto exp = tc.expectedRoots;
            sort(exp.begin(), exp.end());

            ok = ok && ((int)exp.size() == n);
            for (int i = 0; ok && i < n; ++i)
                if (!equalD(got[i], exp[i])) ok = false;

            cout << (ok ? "[PASS] " : "[FAIL] ");
            cout << tc.name << " | expectedN=" << tc.expectedN
                 << " gotN=" << n << " | got:";
            for (double v : got) cout << " " << v;
            cout << "\n";
        } else {
            // n == 0 or n == -1: just report the count check
            cout << (ok ? "[PASS] " : "[FAIL] ");
            cout << tc.name << " | expectedN=" << tc.expectedN
                 << " gotN=" << n << "\n";
        }

        passed += ok;
    }
    cout << "\nSummary: " << passed << "/" << (int)tests.size() << " passed\n";
    return 0;
}
