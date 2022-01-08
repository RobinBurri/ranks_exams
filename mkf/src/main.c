#include "print.h"

int main(int argc, char **argv){
	int i = 1;
	while (i < argc) {
		lets_print(argv[i++]);
	}
	print_num(i);
	return (0);
}