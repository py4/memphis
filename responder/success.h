#ifndef SUCCESS_H_
#define SUCCESS_H_
#include <string>
namespace Success
{
	inline std::string ok_signup() { return "successfully signed up"; }
	inline std::string ok_login() { return "successfully logged in"; }
	inline std::string ok_logout() { return  "successfully logged out";}
	inline std::string book_added() { return "book successfully added to your library";}
	inline std::string shelf_added() { return "shelf successfully added to your library"; }
	inline std::string book_added_to_shelf() { return "book successfully added to the shelf"; }
	inline std::string liked() { return "starred"; }
	inline std::string followed() { return "you now follow him"; }
	inline std::string updated() { return "database successfully updated"; }
}
#endif
