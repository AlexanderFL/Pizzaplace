#pragma once
#include <iostream>
#include <string>
using namespace std;

class User
{
public:
	static const string filename;
private:
	string username;
	string password;
	string name;
	int job;
public:
	User();
	User(string username, string password, string name, int job);
	string getUsername() const;
	string getPassword() const;
	string getName() const;
	int getJob() const;
	void setUsername(const string& username);
	void setPassword(const string& password);
	void setName(const string& name);
	void setJob(const int& job);
	friend ostream& operator << (ostream& out, const User& user);
	friend istream& operator >> (istream& in, User& user);
};

