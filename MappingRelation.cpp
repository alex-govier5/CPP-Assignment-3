// Alex Govier 300174954
// Taj Loodu 300128141

#include "MappingRelation.h"
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
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

template<typename A, typename B>
int MappingRelation<A, B>::cardinality() {
	return elements.size();
}

template<typename A, typename B>
bool MappingRelation<A, B>::add_element(A one, B two) {
	pair p;
	p.first = one;
	p.second = two;
	if (is_member(one, two)) {
		return false;
	}
	elements.push_back(p);
	return true;
}

template<typename A, typename B>
void MappingRelation<A, B>::remove_element(A one, B two) {
	if (cardinality() == 0) {
		return;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == one && elements[i].second == two) {
			elements.erase(elements.begin() +i);
		}
	}
	return;
}

template<typename A, typename B>
bool MappingRelation<A, B>::is_member(A one, B two) {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == one && elements[i].second == two) {
			return true;
		}
	}
	return false;
}

template<typename A, typename B>
bool MappingRelation<A, B>::operator ==(MappingRelation<A, B> m) {
	for (int i = 0; i < cardinality(); i++) {
		if (!m.is_member(elements[i].first, elements[i].second)) {
			return false;
		}
	}
	for (int i = 0; i < m.cardinality(); i++) {
		if (!is_member(m.elements[i].first, m.elements[i].second)) {
			return false;
		}
	}
	return true;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::operator +(MappingRelation<A, B> m) {
	MappingRelation<A, B> result;
	for (int i = 0; i < cardinality(); i++) {
		if (!result.is_member(elements[i].first, elements[i].second)) {
			result.add_element(elements[i].first, elements[i].second);
		}
	}
	for (int i = 0; i < m.cardinality(); i++) {
		if (!result.is_member(m.elements[i].first, m.elements[i].second)) {
			result.add_element(m.elements[i].first, m.elements[i].second);
		}
	}
	return result;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::operator -(MappingRelation<A, B> m) {
	MappingRelation<A, B> result;
	for (int i = 0; i < cardinality(); i++) {
		if (!m.is_member(elements[i].first, elements[i].second) && !result.is_member(elements[i].first, elements[i].second)) {
			result.add_element(elements[i].first, elements[i].second);
		}
	}

	return result;
}
template<typename A, typename B>
vector<B> MappingRelation<A, B>::operator [](A n) {
	vector<B> result;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i].first == n) {
			result.push_back(elements[i].second);
		}
	}
	sort(result.begin(), result.end());
	return result;
}

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::intersection(MappingRelation<A, B> m) {
	MappingRelation<A, B> result;
	for (int i = 0; i < cardinality(); i++) {
		if (m.is_member(elements[i].first, elements[i].second) && !result.is_member(elements[i].first, elements[i].second)) {
			result.add_element(elements[i].first, elements[i].second);
		}
	}
	for (int i = 0; i < m.cardinality(); i++) {
		if (is_member(m.elements[i].first, m.elements[i].second) && !result.is_member(m.elements[i].first, m.elements[i].second)) {
			result.add_element(m.elements[i].first, m.elements[i].second);
		}
	}
	return result;
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

template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::inverse() {
	MappingRelation<A, B> result;
	for (int i = 0; i < cardinality(); i++) {
		result.add_element(elements[i].second, elements[i].first);
	}
	return result;
}
template<typename A, typename B>
MappingRelation<A, B> MappingRelation<A, B>::combination(MappingRelation<A, B> m) {
	MappingRelation<A, B> result;
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < m.cardinality(); j++) {
			if (elements[i].second == m.elements[j].first) {
				result.add_element(elements[i].first, m.elements[j].second);
			}
		}
	}
	return result;
}

template<typename C, typename D>
ostream& operator <<(ostream& out, MappingRelation<C, D> m) {
	if (m.cardinality() == 0) {
		out << "{ }";
		return out;
	}
	out << "{ ";
	for (int i = 0; i < m.cardinality() - 1; i++) {
		out << "(" << m.elements[i].first << ", " << m.elements[i].second << "), ";
	}
	out << "(" << m.elements[m.cardinality() - 1].first << ", " << m.elements[m.cardinality() - 1].second << ") ";
	out << "}";
	return out;
}

