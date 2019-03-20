#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "c_lang_task.h"

void print_number_table(short col, short row) {
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
    FILE *file;
    file = fopen(full_fname1,"w");
    char ch =0x00;
    for (int i = 0; i < N; i++){
        fputc (ch, file);
    }
    fclose(file);
}

void write_ones_to_tail_fail(const char* full_fname1, int N) {
    FILE *file;
    file = fopen(full_fname1,"a");
    char ch =0xff;
    for (int i = 0; i < N; i++){
        fputc (ch, file);
    }
    fclose(file);
}

int read_i_string_from_file(const char* full_fname2, int i, char* cut_str, int max_sz) {
    FILE *file;
    file = fopen(full_fname2,"r");
    for (int j = 0; j < i; j++){

    }
    fclose(file);
}
/*
void TEST_memcpy_and_memset(void){

}

void TEST_read_i_string_from_file(void) {

}*/

int main() {
//int col = 20, row = 20;
//char* full_fname1 = "/home/student/Project/c_lang_task/File.Txt";
char* full_fname2 = "/home/student/Project/c_lang_task/File2.Txt";
char* cut_str;
//int N = 8;
int i = 6, max_sz = 11;
//print_number_table(col, row);
//write_nils_to_head_file(full_fname, N);
//write_ones_to_tail_fail(full_fname, N);
read_i_string_from_file(full_fname, i, cut_str, max_sz);
/*TEST_memcpy_and_memset();
TEST_read_i_string_from_file();*/
system("pause");
return 0;
}
