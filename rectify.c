#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string.h"
#include "cmd-args.h"
#include "print-rect.h"
#define RECTIFY_VERSION "0.1"

char* input(const char* prompt) {
	printf("%s", prompt);
	char* buff = calloc(1, sizeof(char*)), c;
	size_t i=0;
	while((c = fgetc(stdin))) {
		if(c == '\n' && i != 0) break;
		(c != '\n') ? (buff[i++] = c) : 0;
		char* temp = buff;
		buff = calloc(i+1, sizeof(char*));
		strcpy(buff, temp);
		free(temp);
	}
	return buff;
}

int main(int argc, char** argv) {
	args_t args = {0};
	char* welcome[] = {"Welcome to rectify!", NULL};
	parse_specargs(argc, argv, &args);
	if(args.interactive || argc < 2) {
		while(1) {
			char* color_opt, frame = '\0', *srow;
			print_rect(welcome, '*', 1, -1);
			printf("Version: \033[36mrectify 0.1\033[0m\n");
			printf("Enter the character for the frame: "); scanf("%c", &frame);
			if(frame == '\n') { frame = '\0'; }
			while(getchar() != '\n') { }
			srow = input("Enter the amount of rows for the frame: ");
			size_t rows = 0;int color = -1;
			if(isnum(srow)) { rows = strtol(srow, NULL, 0); }
			else fprintf(stderr, "%s is not a valid row. row must be a positive integer", srow);
			free(srow);

			list_colors(), color_opt = input("Choose one of the colors to use above (color must be a number): ");
			if(raise_numerr(color_opt, NULL)) { color = atoi(color_opt); }
			free(color_opt);

			char* list[rows+1]; list[rows] = NULL;
			for(size_t i=0;i<rows;i++) { list[i] = input("Enter the text for each row separated by a new line (enter): "); }

			if(rows != 0) (frame != '\0') ? print_rect(list, frame, color, -1) : print_rect(list, '*', color, -1);
			printf("\n");
			for(size_t i=0;i<rows;i++) { free(list[i]); }
		}
	} else {
		print_rect(welcome, '*', 1, -1);
		printf("Version: \033[36mrectify 0.1\033[0m\n");
		args = parse_args(argc, argv);
		(args.frame == '\0') ? args.frame = '*': 0;
		if(!args.text) {
			fprintf(stderr, "%s: option -t is required but not specified\n", argv[0]);
		} else {
			print_rect(args.string.list, args.frame, args.color, args.string.size);
		}
		string_free(&args.string);
	}
	return 0;
}
