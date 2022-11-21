#include "MappingRelation.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

template<typename A, typename B>
MappingRelation<A, B>::MappingRelation() {
	//Nothing to set up
}

template<typename A, typename B>
MappingRelation<A, B>::MappingRelation(const MappingRelation<A, B>& m) {
	for (int i = 0; i < m.elements.size(); i++) {
		elements.push_back(m.elements[i]);
	}
	typename set<A>::iterator itr;
	for (itr = m.one.begin(); itr != m.one.end(); itr++) {
		one.insert(*itr);
	}
	typename set<B>::iterator itr2;
	for (itr2 = m.two.begin(); itr2 != m.two.end(); itr2++) {
		two.insert(*itr2);
	}
}

template<typename A, typename B>
MappingRelation<A, B>::~MappingRelation() {
	elements.clear();
	one.clear();
	two.clear();
}

template <typename A, typename B>
void MappingRelation<A, B>::add_to_setOne(A elem) {
	one.insert(elem);
}

template <typename A, typename B>
void MappingRelation<A, B>::add_to_setTwo(B elem) {
	two.insert(elem);
}

template<typename A, typename B>
int MappingRelation<A, B>::cardinality() {
	return elements.size();
}

template<typename A, typename B>
bool MappingRelation<A, B>::add_element(pair p) {
	if (one.find(p.first) == one.end() || two.find(p.second) == two.end()) {
		return false;
	}
	if (is_member(p)) {
		return false;
	}
	elements.push_back(p);
	return true;
}

template<typename A, typename B>
void MappingRelation<A, B>::remove_element(pair p) {
	if (cardinality() == 0) {
		return;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == p.first && elements[i].second == p.second) {
			elements.erase(i);
		}
	}
	return;
}

template<typename A, typename B>
bool MappingRelation<A, B>::is_member(pair p) {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == p.first && elements[i].second == p.second) {
			return true;
		}
	}
	return false;
}

template<typename A, typename B>
bool MappingRelation<A, B>::operator ==(MappingRelation<A, B> m) {
	if (cardinality() != m.cardinality()) {
		return false;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (!is_member(m.elements[i])) {
			return false;
		}
	}
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
vector<A, B> MappingRelation<A, B>::operator [](int n) {
	vector<A, B> result;
	result.push_back(elements[n].first);
	result.push_back(elements[n].second);
	return result;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::intersection(MappingRelation<A, B> m) {
	return *this;
}

template<typename A, typename B>
bool MappingRelation<A, B>::is_function() {
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < cardinality(); j++) {
			if (elements[j].first == elements[i].first && elements[j].second != elements[i].second) {
				return false;
			}
		}
	}
	return true;
}

template<typename C, typename D>
ostream& operator <<(ostream& out, MappingRelation<C, D> m) {
	out << "{ ";
	for (int i = 0; i < m.cardinality() - 1; i++) {
		out << "(" << m.elements[i].first << ", " << m.elements[i].second << "), ";
	}
	out << "(" << m.elements[m.cardinality() - 1].first << ", " << m.elements[m.cardinality() - 1].second << ") ";
	out << "}";
	return out;
}