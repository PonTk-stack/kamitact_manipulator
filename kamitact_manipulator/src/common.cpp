#include "kamitact_manipulator/common.h"


std::string StringCat(const char *s1, const char *s2){
    size_t len = strlen(s1) + strlen(s2);
    char *str = (char *)malloc(len + 1);
    unsigned int i;

    str[i=0] = *s1;
    while ( (str[++i]=*++s1) != '\0'){};
    str[i] = *s2;
    while ( (str[++i]=*++s2) != '\0'){};
    return str;
}
