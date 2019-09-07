#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compstrings (char* str1, char* str2);

int swapper(char** index, int index1, int index2);

int filesize(FILE* fin);

char* fileread(FILE* fin, int fs);

int get_strcnt(char* onegin, int fs);

void get_strindex(char* onegin, char** index, int fs);

void qsstr(char** index, int left, int right);

void print(char** index, int strcnt, FILE* fout);

int is_digit_or_letter(char a);

/*!This program sorts input file. The result will be saved at output file.*/

int main()
{
    char finname[50];
    char foutname[50];
    printf("Input filename: ");
    scanf("%s", finname);
    printf("Output filename: ");
    scanf("%s", foutname);

    FILE *fin = fopen(finname, "r"), *fout = fopen(foutname, "w");
    int fs = filesize(fin);
    char* onegin = fileread(fin, fs);

    int strcnt = get_strcnt(onegin, fs);
    char** index = (char**)calloc(strcnt, sizeof(char*));
    assert(index != nullptr);
    get_strindex(onegin, index, fs);

    qsstr(index, 0, strcnt-1);
    print(index, strcnt, fout);

    free(onegin);
    fclose(fin);
    fclose(fout);

}

/*!This function puts strings saved in index[] to fout file
@param [in] index - array of sorted strings indexes.
@param [in] strcnt - count of strings in index[].
@param [in] fout - output file.*/

void print(char** index, int strcnt, FILE* fout)
{
    int i, j;
    for(i = 0; i < strcnt; ++i)
    {
        j = 0;
        while (is_digit_or_letter(index[i][j]) == -1)
            ++j;
        if (index[i][j] != '\0')
            fprintf(fout, "%s\n", index[i]);
    }
}

/*!This function returns a if a is digit, '\0', or a letter from lower register.
If a is a letter of upper register, it returns this letter in lower register for comparing.
If a is other symbol, it returns -1.
@param [in] a - char we need information about.  */

int is_digit_or_letter(char a)
{
    if (('a' <= a && a <= 'z') || ('0' <= a && a <= '9') || (a == '\0'))
        return a;
    if (('A' <= a && a <= 'Z'))
        return a - 'A' + 'a';
    else
        return -1;
}

/*!This function writes indexes of strings saved in one big string onegin (where strings are devided by '\n') to array index. Also it replaces '\n' with '\0'.
@param [in] onegin - input file turned to one string.
@param [in] index - array of indexes of strings.
@param [in] fs - size of onegin in bytes.*/

void get_strindex(char* onegin, char** index, int fs)
{
    int i, j = 0;
    index[j] = onegin;
    for(i = 1; i < fs; ++i)
        if (onegin[i] == '\n')
            {
                if (i != fs-1 || onegin[i+1] != '\0')
                    {
                        ++j;
                        index[j] = onegin+i+1;
                        onegin[i] = '\0';
                    }
            }
}

/*!This function returns count of strings in onegin.
@param [in] onegin - input file turned to one string.
@param [in] fs - size of onegin in bytes. */

int get_strcnt(char* onegin, int fs)
{
    int cnt = 0, i;
    for (i = 0; i < fs; ++i)
        if (onegin[i] == '\n') ++cnt;
    return cnt;
}

/*!This function returns count of characters in input file.
@param [in] fin - input file.*/

int filesize(FILE * fin)
{
    int needspace;
    fseek(fin, 0, 2);
    needspace = ftell(fin)+1;
    fseek(fin, 0, 0);
    return needspace;
}

/*!This function gets count of strings in onegin.
@param [in] fin - input file
@param [in] fs - size of file in bytes.*/

char* fileread(FILE * fin, int fs)
{
    char* onegin = (char*)calloc(fs, sizeof(char));
    assert(onegin != nullptr);
    fread(onegin, sizeof(char), fs, fin);
    return onegin;
}

/*!This function compares two strings.
Returns 1 if str1 > str2, returns -1 if str2 < str1, returns 0 if str1 = str2.
@param [in] str1 - first comparing string.
@param [in] str2 - second comparing string.*/

int compstrings(char* str1, char* str2)
{
    int i = 0, j = 0;
    char c1, c2;
    do
    {
        while (is_digit_or_letter(str1[i]) == -1)
            ++i;
        c1 = is_digit_or_letter(str1[i]);

        while (is_digit_or_letter(str2[j]) == -1)
            ++j;
        c2 = is_digit_or_letter(str2[j]);

        if (c1 > c2)
            return 1;
        if (c2 > c1)
            return -1;
        if (c1 == c2 && c2 == '\0')
            return 0;
        ++i; ++j;
    } while((str1[i] != '\0', str2[j] != '\0'));
    return 0;
}

/*!This function sorts strings in index[].
@param [in] index - array of indexes of strings.
@param [in] left - left index of sorting part of index.
@param [in] right - right index of sorting part of index.*/

void qsstr(char** index, int left, int right)
{
    int i, l;
    if (right - left == 1)
    {
        swapper(index, left, right);
        return;
    }
    if (right <= left)
        return;

    l = left;
    for(i = l+1; i <= right; i++)
        {
            if (compstrings(index[left], index[i]) == 1)
            {
                ++l;
                swapper(index, i, l);
            }
        }
    swapper(index, left, l);
    qsstr(index, left, l-1);
    qsstr(index, l+1, right);
}

/*!This function swaps two elements of array index.
@param [in] index - array of indexes of strings.
@param [in] index1 - index of first swapping element.
@param [in] index2 - index of second swapping element.*/

int swapper(char** index, int index1, int index2)
{
    char* d = index[index1];
    index[index1] = index[index2];
    index[index2] = d;
}
