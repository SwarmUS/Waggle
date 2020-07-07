#ifndef BBO2HEADER_H
#define BBO2HEADER_H

#define PACKED __attribute__((__packed__))

typedef enum bbo2header_ret {
    BBO2HEADER_OK,
    BBO2HEADER_ERR_NULL,
    BBO2HEADER_ERR_FILE
} bbo2header_ret;


bbo2header_ret bbo2header(char* bo_file, char* bbo_file, char* output_file);


#endif //BBO2HEADER_H