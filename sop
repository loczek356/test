#define _GNU_SOURCE
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


#define ERR(source) (perror(source), fprintf(stderr, "%s:%d\n", __FILE__, __LINE__), exit(EXIT_FAILURE))

#define FILE_BUF_LEN 256

void usage(char *pname) {
    fprintf(stderr, "USAGE:%s -c creat env w name -v where \n", pname);
    exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    char *whe[argc] = {};
    char buf[FILE_BUF_LEN];
    int a, i = 0;
    char *creat = NULL;
    char *pname = NULL;
    char *ver;
    int fl = 0;
    char home[FILE_BUF_LEN];
    char *rem = NULL;


    while ((a = getopt(argc, argv, "c:v:i:r:")) != -1)
        switch (a) {
            case 'c':
                creat = optarg;
                break;
            case 'i':
                char *mid = strstr(optarg, "==");
                *mid = '\0';
                pname = optarg;
                ver = mid + 2;
                break;
            case 'v':
                whe[i] = optarg;
                i++;
                break;
            case 'r':
                rem = optarg;
                break;
            case '?':
            default:
                usage(argv[0]);
        }
    if (creat && whe[1]) {
        ERR("ceate and 2 v");
    }
    if (creat) {
        if (mkdir(creat, 0777) == -1) {
            ERR("mkdir");
        }
        if (chdir(creat)) {
            ERR("chdir");
        }
        FILE *new = fopen("requirements", "w");
        if (new == NULL) {
            ERR("fopen");
        }
    }
    if (getcwd(home,FILE_BUF_LEN) == NULL) {
        ERR("getcwd");
    }
    i = 0;
    while (whe[i]) {
        if (chdir(whe[i])) {
            ERR("chdir");
        }
        FILE *req = fopen("requirements", "r");
        FILE *nreq = fopen("nrequirements", "w");
        if (rem) {
            remove(rem);
            while (fgets(buf,FILE_BUF_LEN, req)) {
                if (strstr(buf, rem)) {
                } else {
                    fprintf(nreq, "%s", buf);
                }
            }
        }
        if (pname) {
            // umask(0222);
            int new = open(pname,O_RDONLY | O_CREAT, 0444);
            if (new < 0) {
                ERR("fopen");
            }
            while (fgets(buf,FILE_BUF_LEN, req)) {
                if (strstr(buf, pname)) {
                    fprintf(nreq, "%s %s\n", pname, ver);
                    fl = 1;
                } else {
                    fprintf(nreq, "%s", buf);
                }
            }
            if (!fl) {
                fprintf(nreq, "%s %s\n", pname, ver);
            }
        }

        fclose(req);
        fclose(nreq);
        remove("requirements");
        rename("nrequirements", "requirements");
        chdir(home);
        i++;
    }
}
