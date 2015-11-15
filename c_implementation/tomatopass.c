#include <dirent.h>
#include "common.h"


/*
* Intense Tomato Password Generator 1.0                                           
*   This generator produces 4 (default) words from a given                        
*   language to be used as a password.                                            
*                                                                                 
*   Usage:                                                                        
*     Arguments should be a list of languages. To get the list of                 
*     supported languages, simply use the single argument "list".                 
*     If one would like to specify number of words produced, use                  
*     the flag "-n" followed by an integer.                                       
*                                                                                 
*     ex: ./tomatopass.py swedish english -n 5                                    
*                                                                                 
*  Written by Linus Lagerhjelm 
*
*/

static int NR_OF_WORDS; 
static const char dict_path[] = "dictionaries/";

void print_usage() {
 printf("Vicious Tomato Password Generator 1.0\n "
   "This generator produces 4 (default) words from a given\n "
   "language to be used as a password.\n"
                                                                                 
   "Usage:\n"
     "Arguments should be a list of languages. To get the list of\n "
     "supported languages, simply use the single argument 'list'.\n "
     "If one would like to specify number of words produced, use \n "
     "the flag '-n' followed by an integer.\n");
 
   exit(EXIT_FAILURE); 
}
void print_available_dictionaries() {
  int i = 0;
  struct dirent *pDirent;
  DIR *dic_dir = opendir(dict_path);

  printf("%s\n\n", "Available dictionaries:");
  while ( ++i && ((pDirent = readdir(dic_dir)) != NULL)) {
    if ( !strncmp(pDirent->d_name, ".", 2) == 0 && 
          !strncmp(pDirent->d_name, "..", 3) == 0) {
      printf("%s\n", pDirent->d_name);
    }
  }
}

void check_input(int argc, char **argv) {
  for (int i = 0; i < argc; ++i) {
    
    //print the list of dictionaries if asked for
    if (strncmp(argv[i], "list", 5) == 0) {
      print_available_dictionaries(); 
    }  
    
    //fetch the desired number of words to generate
    else if ( strncmp(argv[i], "-n", 3 ) == 0) {
        NR_OF_WORDS = atoi(argv[++i]);
        if(!NR_OF_WORDS)
          print_usage();
    } 
    
    //open specified dictionaries
    else if ( 0/*list_contains(argv[i])*/ ) {
      //TODO: implement
    }

    //something went wrong. Print usages and exit
    else {
      print_usage();
    }
  }
}


int main(int argc, char **argv) {
  
  print_available_dictionaries();
  //check_input(argc, argv);

  //char *words[NR_OF_WORDS];

  //get_random_words(words);
  //char *new_words[NR_OF_WORDS];// = choose_random_word(words);
  //output_words(new_words);  

  return 0;
}
