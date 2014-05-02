#ifndef FAILURE_H_
#define FAILURE_H_

#include <iostream>
using namespace std;

void bad_input() { cout << "bad input format" << endl; }
void in_use() { cout << "username is already in user. Try again." << endl; }
void already_logged_in() { cout << "you are already logged in" << endl; }
void wrong_credentials() { cout << "wrong username or password" << endl; }
void book_not_found() { cout << "book not found" << endl; }
void shelf_already_exists() { cout << "shelf already exists in your library" << endl; }
void shelf_not_found() { cout << "shelf not found in your library" << endl; }
void is_in_stared() { cout << "you've already starred this book" << endl; }
void user_not_found() { cout << "user not found" << endl; }
void are_already_friends() { cout << "you already follow him" << endl; }


#endif
