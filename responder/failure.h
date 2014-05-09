#ifndef FAILURE_H_
#define FAILURE_H_
#include <string>
namespace Failure
{
	inline std::string bad_input() { return "bad input format"; }
	inline std::string in_use() { return "username is already in user. Try again.";}
	inline std::string already_logged_in() { return "you are already logged in"; }
	inline std::string access_denied() { return "access denied"; }
	inline std::string wrong_credentials() { return "wrong username or password"; }
	inline std::string book_not_found() { return "book not found"; }
	inline std::string book_not_in_library() { return "book not found in your library"; }
	inline std::string have_book() { return "book is already in your library"; }
	inline std::string shelf_already_exists() { return "shelf already exists in your library";}
	inline std::string shelf_not_found() { return "shelf not found in your library"; }
	inline std::string book_is_in_shelf() { return "the book is already in the shelf"; }
	inline std::string is_in_stared() { return "you've already starred this book"; }
	inline std::string user_not_found() { return "user not found"; }
	inline std::string already_following() { return "you already follow him"; }
}


#endif
