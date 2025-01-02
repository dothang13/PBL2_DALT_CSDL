#include "User.h"
#include "../InterfaceSupport/DisplayOption.h"
#include "../InterfaceSupport/Console.h"
#include "../Management/Valid_Input.h"
#include "Usermanagement.h"

using namespace std;

User::User(const string& id, const string& username, const string& password, const string name, const string phone, int points)
    :userId(id), username(username), password(password), name(name), phone(phone), points(points){

}

int User::getPoints(){
    return this->points;
}

void User::setPoints(int point){
    this->points = point;
}

string User::getId() const{
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

bool User::validUsername(const string& username) {
    if (username.empty() || username.length() < 5 || username.length() > 20)
        return false;

    for (char ch : username) {
        if (!isalnum(ch) && ch != '_')
            return false;
    }
    return true;
}

bool User::validPass(const string& pass){
    if (pass.length() < 8) return false;
    else return true;
}

bool User::validPhone(const string& phone){
    if (phone.length()!= 10) return false;
    else return true;
}

User::~User(){

}

string User::getName() const{
    return this->name;
}
void User::setName(const string& name){
    this->name = name;
}

string User::getPhone() const{
    return this->phone;
}

void User::setPhone(const string& phone){
    this->phone = phone;
}
