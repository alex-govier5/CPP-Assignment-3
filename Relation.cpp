#include "Relation.h"
#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <typename T>
Relation<T>::Relation() {
	//Nothing to do, vector of pairs already set up
}

template <typename T>
Relation<T>::Relation(const Relation<T>& r) {
	for (int i = 0; i < r.cardinality(); i++) {
		elements.push_back(r.elements[i]);
	}
	typename set<T>::iterator itr;
	for (itr = r.root.begin(); itr != r.root.end(); itr++) {
		root.insert(*itr);
	}
}

template <typename T>
Relation<T>::~Relation() {
	elements.clear();
	root.clear();
}

template<typename T>
void Relation<T>::add_to_set(T elem) {
	root.insert(elem);
}

template<typename T>
int Relation<T>::cardinality() const {
	return elements.size();
}

template<typename T>
bool Relation<T>::add_element(T elem1, T elem2) {
	pair elem;
	elem.first = elem1;
	elem.second = elem2;
	if (root.find(elem.first) == root.end() || root.find(elem.second) == root.end()) {
		return false;
	}
	if (is_member(elem.first, elem.second)) {
		
		return false;
	}

	elements.push_back(elem);
	return true;
}

template<typename T>
void Relation<T>::remove_element(T elem1, T elem2) {
	pair elem;
	elem.first = elem1;
	elem.second = elem2;
	if (cardinality() == 0) {
		return;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elem.first && elements[i].second == elem.second) {
			elements.erase(elements.begin() + i);
		}
	}
	return;
}

template<typename T>
bool Relation<T>::is_member(T elem1, T elem2) {
	pair elem;
	elem.first = elem1;
	elem.second = elem2;
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elem.first && elements[i].second == elem.second) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Relation<T>::operator ==(Relation<T> r) {

	for (int i = 0; i < r.cardinality(); i++) {
		pair p = r.elements[i];
		if (!is_member(p.first, p.second)) {
			return false;
		}
	}
	for (int i = 0; i < cardinality(); i++) {
		pair p = elements[i];
		if (!r.is_member(p.first, p.second)) {
			return false;
		}
	}
	return true;
}

template<typename T>
vector<T> Relation<T>::operator [](T n) {
	vector<T> result;
	for (int i = 0; i < elements.size(); i++) {
		if (elements[i].first == n) {
			result.push_back(elements[i].second);
		}
	}
	return result;
}

template<typename T>
bool Relation<T>::reflexive() {
	typename set<T>::iterator itr;
	for (itr = root.begin(); itr != root.end(); itr++) {
		pair p;
		p.first = p.second = *itr;
		if (!is_member(p.first, p.second)) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::irreflexive() {
	typename set<T>::iterator itr;
	for (itr = root.begin(); itr != root.end(); itr++) {
		pair p;
		p.first = p.second = *itr;
		if (is_member(p.first, p.second)) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::symmetric() {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elements[i].second) {
			continue;
		}
		else {
			pair p;
			p.first = elements[i].second;
			p.second = elements[i].first;
			if (!is_member(p.first, p.second)) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::asymmetric() {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first != elements[i].second) {
			pair p;
			p.first = elements[i].second;
			p.second = elements[i].first;
			if (is_member(p.first, p.second)) {
				return false;
			}
		}
	}
	return true;
}
template<typename T>
bool Relation<T>::transitive() {
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < cardinality(); j++) {
			if (elements[j].first == elements[i].second) {
				for (int x = 0; x < cardinality(); x++) {
					pair p;
					p.first = elements[i].first;
					p.second = elements[j].second;
					if (!is_member(p.first, p.second)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::is_function() {
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < cardinality(); j++) {
			if (elements[j].first == elements[i].first && elements[j].second != elements[i].second) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
Relation<T> Relation<T>::inverse() {
	Relation<T> result;
	typename set<T>::iterator itr;
	for (itr = root.begin(); itr != root.end(); itr++) {
		result.root.insert(*itr);
	}

	for (int i = 0; i < cardinality(); i++) {
		result.add_element(elements[i].second, elements[i].first);
	}
	return result;
}

template<typename T>
Relation<T> Relation<T>::combination(Relation<T> r) {
	Relation<T> result;
	typename set<T>::iterator itr;
	for (itr = root.begin(); itr != root.end(); itr++) {
		result.add_to_set(*itr);
	}
	typename set<T>::iterator itr2;
	for (itr2 = r.root.begin(); itr2 != r.root.end(); itr2++) {
		result.add_to_set(*itr2);
	}
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < r.cardinality(); j++) {
			if (elements[i].second == r.elements[j].first) {
				result.add_element(elements[i].first, r.elements[j].second);
			}
		}
	}
	return result;
}


template<typename R>
ostream& operator <<(ostream& out, Relation<R> r) {
	if (r.cardinality() == 0) {
		out << "{ }";
		return out;
	}
	out << "{ ";
	for (int i = 0; i < r.cardinality() - 1; i++) {
		out << "(" << r.elements[i].first << ", " << r.elements[i].second << "), ";
	}
	out << "(" << r.elements[r.cardinality() - 1].first << ", " << r.elements[r.cardinality() - 1].second << ") ";
	out << "}";
	return out;
}