#include "LoginService.h"


LoginService::LoginService() {}

profession LoginService::login(string username, string password) {
	vector<User> users = repo.RetrieveAllFromFile<User>();
	for (int i = 0; i < users.size(); ++i) {
		if (username == users.at(i).getUsername() && password == users.at(i).getPassword()) {
			return users.at(i).getJob();
		}
	}
	throw InvalidLogin();
}