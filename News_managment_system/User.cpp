#include "User.h"
#include<vector>
#include "Sorted_LinkedList.h"


User::User(
	string userName,
	unordered_map<string, userData>& users,
	unordered_map<int, NewsArticle>& news, 
	vector<int>& ids,
	unordered_map<string, vector<int>>& categorys,

	loadAndStoreFiles tool)
{
	usr = users[userName];
	
	string prompt= " \nhi, " + usr.username + "\n"\
					"\rChoose an option:\n" \
					 "\r 1. Display news by latest.\n" \
					 "\r 2. Display news by special category.\n" \
					 "\r 3. Display news by Higher rating.\n" \
					 "\r 4. Add Rate For a news.\n" \
					 "\r 5. Add comment for a news.\n" \
					 "\r 6. Spam News.\n" \
		             "\r 7. Display by prefrences .\n" \
					 "\r 8. Exit.\n" \
					 "\r Enter your choice: ";

	int choice;
	do {
		
		cout << prompt;
		cin >> choice;

		switch (choice) {
		// Display news by latest.
		case 1: {
			display_latest_news(news, ids, tool);
			break;
		}

		// Display news by special category.
		case 2: {
			string input_category;

			while (true)
			{
				cout << "enter the category : "; cin >> input_category;

				if (tool.categorys[input_category].empty())
					cout << "invalid category, try agin.\n";
				else break;

			}

			display_categories_news(input_category, news, tool);
			break;
		}
	
		// Display news by Higher rating.
		case 3: {
			display_rating_news(news, tool);
			break;
		}
		
		// Add Rate For a news.
		case 4: {
			int id;
			float rate;

			while (true) {
				cout << "enter the id : "; cin >> id;

				if (!contain(ids, id)) {
					cout << "invalid id try agin\n";
				}
				else break;
			}

			cout << "enter the rate for news id " << id << " : "; cin >> rate;
			rate_news(id, rate, news, ids, categorys,tool);
			break;
		}

		// Add comment for a news.
		case 5: {
			int id;
			string comm = "";

			while (true) {
				cout << "enter the id : "; cin >> id;

				if (!contain(ids, id)) {
					cout << "invalid id try again\n";
				}
				else break;
			}

			cout << "enter the comment for news " << id << " : ";
			cin.ignore();
			getline(cin, comm);

			add_comment(id, comm, news, tool);
			break;
		}

		case 6: {
			int id;

			while (true)
			{
				cout << "Enter News's Id to spam : "; cin >> id;
				if (!contain(ids, id))
					cout << "invalid ID, try again.\n";
				else break;
			}

			
			if (news[id].spam == 4) {
				tool.removeNewsArticle(id, news, ids, categorys);
			}
			else {
				news[id].spam++;
				usr.spam.push_back(id);
			}

			cout << "done.\n";
			break;
		}
		
		case 7: {
			display_by_preferance(categorys,news,tool);
			break;
		}

		case 8: {
			cout << "ok bye.\n";
			break;
		}

		default: {
			   cout << "Invalid choice. Try again.\n" << endl;
			   break;
			}
		}

	} while (choice!=8);
	 
	users[userName] = usr;
}

void User::display_latest_news(
	unordered_map<int, NewsArticle> news,
	vector<int> ids,
	loadAndStoreFiles tool)
{
	stack<int>temp_stack_ids = tool.getIdsStack(ids);

	//display all the news objects in the stack
	while (!temp_stack_ids.empty()) {

		if (contain(usr.spam, temp_stack_ids.top())) {
			temp_stack_ids.pop();
			continue;
		}
		tool.printNew(news[temp_stack_ids.top()]);
		temp_stack_ids.pop();
	}
}

void User::display_categories_news(
	string cat,
	unordered_map<int, NewsArticle>news,
	loadAndStoreFiles tool)
{
	cout << "\n\nAll News About " << cat << ": \n";

	for (auto id : tool.categorys[cat]) {

		if (contain(usr.spam, id)) continue;
		
		tool.printNew(news[id]);
	}
}


void User::display_rating_news(
	unordered_map<int, NewsArticle>news,
	loadAndStoreFiles tool)
{
	vector<int> soretedIds = tool.getSortedIds_byRate(news);
	for (auto id : soretedIds) {

		if (contain(usr.spam, id)) continue;
		tool.printNew(news[id]);
	}
}


void User::rate_news(
	int id,
	float rating,

	unordered_map<int, NewsArticle>& news,

	vector<int>& ids,
	unordered_map<string, vector<int>>& categorys,

	loadAndStoreFiles tool)
{
	news[id].rates.push_back(rating);
	cout << "rate added successfully." <<  endl;

	if ((news[id].printRate() != "Not Rated") && (news[id].getRate() < 2)) {

			tool.removeNewsArticle(id, news, ids, categorys);
	}
	
	if (rating >= 3) usr.prefrenceCategory.insert(news[id].category);
}


void User::add_comment(
	int id, 
	string comm,
	unordered_map<int, NewsArticle>& news,
	loadAndStoreFiles tool)
{

	news[id].comments.push_back({ usr.username, comm });
	cout << "comment added successfully to the news of id : " << id;
	cout << "\n";
}

bool User::contain(vector<int>ids, int id) {

	vector<int>::iterator itr;

	itr = find(ids.begin(), ids.end(), id);

	return (itr != ids.end());
}

void User::display_by_preferance( unordered_map<string, vector<int>>& categorys
	                           , unordered_map<int, NewsArticle>& news ,loadAndStoreFiles tool )
{

	random_device rd;
	mt19937 g(rd());
	vector<int> randomized_ids;
	
	for (auto cat : usr.prefrenceCategory) {
		for (auto ids : categorys[cat]) {
			randomized_ids.push_back(ids);
		}
	}
	shuffle(randomized_ids.begin(), randomized_ids.end(), g);

	for (auto rand_ids : randomized_ids) {
		tool.printNew(news[rand_ids]);
	}
}