#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

void list(char *path, int a, int l){
    DIR *d;

    d = opendir(path);
    if(d == NULL){
        perror("Unable to open directory\n");
        exit(1);
    }

    struct dirent *dir;
    while((dir = readdir(d)) != NULL){
        if(!a && dir->d_name[0] == '.') continue;
        printf("%s\t", dir->d_name);
        if(l) printf("\n");
    }
    if(!l) printf("\n");
    closedir(d);
}

int main(int argc, char *argv[]){
    switch (argc){
        case 2:{
            if(argv[1][0] == '-'){
                int a=0, l=0;
                for(int i=1; argv[1][i] != '\0'; i++){
                    if(argv[1][i] == 'a')
                        a = 1;
                    else if(argv[1][i] == 'l')
                        l = 1;
                }
                list(".", a, l);
            }
            else{
                list(argv[1], 0, 0);
            }
            break;
        }    
        case 3:{
            int a=0, l=0;
            for(int i=1; argv[1][i] != '\0'; i++){
                if(argv[1][i] == 'a')
                    a = 1;
                else if(argv[1][i] == 'l')
                    l = 1;
            }
            list(argv[2], a, l);
            break;
        }
        default: 
            list(".", 0, 0);
        }

    //list(".", 0, 0);
    return 0;
}