#pragma once
#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <typename T>
class Relation {

    struct pair {
        T first;
        T second;
    };


private:
    vector<pair> elements;
    set<T> root;

public:
    Relation();
    Relation(const Relation<T>&);
    ~Relation();
    void add_to_set(T);
    int cardinality() const;
    bool add_element(T, T);
    void remove_element(T, T);
    bool is_member(T, T);
    bool operator ==(Relation<T>);
    vector<T> operator [](T);
    bool reflexive();
    bool irreflexive();
    bool symmetric();
    bool asymmetric();
    bool transitive();
    bool is_function();
    Relation<T> inverse();
    Relation<T> combination(Relation<T>);
    template<typename R> friend ostream& operator <<(ostream&, Relation<R>);
};