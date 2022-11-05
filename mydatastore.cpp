#include <iomanip>
#include <iterator>
#include "book.h"
#include "clothing.h"
#include "movie.h"
#include "util.h"
#include "mydatastore.h"

void MyDataStore::addProduct(Product* p)
{ 
	std::set<std::string> keywords = p->keywords();

	for (std::set<std::string>::iterator keywordsIt = keywords.begin(); keywordsIt != keywords.end(); ++keywordsIt){ //iterate through a products' keywords()
			keywordProductMatcher[*keywordsIt].insert(p); //add product to the set that is linked with this keyword 
		}

	productVector.push_back(p); //add product to the productVector containing all the products.
}

void MyDataStore::addUser(User* u)
{
	userMap[u->getName()] = u;
	userVector.push_back(u);
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type)
{
	std::set<Product*> hits;

	if (type == 0){ //AND
	for(std::vector<std::string>::iterator searchedTerm = terms.begin(); searchedTerm != terms.end(); ++searchedTerm)
	{
		if (searchedTerm == terms.begin()){ //if this is the first searched term 
				hits = keywordProductMatcher.find(convToLower(*searchedTerm))->second;  //initially set hits = to the products associated with the first searched term
		} else { // run setIntersection on first term's products and every other searched term's products 
			hits = setIntersection(hits, keywordProductMatcher.find(convToLower(*searchedTerm))->second );
		}
	}
			std::vector<Product*> results(hits.begin(), hits.end()); //converting hits set to a vector for return
			return results;
	}
	 
	//OR SEARCH
	for (std::vector<std::string>::iterator searchedTerm = terms.begin(); searchedTerm != terms.end(); ++searchedTerm){
				if (keywordProductMatcher.find(*searchedTerm)  != keywordProductMatcher.end()){//there are products with this keyword
						hits.insert(keywordProductMatcher.find(*searchedTerm)->second.begin(), keywordProductMatcher.find(*searchedTerm)->second.end() ); 
						//add all the prodcuts asscoiated with this keyword to hits^
				}			
		}
		std::vector<Product*> results(hits.begin(), hits.end()); //converting hits set to a vector for return
		return results;
	}


void MyDataStore::addCart(std::string username, Product* product)
{
	if (userMap.find(username) == userMap.end()){ //username is not valid
		std::cout << "Invalid request" << std::endl;
	}
	else {
		cart[username].push_back(product); //adds product to this user's cart 		
	}	

}

void MyDataStore::viewCart(std::string username)
{
		if (userMap.find(username) == userMap.end()){ //username is not valid
		std::cout << "Invalid username" << std::endl;
		return;
	}
	else if (cart.find(username) == cart.end()){ 		// this user's cart is empty
		return;
	}
	else{
		//displaying cart items
		int cartIndex =1;
		std::deque<Product*> userCart = cart.find(username)->second;
		while (!userCart.empty() ){
		std::cout << "Item " << cartIndex << std::endl;
		std::cout<<	userCart.front()->displayString() << std::endl;
		std::cout << std::endl;
		cartIndex++;
		userCart.pop_front();
		}
	}
}

void MyDataStore::buyCart(std::string username)
{
	if (userMap.find(username) == userMap.end()){ //invalid username
	std::cout << "Invalid username" << std::endl;
	return;
	}
	else if (cart.find(username) == cart.end()){  // this user's cart is empty
		return;
	}
	std::deque<Product*> userCart = cart.find(username)->second; //userCart = copy of user's cart
	for(std::deque<Product*>::iterator cartIt = userCart.begin(); cartIt != userCart.end();){
		if( ((*cartIt)->getQty() > 0) && (userMap.find(username)->second->getBalance() >= (*cartIt)->getPrice()) ){ 
			//if the item is in stock and the user's funds is greater or = to the price ^
				(*cartIt)->subtractQty(1);
				userMap.find(username)->second->deductAmount((*cartIt)->getPrice());
				cartIt = userCart.erase(cartIt); //deletes item from cart & adjusts iterator
		}
		else{
			++cartIt;
		}
	}
	cart.find(username)->second = userCart; //set user's cart = to the updated cart, after purchase removals
}


MyDataStore::~MyDataStore() 
{
	//deleting products and users to free heap usage

	for (std::vector<Product*>::iterator productIt = productVector.begin(); productIt != productVector.end();){
		delete *productIt;
		if (*productIt != nullptr){
			productIt = productVector.erase(productIt);
		}else {
			++productIt;
		}
	}

	for (std::vector<User*>::iterator userIt = userVector.begin(); userIt != userVector.end();){
		delete *userIt;
		if (*userIt != nullptr){
			userIt = userVector.erase(userIt);
		}else {
			++userIt;
		}
	}
}

void MyDataStore:: dump(std::ostream& ofile)
{
	ofile << "<products>" << "\n";
	for (std::vector<Product*>::iterator productIt = productVector.begin(); productIt != productVector.end(); productIt++)
	{
		(*productIt)->dump(ofile);
	}
	ofile <<"</products>" << "\n";

	ofile << "<users>" << "\n";
	for (std::vector<User*>::iterator userIt = userVector.begin(); userIt != userVector.end(); userIt++)
	{
		(*userIt)->dump(ofile);
	}
	ofile << "</users>";
}
