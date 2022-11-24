// Alex Govier 300174954
// Taj Loodu 300128141

#pragma once
#include <iostream>
#include <vector>
#include <set>
using namespace std;

template <typename A, typename B>
class MappingRelation {

	struct pair {
		A first;
		B second;
	};

private:
	vector<pair> elements;
	set<A> one;
	set<B> two;

public:

	MappingRelation();
	MappingRelation(const MappingRelation<A, B>&);
	~MappingRelation();
	int cardinality();
	bool add_element(A,B);
	void remove_element(A,B);
	bool is_member(A,B);
	bool operator ==(MappingRelation<A, B>);
	MappingRelation<A, B> operator +(MappingRelation<A, B>);
	MappingRelation<A, B> operator -(MappingRelation<A, B>);
	vector<B> operator[](A);
	MappingRelation<A, B> intersection(MappingRelation<A, B>);
	bool is_function();
	MappingRelation<A, B> inverse();
	MappingRelation<A, B> combination(MappingRelation<A, B>);
	template<typename C, typename D> friend ostream& operator <<(ostream&, MappingRelation<C, D>);

};