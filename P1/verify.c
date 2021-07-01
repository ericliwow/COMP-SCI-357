// Eric Bocheng Li
// bli392
// Eric Li
// 908 166 7231
// July 1, 1:29 AM

#include <stdio.h>
#include <string.h>

#define USER_NAME_LENGTH 256
#define EMAIL_LENGTH 512
#define PASSWORD_LENGTH 256

void Get_User_Data(char *message, char *username, const int MAX_LENGTH);
int Check_First_Letter(const char firstLet);
int Check_All_Letter(const char username[]);
int Check_Email_Letter(const char email);
int Check_Domain_Name(const char domain);

int main(){
    char username[USER_NAME_LENGTH];
    char email[EMAIL_LENGTH];
    char password_1[PASSWORD_LENGTH];
    char password_2[PASSWORD_LENGTH];

    // ################################################
    // #####  VERIFY USERNAME  ##### 
    // ################################################
    Get_User_Data("Enter username: ", username, USER_NAME_LENGTH);
    // username must begin with letter [A-Z, a-z]

    char firstChar = username[0];

    if (Check_First_Letter(firstChar) == 1) {
        // printf("Is valid.");
        // The character is valid, so nothing should be printed (?)
    } else {
        printf("Invalid username starting character\n");
        return 0;
    }

    // max 32 charcters
    if(strlen(username)-1 > 32) {
        printf("Max 32 charcters\n");
        return 0;
    } else {
        // printf("TEST: Passed max 32 char test case\n");
    }

    // may contain only letters, underscore, or digits [A-Z, a-z, _, 0-9]
    if (Check_All_Letter(username) == 0) {
        printf("Invalid character in username\n");  
        return 0;  
    } else { // Good! And we are done with username cases.
        printf("Username formatting is correct\n");
    }
    
    // ################################################
    // #####  VERIFY EMAIL ADDRESS  ##### 
    // ################################################
    Get_User_Data("Enter email address: ", email, EMAIL_LENGTH);
    // email address have 4 parts in this order
        // name
            // max 32 characters
            // must start with letter
            // may contain [letters or digits]
        // @ symbol
        // domain name
            // max of 64 characters
            // consists of a domain name and subdomains separated by . 
            // each domain or subdomain  must begin with a letter
            // domain and subdomains may contain only [letters, digits]
        // top-level domain 
            // must be [.edu, .com, .net]

    // ********************************************************************
    // Step 1: Find pointers to the first char (email[0]),
    // second (@)
    // third (. of last domain)
    // fourth (null terminal char)

    // Pointer 1: First Char
    // char emailFirstChar = email[0];

    // Pointer 2: @ symbol
    char *atChar = &email[0];

    // The idea of looping through an array comes from Stack Over Flow:
    // Cited from https://stackoverflow.com/a/28032172, author Diizzy
    char *i;
    i = email;

    for (; *i != '\0'; ++i) {
        if (i[0] == 64) {
            // printf("TEST: Found an instance of @ symbol\n");
            atChar = &i[0];
            break;
        }
            // atChar = &email[0];
    }

    // So now atChar should be set as a character array.
    // If there is @, it will be at [0].
    // If it is not @, it will be checked for the @ symbol test.
    // Also this provides benefit to checking [1]
    // about whether the domain is missing.
    
    // Error messages
    // name
    // When first char is the @ domain
    if (email[0] == 64) {
        printf("Name missing\n");  // example @domain.com
        return 0;
    }

    // When name doesn't begin with a letter.
    if (Check_First_Letter(email[0]) == 0) {
        printf("Name must begin with letter\n");
        return 0;
    }

    // When name has more than 32 characters
    // Professor Doescher said you can just do arithematic stuffs with these char.
    // TODO: What happens when the user enters 33 chars of letters without @ symbol?
    // Because this part depends on the atChar position.
    int nameLen = atChar - email;
    if (nameLen > 32 ) {
        printf("Name must have fewer than 32 characters\n");
        return 0;
    }
    
    /* When I tried to iterate email by comparing every char to an @ symbol.
    // printf("TEST: length of name is %d", temp);
    /char *temp = &email[0];
    for (int i = 0; *temp != '@'; ++i) {
        // When there are more than 32 chars.
        if (i > 32) {
            printf("Name must have fewer than 32 characters\n");
            return 0;        
        }
        temp = &email[i+1];
    }*/

    // TODO: Invalid character in name, still needs testing
    // Plan is to iterate through the email's name part and use
    // Check_All_Letters method on every char.

    // The idea of looping through an array comes from Stack Over Flow:
    // Cited from https://stackoverflow.com/a/28032172, author Diizzy
    char *j;
    // int loopjtime = 1;
    j = email;

    for (; j[0] != 64; ++j) {
        if (j[0] == 0 || j[0] == 10 || j[0] == 46) {
            break;
        }

        // printf("TEST: going through, and string is %s", j);
        // printf("TEST: Looking at char %c, at loop %d\n", j[0], loopjtime);
        if (Check_Email_Letter(*j) == 0) {
            //
            printf("Invalid character in name\n");
            return 0;
        }
        // loopjtime++;
    }

    // ********************************************************************
    // @ symbol
    // atChar[0] is should be NULL if not any already somehow. IGNORE THIS!
    if (atChar[0] == 64) {
        // DO nothing, since it is @.
        // printf("TEST: Passed @ symbol test\n");
    } else {
        printf("missing @\n");
        return 0;
    }


    // ********************************************************************
    // domain name
    int moreDot = 0;
    j = atChar;
    for (; *j != 0; ++j) {
        if (j[0] == 46) {
            moreDot++;
        }
    }

    if (moreDot > 1) {
        // pass;
    } else if (atChar[1] == 46) {
        printf("Domain missing\n"); // example mike@.edu
        return 0;
    }

    // We will need to find domain pointer now. Pointer 3.
    // char *lastDomain = &email[0];

    // Plan is to find every . char first, and then determine the following 3 char.
    // If If they fit with com, edu and net then we will set the pointer.
    
    char *lastDot = &email[0]; // Pointer 3;
    char *nullTerm = &email[0]; // Pointer 4

    j = atChar;
    for (; *j != '\0'; ++j) {
        // printf("now j is at: %s", j);
    }
    nullTerm = &j[0];

    // The idea of looping through an array comes from Stack Over Flow:
    // Cited from https://stackoverflow.com/a/28032172, author Diizzy
    char *k;
    k = atChar;

    for (; *k != '\0'; ++k) {
        if (k[0] == 46) { // When we find a dot.
        // printf("TEST: Found case of .\n");
            if (k[1] == 99 && k[2] == 111 && k[3] == 109) { //.com case
                // printf("TEST: . is followed by com\n");
                lastDot = &k[0];
            } else if (k[1] == 110 && k[2] == 101 && k[3] == 116) { //.net case
                // printf("TEST: . is followed by net\n");
                lastDot = &k[0];
            } else if (k[1] == 101 && k[2] == 100 && k[3] == 117) { //.edu case
                lastDot = &k[0];
                // printf("so now we have: %s", lastDot);
            }
        }
    }

    
    // Checking for 64 characters in domain, P3-P2
    int domainLen = lastDot - atChar;
    if ((domainLen-1) > 64) { // For some reason there is an extra bit?
        printf("Maximum of 64 characters in domain\n");   
        return 0;
    }

    k = atChar;
    if (Check_First_Letter(k[1]) == 0) { // This is for the first domain name.
        //printf("TEST: first case\n");
        printf("Domain or subdomain must begin with letter\n");
        return 0;
    }

    for (; k != lastDot; k++) {
        // printf("Current k 0 and 1 are: %c, %c\n", k[0], k[1]);
        if (k[0] == 46 && k[1] == 46) {
            //printf("TEST: Second case\n");
            printf("Domain or subdomain must begin with letter\n");
            return 0;
        } else if (k[0] == 46 && (Check_First_Letter(k[1]) == 0)) {
            if (moreDot == 1 || moreDot == 0) {
                break;
            }
            //printf("TEST: third case\n");
            //printf("Current string is %s\n", k);
            printf("Domain or subdomain must begin with letter\n");
            return 0;
        }
    }

    /*k = atChar;

    for (; *k != '\0'; ++k) { // This is for all the subdomains
        if (k[0] == 46) { // still finding dots.
            if (Check_First_Letter(k[1]) == 0) {
                // printf("TEST: second case\n");
                printf("Domain or subdomain must begin with letter\n");
                return 0;
            }
        }
    }*/

    // k = atChar+1; +1 because atChar is located at @.
    for (k = atChar + 1; k != nullTerm; k++) {
        if (Check_Domain_Name(k[0]) == 0) { // If the character is not letter/number
            printf("Invalid character in domain\n");        
            return 0;
        } 
    } 

    // top level domain
    // nullTerm - 4 will give us a string of edu, com or net.
    char *topLvlDom = nullTerm-5;

    // printf("TEST: top-level domain: %s", topLvlDom);
    if ((topLvlDom[0] == 46 && topLvlDom[1] == 99 && topLvlDom[2] == 111 && topLvlDom[3] == 109) || 
       (topLvlDom[0] == 46 && topLvlDom[1] == 110 && topLvlDom[2] == 101 && topLvlDom[3] == 116) ||
       (topLvlDom[0] == 46 && topLvlDom[1] == 101 && topLvlDom[2] == 100 && topLvlDom[3] == 117)) {
        // Do nothing
    } else{
        printf("Top level domain must be .edu, .com, or .net\n");
        return 0;
    }
    
    printf("Email formatting is correct\n");


    // ################################################
    // #####  VERIFY PASSWORD  ##### 
    // ################################################
    Get_User_Data("Enter password: ", password_1, PASSWORD_LENGTH);

    // May use any character except spaces // example "my password" is invalid
    // passwords must contain at least 8 characters // example "Password" has 8 characters and is valid
    // passwords have at most 16 characters // example "1234567890Abcdef" has 16 characters and is valid 
    // Must contain at least one upper case character [A-Z]
    // Must contain at least one lower case character [a-z]
    // Original Password and the Reentered Password must match

    // Error messages
    k = password_1;
    for (; *k != 0; k++) {
        if (k[0] == 32) {
            printf("Password may not contain spaces\n");
            return 0;
        }
    }


    // I think here, we just do - by the starting pointer and edning pointer.
    k = password_1;
    char *pw1term;
    for (; *k != 0; k++) {
        // do nothing
    }
    pw1term = k;

    int pw1Len = pw1term - password_1 - 1; // -1 because there is one little \0 char
    // printf("TEST: Length of password 1 was: %d\n", pw1Len);
    
    if (pw1Len < 8) {
        printf("Password must have at least 8 characters\n");
        return 0;
    } else if ( pw1Len > 16 ) {
        printf("Password may have at most 16 character\n");
        return 0;
    }

    int hasUpper = 0;
    int hasLower = 0;

    k = password_1;
    // Must contain at least one upper case, so upper case will be 65-90
    for(; *k != 0; k++) {
        if (k[0] > 64 && k[0] < 91) { // I almost missed the capital A!
            // printf("TEST: Password is at char %c, and it is UPPER\n", k[0]);
            hasUpper = 1;
        }
        // printf("TEST: Password is at char %c \n", k[0]);
    }

    if (hasUpper == 0) {
        printf("Password must contain at least one upper case character\n");
        return 0;
    }
    
    k = password_1;
    // Must contain at least one lower case, so it will be  97-122
    for (; *k != 0; k++) {
        if (k[0] > 96 && k[0] < 123) {
            // printf("TEST: Password is at char %c, and it is lower\n", k[0]);
            hasLower = 1;
        }
        // printf("TEST: Password is at char %c\n", k[0]);
    }
    
    if (hasLower == 0) {
        printf("Password must contain at least one lower case character\n");
        return 0;
    }
    
    Get_User_Data("Confirm password: ", password_2, PASSWORD_LENGTH);

    k = password_1;
    j = password_2;

    for (; *k != 0; k++, j++) {
        //printf("TEST: Password 1 is at char %c \n", k[0]);
        //printf("TEST: Password 2 is at char %c \n", j[0]);
        if (k[0] != j[0]) {
            printf("Passwords do not match\n");    
            return 0;
        }
    }

    printf("Passwords match\n");
	return 0;
}

