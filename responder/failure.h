#ifndef FAILURE_H_
#define FAILURE_H_

namespace Failure
{
	inline string bad_input() { return "bad input format"; }
	inline string in_use() { return "username is already in user. Try again.";}
	inline string already_logged_in() { return "you are already logged in"; }
	inline string wrong_credentials() { return "wrong username or password"; }
	inline string book_not_found() { return "book not found"; }
	inline string shelf_already_exists() { return "shelf already exists in your library";}
	inline string shelf_not_found() { return "shelf not found in your library"; }
	inline string is_in_stared() { return "you've already starred this book"; }
	inline string user_not_found() { return "user not found"; }
	inline string are_already_friends() { return "you already follow him"; }
}


#endif