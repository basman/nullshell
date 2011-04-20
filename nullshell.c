/* 
 * required: libreadline5-dev
 * compile: gcc -o nullshell -lreadline nullshell.c
 *
 * check: splint -exportlocal -nullassign nullshell.c 
 *
 * HISTORY
 *
 * v0.3 (TODO)
 * 	- read ~/.motd
 *
 * v0.2.1 2008-10-02
 *      - fix splint warning, line 118, while(1) {..}
 *
 * v0.2 2008-02-25
 * 	- provide command line history and completion
 * 	- new command 'version'
 * 	- new command 'help'
 *
 * v0.1 2007-11-16
 * 	- first basic release, no special features
 */
#include <signal.h>
//#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

const static char version[] = "v0.2.1  2008-10-02";

const static char greeting[] = "\n\nWelcome to the null shell.\nWritten by Roman Hoog Antink, 2007-11-01\n";

const static char prompt[] = "$ ";

static char* commands[] = {
	"exit", "help", "logout", "version", NULL
};

/*
 *void sigIntHandler(int signum) {
 *
 *}
 */

/*@null@*/
char * dupstr (char *s) {
       char *r;
     
       r = malloc (strlen (s) + 1);
       if(r == NULL)
		return NULL;
       strcpy (r, s);
       return (r);
}

void rtrim(char *l) {
	char *p;
	for(p = l+strlen(l)-1; p >= l; p--) {
		if(*p != ' ') break;
		*p = '\0';
	}
}

int processCommand(char *line) {
	int cmdIdx;

	rtrim(line);

	if(strcmp(line, "exit") == 0 ||
			strcmp(line, "logout") == 0) {
		return 0;
	} else if(strcmp(line, "help") == 0) {
		printf("available commands: ");
		for(cmdIdx=0; commands[cmdIdx]; cmdIdx++) {
			printf("%s ", commands[cmdIdx]);
		}
		printf("\n");
	} else if(strcmp(line, "version") == 0) {
		printf("%s\n", version);
	} else {
		printf("Unknown command: '%s'. Try help.\n", line);
	}
	return 1;
}

/*@null@*/
char** completionGenerator(const char *word, int start, /*@unused@*/ int stop) {
	int cmdIdx = 0;
	char **result;

	result = (char **)NULL;

	if(start == 0) { // we complete first words of a line only
		// note: this algorithm only returns the first match as a completion.
		//       that's ok for now, since all commands start with different letters.
		while(commands[cmdIdx]) {
			char *cmd = commands[cmdIdx++];
			if(strncmp(word, cmd, strlen(word)) == 0) {
				result = malloc(sizeof(char*) * 2);
				if(result == NULL)
					break;
				result[0] = dupstr(cmd);
				result[1] = NULL;
				break;
			}
		}
	}
	return result;
}

int main(/*@unused@*/ int argc, /*@unused@*/ char *argv[]) {
	char *line = 0;

	// signal(SIGINT, sigIntHandler);
	// rl_bind_key ('\t', rl_insert); // switch off tab completion
	rl_attempted_completion_function = completionGenerator;

	printf("%s", greeting);

	while(1==1) {
		line = readline (prompt);

		if(line != 0 && strlen(line) > 0) {
			if(processCommand(line) == 0) {
				break;
			}
			add_history(line);
		}

		if(line == 0) {
			break;
		}

		if(line != 0) {
			free(line);
			line = (char *)NULL;
		}
	}

	printf("Bye.\n");

	if(line != 0) {
		free(line);
		line = (char *)NULL;
	}
	return 0;
}
