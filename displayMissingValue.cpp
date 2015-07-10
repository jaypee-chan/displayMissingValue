#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>
using namespace std;

#define BUFF_SIZE (4092)

void revint(int *str, int len)
{
  int i = len;

  while (i < 8)
    str[i++] = 0;
  while (i > 0)
    cout << str[--i];
  cout << endl;
}

void displayBytes(int bytes)
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

size_t checkMaxValue(FILE *file)
{
  char buff[BUFF_SIZE];
  size_t maxVal = 0;

  while (fgets(buff, BUFF_SIZE, file))
  {
    if (atoi(buff) > maxVal)
      maxVal = atoi(buff);
  }
  fseek(file, 0, SEEK_SET);
  return (maxVal);
}

void stockBytes(char *buff, char *bitsvector)
{
  char value = 0;
  int i;
  char b;

  b = (b | 1);
  i = atoi(buff) / 8;
  b = b << (atoi(buff) % 8);
  bitsvector[i] |= b;
}

void displayMissingValueInBinary(char *bitsvector, size_t maxVal)
{
  for (int i = 0; i < (maxVal / 8 + 1); ++i)
  {
    cout << "CASE[" << i << "] = ";
    displayBytes(bitsvector[i]);
  }
}

void displayMissingValue(char *bitsvector, size_t maxVal)
{
  char tmp;

  for (int i = 0; i < (maxVal / 8 + 1); ++i)
  {
    for (int j = 0; j < 8 && (i * 8 + j) < maxVal; ++j)
    {
      if (!((bitsvector[i] >> j) & 1))
        cout << "Missing Value ==> " << i * 8 + j << endl;
    }
  }
}

int checkMissingValue(char const * filename)
{
  char buff[BUFF_SIZE];
  char *bitsvector;
  FILE *file;
  size_t maxVal;

  if ((file = fopen(filename, "r")) == NULL)
  {
    cout << "Could not open the file." << endl;
    return (EXIT_FAILURE);
  }
  maxVal = checkMaxValue(file);
  if ((bitsvector = (char *)malloc(sizeof(char *) * (maxVal / 8))) == NULL)
  {
    cout << "Could not allocate memory." << endl;
    return (EXIT_FAILURE);
  }
  while (fgets(buff, BUFF_SIZE, file))
    stockBytes(buff, bitsvector);
  cout << "FROM 0 TO " << maxVal << endl;
  displayMissingValue(bitsvector, maxVal);
  return (EXIT_SUCCESS);
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " [FILE]" << endl;
    return (EXIT_FAILURE);
  }
  if (checkMissingValue(argv[1]) == EXIT_FAILURE)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
