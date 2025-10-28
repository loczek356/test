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
    char* whe[argc]={};
    int a,i=0;
    DIR* dirp;
    struct dirent* dp;
    char* ext="";
    struct stat sta;
    FILE * out=stdout;
    char home[FILE_BUF_LEN];
    // int d=1;


    while ((a = getopt(argc, argv, "p:e:od:")) != -1)
        switch (a) {
        case 'p':
                whe[i] = optarg;
                i++;
                break;
        case 'e':
                ext=optarg;
                break;
        case'o':
                out=fopen(getenv("L1_OUTPUTFILE"),"w");
                break;
        case 'd':
                // d=atoi(optarg);
        case '?':
        default:
                usage(argv[0]);
        }
    i=0;
    if (getcwd(home,FILE_BUF_LEN)==NULL) {
        ERR("getcwd()");
    }
    while (whe[i]) {
        if ((dirp=opendir(whe[i]))==NULL) {
            ERR("opendir()");
        }
        chdir(whe[i]);
        do {
            if ((dp=readdir(dirp))!=NULL) {
                // fprintf(stderr,"%s",dp->d_name);
                if (lstat(dp->d_name, &sta)) {
                    ERR("lstat()");
                }
                if (S_ISREG(sta.st_mode)) {
                    if (strstr(dp->d_name, ext)!=NULL) {
                        fprintf(out, "%s %ld\n", dp->d_name,sta.st_size);
                    }
                }

            }
        }while(dp!=NULL);
        chdir(home);
        closedir(dirp);
        i++;
    }

}
