#include <iostream>
#include "MappingRelation.cpp"
#include <vector>

using namespace std;

int main()
{
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
	if (nations.cardinality() == 5) cout << "Cardinality - Test 1 - Passed." << endl;
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

	/*
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
	*/


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
	if (v[0] == 7 && v[1] == 13 && v.size() == 2) cout << "operator [] - Test 1 - Passed." << endl;
	else cout << "operator [] - Test 1 - Failed!" << endl;

	vector <string> names = invnations["Italy"];
	if (names.size() == 0) cout << "operator [] - Test 2 - Passed." << endl;
	else cout << "operator [] - Test 2 - Failed!" << endl;

	//Testing operator +
	if (nations3 == nations + nations2) cout << "operator + - Test 1 - Passed." << endl;
	else cout << "operator + - Test 1 - Failed!" << endl;

	if (nations3 == nations3 + nations ) cout << "operator + - Test 2 - Passed." << endl;
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