#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20
#define MAX_WEBSITE_LENGTH 50
#define MAX_PASSWORD_GEN_LENGTH 17


void printBoxTop(int width) {
    printf("\033[1;36m");  // Set color to cyan
    printf("+");
    for (int i = 0; i < width - 2; i++) {
        printf("-");
    }
    printf("+\n");
    printf("\033[0m");  // Reset color
}

void printBoxBottom(int width) {
    printf("\033[1;36m");  // Set color to cyan
    printf("+");

    for (int i = 0; i < width - 2; i++) {
        printf("-");
    }
    printf("+\n");
    printf("\033[0m");  // Reset color
}

void printBoxRow(const char* content, int width) {
    printf("\033[1;36m");  // Set color to cyan
    printf("|");
    int contentLength = strlen(content);
    int padding = (width - 2 - contentLength) / 2;
    int remainingPadding = (width - 2 - contentLength) % 2;

    for (int i = 0; i < padding; i++) {
        printf(" ");
    }
    printf("%s", content);
    for (int i = 0; i < padding + remainingPadding; i++) {
        printf(" ");
    }
    printf("|\n");
    printf("\033[0m");  // Reset color
}


void printMenu() {
    printf("\n");
    int width = 40;

   
    printf("\033[1;34m");  // Set color to blue
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Generate password\n");
    printf("4. Exit\n");
    printf("\033[0m");  // Reset color
}


unsigned int hashWord(const char* word) {
    unsigned int hash = 0;

    // Simple hash function to calculate a unique hash value for the word
    for (size_t i = 0; i < strlen(word); i++) {
        hash = hash * 31 + word[i];
    }
    return hash;
}

void generatepassword_gen(const char* word, char* password_gen) {
    unsigned int hash = hashWord(word);

    // Seed the random number generator with the hash value
    srand(hash);

    // Generate a random password_gen by replacing characters in the word
    for (size_t i = 0; i < MAX_PASSWORD_GEN_LENGTH - 1; i++) {
        password_gen[i] = rand() % 94 + 33;  // ASCII range: 33-126
    }

    // Null-terminate the password_gen string
    password_gen[MAX_PASSWORD_GEN_LENGTH - 1] = '\0';
}

typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    char website[MAX_WEBSITE_LENGTH];
} User;

void storeCredentials(User* user, const char* website, const char* username, const char* password) {
    strncpy(user->website, website, MAX_WEBSITE_LENGTH - 1);
    strncpy(user->username, username, MAX_USERNAME_LENGTH - 1);
    strncpy(user->password, password, MAX_PASSWORD_LENGTH - 1);
    user->website[MAX_WEBSITE_LENGTH - 1] = '\0';
    user->username[MAX_USERNAME_LENGTH - 1] = '\0';
    user->password[MAX_PASSWORD_LENGTH - 1] = '\0';
}

void saveUserToFile(const User* user) {
    FILE* file = fopen("users.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s\n", user->website, user->username, user->password);
    fclose(file);
}

int isUsernameTaken(const char* username) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[MAX_USERNAME_LENGTH];
        sscanf(line, ",%[^,]", storedUsername);

        if (strcmp(storedUsername, username) == 0) {
            fclose(file);
            return 1;  // Username already taken
        }
    }

    fclose(file);
    return 0;  // Username available
}

void registerUser() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
                  system("cls");
      printBoxTop(40);
           printBoxRow("PASSWORD MANAGER", 40);
            printBoxBottom(40);

    printf("\n\033[1;33m");  // Set color to yellow
    printf("Enter a username: ");
    printf("\033[0m");      // Reset color
    scanf("%s", username);

    // Check if username is already taken
    if (isUsernameTaken(username)) {
        system("cls");
         printBoxTop(40);
    printBoxRow("PASSWORD MANAGER", 40);
    printBoxBottom(40);
        
                    printf("\n\033[1;31m");  // Set color to red
                printf("Username already taken. Please choose a different username.\n");
        printf("\033[0m");  // Reset color
        return;
    }

    printf("\033[1;33m");  // Set color to yellow
    printf("Enter a password: ");
        printf("\033[0m");  // Reset color

    scanf("%s", password);

    // Create a new user object
    User newUser;
    storeCredentials(&newUser, "", username, password);
    saveUserToFile(&newUser);

    system("cls");
     printBoxTop(40);
    printBoxRow("PASSWORD MANAGER", 40);
    printBoxBottom(40);
        printf("\n\033[1;32m");  // Set color to green

    printf("Registration successful. You can now log in with your username and password.\n");
    printf("\033[0m");  // Reset color
}

