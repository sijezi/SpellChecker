/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"

 
typedef struct node
{
    struct node* words[LENGTH + 1];  
    bool isWord; 
}
node; 
// struct for first node
struct node* first = {NULL}; 

// some global variables
unsigned int dictSize = 0; 
char word[LENGTH + 1]; 

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    node* head = first; 
    int str = 0; 
    int index = 0; 
    
   
    // 0 for NULL character
    while(str != '\0')
    {
        str = word[index]; 
        
        // uppercase
        if ((str >= 'A') && (str <= 'Z'))
        {
            // 32 represents space for ascii
            str = str + 32; 
        }
        
        // ascii value 39 represents apostrophe
        if ((str == 39) || (str <= 'z' && str >= 'a'))
        {
            if (str == 39)
            {
            
                str = LENGTH + 'a';
            
            }
            if (head->words[str - 'a'] == NULL)
            {
                return 0;
            }
            else
            {
                head = head->words[str - 'a'];
            }
           
        }
        
        // increment index
        index++; 
        
    }
    // return leading node
    return head->isWord; 
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // open file
    FILE* file = fopen(dictionary, "r");
    
    // check file permission
    if (file == NULL)
    {
        return false;
    }

    // memory for the first node
    first = malloc(sizeof(node));
   
    int str = 0;
    
    // temp empty node
    node* temp = NULL;

    // until not end of file
    while(fgetc(file) != EOF)
    {
        fseek(file, -1, SEEK_CUR); 
        temp = first;

        for ( str = fgetc(file); str != '\n'; 
                str = fgetc(file))
        {    
            // 39 ascii code for apostrophe
            if (str == 39)
            {
                // go past z by 1
                str = 'z' + 1;
            }
            if (temp->words[str - 'a'] == NULL)
            {
                // allocate memory for new node
                temp->words[str - 'a'] = malloc(sizeof(node));
		
                // temperory new node
                temp = temp->words[str - 'a'];
	        }
	        else
            {
                // see current node
                temp = temp->words[str - 'a'];
	        }
	    }
	    
        // this is a word
        temp->isWord = true;
        
        // increment words
        dictSize++;
    }
    
    // close file
    fclose(file);
    
    // success! 
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // return total number of words in dictionary otherwise prompt
    return dictSize; 
}

// recursive function to free node
bool noNode(node* currentNode)
{
  // 
    for(int i = 0; i < LENGTH; i++)
    {
        if (currentNode->words[i] != NULL)
        {
            noNode(currentNode->words[i]);  
        }      
	}

    // free node
    free(currentNode);
    return true;
}


/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{ 

    // free the first node 
    return noNode(first); 
}