/* Example function from the teaching group. Thanks a lot!!!
 *
 */
void Get_User_Data(char *message, char *data, const int MAX_LENGTH) {
    printf("%s", message);
    fgets(data, MAX_LENGTH, stdin);
    return;
}

/*
 * Takes in the argument's character and checks if it's within the bound 
 * of normal English letters.
 *
 * returns 0 when the letter is invalid (not a normal English character)
 * and 1 when the letter is okay as the beginning letter.
 */
int Check_First_Letter(const char firstLet) {
    // printf("The passed arg is %c", firstLet);
    // First task is to make char into comparable int.

    char lowerEndBound = 122;
    char upperBeginBound = 65;

    // When the letter is not in range of A
    if (firstLet < upperBeginBound) {
        return 0;
    } else if (firstLet > lowerEndBound) { // If bigger than last character z
        return 0;
    }

    // Cannot be 91-96
    if (firstLet < 97 && firstLet > 90) {
        return 0;
    }

    return 1;
}

// may contain only letters, underscore, or digits [A-Z, a-z, _, 0-9]
int Check_All_Letter(const char username[]) {
    for (int i = 0; i < strlen(username)-1; i++) {

        // printf("TEST: Current char is [%c] at [%d]\n", username[i], i);

        if (username[i] == 95 || (username[i] > 47 && username[i] < 58)) {
            continue;
        } else if (Check_First_Letter(username[i]) == 1) {
            continue;
        }

        // printf("TEST: Bad case of char [%c] at [%d]", username[i], i);

        return 0;
    }
    return 1;
}

/*
 * may contain only letters and digits [A-Z, a-z, 0-9]
 *
 * returns 0 when the letter is invalid (not a letter or number)
 * and 1 when the letter is okay 
 */
int Check_Email_Letter(const char email) {
    if (email > 47 && email < 58) {
        // Do nothing
    } else if (Check_First_Letter(email) == 1) {
        // Do nothing
    } else {
        return 0;
    }
    return 1;
}

/*
 * Duplicate (?) of previous methods, but this one handles the case of dot.
 */
int Check_Domain_Name(const char domain) {
    // printf("TEST: domain char is %c\n", domain);
    if (domain == 46 || domain == 10) { // Edge case is . maybe also new line char???
        // Do nothing
    } else if (Check_Email_Letter(domain) == 1) {
        // Do nothing
    } else {
        return 0;
    }
    return 1;
}