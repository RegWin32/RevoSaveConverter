#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define SWAP_UINT16(n) (((n&0xFF00)>>8)|((n&0x00FF)<<8))
const int16_t DEAD_VALUE = SWAP_UINT16(0xDEAD);

#define STRING_MATCH            0
#define UINT_LEAST8_MAX        255

#define REVO_SAVE_SIZE         139264
#define GBA_SAVE_SIZE_MAX      131072


long fsize(FILE *fp) {
    long prev = ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long sz = ftell(fp);
    fseek(fp, prev, SEEK_SET); //go back to where we were
    return sz;
}


int main(int argc, char *argv[]) {
    FILE *pFile;
    char fileNameTrimmed[UINT_LEAST8_MAX];
    char newFileName[UINT_LEAST8_MAX];


    if (argc > 2 && strcmp(argv[1], "help") != STRING_MATCH)
    {
        char *optionArgument = argv[1];
        char *fileArgument = argv[2];

        if (access(fileArgument, F_OK) == 0)
        {
            strncpy(fileNameTrimmed, fileArgument, sizeof(fileNameTrimmed));
            char *ptr = strtok(fileNameTrimmed, ".");

            pFile = fopen(fileArgument, "a+");

            if (pFile == NULL)
            {
                printf("Couldn't get pointer of file <%s> \n", fileArgument);
                perror("fopen()");
                return EXIT_FAILURE;
            }
            else if(strcmp(optionArgument, "gba") == STRING_MATCH)
            {
                 if (fsize(pFile) == REVO_SAVE_SIZE)
                 {
                    snprintf(newFileName,
                             sizeof(newFileName)+sizeof(".sav"), "%s.sav", fileNameTrimmed);

                    FILE *pNewFile = fopen(newFileName, "a+");
                    char cTemp;

                    while (fread(&cTemp, 1, 1, pFile) == 1)
                    {
                        if (fsize(pNewFile) < GBA_SAVE_SIZE_MAX)
                            fwrite(&cTemp, 1, 1, pNewFile);
                    }
                    fclose(pFile);
                    fclose(pNewFile);
                    remove(fileArgument);
                    return EXIT_SUCCESS;
                }
            }
            else if (strcmp(optionArgument, "revo") == STRING_MATCH)
            {
                while (fsize(pFile) < REVO_SAVE_SIZE)
                {
                    fwrite(&DEAD_VALUE, sizeof(DEAD_VALUE), 1, pFile);
                }
                fclose(pFile);

                snprintf(newFileName,
                         sizeof(newFileName)+sizeof(".gba.sav"), "%s.gba.sav", fileNameTrimmed);

                rename(fileArgument, newFileName);

                return EXIT_SUCCESS;
            }
        }
        else
        {
            printf("File <%s> was not valid\n", fileArgument);
            perror("access()");
            return EXIT_FAILURE;
        }
    }
    else
    {
        printf("No file was specified\n"
               "Usage GBA_Convert [OPTION] [SAVE-FILE]\n"
               "OPTION\n"
               "    revo   to revo file format\n"
               "    gba    to gba file format\n"
               "SAVEFILE\n"
               "    string  name of the savefile\n");
        return EXIT_FAILURE;
    }
    return 400;
}
