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
  {"line-number",   'l', "line_number",  0, "Provide which line number to read" },
  { 0 }
};



struct arguments {
  char *args[2];
  int read;
  int write;
  long line_number;
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
  argp_parse (&argp, argc, argv, 0, 0, &arguments);

  if (arguments.read) {
    if(arguments.line_number == -2) {
      printf("Please Provide the line number too\n");
      exit(-1);
    }
    read_from_index(arguments.args[0], arguments.args[1], arguments.line_number);
  }
  else {
    make_index_from_file(arguments.args[0],arguments.args[1],0);
  }

  return 0;
}
