#include <string>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
using namespace std;

class AlgString{
	public:
	string m_string; 
	int m_word_number;
	
	AlgString(){};
	AlgString(const string& set_string, const int& set_word_number){
		m_string = set_string;
		m_word_number = set_word_number;
		};
	bool operator>(AlgString s){if (cmp(s) > 0) return true; else return false;};
	bool operator>=(AlgString s){if (cmp(s) >= 0) return true; else return false;};
	bool operator<(AlgString s){if (cmp(s) < 0) return true; else return false;};
	bool operator<=(AlgString s){if (cmp(s) <= 0) return true; else return false;};
	bool operator==(AlgString s){if (cmp(s) == 0) return true; else return false;};
	
	private:
	int cmp(AlgString);
};

class AlgParser
{
	public:
	AlgParser(){};
	// Specify the parsing file name and then parse the file
	void Parse(const char*);
	// Write the sorted array to the specified file
	void Write(const char*);
	// Return the ith string in the file
	string QueryString(const int&);
	// Return the number of the ith string in the file
	int QueryWordNumber(const int&);
	// Swap the contents of ith and jth strings
	void swap(const int&, const int&);
	// Sort the vector with assigned algorithm
	bool sort(const string&);
	
	private:
	vector<AlgString> lex_string_vector;
};

class AlgTimer
{
	public:
	long begin_clock;
	
	AlgTimer(){};
	// Strat the timer
	void Begin();
	// Return the accumulated time in seconds
	double End();
};
