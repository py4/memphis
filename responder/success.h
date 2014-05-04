#ifndef SUCCESS_H_
#define SUCCESS_H_

namespace Success
{
	inline string ok_signup() { return "successfully signed up"; }
	inline string ok_login() { return "successfully logged in"; }
	inline string ok_logout() { return  "successfully logged out";}
	inline string  book_added() { return "book successfully added to your library";}
	inline string  shelf_added() { return "shelf successfully added to your library"; }
	inline string book_added_to_shelf() { return "book successfully added to the shelf"; }
	inline string liked() { return "starred"; }
	inline string followed() { return "you now follow him"; }
	inline string updated() { return "database successfully updated"; }
}
#endif
