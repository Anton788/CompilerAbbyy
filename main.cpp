#include <iostream>
#include <cstring>



int main() {
    yyscan_t scanner;
    YY_BUFFER_STATE buf;
    yylex_init(&scanner);
    buf = yy_scan_string("replace me with the string youd like to scan", scanner);
    yylex(scanner);
    yy_delete_buffer(buf, scanner);
    yylex_destroy(scanner);
    return 0;
}