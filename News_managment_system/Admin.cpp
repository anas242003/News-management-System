#include "Admin.h"
using namespace std;

Admin::Admin(
    string userName,
    unordered_map<string, userData>&users,
    unordered_map<int, NewsArticle>& news,
    vector<int>& ids,
    unordered_map<string, vector<int>>& categorys,
    loadAndStoreFiles tool) 
{
    idcounter = generate_id(ids);

    int choice, id;
    string title, author, category, description, date;

    string prompt = "\nhi, " + userName + ".\n" \
                    "\rChoose an option :\n"\
                    "\r 1. Add news article.\n"\
                    "\r 2. Display all articles.\n"\
                    "\r 3. Remove artical.\n"\
                    "\r 4. Update exsiting artical.\n"\
                    "\r 5. Add New Category.\n"\
                    "\r 6. Add Admin Account.\n"\
                    "\r 7. Exit.\n"\
                    "\r > ";

    do {
        cout << prompt;

        cin >> choice;

        switch (choice) {

        case 1:{
            cout << " title      : "; cin.ignore(); getline(cin, title);
            cout << " author     : "; getline(cin, author);
            cout << " describtion: "; getline(cin, description);
            cout << " category   : "; getline(cin, category);
            cout << " date       : "; getline(cin, date);

            postNewsArticle(category, title, author, description, date, news, ids, categorys);
            cout << "News article added." << endl;
            break;
        }

        case 2:{
            tool.printNews(news);
            break;
        }

        case 3:{
            while (true)
            {
                cout << " remove news with ID : "; cin >> id;

                if (!checkID(id, ids))
                    cout << "invalid id, try again\n";
                else break;

            }

            tool.removeNewsArticle(id, news, ids, categorys);
            cout << "News article removed." << endl;
            break;
        }

        case 4:{
            cout << "If not update say skip or -1 for rate\n";

            while (true)
            {
                cout << "Enter ID of article to update: "; cin >> id;

                if (!checkID(id, ids))
                    cout << "invalid id, try again\n";
                else break;

            }

            cout << "New title      : "; cin.ignore(); getline(cin, title);
            cout << "New author     : "; getline(cin, author);
            cout << "New Describtion: "; getline(cin, description);
            cout << "New category   : "; getline(cin, category);
            cout << "New date       : "; getline(cin, date);

            updateNewsArticle(id,
                category,
                title,
                author,
                description,
                date,
                news, ids, categorys);

            break; 
        }

        case 5: {
            cout << "Enter Category: "; cin >> category;

            if (categorys[category].size() != 0) {
                cout << "sorry, this category already exists.\n";
                break;
            }
            addCategory(category, categorys);
            cout << "category added, done.\n";
            break;
        }

        case 6: {
            addAdminAcc(users);

        }
    
        case 7: {
            cout << "Exiting program." << endl;
            break; 
        }
           
        default:{
            cout << "Invalid choice. Try again." << endl;
            break; 
            }
        }
    } while (choice != 7);

}

int Admin::generate_id(vector<int>& ids)
{
    // Function to generate a unique ID for the article
    int max_id = 0;
    for (int id : ids) {
        if (id > max_id) {
            max_id = id;
        }
    }
        return ++max_id;
}


void Admin::postNewsArticle(
    string category_,
    string title,
    string author,
    string description,
    string date,
    unordered_map<int, NewsArticle>& news,
    vector<int>& ids,
    unordered_map<string, vector<int>>& categorys) {

    /*
      Function: postNewsArticle

      Description:
          Adds a new news article to the system.
          The news article is stored in a map called news.

      Parameters:
          id (int) - The ID of the news article as the key.
          category_ (string) - The category of the news article.
          title (string) - The title of the news article.
          author (string) - The author of the news article.
          content (string) - The content of the news article.
          date (string) - The date of the news article.

      Returns:
          void
    */
    
    news[idcounter] = { idcounter ,category_, title, author, description , date, {0.0}, {{" ", " "}}};

    categorys[category_].push_back(idcounter);

    ids.push_back(idcounter++);
}

void Admin::updateNewsArticle(
    int id,
    string category_,
    string newtitle,
    string newauthor,
    string newdescription,
    string newDate,
    unordered_map<int, NewsArticle>& news,
    vector<int>& ids,
    unordered_map<string, vector<int>>& categorys) {

    /*
     Function: updateNewsArticle

     Description:
         Updates the news article with the given ID in the system.
         If any of these fields are not being updated, the string "skip" should be passed in as the corresponding argument.

     Parameters:
         id (int) - The ID of the news article to be updated.
         category_ (string) - The new category of the news article.
         title (string) - The current title of the news article.
         newtitle (string) - The new title of the news article, or "skip" if the title is not being updated.
         newauthor (string) - The new author of the news article, or "skip" if the author is not being updated.
         newContent (string) - The new content of the news article, or "skip" if the content is not being updated.
         newDate (string) - The new date of the news article, or "skip" if the date is not being updated.

     Returns:
         void
   */

    NewsArticle tempNews = news[id];

    if (newtitle != "skip") {
        tempNews.title = newtitle;
    }
    if (newauthor != "skip") {
        tempNews.author = newauthor;
    }
    if (newdescription != "skip") {
        tempNews.description = newdescription;
    }
    if (newDate != "skip") {
        tempNews.date = newDate;
    }
    if (category_ != "skip") {

        remove( categorys[tempNews.category].begin(),
                categorys[tempNews.category].end(),
                id);

        tempNews.category = category_;
        categorys[tempNews.category].push_back(id);
    }

    news[id] = tempNews;
}

void Admin::addCategory(
    string name,
    unordered_map<string, vector<int>>& categorys) {

    /*
     Function: addCategory

     Description:
        This function adds a new category to the admin's list of categories.
        The category of the news article is also stored in a map called category,
         which maps each category to a vector of news article IDs.

     Params:
       name (string): The name of the new category.

     Return:
       void.
   */

    categorys[name] = {};
}

bool Admin::checkID(int id, vector<int> ids) {

    vector<int>::iterator itr;

    itr = find(ids.begin(), ids.end(), id);

    return (itr != ids.end());
}

void Admin::addAdminAcc(unordered_map<string, userData>& users)
{
    cout << "\nRegester as Admin Account.\n";
    string name, pass, back;

    while (1)
    {
        // get user name, password
        cout << "\n user name: "; cin >> name;
        cout << " password : "; cin >> pass;

        // some chek on username like 
        // (user name is used, or is empty or not, min length is 3)
        if (users[name].username.empty() &&
            name != " " &&
            name.length() > 2)
        {

            // adding new user ot <users>
            users[name] = { name, pass, "admin", {0}, {""} };
            cout << "Admin account added, done.\n\n";
            break;
        }

        cout << "\n User name is used or invalid, try another one.\n";
        cout << " if you dont add anthing enter (y / any letter for try again) > ";
        cin >> back;
        if (back == "y") {
            cout << "\n";
            break;
        }
    }
}
