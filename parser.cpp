#include "parser.h"
#include <cctype>
#include <cassert>

void AlgTimer::Begin(void)
{
	begin_clock = clock();
}

double AlgTimer::End(void)
{
	return ((double)(clock() - begin_clock) / (double)CLOCKS_PER_SEC);
}

int AlgString::cmp(AlgString s)
{
	int leng = min(m_string.length(),s.m_string.length());
	int i = 0, j = 0;
	while (i < leng && j < leng){
		while (!isalpha(m_string[i])) i++;
		while (!isalpha(s.m_string[j])) j++;
		if (tolower(m_string[i]) > tolower(s.m_string[j])) return 1;
		if (tolower(m_string[i]) < tolower(s.m_string[j])) return -1;
		i++;
		j++;
		}
	if (m_string.length() > s.m_string.length()) return 1;
	if (m_string.length() < s.m_string.length()) return -1;
	return 0;
}

void AlgParser::Parse(const char* input_file_name)
{
	string_vector.clear();
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
		if (s.find_first_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos)
			string_vector.push_back(AlgString(s, ++word_count));
		}
	fin.close();
	input_size = string_vector.size();
}

void AlgParser::Write(const char* output_file_name)
{
	fstream fout;
	fout.open(output_file_name, fstream::out);
	if (!fout.is_open()){
		cout << "Output file open error" << endl;
		exit(0);
		}
	fout << input_size << endl;
	for (int i = 0; i < input_size; i++)
		fout << string_vector[i].m_string << " " << string_vector[i].m_word_number << endl;
	fout.close();
}

void AlgParser::swap(const int& ith, const int& jth)
{
	assert(ith < input_size && ith >= 0);
	assert(jth < input_size && jth >= 0);
	AlgString temp(string_vector[ith].m_string, string_vector[ith].m_word_number);
	string_vector[ith].m_string = string_vector[jth].m_string;
	string_vector[ith].m_word_number = string_vector[jth].m_word_number;
	string_vector[jth].m_string = temp.m_string;
	string_vector[jth].m_word_number = temp.m_word_number;
}

bool AlgParser::sort(const char* alg)
{
	switch (*alg){
		case 'i':
			insertionsort();
			break;
		case 'm':
			mergesort(0, input_size-1);
			break;
		case 'h':
			heapsort();
			break;
		case 'q':
			quicksort(0, input_size-1);
			break;
		case 'b':
			bubblesort();
			break;
		default: return false;
	}
	return true;
}

void AlgParser::insertionsort(){
	for (int i = 1; i < input_size; i++){
		int j = i;
		while (j > 0 && string_vector[j-1] > string_vector[j]){
			swap(j, j-1);
			j--;
		}
	}
}

void AlgParser::mergesort(const int& left, const int& right){
	if (left < right){
		int mid = (left + right)/2;
		mergesort(left, mid);
		mergesort(mid+1, right);
		merge(left, mid, right);
	}
}

void AlgParser::merge(const int& left, const int& mid, const int& right){
	int ln = mid - left + 1;
	int rn = right - mid;
	vector<AlgString> L;
	vector<AlgString> R;
	int i, j, k;
	for (i = 0; i < ln; i++) L.push_back(string_vector[left + i]);
	for (j = 0; j < rn; j++) R.push_back(string_vector[mid + j + 1]);
	i = 0;
	j = 0;
	for (k = left; k <= right; k++){
		if (j == R.size()) string_vector[k] = L[i++];
		else if (i == L.size()) string_vector[k] = R[j++];
		else if (L[i] <= R[j]) string_vector[k] = L[i++];
		else string_vector[k] = R[j++];
	}
}

void AlgParser::heapsort(){
	build_heap();
	for (int i = input_size - 1; i > 0; i--){
		swap(0, i);
		heap_size--;
		heapify(0);
	}
}

void AlgParser::build_heap(){
	heap_size = input_size;
	for (int i = input_size/2; i >= 0; i--)
		heapify(i);
}

void AlgParser::heapify(const int& i){
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	assert(l < input_size && l >= 0);
	assert(r < input_size && r >= 0);
	int largest;
	if (l < heap_size && string_vector[l] > string_vector[i]) largest = l;
	else largest = i;
	if (r < heap_size && string_vector[r] > string_vector[largest]) largest = r;
	if (largest != i){
		swap(i, largest);
		heapify(largest);
	}
}

void AlgParser::quicksort(const int& left, const int& right){
	if (left < right){
		int p = partition(left, right);
		quicksort(left, p - 1);
		quicksort(p + 1, right);
	}
}

int AlgParser::partition(const int& left, const int& right){
	AlgString temp = string_vector[right];
	int i = left - 1;
	int j = right + 1;
	while (i < j){
		while (string_vector[++i] < temp) if (i == right) break;
		while (string_vector[--j] > temp) if (j == left) break;
		assert(i <= right && i >= left);
		assert(j <= right && j >= left);
		if (i < j) swap(i, j);
	}
	swap(i, right);
	return i;
}

void AlgParser::bubblesort(){
	int l = input_size;
	while (l != 0){
		int n = 0;
		for (int i = 1; i < l; i++){
			if (string_vector[i-1] > string_vector[i]){
				swap(i, i-1);
				n = i;
			}
		}
		l = n;
	}
}
