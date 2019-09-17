#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stringsort.c"
#include "unit_tests.c"


const char KERN[] = "kernigan.txt", ONEG[] = "onegin.txt", OUTF[] = "output.txt";
const int FILENAMESIZE = 50, SPAMSIZE = 10;

/*!This program sorts strings in input file.*/


int main()
{
    char c = 'n';
    printf ("Make UNIT TESTS? (Y/N): ");
    c = getchar();
    printf ("\n");
    if (c == 'Y' || c == 'y')
        unit_test();

    char fin_name[FILENAMESIZE] = "", fout_name[FILENAMESIZE] = "";
    get_file_names (fin_name, fout_name);

    FILE *fin = fopen(fin_name, "r"), *fout = fopen (fout_name, "w");
    int size_of_file = file_size(fin);

    char* onegin = (char*) file_read(fin, &size_of_file);
    int string_count = get_string_count(onegin, size_of_file);

    struct indexes *index = (indexes*) calloc(string_count, sizeof(indexes));
    get_str_index(onegin, index, string_count, size_of_file);

    print_all_to(fout, index, string_count, onegin, SPAMSIZE);

    free   (index);
    free   (onegin);
    fclose (fin);
    fclose (fout);

    printf ("Success! Check the %s.", fout_name);

}





