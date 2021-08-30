#include <ctype.h>
#include <stdbool.h>
#include <getopt.h>
char* colors[] = {"black", "red", "green", "yellow", "blue", "magenta", "cyan", "white"};
typedef struct args {
	char frame;
	int color, list_colors, interactive, text;
	string_t string;
} args_t;

void args_free(args_t* args);
void args_exitfree(args_t* args);

void usage(char* program_name) {
	fprintf(stderr, "Usage: %s [OPTION]...\n"
			"Print out text in a rectangular frame\n"
			"  -f, --frame-character\tcharacter to use when creating frame\n"
			"  -l, --list-colors\tprint the list of colors supported\n"
			"  -c, --color\tcolor to use to color the frame\n"
			"  -t, --text\ttext to put inside the frame\n"
			"  -i, --interactive\tEnter Interactive mode\n"
			"  -h, --help\tprint this help message and exit (also --help)\n", program_name);
}

void list_colors() {
	puts("Colors Numbers:");
	for(int i=0;i<sizeof(colors)/sizeof(colors[0]);i++) {
		printf("%d - %s\n", i, colors[i]);
	}
}

bool isnum(char* s) {
	size_t i=0;
	while(s[i]) {
		if(!isdigit(s[i])) {
			return false;
		}
		i++;
	}
	return true;
}

int raise_numerr(char* num, args_t* args) {
	if(num == NULL) return 0;
	else if(num[0] == '-') {
		fprintf(stderr, "No color specified however selecting default color.\n");
		return 0;
	} else if(!isnum(num)) {
		fprintf(stderr, "%s is not a valid color selecting default color.\n"
				"color must be of type positive integer", num);
		if(args != NULL) {
			fprintf(stderr, " however here are the list of colors and there numbers below.\n"); list_colors();
		} else { fprintf(stderr, ".\n"); }
		return 0;
	} else {
		int color = atoi(num);
		if(!(color >= 0 && color <= 7)) {
			fprintf(stderr, "%d is not in the range of 0 - 7 selecting default color.\n", color);
			(args != NULL) ? fprintf(stderr, "however here are a list of colors and there numbers below.\n") : 0;
			return 0;
		}
		if(args != NULL) { args->color = color; }
	}
	return 1;
}

args_t parse_args(int argc, char** argv) {
	args_t args = {0};
	args.color = -1;
	string_init(&args.string);
	char option = '\0';
	//for(int i=1;i<argc;i++) { puts(argv[i]);
	int loption_index = 0;
	struct option options[] = {
		{"list-colors", no_argument, 0, 'l'},
		{"text", required_argument, 0, 't'},
		{"frame-character", optional_argument, 0, 'f'},
		{"color", optional_argument, 0, 'c'},
		{0, 0, 0, 0}
	};
	while((option = getopt_long(argc, argv, "lt:f::c::", options, &loption_index)) != -1) {
		switch(option) {
			case 't': {
				args.text = 1;
				if(optarg == NULL) {
					args_exitfree(&args);
				} else {
					string_append(&args.string, optarg);
					while(argv[optind] != NULL) {
						if(argv[optind][0] != '-') {
							string_append(&args.string, argv[optind]);
						} else {
							break;
						}
						optind++;
					}
				}
				break;
			} case 'l': {
				list_colors(); break;
			}
			case 'c': {
				if(argv[optind] != NULL) {
					char* number = argv[optind++]; raise_numerr(number, &args);
					(number[0] == '-') ? optind-- : 0;
				} else {
					fprintf(stderr, "No color specified however selecting default color.\n");
				}
				break;
			}
			case 'f': {
				if(argv[optind] != NULL) {
					if(argv[optind][0] != '-') {
						for(size_t i=0;i<strlen(argv[optind]);i++) { args.frame = argv[optind][i]; }
					}
				}  break;
			}
			default: exit(0);
		}
	} optind = 0;
	return args;
}

// parse special arguments
void parse_specargs(int argc, char** argv, args_t* args) {
	for(int i=1;i<argc;i++) {
		if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) { usage(argv[0]); exit(0); }
		else if(strcmp(argv[i], "-i") == 0 || strcmp(argv[i], "--interactive") == 0) { args->interactive = 1; }
	}
}

void args_exitfree(args_t* args) {
	string_free(&args->string);
	exit(0);
}
