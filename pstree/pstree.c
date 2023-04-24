#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>

#define true ((unsigned char)(1))
#define false ((unsigned char)(0))

/* 打印信息 */
static const char *help_message = "Usage: pstree [-pn]\n   or: pstree -V\n"
                                  "Display a tree of processes.\n"
                                  "  -p, --show-pids     show PIDs; implies -c\n"
                                  "  -n, --numeric-sort  sort output by PID\n"
                                  "  -V, --version       display version information\n";

/* 命令行参数结构 */
static struct option long_options[] = {
    {"show-pids", no_argument, NULL, 'p'},
    {"numeric-sort", no_argument, NULL, 'n'},
    {"version", no_argument, NULL, 'V'},
    {0, 0, 0, 0}};

/* 记录参数 */
static unsigned char pFlag = false;
static unsigned char nFlag = false;

/* 命令行参数解析 */
void parseArgs(int argc, char *argv[])
{
  char ch;
  int option_index = 0;

  while (-1 != (ch = getopt_long(argc, argv, "pnV", long_options, &option_index)))
  {
    switch (ch)
    {
    case 'p':
      pFlag = true;
      break;
    case 'n':
      nFlag = true;
      break;
    case 'V':
      printf("pstree version: 2023\n");
      break;
    default:
      printf("%s", help_message);
      exit(0);
    }
  }
}

int main(int argc, char *argv[])
{
  parseArgs(argc, argv);

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
