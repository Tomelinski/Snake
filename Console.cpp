#pragma once 			// Avoid redefinition of the class Console
#include "iostream" 	// cin, cout
#include "string"		// To use strings
#include "Windows.h" 	// For colours, Beep(), and Sleep()


using namespace std;

// A group of constants enumerated starting from 0
// E.g. Colour::DarkBlue will have a value of 1
enum Colour
{
	Black, DarkBlue, DarkGreen, DarkCyan, DarkRed, DarkMagenta, DarkYellow, Grey, DarkGrey, Blue, Green, Cyan, Red, Magenta, Yellow, White
};

// Class that groups functions related to the Console.
// Implements some of the methods from the C# Console class.
class Console
{
private:

public:

	// Sets the title on top of the Console window 
	static void SetTitle(string title)
	{
		system(("title " + title + " - Tom Zielinski and Rose Nguyen").c_str());
		//SetConsoleTitle(title.c_str()); //needs windows.h
	}

	// Receives the program title, format it into a banner, and returns it as string
	static string FormatBanner(string title, string description = "")
	{
		// These variables only exist within the method
		string banner = "";
		string line = "";

		// Draw line - length of line is title length + 4 
		for (int count = 0; count < title.length() + 4; count++)
		{
			line += '='; // add a '=' to the line
		}

		// Formats the banner and assign it to a variable
		if (description == "") {
			banner = line + "\n= " + title + " =\n" + line + "\n\n";
		}
		else {
			banner = line + "\n= " + title + " =\n" + line + "\n\n" + description + "\n\n";
		}

		// Returns formatted string banner
		return banner;
	}

	// Clear the console window
	static void Clear()
	{
		system("cls");
	}

	// Writes text on the Console 
	static void Write(string message)
	{
		cout << message;
	}

	// Writes a message in colour (foregroung and background)
	// If no background is passed, will use default black
	static void Write(string message, int foreColour, int backColour = Colour::Black)
	{
		// Get the Console handle (pointer to a system resource), so we can use its properties
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Calculate colour
		int colour = foreColour + (16 * backColour);
		
		// Set text colour
		SetConsoleTextAttribute(consoleHandle, colour);

		// Print message
		cout << message;

		// Set text colour back to default Grey
		SetConsoleTextAttribute(consoleHandle, Colour::Grey);
	}

	static void Write(char message, int foreColour, int backColour = Colour::Black)
	{
		// Get the Console handle (pointer to a system resource), so we can use its properties
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Calculate colour
		int colour = foreColour + (16 * backColour);

		// Set text colour
		SetConsoleTextAttribute(consoleHandle, colour);

		// Print message
		cout << message;

		// Set text colour back to default Grey
		SetConsoleTextAttribute(consoleHandle, Colour::Grey);
	}

	// Writes text on the Console ending with a line break 
	static void WriteLine(string message)
	{
		cout << message << "\n";
	}

	// Writes a message in colour (foreground and background) ending with a line break
	// If no background is passed, will use default black
	static void WriteLine(string message, int foreColour, int backColour = Colour::Black)
	{
		// Get the Console handle (pointer to a system resource), so we can use its properties
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

		// Calculate colour
		int colour = foreColour + (16 * backColour);
		
		// Set text colour
		SetConsoleTextAttribute(consoleHandle, colour);

		// Print message
		cout << message;

		// Set text colour back to default Grey
		SetConsoleTextAttribute(consoleHandle, Colour::Grey);
		cout << " \n";
	}

	// Reads user input and returns as string
	static string ReadLine()
	{
		string input;
		getline(cin, input);
		return input;
	}

	// Tries to convert a string (by value) into an integer (by reference)
	// returns true in case of sucess, false if failure
	static bool TryParse(string text, int &number)
	{
		// Tries to convert from string to int
		try
		{
			number = stoi(text); // float stof, double stod
		}

		// Not able to parse
		catch (exception e) 
		{
			return false;
		}

		// Able to parse
		return true;
	}

	// Writes a formatted error message in red foreground colour
	static void WriteError(string message)
	{
		WriteLine("Error - " + message, Colour::Red);
		//BeepNope();
		//Sleep(500);
	}

	// Beeps a "no" sound
	static void BeepNope()
	{
		Beep(300,100); // 300 hertz for 100 milliseconds     
		Beep(300,500); // 300 hertz for 500 milliseconds
	}

	// Beeps a "yes" sound
	static void BeepYep()
	{
		Beep(500,250); // 300 hertz for 100 milliseconds     
	}

};


