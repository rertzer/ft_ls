#include <stdio.h>
#include <sys/stat.h>

int	main()
{
	unsigned long long ul = sizeof(unsigned long);
	unsigned long long ull = sizeof(unsigned long long);
	unsigned long long nlink = sizeof(nlink_t);
	unsigned long long size = sizeof(nlink_t);

	printf("nlink_t: %llu\n", nlink);
	printf("ul: %llu\n", ul);
	printf("ull: %llu\n", ull);
	printf("size: %llu\n", size);
	return (0);
}
