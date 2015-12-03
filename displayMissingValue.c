#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFF_SIZE (4092)

static int
msgErr(char const *err_msg)
{
  perror(err_msg);
  return EXIT_FAILURE;
}

static void
revint(int *str, int len)
{
  while (len < 8)
    str[len++] = 0;
  while (len > 0)
    printf("%d\n", str[--len]);
}

static void
displayBytes(int bytes)
{
  int bytestr[8];
  int i = 0;

  while (bytes > 0)
  {
    bytestr[i++] = bytes % 2;
    bytes /= 2;
  }
  revint(bytestr, i);
}

static int
checkMaxValue(FILE *file)
{
  char buff[BUFF_SIZE];
  int maxVal = 0;
  int val;

  while (fgets(buff, BUFF_SIZE, file))
  {
    val = atoi(buff);
    if (val < 0)
      return -1;
    if (val > maxVal)
      maxVal = val;
  }
  fseek(file, 0, SEEK_SET);
  return (maxVal);
}

inline static void
stockBytes(char const *buff, char *bitsvector)
{
  int i;
  char b;
  int val = atoi(buff);

  b = (b | 1);
  i = val / 8;
  b = (b << val % 8);
  bitsvector[i] |= b;
}

static void
displayMissingValueInBinary(char *bitsvector, size_t maxVal)
{
  for (int i = 0; i < (maxVal / 8 + 1); ++i)
  {
    printf("CASE[%d] = ", i);
    displayBytes(bitsvector[i]);
  }
}

static void
displayMissingValue(char *bitsvector, size_t maxVal)
{
  for (int i = 0; i < (maxVal / 8 + 1); ++i)
  {
    for (int j = 0; j < 8 && (i * 8 + j) < maxVal; ++j)
    {
      if (!((bitsvector[i] >> j) & 1))
        printf("Missing Value ==> %d\n", i * 8 + j);
    }
  }
}

static int
checkMissingValue(char const * filename)
{
  char buff[BUFF_SIZE];
  char *bitsvector;
  FILE *file;
  int maxVal;

  file = fopen(filename, "r");
  if (file == 0)
    return msgErr("Could not open the file");
  maxVal = checkMaxValue(file);
  if (maxVal == -1)
    return msgErr("A value is either too small or too big");
  bitsvector = (char *)malloc(sizeof(char *) * (maxVal / 8));
  if (bitsvector == 0)
    return msgErr("Could not allocate memory.");
  while (fgets(buff, BUFF_SIZE, file))
    stockBytes(buff, bitsvector);
  printf("FROM 0 TO %d\n", maxVal);
  displayMissingValue(bitsvector, maxVal);
  return (EXIT_SUCCESS);
}

int
main(int argc, const char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s [FILE]\n", argv[0]);
    return (EXIT_FAILURE);
  }
  return checkMissingValue(argv[1]);
}
