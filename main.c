#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdbool.h>


//Struct to hold movie information
struct movie{
  char* title;
  int  year;
  char* lang;
  double rating;
  struct movie* next;
};

//Parse each line and create the movie struct
struct movie *createmovie(char *currLine)
{
    struct movie *currMovie = malloc(sizeof(struct movie));
    // For use with strtok_r
    char *saveptr;
    int a;
    double b;
    // The first token is the title
    char *token = strtok_r(currLine, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year
    token = strtok_r(NULL, ",",&saveptr);
    currMovie->year = atoi(token);

    // The next token is the lang
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->lang = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->lang, token);

    // The last token is the rating **atoi
    token = strtok_r(NULL, "\n", &saveptr);
    currMovie->rating = strtod(token,NULL);

    // Set the next node to NULL in the newly created student entry
    currMovie->next = NULL;

    return currMovie;
}


// Print info of the movie
void printMovie(struct movie* aMovie){

  printf("%s, %d, %s, %.1f\n", aMovie->title,
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


//checks for the year of the movie and prints out the movie and year
void checkYear(struct movie* head, int x)
{
	struct movie* temp = head;
	while (temp != NULL)
	{
		if(temp->year == x){
			printf("%s, %d\n",temp->title, temp->year);
		}
		temp = temp->next;
	}
}



//Finds specific movie languages and prints it out
void pickLang(struct movie* head)
{	
	char l[20];
	printf("Enter language you want to look up\n");
//gets rid of extra white space to use strstr
	scanf("%s\n",&l);
	fgets(l,20,stdin);
	struct movie* temp = head;
	char* check = NULL;

	int len = strlen(l);
	if(l[len-1]=='\n')
	{
		l[len-1] = '\0' ;
}
	while (temp != NULL)
	{	

		 check = strstr(temp->lang,l);
		if(check != NULL)
		{
			printf("%d,%s\n", temp->year,temp->title);
			
		}

		temp = temp->next;
	}

}



//Return a linked list of students by parsing data from each line of the specified file.

struct movie *processFile(char *filePath)
{
    // Open the specified file for reading only
    FILE *movieFile = fopen(filePath, "r");
	int ccc;
	
    if(!movieFile)
    {
      perror("fopen");
    }
    int counter = 0; 
    char *currLine = NULL;
    size_t len = 0;
    ssize_t nread;
    char *token;

    // The head of the linked list
    struct movie *head = NULL;
    // The tail of the linked list
    struct movie *tail = NULL;

    // Read the file line by line
     while ((nread = getline(&currLine, &len, movieFile)) != -1)
    {
   

        // Get a new movie node corresponding to the current line
         struct movie *newNode = createmovie(currLine);
        
       ccc++;
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
     printf("All %d files loaded\n", ccc);
     free(currLine);
     fclose(movieFile);
     return head;
}


//Sets index value then iterate through list comparing the index  to list. Saves it in node if value is higher
void highRate(struct movie* head)
{
	struct movie* a;
	struct movie* b;
	struct movie* c;

	a = head;
	b = head;
	c = NULL;


	while(b !=  NULL)
	{
		
		a = head;	
		c = b;
		while(a != NULL){	
			if(a->year == b->year && a->rating > b->rating)
			{
				c = a;
				
			}
			
			 if (a->next == NULL)
                           {        
                                         printf("%d %s %.1f\n",c->year,c->title,c->rating);
                            }
			a = a->next;
		}
		b = b->next;
	}
}
int main(int argc, char *argv[])
{
	
	
    if (argc < 2)
    {
        printf("You must provide the name of the file to process\n");
        printf("Example usage: ./movies movie_sample_1.csv \n");
        return 0;
    }
    
			
	
    struct movie *list;
    list = processFile(argv[1]);
	int sw = 1;
	int ychoice = 0;
	while(sw != 0)
	{	
		printf("1. Show all movies by year\n");

		printf(	"2. Show highest rated for each year\n");
		printf(	"3. Show title of all movies in specific language\n");
		printf("4. Exit\n");


		scanf("%d", &sw);
		if(sw == 1)
			{
				printf("Enter in year\n");
				scanf("%d", &ychoice);
				
			
				
				checkYear(list,ychoice);
			}
		else if(sw == 3)
			{
				pickLang(list);
			}

		else if(sw == 4)
			{
				sw = 0;
				return 0;
			}	
		
		else if(sw == 2)
			{
				highRate(list);
			}		
		else
			
		{
			printf("Invalid choice\n");
		}
			
	}
   
  return 0;
}
