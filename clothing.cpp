#include <iomanip>
#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;


std::set<std::string> Clothing::keywords() const
{
		std::set<std::string> results;

		// add clothing name as a keyword 
		std::set<std::string> nameWords = parseStringToWords(name_);
		results.insert(nameWords.begin(), nameWords.end());

		// add clothing brand as a keyword 
		std::set<std::string> brandWords = parseStringToWords(brand_);
		results.insert(brandWords.begin(), brandWords.end());

		return results;
}

std::string Clothing::displayString() const
{
	//converting price to string
	std::ostringstream strs;
  strs << price_;
  std::string priceString = strs.str();

	std:: string clothingInfo;
	clothingInfo = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + priceString + " " + std::to_string(qty_) + " left.";
	return clothingInfo;
}

void Clothing::dump(std::ostream& os) const
{
	os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}

Clothing::Clothing (std::string category, std::string name, double price, int qty, std::string size, std::string brand) :
Product(category, name, price, qty)
{
	size_ = size;
	brand_ = brand;
}