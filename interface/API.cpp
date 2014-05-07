#include "API.h"
#include "../libs/user.h"
#include "../libs/library.h"
#include "../libs/book.h"
#include "../libs/shelf.h"
#include "../logger/logger.h"

using namespace std;

API::API()
{
	current_user = NULL;
}

void API::start()
{
	string command_name;
	while(true)
	{
		cout << "> ";
		getline(cin,command);
		try {
			set_params(params,command);
		} catch (string error) {
			cerr << error << endl;
			continue;
		}

		try {
			
			if(params["command"] == "register")
				sign_up();
			else if(params["command"] == "login")
				sign_in();
			else if(params["command"] == "logout")
			{
				current_user = NULL;
				cout << RespondTo::Success::ok_logout() << endl;
				continue;
			}
			else if(params["command"] == "add_book")
				add_book();
			else if(params["command"] == "dump")
				cout << DB::db()->dump_db() << endl;
			else if(params["command"] == "show_book")
				show_book();
			else if(params["command"] == "add_shelf")
				add_shelf();
			else if(params["command"] == "add_to_shelf")
				add_to_shelf();
			else if(params["command"] == "like")
				like();
			else if(params["command"] == "show_books")
				show_books();
			else if(params["command"] == "show_all_books")
				show_all_books();
			else if(params["command"] == "show_favorites")
				show_favorites();
			else if(params["command"] == "follow")
				follow();
			else if(params["command"] == "show_updates")
				show_updates();
			else if(params["command"] == "update_database") //TODO: permission checking
			{
				DB::db()->load_new_books();
				cout << RespondTo::Success::updated() << endl;
			}
			else if(params["command"] == "quit")
			{
				DB::db()->save_to_disk();
				break;
			}
			else {
				cout << "undefined command" << endl;
			}
			
		} catch (string error) {
			cerr << error << endl;
			continue;
		}
	}
}

void API::sign_up()
{
	ensure_no_user();
	
	User* user = DB::db()->find_user(params["username"]);
	if(user != NULL)
		throw RespondTo::Failure::in_use();
	
	user = new User(params["username"], params["password"]);
	DB::db()->add_user(user);
	current_user = user;

	cout << RespondTo::Success::ok_signup() << endl;
}

void API::sign_in()
{
	ensure_no_user();
	
	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
		throw RespondTo::Failure::user_not_found();
	if(user->password != params["password"])
		throw RespondTo::Failure::wrong_credentials();

	current_user = user;

	cout << RespondTo::Success::ok_login() << endl;
}

void API::add_book()
{
	ensure_user();
	
	Book* book = DB::db()->find_book(params["name"]);
	if(book == NULL)
		throw RespondTo::Failure::book_not_found();
	else
	{
		if(current_user->library->add_book(book->name))
		{
			current_user->add_log(Logger::added_to_library(book->name));
			cout << RespondTo::Success::book_added() << endl;
		}
		else
			throw RespondTo::Failure::have_book();
	}
}

void API::show_book()
{
	ensure_user();

	Book* book = DB::db()->find_book(params["name"]);
	if(book == NULL)
		throw RespondTo::Failure::book_not_found();

	book->show_info();
	if(current_user->library->is_in_starred(book))
		cout << "you've starred it" << endl;
	if(current_user->is_in_library(book))
		cout << "it's in your library" << endl;
}

void API::add_shelf()
{
	ensure_user();
	Shelf* found_shelf = current_user->library->get_shelf(params["shelf_name"]);
	if(found_shelf != NULL)
		throw RespondTo::Failure::shelf_already_exists();

	current_user->library->add_shelf(params["shelf_name"]);
	cout << RespondTo::Success::shelf_added() << endl;
}

//TODO: factoriing ensure_user()
//TODO: wrong input when parameters are not passed
//TODO: checking friendships
//TODO: checking public private
void API::add_to_shelf()
{
	ensure_user();
	Shelf* found_shelf = current_user->library->get_shelf(params["shelf_name"]);
	string book_name = params["book_name"];
	
	if(found_shelf == NULL)
		throw RespondTo::Failure::shelf_not_found();

	if(!current_user->library->is_in_library(book_name))
		throw RespondTo::Failure::book_not_in_library();
	else if(found_shelf->has_book(book_name))
		throw RespondTo::Failure::book_is_in_shelf();
	else
	{
		found_shelf->add_book(book_name);
		current_user->add_log(Logger::added_to_shelf(book_name,found_shelf->name));
	}

	cout << RespondTo::Success::book_added_to_shelf() << endl;
}

void API::like()
{
	ensure_user();
	Book* found_book = current_user->library->find_book(params["name"]);
	if(found_book == NULL)
		throw RespondTo::Failure::book_not_in_library();
	if(current_user->library->is_in_starred(found_book))
		throw RespondTo::Failure::is_in_stared();
	
	current_user->library->star_book(found_book);
	current_user->add_log(Logger::liked(found_book->name));
	cout << RespondTo::Success::liked() << endl;
}

void API::show_books()
{
	ensure_user();
	Shelf* found_shelf = current_user->library->get_shelf(params["shelf_name"]);
	if(found_shelf == NULL)
		throw RespondTo::Failure::shelf_not_found();
	found_shelf->show_books();
}

void API::show_all_books()
{
	ensure_user();
	current_user->library->show_all_books();
}

void API::show_favorites()
{
	ensure_user();
	current_user->library->show_favorites();
}

void API::follow()
{
	ensure_user();
	User* user = DB::db()->find_user(params["username"]);
	if(user == NULL)
		throw RespondTo::Failure::user_not_found();
	if(current_user->does_follow(user))
		throw RespondTo::Failure::already_following();
	current_user->follow(user);
	cout << RespondTo::Success::followed() << endl;
}

void API::show_updates()
{
	ensure_user();
	current_user->show_logs();
}

void API::ensure_user()
{
	if(current_user == NULL)
		throw RespondTo::Failure::access_denied();
}

void API::ensure_no_user()
{
	if(current_user != NULL)
		throw RespondTo::Failure::already_logged_in();
}
