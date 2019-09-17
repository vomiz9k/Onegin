#include "stringsort.h"

struct indexes
{
char* start;
char* ending;
};

/*!Function gets files names.
@param [in] fin_name - input file name variable.
@param [in] fout_name - output file name variable*/
void get_file_names (char* fin_name, char* fout_name)
{
    printf ("Input filename: ");
    scanf ("%s", fin_name);

    printf ("Output filename: ");
    scanf ("%s", fout_name);
}

/*!This function returns count of characters in input file.
@param [in] fin - input file.*/
int file_size (FILE * fin)
{
    int needspace = 0;
    fseek (fin, 0, 2);
    needspace = ftell (fin);
    assert (needspace > 0);
    fseek (fin, 0, 0);
    return needspace;
}

/*!This function returns count of strings in onegin.
@param [in] fin - input file
@param [in] size_of_file - size of file in bytes.*/
int file_read(FILE * fin, int *size_of_file)
{
    char* file_pointer = (char*) calloc (*size_of_file+1, sizeof(char));;
    assert (file_pointer != nullptr);

    int symbols = fread (file_pointer, sizeof(char), *size_of_file, fin);
    file_pointer[symbols] = 0;
    *size_of_file = symbols;

    return (int)file_pointer;
}

/*!This function returns count of strings in onegin.
@param [in] onegin - input file turned to one string.
@param [in] size_of_file - size of onegin in bytes. */
int get_string_count(char* onegin, int size_of_file)
{
    int cnt = 0, i = 0;
    for (i = 0; i < size_of_file; ++i)

        if (onegin[i] == '\n')
            ++cnt;

    return cnt;
}

/*!This function writes pointers of strings saved in one big string onegin (where strings are devided by '\n') to array index. Also it replaces '\n' with '\0'.
@param [in] onegin - input file turned to one string.
@param [in] index - array of pointers of strings.
@param [in] size_of_file - size of onegin in bytes.
@param [in] parameter - bool variable(true = sort by last symbols, false == sort by first symbols)*/
void get_str_index(char* onegin, indexes* index, int string_count, int size_of_file)
{
    assert (index != nullptr);
    int i = 0, j = 0;
    index[j].start = onegin;
    for(i = 0; i < size_of_file && j < string_count; ++i)

        if (onegin[i] == '\n')
        {
            index[j].ending = onegin + i;
            ++j;
            if (j < string_count)
                index[j].start = onegin + i + 1;
            //onegin[i] = '\0';
        }

}

/*!Thif func prints all things that we needed in file fout.
@param [in] fout - file we need to write in.
@param [in] index - array of struct indexes, in the right order.
@param [in] string_count - count of strings we need to write. Also count of elements in index.
@param [in] onegin - pointer on original text.
@param [in] spam_size - size of spam we need to put between texts.*/
void print_all_to(FILE * fout, indexes* index, int string_count, char* onegin, int spam_size)
{
    my_qsort (index, string_count, sizeof(indexes), comp_strings_end);
    print (index, string_count, fout);

    spam (fout, spam_size);

    my_qsort (index, string_count, sizeof(indexes), comp_strings_start);
    print (index, string_count, fout);

    spam (fout, spam_size);

    fprintf (fout, "%s", onegin);
}

/*! Analog of default qsort function.
@param [in] arr - array we need to sort.
@param [in] cnt - count of elements in array.
@param [in] el_size - size of element in array.
@param [in] comp - comparing function.*/
void my_qsort(void* arr, int cnt, int el_size, int (*comp)(const void* a, const void* b))
{
    int i = 1, j = 0;
    if (cnt <= 1)
        return;
    if (cnt == 2)
    {
        swap (arr, (arr+el_size), el_size);
        return;
    }
    swap ((arr+el_size*(cnt/2)), arr, el_size);
    for (i = 1; i < cnt; ++i)
    {
            if (comp (arr, (arr+i*el_size)) > 0)
            {
                ++j;
                swap ((arr+i*el_size), (arr+el_size*j), el_size);

            }

        }
    swap (arr, (arr+j*el_size), el_size);
    my_qsort (arr, j, el_size, comp);
    my_qsort (arr+el_size*(j+1), cnt-j-1, el_size, comp);
}

