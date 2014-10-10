#include "parser.h"
#include <cctype>

void AlgTimer::Begin(void)
{
	begin_clock = clock();
}

double AlgTimer::End(void)
{
	return ( (double)( clock() - begin_clock ) / (double)CLOCKS_PER_SEC );
}

int AlgString::cmp(AlgString s)
{
	int leng = min(m_string.length(),s.m_string.length());
	int i = 0, j = 0;
	while (i < leng && j < leng){
		while (!isalpha(m_string[i])) i++;
		while (!isalpha(s.m_string[j])) j++;
		if (m_string[i] > s.m_string[j]) return 1;
		if (m_string[i] < s.m_string[j]) return -1;
		i++;
		j++;
		}
	if (m_string.length() > s.m_string.length()) return 1;
	if (m_string.length() < s.m_string.length()) return -1;
    return 0;
}

void AlgParser::Parse(const char* input_file_name)
{
	lex_string_vector.clear();
	fstream fin;
	fin.open(input_file_name, fstream::in);
	if (!fin.is_open()){
       cout << "Input file open error" << endl;
       exit(0);
       }
	int word_count = 0;
	string s;
	while (!fin.eof()){
		fin >> s;
		lex_string_vector.push_back(AlgString(s, ++word_count));
		}
	fin.close();
}

void AlgParser::Write(const char* output_file_name)
{
	fstream fout;
	fout.open(output_file_name, fstream::out);
	if (!fout.is_open()){
       cout << "Output file open error" << endl;
       exit(0);
       }
    fout << lex_string_vector.size() << endl;
    for (int i = 0; i < lex_string_vector.size(); i++)
    	fout << QueryString(i) << " " << QueryWordNumber(i) << endl;
    fout.close();
}

string AlgParser::QueryString(const int& ith)
{
	if(ith >= (signed)lex_string_vector.size()){
		printf("The querying of index %d exceeds the number of strings\n", ith);
		exit(0);
		}
	if(ith < 0){
		printf("The querying index can't be negative\n");
		exit(0);
		}
	return lex_string_vector[ith].m_string;
}

int AlgParser::QueryWordNumber(const int& ith)
{
    if(ith >= (signed)lex_string_vector.size()){
        printf("The querying of index %d exceeds the number of strings\n", ith);
		exit(0);
    }
    if(ith < 0){
        printf("The querying index can't be negative\n");
		exit(0);
    }
	return lex_string_vector[ith].m_word_number;
}

void AlgParser::swap(const int& ith, const int& jth)
{
     AlgString temp(lex_string_vector[ith].m_string, lex_string_vector[ith].m_word_number);
     lex_string_vector[ith].m_string = lex_string_vector[jth].m_string;
     lex_string_vector[ith].m_word_number = lex_string_vector[jth].m_word_number;
     lex_string_vector[jth].m_string = temp.m_string;
     lex_string_vector[jth].m_word_number = temp.m_word_number;
}

bool AlgParser::sort(const string& alg)
{
     switch (alg[0]){
            case 'i':
                  
                 break;
            case 'm': 
                 
                 break;
            case 'h': 
                 
                 break;
            case 'q': 
                 
                 break;
            case 'b': 
                 
                 break;
            default: return false;
            }
     return true;
}
