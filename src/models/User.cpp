#include "User.h"
#include <fstream>

const string User::filename = "users.dat";

User::User()
{
	this->job = DELIVERY;
};

User::User(string username, string password, string name, profession job)
{
	this->username = username;
	setPassword(password);
	this->name = name;
	this->job = job;
}

string
User::getUsername() const
{
	return this->username;
}

string
User::getPassword() const
{
	return this->password;
}

string
User::getName() const
{
	return this->name;
}

profession
User::getJob() const
{
	return this->job;
}

void
User::setUsername(const string &username)
{
	this->username = username;
}

void
User::setPassword(const string &password)
{
	std::hash<std::string> str_hash;
	size_t tempStor = str_hash(password);
	this->password = to_string(tempStor);
}

void
User::setName(const string &name)
{
	this->name = name;
}

void
User::setJob(const profession &job)
{
	this->job = job;
}

ostream &
operator<<(ostream &out, const User &user)
{
	if (&out != &cout)
	{
		size_t len = user.username.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(user.username.c_str(), len);
		len = user.password.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(user.password.c_str(), len);
		len = user.name.length() + 1;
		out.write((char *)(&len), sizeof(size_t));
		out.write(user.name.c_str(), len);
		out.write((char *)(&user.job), sizeof(profession));
	}
	return out;
}

istream &
operator>>(istream &in, User &user)
{
	if (&in != &cin)
	{
		size_t len;
		in.read((char *)(&len), sizeof(size_t));
		char *str = new char[len];
		in.read(str, len);
		user.username = str;
		delete[] str;
		in.read((char *)(&len), sizeof(size_t));
		str = new char[len];
		in.read(str, len);
		user.password = str;
		delete[] str;
		in.read((char *)(&len), sizeof(size_t));
		str = new char[len];
		in.read(str, len);
		user.name = str;
		delete[] str;
		in.read((char *)(&user.job), sizeof(profession));
	}
	return in;
}

bool
operator==(const User &first, const User &second)
{
	if (first.getName() == second.getName())
	{
		if (first.getPassword() == second.getPassword())
		{
			if (first.getJob() == second.getJob())
			{
				if (first.getUsername() == second.getUsername())
				{
					return true;
				}
			}
		}
	}
	return false;
}