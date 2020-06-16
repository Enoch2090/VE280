#include "ex1.h"

static list_t reverse_list(list_t list)
{
	list_t new_list = list_make();
	while (!list_isEmpty(list))
	{
		new_list = list_make(list_first(list), new_list);
		list = list_rest(list);
	}
	return new_list;
}

int dot(list_t v1, list_t v2)
{
	int res = 0;

	while ((!list_isEmpty(v1)) && (!list_isEmpty(v2)))
	{
		res += list_first(v1) * list_first(v2);
		v1 = list_rest(v1);
		v2 = list_rest(v2);
	}
	return res;
}

list_t filter_odd(list_t list)
{
	list = reverse_list(list);
	list_t new_list = list_make();
	int curr;
	while (!list_isEmpty(list))
	{
		curr = list_first(list) < 0 ? (-list_first(list)) : (list_first(list));
		if (curr % 2 == 1)
		{
			new_list = list_make(list_first(list), new_list);
		}
		list = list_rest(list);
	}
	return new_list;
}

list_t filter(list_t list, bool (*fn)(int))
{
	list = reverse_list(list);
	list_t new_list = list_make();
	while (!list_isEmpty(list))
	{
		if (fn(list_first(list)))
		{
			new_list = list_make(list_first(list), new_list);
		}
		list = list_rest(list);
	}
	return new_list;
}