int authenticateUser(const char* username, const char* password) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 0;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[MAX_USERNAME_LENGTH];
        char storedPassword[MAX_PASSWORD_LENGTH];
        sscanf(line, ",%[^,],%s", storedUsername, storedPassword);

        if (strcmp(storedUsername, username) == 0 && strcmp(storedPassword, password) == 0) {
            fclose(file);
            return 1;  // Authentication successful
        }
    }

    fclose(file);
    return 0;  // Authentication failed
}

void addCredential(const char* username) {
    char website[MAX_WEBSITE_LENGTH];
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];
    
     printBoxTop(40);
    printBoxRow("PASSWORD MANAGER", 40);
    printBoxBottom(40);

    printf("\n\033[1;33m");  // Set color to yellow
    printf("Enter website: ");
        printf("\033[0m");  // Reset color

    scanf("%s", website);
        printf("\n\033[1;33m");  // Set color to yellow
        strcpy(storedUsername,username);

            printf("\n\033[1;33m");  // Set color to yellow
      printf("Enter password: ");
                  printf("\033[0m");  // Reset color


    scanf("%s", storedPassword);
    printf("\033[0m");  // Reset color

    User newUser;
    storeCredentials(&newUser, website, storedUsername, storedPassword);
    saveUserToFile(&newUser);
                 system("cls");
                    printBoxTop(40);
           printBoxRow("PASSWORD MANAGER", 40);
            printBoxBottom(40);


    printf("\n\033[1;32m");  // Set color to green
    printf("Credential added successfully.\n");
    printf("\033[0m");  // Reset color
}

/*void addCredential(const char* username) { 
    char website[MAX_WEBSITE_LENGTH];
    char storedUsername[MAX_USERNAME_LENGTH];
    char storedPassword[MAX_PASSWORD_LENGTH];

    printf("Enter website: ");
    scanf("%s", website);

    strcpy(storedUsername,username);

    printf("Enter password: ");
    scanf("%s", storedPassword);

    User newUser;
    storeCredentials(&newUser, website, storedUsername, storedPassword);
    saveUserToFile(&newUser);

    printf("Credential added successfully.\n");
}*/

/*void showCredentials(const char* username) {
    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n\033[1;35m");  // Set color to magenta
    printf("Credentials for user: %s\n", username);
    printf("\033[0m");  // Reset color

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[MAX_USERNAME_LENGTH];
        char storedPassword[MAX_PASSWORD_LENGTH];
        char website[MAX_WEBSITE_LENGTH];
        sscanf(line, "%[^,],%[^,],%s", website, storedUsername, storedPassword);

        if (strcmp(storedUsername, username) == 0) {
            printf("Website: %s\n", website);
            printf("Username: %s\n", storedUsername);
            printf("Password: %s\n\n", storedPassword);
        }
    }

    fclose(file);
}*/

void showCredentials(const char* username) {
        system("cls");
     printBoxTop(40);
    printBoxRow("PASSWORD MANAGER", 40);
    printBoxBottom(40);


    FILE* file = fopen("users.txt", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
        printf("\n\033[1;35m");  // Set color to magenta
        printf("Credentials for user: %s\n", username);
         printf("\033[0m");  // Reset color

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char storedUsername[MAX_USERNAME_LENGTH];
        char storedPassword[MAX_PASSWORD_LENGTH];
        char storedWebsite[MAX_WEBSITE_LENGTH];
        sscanf(line, "%[^,],%[^,],%s", storedWebsite, storedUsername, storedPassword);

        if (strcmp(storedUsername, username) == 0) {
                printf("\n\033[1;33m");  // Set color to yellow
            printf("Website:");
                     printf("\033[0m");  // Reset color
            printf("%s",storedWebsite);
            //printf("Username: %s\n", storedUsername);
                printf("\n\033[1;33m");  // Set color to yellow
                printf("Password:");
               printf("\033[0m");  // Reset color
               printf("%s\n",storedPassword);
            found = 1;
        }
    }
    if (found != 1) {
                            printf("\n\033[1;31m");  // Set color to red
        printf("No credentials found for the user: %s\n", username);
                       printf("\033[0m");  // Reset color
    }
    fclose(file);
}



