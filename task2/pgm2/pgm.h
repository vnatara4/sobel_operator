typedef struct _PGMData {
    int row;
    int col;
    int max_gray;
    int *data;
} PGMData;

void SkipComments(FILE *fp);
PGMData* readPGM(const char *file_name, PGMData *data);
void writePGM(const char *filename, const PGMData *data);
