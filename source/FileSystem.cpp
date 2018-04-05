#include <FileSystem.h>

#include <stdio.h>
#include <stdlib.h>

char * FileSystem::readTextFile(const char * filepath) {
    FILE *f = fopen(filepath, "rb");

    if (f == NULL) {
        printf("File not found: %s", filepath);
        return NULL;
    }
    else {
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);  //same as rewind(f);

        char *string = (char *)malloc(fsize + 1);
        fread(string, fsize, 1, f);
        fclose(f);

        string[fsize] = 0;
        return string;
    }
}

void FileSystem::writeTextFile(const char * filepath, char * text) {
    FILE *f = fopen(filepath, "w");
    if(f == NULL) {
        printf("Could not open: %s", text);
    }
    else {
        fprintf(f, text);
        fclose(f);
    }
}