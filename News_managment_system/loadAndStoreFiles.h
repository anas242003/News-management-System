#pragma once
#include <fstream>
#include <sstream>
#include <iostream>

#include <vector>
#include <unordered_map>
#include <set>
#include <stack>

#include "Sorted_LinkedList.h"

using namespace std;

struct NewsArticle  {

    int id =0 ;
    string category;
    string title = "";
    string author;
    string description;
    string date;
    vector<float> rates;
    vector<vector<string>> comments;
    int spam = 0;

    string printRate() {
        float rate = getRate();
        if (rate == 0.0) return "Not Rated";
        return to_string(rate);
    }

    float getRate() {

        if ((rates.size() - 1) == 0) return 0;

        float sm = 0.0;
        for (auto rate : rates) sm += rate;
        return (sm / (rates.size() -1));
    }

    string getcomment() {

        if (comments.size() == 1) return " ";

        string cmnt = "";
        for (auto comment : comments) {
            if (comment[0] == " ") continue;
            cmnt += comment[0] + ": " + comment[1] + "\n\t   ";
        }
        return cmnt;
    }

    string getRateStr() {

        string tempRate = "";

        for (auto rate : rates) tempRate += "*" + to_string(rate);

        return tempRate.substr(1);
    }

    string getCommStr() {

        string tempComments = "";

        for (auto comment : comments) {
            tempComments += "+" + comment[0] + '#' + comment[1];
        }

        return tempComments.substr(1);
    }
};

struct userData {
    string username = "";
    string pass;
    string role;

    vector<int> spam;
    set<string> prefrenceCategory;

    string printSpam() {

        if (spam.size() == 1 && spam[0] == 0) return "Spam Nothing";

        string temp = "";
        for (int id : spam) temp += ", " + to_string(id);

        if (spam.size() != 1 && spam[0] == 0)
            return temp.substr(4);

        return temp.substr(1);
    }

    string getSpamStr() {

        if (spam.size() == 1 && spam[0] == 0) return "*";

        string temp = "";
        for (int id : spam) temp += "*" + to_string(id);
        
        if (spam.size() != 1 && spam[0] == 0)
            return temp.substr(3) + "*";

        return temp.substr(1) + "*";
    }

    string getCatStr() {

        string temp = "";
        for (string catname : prefrenceCategory) temp += "?" + catname;

        if (*prefrenceCategory.begin() == "" && prefrenceCategory.size() != 1) return temp.substr(2)+ "?";

        return temp.substr(1) + "?";
    }

    string printPrefrenceCategory() {

        if (*prefrenceCategory.begin() == "" && prefrenceCategory.size() == 1) return "prefrence Nothing";

        string temp = "";
        for (string id : prefrenceCategory) temp += ", " + id;

        if (*prefrenceCategory.begin() == "" && prefrenceCategory.size() != 1) return temp.substr(4);

        return temp.substr(1);
    }
};

class loadAndStoreFiles
{
public:
    loadAndStoreFiles();

    void saveAndClose(
        unordered_map<string, userData > users,
        unordered_map<int, NewsArticle> news
    );

    string news_path = "news.csv";
    string users_path = "users.csv";

    unordered_map<string, userData> users;

    unordered_map<int, NewsArticle> news;

    unordered_map<string, vector<int>> categorys;
    vector<int> ids;

    void loadUsers();
    void loadNews();

    void saveUsers(unordered_map<string, userData > users);
    void saveNews(unordered_map<int, NewsArticle> news);

    stack<int> getIdsStack(vector<int>ids);
    vector<int> getSortedIds_byRate(unordered_map<int, NewsArticle> news);

    vector<float> getRateVec(string);

    void printUsers(unordered_map<string, userData > users);

    void printNewsByRate(unordered_map<int, NewsArticle> news);

    void printNews(unordered_map<int, NewsArticle> news);

    void printNew(NewsArticle article);

    vector<vector<string>> addCommentVec(string);

    void removeNewsArticle(
        int id,
        unordered_map<int, NewsArticle>& news,
        vector<int>& ids,
        unordered_map<string, vector<int>>& categorys);

    vector<int> getSpamVec(string str);
    set<string> getCatPreVec(string str);
};