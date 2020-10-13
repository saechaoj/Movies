#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

//Struct to hold movie information
struct movie{
  char* title;
  char* year;
  char* lang;
  char* rating;
  struct movie* next;
};

//Parse each line and create the movie struct
struct movie *createmovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));
    // For use with strtok_r
    char *saveptr;
    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->year, token);

    // The next token is the lang
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->lang = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->lang, token);

    // The last token is the rating **atoi
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->rating, token);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}


// Print info of the movie
void printMovie(struct movie* aMovie){

  printf("%s, %s %s, %.s\n", aMovie->title,
               aMovie->year,
               aMovie->lang,
               aMovie->rating);
}

// Print the linked list of movies
void printMovieList (struct movie *list)
{
    while (list != NULL)
    {
        printMovie(list);
        list = list->next;
    }
}


//Return a linked list of students by parsing data from each line of the specified file.

struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");
    if(!movieFile)
    {
      perror("fopen");
    }
  
    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;
	printf("movie null");
    // Read the file line by line
     while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {

        // Get a new movie node corresponding to the current line
         struct movie *newNode = createmovie(currLine);
        //
       
         if (head == NULL)
         {
        //     // This is the first node in the linked link
        //     // Set the head and the tail to this node
             head = newNode;
             tail = newNode;
         }
         else
         {
        //     // This is not the first node.
        //     // Add this node to the list and advance the tail
             tail->next = newNode;
             tail = newNode;
         }
    }
     free(currLine);
     fclose(movieFile);
     return head;
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_sample_1.csv \n");
        return 0;
    }
    printf("Path relative to the working directory is: %s\n", argv[1]);


    struct movie *list;
    list = processFile(argv[1]);
    printMovieList(list);
    printMovie(list);
  return 0;
}
