#include <limits.h>
#include <string.h>
#include <sys/stat.h>
#include <dlfcn.h>

// find(["abracazabra", "/usr/lib/python", ".", "/etc/mymodules"], "mymodule")

// + /mymodule.py ...
// + /mymodule/__init__.py ...
// + /python3.mymodule.so ...

int check(const char *path, const char *func) {
    void* h = dlopen(path, RTLD_LAZYRTLD_LAZY);
    if (!h) {
        return 0;
    }
    void* f = dlsym(h, func);
    dlclose(h);
    return f != NULL;
}

char* find(const char **paths, const char *module) {
    char buf[PATH_MAX];

    for (;*paths;++paths) {
        const char * cur_path = *paths;

        strcpy(buf, cur_path);
        char * tmp = buf + strlen(cur_path);
        *tmp = '/'; ++tmp;

        {  // /mymodule.py
            strcpy(tmp, module);
            strcpy(tmp + strlen(module), ".py");

            struct stat st;
            if (stat(tmp, &st) == 0 &&
                S_ISREG(st.dt_mode)) {
                return strdup(buf);
            }
        }

        {
            strcpy(tmp, module);
            strcpy(tmp + strlen(module), "/__init__.py");

            struct stat st;
            if (stat(tmp, &st) == 0 &&
                S_ISREG(st.dt_mode)) {
                return strdup(buf);
            }
        }

        {
            strcpy(tmp, "python3.");
            strcpy(tmp + strlen("python3."), module);
            strcpy(tmp + strlen("python3.") + strlen(module), ".so");

            struct stat st;
            if (stat(tmp, &st) == 0 &&
                S_ISREG(st.dt_mode) &&
                check(buf, "python_init")) {
                return strdup(buf);
            }
        }
    }
}
