#include <iterator>
#include <iostream>
#include "sorted_vector_algo.h"
using namespace std;

using std::vector;
using namespace sorted_vector_algo;
//using std::lower_bound; //二分查找，在有序数组上时间复杂度为O(logn)
//using std::upper_bound;
/*
 *sort采用的是成熟的"快速排序算法"(目前大部分STL版本已经不是采用简单的快速排序，而是结合内插排序算法)。
 可以保证很好的平均性能、复杂度为n*log(n)，由于单纯的快速排序在理论上有最差的情况，性能很低，其最坏算法复杂度为n*n，
 但目前大部分的STL版本都已经在这方面做了优化。
 stable_sort采用的是"归并排序"，分派足够内存时，其算法复杂度为n*log(n), 否则其复杂度为n*log(n)*log(n)，
 其优点是会保持相等元素之间的相对位置在排序前后保持一致。
 * */

template <class T, class Compare = std::less<T> >
struct sorted_vector {
    vector<T> V;
    Compare cmp;

    typedef typename vector<T>::size_type size_type;
    typedef typename vector<T>::iterator iterator;
    typedef typename vector<T>::const_iterator const_iterator;
    typedef typename vector<T>::reference reference;
    typedef typename vector<T>::const_reference const_reference;   
    iterator begin() { return V.begin(); }
    iterator end() { return V.end(); }
    const_iterator begin() const { return V.begin(); }
    const_iterator end() const { return V.end(); }

    sorted_vector(const Compare& c = Compare()): V(), cmp(c) {}

    template <class InputIterator>
    sorted_vector(InputIterator first, InputIterator last,
                const Compare& c = Compare()): V(first, last), cmp(c)
    {
        std::sort(begin(), end(), cmp);
    }

    iterator insert(const T& t) {
        iterator i = sorted_vector_algo::lower_bound(begin(), end(), t, cmp);
        if (i == end() || cmp(t, *i))
            V.insert(i, t);
        return i;
    }
    iterator erase(const T& t) {
        iterator i = std::lower_bound(begin(), end(), t, cmp);
        iterator j = std::upper_bound(begin(), end(), t, cmp);

        return V.erase(i, j);
    }

    //针对多维索引的属性值查找，需提供自定义的比较方法。只能查找排序的属性值。
    template <typename _Tp, class _Compare> 
    const_iterator find(const _Tp& t, _Compare cmp) {
        const_iterator i = lower_bound(t, cmp);
        return (i == end() || cmp(t, *i)) ? end() : i;
    }

    template <typename _Tp, typename _Compare> 
    iterator lower_bound (const _Tp& val, _Compare cmp) {
        return  sorted_vector_algo::lower_bound(begin(), end(), val, cmp);
    }

    const_iterator find(const T& t) const {
        const_iterator i =  sorted_vector_algo::lower_bound(begin(), end(), t, cmp);
        return (i == end() || cmp(t, *i)) ? end() : i;
    }

    iterator lower_bound (const T& val) {
        return  sorted_vector_algo::lower_bound(begin(), end(), val, cmp);
    }
    iterator upper_bound (const T& val) {
        return  sorted_vector_algo::upper_bound(begin(), end(), val, cmp);
    }

    bool empty() const {
        return V.empty();
    }
    reference operator[] (size_type n) {
        return V[n];
    }
    const_reference operator[] (size_type n) const{
        return V[n];
    }

    std::size_t size(){
        return V.size();
    }
};
