#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "c_lang_task.h"


void print_number_table(short col, short row) {
    printf("\n    Task 1 \n");
    srand(time(NULL));
    short **tab;
    tab = (short**)malloc(row * sizeof(short*));

    for (int i = 0; i < row; i++){
        tab[i] = (short*)malloc(col * sizeof(short));
        for (int j = 0; j < col; j++){
            tab[i][j] = 0 + rand() % 9;
            printf("|%d|", tab[i][j]);
        }
    printf("\n");
    }
}


void write_nils_to_head_file(const char* full_fname1, int N) {
    printf("\n    Task 2 \n");
    FILE *file;
    file = fopen(full_fname1,"w");
    char ch =0x00;

    for (int i = 0; i < N; i++){
        fputc (ch, file);
    }
    fclose(file);
}


void write_ones_to_tail_fail(const char* full_fname1, int N) {
    printf("\n    Task 3 \n");
    FILE *file;
    file = fopen(full_fname1,"a");
    char ch =0xff;

    for (int i = 0; i < N; i++){
        fputc (ch, file);
    }
    fclose(file);
}


int read_i_string_from_file(const char* full_fname2, int i, char* out_str, int max_sz) {
    FILE *file;
    file = fopen(full_fname2,"r");

    if (file == NULL){
        printf("ERROR\n File not found.\n");
        return -1;
    }

    char ch = 'a';
    int j = 1;
    while (j < i){
        if (feof(file)){
            printf("ERROR\nThere is no such line.\n");
            return -1;
        }
        ch = fgetc(file);
        if (ch == '\n'){
            j++;
        }
    }

    int flag = 0;
    while ((flag < max_sz) & (!feof(file)) & (out_str[flag-1] !='\n')){
        out_str[flag] = fgetc(file);
        flag++;
    }

    if ((flag == max_sz) & (out_str[flag - 1] != '\n')){
        out_str[flag-1] = '\0';
    }
    fclose(file);
    return flag;
}


void TEST_memcpy_and_memset(void){
    printf("\n    Task 5 \n");
    int si = 40*sizeof(int);
    int sd = 20*sizeof(double);
    int sc = 80*sizeof(char);

    int *in = (int*)malloc(si);
    double *doubl = (double*)malloc(sd);
    char *cha = (char*)malloc(sc);

    memset(cha,0x01,sc);
    memset(doubl,0x00,sd);
    memset(in,0x00,si);
    for (int i = 0; i < 40; i++){
        memset(in+i,0x01,1);
    }

    for (int i = 0; i <10; i++){
        printf("%c ",cha[i]);
    }
    printf("\n");
    for (int i = 0; i <10; i++){
        printf("%d ",in[i]);
    }
    printf("\n");
    for (int i = 0; i <10; i++){
        printf("%f ",doubl[i]);
    }
    printf("\n");

    memcpy(cha, in, sc);
    memcpy(in, doubl, si);
    memcpy(doubl, cha, sc);

    for (int i = 0; i <10; i++){
        printf("%c ",cha[i]);
    }
    printf("\n");
    for (int i = 0; i <10; i++){
        printf("%d ",in[i]);
    }
    printf("\n");
    for (int i = 0; i <10; i++){
        printf("%f ",doubl[i]);
    }
    printf("\n");
}


void TEST_read_i_string_from_file(void) {
    printf("\n    Task 6 and 4 \n");
    char* full_fname2 = "/home/student/Project/c_lang_task/File2.Txt";

    int i = 6, max_sz = 15;
    char* out_str = (char*)malloc(sizeof(char)*max_sz);
    int size_str = read_i_string_from_file(full_fname2, i, out_str, max_sz);
    printf("%d\n", size_str);
    for (int j = 0; j < max_sz; j++){
        printf("%c", out_str[j]);
    }
    printf("\n");

    free(out_str);
    max_sz = 7;
    out_str = (char*)malloc(sizeof(char)*max_sz);
    size_str = read_i_string_from_file(full_fname2, i, out_str, max_sz);
    printf("%d\n", size_str);
    for (int j = 0; j < max_sz; j++){
        printf("%c", out_str[j]);
    }
    printf("\n");

    i = 20;
    size_str = read_i_string_from_file(full_fname2, i, out_str, max_sz);
    printf("%d\n", size_str);
    for (int j = 0; j < max_sz; j++){
        printf("%c", out_str[j]);
    }
    printf("\n");
}


int main() {
int col = 4, row = 8;
char* full_fname1 = "/home/student/Project/c_lang_task/File.Txt";
int N = 8;
print_number_table(col, row);
write_nils_to_head_file(full_fname1, N);
write_ones_to_tail_fail(full_fname1, N);
TEST_memcpy_and_memset();
TEST_read_i_string_from_file();
return 0;
}
