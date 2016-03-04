#include "book.h"
#include<iostream>
#include <stdlib.h>
#include <cstdlib>
using namespace std;
book::book()
{

}
void book::create_book()
{
    cout<<"Numele cartii: ";
    cin.get(bName,30);cin.get();
    cout<<"Numele autorului: ";
    cin.get(aName,30);cin.get();
}
void book::show_book()
{
    cout<<bName<<" ";
    cout<<aName<<endl;
}
