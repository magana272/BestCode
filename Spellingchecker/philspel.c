/*
 * Include the provided hash table library.
 */
#include "hashtable.h"

/*
 * Include the header file.
 */
#include "philspel.h"

/*
 * Standard IO and file routines.
 */
#include <stdio.h>

/*
 * General utility routines (including malloc()).
 */
#include <stdlib.h>

/*
 * Character utility routines.
 */
#include <ctype.h>

/*
 * String utility routines.
 */
#include <string.h>

/*
 * This hash table stores the dictionary.
 */
HashTable *dictionary;

/*
 * The MAIN routine.  You can safely print debugging information
 * to standard error (stderr) as shown and it will be ignored in
 * the grading process.
 */
int convertandcheck(void* word, int wordlength){
 char* word1 =(char *) word;
 char * check = (char*) malloc(sizeof(char) * wordlength+1);
 if(check == NULL){
        exit(1);
 }
 strcpy(check, word1);
 int i ;
 char * regular;
 char * capfirst;
 char * alllower;
 int found = 0;
 regular = (char*) malloc((sizeof(char) * wordlength));
 if(regular == NULL){
        exit(1);
 }
 capfirst =(char*) malloc((sizeof(char) * wordlength) );
 if(capfirst == NULL){
        exit(1);
 }
 alllower =(char*) malloc((sizeof(char) * wordlength ));
 if(alllower == NULL){
        exit(1);
 }
 strcpy(regular, check);
 if(findData(dictionary, regular) != NULL){
         found = 1;
     }
 strcpy(alllower, word1);
 for(i=0; i <= wordlength; i++){
        alllower[i] = tolower(regular[i]);
         }
 if(findData(dictionary, alllower) != NULL){
         found = 1;
 }
 strcpy(capfirst, regular);
 for(i=1; i <= wordlength; i++){
        capfirst[i] = tolower(regular[i]);
 }
 if(findData(dictionary, capfirst) != NULL){
        found = 1;
}
if(check){
        free(check);
}
if(regular){
        free(regular);
}
if(capfirst){
        free(capfirst);
}
if(alllower){
        free(alllower);
     }
            return found;

    }

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Specify a dictionary\n");
    return 0;
  }
  /*
   * Allocate a hash table to store the dictionary.
   */
  fprintf(stderr, "Creating hashtable\n");
  dictionary = createHashTable(2255, &stringHash, &stringEquals);

  fprintf(stderr, "Loading dictionary %s\n", argv[1]);
  readDictionary(argv[1]);
  fprintf(stderr, "Dictionary loaded\n");

  fprintf(stderr, "Processing stdin\n");
  processInput();
  int theSize = (dictionary->size);
  int i;
  struct HashBucket * head;
  struct HashBucket * ptr;
  for(i=0; i < theSize;i++){
       head = dictionary->data[i];
    while (head != NULL){
        ptr = head;
               head = head->next;
//        printf("%s \n", (char*)ptr->data);
               free(ptr->data);
        free(ptr->key);
        free(ptr);
      }
    free(head);
   }
return 0;
}
  /*
   * The MAIN function in C should always return 0 as a way of telling
   * whatever program invoked this that everything went OK.
   */

/*
 * This should hash a string to a bucket index.  Void *s can be safely cast
 * to a char * (null terminated string) and is already done for you here
 * for convenience.
 */
        unsigned int stringHash(void*s){
            unsigned int hash = 5381;
            unsigned int c;
            while((c = (unsigned int)*(char*)s++)){
                hash = ((hash << 5) + hash) + c;
            }
        return hash;
    }

//    char *string = (char *)s;
//    unsigned int returnVAl = 0;
//    int i;
//    siet addae_t length = (size_t)(strlen((char *)s) - 1) ;
//    for(i = 0; length >= 0; i++){
//        returnVAl += ((unsigned int) string[i]) * ((unsigned int) powe((unsigned int) 126,(unsigned int)length));
//        length-- ;
//    }
//    return returnVAl;

/*
 * This should return a nonzero value if the two strings are identical
 * (case sensitive comparison) and 0 otherwise.
 */
int stringEquals(void *s1, void *s2) {
    char *string1 = (char *)s1;
    char *string2 = (char *)s2;
    return (strcmp(string1,string2) == 0);
}

