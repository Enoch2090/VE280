#include <iostream>
#include <cassert>
#include "recursive.h"

using namespace std;

// Implementation of the list ADT
const unsigned int list_node_id = 0x11341134;
const unsigned int list_empty_id = 0x22452245;

struct list_node
{
    unsigned int ln_id;        // Are we really a list_node?
    int ln_elt;                // This element
    struct list_node *ln_rest; // rest of this list, null for empty node
} list_node_t;

static struct list_node *
list_checkValid(list_t list)
// MODIFIES: cerr
// EFFECTS: assert if lnp does not appear to be a valid list.
//          writing an appropriate error message to cerr.
{
    struct list_node *lnp = (struct list_node *)list;

    if ((lnp->ln_id != list_node_id) && (lnp->ln_id != list_empty_id))
    {
        cerr << "Error: user passed invalid list\n";
        assert(0);
    }

    return lnp;
}

static void
list_checkNonEmpty(list_t list)
// MODIFIES: cerr
// EFFECTS: assert if lnp is an empty list,
//          writing an appropriate error message to cerr.
{
    if (list_isEmpty(list))
    {
        cerr << "error: user passed empty list where non-empty requried\n";
        assert(0);
    }
}

static void
not_allocated()
{
    cerr << "Your test case is too large for this machine\n";
    cerr << "Try using a smaller test case\n";
    assert(0);
}

bool list_isEmpty(list_t list)
{
    struct list_node *lnp = list_checkValid(list);
    return (lnp->ln_id == list_empty_id);
}

list_t
list_make()
{
    struct list_node *newp = 0;

    try
    {
        newp = new struct list_node;
    }
    catch (bad_alloc a)
    {
        not_allocated();
    }

    newp->ln_id = list_empty_id;
    newp->ln_rest = NULL;

    return (list_t)(newp);
}

list_t
list_make(int elt, list_t list)
{
    struct list_node *newp = 0;
    struct list_node *restp = list_checkValid(list);

    try
    {
        newp = new struct list_node;
    }
    catch (bad_alloc a)
    {
        not_allocated();
    }

    newp->ln_id = list_node_id;
    newp->ln_elt = elt;
    newp->ln_rest = restp;

    return (list_t)(newp);
}

int list_first(list_t list)
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return lnp->ln_elt;
}

list_t
list_rest(list_t list)
{
    list_checkNonEmpty(list);
    struct list_node *lnp = list_checkValid(list);
    return (list_t)(lnp->ln_rest);
}

static void
list_print_helper(list_t list)
// MODIFIES: cout
// EFFECTS: prints list contents to cout, with no parens
{
    if (list_isEmpty(list))
    {
        return;
    }
    else
    {
        cout << list_first(list) << " ";
        list_print_helper(list_rest(list));
    }
}

void list_print(list_t list)
{
    cout << "( ";
    list_print_helper(list);
    cout << ")";
}

int list_len(list_t list)
{
    int len = 0;
    while (!list_isEmpty(list))
    {
        len++;
        list = list_rest(list);
    }
    return len;
}

list_t first_n(list_t list, int n)
{
    list_t list_out = list_make();
    for (int i = 0; i < n; i++)
    {
        list_out = list_make(list_first(list), list_out);
        list = list_rest(list);
    }
    return reverse_list(list_out);
}

list_t last_n(list_t list, int n)
{
    int len = list_len(list);
    if (len > n)
    {
        for (int i = 0; i < len - n; i++)
        {
            list = list_rest(list);
        }
        return list;
    }
    else
    {
        throw 0;
    }
}

list_t list_concat(list_t L1, list_t L2)
{
    if (list_isEmpty(L2))
    {
        return L1;
    }
    else
    {
        list_t new_list = list_make(list_first(L2), L1);
        return list_concat(new_list, list_rest(L2));
    }
}

list_t reverse_list(list_t list)
{
    list_t new_list = list_make();
    while (!list_isEmpty(list))
    {
        new_list = list_make(list_first(list), new_list);
        list = list_rest(list);
    }
    return new_list;
}

list_t insert_list(list_t first, list_t second, int n)
{
    n++;
    list_t list_fN = first_n(first, n);
    list_t list_lN = last_n(first, list_len(first) - n);
    return list_concat(list_lN, reverse_list(list_concat(second, reverse_list(list_fN))));
}