#include <map>
#include <iostream>
#include <string.h>
#include <vector>
#include <set>
#include <utility>
#include <math.h>
#include <string.h>

using namespace std;

template <typename T>
struct elem {
    T inf;
    elem<T>* link;
};

template <typename T = int>
class queue
{public:
    queue();
    ~queue();
    queue(const queue&);
    queue& operator=(const queue&);
    
    
    int length() const;
    bool empty() const;
    T& front() const;
    void print() const;
    void insert(const T&);
    T& remove();
    
    
private:
    void copy(const queue&);
    void del();
    elem<T> *first;
    elem<T> *last;
    int size;
};

template <typename T>
queue<T>::queue()
{
    first = last = NULL;
    size = 0;
}

template <typename T>
queue<T>::~queue()
{
    del();
}

template <typename T>
queue<T>::queue(const queue& r)
{
    copy(r);
}

template <typename T>
queue<T>& queue<T>::operator=(const queue<T> &r)
{
    if (this != &r) {
        del();
        copy(r);
    }
    return *this;
}

template <typename T>
void queue<T>::copy(const queue<T> &r)
{
    first = last = NULL;
    size = 0;
    elem<T> *q = r.first;

    while (q) {
        insert(q->inf);
        q = q->link;
    }
    size = r.size;
}

template <typename T>
void queue<T>::del()
{
    elem<T> *p;
    while (!empty()) {
        remove();
    }
    size = 0;
}

template <typename T>
bool queue<T>::empty() const
{
    return first == NULL;
}

template <typename T>
int queue<T>::length() const {
    return size;
}

template <typename T>
void queue<T>::insert(const T& val)
{
    elem<T> *p = new elem<T>;
    p->inf = val;
    p->link = NULL;
    if (last) {
        last->link = p;
    } else {
        first = p;
    }
    last = p;
    size++;
}

template <typename T>
T& queue<T>::remove()
{
    if (first == NULL) {
        throw runtime_error("The queue is empty");
    }
    elem<T> *p = first;
    T result = p->inf;
    if (p == last) {
        first = last = NULL;
        size = 0;
    } else {
        first = first->link;
        size--;
    }
    delete p;
    return result;
}

template <typename T>
void queue<T>::print() const
{
    elem<T> *p = first;
    while (p) {
        cout << p->inf << " ";
        p = p->link;
    }
    cout << endl;
}

int main()
{
    queue<int> *q = new queue<int>();
    q->insert(1);
    q->insert(2);
    q->insert(3);
    
    q->print();
    q->remove();
    q->print();
    return 0;
}
