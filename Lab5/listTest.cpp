#include <iostream>
#include "recursive.h"

using namespace std;

static bool list_equal(list_t l1, list_t l2)
// EFFECTS: returns true iff l1 == l2.
{
    if (list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if (list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if (list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }
}

int main()
{
    int i = 0;
    list_t listA, listA_answer;
    list_t listB;

    listA = list_make();
    listB = list_make();
    listA_answer = list_make();

    for (i = 5; i > 0; i--)
    {
        listA = list_make(i, listA);
        listB = list_make(i + 10, listB);
    }

    // list_print(listA);
    // cout << endl;
    // list_print(listB);
    // cout << endl;
    // list_print(first_n(listA, 2));
    // cout << endl;
    // list_print(first_n(listA, 4));
    // cout << endl;
    // list_print(last_n(listA, 2));
    // cout << endl;
    // list_print(last_n(listA, 4));
    // cout << endl;
    list_t listC = insert_list(listA, listB, 3);
    list_print(listC);
    cout << endl;
    listC = insert_list(listA, listB, 1);
    list_print(listC);
    cout << endl;
    return 0;
}
