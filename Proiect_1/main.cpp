#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

ifstream fin ("date.in");

bool check(vector<int> v, int n)
{
    for(int i = 0; i < n-1; ++i)
        if(v[i] > v[i+1]) return 0;
    return 1;
}

vector<int> bubble_sort(vector<int> v, int n)
{
    int m = n;
    bool ok;
    do
    {
        ok = 1;
        for(int i = 0; i < m-1; ++i)
            if(v[i] > v[i+1])
            {
                swap(v[i], v[i+1]);
                ok = 0;
            }
    } while(!ok);
    return v;
}

vector<int> count_sort(vector<int> v, int n, int Max)
{
    int f[Max+1] = {0};
    for(int i = 0; i < n; ++i) f[v[i]]++;
    vector<int> aux;
    for(int i = 0; i <= Max; ++i)
        while(f[i]--) aux.push_back(i);
    return aux;
}

void quick_sort(vector<int> &v, int st, int dr)
{
    int i = st, j = dr;
    int x = v[rand()% (dr-st+1) + st];
    while(i < j)
    {
        while(v[i] < x) i++;
        while(v[j] > x) j--;
        if(i <= j) swap(v[i++], v[j--]);
    }
    if(j > st) quick_sort(v, st, j);
    if(i < dr) quick_sort(v, i, dr);
}

void Merge(vector<int> &v, int st, int mij, int dr)
{
    int i = st, j = mij+1, l = 1;
    vector<int> aux;
    while(i <= mij && j <= dr)
        if(v[i] < v[j]) aux.push_back(v[i++]);
        else aux.push_back(v[j++]);
    while(i <= mij) aux.push_back(v[i++]);
    while(j <= dr) aux.push_back(v[j++]);
    for(int i = st; i <= dr; ++i) v[i] = aux[i-st];
}
void merge_sort(vector<int> &v, int st, int dr)
{
    if(dr > st)
    {
        int mij = (st+dr)/2;
        merge_sort(v, st, mij);
        merge_sort(v, mij+1, dr);
        Merge(v, st, mij, dr);
    }
}

void radix_sort256(vector<int> &v, int n)
{
    queue<int> q[256];
    int k;
    for(int i = 0; i <= 24; i += 8)
    {
        for(int j = 0; j < n; ++j)
            q[(v[j]>>i)&255].push(v[j]);
        k = 0;
        for(int j = 0; j <= 255 && k < n; ++j)
            while(!q[j].empty())
            {
                v[k++] = q[j].front();
                q[j].pop();
            }
    }
}
void radix_sort16(vector<int> &v, int n)
{
    queue<int> q[16];
    int k;
    for(int i = 0; i <= 24; i += 4)
    {
        for(int j = 0; j < n; ++j)
            q[(v[j]>>i)&15].push(v[j]);
        k = 0;
        for(int j = 0; j <= 15 && k < n; ++j)
            while(!q[j].empty())
            {
                v[k++] = q[j].front();
                q[j].pop();
            }
    }
}

int main()
{
    vector <int> v;
    int T;
    fin >> T;
    for(int t = 1; t <= T; ++t)
    {
        v.clear();
        int n, maxVal;
        fin >> n >> maxVal;
        for(int i = 0, x; i < n; ++i) v.push_back(rand() % maxVal + 1);
        vector<int> aux;

        cout << "TESTUL " << t << " (n = " << n << " maxValue = " << maxVal << ")" << '\n';

        if(n > 10000) cout << "Bubble Sort: FAILED ... n is too large!\n";
        else
        {
            auto start = high_resolution_clock::now();
            aux = bubble_sort(v, n);
            auto stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Bubble Sort: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Bubble Sort: FAILED :(\n";
        }

        if(maxVal >= 1000000) cout << "Count Sort: FAILED ... maxValue is too large!\n";
        else if(n >= 100000000) cout << "Count Sort: FAILED ... n is too large!\n";
        else
        {
            auto start = high_resolution_clock::now();
            aux = count_sort(v, n, maxVal);
            auto stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Count Sort: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Count Sort: FAILED :(\n";
        }

        if(n >= 100000000) cout << "Quick Sort: FAILED ... n is too large!\n";
        else
        {
            aux = v;
            auto start = high_resolution_clock::now();
            quick_sort(aux, 0, n-1);
            auto stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Quick Sort: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Quick Sort: FAILED :(\n";
        }

        if(n >= 10000000) cout << "Merge Sort: FAILED ... n is too large!\n";
        else
        {
            aux = v;
            auto start = high_resolution_clock::now();
            merge_sort(aux, 0, n-1);
            auto stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Merge Sort: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Merge Sort: FAILED :(\n";
        }

        if(n >= 100000000) cout << "Radix Sort: FAILED ... n is too large!\n";
        else
        {
            /// Radix Sort in baza 256
            aux = v;
            auto start = high_resolution_clock::now();
            radix_sort256(aux, n);
            auto stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Radix Sort base 256: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Radix Sort base 256: FAILED :(\n";
            /// Radix Sort in baza 16
            aux = v;
            start = high_resolution_clock::now();
            radix_sort16(aux, n);
            stop = high_resolution_clock::now();
            if(check(aux, n))
            {
                auto duration = duration_cast<milliseconds>(stop-start);
                cout << "Radix Sort base 16: SUCCESS ... " << duration.count() << " ms\n";
            }
            else cout << "Radix Sort base 16: FAILED :(\n";
        }

        if(n >= 100000000) cout << "STL Sort: FAILED ... n is too large!\n";
        else
        {
            aux = v;
            auto start = high_resolution_clock::now();
            sort(aux.begin(), aux.end());
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop-start);
            cout << "Native(STL) Sort: SUCCESS ... " << duration.count() << " ms\n";
        }

        cout << "/-----------------------------/\n";
    }
    return 0;
}
