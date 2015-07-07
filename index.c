#include "index.h"
#include <stdio.h>
#include <stdlib.h>
#include <argp.h>



const char *argp_program_version =
"1.0";
const char *argp_program_bug_address =
"<ganesh.katrapati@research.iiit.ac.in>";

static char doc[] =
"A program which computes the index of a given file and provides fast search.";

static struct argp_option options[] = {
  {"write",   'w', 0,  0, "Compute the index and save it to the file" },
  {"read",   'r', 0,  0, "Read the index file instead of making a new one." },
  {"random_reads",   'n', "count",  0, "Choose count number of random line numbers to read" },
  {"line-number",   'l', "line_number",  0, "Provide which line number to read" },
  { 0 }
};



struct arguments {
  char *args[2];
  int read;
  int write;
  long line_number;
  long random_count;
};



static error_t parse_opt (int key, char *arg, struct argp_state *state){
  /* Get the input argument from argp_parse, which we
  know is a pointer to our arguments structure. */
  struct arguments *arguments = state->input;
  //printf("%s\n", arguments -> args[0]);
  switch (key)
  {
    case ARGP_KEY_ARG:
    if (state->arg_num >= 2)
    /* Too many arguments. */
    argp_usage (state);

    arguments->args[state->arg_num] = arg;

    break;

    case ARGP_KEY_END:
    /* Not enough arguments. */
    if (state->arg_num < 2)
    argp_usage (state);
    break;

    case 'r':
    arguments -> read  = 1;

    break;

    case 'l':
    arguments -> line_number = atol(arg);
    break;

    case 'n':
    arguments -> random_count = atol(arg);
    break;

    case 'w': default:
    //printf("%s\n", arguments -> args[0]);
    arguments -> write = 1;
    //make_index_from_file(arguments -> args[0], arguments -> args[1], 0);

  }
  return 0;
}


static char args_doc[] = "InputFile IndexFile";
static struct argp argp = { options, parse_opt, args_doc, doc };


int main(int argc, char  ** argv) {
  /* code */
  //make_index_from_file(argv[1], argv[2], 0);
  //read_from_index(argv[2]);
  struct arguments arguments;
  arguments.read = 0;
  arguments.write = 0;
  arguments.line_number = -2;
  arguments.random_count = -2;
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.read) {
    FILE *source_file, *index_file;
    source_file = fopen(arguments.args[0], "r");
    index_file = fopen(arguments.args[1], "r");

    if(arguments.line_number != -2) {
      char *buf = read_from_index(source_file, index_file, arguments.line_number);
      printf("%s", buf);
      free(buf);
    }
    else if (arguments.random_count != -2) {
      long i;
      for (i = 0; i < arguments.random_count; i++) {
        int line_number  = rand() % 10000;
        char *buf = read_from_index(source_file, index_file, line_number);
        printf("%s", buf);
        free(buf);
      }
    }
    else {
      printf("Please Provide the line number or supply -n for random reads\n");
      exit(-1);
    }

    fclose(source_file);
    fclose(index_file);

  }
  else {
    make_index_from_file(arguments.args[0],arguments.args[1],0);
  }

  return 0;
}
