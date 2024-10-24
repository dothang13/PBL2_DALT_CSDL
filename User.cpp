#include "User.h"
using namespace std;

User::User(const string& id, const string& username, const string& password)
    :userId(id), username(username), password(password){

}

string User::getUserId() const{
    return this->userId;
}

string User::getUsername() const{
    return this->username;
}
void User::setUsername(const string& username){
    this->username = username;
}

string User::getPassword() const{
    return this->password;
}
void User::setPassword(const string& password){
    this->password = password;
}

bool User::validPass(const string& pass) const{
    if (pass.length() < 8) return true;
    else return false;
}

User::~User(){

}
