#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  
  // Bubble sort array based of name
  for(int i = 0; i < count - 1; i++) {
    for(int j = 0; j < count - 1 - i; j++) {
      if (strcmp(array[j], array[j + 1]) > 0) {
        char *tmp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = tmp;
      }
    }
  }
  
  for (int i = 0; i < count; i++) {
    printf("%s\n", array[i]);
    free(array[i]);
  }

  free(array);
  closedir(dir);
  return 0;
}
