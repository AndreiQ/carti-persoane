#ifndef BOOK_H
#define BOOK_H


class book
{
private:
    //char bookNr[3];

    bool isBorrowed=false;
public:
    char aName[30];
    char bName[30];
    book();
    void create_book();
    void show_book();
    void modify_book();
};

#endif // BOOK_H
