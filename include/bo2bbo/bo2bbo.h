#ifndef BO2BBO_H
#define BO2BBO_H

#define PACKED __attribute__((__packed__))

typedef enum bo2bbo_ret {
    BO2BBO_OK,
    BO2BBO_ERR_NULL,
    BO2BBO_ERR_FILE
} bo2bbo_ret;


bo2bbo_ret bo2bbo(char* input_file, char* output_file);


#endif //BO2BBO_H