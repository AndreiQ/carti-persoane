#ifndef BOOK_H
#define BOOK_H


class book
{
private:
    char bName[30];
    //char bookNr[3];
    char aName[30];
    bool isBorrowed=false;
public:
    book();
    void create_book();
    void show_book();
    void modify_book();
};

#endif // BOOK_H
