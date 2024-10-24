#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include "Usermanagement.h"

bool registerUser(UserManagement& userManager);
User* loginUser(UserManagement& userManager);

#endif