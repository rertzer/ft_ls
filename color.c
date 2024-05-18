#include <stdio.h>

#define COLOR_DIRE "\x1b[34;01m"		//directory
#define COLOR_LINK	"\x1b[36;01m"		//sym link
#define COLOR_EXEX	"\x1b[32;01m"		//exec file
#define COLOR_ARCH	"\x1b[31;01m"		//archive file
#define COLOR_FIFO	"\x1b[33;40m"		//fifo
#define COLOR_BLNK	"\x1b[31;40m;01"	//broken link and missing files
#define COLOR_SOCK	"\x1b[35;01m"		//socket
#define COLOR_IMAG	"\x1b[35;01"		//image, video files...
#define COLOR_AUDI	"\x1b[36;00m"		//audio files...
#define COLOR_BLCK	"\x1b[33;43m;01"		//block device
#define COLOR_CHAR	"\x1b[33;43m;01"		//char device
#define COLOR_SUID	"\x1b[37;41m"		//set uid
#define COLOR_GUID	"\x1b[30;43m"		//set gid
#define COLOR_CAPA	"\x1b[30;41m"		//files whith capabilities
#define COLOR_DEFT	"\x1b[00;00m"
#define COLOR_SKDR	"\x1b[37;44m"		//sticky directory
#define COLOR_OWDR	"\x1b[34;42m"		//other writable directory
#define COLOR_SOWD	"\x1b[30;42m"		//sticky and other directory

int	main()
{
	char color[15] = COLOR_DIRE;
	printf("%s directory\n", color);
	
	printf("COLOR_LINK sym link\n");
	printf("COLOR_EXEX exec file\n");
	printf("COLOR_ARCH archive\n");
	printf("COLOR_FIFO fifo\n");
	printf("COLOR_BLNK broken link\n");
	printf("COLOR_SOCK socket\n");
	printf("COLOR_IMAG image\n");
	printf("COLOR_AUDI audio\n");
	printf("COLOR_BLCK block\n");
	printf("COLOR_CHAR character\n");
	printf("COLOR_SUID set uid bit\n");
	printf("COLOR_GUID set gid bit\n");
	printf("COLOR_CAPA file with capabilities\n");
	printf("COLOR_DEFT default\n");
	printf("COLOR_SKDR sticky directory\n");
	printf("COLOR_OWDR other writable directory\n");
	printf("COLOR_SOWD sticky and other writable directory\n");
}
