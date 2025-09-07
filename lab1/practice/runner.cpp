// runner.cpp
#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

#ifdef _WIN32
const string USER_EXE = "baie.exe";   // Solver build từ bt_test.cpp
#else
const string USER_EXE = "baie";       // nhớ chmod +x nếu cần
#endif

// ================== Cấu hình ==================
static const long double EPS_PARSE  = 1e-9L;   // ngưỡng chuẩn hoá 0.0
static const long double EPS_EQUAL  = 1e-6L;   // sai số so sánh nghiệm
static const long double EPS_DELTA  = 1e-9L;   // sai số cho delta
static const long double EPS_FIX    = 1e-12L;  // ngưỡng xoá -0 -> 0 khi normalize
static const bool         STRICT_N  = false;    // bật strict: n phải đúng số nghiệm phân biệt

// ================== Tiện ích hệ thống & I/O ==================
int run_user_prog(const string& exe, const string& infile, const string& outfile) {
#ifdef _WIN32
    string cmd = exe + " < " + infile + " > " + outfile;
#else
    string cmd = "./" + exe + " < " + infile + " > " + outfile;
#endif
    return system(cmd.c_str());
}

string slurp(const string& path) {
    ifstream f(path, ios::binary);
    if (!f) return "";
    return string((istreambuf_iterator<char>(f)), istreambuf_iterator<char>());
}

string normalize_ws(string s) {
    string t; t.reserve(s.size());
    bool in_ws = false;
    for (char c : s) {
        if (isspace((unsigned char)c)) {
            if (!in_ws) { t.push_back(' '); in_ws = true; }
        } else { t.push_back(c); in_ws = false; }
    }
    if (!t.empty() && t.front()==' ') t.erase(t.begin());
    if (!t.empty() && t.back()==' ') t.pop_back();
    return t;
}

// ================== Chuẩn hoá file output: xoá -0 -> 0 ==================
void normalize_output_file(const string& path) {
    ifstream fin(path, ios::binary);
    if (!fin) return;
    string s((istreambuf_iterator<char>(fin)), istreambuf_iterator<char>());
    fin.close();

    static const regex rgx(R"([+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)");

    string out; out.reserve(s.size());
    size_t last = 0;
    for (auto it = sregex_iterator(s.begin(), s.end(), rgx);
         it != sregex_iterator(); ++it) {
        auto m = *it;
        out.append(s, last, m.position() - last);
        long double val = 0.0L;
        try { val = stold(m.str()); } catch(...) { val = 0.0L; }
        if (fabsl(val) <= EPS_FIX) out += "0";
        else out += m.str();
        last = m.position() + m.length();
    }
    out.append(s, last, string::npos);

    ofstream fout(path, ios::binary | ios::trunc);
    fout << out;
}

// ================== Xử lý số: parse / chuẩn hoá / gộp ==================
vector<long double> parse_numbers(const string& s) {
    static const regex rgx(R"([+-]?(?:\d+\.?\d*|\.\d+)(?:[eE][+-]?\d+)?)");
    vector<long double> v;
    for (auto it=sregex_iterator(s.begin(), s.end(), rgx);
         it!=sregex_iterator(); ++it) {
        v.push_back(stold((*it).str()));
    }
    return v;
}

// Chuẩn hoá -0.0 -> 0.0 (và mọi số rất nhỏ thành 0.0)
inline long double norm0(long double x) {
    return (fabsl(x) <= EPS_PARSE) ? 0.0L : x;
}

// Gộp nghiệm trùng (bao gồm -0/+0) theo sai số eps
vector<long double> dedup_numbers(vector<long double> v, long double eps = EPS_EQUAL) {
    for (auto &x : v) x = norm0(x);
    sort(v.begin(), v.end());
    vector<long double> u;
    for (auto x : v) {
        if (u.empty() || fabsl(x - u.back()) > eps) u.push_back(x);
        else u.back() = norm0((u.back() + x) / 2.0L); // làm mượt
    }
    return u;
}

