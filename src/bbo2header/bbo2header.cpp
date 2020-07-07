#include <stdint.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>

#include "bbo2header.h"


bool is_valid_char(char c) {
    return
        (c >= 'A' && c <= 'Z') ||
        (c >= 'a' && c <= 'z') ||
        (c >= '0' && c <= '9') ||
        c == '_' ||
        c == '\0';
}

bbo2header_ret bbo2header(char* bo_file, char* bbo_file, char* output_file){

    if(bo_file == NULL || bbo_file == NULL || output_file == NULL){
        return BBO2HEADER_ERR_NULL;
    }

    FILE* f_in  = fopen(bbo_file, "rb");
    if (!f_in) {
        fprintf(stderr, "Cannot open %s\n", bbo_file);
        return BBO2HEADER_ERR_FILE;
    }

    FILE* f_out = fopen(output_file, "w");
    if (!f_out) {
        fprintf(stderr, "Cannot open %s\n", output_file);
        return BBO2HEADER_ERR_FILE;
    }

    fseek(f_in, 0, SEEK_END);
    uintmax_t bcode_size = (uintmax_t)ftell(f_in);
    fseek(f_in, 0, SEEK_SET);

    fprintf(f_out, "/***************************************************/\n");
    fprintf(f_out, "//      THIS IS A GENERATED FILE, DO NOT MODIFY      \n");
    fprintf(f_out, "/***************************************************/\n\n");

    fprintf(f_out, "#ifndef ARGONCODEGEN_H\n");
    fprintf(f_out, "#define ARGONCODEGEN_H\n\n");
    fprintf(f_out, "#include <inttypes.h>\n\n");
    fprintf(f_out, "const uint8_t bcode[] = {");

    if (bcode_size > 0) {
        uint8_t buf;
        fread(&buf, 1, 1, f_in);
        fprintf(f_out, "%" PRIu8, buf);
        for (unsigned int i = 1; i < bcode_size; ++i) {
            fread(&buf, 1, 1, f_in);
            fprintf(f_out, ",%" PRIu8, buf);
        }
        // We make sure that the alignment is on 2 bytes because it will be in the flash and
        // the alignment is needed for the simulator
        if (bcode_size % 2 == 1) {
            fprintf(f_out, ",0");
        }
    }

    fprintf(f_out, "};\n\n");
    fprintf(f_out, "const uint16_t bcode_size = %d;\n\n", (unsigned int)bcode_size);

    FILE* f_obj = fopen(bo_file, "rb");

    if (!f_obj) {
        fprintf(stderr, "Cannot open %s\n", bo_file);
        return BBO2HEADER_ERR_FILE;
    }

    char buf;
    char str[128] = "";
    uint16_t strcnt;
    fread(&strcnt, sizeof(strcnt), 1, f_obj);
    for (int i = 0; i < strcnt; ++i) {
        strcpy(str, "");
        do {
            fread(&buf, sizeof(buf), 1, f_obj);
            if (!is_valid_char(buf)) {
                buf = '_';
            }
            strncat(str, &buf, 1);
        } while(buf != '\0');
        if (!strchr(str, ' ')) {
            fprintf(f_out, "#define BBZSTRID_%s %d\n", str, i);
        }
    }

    fprintf(f_out, "\n#endif // !ARGONCODEGEN_H\n");

    fclose(f_in);
    fclose(f_out);
    fclose(f_obj);

    return BBO2HEADER_OK;

}