#include <unordered_map>
#include <streambuf>
#include <iostream>
#include <MiniJava.lexer.h>

int main() {
    yyscan_t scanner;
    if (yylex_init(&scanner)) {
        throw std::runtime_error("Failed initialization scanner");
    }

    YY_BUFFER_STATE state = yy_scan_string("down down down", scanner);

    std::cout << yylex(scanner);




    /*
    Lexer lexer;
    while (true) {
        int token = lexer.ScanToken();
        if (token == TOKEN_EXIT) {
            std::cout << "Good bye" << std::endl;
            return 0;
        }
        std::cout << token << std::endl;
    }*/
    return 0;
}
