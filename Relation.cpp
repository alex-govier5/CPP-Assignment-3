#include "Relation.h"
#include <iostream>
#include <vector>
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
}

template <typename T>
Relation<T>::~Relation() {
	elements.clear();
}

template<typename T>
int Relation<T>::cardinality() {
	return elements.size();
}

template<typename T>
bool Relation<T>::add_element(pair elem) {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elem.first && elements[i].second == elem.second) {
			return false;
		}
	}
	elements.push_back(elem);
	return true;
}
template<typename T>
void Relation<T>::remove_element(pair elem) {
	if (cardinality() == 0) {
		return;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elem.first && elements[i].second == elem.second) {
			elements.erase(i);
		}
	}
	return;
}

template<typename T>
bool Relation<T>::is_member(pair elem) {
	for (int i = 0; i < cardinality(); i++) {
		if (elements[i].first == elem.first && elements[i].second == elem.second) {
			return true;
		}
	}
	return false;
}

template<typename T>
bool Relation<T>::operator ==(Relation<T> r) {
	if (cardinality() != r.cardinality()) {
		return false;
	}
	for (int i = 0; i < cardinality(); i++) {
		if (!is_member(r.elements[i])) {
			return false;
		}
	}
	return true;
}

template<typename T>
vector<T> Relation<T>::operator [](int n){
	vector<T> result;
	result.push_back(elements[n].first);
	result.push_back(elements[n].second);
	return result;
}

template<typename T>
bool Relation<T>::reflexive() {
	vector<T> values;
	for (int i = 0; i < cardinality();i++) {
		values.push_back(elements[i].first);
		values.push_back(elements[i].second);
	}
	for (int i = 0; i < values.size(); i++) {
		pair p;
		p.first = values[i];
		p.second = values[i];
		if (!is_member(p)) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::irreflexive() {
	vector<T> values;
	for (int i = 0; i < cardinality();i++) {
		values.push_back(elements[i].first);
		values.push_back(elements[i].second);
	}
	for (int i = 0; i < values.size(); i++) {
		pair p;
		p.first = values[i];
		p.second = values[i];
		if (is_member(p)) {
			return false;
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::symmetric() {
	for (int i = 0; i < cardinality();i++) {
		if (elements[i].first == elements[i].second) {
			continue;
		}
		else {
			pair p;
			p.first = elements[i].second;
			p.second = elements[i].first;
			if (!is_member(p)) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
bool Relation<T>::asymmetric() {
	for (int i = 0; i < cardinality();i++) {
		if (elements[i].first == elements[i].second) {
			continue;
		}
		else {
			pair p;
			p.first = elements[i].second;
			p.second = elements[i].first;
			if (is_member(p)) {
				return false;
			}
		}
	}
	return true;
}
template<typename T>
bool Relation<T>::transitive() {
	for (int i = 0; i < cardinality();i++) {
		for (int j = 0; j < cardinality();j++) {
			if (elements[j].first == elements[i].second) {
				for (int x = 0; x < cardinality(); x++) {
					pair p;
					p.first = elements[i].first;
					p.second = elements[j].second;
					if (!is_member(p)) {
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
	for (int i = 0; i < cardinality();i++) {
		for (int j = 0; j < cardinality();j++) {
			if (elements[j].first == elements[i].first && elements[j].second != elements[i].second) {
				return false;
			}
		}
	}
	return true;
}

template<typename T>
Relation<T> Relation<T>::inverse() {
	for (int i = 0; i < cardinality();i++) {
		int temp = elements[i].first;
		elements[i].first = elements[i].second;
		elements[i].second = temp;
	}
	return *this;
}
template<typename T>
Relation<T> Relation<T>::combination(Relation<T> r) {
	Relation<T> temp;
	for (int i = 0; i < cardinality(); i++) {
		for (int j = 0; j < r.cardinality(); j++) {
			temp.add_element(pair{ elements[i].first, elements[j].second });
		}
	}

	return temp;
}


template<typename R>
ostream& operator <<(ostream& out, Relation<R> r) {
	out << "{ ";
	for (int i = 0; i < r.cardinality()-1; i++) {
		out << "(" << r.elements[i].first << ", " << r.add_element[i].second << "), ";
	}
	out << "(" << r.elements[r.cardinality()-1].first << ", " << r.add_element[r.cardinality()-1].second << ") ";
	out << "}";
	return out;
}

int main() {
	

}