/*
 * This function should read in every word from the dictionary and
 * store it in the hash table.  You should first open the file specified,
 * then read the words one at a time and insert them into the dictionary.
 * Once the file is read in completely, return.  You will need to allocate
 * (using malloc()) space for each word.  As described in the spec, you
 * can initially assume that no word is longer than 60 characters.  However,
 * for the final 20% of your grade, you cannot assumed that words have a bounded
 * length.  You CANNOT assume that the specified file exists.  If the file does
 * NOT exist, you should print some message to standard error and call exit(0)
 * to cleanly exit the program.
 *
 * Since the format is one word at a time, with new lines in between,
 * you can safely use fscanf() to read in the strings until you want to handle
 * arbitrarily long dictionary chacaters.
 */
void readDictionary(char *dictName){
    FILE *fptr;
    fptr =  fopen(dictName,"r");
    if (fptr  == NULL){
        exit(1);
    }
    int wordlength = 0;
    int size = 1;
    char *word = calloc(size,sizeof(char) * size);
    char *pass = calloc(size,sizeof(char) * size);
    int thechar;
    char letter;
    while((thechar = fgetc(fptr))){
        letter = (char)thechar;
        word[wordlength] = letter;
        wordlength ++;
        if(thechar == EOF){
            //emptyfile
            if(wordlength > 1){
                word[wordlength] = '\0';
                strcpy(pass, word);
                insertData(dictionary, pass, pass);
                free(word);
                free(pass);
                   }
            break;
        }
        else{
            if (letter == ' '){
                                 free(pass);
    free(word);
        break;
        }
        if(letter == '\n'){
                word[wordlength-1] = '\0';
                strncpy(pass, word, wordlength);
                insertData(dictionary, pass, pass);
                free(word);
                free(pass);
                word = calloc(size , sizeof(char) * size);
                pass = calloc(size, sizeof(char) * size);
                wordlength = 0;
        }
            if(wordlength >= size){
                word = realloc(word, (sizeof(char) * wordlength) + 1);
                pass = realloc(pass, (sizeof(char) * wordlength) + 1);
            }

        }
    }
    if(word){
    free(word);
    }
    if(pass){
    free(pass);
    }
    fclose(fptr);
}
/*
 * This should process standard input (stdin) and copy it to standard
 * output (stdout) as specified in the spec (e.g., if a standard
 * dictionary was used and the string "this is a taest of  this-proGram"
 * was given to stdin, the output to stdout should be
 * "this is a teast [sic] of  this-proGram").  All words should be checked
 * against the dictionary as they are input, then with all but the first
 * letter converted to lowercase, and finally with all letters converted
 * to lowercase.  Only if all 3 cases are not in the dictionary should it
 * be reported as not found by appending " [sic]" after the error.
 *
 * Since we care about preserving whitespace and pass through all non alphabet
 * characters untouched, scanf() is probably insufficent (since it only considers
 * whitespace as breaking strings), meaning you will probably have
 * to get characters from stdin one at a time.
 *
 * Do note that even under the initial assumption that no word is longer than 60
 * characters, you may still encounter strings of non-alphabetic characters (e.g.,
 * numbers and punctuation) which are longer than 60 characters. Again, for the
 * final 20% of your grade, you cannot assume words have a bounded length.
 */
void processInput() {
/// inilatlize variables
char* word;
int letter;
int maxWordlen  = 60;
int lengthOfword = 0;
char *error = " [sic]";
int wordch = 0;
int spellerror = 0;
///malloc space for letters
word =(char*)malloc((sizeof(char) *maxWordlen));
//counter
if(!word){
        exit(1);
}
while((letter = getchar())){
        if((letter>= 65 && letter <= 90) || (letter >= 97 && letter <= 122)){
                wordch = 1;
                word[lengthOfword] = (char)letter;
                lengthOfword++;
                if (lengthOfword >= maxWordlen){
                         word = realloc(word, 1+( lengthOfword * sizeof(char)));
                 }
        }
        else{
                if (wordch){
                    word[lengthOfword] = '\0';
                    wordch = 0;
                    if(convertandcheck((void*)word, lengthOfword)== 0){
                            spellerror = 1;
                    }
                    if(spellerror){
                        printf("%s", error);
                        spellerror = 0;
                    }
                    if(word){
                        free(word);
                        word = NULL;
                        word = malloc(maxWordlen*sizeof(char));
                        lengthOfword = 0;
                    }
                }
            if(letter == EOF){
                break;
            }
        
    }
    letter = putchar(letter);
    }
    if(word){
            free(word);

    }
}
