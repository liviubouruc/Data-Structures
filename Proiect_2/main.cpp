#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin ("date.in");

class MinMaxHeap
{
    int dim;
    vector <int> heap;

    int level(int i)
    {
        int lvl = 0, pow = 1;
        while(pow <= i)
        {
            pow <<= 1;
            lvl++;
        }
        return lvl;
    }
    void pushDown(int i)
    {
        if(level(i) % 2 == 0) pushDownMin(i);
        else pushDownMax(i);
    }
    void pushDownMin(int m)
    {
        while(m*2 <= dim)
        {
            int i = m;
            int left_son = i*2, right_son = i*2+1;
            m = left_son;
            if(right_son <= dim)
                if(heap[m-1] > heap[right_son-1]) m = right_son;

            bool isGc = 0;
            if(left_son*2 <= dim)
            {
                if(heap[m-1] > heap[left_son*2-1]) m = left_son*2, isGc = 1;
                if(left_son*2+1 <= dim)
                    if(heap[m-1] > heap[left_son*2+1-1]) m = left_son*2+1, isGc = 1;
            }
            if(right_son*2 <= dim)
            {
                if(heap[m-1] > heap[right_son*2-1]) m = right_son*2, isGc = 1;
                if(right_son*2+1 <= dim)
                    if(heap[m-1] > heap[right_son*2+1-1]) m = right_son*2+1, isGc = 1;
            }

            if(isGc)
            {
                if(heap[m-1] < heap[i-1])
                {
                    swap(heap[m-1], heap[i-1]);
                    if(heap[m-1] > heap[m/2-1]) swap(heap[m-1], heap[m/2-1]);
                }
            }
            else if(heap[m-1] < heap[i-1]) swap(heap[m-1], heap[i]);
        }
    }
    void pushDownMax(int m)
    {
        while(m*2 <= dim)
        {
            int i = m;
            int left_son = i*2, right_son = i*2+1;
            m = left_son;
            if(right_son <= dim)
                if(heap[m-1] < heap[right_son-1]) m = right_son;

            bool isGc = 0;
            if(left_son*2 <= dim)
            {
                if(heap[m-1] < heap[left_son*2-1]) m = left_son*2, isGc = 1;
                if(left_son*2+1 <= dim)
                    if(heap[m-1] < heap[left_son*2+1-1]) m = left_son*2+1, isGc = 1;
            }
            if(right_son*2 <= dim)
            {
                if(heap[m-1] < heap[right_son*2-1]) m = right_son*2, isGc = 1;
                if(right_son*2+1 <= dim)
                    if(heap[m-1] < heap[right_son*2+1-1]) m = right_son*2+1, isGc = 1;
            }

            if(isGc)
            {
                if(heap[m-1] > heap[i-1])
                {
                    swap(heap[m-1], heap[i-1]);
                    if(heap[m-1] < heap[m/2-1]) swap(heap[m-1], heap[m/2-1]);
                }
            }
            else if(heap[m-1] > heap[i-1]) swap(heap[m-1], heap[i]);
        }
    }
    void pushUp(int i)
    {
        if(i != 1)
        {
            if(level(i) % 2 == 0)
            {
                if(heap[i-1] > heap[i/2-1])
                {
                    swap(heap[i-1], heap[i/2-1]);
                    pushUpMax(i/2);
                }
                else pushUpMin(i);
            }
            else
            {
                if(heap[i-1] < heap[i/2-1])
                {
                    swap(heap[i-1], heap[i/2-1]);
                    pushUpMin(i/2);
                }
                else pushUpMax(i);
            }
        }
    }
    void pushUpMin(int i)
    {
        if(i/4 && heap[i-1] < heap[i/4-1])
        {
            swap(heap[i-1], heap[i/4-1]);
            i = i/4;
        }
    }
    void pushUpMax(int i)
    {
        if(i/4 && heap[i-1] > heap[i/4-1])
        {
            swap(heap[i-1], heap[i/4-1]);
            i = i/4;
        }
    }
public:
    MinMaxHeap() : dim(0) {}
    void build(int n, vector <int> arr)
    {
        dim = n;
        heap = arr;
        for(int i = n/2; i >= 1; --i) pushDown(i);
    }
    void insert(int x)
    {
        dim++;
        heap.push_back(x);
        pushUp(dim);
    }
    void deleteMin()
    {
        if(dim == 1) dim = 0;
        else
        {
            heap[0] = heap[dim-1];
            dim--;
            pushDown(1);
        }
    }
    void deleteMax()
    {
        if(dim < 3) dim--;
        else
        {
            int Max;
            if(heap[2] > heap[3]) Max = 3;
            else Max = 4;
            heap[Max-1] = heap[dim-1];
            dim--;
            pushDown(Max);
        }
    }
    int getMin() const { return heap[0]; }
    int getMax() const
    {
        if(dim == 1) return heap[0];
        else if(dim == 2) return heap[1];
        else return max(heap[1], heap[2]);
    }
    int size() const { return dim; }
};

int main()
{
    MinMaxHeap myHeap;

    int nrop, var;
    fin >> nrop;
    while(nrop--)
    {
        fin >> var;
        if(var == 6)
        {
            int n;
            vector <int> aux;
            fin >> n;
            for(int i = 1, x; i <= n; ++i)
            {
                fin >> x;
                aux.push_back(x);
            }
            myHeap.build(n, aux);
        }
        else if(var == 1)
        {
            int x;
            fin >> x;
            myHeap.insert(x);
        }
        else if(var == 2)
        {
            if(!myHeap.size()) cout << "Heap-ul este gol!\n";
            else
            {
                myHeap.deleteMin();
                cout << "Am sters minimul!\n";
            }
        }
        else if(var == 3)
        {
            if(!myHeap.size()) cout << "Heap-ul este gol!\n";
            else
            {
                myHeap.deleteMax();
                cout << "Am sters maximul!\n";
            }
        }
        else if(var == 4)
        {
            if(!myHeap.size()) cout << "Heap-ul este gol!\n";
            else cout << "Minimul: " << myHeap.getMin() << '\n';
        }
        else if(var == 5)
        {
            if(!myHeap.size()) cout << "Heap-ul este gol!\n";
            else cout << "Maximul: " << myHeap.getMax() << '\n';
        }
    }
    return 0;
}
