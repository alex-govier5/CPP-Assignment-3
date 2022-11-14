#include "MappingRelation.h"
#include <iostream>
#include <vector>
using namespace std;

template<typename A, typename B>
MappingRelation<A, B>::MappingRelation() {

}

template<typename A, typename B>
MappingRelation<A, B>::MappingRelation(const MappingRelation<A,B>& m) {
	
}

template<typename A, typename B>
MappingRelation<A, B>::~MappingRelation() {
	
}

template<typename A, typename B>
int MappingRelation<A, B>::cardinality() {
	return 0;
}

template<typename A, typename B>
bool MappingRelation<A, B>::add_element(pair p) {
	return true;
}

template<typename A, typename B>
void MappingRelation<A, B>::remove_element(pair p) {
	return;
}

template<typename A, typename B>
bool MappingRelation<A, B>::is_member(pair p) {
	return true;
}
template<typename A, typename B>
bool MappingRelation<A, B>::operator ==(MappingRelation<A, B> m) {
	return true;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::operator +(MappingRelation<A, B> m) {
	return *this;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::operator -(MappingRelation<A, B> m) {
	return *this;
}
template<typename A, typename B>
vector<A,B> MappingRelation<A, B>::operator [](int n) {
	return elements;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::intersection(MappingRelation<A, B> m) {
	return *this;
}

template<typename A, typename B>
bool MappingRelation<A, B>::is_function() {
	return true;
}

template<typename C, typename D>
ostream& operator <<(ostream& out, MappingRelation<C,D> m) {
	return out;
}





