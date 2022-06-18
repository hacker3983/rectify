#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
// swap two long ints
void swap(size_t* a, size_t* b) {
	size_t temp = *a;
	*a = *b;
	*b = temp;
}

// multiply a character x amount of times returning a pointer to a string
char* multiply(char c, size_t x) {
	char* buff = calloc(x, sizeof(char*));
	for(size_t i=0;i<x;i++) { buff[i] = c; }
	return buff;
}
// writes to a file stream and prints to stdout
void print_writef(FILE* f, const char* format, ...) {
	char* buff = calloc(1, sizeof(char*));
	va_list va;
	va_start(va, format);
	size_t i=0, x=0;
	while(format[i]) {
		int num;
		char* str, *temp, c;
		if(format[i] == '%') {
			i++;
			switch(format[i]) {
				case 'c':
					c = (char)va_arg(va, int);
					buff[x++] = c;
					temp = buff;
					buff = calloc(x+1, sizeof(char*));
					strcpy(buff, temp);
					free(temp);
					break;
				case 'd': {
					int j = 0, n = 0;
					num = va_arg(va, int), n = num;
					while(n != 0) {
						j++; n /= 10;
					}
					char* strnum = calloc(j, sizeof(char*)), *temp;
					sprintf(strnum, "%d", num);
					x += j;
					temp = buff;
					buff = calloc(x, sizeof(char*));
					strcpy(buff, temp);
					strcat(buff, strnum);
					free(temp);
					free(strnum);
					break;
				} case 's':
					str = va_arg(va, char*);
					x += strlen(str);
					temp = buff;
					buff = calloc(x, sizeof(char*));
					strcpy(buff, temp);
					strcat(buff, str);
					free(temp);
					break;
			}
		} else {
			buff[x++] = format[i];
			char* temp = buff;
			buff = calloc(x+1, sizeof(char*));
			strcpy(buff, temp);
			free(temp);
		}
		i++;
	}
	va_end(va);
	fprintf(f, "%s", buff);
	printf("%s", buff);
	free(buff);
}

// print the frame in a rectangular shape
void print_rect(char* list[], char c, int color, size_t length) {
	if(color != -1) printf("\033[%dm", 30+color);
	size_t size=0;
	if(length == -1) { while(list[size] != NULL) { size++; } }
	else { size = length; }
	size_t arr[size], max = 0;
	for(size_t i=0;i<size;i++) { arr[i] = strlen(list[i]); }
	max = arr[0];
	for(size_t i=0;i<size;i++) {
		if(arr[i] > max) {
			max = arr[i];
		}
	}
	char* buff = multiply(c, max+4);
	printf("%s\n", buff);
	/*
	   *********
	   * Hello *
	   * World *
	   * In    *
	   * A     *
	   * Frame *
	   *********
	   5 + 3 = 8
	  +--------------------------------------------------+
	  |  Find the maximum length for the longest string  |
	  |  subtract the length of the current string + 1   |
	  |  from the maximum length for the longest string  |
	  |  (l+2) - (n+1)                                   |
	  +--------------------------------------------------+
	*/
	for(size_t i=0;i<size;i++) {
		printf("%c %s", c, list[i]);
		size_t n = strlen(list[i]);
		for(size_t x=0;x<(max+2)-(n+1);x++) { printf(" "); }
		printf("%c\n", c);
	}
	printf("%s\033[0m\n", buff);
	free(buff);
}
// print_rectw is equivalent to print_rect except that it writes to a given file stream
void print_rectw(char* list[], char c, int color, size_t length, char* filename) {
	FILE* f = fopen(filename, "wb");
	if(color != -1) print_writef(f, "\033[%dm", 30+color);
	size_t size=0;
	if(length == -1) { while(list[size] != NULL) { size++; } }
	else { size = length; }
	size_t arr[size], max = 0;
	for(size_t i=0;i<size;i++) { arr[i] = strlen(list[i]); }
	max = arr[0];
	for(size_t i=0;i<size;i++) {
		if(arr[i] > max) {
			max = arr[i];
		}
	}
	printf("%ld\n", max);
	char* buff = multiply(c, max+4);
	print_writef(f, "%s\n", buff);
	for(size_t i=0;i<size;i++) {
		print_writef(f, "%c %s", c, list[i]);
		size_t n = strlen(list[i]);
		for(size_t x=0;x<(max+2)-(n+1);x++) { print_writef(f, " "); }
		print_writef(f, "%c\n", c);
	}
	print_writef(f, "%s\033[0m\n", buff);
	free(buff);
	fclose(f);
}
