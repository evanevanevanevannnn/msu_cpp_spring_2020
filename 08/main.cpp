#include "threadpool.h"
#include <iostream>
#include <assert.h>
#include <vector>
#include <cmath>

using namespace std;

const int width = 2560, height = 1440;
const int inf = 20;
vector <vector <int>> a;

ThreadPool pool(8), *calculator;
mutex _m;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void print() {
    
    vector<int> cnt(12);

    for (auto i : a) {
        for (auto j : i) {
            printf("%3d ", j);
            cnt[abs(j)]++;
        }
        cout << '\n';
    }
    // for (int i = 0; i < cnt.size(); ++i)
    //     cout << i << ' ' << cnt[i] << '\n';

    cout << "\n\n";
}

void mark() {
    for (int p = 6; pow(2, p - 1) <= width; ++p) {
        int n = min(width, pow(2, p));

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                int y = height * i / n,
                    x = width * j / n;
                if (a[y][x] == -inf)
                    a[y][x] = -p;
            }
    }
}

void func2(int n, int l_w, int r_w) {
    double a2, b2, a_2, b_2;

    for (int i = 0; i < height; ++i) {
        for (int j = l_w; j < r_w; ++j) {
            if (a[i][j] == -n) {

                a2 = 0, b2 = 0;
                for (int k = 0; k < 1000; ++k) {
                    a_2 = a2 * a2;
                    b_2 = b2 * b2;

                    b2 = 2 * a2 * b2;
                    a2 = a_2 - b_2;

                    if (a2 * a2 + b2 * b2 > 4)
                        break;
                }

                a[i][j] = 50;
            }
        }
    }
}

void func3() {
    for (auto &i : a)
        for (auto &j : i)
            j = -inf;

    mark();

    vector<future<void>> f;
    for (int i = log2(width); i > 0; --i)
        for (int n = 0; n < 8; ++n)
            f.push_back(calculator->exec(func2, i, width * n / 8, width * (n + 1) / 8)); 

    for (int i = f.size() - 1; i >= 0; --i) {
        f[i].wait();

        if ((i + 1) % 8 == 0)
            cout << "done " << 12 - (i + 1) / 8 << '\n';
    }
}

int main() {

    a.resize(height);
    for (auto &i : a)
        i.resize(width);

    calculator = new ThreadPool(100);

    auto begin = std::chrono::steady_clock::now();

    func3();

    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    cout << elapsed_ms << '\n';

    return 0;
}