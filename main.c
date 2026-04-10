#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *action[] = {"compress", "decompress"};

void compress (char *file_context, int buffer_size, char* file_path){
    int i=0;
    char compressed_file_name[256];
    snprintf(compressed_file_name, sizeof(compressed_file_name),"%s.compressed",file_path);
    FILE *cf = fopen(compressed_file_name, "w");

    while(i<buffer_size){
        char curr = file_context[i];
        int count = 0;
        while(i<buffer_size && file_context[i]==curr){
            count++;
            i++;
        }
        if(curr=='\n'){
            fprintf(cf, "%d\n", count);
            printf("%d\\n,", count);
        }else if(curr=='\t'){
            fprintf(cf, "%d\t", count);
            printf("%d\\t,", count);
        }else{
            fprintf(cf, "%d:%c:", count, curr);
            printf("%d:%c:,", count, curr);
        }
    }
    printf("\n");
    fclose(cf);
}

void decompress(char* file_path){

    char decompressed_file_name[256];
    snprintf(decompressed_file_name, sizeof(decompressed_file_name),"%s.decompressed",file_path);
    FILE *cf = fopen(file_path, "r");
    FILE *df = fopen(decompressed_file_name, "w");

    if (!cf || !df) {     
        perror("couldnt open files");
        return;
    }
    
    int count;
    int c;
    char delim;
    while(fscanf(cf, "%d", &count) == 1){
        c = fgetc(cf);
        if(c == EOF) break;
        
        if(c == '\n'){
            for(int i=0; i<count; i++){
                fputc('\n', df);
            }
        }else if(c == '\t'){
            for(int i=0; i<count; i++){
                fputc('\t', df);
            }
        }else if(c == ':'){
            c = fgetc(cf);
            delim = fgetc(cf); 
            for(int i=0; i<count; i++){
                fputc(c, df);
            }
        }
    }
    fclose(df);
    fclose(cf);
}

int main(int argc, char *argv[]){
    if (argc!=3) {
        printf("invalid args!\nusage:\n-include the action (compress/decompress)\n-include the file path\n");
    }


    FILE *f = fopen(argv[2], "r");
    fseek(f, 0, SEEK_END);
    long buffer_size = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *buffer = malloc(buffer_size + 1);

    fread(buffer, 1, buffer_size, f);
    buffer[buffer_size] = '\0';

    if (strcmp(argv[1], "compress") == 0) {
        compress(buffer, buffer_size, argv[2]);

    }else if(strcmp(argv[1], "decompress") == 0){
        decompress(argv[2]);
    }

    fclose(f);
}   