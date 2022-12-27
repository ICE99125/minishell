#ifndef __UTILS_H__
#define __UTILS_H__

// @Author : ARCTURUS <ice99125@qq.com>
// @Created : 2022-12-21 16:31:03

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

#define WELCOME                                                          \
    "+++++++++++++++++++++++++++++++++++++++++++++++++\n"                \
    "+                                               +\n"                \
    "+            \033[35mwelcome to mini-shell.\033[0m             +\n" \
    "+        ctrl+c or input \"exit\" to quit.        +\n"              \
    "+                                               +\n"                \
    "+++++++++++++++++++++++++++++++++++++++++++++++++\n"

#define USERINFO "\033[31m%s@$%s:\033[0m"

#define DIRNAME "\033[34m%s$\033[0m"

#define TIP USERINFO DIRNAME

#define ERROR "\033[31m%s\033[0m"  // red

#define WARNING "\033[35m%s\033[0m"  // purple

#define SUCCESS "\033[36m%s\033[0m"  // green

// env.c

char* get_env(const char* key);

void show_all_env();

void unset_env(const char* key);

// set enviroment variable by additional
void put_env(const char* key, const char* value);

void set_env(const char* key, const char* value, int overwrite);

// printf.c

void show_error(int quit, char* fmt, ...);

void welcome_to_shell();

void prompt_msg();

// sys.c

// obtain current work directory.
char* get_cwd();

// obtain user's home directory
char* get_pwnam(const char* name);

char* get_kernel_name();

struct passwd* get_user_record();

char* get_user_name();

char* get_cur_home_dir();

// str.c

typedef enum Direct {
    left,
    right,
    both,
} Direct;

// open file mode
typedef enum {
    WRITE,
    APPEND,
} fmode;

// whether string is a number
int isDigit(char* str);

// determines whether the src begins with dest
// if src does not begin with dest then return 0, otherwise, return 1
int startswith(const char* src, const char* dest);

int endswith(const char* src, const char* dest);

// @param all: whether replace all string in str
char* strrepl(const char* str, const char* search, const char* replace_with, int all);

char** strsplit(const char* source, const char* separator);

// @param direct: 0: left, 1: right, 2: both
char* strtrim(const char* str, const char* flag, Direct direct);

// concatenate string
char* strjoin(const char* src, const char* sub, const char* join_with);

// history.c

// write command into .history
void write_to_history();

void add_cmd(char* cmd);

void initHistory();

void clear_history();

FILE* open_history(char* mode);

void write_to_history_and_close();

void show_history(int num);

// signal.c

void interruptHandler(int signum);

// file.c
void writeTofile(char* dst, char* content, int mode);

#endif