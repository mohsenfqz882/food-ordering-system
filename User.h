#pragma once

#include <string>

using namespace std;

class User {
protected:
    int id;
    string username;
    string password;

public:
    // Constructors
    User();

    User(int id,
         const string& username,
         const string& password);

    virtual ~User() = default;

    // Getters
    int getId() const;
    string getUsername() const;
    string getPassword() const;

    // Setters
    void setUsername(const string& username);
    void setPassword(const string& password);
};

// =======================
// Implementations
// =======================

inline User::User()
    : id(0), username(""), password("") {}

inline User::User(int id,
                  const string& username,
                  const string& password)
    : id(id),
      username(username),
      password(password) {}

inline int User::getId() const {
    return id;
}

inline string User::getUsername() const {
    return username;
}

inline string User::getPassword() const {
    return password;
}

inline void User::setUsername(const string& username) {
    this->username = username;
}

inline void User::setPassword(const string& password) {
    this->password = password;
}