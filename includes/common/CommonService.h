#pragma once

#include "Data.h"
#include "EmptyVector.h"

class CommonService
{
private:
	Data repo;
public:
	
	// Templates
	template<class T> vector<T> getItems();
	template<class T> void addItem(T& item) const;
	template<class T> void deleteItem(int index);
	template<class T> void validateVectorNotEmpty(const vector<T>& items) const;
};

template<class T> vector<T> CommonService::getItems() {
	vector<T> items = repo.RetrieveAllFromFile<T>();
	validateVectorNotEmpty(items);
	return items;
}

template<class T> void CommonService::addItem(T& item) const {
	repo.WriteToFile(item);
}

template<class T> void CommonService::deleteItem(int index) {
	repo.RemoveFromFileAtIndex<T>(index);
}

template<class T> void CommonService::validateVectorNotEmpty(const vector<T>& items) const {
	if (items.size() == 0) {
		throw EmptyVector();
	}
}