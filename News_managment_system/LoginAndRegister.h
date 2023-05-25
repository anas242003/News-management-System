
#pragma once
#include "loadAndStoreFiles.h"

class LoginAndRegister
{


public:
	unordered_map<int, NewsArticle> news;

	unordered_map<string, userData> users;

	vector<int> ids;

	LoginAndRegister();

	vector<string> login();
	vector<string> regsiter();
};
