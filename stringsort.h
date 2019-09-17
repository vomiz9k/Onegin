#ifndef STRINGSORT_H_INCLUDED
#define STRINGSORT_H_INCLUDED

int main();
struct indexes;
void print_all_to(FILE * fout, indexes* index, int string_count, char* onegin, int spam_size);

void swap(void* a, void* b, int el_size);

void my_qsort(void* arr, int cnt, int el_size, int (*comp)(const void* a, const void* b));

int comp_strings_start(const void* str1_pointer, const void* str2_pointer);
int comp_strings_end(const void* str1_pointer, const void* str2_pointer);

void print(indexes* index, int string_count, FILE* fout);

int file_size(FILE* fin);

int file_read(FILE* fin, int *size_of_file);

int get_string_count(char* onegin, int size_of_file);

void get_str_index(char* onegin, indexes* index, int string_count, int size_of_file);

int is_letter(char c);

void get_file_names(char* fin_name, char* fout_name);

void spam(FILE* fout, int spam_size);


//---------FOR UNIT TESTS---------
void unit_test();

void test_comp_strings_start();
void test_comp_strings_start_1();
void test_comp_strings_start_2();
void test_comp_strings_start_3();

void test_comp_strings_end();
void test_comp_strings_end_1();
void test_comp_strings_end_2();
void test_comp_strings_end_3();

void test_is_letter();

void test_my_qsort();
void test_my_qsort_1();
void test_my_qsort_2();
void test_my_qsort_3();

int easy_comp(const void* a, const void* b);
//--------------------------------


#endif
