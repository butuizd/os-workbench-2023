#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <dirent.h>

/* 参数解析 */
/* --------------------------------------------------------------------------------------------- */
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
void parse_args(int argc, char *argv[])
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
      exit(1);
    }
  }
}
/* --------------------------------------------------------------------------------------------- */

/* 动态扩容数组 */
/* --------------------------------------------------------------------------------------------- */
typedef struct VECTOR
{
  void *vec;
  long int capacity, size;
} Vector;

static Vector *__VECTOR_INIT(unsigned int type_size, unsigned int vector_capacity)
{
  Vector *vector = (Vector *)malloc(sizeof(Vector));
  if (vector == NULL)
  {
    printf("Memory allocation failed");
    exit(1);
  }

  vector->vec = malloc(type_size * vector_capacity);
  if (vector->vec == NULL)
  {
    printf("Memory allocation failed");
    exit(1);
  }

  vector->size = 0;
  vector->capacity = vector_capacity;
  return vector;
}

static void __VECTOR_PUSH(Vector *vector, unsigned int type_size, void *element)
{
  if (vector->size == vector->capacity)
  {
    vector->vec = realloc(vector->vec, type_size * vector->capacity * 2);
    if (vector->vec == NULL)
    {
      printf("Memory allocation failed");
      exit(1);
    }
    vector->capacity *= 2;

    unsigned char *src = (unsigned char *)element;
    unsigned char *dst = ((unsigned char *)(vector->vec)) + type_size * (vector->size++);
    for (int i = 0; i < type_size; ++i)
    {
      dst[i] = src[i];
    }
  }
}

#define Vector_Init(type, capacity) (__VECTOR_INIT(sizeof(type), (capacity)))
#define Vector_Push(type, vector, element) (__VECTOR_PUSH(vector, sizeof(type), (element)))
#define Vector_Get(type, vector, idx) ((type)((type *)((vector->vec))[(idx)]))
/* --------------------------------------------------------------------------------------------- */

/* 将所有pid放入一个vector中*/
/* --------------------------------------------------------------------------------------------- */
static Vector *pids = NULL;
pids = Vector_Init(pid_t, 8);

/* 将文件名转换为数字 */
static int dirent_to_pid(struct dirent *dirItem)
{
  pid_t pid = 0;

  if (dirItem->d_type == DT_DIR)
  {
    char *name = dirItem->d_name;
    for (int i = 0; name[i]; ++i)
    {
      if (name[i] > '9' || name[i] < '0')
      {
        return -1;
      }
      pid = pid * 10 + name[i] - '0';
    }
    return pid;
  }
  return -1;
}

/* 写入pid */
static void push_pid()
{
  DIR *dir = opendir("/proc/");
  if (dir == NULL)
  {
    printf("Fail to open /proc");
    exit(1);
  }

  struct dirent *dirItem = NULL;
  while (dirItem = readdir(dir) != NULL)
  {
    pid_t pid = dirent_to_pid(dirItem);
    if (pid > 0)
    {
      Vector_Push(pid_t, pids, pid);
    }
  }
}
/* --------------------------------------------------------------------------------------------- */

int main(int argc, char *argv[])
{
  parse_args(argc, argv);

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
