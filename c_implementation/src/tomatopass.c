#include <dirent.h>
#include "../include/common.h"
#include "../include/list.h"

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

//TODO: Fix valgrind errors

static int NR_OF_WORDS = 4; 
static const char dict_path[] = "../dictionaries/";

void set_random_seed() {
  timeval seed;
  gettimeofday(&seed, NULL);
  srand(seed.tv_usec * seed.tv_sec);
}
char *remove_extension(char *in_string) {
  int name_length = 0;
  char *out_string = NULL;
  for (int i = 0; i < strlen(in_string); ++i) {
    if(in_string[i] == '.'){
      name_length = i;
    }
  }
  out_string = salloc((name_length+1)*sizeof(char));
  strncpy(out_string, in_string, name_length);
  out_string[name_length] = '\0';
  return out_string;
}
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
void print_available_dictionaries(list *list) {
  printf("%s\n", "Available dictionaries:");
  for (int i = 0; i < list_get_size(list); ++i) {
    printf("%s\n", (char *)list[i]->data);
  }
}
list *get_directories() {
  int i = 0;
  list *list = new_list();
  struct dirent *pDirent;
  DIR *dic_dir = opendir(dict_path);
  if ( !dic_dir ) { error("ERROR: Could not find dictionaries\n"); }

  while ( ++i && ((pDirent = readdir(dic_dir)) != NULL)) {
    if ( !strncmp(pDirent->d_name, ".", 2) == 0 && 
          !strncmp(pDirent->d_name, "..", 3) == 0) {
     list = list_add(list, new_list_item(remove_extension(pDirent->d_name)));
    }
  }
  return list;
}
char *build_file_name(char *name) {
  char *fname = salloc(BUFSIZ*sizeof(char));
  strncat(fname, dict_path, BUFSIZ);
  strncat(fname, name, BUFSIZ);
  strncat(fname, ".dict", BUFSIZ);
  return fname;
}
char **open_dict(char *name) {
  char *fname = build_file_name(name); 
  FILE *fp = sfopen(fname);
  return read_file(fp);
}
void get_random_words(char **words, list *selected_dict) {
  int array[2];
  char ***dict_contents = salloc(list_get_size(selected_dict)*sizeof(char **));
  
  for (int i = 0; i < list_get_size(selected_dict); ++i) {
    dict_contents[i] = open_dict(selected_dict[i]->data);
  }
  for (int i = 0; i < NR_OF_WORDS; ++i) {
    array[0] = rand()%list_get_size(selected_dict);
    array[1] = rand()%3418; //length of smallest dictionairy
    words[i] = salloc(BUFSIZ*sizeof(char));
    strncpy(words[i], dict_contents[array[0]][array[1]],BUFSIZ);
  } 
}
void pick_out_words(char **new_words, char **old_words) {
  for (int i = 0; i < NR_OF_WORDS; ++i) {
    new_words[i] = salloc(BUFSIZ*sizeof(char));
    strncpy(new_words[i], old_words[rand()%NR_OF_WORDS], BUFSIZ);
    for (int j = 0; j < BUFSIZ; ++j) {
      if (new_words[i][j] == '\n') {
        new_words[i][j] = ' ';
      }
    }
  }
}
void check_input(int argc, char **argv, list *available_dict, list *selected_dict) {
  
  for (int i = 1; i < argc; ++i) {

    //print the list of dictionaries if asked for
    if (strncmp(argv[i], "list", 5) == 0) {
      print_available_dictionaries(available_dict); 
    }  
    
    //fetch the desired number of words to generate
    else if ( strncmp(argv[i], "-n", 3 ) == 0) {
        NR_OF_WORDS = atoi(argv[++i]);
        if(!NR_OF_WORDS)
          print_usage();
    } 
    
    //open specified dictionaries
    else if ( list_contains(available_dict, new_list_item(argv[i])) ) {
      list_add(selected_dict, new_list_item(argv[i]));
    }

    //something went wrong. Print usages and exit
    else {
      print_usage();
    }
  }
}
void print_result(char **new_words) {
  printf("\n"); 
  printf("%s\n", "Your new password is:");
  for (int i = 0; i < NR_OF_WORDS; ++i) {
      printf("%s", new_words[i]);
    } 
    printf("\n\n"); 
}

int main(int argc, char **argv) {
  list *available_dict = get_directories();
  list *selected_dict = new_list();
  check_input(argc, argv, available_dict, selected_dict);
  
  char **words = salloc(NR_OF_WORDS*sizeof(char **));
  char **new_words = salloc(NR_OF_WORDS*sizeof(char **));
  set_random_seed();
  get_random_words(words, selected_dict);
  pick_out_words(new_words, words);
  print_result(new_words);

  //mem_free_func();
  return 0;
}
