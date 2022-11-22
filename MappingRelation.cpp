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

int main() {

	MappingRelation <string, string> nations;
	MappingRelation <string, string> nations2;
	MappingRelation <string, string> nations3;
	MappingRelation <string, string> nations4;
	MappingRelation <string, string> nations5;

	MappingRelation <string, int> numbers;
	MappingRelation <string, int> ages;

	nations.add_element("Christiano Ronaldo", "Portugal");
	nations.add_element("Thomas Muller", "Germany");
	nations.add_element("Lionel Messi", "Argentina");
	nations.add_element("Neymar", "Brazil");
	nations.add_element("Mohamed Salah", "Egypt");
	nations.add_element("Joshua Kimmich", "Germany");

	nations2.add_element("Paola Dibala", "Argentina");
	nations2.add_element("Thomas Muller", "Germany");
	nations2.add_element("Lionel Messi", "Argentina");
	nations2.add_element("Neymar", "Brazil");
	nations2.add_element("Leon Goretzka", "Germany");

	nations3.add_element("Christiano Ronaldo", "Portugal");
	nations3.add_element("Thomas Muller", "Germany");
	nations3.add_element("Lionel Messi", "Argentina");
	nations3.add_element("Neymar", "Brazil");
	nations3.add_element("Mohamed Salah", "Egypt");
	nations3.add_element("Joshua Kimmich", "Germany");
	nations3.add_element("Paola Dibala", "Argentina");
	nations3.add_element("Leon Goretzka", "Germany");
	nations3.add_element("Antoine Griezmann", "France");


	nations4.add_element("Thomas Muller", "Germany");
	nations4.add_element("Lionel Messi", "Argentina");
	nations4.add_element("Neymar", "Brazil");

	nations5.add_element("Antoine Griezmann", "France");
	nations5.add_element("Christiano Ronaldo", "Portugal");
	nations5.add_element("Mohamed Salah", "Egypt");
	nations5.add_element("Joshua Kimmich", "Germany");

	numbers.add_element("Portugal", 7);
	numbers.add_element("Germany", 13);
	numbers.add_element("Argentina", 10);
	numbers.add_element("Brazil", 10);
	numbers.add_element("Egypt", 10);
	numbers.add_element("Germany", 7);

	//Testing Cardinality
	if (nations.cardinality() == 6) cout << "Cardinality - Test 1 - Passed." << endl;
	else cout << "Cardinality - Test 1 - Failed!" << endl;

	if (numbers.cardinality() == 6) cout << "Cardinality - Test 2 - Passed." << endl;
	else cout << "Cardinality - Test 2 - Failed!" << endl;

	if (ages.cardinality() == 0) cout << "Cardinality - Test 3 - Passed." << endl;
	else cout << "Cardinality - Test 3 - Failed!" << endl;

	//Testing is_member
	if (nations.is_member("Thomas Muller", "Germany")) cout << "is_member - Test 1 - Passed." << endl;
	else cout << "is_member - Test 1 - Failed!" << endl;

	if (!ages.is_member("Thomas Muller", 32)) cout << "is_member - Test 2 - Passed." << endl;
	else cout << "is_member - Test 2 - Failed!" << endl;

	if (!numbers.is_member("Argentina", 1)) cout << "is_member - Test 3 - Passed." << endl;
	else cout << "is_member - Test 3 - Failed!" << endl;

	if (numbers.is_member("Argentina", 10)) cout << "is_member - Test 4 - Passed." << endl;
	else cout << "is_member - Test 4 - Failed!" << endl;

	//Testing add_element
	nations.add_element("Antoine Griezmann", "France");
	if (nations.is_member("Antoine Griezmann", "France")) cout << "add_element - Test 1 - Passed." << endl;
	else cout << "add_element - Test 1 - Failed!" << endl;

	numbers.add_element("France", 17);
	if (numbers.is_member("France", 17)) cout << "add_element - Test 2 - Passed." << endl;
	else cout << "add_element - Test 2 - Failed!" << endl;

	if (!numbers.is_member("France", 7)) cout << "add_element - Test 3 - Passed." << endl;
	else cout << "add_element - Test 3 - Failed!" << endl;

	//Testing remove_element
	nations.remove_element("Neymar", "Brazil");
	if (!nations.is_member("Neymar", "Brazil")) cout << "remove_element - Test 1 - Passed." << endl;
	else cout << "remove_element - Test 1 - Failed!" << endl;
	nations.add_element("Neymar", "Brazil");

	numbers.remove_element("Portugal", 17);
	if (!numbers.is_member("Portugal", 17)) cout << "remove_element - Test 2 - Passed." << endl;
	else cout << "remove_element - Test 2 - Failed!" << endl;

	ages.remove_element("Christiano Ronaldo", 37);
	if (!ages.is_member("Christiano Ronaldo", 37)) cout << "remove_element - Test 3 - Passed." << endl;
	else cout << "remove_element - Test 3 - Failed!" << endl;

	
	//Testing is_funciton
	if (!numbers.is_function()) cout << "is_function - Test 1 - Passed." << endl;
	else cout << "is_function - Test 1 - Failed!" << endl;

	if (nations.is_function()) cout << "is_function - Test 2 - Passed." << endl;
	else cout << "is_function - Test 2 - Failed!" << endl;

	if (ages.is_function()) cout << "is_function - Test 3 - Passed." << endl;
	else cout << "is_function - Test 3 - Failed!" << endl;
	
	MappingRelation <string, string> invnations = nations.inverse();

	//Testing operator ==
	if (nations == invnations.inverse()) cout << "operator == - Test 1 - Passed." << endl;
	else cout << "operator == - Test 1 - Failed!" << endl;

	if (!(ages == numbers)) cout << "operator == - Test 2 - Passed." << endl;
	else cout << "operator == - Test 2 - Failed!" << endl;

	//Testing operator []
	vector <int> v = numbers["Germany"];
	if (v[0] == 13 && v[1] == 7 && v.size() == 2) cout << "operator [] - Test 1 - Passed." << endl;
	else cout << "operator [] - Test 1 - Failed!" << endl;

	vector <string> names = invnations["Italy"];
	if (names.size() == 0) cout << "operator [] - Test 2 - Passed." << endl;
	else cout << "operator [] - Test 2 - Failed!" << endl;
	
	//Testing operator +
	if (nations3 == nations + nations2) cout << "operator + - Test 1 - Passed." << endl;
	else cout << "operator + - Test 1 - Failed!" << endl;

	if (nations3 == nations3 + nations) cout << "operator + - Test 2 - Passed." << endl;
	else cout << "operator + - Test 2 - Failed!" << endl;
	
	//Testing operator intersection
	if (nations4 == nations.intersection(nations2)) cout << "intersection - Test 1 - Passed." << endl;
	else cout << "intersection - Test 1 - Failed!" << endl;

	if (nations4 == nations.intersection(nations4)) cout << "intersection - Test 2 - Passed." << endl;
	else cout << "intersection - Test 2 - Failed!" << endl;
	
	//Testing operator -
	if (nations5 == nations - nations2) cout << "operator - - Test 1 - Passed." << endl;
	else cout << "operator - - Test 1 - Failed!" << endl;

	if (nations2 - nations == nations3 - nations) cout << "operator - - Test 2 - Passed." << endl;
	else cout << "operator - - Test 2 - Failed!" << endl;

	cout << "nations = " << nations << endl;
	cout << "numbers = " << numbers << endl;

	cout << "nations-inverse = " << invnations << endl;
	cout << "ages = " << ages << endl;

	/*Should be printed
	nations = { (Antoine Griezmann, France), (Christiano Ronaldo, Portugal), (Joshua Kimmich, Germany), (Lionel Messi, Argentina), (Mohamed Salah, Egypt), (Neymar, Brazil), (Thomas Muller, Germany) }
	numbers = { (Argentina, 10), (Brazil, 10), (Egypt, 10), (France, 17), (Germany, 7), (Germany, 13), (Portugal, 7) }
	nations-inverse = { (Argentina, Lionel Messi), (Brazil, Neymar), (Egypt, Mohamed Salah), (France, Antoine Griezmann), (Germany, Joshua Kimmich), (Germany, Thomas Muller), (Portugal, Christiano Ronaldo) }
	ages = {  }
	*/
	return 0;
}

