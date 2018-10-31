#ifndef USER_H_
#define USER_H_

#include "set.h"
#include "series.h"

typedef struct user_t* User;

User userCreate(int age);
User userCopy (User user);
void userFree(User user);

MtmFlixResult userAddFavSeries (User user, const char* series_name);
MtmFlixResult userAddFriend(User user1, const char* username2);
MtmFlixResult userRemoveFriend(User user1, const char* username2);
MtmFlixResult userAddFavSeries(User user, const char* series_name);
MtmFlixResult userDeleteFavSeries(User user, const char* series_name);
MtmFlixResult userAddFavSeries (User user, const char* series_name);

Set userGetFriends(User user);
int userGetAge(User user);
Set userGetFavSeries(User user);

#endif /*USER_H_*/
