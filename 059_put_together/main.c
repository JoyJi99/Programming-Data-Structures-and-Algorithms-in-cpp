#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Can not open file %s.\n", filename);
    exit(EXIT_FAILURE);
  }
  size_t sz = 0;
  ssize_t len = 0;
  char * keyLine = NULL;
  counts_t * c = createCounts();
  char * newLine;
  while ((len = getline(&keyLine, &sz, f)) >= 0) {
    newLine = strchr(keyLine, '\n');
    *newLine = '\0';
    addCount(c, lookupValue(kvPairs, keyLine));
  }
  free(keyLine);
  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file %s.\n", filename);
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  if (argc < 3) {
    fprintf(stderr, "Useage: ./count_values kvFile keyListFile1 keyListfile2 ...\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "Can not open file %s.\n", outName);
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Can not close file %s.\n", outName);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
 //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
