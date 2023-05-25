#include <iostream>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include "loadAndStoreFiles.h"

using namespace std;

class Admin{
public:

    int idcounter;

    Admin(string userName, 
        unordered_map<string, userData>& users,
        unordered_map<int, NewsArticle>& news,
        vector<int>& ids,
        unordered_map<string, vector<int>>& categorys,
        loadAndStoreFiles tool);

    int generate_id(vector<int>& ids);

    void postNewsArticle(
        string category,
        string title,
        string author,
        string content,
        string date,

        unordered_map<int, NewsArticle>& news,
        vector<int>& ids,
        unordered_map<string, vector<int>>& categorys);

    void updateNewsArticle(
        int id,
        string category,
        string newtitle,
        string newauthor,
        string newContent,
        string newDate,
        
        unordered_map<int, NewsArticle>& news,
        vector<int>& ids,
        unordered_map<string, vector<int>>& categorys);

    void addCategory(string name,
        unordered_map<string, vector<int>>& categorys);

    bool checkID(int id, vector<int>ids);


    void addAdminAcc(unordered_map<string, userData>&);
};