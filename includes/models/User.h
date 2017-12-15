#pragma once
#include <iostream>
#include <string>
using namespace std;

enum profession {ADMIN, MANAGER, SALESMAN, KITCHEN, DELIVERY};

class User
{
public:
	static const string filename;
private:
	string username;
	string password;
	string name;
	profession job;
public:
	// Constructors
	User();
	User(string username, string password, string name, profession job);

	// Get functions
	//Gets the username
	string getUsername() const;
	//Gets the password
	string getPassword() const;
	//Gets the name
	string getName() const;
	//Gets the job
	profession getJob() const;

	// Set functions
	//Sets the username
	void setUsername(const string& username);
	//Sets the password
	void setPassword(const string& password);
	//Sets the name
	void setName(const string& name);
	//Sets the job
	void setJob(const profession& job);

	// Operator overloads
	friend ostream& operator << (ostream& out, const User& user);
	friend istream& operator >> (istream& in, User& user);
	friend bool operator == (const User& first, const User& second);
};

