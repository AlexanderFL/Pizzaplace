#include "User.h"

const string PizzaCrust::filename = "users.dat";

User::User(string username, string password, string name, int job) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->job = job;
}

string getUsername() const {
	return this->username;
}

string getPassword() const {
	return this->password;
}

string getName() const {
	return this->name;
}

int getJob() const {
	return this->job;
}

void setUsername(const string& username) {
	this->username = username;
}

void setPassword(const string& password) {
	this->password = password;
}

void setName(const string& name) {
	this->name = name;
}

void setJob(const int& job) {
	this->job = job;
}

