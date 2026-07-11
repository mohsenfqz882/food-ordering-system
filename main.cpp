#include <iostream>

#include "DatabaseManager.h"
#include "dao/UserDAO.h"
#include "CustomerMenu.h"

using namespace std;

int main() {

    DatabaseManager db;

    if (!db.open("food.db"))
        return 0;

    db.init();

    UserDAO userDAO(&db);

    while (true) {

        int choice;

        cout << "\n========== Food Ordering System ==========\n";
        cout << "1. Sign Up\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 0)
            break;

        if (choice == 1) {

            string username;
            string password;

            cout << "Username: ";
            cin >> username;

            if (userDAO.usernameExists(username)) {
                cout << "Username already exists.\n";
                continue;
            }

            cout << "Password: ";
            cin >> password;

            User user(0, username, password);

            if (userDAO.addUser(user))
                cout << "Account created successfully.\n";
            else
                cout << "Error creating account.\n";
        }

        else if (choice == 2) {

            string username;
            string password;

            cout << "Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (!userDAO.login(username, password)) {
                cout << "Wrong username or password.\n";
                continue;
            }

            string role = userDAO.getRole(username);

            if (role == "customer") {

                CustomerMenu menu(&db);
                menu.run();

            } else if (role == "manager") {

                cout << "Restaurant Manager section will be implemented later.\n";

            } else if (role == "admin") {

                cout << "Admin section will be implemented later.\n";

            } else {

                cout << "Unknown user role.\n";
            }
        }
    }

    db.close();

    return 0;
}