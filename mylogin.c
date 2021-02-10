/*
 * Shows user info from local pwfile.
 *  
 * Usage: userinfo username
 */

#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pwdblib.h" /* include header declarations for pwdblib.c */
#include <crypt.h>

/* Define some constants. */
#define USERNAME_SIZE (32)
#define NOUSER (-1)


int print_info(const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  if (p != NULL) {
    printf("Name: %s\n", p->pw_name);
    printf("Passwd: %s\n", p->pw_passwd);
    printf("Uid: %u\n", p->pw_uid);
    printf("Gid: %u\n", p->pw_gid);
    printf("Real name: %s\n", p->pw_gecos);
    printf("Home dir: %s\n",p->pw_dir);
    printf("Shell: %s\n", p->pw_shell);
	return 0;
  } else {
    return NOUSER;
  }
}

void read_username(char *username)
{
  printf("login: ");
  fgets(username, USERNAME_SIZE, stdin);

  /* remove the newline included by getline() */
  username[strlen(username) - 1] = '\0';
}

void read_password(char *password)
{
  password = getpass("password:");

}



int checkPassword(const char *password, const char *username)
{
  struct pwdb_passwd *p = pwdb_getpwnam(username);
  char *dbPass = p -> pw_passwd;

  //const char *typedPass = crypt(password, "Pv");

  return strcmp(password, dbPass);
  
}

int main(int argc, char **argv)
{
  
  
  while(1){

    char username[USERNAME_SIZE];
    char *password;
  

    read_username(username);

    print_info(username);

    //read_password(password);
    password = getpass("password: ");

    if(checkPassword(password, username) == 0){
      break;
    }
    
    printf("Unknown user or incorrect password \n");

  }

  printf("User authenticated successfully \n");
 

  
}
  

  
