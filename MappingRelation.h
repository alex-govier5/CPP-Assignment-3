#pragma once
#include <iostream>
#include <vector>
using namespace std;

template <typename A,typename B>
class MappingRelation {

	struct pair {
		A first;
		B second;
	};

private:
	vector<pair> elements;

public:

	MappingRelation();
	MappingRelation(const MappingRelation<A,B>&);
	~MappingRelation();
	int cardinality();
	bool add_element(pair);
	void remove_element(pair);
	bool is_member(pair);
	bool operator ==(MappingRelation<A, B>);
	MappingRelation<A, B> operator +(MappingRelation<A, B>);
	MappingRelation<A, B> operator -(MappingRelation<A, B>);
	vector<A,B> operator[](int);
	MappingRelation<A, B> intersection(MappingRelation<A, B>);
	bool is_function();
	template<typename C, typename D> friend ostream& operator <<(ostream&, MappingRelation<C, D>);

};