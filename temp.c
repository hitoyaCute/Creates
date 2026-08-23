typedef int *(T1) (
    char **,
    // char* func()
 char *(*)()
);

typedef T1 *(T2)[];

typedef T2 *(T3) (
    char *,
    // int* func(char*)
    int *(*)(char *)
);

typedef T3 **x[];
int main() {
    return -1;
}
