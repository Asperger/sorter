#include "parser.h"
// sorter.exe input_file output_file algorithm_type
int main(int argc, char** argv){ 
	if (argc != 4){cout << "Illegal command line" << endl; return 1;}
	// Declare the functional objects 
	AlgParser p; 
	AlgTimer t; 
	// Pass the arguement 1 as the input file name 
	if (!p.Parse(argv[1])) {cout << "Input file open error" << endl; return 1;}
	// Start timer 
	t.Begin(); 
	// Start sorting
	if (p.sort(argv[3])) cout << "Sorting complete" << endl;
	else {cout << "Illegal algorithm" << endl; return 1;}
	// Write the result
	if (!p.Write(argv[2])) {cout << "Output file open error" << endl; return 1;}
	// Display the accumulated time 
	cout << "The execution spends " << t.End() << " seconds" << endl; 
	//getchar();
	return 1; 
} 