/*!This function compares two strings by first letters.
Returns 1 if str1 > str2, returns -1 if str2 < str1, returns 0 if str1 = str2.
@param [in] str1_pointer - pointer on pointer on string 1.
@param [in] str2_pointer - pointer on pointer on string 2*/
int comp_strings_start(const void* str1_pointer, const void* str2_pointer)
{
    int i = 0, j = 0;
    indexes index1 = *(indexes*) str1_pointer, index2 = *(indexes*) str2_pointer;
    char c1 = 0, c2 = 0;
    int size1 = index1.ending - index1.start, size2 = index2.ending - index2.start;

    do
    {
        while (is_letter (*(index1.start + i)) < 0 && i < size1)
            ++i;
        while (is_letter (*(index2.start + j)) < 0 && j < size2)
            ++j;

        c1 = is_letter (*(index1.start+i));
        c2 = is_letter (*(index2.start+j));

        if ((c1 == '\0' || c2 == '\0' || c1 != c2))
            return c1 - c2;

        ++i; ++j;

    } while(i < size1 || j < size2);
    return c1 - c2;
}

/*!This function compares two strings by first letters.
Returns 1 if str1 > str2, returns -1 if str2 < str1, returns 0 if str1 = str2.
@param [in] str1_pointer - pointer on pointer on string 1.
@param [in] str2_pointer - pointer on pointer on string 2*/
int comp_strings_end(const void* str1_pointer, const void* str2_pointer)
{
    int i = 0, j = 0;
    char c1 = 0, c2 = 0;
    indexes index1 = *(indexes*) str1_pointer, index2 = *(indexes*) str2_pointer;
    int size1 = (int) (index1.ending - index1.start), size2 = (int) (index2.ending - index2.start);
    do
    {
        ++i; ++j;

        while (is_letter (*(index1.ending-i)) < 0 && i < size1)
            ++i;

        while (is_letter (*(index2.ending-j)) < 0 && j < size2)
            ++j;

        c1 = is_letter (*(index1.ending-i));
        c2 = is_letter (*(index2.ending-j));

        if (c1 == '\0' || c2 == '\0' || c1 != c2)
            return c1 - c2;

    } while (i < size1 || j < size2);
    return c1 - c2;
}

/*!This functions swap 2 elements by bytes.
@param [in] a - pointer of element 1
@paran [in] b - pointer of element 2*/
void swap(void* a, void* b, int el_size)
{
    int i = 0;
    char char_cch;
    for (i = 0; i < el_size; ++i)
    {
        char_cch = *(char*) (a + i);
        *(char*) (a + i) = *(char*) (b + i);
        *(char*) (b + i) = char_cch;
    }
}

/*!This function returns a if a is '\0' or a letter from lower register.
If a is a letter of upper register, it returns this letter in lower register for comparing.
If a is other symbol, it returns -1.
@param [in] a - char we need information about.  */
int is_letter(char c)
{
    if (('a' <= c && c <= 'z') || (c =='\0'))
        return c;
    if (c == '\n')
        return '\0';
    if (('A' <= c && c <= 'Z'))
        return c - 'A' + 'a';
    else
        return -1;
}

/*!This function puts strings saved in index[] to fout file for text sorted by first letters.
@param [in] index - array of sorted strings indexes.
@param [in] string_count - count of strings in index[].
@param [in] fout - output file.*/
void print(indexes* index, int string_count, FILE* fout)
{
    int i = 0;
    char *j = index[i].start;
    for(i = 0; i < string_count; ++i)
    {
        j = index[i].start;
        while (is_letter(*j) < 0)
            ++j;
        if (j < index[i].ending)
        {
            *index[i].ending = '\0';
            fprintf (fout, "%s\n", index[i].start);
            *index[i].ending = '\n';
        }
    }
}










/*! This function spams 50 empty strings in file
@param [in] fout - file we need to spam in.*/
void spam(FILE* fout, int spam_size)
{
    int i = 0;
    for (i = 0; i < spam_size; ++i)
        fprintf(fout, " %c ", '\n');
}







