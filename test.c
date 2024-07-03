#include <dirent.h>
#include <stdio.h>

int	main()
{
	printf("REG %u, DIR %u, CHR %u, BLK, %u, FIFO %u, LNK %u, SOCK %u, UNK %u\n", DT_REG, DT_DIR, DT_CHR, DT_BLK, DT_FIFO, DT_LNK, DT_SOCK, DT_UNKNOWN);	
}

