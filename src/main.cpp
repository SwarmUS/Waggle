#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdbool.h>

#ifdef _WIN32
#define PATH_SEP '\\'
#else
#define PATH_SEP '/'
#endif

#include "bo2bbo/bo2bbo.h"
#include "bbo2header/bbo2header.h"

/**
 * @brief Removes the "extension" from a file spec.
 * @param[in] mystr The string to process.
 * @param[in] dot The extension separator.
 * @param[in] sep The path separator (0 means to ignore).
 * @return An allocated string identical to the original but
 * with the extension removed. It must be freed when you're
 * finished with it.
 * @note If you pass in NULL or the new string can't be allocated,
 * it returns NULL.
 */
char *remove_ext (char* mystr, char dot, char sep) {
    char *retstr, *lastdot, *lastsep;

    // Error checks and allocate string.

    if (mystr == NULL)
        return NULL;
    if ((retstr = (char *)malloc (strlen (mystr) + 1)) == NULL)
        return NULL;

    // Make a copy and find the relevant characters.

    strcpy (retstr, mystr);
    lastdot = strrchr (retstr, dot);
    lastsep = (sep == 0) ? NULL : strrchr (retstr, sep);

    // If it has an extension separator.

    if (lastdot != NULL) {
        // and it's before the extenstion separator.

        if (lastsep != NULL) {
            if (lastsep < lastdot) {
                // then remove it.

                *lastdot = '\0';
            }
        } else {
            // Has extension separator with no path separator.

            *lastdot = '\0';
        }
    }

    // Return the modified string.

    return retstr;
}


int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Usage: \n\tbcodegen <buzzscript.bo> <outfile.h>\n\n\n"


               "Metaprogram which takes a Buzz object (.bo) file generated \n"
               "by the Buzz compiler (bzzc or bzzasm) and generates a header \n"
               "file containing raw bytecode for kilobot programs, as well \n"
               "as macros corresponding to the string ID of strings appearing \n"
               "in the Buzz program.\n\n"

               "The bytecode is available as 'uint8_t bcode[]', and its size \n"
               "is stored as 'uint16_t bcode_size'.\n\n"

               "Given a string, use the 'BBZSTRING_ID' macro defined in \n"
               "\"bbzstring.h\" to get the string ID of a string. Note that \n"
               "all characters that would otherwise make an invalid \n"
               "identifier should be replaced by an underscore (case remains \n"
               "unchanged). Thus, some string names may collide.\n"
               "E.g. \"2 Swarms\" -> BBZSTRING_ID(__Swarms).\n");
        return 1;
    }

    char str[1024] = "./bo2bbo ";
    char* outFile = remove_ext(basename(argv[1]), '.', PATH_SEP);
    outFile = (char *)realloc(outFile, strlen(outFile) + 5);
    strcat(outFile, ".bbo");

    basename(argv[1]);
    strcat(str, argv[1]);
    strcat(str, " ");
    strcat(str, outFile);

    if (bo2bbo(argv[1], outFile) != BO2BBO_OK) {
        fprintf(stderr, "Failed to run bo2bbo on %s\n", basename(argv[1]));
        return 1;
    }

    if (bbo2header(argv[1], outFile, argv[2]) != BBO2HEADER_OK){
        fprintf(stderr, "Failed to run bbo2header on %s\n", basename(outFile));
        return 1;
    }

    free(outFile);

    return 0;
}