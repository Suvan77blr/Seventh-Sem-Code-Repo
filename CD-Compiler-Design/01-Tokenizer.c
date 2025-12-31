
/*
    Program to Tokenize a C statement.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// List of C keywords.
char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "_Bool", "_Complex", "_Imaginary"
};

// List of C operators.
char *operators[] = {
    "+", "-", "*", "/", "%%", "=", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "!", "&", "|", "^", "~", "<<", ">>", "++", "--", "+=", "-=", "*=", "/=", "%%=", "&=", "|=", "^=", "<<=", ">>=", "->", "."
};

// List of C special sybmols.
char *special_symbols[] = {
    "[", "]", "{", "}", "(", ")", ",", "#", ":", ";"
};

int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
int num_operators = sizeof(operators) / sizeof(operators[0]);
int num_special_symbols = sizeof(special_symbols) / sizeof(special_symbols[0]);

// Function prototypes.
int is_keyword(const char *str);
int is_operator(const char *str);
int is_special_symbol(const char ch);

int main(void) {
    char input_statement[200];
    int keyword_count, operator_count, special_symbol_count, string_count, identifier_count, total_count;

    keyword_count = operator_count = special_symbol_count = string_count = identifier_count = total_count = 0;

    printf("Enter a valid C statement (max 200 characters):\n");
    fgets(input_statement, sizeof(input_statement), stdin);

    // Removing the "\n" character which is added by fgets.
    input_statement[strcspn(input_statement, "\n")] = 0;

    char *current_char = input_statement;

    while(*current_char != '\0') {
        // Skipping the white space.
        if(isspace(*current_char)) {
            current_char++;
            continue;
        }

        // Handling the string literal.
        if(*current_char == '\"') {
            string_count++;
            total_count++;
            current_char++;
            while(*current_char != '\0' && *current_char != '\"') {
                current_char++;
            }
            if(*current_char == '\"') {
                current_char++;
                continue;
            }
        }

        // Handling operators.
        char op_buffer[4];
        short int op_found = 0;

        // Checking 3-character operators.
        if(current_char[0] != '\0' && current_char[1] != '\0' && current_char[2] != '\0') 
        {
            op_buffer[0] = current_char[0];
            op_buffer[1] = current_char[1];
            op_buffer[2] = current_char[2];
            op_buffer[3] = '\0';

            if(is_operator(op_buffer)) {
                operator_count++;
                total_count++;
                current_char += 3;
                op_found = 1;
            }
        }

        // Checking 2-character operators.
        if(!op_found && current_char[0] != '\0' && current_char[1] != '\0')
        {
            op_buffer[0] = current_char[0];
            op_buffer[1] = current_char[1];
            op_buffer[2] = '\0';
            if(is_operator(op_buffer)) {
                operator_count++;
                total_count++;
                current_char += 2;
                op_found = 1;
            }
        }

        if(!op_found) {
            op_buffer[0] = current_char[0];
            op_buffer[1] = '\0';
            if(is_operator(op_buffer)) {
                operator_count++;
                total_count++;
                current_char++;
                op_found = 1;
            }
        }

        if(op_found) {
            // Count increments here.
            continue;
        }

        // Checking for special symbols.
        if(is_special_symbol(*current_char)) {
            special_symbol_count++;
            total_count++;
            current_char++;
            continue;
        }

        // Checking for keywords and identifiers.
        if(isalpha(*current_char)) {
            char word_buffer[50];
            int i = 0;
            while(isalnum(*current_char) && i<sizeof(word_buffer) - 1) {
                word_buffer[i++] = *current_char;
                current_char++;
            }
            word_buffer[i] = '\0';

            if(is_keyword(word_buffer)) {   keyword_count++;    }
            else identifier_count++;

            total_count++;
            continue;
        }

        current_char++;
    }

    puts("\n--- Token Counts ---\n");
    printf("Keywords: %d\n", keyword_count);
    printf("Identifiers: %d\n", identifier_count);
    printf("Operators: %d\n", operator_count);
    printf("Special_Symbols: %d\n", special_symbol_count);
    printf("Strings: %d\n", string_count);
    printf("Total Tokens: %d\n", total_count);

    return 0;
}

/** 
 * Checks if a strings is a C keyword.
 * @param str: the string to check.
 * @return 1 if str is a keyword, 0 otherwise.   
*/
int is_keyword(const char *str) {
    // int num_keywords = sizeof(keywords) / sizeof(keywords[0]);
    for(int i = 0; i<num_keywords; i++) {
        if(strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

/**
 * Checks if a string is a C operator.
 * @param str: the string to check.
 * @return 1 if str is an operator, 0 otherwise.
 */
int is_operator(const char *str) {
    for(int i = 0; i<num_operators; i++) {
        if(strcmp(str, operators[i]) == 0) {
            return 1;
        }
    } return 0;
}

/**
 * Checks if a string is a C special symbol.
 * @param ch: the character to check.
 * @return 1 if ch is a special-symbol, 0 otherwise.
 */
int is_special_symbol(const char ch) {
    for(int i=0; i<num_special_symbols; i++) {
        if(special_symbols[i][0] == ch) {
            return 1;
        }
    } return 0;
}
