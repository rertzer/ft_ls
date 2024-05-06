# 42 school libft project

The aim of this project is to create a C library reimplementing some standard C functions
and some extra ones.

## implemented functions
### libc functions

| function | library | include |
|:---------|:--------|:--------|
| isalpha | standard | ctype.h |
| isdigit | standard | ctype.h |
|isalnum | standard | ctype.h |
|isascii | standard | ctype.h |
|isprint | standard | ctype.h |
|strlen | standard | string.h |
|memset | standard | string.h |
|bzero | standard | strings.h |
|memmove | standard | string.h |
|strlcpy | bsd | bsd/string.h |
|strlcat | bsd | bsd/string.h |
|toupper | standard | ctype.h |
|tolower | standard | ctype.h |
|strchr | standard | string.h |
|strrchr | standard | string.h |
|strncmp | standard | string.h |
|memchr | standard | string.h |
|memcmp | standard | string.h |
|strnstr | standard | string.h |
|atoi | standard | stdlib.h |
|calloc | standard | stdlib.h |
|strdup | standard | string.h |


### additional functions
|name|usage|
|:----------------|:---------|
|ft_substr | char *ft_substr(char const *s, unsigned int start, size_t len);
| | Allocates (with malloc(3)) and returns a substring from the string ’s’. The substring begins at index ’start’ and is of maximum size ’len’.|
|ft_strjoin | char *ft_strjoin(char const *s1, char const *s2);|
| | Allocates (with malloc(3)) and returns a new string, which is the result of the concatenation of ’s1’ and ’s2’.|
|ft_strtrim | char *ft_strtrim(char const *s1, char const *set);|
| | Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters specified in ’set’ removed from the beginning and the end of the string.|
|ft_split | char **ft_split(char const *s, char c);|
| | Allocates (with malloc(3)) and returns an array of strings obtained by splitting ’s’ using the character ’c’ as a delimiter. The array must end with a NULL pointer.|
|ft_itoa | char *ft_itoa(int n);|
| | Allocates (with malloc(3)) and returns a string representing the integer received as an argument. Negative numbers must be handled.|
|ft_strmapi | char *ft_strmapi(char const *s, char (*)(unsigned int, char));|
| | Applies the function ’f’ to each character of the string ’s’, and passing its index as first argument to create a new string (with malloc(3)) resulting from successive applications of ’f’.|
|ft_striteri | void ft_striteri(char *s, void(*)(unsigned int, char *));|
| | Applies the function ’f’ on each character of the string passed as argument, passing its index as first argument. Each character is passed by address to ’f’ to be modified if necessary.|
|ft_putchar_fd | void ft_putchar_fd(char c, int fd);|
| | Outputs the character ’c’ to the given file descriptor.                                                                                                              |
|ft_putstr_fd | void ft_puststr_fd(char *s, int fd);|
| | Outputs the string ’s’ to the given file descriptor.|
|ft_putendl_fd | void ft_putendl_fd(char *s, int fd);|
| | Outputs the string ’s’ to the given file descriptor followed by a newline.|
|ft_putnbr_fd | void ft_putnbr_fd(int n, int fd);|
| | Outputs the integer ’n’ to the given file descriptor.|


### BONUS (list handling)
```
typedef struct s_list
{
	void	*content;
	struct s_list	*next;
}	t_list;
```

|name|usage|
|:----------------|:---------|
|ft_lstnew | t_list *ft_lstnew(void *content);|
| | Allocates (with malloc(3)) and returns a new node. The member variable ’content’ is initialized with the value of the parameter ’content’. The variable ’next’ is initialized to NULL.|
|ft_lstadd_front | void ft_lstaddfront(t_list **lst, t_list *new);|
| | Adds the node ’new’ at the beginning of the list.|
|ft_lstsize | int ft_lstsize(t_list *lst);|
| | Counts the number of nodes in a list.|
|ft_lstlast | t_list *ft_lstlast(t_list *lst);|
| | Returns the last node of the list.|
|ft_lstadd_back | void ft_lstadd_back(t_list **lst, t_list *new);|
| | Adds the node ’new’ at the end of the list.|
|ft_lstdelone | void ft_lstdelone(t_list *lst, void(*del)(void *));|
| | Takes as a parameter a node and frees the memory of the node’s content using the function ’del’ given as a parameter and free the node. The memory of ’next’ must not be freed.|
|ft_lstclear | void ft_lstclear(t_list **lst, void(*del)(void *));|
| | Deletes and frees the given node and every successor of that node, using the function ’del’ and free(3). Finally, the pointer to the list must be set to NULL.|
|ft_lstiter | void ft_lstiter(t_list *lst, void(*f)(void *));|
| | Iterates the list ’lst’ and applies the function ’f’ on the content of each node.|
|ft_lstmap | t_list *ft_lstmap(t_list *lst, void*(*f)(void *), void (*del)(void *));|
| | Iterates the list ’lst’ and applies the function ’f’ on the content of each node. Creates a new list resulting of the successive applications of the function ’f’. The ’del’ function is used to delete the content of a node if needed.|


### EXTRA (usefull functions not required by the subject)
|name|usage|
|:----------------|:---------|
|ft_split_clean | char **ft_split_clean(char **splited;|
| | free a null terminated char** array of strings. Return NULL.|
| ft_strcpy | char * ft_strcpy(char *dest, const char *src);|
| |Copy dest into src. Null terminate the string.|
|ft_is_inset| bool    ft_is_inset(const char c, const char *set);|
| |Return true if c is in set, else return false.|
