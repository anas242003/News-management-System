#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <stack>
#include<vector>
#include"loadAndStoreFiles.h"
#include <random>
#include <algorithm>

using namespace std;
class User
{
public:
	userData usr;

	User(string userName,
		unordered_map<string, userData>&users,
		unordered_map<int, NewsArticle>&news,
		vector<int>& ids,
		unordered_map<string, vector<int>>&cats,
		loadAndStoreFiles tool);

	void display_latest_news(unordered_map<int, NewsArticle>,
		vector<int> ids,
		loadAndStoreFiles tool);

	void rate_news(int id, float rating,

		unordered_map<int, NewsArticle>& news,
		vector<int>& ids,
		unordered_map<string, vector<int>>& categorys,

		loadAndStoreFiles tool);

	void display_categories_news( string cat, 
		unordered_map<int, NewsArticle>news,
		loadAndStoreFiles tool);

	void display_rating_news(unordered_map<int, NewsArticle>news,
		loadAndStoreFiles tool);

	void add_comment( 
		int id, string comm,
		unordered_map<int, NewsArticle>&news,
		loadAndStoreFiles tool);


	bool contain(vector<int>ids, int id);
	void display_by_preferance( unordered_map<string, vector<int>>& categorys, unordered_map<int, NewsArticle>& news
		                        , loadAndStoreFiles tool);
};

