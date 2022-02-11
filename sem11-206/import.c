/// paths = [path1, parth2, ..., NULL]
/// mymodule
/// for path in paths
/// path + /mymodule/__init__.py
/// path + /mymodule.py
/// path + /python39.mymodule.so python_init
/// мб первый mymodule?
/// returns path to file

int HasSymbol(const char* library_path, const char* symbol_name) {
    void* handle = dlopen(library_path, RTLD_LAZY);
    const char* error;
    if (handle == NULL || (error = dlerror()) != NULL) {
        fprinf(stderr, "unable to load library %s : %s", library_path, error);
        return 0;
    }
    void* symbol = dlsym(handle, symbol_name);
    if ((error = dlerror()) != NULL) {
        fprinf(stderr, "unable to find symbol %s from library %s : %s", symbol_name, library_path, error);
    }

    int close_result = dlclose(handle);

    return symbol != NULL;
}

const char* Find(const char* mymodule, const char** paths) {
    char buf[PATH_MAX + 1] = {'\0'};                                         тут %s горжусь! ... это вариадики? (ну типа)
    for (const char* path = paths[0]; *path; ++path) { //snprintf(buf, len, "%s/%s", path, mymodule)
        char * tmp = buf;
        tmp = strcat(tmp, path) + strlen(path);
        tmp = strcat(tmp, "/") + 1;
        tmp = strcat(tmp, mymodule) + strlen(module);

        strcat(buf, "/__init__.py");
        struct stat st{};
        if (stat(buf, &st) == 0 && S_ISREG(st.st_mode)) {
            return strdup(buf);
        }
        //тут ещё глина, чтобы добавить \0 после mymodule
        strcat(buf, ".py");
        struct stat st{};
        if (stat(buf, &st) == 0 && S_ISREG(st.st_mode)) {
            return strdup(buf);
        }

    }
}

// The strcat() and strncat() functions return a pointer to the  resulting
//       string dest.