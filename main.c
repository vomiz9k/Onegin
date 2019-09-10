#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int compstringsStart(const void* pstr1, const void* pstr2);
int compstringsEnd(const void* pstr1, const void* pstr2);

int filesize(FILE* fin);

char* fileread(FILE* fin, int fs);

int get_strcnt(char* onegin, int fs);

void get_strindex(char* onegin, char** index, int fs, bool parameter);

void printStart(char** index, int strcnt, FILE* fout);
void printEnd(char** index, int strcnt, FILE* fout);

int is_letter(char a);

/*!This program sorts input file by first or end letters. The result will be saved at output file.*/

int main()
{
    char finname[50];// = "onegin.txt";
    char foutname[50];// = "out.txt";
    printf("Input filename: ");
    scanf("%s", finname);
    printf("Output filename: ");
    scanf("%s", foutname);

    char param[1];
    printf("Sort by last symbols? (Y/N): ");
    scanf("%s", param);
    bool parameter = false;
    if (param[0] == 'Y')
        parameter = true;

    FILE *fin = fopen(finname, "r"), *fout = fopen(foutname, "w");
    int fs = filesize(fin);
    char* onegin = fileread(fin, fs);;

    int strcnt = get_strcnt(onegin, fs);

    char** index = (char**)calloc(strcnt, sizeof(char*));
    assert(index != nullptr);
    get_strindex(onegin, index, fs, parameter);

    if (parameter == true)
    {
        qsort(index, strcnt, sizeof(int), compstringsEnd);
        printEnd(index, strcnt, fout);
    }
    else
    {
        qsort(index, strcnt, sizeof(int), compstringsStart);
        printStart(index, strcnt, fout);
    }

    free(onegin);
    fclose(fin);
    fclose(fout);

}

/*!This function puts strings saved in index[] to fout file (if parameter == false)
@param [in] index - array of sorted strings indexes.
@param [in] strcnt - count of strings in index[].
@param [in] fout - output file.*/

void printEnd(char** index, int strcnt, FILE* fout)
{
    int i;
    for(i = 0; i < strcnt; ++i)
    {
        char* j = index[i] - 1;
        while (is_letter(*j) == -1)
            --j;
        if (*j != '\0')
        {
            while (*j != '\0')
                --j;
            fprintf(fout, "%s\n", j+1);
        }
    }
}

/*!This function puts strings saved in index[] to fout file (if parameter == true)
@param [in] index - array of sorted strings indexes.
@param [in] strcnt - count of strings in index[].
@param [in] fout - output file.*/

void printStart(char** index, int strcnt, FILE* fout)
{
    int i, j;
    for(i = 0; i < strcnt; ++i)
    {
        j = 0;
        while (is_letter(index[i][j]) == -1)
            ++j;
        if (index[i][j] != '\0')
            fprintf(fout, "%s\n", index[i]);
    }
}

/*!This function returns '\0' or a letter from lower register.
If a is a letter of upper or lower register, it returns this letter in lower register for comparing.
If a is other symbol, it returns -1.
@param [in] a - char we need information about.  */

int is_letter(char a)
{
    if (('a' <= a && a <= 'z') || /*('0' <= a && a <= '9') ||*/ (a == '\0'))
        return a;
    if (('A' <= a && a <= 'Z'))
        return a - 'A' + 'a';
    else
        return -1;
}

/*!This function writes indexes of strings saved in one big string onegin (where strings are devided by '\n') to array index. Also it replaces '\n' with '\0'.
@param [in] onegin - input file turned to one string.
@param [in] index - array of indexes of strings.
@param [in] fs - size of onegin in bytes.
@param [in] parameter - bool variable(true = sort by last symbols, false == sort by first symbols)*/

void get_strindex(char* onegin, char** index, int fs, bool parameter)
{
    int i, j = 0;
    if (parameter == false) // for first letters
    {
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
    else                    // for last letters
        for(i = 0; i < fs; ++i)
            if (onegin[i] == '\n')
                {
                    index[j] = onegin+i;
                    ++j;
                    onegin[i] = '\0';
                }
            else if (onegin[i] =='\0')
                {
                    index[j] = onegin + i;
                    break;
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
    needspace = ftell(fin);
    fseek(fin, 0, 0);
    return needspace;
}

/*!This function returns count of strings in onegin.
@param [in] fin - input file
@param [in] fs - size of file in bytes.*/

char* fileread(FILE * fin, int fs)
{
    void* firstpointer = calloc(fs+2, sizeof(char));
    assert(firstpointer != nullptr);
    char* nullsymbol =(char*)firstpointer;
    nullsymbol[0] = '\0';
    fread(nullsymbol+1, sizeof(char), fs, fin);
    return nullsymbol+1;
}

/*!This function compares two strings by first letters.
Returns 1 if str1 > str2, returns -1 if str2 < str1, returns 0 if str1 = str2.
@param [in] pstr1 - pointer on pointer on string 1.
@param [in] pstr2 - pointer on pointer on string 2*/

int compstringsStart(const void* pstr1, const void* pstr2)
{
    int i = 0, j = 0;
    char *str1 = *(char**)pstr1, *str2 = *(char**)pstr2;
    char c1, c2;
    do
    {
        while (is_letter(str1[i]) == -1)
            ++i;
        c1 = is_letter(str1[i]);

        while (is_letter(str2[j]) == -1)
            ++j;
        c2 = is_letter(str2[j]);

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
/*!This function compares two strings by first letters.
Returns 1 if str1 > str2, returns -1 if str2 < str1, returns 0 if str1 = str2.
@param [in] pstr1 - pointer on pointer on string 1.
@param [in] pstr2 - pointer on pointer on string 2*/

int compstringsEnd(const void* pstr1, const void* pstr2)
{
    int i = 1, j = 1;
    char *str1 = *(char**)pstr1, *str2 = *(char**)pstr2;
    char c1, c2;
    do
    {
        while (is_letter(*(str1-i)) == -1)
            ++i;
        c1 = is_letter(*(str1-i));

        while (is_letter(*(str2-j)) == -1)
            ++j;
        c2 = is_letter(*(str2-j));
        if (c1 > c2)
            return 1;
        if (c2 > c1)
            return -1;
        if (c1 == c2 && c2 == '\0')
            return 0;
        ++i; ++j;
        } while((*(str1-i)) != '\0', (*(str2-j)) != '\0');
    return 0;
}
