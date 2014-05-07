#ifndef LOGGER_H_
#define LOGGER_H_
#include <string>
namespace Logger
{
	inline string added_to_library(std::string book) { return "added " + book + " to his library"; }
	inline string added_to_shelf(std::string book, std::string shelf) { return "added " + book + " to " + shelf; }
	inline string liked(std::string book) { return "liked " + book; }
}
#endif
