/*
 * recursive.h
 * 
 * A simple interface to two recursively-defined, applicative
 * structures, lists and trees.
 */

#ifndef __RECURSIVE_H__
#define __RECURSIVE_H__

/*
 * lists
 *
 * A well-formed list is either:
 *      the empty list
 *   or an integer followed by a well-formed list.
 *
 * Lists are applicative (functional) data structures---in other
 * words, they are immutable.
 */

/*
 * We define lists using the following type declaration.  Don't worry
 * if you don't understand what this means---we haven't covered the
 * syntax for this sort of declaration yet.  For the purposes of this
 * project, just assume that "list_t" is the name of a type that you can
 * use just like "int" or "double".
 */

struct opaque_list;
typedef opaque_list *list_t;

extern bool list_isEmpty(list_t list);
// EFFECTS: returns true if list is empty, false otherwise

list_t list_make();
// EFFECTS: returns an empty list.

list_t list_make(int elt, list_t list);
// EFFECTS: given the list (list) make a new list consisting of
//          the new element followed by the elements of the
//          original list.

extern list_t insert_list(list_t first, list_t second, int n);
// REQUIRES:
// EFFECTS:

extern list_t reverse_list(list_t list);
// REQUIRES:
// EFFECTS:

extern list_t first_n(list_t list, int n);

extern list_t last_n(list_t list, int n);

extern list_t list_concat(list_t L1, list_t L2);

int list_len(list_t list);

extern int list_first(list_t list);
// REQUIRES: list is not empty
// EFFECTS: returns the first element of list

extern list_t list_rest(list_t list);
// REQUIRES: list is not empty
// EFFECTS: returns the list containing all but the first element of list

extern void list_print(list_t list);
// MODIFIES: cout
// EFFECTS: prints list to cout.
#endif /* __RECURSIVE_H__ */
