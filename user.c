#include <stdlib.h>
#include <assert.h>
#include "utilities.h"
#include "mtmflix.h"
#include "user.h"

struct user_t {
	int age;
	Set fav_series; //set of names
	Set friends; //set of names
};

//creates a user instance given user's age
//it will be used as a value in a key-value pair in a map of users
User userCreate(int age) {
	//age limits are already checked in the calling function
	assert(age >= MTM_MIN_AGE);
	assert(age <= MTM_MAX_AGE);
	User user = malloc(sizeof(*user));
	if (user == NULL) {
		return NULL;
	}
	user->age = age;
	user->fav_series = setCreate((copySetElements)copyString, 
		(freeSetElements)freeString, (compareSetElements)compareStrings);
	user->friends = setCreate((copySetElements)copyString, 
		(freeSetElements)freeString, (compareSetElements)compareStrings);
	return user;
}

//creates a copy of a user instance, returns a new user
User userCopy (User user) {
	if (user == NULL) {
		return NULL;
	}
	User new_user = malloc(sizeof(*new_user));
	if (new_user == NULL) {
		return NULL;
	}
	new_user->age = user->age;
	new_user->fav_series = setCopy(user->fav_series);
	new_user->friends = setCopy(user->friends);
	return new_user;
}

//deletes a user
void userFree(User user) {
	setDestroy(user->fav_series);
	user->fav_series = NULL;
	setDestroy(user->friends);
	user->friends = NULL;
	free(user);
	user = NULL;
}

//given a name of a series and a user, 
//adds the series to the list of the user's favorite series
MtmFlixResult userAddFavSeries(User user, const char* series_name) {
	//we check those arguments before passing them to the function
	assert(user != NULL && series_name != NULL);
	switch (setAdd(user->fav_series, (SetElement)series_name)) {
		case SET_SUCCESS : return MTMFLIX_SUCCESS;
		case SET_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY;
		case SET_ITEM_ALREADY_EXISTS : return MTMFLIX_SUCCESS;
		case SET_NULL_ARGUMENT : return MTMFLIX_NULL_ARGUMENT;
		default: return MTMFLIX_NULL_ARGUMENT;
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;
}

//given a name of a series and a user, 
//removes the series from the list of the user's favorite series
MtmFlixResult userDeleteFavSeries(User user, const char* series_name) {
	//we check those arguments before passing them to the function
	assert(user != NULL && series_name != NULL);
	switch (setRemove(user->fav_series, (SetElement)series_name)) {
		case SET_NULL_ARGUMENT : return MTMFLIX_NULL_ARGUMENT;
		case SET_SUCCESS: return MTMFLIX_SUCCESS;
		default: return MTMFLIX_NULL_ARGUMENT;
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;
}

//given a user instance (user1), and a name of another user
//adds the second user to the first user's friend list
MtmFlixResult userAddFriend(User user1, const char* username2) {
	//we check those arguments before passing them to the function
	assert(user1 != NULL && username2 != NULL);
	switch (setAdd(user1->friends, (SetElement)username2)) {
		case SET_SUCCESS : return MTMFLIX_SUCCESS;
		case SET_NULL_ARGUMENT : return MTMFLIX_NULL_ARGUMENT;
		case SET_OUT_OF_MEMORY : return MTMFLIX_OUT_OF_MEMORY;
		case SET_ITEM_ALREADY_EXISTS : return MTMFLIX_SUCCESS;
		default: return MTMFLIX_NULL_ARGUMENT;
	}
	assert(false);
	return MTMFLIX_NULL_ARGUMENT;
}

//given a user instance (user1), and a name of another user,
//deletes the second user from the first user's friend list
MtmFlixResult userRemoveFriend(User user1, const char* username2) {
	//we check those arguments before passing them to the function
	assert(user1 != NULL && username2 != NULL);
	setRemove(user1->friends, (SetElement)username2);
	return MTMFLIX_SUCCESS;
}

//given a user instance, returns the user's favorite series
//returns NULL when given a NULL argument
Set userGetFavSeries(User user){
    if(user==NULL){
        return NULL;
    }
    return user->fav_series;
}

//given a user instance, returns the user's age
//returns NULL when given a NULL argument
int userGetAge(User user){
    if(user==NULL){
        return 0;
    }
    return user->age;
}

//given a user instance, returns the user's friends
//returns NULL when given a NULL argument
Set userGetFriends(User user){
    if(user==NULL){
        return NULL;
    }
    return user->friends;
}
