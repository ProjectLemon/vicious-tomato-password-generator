/*
*   Author:             Linus Lagerhjelm
*   Date:                2015-10-25 
*   File:                  common.h
*   Description:      Implements functionallity for basic functions that I find myself write for more 
*                            or less every C project. (Consult below interface for complete list)
*
*    Copyright (C) <2015>  <Linus Lagerhjelm>
*
*    This program is free software: you can redistribute it and/or modify
*    it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*    (at your option) any later version.
*
*    This program is distributed in the hope that it will be useful,
*    but WITHOUT ANY WARRANTY; without even the implied warranty of
*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*    GNU General Public License for more details.
*
*    You should have received a copy of the GNU General Public License
*    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "common.h"

__mem_tracker __mem = {NULL, 0};

/**
* Prints the given error message to standard error and exits the program
*
* Parameter:  (char *) The string to print
*/
void error(char *message){
  fprintf(stderr, "%s", message);
  exit(-1);
}

/**
* Declares a function that dynamically allocates memmory
* using malloc. This function will, however, handle memcheck
* for you. Memmory allocated with this function will also be automatically
* free'd when mem_free_func() is called.
* 
* Parameter:  (size_t) number of bytes to be allocated
* Return:     (void *) pointer to the allocated memmory
* Note:       Will exit program if insufficient memmory
*/
void *salloc(size_t size){
  void *p = malloc(size);
  if(!p){
    error("ERROR: out of memmory");
  }
  mem_reg(p);
  return p;
}

/**
* When this function is called, memory allocated with salloc() 
* and memmory allocated elsewhere but registered with mem_reg() 
* will be free'd
*/
void mem_free_func(){
  for (int i = 0; i < __mem.size; ++i){ 
    free(__mem.list[i]); 
  } 
  free(__mem.list);
  __mem.list = NULL;
  __mem.size = 0;
}

/**
* Register memmory for the library to keep track of for
* safe removal when mem_free_func() is called.
* 
* Parameter:  (void *) pointer to the memmory to register
* Return:     (void ) 
* Note:       This function is allready called internally within salloc()
*/
void mem_reg(void *p){
  __mem.list = realloc( __mem.list, ++(__mem.size)*sizeof(void **));
  __mem.list[__mem.size-1] = p;
}

/**
* This function will safely open a file att the specified path
* and return a pointer to the opened file. Will exit the program if
* the file could not be opened 
*
* Parameter:  (char *) Search path to the file to open
* Return:     (void *) pointer to the opened file
* Note:       Will open the file in r+ mode
*/
FILE *sfopen(char *path){
  FILE *fp = fopen(path, "r+");
  if(!fp){
    error("ERROR: could not open file");
  }
  return fp;
}

/**
* Reads the content of a specified file and returns an array containing 
* All the lines of the file. Returns NULL if file was empty
*
* Parameter:  (FILE *) The file to read from
* Return:     (char **) An array containing the lines of the file
* Note:       The lines of the file can be no more than 1024 char
*/
char **read_file(FILE *fp){
  int i = 0;
  char *buffer = salloc(BUFSIZ*sizeof(char));
  char **lines = NULL;

  while(++i && fgets(buffer,BUFSIZ, fp)){
    char *line = salloc((1+strlen(buffer))*sizeof(char));
    memcpy(line, buffer, strlen(buffer)+1);
    lines = realloc(lines, i*sizeof(char **));
    lines[i-1] = line;
  }
  mem_reg(lines);
  return lines;
}

/**
* Creates a new array of size n and fills it with random values
* 
* Parameter 1:  (int) The array to fill
* Parameter 2:  (int) The size of the array
* Parameter 3:  (int) Numbers will be generated in range 0 - (range-1)
*
* Note:              Overrides the value of srand()
*/
void initialize_random_array(int *array, int n, int range){
    timeval seed;
    gettimeofday(&seed, NULL);
    srand(seed.tv_usec * seed.tv_sec);
    for (int i = 0; i < n; ++i){
        array[i] = rand()%range;
    }
}

/**
* Prints an int array as a sequence of ints. Sepparated by ,
* 
* Parameter 1:  (int *) The array to print
* Parameter 2:  (int) The size of the array
*/
void print_array(int *array, int n){
    for (int i = 0; i < n-1; ++i) {
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[n-1]);
}

/**
* Finds the smallest value in an array
*  
* Parameter 1:  (int *) The array to search in
* Parameter 2:  (int) Length of the array
*/
int min_value_in(int *array, int n){
    int min = array[0];
    for (int i = 1; i < n; ++i){
        if ( min > array[i] ) {
            min = array[i];
        }
    }
    return min;
}

/**
* Takes variable number of integers and returns the smallest one
*
* Parameter:  (int ...) n amount of integers to compare
*
* Return:        (int) smallest parameter value
*/
int min(int n_args, ...){
    int min, temp;
    va_list next_arg;
    va_start(next_arg, n_args);

    min = va_arg(next_arg, int);
    for(int i = 0; i < n_args; ++i){
        if((temp = va_arg(next_arg, int)) < min ){
            min = temp;
        }
    }
    va_end(next_arg);
    return min;
}

/**
* Finds the largest value in an array
*  
* Parameter 1:  (int *) The array to search in
* Parameter 2:  (int) Length of the array
*/
int max_value_in(int *array, int n){
    int max = array[0];
    for (int i = 1; i < n; ++i){
        if ( max < array[i] ) {
            max = array[i];
        }
    }
    return max;
}

/**
* Takes variable number of integers and returns the largest one
*
* Parameter:  (int ...) n amount of integers to compare
*
* Return:        (int) largest parameter value
*/
int max(int n_args, ...){
    int max, temp;
    va_list next_arg;
    va_start(next_arg, n_args);

    max = va_arg(next_arg, int);
    for(int i = 0; i < n_args; ++i){
        if((temp = va_arg(next_arg, int)) > max ){
            max = temp;
        }
    }
    va_end(next_arg);
    return max;
}
