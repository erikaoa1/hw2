#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>
#include "datastore.h"
#include "product.h"
#include "user.h"
#include "util.h"



class MyDataStore : public DataStore
{
	public:
    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
		void addCart(std::string username, Product* product);
		void viewCart(std::string);
		void buyCart(std::string);

		~MyDataStore();
   
	 
    void dump(std::ostream& ofile);


		private:
		std::vector<Product*> productVector;
		std::vector<User*> userVector;
		std::map<std::string, User*> userMap;
		std::map<std::string, std::set<Product*> > keywordProductMatcher; //maps each and every keyword to a set of products that have that keyword.


		std::map<std::string, std::deque<Product*> > cart;


};
#endif