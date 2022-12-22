#include "include/utils.h"

char* get_cwd() {
    char* buf = (char*)malloc(sizeof(char) * 1024);

    getcwd(buf, 1024);

    if (NULL == buf) {
        show_error(1, "get current work directory failed");
    }

    return buf;
}

char* get_pwnam(const char* name) {
    struct passwd* pw = getpwnam(name);

    if (NULL == pw) {
        show_error(1, "get user's home directory failed");
    }

    return pw->pw_dir;
}

char* get_kernel_name() {
    struct utsname* ut = (struct utsname*)malloc(sizeof(struct utsname));

    if (-1 == uname(ut)) {
        show_error(1, "get kernel name failed");
    }

    return ut->nodename;
}

struct passwd* get_user_record() {
    struct passwd* u = getpwuid(getuid());

    if (NULL == u) {
        show_error(1, "get user's record failed");
    }

    return u;
}

char* get_user_name() {
    return get_user_record()->pw_name;
}

char* get_cur_home_dir() {
    return get_pwnam(get_user_name());
}
