#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
  const char *help_message = "Usage: pstree [-pn]\n   or: pstree -V\n"
                             "Display a tree of processes.\n"
                             "  -p, --show-pids     show PIDs; implies -c\n"
                             "  -n, --numeric-sort  sort output by PID\n"
                             "  -V, --version       display version information\n";

  struct option long_options[] = {
      {"show-pids", no_argument, NULL, 'p'},
      {"numeric-sort", no_argument, NULL, 'n'},
      {"version", no_argument, NULL, 'V'},
      {0, 0, 0, 0}};

  char ch;
  int option_index = 0;
  char pFlag = 0;
  char nFlag = 0;

  while (-1 != (ch = getopt_long(argc, argv, "pnV", long_options, &option_index)))
  {
    switch (ch)
    {
    case 'p':
      pFlag = 1;
      break;
    case 'n':
      nFlag = 1;
      break;
    case 'V':
      printf("pstree version: 2023\n");
      break;
    default:
      printf("%s", help_message);
      exit(0);
    }
  }

  if (pFlag)
  {
    printf("pid\n");
  }

  if (nFlag)
  {
    printf("numeric\n");
  }

  return 0;
}
