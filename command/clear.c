#include <stdio.h>

void clear(){
    printf("\033[H\033[J");
}

int main(int argc,char** argv){
    clear();
}