#pragma once 			// Avoid redefinition of the class Console
#include "iostream"
#include "string"

using namespace std;

class Users
{
public:
	string name;
	int score;

	//constructor, create icecream object
	Users(string name, double score) {
		this->name = name;
		this->score = score;
	}

	static bool SortScore(Users user1, Users user2) {
		return user1.score > user2.score;
	}



};
