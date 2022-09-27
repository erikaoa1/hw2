#include <iomanip>
#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;


std::set<std::string> Movie::keywords() const
{
		std::set<std::string> results;

		// inserting movie name as a keyword 
		std::set<std::string> nameWords = parseStringToWords(name_);
		results.insert(nameWords.begin(), nameWords.end());

		// inserting movie genre as a keyword 
		std::set<std::string> genreWords = parseStringToWords(genre_);
		results.insert(genreWords.begin(), genreWords.end());

		return results;
}


std::string Movie::displayString() const
{
	//converting price to string
	std::ostringstream strs;
  strs << price_;
  std::string priceString = strs.str();

	std:: string movieInfo;
	movieInfo = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + priceString + " " + std::to_string(qty_) + " left.";
	return movieInfo;
}

void Movie::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}


Movie::Movie (std::string category, std::string name, double price, int qty, std::string genre, std::string rating) :
Product(category, name, price, qty)
{
	genre_ = genre;
	rating_ = rating;
}