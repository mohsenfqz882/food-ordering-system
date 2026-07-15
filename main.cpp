#include <iostream>

#include "DatabaseManager.h"
#include "SeedData.h"

#include "dao/UserDAO.h"

#include "CustomerMenu.h"
#include "RestaurantManagerMenu.h"
#include "AdminMenu.h"

using namespace std;

int main() {

    DatabaseManager db;

    if (!db.open("food.db"))
        return 0;

    db.init();

    SeedData::initialize(&db);

    UserDAO userDAO(&db);

    while (true) {

        int roleChoice;

        cout << "\n========== Food Ordering System ==========\n";
        cout << "1. Customer\n";
        cout << "2. Restaurant Manager\n";
        cout << "3. System Admin\n";
        cout << "0. Exit\n";
        cout << "Choice: ";

        cin >> roleChoice;

        if (roleChoice == 0)
            break;

        // ================= CUSTOMER =================

        if (roleChoice == 1) {

            int choice;

            cout << "\n1. Sign Up\n";
            cout << "2. Login\n";
            cout << "Choice: ";

            cin >> choice;

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
                    cout << "Account creation failed.\n";
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

                if (userDAO.getRole(username) != "customer") {

                    cout << "This account is not a customer.\n";
                    continue;
                }

                User user = userDAO.getUser(username);

                CustomerMenu menu(&db, user.getId());
                menu.run();
            }

            else {

                cout << "Invalid choice.\n";
            }
        }

        // ================= MANAGER =================

        else if (roleChoice == 2) {

            string username;
            string password;

            cout << "Manager Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (!userDAO.login(username, password)) {

                cout << "Wrong username or password.\n";
                continue;
            }

            if (userDAO.getRole(username) != "manager") {

                cout << "This account is not a manager.\n";
                continue;
            }

            int restaurantId = userDAO.getRestaurantId(username);

            if (restaurantId == 0) {

                cout << "No restaurant assigned to this manager.\n";
                continue;
            }

            RestaurantManagerMenu menu(&db, restaurantId);
            menu.run();
        }

        // ================= ADMIN =================

        else if (roleChoice == 3) {

            string username;
            string password;

            cout << "Admin Username: ";
            cin >> username;

            cout << "Password: ";
            cin >> password;

            if (!userDAO.login(username, password)) {

                cout << "Wrong username or password.\n";
                continue;
            }

            if (userDAO.getRole(username) != "admin") {

                cout << "This account is not an admin.\n";
                continue;
            }

            AdminMenu menu(&db);
            menu.run();
        }

        else {

            cout << "Invalid choice.\n";
        }
    }

    db.close();

    return 0;
}