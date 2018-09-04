#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <list>

using namespace std;


/*
 Задача 2.(25min)Напишете функция, която получава като аргумент свързан списък с елементи цели числа и го сортира. Списъкът е представен и подаден на функцията по избран от вас начин.Напишете кратка програма, която създава списък, добавя в него няколко елемента, използва функцията за сортиране и извежда на екрана резултата.Използвайтеезиците JAVA, C или C++, но безбиблиотечни структури данни и алгоритми.
 */

template <typename T>
struct elem {
    T inf;
    elem<T>* link;
};

template <typename T>
class linked_list
{public:
    linked_list();
    ~linked_list();
    linked_list(const linked_list&);
    linked_list& operator=(const linked_list&);
    void insertBefore(elem<T>*, const T&);
    void insertAfter(elem<T>*, const T&);
    void deleteBefore(elem<T>*, const T&);
    void deleteAfter(elem<T>*, const T&);
    void deleteElem(elem<T>*, const T&);
    
    void iterStart(elem<T>* = NULL);
    elem<T>* iter();
    void toEnd(const T&);
    
    int length() const;
    bool empty() const;
    void concat(const linked_list&);
    void print() const;
    
private:
    elem<T> *start, *end, *current;
    int size;
    
    void copyList(const linked_list&);
    void delList();
};

template <typename T>
linked_list<T>::linked_list()
{
    start = end = NULL;
    size = 0;
}

template <typename T>
linked_list<T>::~linked_list()
{
    delList();
}

template <typename T>
linked_list<T>::linked_list(const linked_list& another)
{
    copyList(another);
}

template <typename T>
linked_list<T>& linked_list<T>::operator=(const linked_list<T>& another)
{
    if (this != &another) {
        delList();
        copyList(another);
    }
    return *this;
}

template <typename T>
void linked_list<T>::copyList(const linked_list<T>& another)
{
    start = end = current = NULL;
    elem<T> *p = another.start;
    
    while (p) {
        toEnd(p->inf);
        p = p->link;
    }
    size = another.size;
}

template <typename T>
void linked_list<T>::delList()
{
    elem<T> *p;
    while (start) {
        p = start;
        start = start->link;
        delete p;
    }
    end = NULL;
    size = 0;
}

template <typename T>
void linked_list<T>::iterStart(elem<T>* p)
{
    if (p) {
        current = p;
    }
    current = start;
}

template <typename T>
elem<T>* linked_list<T>::iter()
{
    elem<T> *result = current;
    if (current) {
        current = current->link;
    }
    return result;
}

template <typename T>
void linked_list<T>::toEnd(const T& val)
{
    elem<T> *p = end;
    end = new elem<T>;
    end->inf = val;
    end->link = NULL;
    if (p) {
        p->link = end;
    } else {
        start = end;
    }
    size++;
}

template <typename T>
void linked_list<T>::insertAfter(elem<T> *el, const T& val)
{
    elem<T> *p = new elem<T>;
    p->inf = val;
    p->link = el->link;
    
    el->link = p;
    if (el == end) {
        end = p;
    }
    size++;
}

template <typename T>
void linked_list<T>::insertBefore(elem<T> *p, const T& val)
{
    elem<T> *q = new elem<T>;
    *q = *p;
    p->inf = val;
    p->link = q;
    size++;
}

template <typename T>
void linked_list<T>::deleteAfter(elem<T> *p, const T& val)
{
    if (p->link) {
        elem<T> *q = p->link;
        val = q->inf;
        p->link = q->link;
        if (q == end) {
            end = p;
        }
        delete q;
        size--;
    }
}


template <typename T>
void linked_list<T>::deleteElem(elem<T> *p, const T& val)
{
    val = p->inf;
    if (p == start) {
        val = p->inf;
        if (start == end) {
            start = end = NULL;
            size = 0;
        } else {
            start = start->link;
            delete p;
            size--;
        }
    } else {
        elem<T> *q = start;
        while (q->link != p) {
            q = q->link;
        }
        deleteAfter(q, val);
    }
}

template <typename T>
void linked_list<T>::deleteBefore(elem<T> *p, const T& val)
{
    if (p != start) {
        elem<T> *q = start;
        while (q->link != p) {
            q = q->link;
        }
        deleteElem(q);
    } else {
        cout << "there's no element before p";
        exit(1);
    }
}


template <typename T>
bool linked_list<T>::empty() const
{
    return start == NULL;
}

template <typename T>
void linked_list<T>::concat(const linked_list& another) {
    elem<T> *p = another.start;
    while (p) {
        toEnd(p->inf);
        p = p->link;
    }
}

template <typename T>
int linked_list<T>::length() const {
    return size;
}

template <typename T>
void linked_list<T>::print() const {
    elem<T> *p = start;
    while (p) {
        cout << p->inf << " ";
        p = p->link;
    }
    cout << endl;
}

bool is_sorted(linked_list<int> list)
{
    list.iterStart();
    elem<int> *current = list.iter();

    while(current->link) {
        if (current->inf > current->link->inf) {
            return false;
        }
        current = current->link;
    }
    return true;
}


linked_list<int> transform(linked_list<linked_list<int>> list)
{
    linked_list<int> *result_list = new linked_list<int>();
    list.iterStart();
    elem<linked_list<int>> *current = list.iter();
    
    while (current) {
        if (is_sorted(current->inf)) {
            result_list->concat(current->inf);
        }
    }
    return *result_list;
}

void sort_arr(int arr[], int n)
{
    int tmp;
    for (int i = 0; i < n; i++) {
        int min = arr[i];
        int min_i = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_i = j;
            }
        }
        tmp = *(arr+i);
        *(arr+i) = *(arr+min_i);
        *(arr + min_i) = tmp;
    }
}

void sort(linked_list<int> *list)
{
    int *arr = new int[list->length()];
    list->iterStart();
    elem<int> *current = list->iter();
    
    int i = 0;
    while (current) {
        arr[i] = current->inf;

        current = current->link;
        i++;
    }
    sort_arr(arr, list->length());
    
    list->iterStart();
    current = list->iter();
    i = 0;
    while (current) {
        current->inf = arr[i];
        current = current->link;
        i++;
    }
}

int main()
{
    //linked_list<linked_list<int>> *list_of_lists = new linked_list<linked_list<int>>();
    // some example with this shit

    int arr[5] = {5,4,3,2,1};
    sort_arr(arr, 5);
    for (int i = 0; i < 5; i++) {
        // cout << arr[i] << endl;
    }

    linked_list<int> *list = new linked_list<int>();
    list->toEnd(5);
    list->toEnd(4);
    list->toEnd(3);
    list->toEnd(2);
    list->toEnd(1);
    
    sort(list);
    
    list->print();

    return 0;
}