// So sánh hai output dạng text: ưu tiên so sánh số học (gộp nghiệm), fallback text
bool compare_outputs(const string& got, const string& exp,
                     long double eps = EPS_EQUAL) {
    auto a = parse_numbers(got);
    auto b = parse_numbers(exp);

    if (!a.empty() || !b.empty()) {
        // Nếu hai bên đều có số: bỏ qua token "n" đầu tiên nếu có, chỉ so nghiệm
        vector<long double> ra = (a.size() >= 2)
                                 ? vector<long double>(a.begin()+1, a.end())
                                 : vector<long double>{};
        vector<long double> rb = (b.size() >= 2)
                                 ? vector<long double>(b.begin()+1, b.end())
                                 : vector<long double>{};

        ra = dedup_numbers(ra, eps);
        rb = dedup_numbers(rb, eps);

        if (ra.size() != rb.size()) return false;
        for (size_t i=0; i<ra.size(); ++i)
            if (fabsl(ra[i] - rb[i]) > eps) return false;
        return true;
    }
    // Không parse được số: so sánh text chuẩn hoá khoảng trắng
    return normalize_ws(got) == normalize_ws(exp);
}

// ================== ORACLE: nghiệm thực của ax^4 + b x^2 + c = 0 ==================
vector<long double> oracle_roots(long double a, long double b, long double c, bool &isInf) {
    isInf = false;
    vector<long double> roots;
    auto add=[&](long double x){
        for (auto r: roots) if (fabsl(r-x) <= EPS_EQUAL/10) return;
        roots.push_back(x);
    };

    // Vô số nghiệm
    if (fabsl(a)<=EPS_DELTA && fabsl(b)<=EPS_DELTA && fabsl(c)<=EPS_DELTA) {
        isInf = true; return roots;
    }

    // a == 0 => b x^2 + c = 0
    if (fabsl(a) <= EPS_DELTA) {
        if (fabsl(b) <= EPS_DELTA) {
            // c != 0 => vô nghiệm thực
            return roots;
        }
        long double y = -c / b;
        if (y > EPS_DELTA) {
            long double s = sqrtl(max((long double)0, y));
            add(-s); add(+s);
        } else if (fabsl(y) <= EPS_DELTA) {
            add(0.0L);
        }
        roots = dedup_numbers(roots, EPS_EQUAL);
        return roots;
    }

    // ax^4 + bx^2 + c = 0 => a y^2 + b y + c = 0, y = x^2
    long double D = b*b - 4*a*c;
    if (D < -EPS_DELTA) return roots;
    if (fabsl(D) <= EPS_DELTA) D = 0.0L;

    auto handle_y = [&](long double y){
        if (y > EPS_DELTA) {
            long double s = sqrtl(max((long double)0, y));
            add(-s); add(+s);
        } else if (fabsl(y) <= EPS_DELTA) {
            add(0.0L);
        }
    };

    if (D > 0) {
        long double sD = sqrtl(max((long double)0, D));
        long double y1 = (-b + sD) / (2*a);
        long double y2 = (-b - sD) / (2*a);
        handle_y(y1); handle_y(y2);
    } else { // D == 0
        long double y = -b / (2*a);
        handle_y(y);
    }

    roots = dedup_numbers(roots, EPS_EQUAL);
    return roots;
}

// Trích chỉ số k từ tên "baie_t{k}.inp"
optional<int> extract_index(const string& filename) {
    static const regex rgx(R"(baie_t(\d+)\.inp$)");
    smatch m;
    if (regex_search(filename, m, rgx)) return stoi(m[1].str());
    return nullopt;
}

