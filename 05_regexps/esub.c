#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <regex.h>
void esub(const char *regexp, const char *substitution, const char *input) {
    regex_t regex;
    regmatch_t match[10];  
    if (regcomp(&regex, regexp, REG_EXTENDED)) {
        char errbuf[256];
        regerror(regcomp(&regex, regexp, REG_EXTENDED), &regex, errbuf, sizeof(errbuf));
        fprintf(stderr, "Regex compile error: %s\n", errbuf);
        exit(1);
    }
    if (regexec(&regex, input, 10, match, 0) == 0) {
        char result[1024]; 
        int result_idx = 0;
        const char *sub_ptr = substitution;
        while (*sub_ptr) {
            if (*sub_ptr == '\\') {
                sub_ptr++;
                if (*sub_ptr == '\\') {
                    result[result_idx++] = '\\'; 
                    sub_ptr++;
                } else if (*sub_ptr >= '1' && *sub_ptr <= '9') {
                    int group_num = *sub_ptr - '0';
                    if (group_num < 10 && match[group_num].rm_so != -1) {
                        int group_len = match[group_num].rm_eo - match[group_num].rm_so;
                        memcpy(result + result_idx, input + match[group_num].rm_so, group_len);
                        result_idx += group_len;
                    } else {
                        fprintf(stderr, "Invalid group reference \\%c\n", *sub_ptr);
                        regfree(&regex);
                        exit(1);
                    }
                    sub_ptr++;
                } else {
                    fprintf(stderr, "Invalid escape sequence \\%c\n", *sub_ptr);
                    regfree(&regex);
                    exit(1);
                }
            } else {
                result[result_idx++] = *sub_ptr++;
            }
        }
        result[result_idx] = '\0';
        fwrite(input, 1, match[0].rm_so, stdout);  
        printf("%s", result);  
        fwrite(input + match[0].rm_eo, 1, strlen(input) - match[0].rm_eo, stdout); 
    } else {
        printf("%s", input);
    }
    regfree(&regex);
}
int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <regexp> <substitution> <string>\n", argv[0]);
        return 1;
    }
    const char *regexp = argv[1];
    const char *substitution = argv[2];
    const char *input = argv[3];
    esub(regexp, substitution, input);
    return 0;
}
