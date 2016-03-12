#include "book.h"
#include<iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string.h>
using namespace std;
void book::create_book(char numeAutor[],char numeCarte[])
{
    strcpy(aName,numeAutor);
    strcpy(bName,numeCarte);
}