// ================== Main ==================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Quét tất cả file input
    vector<pair<int,string>> tests; // (k, path)
    for (auto& p : fs::directory_iterator(fs::current_path())) {
        if (!p.is_regular_file()) continue;
        string name = p.path().filename().string();
        if (auto idx = extract_index(name)) tests.push_back({*idx, name});
    }
    if (tests.empty()) {
        cerr << "Không tìm thấy file 'baie_t*.inp' trong thư mục hiện tại.\n";
        return 1;
    }
    sort(tests.begin(), tests.end());

    int passed = 0;
    for (auto [k, inFile] : tests) {
        string gotFile = "got" + to_string(k) + ".txt";
        string expFile = "out" + to_string(k) + ".txt";

        // Chạy solver
        int rc = run_user_prog(USER_EXE, inFile, gotFile);
        if (rc != 0) {
            cerr << "[FAIL] Test " << k << " (" << inFile << ") rc=" << rc << "\n";
            return 2;
        }

        // Chuẩn hoá file output (xoá -0 -> 0)
        normalize_output_file(gotFile);

        // Có expected -> so sánh file
        if (fs::exists(expFile)) {
            string got = slurp(gotFile);
            string exp = slurp(expFile);
            if (!compare_outputs(got, exp, EPS_EQUAL)) {
                cerr << "[WRONG] Test " << k << ": khác " << expFile << "\n";
#ifdef _WIN32
                cerr << "Gợi ý: fc " << expFile << " " << gotFile << "\n";
#else
                cerr << "Gợi ý: diff -u " << expFile << " " << gotFile << "\n";
#endif
                return 3;
            }

            // STRICT_N cũng áp cho trường hợp có expected (tuỳ chọn)
            if (STRICT_N) {
                auto numsGot = parse_numbers(got);
                if (!numsGot.empty()) {
                    int nDecl = (int)llround(numsGot[0]);
                    vector<long double> rootsGot =
                        (numsGot.size() >= 2) ? vector<long double>(numsGot.begin()+1, numsGot.end())
                                              : vector<long double>{};
                    rootsGot = dedup_numbers(rootsGot, EPS_EQUAL);
                    if (nDecl != (int)rootsGot.size()) {
                        cerr << "[WRONG] Test " << k << ": bạn in n=" << nDecl
                             << " nhưng số nghiệm phân biệt thực tế là "
                             << rootsGot.size() << " (mode strict).\n";
                        return 11;
                    }
                }
            }

            cout << "Test " << k << " OK (so với " << expFile << ")\n";
        }
        // Không có expected -> dùng oracle
        else {
            // Đọc a b c từ input
            ifstream fin(inFile);
            long double a,b,c;
            if (!(fin >> a >> b >> c)) {
                cerr << "[FAIL] Test " << k << ": không đọc được a b c từ " << inFile << "\n";
                return 4;
            }

            bool inf = false;
            vector<long double> gold = oracle_roots(a,b,c,inf);

            string out = slurp(gotFile);
            auto nums = parse_numbers(out);

            if (inf) {
                if (out.find("Infinite") == string::npos &&
                    out.find("INF") == string::npos) {
                    cerr << "[WRONG] Test " << k << ": mong đợi vô số nghiệm.\n";
                    return 5;
                }
                cout << "Test " << k << " OK (oracle: INF)\n";
            } else {
                if (nums.empty()) {
                    cerr << "[WRONG] Test " << k << ": không parse được số từ output.\n";
                    return 6;
                }

                // Lấy 'n' mà chương trình in ra (nếu có)
                int userDeclaredN = (int)llround(nums[0]);

                // Chỉ lấy các nghiệm sau 'n'
                vector<long double> userRoots =
                    (nums.size() >= 2) ? vector<long double>(nums.begin()+1, nums.end())
                                       : vector<long double>{};

                // Chuẩn hoá & gộp nghiệm (-0/+0 -> 0, nghiệm trùng -> 1)
                userRoots = dedup_numbers(userRoots, EPS_EQUAL);

                // ---- STRICT: n in ra phải khớp số nghiệm phân biệt thực tế
                if (STRICT_N && userDeclaredN != (int)userRoots.size()) {
                    cerr << "[WRONG] Test " << k << ": bạn in n=" << userDeclaredN
                         << " nhưng số nghiệm phân biệt thực tế là "
                         << userRoots.size() << ".\n";
                    return 7;
                }

                // So với oracle
                if (userRoots.size() != gold.size()) {
                    cerr << "[WRONG] Test " << k << ": số nghiệm sai (expect "
                         << gold.size() << ", got " << userRoots.size() << ").\n";
                    return 8;
                }
                for (size_t i=0; i<gold.size(); ++i) {
                    if (fabsl(gold[i] - userRoots[i]) > EPS_EQUAL) {
                        cerr << "[WRONG] Test " << k << ": nghiệm sai tại vị trí " << i << ".\n";
                        return 9;
                    }
                }

                // ---- STRICT: n in ra phải khớp số nghiệm oracle
                if (STRICT_N && userDeclaredN != (int)gold.size()) {
                    cerr << "[WRONG] Test " << k << ": bạn in n=" << userDeclaredN
                         << " nhưng oracle cho " << gold.size() << " nghiệm.\n";
                    return 10;
                }

                cout << "Test " << k << " OK (oracle)\n";
            }
        }
        ++passed;
    }

    cout << "=> PASS " << passed << "/" << tests.size() << " test.\n";
    return 0;
}
