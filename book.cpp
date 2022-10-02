#include <iomanip>
#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

std::set<std::string> Book::keywords() const
{
		std::set<std::string> results;

		// inserting book name as a keyword 
		std::set<std::string> nameWords = parseStringToWords(name_);
		results.insert(nameWords.begin(), nameWords.end());

		//add authors' name as keyword
		std::set<std::string> authorWords = parseStringToWords(author_);
		results.insert(authorWords.begin(), authorWords.end());

		//add isbn as keyword
		results.insert(isbn_);


		return results;
}

std::string Book::displayString() const
{
	//converting price to string
	std::ostringstream strs;
  strs << price_;
  std::string priceString = strs.str();

	std:: string bookInfo;
	bookInfo = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + priceString + " " + std::to_string(qty_) + " left.";
	return bookInfo;
}

void Book::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}

Book::Book (std::string category, std::string name, double price, int qty, std::string isbn, std::string author) :
Product(category, name, price, qty)
{
	isbn_ = isbn;
	author_ = author;
}


