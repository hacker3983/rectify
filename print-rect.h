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

// print the frame in a rectangular shape
void print_rect(char* list[], char c, int color, size_t length) {
	if(color != -1) printf("\033[%dm", 30+color);
	size_t size=0;
	if(length == -1) { while(list[size] != NULL) { size++; } }
	else { size = length; }
	//printf("%ld\n", size);
	size_t arr[size];
	for(size_t i=0;i<size;i++) { arr[i] = strlen(list[i]); }
	for(size_t i=0;i<size;i++) {
		for(size_t x=0;x<size;x++) {
			if(arr[i] > arr[x]) {
				swap(&arr[i], &arr[x]);
			}
		}
	}
	char* buff = multiply(c, arr[0]+4);
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
		for(size_t x=0;x<(arr[0]+2)-(n+1);x++) { printf(" "); }
		printf("%c\n", c);
	}
	printf("%s\033[0m\n", buff);
	free(buff);
}
