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

void insertWord(Trie* trie, char *word, char *description){
    Data* curr = trie->root;
    for(int i=0; i<strlen(word); i++){
        if(curr->next[word[i] - 'A'] == NULL){
            curr->next[word[i] - 'A'] = createData();
            curr->next[word[i] - 'A']->prev;
        }   
        curr = curr->next[word[i] - 'A'];
    }
    curr->end = true;
    strcpy(curr->description, description);
    system("cls");
    printf("Word %s inputed in the dictionary!\n", word);
    puts("Enter to continue...");
    getch();
    return;
}

void searcSinglehWord(Trie* trie, char *word){
    Data* curr = trie->root;
    for(int i=0; i<strlen(word); i++){
        if(curr->next[word[i] - 'A'] == NULL){
            system("cls");
            printf("There is no word %s in the dictionary!\n", word);
            puts("Enter to continue...");
            getch();
            return;
        }
        curr = curr->next[word[i] - 'A'];
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
    for(int i=0; i<52; i++){
        if(curr->next[i]){
            word[depth] = 'A' + i;
            printWord(curr->next[i], word, depth + 1);
        }
    }
}

void searchRelated(Trie* trie, char *prefix){
    Data* curr = trie->root;
    for(int i=0; i<strlen(prefix); i++){
        if(curr->next[prefix[i] - 'A'] == NULL){
            return;
        }
        curr = curr->next[prefix[i] - 'A'];
    }
    printWord(curr, prefix, strlen(prefix));
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
void inputNewSlang(Trie* trie, char *word, char *description){
    system("cls");
    printf("    ____                     __     \n");
    printf("   /  _/___  ________  _____/ /_    \n");
    printf("   / // __ \\/ ___/ _ \\/ ___/ __/    \n");
    printf(" _/ // / / (__  )  __/ /  / /_      \n");
    printf("/___/_/ /_/____/\\___/_/   \\__/      \n");
    printf("                                    \n");
    do{
        printf("Input a new slang word [Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", word);
        getchar();
    }while(!isNoSpaces(word) && !isLengthValid(word));

    do{
        printf("Input a new slang word description [Must be more than 2 words]: ");
        scanf("%[^\n]", description);
        getchar();
    }while(!isDescriptionValid(description));
    insertWord(trie, word, description);
}

void searchSlangWord(Trie* trie, char *word){
    system("cls");
    printf("   _____                      __       \n");
    printf("  / ___/___  ____ ___________/ /_      \n");
    printf("  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\     \n");
    printf(" ___/ /  __/ /_/ / /  / /__/ / / /     \n");
    printf("/____/\\___/\\__,_/_/   \\___/_/ /_/      \n");
    printf("                                       \n");
    do{
        printf("Input a slang word to be searched[Must be more than 1 characters and contains no space]: ");
        scanf("%[^\n]", word);
        getchar();
    }while(!isNoSpaces(word) && !isLengthValid(word));
    searcSinglehWord(trie, word);
}

void searchRelatedWord(Trie* trie, char *prefix){
    system("cls");
    printf("   _____                      __       ____       __      __           __\n");
    printf("  / ___/___  ____ ___________/ /_     / __ \\___  / /___ _/ /____  ____/ /\n");
    printf("  \\__ \\/ _ \\/ __ `/ ___/ ___/ __ \\   / /_/ / _ \\/ / __ `/ __/ _ \\/ __  / \n");
    printf(" ___/ /  __/ /_/ / /  / /__/ / / /  / _, _/  __/ / /_/ / /_/  __/ /_/ /  \n");
    printf("/____/\\___/\\__,_/_/   \\___/_/ /_/  /_/ |_|\\___/_/\\__,_/\\__/\\___/\\__,_/   \n");
    do{
        printf("Input a prefix to be searched[no spaces]: ");
        scanf("%[^\n]", prefix);
        getchar();
    }while(!isNoSpaces(prefix));
    searchRelated(trie, prefix);
}

void seeAllWord(Data* curr, char *word, int depth){
    system("cls");
    printf("List of all slang words in dictionary:\n");
    printWord(curr, word, 0);
}

int main(){
    Trie boogle;
    boogle.root = createData();

    char word[100];
    char description[256];
    char input;

    do{
        system("cls");
        printf("    ____                    __   \n");
        printf("   / __ )____  ____  ____ _/ /__ \n");
        printf("  / __  / __ \\/ __ \\/ __ `/ / _ \\\n");
        printf(" / /_/ / /_/ / /_/ / /_/ / /  __/\n");
        printf("/_____/\\____/\\____/\\__, /_/\\___/ \n");
        printf("                  /____/         \n");
        printf("1. Release a new slang word\n");
        printf("2. Search a slang word\n");
        printf("3. View all slang words starting with a certain prefix word\n");
        printf("4. View all slang words\n");
        printf("5. Exit\n");
        printf(">> ");
        input = getch();
        getchar();
        switch (input){
        case '1':
            inputNewSlang(&boogle, word, description);
            break;

        case '2':
            searchSlangWord(&boogle, word);
            break;

        case '3':
            searchRelatedWord(&boogle, word);
            break;

        case '4':
            seeAllWord(boogle.root, "", 0);
            break;
        
        case '5':
            system("cls");
            printf("Thank you... Have a nice day :)\n");
            break;
        }

    }while(input != 5);

    return 0;
}