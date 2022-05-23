#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int test(int ca, int threads) {
    char buf1[100];
    char buf2[100];
    pid_t pid1 = fork();
    if (pid1 == 0) {
        sprintf(buf1, "data/out%d", ca);
        int fd_out = open(buf1, O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
        if (fd_out < 0) {
            perror("Failed to open user out file");
            exit(1);
        }
        dup2(fd_out, STDOUT_FILENO);
        sprintf(buf1, "data/err%d", ca);
        int fd_err = open(buf1, O_RDWR | O_CLOEXEC | O_TRUNC | O_CREAT, S_IRWXU | S_IRWXG);
        if (fd_err < 0) {
            perror("Failed to open user err file");
            exit(1);
        }
        dup2(fd_err, STDERR_FILENO);
        sprintf(buf1, "data/stdin%d", ca);
        sprintf(buf2, "%d", threads);
        execlp("./msort", "./msort", buf2, buf1, NULL);
        perror("Execlp Failed: ");
        exit(1);
    } else if (pid1 > 0) {
        int status1;
        pid_t wait_result = waitpid(pid1, &status1, 0);
        if (wait_result == -1) {
            perror("Failed to wait");
            exit(1);
        }
        pid_t pid2 = fork();
        if (pid2 == 0) {
            int fd_null = open("/dev/null", O_RDWR);
            dup2(fd_null, STDOUT_FILENO);
            sprintf(buf1, "data/stdout%d", ca);
            sprintf(buf2, "data/out%d", ca);
            execlp("diff", "diff", buf1, buf2, NULL);
            perror("Execlp diff stdout Failed: ");
            exit(1);
        } else if (pid2 > 0) {
            int status2;
            waitpid(pid2, &status2, 0);
            if (WIFEXITED(status2)) {
                if (WEXITSTATUS(status2) != 0) {
                    return 0;
                }
            }
        } else {
            perror("Failed to fork");
            exit(1);
        }
        pid_t pid3 = fork();
        if (pid3 == 0) {
            int fd_null = open("/dev/null", O_RDWR);
            dup2(fd_null, STDOUT_FILENO);
            sprintf(buf1, "data/stderr%d", ca);
            sprintf(buf2, "data/err%d", ca);
            execlp("./differr", "differr", buf1, buf2, NULL);
            perror("Execlp diff stderr Failed: ");
            exit(1);
        } else if (pid3 > 0) {
            int status3;
            waitpid(pid3, &status3, 0);
            if (WIFEXITED(status3)) {
                if (WEXITSTATUS(status3) != 0) {
                    return 0;
                } else {
                    return 1;
                }
            }
        } else {
            perror("Failed to fork");
            exit(1);
        }
    } else {
        perror("Failed to fork");
        exit(1);
    }
    return 0;
}

int main() {
    int ret1 = (test(1, 4)*25);
    if (ret1) {
        printf("Testcase 1  . . . . .  passed\n");
    } else {
        printf("Testcase 1  . . . . .  failed\n");
    }

    int ret2 = (test(2, 4)*25);
    if (ret2) {
        printf("Testcase 2  . . . . .  passed\n");
    } else {
        printf("Testcase 2  . . . . .  failed\n");
    }

    return 0;
}
