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
*                                                                                 
*  Written by Linus Lagerhjelm 
*
*/


static int NR_OF_WORDS = 4; 
static const char dict_path[] = "../dictionaries/";

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
     "Arguments: \n"
     " -n <words> \t number of words to include\n"
     " list \t\t prints a list of supported langugages\n"
     " <dictionairy> \t specify dictionairy to choose words from (to add multiple, separate with space)\n");
 
   exit(EXIT_FAILURE); 
}
void print_available_dictionaries(list *list) {
  printf("%s\n", "Available dictionaries:");
  for (int i = 0; i < list_get_size(list); ++i) {
    printf("%s\n", (char *)list->item[i]->data);
  }
}
list *get_directories() {
  int i = 0;
  list *list = new_list();
  struct dirent *pDirent;
  DIR *dic_dir = opendir(dict_path);
  if ( !dic_dir ) { error("ERROR: Could not find dictionaries\n"); }

  //Open directory with dictioneries and read the file names
  while ( ++i && ((pDirent = readdir(dic_dir)) != NULL)) {
    if ( !strncmp(pDirent->d_name, ".", 2) == 0 && 
          !strncmp(pDirent->d_name, "..", 3) == 0) {
     list = list_add(list, new_list_item(remove_extension(pDirent->d_name)));
    }
  }
  closedir(dic_dir);
  return list;
}
char *build_file_name(char *name) {
  char *fname = calloc( 1, BUFSIZ*sizeof(char) );
  strncat(fname, dict_path, BUFSIZ);
  strncat(fname, name, BUFSIZ);
  strncat(fname, ".dict", BUFSIZ);
  return fname;
}
char **open_dict(char *name, int dict_length[]) {
  char *fname = build_file_name(name); 
  FILE *fp = sfopen(fname);
  free(fname);
  return read_file(fp, dict_length);
}
void get_random_words(char **words, list *selected_dict) {
  int random[2]; //[0] = which dict, [1] = which word
  int dict_length[NR_OF_WORDS];
  char ***dict_contents = salloc(list_get_size(selected_dict)*sizeof(char **));
  
  //Open get the contents of the desired dictionaries
  for (int i = 0; i < list_get_size(selected_dict); ++i) {
    dict_contents[i] = open_dict(selected_dict->item[i]->data, &dict_length[i]);
  }
  //Pick out random words from random dictionairy
  for (int i = 0; i < NR_OF_WORDS; ++i) {
    
    //Handle the case were there's only one dictionary
    if (list_get_size(selected_dict) <= 1) {
      random[0] = 0;
    } else {
      random[0] = arc4random_uniform(list_get_size(selected_dict));
    }

    //Pick a random word from the desired dictionaries
    random[1] = arc4random_uniform(dict_length[random[0]]);
    words[i] = salloc(BUFSIZ*sizeof(char));
    strncpy(words[i], dict_contents[random[0]][random[1]],BUFSIZ);
  } 
}
void pick_out_words(char **new_words, char **old_words) {
  for (int i = 0; i < NR_OF_WORDS; ++i) {
    new_words[i] = salloc(BUFSIZ*sizeof(char));
    strncpy(new_words[i], old_words[arc4random_uniform(NR_OF_WORDS)], BUFSIZ);
    for (int j = 0; j < BUFSIZ; ++j) {
      if (new_words[i][j] == '\n') {
        new_words[i][j] = ' ';
      }
    }
  }
}
void check_input(int argc, char **argv, list *available_dict, list *selected_dict) {
  
  for (int i = 1; i < argc; ++i) {
    list_item *argument = new_list_item(argv[i]);

    //print the list of dictionaries if asked for
    if (strncmp(argv[i], "list", 5) == 0) {
      print_available_dictionaries(available_dict); 
    }  
    
    //fetch the desired number of words to generate
    else if ( strncmp(argv[i], "-n", 3 ) == 0) {
        NR_OF_WORDS = atoi(argv[++i]);
        if(!NR_OF_WORDS || NR_OF_WORDS < 0)
          print_usage();
    } 
    
    //open specified dictionaries
    else if ( list_contains(available_dict, argument) ) {
        if( list_contains(selected_dict, argument) == FALSE) {
          list_add(selected_dict, new_list_item(argv[i]));
        }
    }

    //something went wrong. Print usages and exit
    else {
      print_usage();
    }
    free(argument);
  }
  if (argc <= 1) {
    print_usage();
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
  
  if( list_get_size(selected_dict) > 0 ) {
    char **words = salloc(NR_OF_WORDS*sizeof(char **));
    char **new_words = salloc(NR_OF_WORDS*sizeof(char **));
    get_random_words(words, selected_dict);
    pick_out_words(new_words, words);
    print_result(new_words);
  }

  list_free(available_dict);
  list_free(selected_dict);
  mem_free_func();
  return 0;
}
