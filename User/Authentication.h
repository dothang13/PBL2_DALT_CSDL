#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "Usermanagement.h"

bool registerUser(UserManagement& userManager, const string userType = "Customer");
User* loginUser(UserManagement& userManager);

#endif