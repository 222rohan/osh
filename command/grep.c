#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void globalRegExPrint(char *files[], int n, char *pattern, int i){
    int flag = ((i && n > 4) || n > 3) ? 1 : 0;
    int start = i == 1 ? 3 : 2;
    
    for(int j=start;j<n;j++){
        FILE *fptr = fopen(files[j], "r");
        if(fptr == NULL){
            perror("No such file or directory\n");
            exit(1);
        }

        char buffer[256];
        while(fgets(buffer, sizeof(buffer), fptr)){
            if(i) {
                char temp[256];
                for(int k=0;buffer[k];k++){
                    temp[k] = tolower(buffer[k]);
                }
                if(strstr(temp, pattern) != NULL){
                    if(flag) printf("%s: ", files[j]);
                    printf("%s", buffer);
                }
            }
            else if(strstr(buffer, pattern) != NULL){
                if(flag) printf("%s: ", files[j]);
                printf("%s", buffer);
            }
        }
        fclose(fptr);
    }
    return;
}

int main(int argc, char *argv[]){
    if(argc < 3){
        printf("Usage: ./grep pattern file1 file2 ... fileN\n");
        exit(1);
    }

    if(argv[1][0] == '-' && argv[1][1] == 'i'){
        globalRegExPrint(argv, argc, argv[2], 1);
    }
    else{
        globalRegExPrint(argv, argc, argv[1], 0);
    }

    return 0;
}