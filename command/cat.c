#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void concatenate(char *files[], int n){
    for(int i=1;i<=n;i++){
        FILE *fptr = fopen(files[i], "r");
        if(fptr == NULL){
            perror("No such file or directory\n");
            exit(1);
        }

        char buffer[256];
        while(fgets(buffer, sizeof(buffer), fptr)){
            printf("%s", buffer);
        }
        fclose(fptr);
        //printf("%s\n", files[i]);
    }
    return;
}

int main(int argc, char *argv[]){
    concatenate(argv, argc - 1);
    return 0;
}