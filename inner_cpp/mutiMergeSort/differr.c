#include <stdio.h>
#include <string.h>

void sort(char d[][1000], int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (strcmp(d[i], d[j]) > 0) {
                char tmp[1000];
                strcpy(tmp, d[i]);
                strcpy(d[i], d[j]);
                strcpy(d[j], tmp);
            }
        }
    }
}

char d1[100][1000], d2[100][1000];
int cnt;

int main(int argc, char* argv[]) {
    FILE *f1 = fopen(argv[1], "r"); // stderr
    FILE *f2 = fopen(argv[2], "r"); // err
    char buf1[1000], buf2[1000];
    fgets(buf1, 999, f1);
    fgets(buf2, 999, f2);
    cnt = 0;
    while (buf1[0] && buf2[0] && buf1[0] == 'S') {
        strcpy(d1[cnt], buf1);
        strcpy(d2[cnt], buf2);
        ++cnt;
        fgets(buf1, 999, f1);
        fgets(buf2, 999, f2);
    }
    if (!buf1[0]) {
        return 0;
    }
    if (!buf2[0]) {
        return -1;
    }
    if (strcmp(buf1, buf2)) {
        return -1;
    }
    sort(d1, cnt);
    sort(d2, cnt);
    for (int i = 0; i < cnt; ++i) {
        if (strcmp(d1[i], d2[i])) {
            return -1;
        }
    }
    fgets(buf1, 999, f1);
    fgets(buf2, 999, f2);
    while (buf1[0] && buf2[0] && buf1[0] == 'M') {
        cnt = 0;
        while (buf1[0] && buf2[0] && buf1[0] == 'M') {
            strcpy(d1[cnt], buf1);
            strcpy(d2[cnt], buf2);
            ++cnt;
            fgets(buf1, 999, f1);
            fgets(buf2, 999, f2);
        }
        if (!buf1[0]) {
            return 0;
        }
        if (!buf2[0]) {
            return -1;
        }
        if (strcmp(buf1, buf2)) {
            return -1;
        }
        sort(d1, cnt);
        sort(d2, cnt);
        for (int i = 0; i < cnt; ++i) {
            if (strcmp(d1[i], d2[i])) {
                return -1;
            }
        }
        fgets(buf1, 999, f1);
        fgets(buf2, 999, f2);
    }
    if (!buf1[0]) {
        return 0;
    }
    if (!buf2[0]) {
        return -1;
    }
    return 0;
}
