//merge sort


int merge_sort(t_dir *dir, bool(*ordered)(t_data *a, t_data *b))
{
	sort(dir->content, dir->entry_nb, ordered);

	return (OK);
}

static t_list *sort(t_list *lst, unsigned int len, bool(*ordered)(t_data *a, t_data *b))
{

	if (len < 2)
	{
		return;
	}

	unsigned int	l_len = len / 2;
	unsigned int	r_len = len - l_len;

	t_list	*l_lst = list;
	t_list	*r_lst = list;
	for (int i = 0; i < l_len; ++i)
	{
		r_lst = r_Lst->next;
	}
	
	l_lst = sort(l_lst, l_len, ordered);
	r_lst = sort(r_lst, r_len, ordered);

	return merge(l_lst, r_lst, l_len, r_len, ordered);
}

static t_list *merge(t_list *l_lst, t_list *r_lst, unsigned int l_len, unsigned int r_len, bool(*ordered)(t_data *a, t_data *b))
{
	t_list	*merged = NULL;
	t_list	*current = NULL;
	t_list	*next	= NULL;

	while (l_len && r_len)
	{
		if (sort_by_func(l_lst->content, r_lst->content, ordered))
		{
			next = l_lst;
			l_lst = l_lst->next;
			--l_len;
		}
		else
		{
			next = r_lst;
			r_lst = r_lst->next;
			--r_len;
		}
		if (merged == NULL)
		{
			merged = next;
		}
		else
		{
			current->next = next;
		}
		current = next;
	}

	while (l_len)
	{
		if (merged == NULL)
		{
			merged = l_lst;
		}
		else
		{
			current->next = l_lst;
		}
		current = next;
		--l_len;
	}

	while (r_len)
	{
		if (merged == NULL)
		{
			merged = r_lst;
		}
		else
		{
			current->next = r_lst;
		}
		current = next;
		--r_len;
	}

	return (merged);

}
