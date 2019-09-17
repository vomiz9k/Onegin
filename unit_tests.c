#include "stringsort.h"
void unit_test()
{
    test_comp_strings_start();
    test_comp_strings_end();
    test_is_letter();
    test_my_qsort();
    printf ("\nUNIT_TEST FINISHED SUCCESSFULL\n\n---------------------\n\n");
}


void test_comp_strings_start()
{
    test_comp_strings_start_1();
    test_comp_strings_start_2();
    test_comp_strings_start_3();
    printf("comp_strings_start testing success\n");
}

void test_comp_strings_start_1()
{
    char *a = "\0abc\0cab";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 4;

    index2.start = a + 5;
    index2.ending = a + 8;

    assert(comp_strings_start((void*) &index1, (void*) &index2) == 'a'-'c');
    assert(comp_strings_start((void*) &index2, (void*) &index1) == 'c'-'a');
    assert(comp_strings_start((void*) &index1, (void*) &index1) == 0);
}

void test_comp_strings_start_2()
{
    char *a = "\0abc\0abcd";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 4;

    index2.start = a + 5;
    index2.ending = a + 9;

    assert(comp_strings_start((void*) &index1, (void*) &index2) == '\0' - 'd');
    assert(comp_strings_start((void*) &index2, (void*) &index1) == 'd' - '\0');
    assert(comp_strings_start((void*) &index1, (void*) &index1) == 0);
}

void test_comp_strings_start_3()
{
    char *a = "\0a\0\0";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 2;

    index2.start = a + 3;
    index2.ending = a + 4;

    assert(comp_strings_start((void*) &index1, (void*) &index2) == 'a');
    assert(comp_strings_start((void*) &index2, (void*) &index1) == -'a');
    assert(comp_strings_start((void*) &index2, (void*) &index2) == 0);
}


void test_comp_strings_end()
{
    test_comp_strings_end_1();
    test_comp_strings_end_2();
    test_comp_strings_end_3();
    printf("comp_strings_end testing success\n");
}

void test_comp_strings_end_1()
{
    char *a = "\0abc\0abcd";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 4;

    index2.start = a + 5;
    index2.ending = a + 9;

    assert(comp_strings_end((void*) &index1, (void*) &index2) == 'c' - 'd');
    assert(comp_strings_end((void*) &index2, (void*) &index1) == 'd' - 'c');
    assert(comp_strings_end((void*) &index2, (void*) &index2) == 0);
}

void test_comp_strings_end_2()
{
    char *a = "\0oabc\0abc\0";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 5;

    index2.start = a + 6;
    index2.ending = a + 9;

    assert(comp_strings_end((void*) &index1, (void*) &index2) == 'o');
    assert(comp_strings_end((void*) &index2, (void*) &index1) == -'o');
    assert(comp_strings_end((void*) &index2, (void*) &index2) == 0);
}

void test_comp_strings_end_3()
{
    char *a = "\0a\0\0";
    struct indexes index1, index2;

    index1.start = a + 1;
    index1.ending = a + 2;

    index2.start = a + 3;
    index2.ending = a + 4;

    assert(comp_strings_end((void*) &index1, (void*) &index2) == 'a');
    assert(comp_strings_end((void*) &index2, (void*) &index1) == -'a');
    assert(comp_strings_end((void*) &index2, (void*) &index2) == 0);
}


void test_is_letter()
{
    assert(is_letter('a') == 'a');
    assert(is_letter('A') == 'a');
    assert(is_letter('\n') == '\0');
    assert(is_letter('\0') == '\0');
    assert(is_letter('1') == -1);
    printf("is_letter  testing success\n");
}


void test_my_qsort()
{
    test_my_qsort_1();
    test_my_qsort_2();
    test_my_qsort_3();
    printf("my_qsort  testing success\n");
}

void test_my_qsort_1()
{
    char* a = "\0b\na\nc\ne\nd";
    struct indexes index[5];

    index[0].start = a+1; index[0].ending = a + 2;
    index[1].start = a+3; index[1].ending = a + 4;
    index[2].start = a+5; index[2].ending = a + 6;
    index[3].start = a+7; index[3].ending = a + 8;
    index[4].start = a+9; index[4].ending = a + 10;

    my_qsort(index, 5, sizeof(indexes), comp_strings_start);
    int i;
    for(i = 0; i < 4; ++i)
        assert(comp_strings_start((index+i), (index+i+1)) <= 0);;

}

void test_my_qsort_2()
{
    char* a = "\0b\na\nc\ne\nd";

    struct indexes index[5];
    index[0].start = a+1; index[0].ending = a + 2;
    index[1].start = a+3; index[1].ending = a + 4;
    index[2].start = a+5; index[2].ending = a + 6;
    index[3].start = a+7; index[3].ending = a + 8;
    index[4].start = a+9; index[4].ending = a + 10;

    my_qsort(index, 5, sizeof(indexes), comp_strings_end);
    int i;
    for(i = 0; i < 4; ++i)
        assert(comp_strings_end((index+i), (index+i+1)) <= 0);
}

void test_my_qsort_3()
{
    int arr[] = {2, 1, 3, 5, 4};

    my_qsort(arr, 5, sizeof(int), easy_comp);

    int i;
    for(i = 0; i < 4; ++i)
        assert(easy_comp((void*)&arr[i], (void*)&arr[i+1]) <= 0);
}


int easy_comp(const void* a, const void* b)
{
    return (*(int*)a-*(int*)b);
}
