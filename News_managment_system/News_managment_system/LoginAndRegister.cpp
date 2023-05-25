#include "LoginAndRegister.h"

#include "Admin.h"
#include "User.h"


LoginAndRegister::LoginAndRegister() {
    /*
       loginAndRgster : Main login and Regestr fram to make user choise optian to take.

       Param  :
           users (unordered_map<string, vector<string> >) : useful for <login> and <rgstsUser>.

       Return :
           data (vector<string>) -> {name, role}: to make main frame know with who deal.
   */


    loadAndStoreFiles tool;

    news = tool.news;
    users = tool.users;
    ids = tool.ids;

    string op;
    vector<string> data;

    string prompt = "\nHello Dear.\n\
                    \rchoise optine to cont :\n\
                     \r 1. Login.\n\
                     \r 2. Rigester.\n\
                     \r 3. Exit.\n\
                     \r > ";

    while (1) {

        cout << prompt;
        cin >> op;

        if (op == "1") data = login();
        else if (op == "2") data = regsiter();
        else if (op == "3") break;

        // this line for development stage.
        else if (op == "4") tool.printUsers(users);

        else cout << "Wrong Option, try again.\n\n";

        if (!data.empty()) {

            if (data[1] == "user") {
                User user(data[0], users, news, ids, tool.categorys, tool);
            }
            else {
                Admin admin(data[0], users,news, ids, tool.categorys, tool);
            };

            data = {};
        };
    }

    
    tool.saveAndClose(users, news);
}

vector<string> LoginAndRegister::login() {

    /*
        Login : to make user get into our program
                with spasefic role if he is regestred before.

        Param :
            users (unordered_map<string, vector<string> > users) : to know if username in it or not.

        Return:
            data (vector<string>) : that holds {name, role}.

    */

    cout << "\nLogin\n";
    string name, pass, rgst;

    userData data;

    while (1)
    {
        // get name, password from input user.
        cout << " user name: "; cin >> name;
        cout << " password : "; cin >> pass;

        // here we try to get user data from <users> map by his name.
        data = users[name];

        // in this case <data> = {}, means this user is not in our database.  
        // so i asked the user to get back to the menue to make acc or try again. 
        if (data.username.empty()) {

            cout << "\n User name not found,\n you want back to"
                << "menue to regiter ? \n(y / any letter for try again) : ";
            cin >> rgst;
            if (rgst == "y") return {};
            cout << endl;
        }
        // in this case password is wrong.
        else if (data.pass != pass) cout << "\n Wrong Password Please Try again\n\n";

        // something else so user logend successfully.
        else return { name, data.role };
    }
}

vector<string> LoginAndRegister::regsiter() {

    /*
        Register : add user to database file.

        Param :
            users (unordered_map<string, vector<string> >) : to add to them, but
                                                             note it is passing by ref to appears
                                                             the changs in out of this funtion.

    */

    cout << "\nRegester\n";
    string name, pass, back;

    while (1)
    {
        // get user name, password
        cout << " user name: "; cin >> name;
        cout << " password : "; cin >> pass;

        // some chek on username like 
        // (user name is used, or is empty or not, min length is 3)
        if (users[name].username.empty() &&
            name != " " &&
            name.length() > 2)
        {

            // adding new user ot <users>
            users[name] = { name, pass, "user", {0}, {""} };

            // to make main know the user's name, role.
            return { name, "user"};
        }

        cout << "\n User name is used or invalid, try another one.\n";
        cout << " if you want back to menue\n\
              \r (y / any letter for try again) : ";
        cin >> back;

        // to back to menue.
        if (back == "y") return {};
        cout << "\n";
    }

};