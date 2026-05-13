#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

extern const char *OPTSTRING;

void arg_parser_init(int argc, char **argv);
int arg_parser_process_arg(int opt);
#endif
