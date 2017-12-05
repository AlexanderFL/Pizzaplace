#pragma once
#include <iostream>
#include <string>
#include <fstream>

#include "Topping.h"
#include "Order.h"
using namespace std;

class Data
{
public:
	template <class Repos>
	void WriteToFile(Repos rep) const;

	template <class Repos>
	void WriteMultipleLinesToFile(vector<Repos> rep) const;

	template <class Repos>
	Repos RetrieveFromFile(int loc);

	template <class Repos>
	vector<Repos> RetrieveAllFromFile();

	template <class Repos>
	void RemoveFromFileAtIndex(int index);

	template <class Repos>
	void ModifyFileAtIndex(int index);
};

template<class Repos>
inline void Data::WriteToFile(Repos rep) const
{
	ofstream fout;
	fout.open(rep.filename, ios::binary | ios::app);
	fout << rep;
	fout.close();
}

template <class Repos>
inline void Data::WriteMultipleLinesToFile(vector<Repos> repVec) const
{
	Repos rep;
	ofstream fout;
	fout.open(rep.filename, ios::binary);
	for (unsigned int i = 0; i < repVec.size(); i++){
		fout << repVec.at(i);
	}
	fout.close();
}

template<class Repos>
inline Repos Data::RetrieveFromFile(int loc)
{
	vector<Repos> repository = RetrieveAllFromFile<Repos>();
	return repository.at(loc);
}

template<class Repos>
inline vector<Repos> Data::RetrieveAllFromFile()
{
	vector<Repos> vec;
	Repos rep;
	ifstream fin;
	
	fin.open(rep.filename, ios::binary);
	if (fin.is_open())
	{
		fin.seekg(0, fin.end);
		int endpos = fin.tellg();
		fin.seekg(0, fin.beg);
		int pos = 0;
		while (pos != endpos)
		{
			fin >> rep;
			vec.push_back(rep);
			pos = fin.tellg();
		}
	}
	fin.close();
	return vec;
}

template<class Repos>
inline void Data::RemoveFromFileAtIndex(int index)
{
	vector<Repos> vec = RetrieveAllFromFile<Repos>();
	vec.erase(vec.begin() + index);
	WriteMultipleLinesToFile(vec);
}

template<class Repos>
inline void Data::ModifyFileAtIndex(int index)
{
	vector<Repos> vec = RetrieveAllFromFile<Repos>();
	Repos rep;
	cin >> rep;
	vec[index] = rep;
	WriteMultipleLinesToFile(vec);
}