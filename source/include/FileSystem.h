
#ifndef FileSystem__h
#define FileSystem__h

class FileSystem {
    public:
        static char * readTextFile(const char * filepath);
        static void writeTextFile(const char * filepath, char * text);
};

#endif