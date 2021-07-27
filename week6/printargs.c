#include <stdio.h>

int main(int argc, char **argv)
{
    for (argc--, argv++; argc > 0; argc--, argv++)
	printf("%s%c", *argv, (argc == 1) ? '\n' : ' ');
    return(0);
}