int main() {
    int choice;
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
     char word[MAX_PASSWORD_GEN_LENGTH];
    char password_gen[MAX_PASSWORD_GEN_LENGTH];
     printBoxTop(40);
    printBoxRow("PASSWORD MANAGER", 40);
    printBoxBottom(40);


    do {
        printMenu();
        printf("\033[35m");
        printf("Enter your choice: ");
         printf("\033[0m");  // Reset color

        scanf("%d", &choice);

        switch (choice) {
            case 1:
               
                registerUser();
                break;
            case 2:
             system("cls");
              printBoxTop(40);
           printBoxRow("PASSWORD MANAGER", 40);
            printBoxBottom(40);
                printf("\n\033[1;33m");  // Set color to yellow
                printf("Enter your username: ");
             printf("\033[0m");  // Reset color

                scanf("%s", username);
             printf("\n\033[1;33m");  // Set color to yellow
               printf("Enter your password: ");
                               printf("\033[0m");  // Reset color

                scanf("%s", password);
                printf("\033[0m");  // Reset color
                
                

                if (authenticateUser(username, password)) {
                  system("cls");
                    printBoxTop(40);
                  printBoxRow("PASSWORD MANAGER", 40);
                    printBoxBottom(40);
                                        printf("\n\033[1;32m");  // Set color to green

                  
                    printf("Authentication successful.");
                      printf("\033[0m");  // Reset color
                    printf("\033[35m");

                    printf("Welcome, %s!\n", username);
                    printf("\033[0m");  // Reset color

                    int option;
                    do {
                        printf("\n\033[1;34m");  // Set color to blue
                        printf("1. Add credential\n");
                        printf("2. Show credentials\n");
                        printf("3. Logout\n");
                        printf("\033[0m");  // Reset color
                         printf("\033[35m");

                        printf("Enter your choice: ");
                        printf("\033[0m");  // Reset color


                        scanf("%d", &option);
                      system("cls");


                        switch (option) {
                            case 1:
                                addCredential(username);
                                break;
                            case 2:
                                showCredentials(username);
                                break;
                            case 3:
                         printBoxTop(40);
                  printBoxRow("PASSWORD MANAGER", 40);
                    printBoxBottom(40);
                                printf("\n\033[1;32m");  // Set color to green
                                printf("Logged out.\n");
                                printf("\033[0m");  // Reset color
                                break;
                            default:
                                printf("\n\033[1;31m");  // Set color to red
                         printBoxTop(40);
                       printBoxRow("PASSWORD MANAGER", 40);
                        printBoxBottom(40);

                                printf("Invalid choice. Please try again.\n");
                                printf("\033[0m");  // Reset color
                                break;
                        }
                    } while (option != 3);
                } else {
                    
                    system("cls");
                                    
        printBoxTop(40);
        printBoxRow("PASSWORD MANAGER", 40);
        printBoxBottom(40);
        printf("\n\033[1;31m");  // Set color to red
                    printf("Authentication failed. Please try again.\n");
                    printf("\033[0m");  // Reset color
                }
                break;
                  case 3:
                  system("cls");
                          printBoxTop(40);
                    printBoxRow("PASSWORD MANAGER", 40);
                  printBoxBottom(40);
                  printf("\033[33m");
                printf("Enter a word: ");
                printf("\033[0m");
                scanf("%s", word);

                generatepassword_gen(word, password_gen);
                                  printf("\033[33m");

                printf("Generated password: ");
                                printf("\033[0m");

                printf("%s\n", password_gen);


                break;

            case 4:
             system("cls");
                printf("\n\033[1;32m");  // Set color to green
                printf("Exiting.\n");
                printf("\033[0m");  // Reset color
                break;
                
            default:
                   system("cls");
                   printBoxTop(40);
                    printBoxRow("PASSWORD MANAGER", 40);
                  printBoxBottom(40);
                printf("\n\033[1;31m");  // Set color to red
                printf("Invalid choice. Please try again.\n");
                printf("\033[0m");  // Reset color
                break;
        }
    } while (choice != 4);

    return 0;
}