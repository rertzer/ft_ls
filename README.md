# 42 School project reimplementing the ls command.

## Implemented options:
### mandatory:
- -a  do not ignore entries starting with .
- -l  long list format
- -r  reverse ordrer while sorting
- -R  recursive
- -t  sort by time, newest first
### bonus:
- -d  list directories, not content  
- -u  sort by acces time
- -f  list all entries in directory order
- -g  like -l but don't show owner
- -G  like -l but dont't show group
- --color

The bonus part should also handle ACL and extended attributes.

## Projet rules: 
The code must be written in C.
For the mandatory part the only allowed functions are:
- write
- opendir
- readdir
- closedir
- stat
- lstat
- getpwuid
- getgrgid
- listxattr
- getxattr
- time
- ctime
- readlink
- malloc
- free
- perror
- strerror
- exit
