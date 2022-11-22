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
/*
int main() {
	Relation <string> r1, r2;


	r1.add_to_set("apple");
	r1.add_to_set("orange");
	r1.add_to_set("banana");
	r1.add_to_set("cherry");

	r2.add_to_set("apple");
	r2.add_to_set("orange");
	r2.add_to_set("banana");
	r2.add_to_set("cherry");

	r1.add_element("apple", "apple");
	r1.add_element("orange", "orange");
	r1.add_element("banana", "banana");
	r1.add_element("cherry", "cherry");
	r1.add_element("apple", "banana");


	//Testing Cardinality
	if (r1.cardinality() == 5) cout << "Cardinality - Test 1 - Passed." << endl;
	else cout << "Cardinality - Test 1 - Failed!" << endl;

	if (r2.cardinality() == 0) cout << "Cardinality - Test 2 - Passed." << endl;
	else cout << "Cardinality - Test 2 - Failed!" << endl;

	r2.add_element("cherry", "banana");
	if (r2.cardinality() == 1) cout << "Cardinality - Test 3 - Passed." << endl;
	else cout << "Cardinality - Test 3 - Failed!" << endl;


	//Testing is_member
	if (r1.is_member("apple", "apple")) cout << "is_member - Test 1 - Passed." << endl;
	else cout << "is_member - Test 1 - Failed!" << endl;

	if (!r1.is_member("cherry", "banana")) cout << "is_member - Test 2 - Passed." << endl;
	else cout << "is_member - Test 2 - Failed!" << endl;

	if (!r2.is_member("cherry", "cherry")) cout << "is_member - Test 3 - Passed." << endl;
	else cout << "is_member - Test 3 - Failed!" << endl;

	if (r2.is_member("cherry", "banana")) cout << "is_member - Test 4 - Passed." << endl;
	else cout << "is_member - Test 4 - Failed!" << endl;


	//Testing add_element
	r1.add_element("orange", "banana");
	if (r1.is_member("orange", "banana")) cout << "add_element - Test 1 - Passed." << endl;
	else cout << "add_element - Test 1 - Failed!" << endl;

	r2.add_element("apple", "cherry");
	if (r2.is_member("apple", "cherry")) cout << "add_element - Test 2 - Passed." << endl;
	else cout << "add_element - Test 2 - Failed!" << endl;

	if (!r2.is_member("apple", "orange")) cout << "add_element - Test 3 - Passed." << endl;
	else cout << "add_element - Test 3 - Failed!" << endl;

	//Testing remove_element
	r1.remove_element("orange", "banana");
	if (!r1.is_member("orange", "banana")) cout << "remove_element - Test 1 - Passed." << endl;
	else cout << "remove_element - Test 1 - Failed!" << endl;

	r2.remove_element("banana", "apple");
	if (!r2.is_member("banana", "apple")) cout << "remove_element - Test 2 - Passed." << endl;
	else cout << "remove_element - Test 2 - Failed!" << endl;

	r1.remove_element("orange", "cherry");
	if (!r1.is_member("orange", "cherry")) cout << "remove_element - Test 3 - Passed." << endl;
	else cout << "remove_element - Test 3 - Failed!" << endl;

	//Testing reflexive
	if (r1.reflexive()) cout << "reflexive - Test 1 - Passed." << endl;
	else cout << "reflexive - Test 1 - Failed!" << endl;

	if (!r2.reflexive()) cout << "reflexive - Test 2 - Passed." << endl;
	else cout << "reflexive - Test 2 - Failed!" << endl;

	r2.add_element("apple", "apple");
	r2.add_element("cherry", "cherry");
	r2.add_element("banana", "banana");
	if (!r2.reflexive()) cout << "reflexive - Test 3 - Passed." << endl;
	else cout << "reflexive - Test 3 - Failed!" << endl;

	//Testing Irreflexive
	if (!r1.irreflexive()) cout << "irreflexive - Test 1 - Passed." << endl;
	else cout << "irreflexive - Test 1 - Failed!" << endl;

	if (!r2.irreflexive()) cout << "irreflexive - Test 2 - Passed." << endl;
	else cout << "irreflexive - Test 2 - Failed!" << endl;

	r2.remove_element("apple", "apple");
	r2.remove_element("cherry", "cherry");
	r2.remove_element("banana", "banana");
	if (r2.irreflexive()) cout << "irreflexive - Test 3 - Passed." << endl;
	else cout << "irreflexive - Test 3 - Failed!" << endl;


	//Testing symmetric
	r1.add_element("banana", "apple");
	if (r1.symmetric()) cout << "symmetric - Test 1 - Passed." << endl;
	else cout << "symmetric - Test 1 - Failed!" << endl;

	if (!r2.symmetric()) cout << "symmetric - Test 2 - Passed." << endl;
	else cout << "symmetric - Test 2 - Failed!" << endl;

	r2.add_element("banana", "banana");
	if (!r2.symmetric()) cout << "symmetric - Test 3 - Passed." << endl;
	else cout << "symmetric - Test 3 - Failed!" << endl;

	//Testing asymmetric
	r2.remove_element("banana", "apple");
	if (!r1.asymmetric()) cout << "asymmetric - Test 1 - Passed." << endl;
	else cout << "asymmetric - Test 1 - Failed!" << endl;

	r2.remove_element("cherry", "apple");
	r2.remove_element("banana", "cherry");
	r2.add_element("cherry", "cherry");
	r2.add_element("apple", "apple");
	if (r2.asymmetric()) cout << "asymmetric - Test 2 - Passed." << endl;
	else cout << "asymmetric - Test 2 - Failed!" << endl;

	r2.add_element("banana", "apple");
	r2.add_element("apple", "banana");
	if (!r2.asymmetric()) cout << "asymmetric - Test 3 - Passed." << endl;
	else cout << "asymmetric - Test 3 - Failed!" << endl;

	//Testing transitive
	if (r1.transitive()) cout << "transitive - Test 1 - Passed." << endl;
	else cout << "transitive - Test 1 - Failed!" << endl;

	r2.add_element("cherry", "cherry");
	if (!r2.transitive()) cout << "transitive - Test 2 - Passed." << endl;
	else cout << "transitive - Test 2 - Failed!" << endl;

	r1.add_element("banana", "orange");
	if (!r1.transitive()) cout << "transitive - Test 3 - Passed." << endl;
	else cout << "transitive - Test 3 - Failed!" << endl;

	//Testing is_funciton
	if (!r1.is_function()) cout << "is_function - Test 1 - Passed." << endl;
	else cout << "is_function - Test 1 - Failed!" << endl;

	if (!r2.is_function()) cout << "is_function - Test 2 - Passed." << endl;
	else cout << "is_function - Test 2 - Failed!" << endl;

	r2.remove_element("apple", "apple");
	r2.remove_element("apple", "banana");
	r2.remove_element("banana", "banana");
	r2.remove_element("cherry", "banana");
	if (r2.is_function()) cout << "is_function - Test 3 - Passed." << endl;
	else cout << "is_function - Test 3 - Failed!" << endl;

	Relation<string> r3 = r1.inverse();

	//Testing operator ==
	if (r3 == r2.inverse()) cout << "operator == - Test 1 - Passed." << endl;
	else cout << "operator == - Test 1 - Failed!" << endl;

	if (!(r1 == r2)) cout << "operator == - Test 2 - Passed." << endl;
	else cout << "operator == - Test 2 - Failed!" << endl;


	//Testing operator []
	int i;
	vector <string> v = r1["apple"];
	if (v[0] == "apple" && v[1] == "banana" && v.size() == 2) cout << "operator [] - Test 1 - Passed." << endl;
	else cout << "operator [] - Test 1 - Failed!" << endl;

	v = r2["orange"];
	if (v.size() == 0) cout << "operator [] - Test 2 - Passed." << endl;
	else cout << "operator [] - Test 2 - Failed!" << endl;

	Relation <string> r4 = r2.inverse();
	Relation <string> r5 = r1.combination(r2);
	Relation <string> r6 = r2.combination(r1);

	cout << "r1 = " << r1 << endl;
	cout << "r2 = " << r2 << endl;

	cout << "r1-inverse = " << r3 << endl;
	cout << "r2-inverse = " << r4 << endl;

	cout << "R1oR2 = " << r5 << endl;
	cout << "R2oR1 = " << r6 << endl;

	/*Should be printed
	r1 = { (apple, apple), (apple, banana), (banana, apple), (banana, banana), (banana, orange), (cherry, cherry), (orange, orange) }
	r2 = { (apple, cherry), (banana, apple), (cherry, cherry) }
	r1-inverse = { (apple, apple), (apple, banana), (banana, apple), (banana, banana), (cherry, cherry), (orange, banana), (orange, orange) }
	r2-inverse = { (apple, banana), (cherry, apple), (cherry, cherry) }
	R1oR2 = { (apple, apple), (apple, cherry), (banana, apple), (banana, cherry), (cherry, cherry) }
	R2oR1 = { (apple, cherry), (banana, apple), (banana, banana), (cherry, cherry) }
	
	return 0;
}*/