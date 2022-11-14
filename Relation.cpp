#include "Relation.h"
#include <iostream>
#include <vector>
using namespace std;

template <typename T>
Relation<T>::Relation() {
	
}

template <typename T>
Relation<T>::Relation(const Relation<T>& r) {

}

template <typename T>
Relation<T>::~Relation() {
	
}

template<typename T>
int Relation<T>::cardinality() {
	return 0;
}

template<typename T>
bool Relation<T>::add_element(pair elem) {
	return true;
}
template<typename T>
void Relation<T>::remove_element(pair elem) {
	return;
}

template<typename T>
bool Relation<T>::is_member(pair elem) {
	return true;
}

template<typename T>
bool Relation<T>::operator ==(Relation<T> r) {
	return true;
}

template<typename T>
vector<T> Relation<T>::operator [](int n){
	return elements;
}

template<typename T>
bool Relation<T>::reflexive() {
	return true;
}

template<typename T>
bool Relation<T>::irreflexive() {
	return true;
}

template<typename T>
bool Relation<T>::symmetric() {
	return true;
}

template<typename T>
bool Relation<T>::asymmetric() {
	return true;
}
template<typename T>
bool Relation<T>::transitive() {
	return true;
}

template<typename T>
bool Relation<T>::is_function() {
	return true;
}

template<typename T>
Relation<T> Relation<T>::inverse() {
	return *this;
}
template<typename T>
Relation<T> Relation<T>::combination(Relation<T> r) {
	return *this;
}

template<typename R>
ostream& operator <<(ostream& out, Relation<R> r) {
	return out;
}

int main() {


}

