#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>

int counter = 1;

//Trie Data Structure
struct Data{
    bool end;
    char description[256];
    Data* next[52];
    Data* prev;
};

struct Trie{
    struct Data* root;
};

Data* createData(){
    Data* newData = (Data*)malloc(sizeof(Data));
    newData->end = false;
    newData->prev = NULL;
    for(int i=0; i<52; i++){
        newData->next[i] = NULL;
    }
    
    return newData;
}

int findIndex(char a){
    if(a >= 'A' && a <= 'Z')
        return a - 'A';
    if(a >= 'a' && a <= 'z')
        return a - 'a' + 26;
    return -1;
}

void insertWord(Trie* trie, char *word, char *description){
    Data* curr = trie->root;
    for(int i=0; i<strlen(word); i++){
        int index = findIndex(word[i]);
        if(index == -1) continue;
        if(curr->next[index] == NULL)
            curr->next[index] = createData();
        curr = curr->next[index];
    }
    strcpy(curr->description, description);
    curr->end = true;
    system("cls");
    printf("Word %s inputed in the dictionary!\n", word);
    puts("Enter to continue...");
    getch();
}

void searcSinglehWord(Trie* trie, char *word){
    Data* curr = trie->root;
    for(int i=0; i<strlen(word); i++){
        int index = findIndex(word[i]);
        if(curr->next[index] == NULL){
            system("cls");
            printf("There is no word %s in the dictionary!\n", word);
            puts("Enter to continue...");
            getch();
            return;
        }
        curr = curr->next[index];
    }
    if(curr->end){
        system("cls");
        printf("Slang word: %s\nDescription: %s\n", word, curr->description);
        puts("Enter to continue...");
        getch();
        return;
    }else {
        system("cls");
        printf("There is no word %s in the dictionary!\n", word);
        puts("Enter to continue...");
        getch();
        return;
    }
}

void printWord(Data* curr, char *word, int depth){
    if(!curr) return;
    if(curr->end){
        printf("|%d. %s\t\t\t\t|\n", counter,word);
    }
    for (int i = 0; i < 52; i++) {
        if (curr->next[i] == NULL) continue;
        if (i < 26) {
            word[depth] = 'A' + i;
        } else {
            word[depth] = 'a' + (i - 26);
        }
        printWord(curr->next[i], word, depth + 1);
    }
}

void searchRelated(Trie* trie, char *prefix) {
    struct Data* curr = trie->root;
    for (int i = 0; i < strlen(prefix); i++) {
        int index = findIndex(prefix[i]);
        if (index == -1) continue;
        if (curr->next[index] == NULL) {
            system("cls");
            printf("No words found with the prefix '%s'\n", prefix);
            puts("Enter to continue...");
            getch();
            return;
        }
        curr = curr->next[index];
    }
    system("cls");
    printf("Slang words starting with prefix '%s':\n", prefix);
    char buffer[256];
    strcpy(buffer, prefix);
    printWord(curr, buffer, strlen(prefix));
    puts("Enter to continue...");
    getch();
}

//Validation
bool isNoSpaces(char word[]){
    for(int i=0; i<strlen(word); i++){
        if(word[i] == ' ') return false;
    }
    return true;
}

bool isLengthValid(char word[]){
    return strlen(word) > 1;
}

bool isDescriptionValid(char word[]){
    int count = 0;
    for(int i=0; i<strlen(word); i++){
        if(word[i] == ' ') count++;
    }
    return count > 0;
}

//Menu
void inputNewSlang(Trie* trie){
    char word[100];
    char description[100];
    system("cls");
    printf("    ____                     __     \n");
    printf("   /  _/___  ________  _____/ /_    \n");
    printf("   / // __ \\/ ___/ _ \\/ ___/ __/    \n");
    printf(" _/ // / / (__  )  __/ /  / /_      \n");
    printf("/___/_/ /_/____/\\___/_/   \\__/      \n");
    printf("                                    \n");
    do{
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%s", word);
        getchar();
    }while(!isNoSpaces(word) && !isLengthValid(word));

    do{
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf("%[^\n]", description);
        getchar();
    }while(!isDescriptionValid(description));
    insertWord(trie, word, description);
}

void searchSlangWord(Trie* trie){
    char word[100];
    system("cls");
    printf("   _____                      __       \n");
    printf("  / ___/___  ____ ___________/ /_      \n");
    printf("  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\     \n");
    printf(" ___/ /  __/ /_/ / /  / /__/ / / /     \n");
    printf("/____/\\___/\\__,_/_/   \\___/_/ /_/      \n");
    printf("                                       \n");
    do{
        printf("Input a slang word to be searched[Must be more than 1 characters and contains no space]: ");
        scanf("%s", word);
        getchar();
    }while(!isNoSpaces(word) && !isLengthValid(word));
    searcSinglehWord(trie, word);
}

void searchRelatedWord(Trie* trie) {
    char prefix[100];
    system("cls");
    printf("   _____                      __       ____       __      __           __\n");
    printf("  / ___/___  ____ ___________/ /_     / __ \\___  / /___ _/ /____  ____/ /\n");
    printf("  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\   / /_/ / _ \\/ / __ `/ __/ _ \\/ __  / \n");
    printf(" ___/ /  __/ /_/ / /  / /__/ / / /  / _, _/  __/ / /_/ / /_/  __/ /_/ /  \n");
    printf("/____/\\___/\\__,_/_/   \\___/_/ /_/  /_/ |_|\\___/_/\\__,_/\\__/\\___/\\__,_/   \n");
    printf("\n");
    do {
        printf("Input a prefix to be searched [no spaces]: ");
        scanf("%s", prefix);
        getchar();
    } while (!isNoSpaces(prefix));
    searchRelated(trie, prefix);
}

void seeAllWord(Data* curr, char *word, int depth) {
    if (!curr) return;
    
    if (curr->end) {
        word[depth] = '\0'; // Null-terminate the word
        printf("Slang word: %s\t\t\tDescription: %s\n", word, curr->description);
    }
    
    for (int i = 0; i < 52; i++) {
        if (curr->next[i] != NULL) {
            word[depth] = (i < 26) ? ('A' + i) : ('a' + (i - 26));
            seeAllWord(curr->next[i], word, depth + 1);
        }
    }
}

void viewAllWords(Trie* trie) {
    system("cls");
    printf("Viewing all slang words:\n");
    char buffer[256];
    seeAllWord(trie->root, buffer, 0);
    puts("Enter to continue...");
    getch();
}

int main(){
    Trie boogle;
    boogle.root = createData();
    int input = -1;

    do{
        system("cls");
        printf("    ____                    __   \n");
        printf("   / __ )____  ____  ____ _/ /__ \n");
        printf("  / __  / __ \\/ __ \\/ __ `/ / _ \\\n");
        printf(" / /_/ / /_/ / /_/ / /_/ / /  __/\n");
        printf("/_____/\\____/\\____/\\__, /_/\\___/ \n");
        printf("                  /____/         \n");
        printf("\n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf(">> ");
        scanf("%d", &input);
        getchar();
        switch (input){
        case 1:
            inputNewSlang(&boogle);
            break;

        case 2:
            searchSlangWord(&boogle);
            break;

        case 3:
            searchRelatedWord(&boogle);
            break;

        case 4:
            viewAllWords(&boogle);
            break;
        
        case 5:
            system("cls");
            printf("Thank you... Have a nice day :)\n");
            break;
        
        default:
        printf("\nInvalid Input\n");
        break;

        }

    }while(input != 5);

    return 0;
}