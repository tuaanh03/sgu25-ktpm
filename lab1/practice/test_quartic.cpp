#include <bits/stdc++.h>
using namespace std;

// --- Khai báo lại solveQuartic giống hệt bản của bạn (hoặc include từ file nguồn) ---
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

// --- Tiện ích so sánh nghiệm ---
static const double EPS = 1e-7;

bool almostEqual(double u, double v, double eps = EPS) {
    return fabs(u - v) <= eps;
}

// Chuẩn hóa nghiệm: gộp -0.0 thành 0.0
double normZero(double x) {
    if (fabs(x) <= EPS) return 0.0;
    return x;
}

// Loại bỏ cặp ±0 trùng nhau (đếm 0 là 1 nghiệm)
vector<double> dedupZerosAndSort(vector<double> v) {
    for (double &t : v) t = normZero(t);
    sort(v.begin(), v.end());
    vector<double> out;
    for (double val : v) {
        if (out.empty() || !almostEqual(out.back(), val)) out.push_back(val);
    }
    return out;
}

struct TestCase {
    string name;
    double a, b, c;
    int expectType; // -1: infinite; 0: none; >0: has solutions
    vector<double> expectRoots; // nghiệm thực khác nhau mong đợi (đã gộp 0)
};

int main() {
    vector<TestCase> cases = {
        {"T1", 0, 0, 0, -1, {}},
        {"T2", 0, 0, 5, 0, {}},
        {"T3", 0, 2, -8, 1, {-2, 2}},
        {"T4", 0, 2, 0, 1, {0}},            // y=0 → 1 nghiệm 0
        {"T5", 0, 2, 8, 0, {}},
        {"T6", 1, 0, 1, 0, {}},
        {"T7", 1, -2, 1, 1, {-1, 1}},
        {"T8", 1, -5, 4, 1, {-2, -1, 1, 2}},
        {"T9", 1, 0, -1, 1, {-1, 1}},
        {"T10",1, 0, 0, 1, {0}},            // x^4 = 0 → 1 nghiệm 0
    };

    bool allPass = true;

    for (auto &tc : cases) {
        double roots[8] = {0};
        int n = solveQuartic(tc.a, tc.b, tc.c, roots);

        // Quy đổi output của chương trình về dạng "nghiệm khác nhau"
        vector<double> got;
        if (n > 0) {
            for (int i = 0; i < n; ++i) got.push_back(roots[i]);
            got = dedupZerosAndSort(got); // gộp 0, sort và dedup
        }

        bool pass = true;
        if (tc.expectType == -1) {
            pass = (n == -1);
        } else if (tc.expectType == 0) {
            // Chấp nhận n==0 là không nghiệm (đúng)
            pass = (n == 0);
        } else {
            // Có nghiệm thực khác nhau
            // Yêu cầu got == expectRoots về kích thước và giá trị (không phân biệt thứ tự)
            auto want = dedupZerosAndSort(tc.expectRoots);
            pass = (got.size() == want.size());
            if (pass) {
                for (size_t i = 0; i < want.size(); ++i) {
                    if (!almostEqual(got[i], want[i])) { pass = false; break; }
                }
            }
        }

        cout << tc.name << ": " << (pass ? "PASS" : "FAIL") << "\n";
        if (!pass) {
            allPass = false;
            cout << "  Input: a=" << tc.a << " b=" << tc.b << " c=" << tc.c << "\n";
            cout << "  Program n=" << n << ", roots = ";
            for (int i = 0; i < n; ++i) cout << roots[i] << " ";
            cout << "\n  Expect type=" << tc.expectType << ", roots = ";
            for (double r : tc.expectRoots) cout << r << " ";
            cout << "\n";
        }
    }

    cout << (allPass ? "==> ALL TESTS PASSED\n" : "==> SOME TESTS FAILED\n");
    return allPass ? 0 : 1;
}
