#pragma once

#include "Data.h"
#include "EmptyVector.h"
#include "InvalidString.h"
#include "NumberInString.h"

class CommonService
{
private:
	Data repo;
public:
	void validateStringIsDigit(const string& str) const;
	int convertStringToInt(const string& str) const;
	// Templates
	template<class T> vector<T> getItems();
	template<class T> vector<string> getNames();
	template<class T> vector<string> getNames(vector<T>& items);
	template<class T> T getItem(int index);
	template<class T> void addItem(T& item) const;
	template<class T> void deleteItem(int index);
	template<class T> vector<T> deleteItem(vector<T>& items, int index);
	template<class T> void validateVectorNotEmpty(const vector<T>& items) const;
};

template<class T> vector<T> CommonService::getItems() {
	vector<T> items = repo.RetrieveAllFromFile<T>();
	validateVectorNotEmpty(items);
	return items;
}

template<class T> vector<string> CommonService::getNames() {
	vector<string> vec;
	vector<T> items = getItems<T>();
	for (size_t i = 0; i < items.size(); ++i) {
		vec.push_back(items.at(i).getName());
	}
	return vec;
}

template<class T> vector<string> CommonService::getNames(vector<T>& items) {
	vector<string> vec;
	for (size_t i = 0; i < items.size(); ++i) {
		vec.push_back(items.at(i).getName());
	}
	return vec;
}

template<class T> T CommonService::getItem(int index) {
	vector<T> items = getItems<T>();
	return items.at(index);
}

template<class T> void CommonService::addItem(T& item) const {
	repo.WriteToFile(item);
}

template<class T> void CommonService::deleteItem(int index) {
	repo.RemoveFromFileAtIndex<T>(index);
}

template<class T> vector<T> CommonService::deleteItem(vector<T>& items, int index) {
	if (index < 0 || index >= items.size()) {
		throw out_of_range("");
	}
	items.erase(items.begin() + index);
	return items;
}

template<class T> void CommonService::validateVectorNotEmpty(const vector<T>& items) const {
	if (items.size() == 0) {
		throw EmptyVector();
	}
 }