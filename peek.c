#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRESHOLD 64

int cmp_string(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

int main(int argc, char *argv[]) {
  printf("Filename\n");
  for(int i = 0; i < 15; i++) {
    (i >= 14) ? printf("\n") : printf("\uf068");
  }

  char *path = (argv[1] != NULL) ? argv[1] : ".";

  DIR *dir = opendir(path);
  struct dirent *entries; 

  int count = 0;
  char **array = NULL;

  while ((entries = readdir(dir))) { 
    char *copy = malloc(strlen(entries->d_name));
    if (!copy) {
      perror("malloc");
      exit(1);
    }
    strcpy(copy, entries->d_name); // Copy entries to copy
    
    char **temp = realloc(array, (count + 1) * sizeof(char *)); // In case realloc failed
    if (!temp) {
      perror("realloc");
      exit(1);
    }
    array = temp; // Proceed only if success
    array[count] = copy; 
    count++;
  }
  
  qsort(array, count, sizeof(char *), cmp_string);
  
  for (int i = 0; i < count; i++) {
    printf("\033[34m%s\033[0m\n", array[i]);
    free(array[i]);
  }

  free(array);
  closedir(dir);
  return 0;
}
