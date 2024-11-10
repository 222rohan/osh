#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int if_flag=0;
int line_flag,word_flag,char_flag=0;

void wc(FILE *file, long *line_count, long *word_count, long *char_count) {
    int ch;
    int in_word = 0;

    while ((ch = fgetc(file)) != EOF) {
        (*char_count)++;
        
        if (ch == '\n') {
            (*line_count)++;
        }
        
        if (isspace(ch)) {
            in_word = 0;
        } else {
            if (!in_word) {
                (*word_count)++;
                in_word = 1;
            }
        }
    }
}

void print_counts(long line_count,long word_count,long char_count){
    if(line_flag){
        printf("%ld\t",line_count);
    }
    if(word_flag){
        printf("%ld\t",word_count);
    }
    if(char_flag){
        printf("%ld\t",char_count);
    }
}

int main(int argc, char** argv) {
    long line_count = 0, word_count = 0, char_count = 0;
    long t_line_count = 0, t_word_count = 0, t_char_count = 0;

    for(int i=0;i<argc;i++){
        if(argv[i][0]=='-'){
            if_flag=1;
            for(int j=1;j<strlen(argv[i]);j++){
                if(argv[i][j]=='m' || argv[i][j]=='c'){
                    char_flag=1;
                }
                else if(argv[i][j]=='l'){
                    line_flag=1;
                }
                else if(argv[i][j]=='w'){
                    word_flag=1;
                }
                else{
                    printf("invalid Flag\n");
                    exit(1);
                }
            }
            break;
        }
    }

    if(!if_flag){
        line_flag=1;
        word_flag=1;
        char_flag=1;
    }

    if (argc-if_flag == 1) {
        wc(stdin, &line_count, &word_count, &char_count);
        print_counts(line_count,word_count,char_count);
        printf("\n");
    } 
    else{
        for (int i = 1; i < argc; i++) {
            if(argv[i][0]=='-'){
                continue;
            }
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror("custom_wc");
                continue;
            }
            
            line_count = word_count = char_count = 0;
            
            wc(file, &line_count, &word_count, &char_count);

            print_counts(line_count,word_count,char_count);
            printf("%s\n",argv[i]);

            fclose(file);
            t_line_count+=line_count;
            t_word_count+=word_count;
            t_char_count+=char_count;
        }
        if(argc-if_flag>2){
            print_counts(t_line_count,t_word_count,t_char_count);
            printf("total\n");
        }
    }
    
    return 0;
}
