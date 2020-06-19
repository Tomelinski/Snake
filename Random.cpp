#pragma once 			// Avoid redefinition of the class Console
#include "iostream" 	// cin, cout
#include "string"		// To use strings

#include "ctime"

using namespace std;


// Class that groups functions related to the Console.
// Implements some of the methods from the C# Console class.
class Random
{
private:

public:
	//generatea a seed
	static void Seed() {
		srand(time(NULL));
	}

	//generate a random number from 0 to max
	static int Next(int max) {
		int randomNumber = rand() % (max);
		cout << randomNumber;
		return randomNumber; 
	}

	//generate a random number from min to max
	static int Next(int min, int max) {
		int randomNumber;
		int range = max - min;


		randomNumber = rand();
		randomNumber %= range;
		randomNumber += min;
		return randomNumber;
	}
};