#include <stdio.h>
#include <string.h>
#define MAX_BOOKS 4
#define MAX_BORROW 3

void displayMenu(){
    printf("\n===== UNIVERSITY LIBRARY MENU =====\n");
    printf("1. Member Registration\n");
    printf("2. Display Available Books\n");
    printf("3. Borrow a Book\n");
    printf("4. Return a Book\n");
    printf("5. Display Member Record\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

void registerMember(char name[], int *studentID, int *memberType){
    printf("\n--- Member Registration ---\n");
    printf("Enter name: ");
    getchar();
    fgets(name,50,stdin);
    name[strcspn(name,"\n")]=0;
    printf("Enter student ID: ");
    scanf("%d",studentID);
    while(1){
        printf("Enter membership type (1-Student, 2-Faculty): ");
        scanf("%d",memberType);
        if(*memberType==1 || *memberType==2) break;
        else printf("Invalid! Enter 1 or 2.\n");
    }
    printf("Registration successful!\n");
    if(*memberType==1) printf("Student can keep book for 14 days.\n");
    else printf("Faculty can keep book for 30 days.\n");
}

void displayBooks(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks){
    printf("\n--- Available Books ---\n");
    printf("ID  Title                     Copies\n");
    printf("-----------------------------------\n");
    for(int i=0;i<totalBooks;i++){
        printf("%d  %s  %d\n",bookIDs[i],bookTitles[i],availableCopies[i]);
    }
}

void borrowBook(int bookIDs[], char bookTitles[][50], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType){
    (void)memberType;
    if(*borrowedCount>=MAX_BORROW){
        printf("Borrow limit reached! Max 3 books.\n");
        return;
    }
    int id,days;
    printf("Enter book ID to borrow: ");
    scanf("%d",&id);
    printf("Enter number of days you want to keep: ");
    scanf("%d",&days);
    if(days<=0){printf("Invalid days!\n");return;}
    int found=-1;
    for(int i=0;i<totalBooks;i++) if(bookIDs[i]==id) found=i;
    if(found==-1){printf("Invalid Book ID!\n");return;}
    if(availableCopies[found]<=0){printf("No copies available!\n");return;}
    availableCopies[found]--;
    borrowedBookIDs[*borrowedCount]=id;
    (*borrowedCount)++;
    printf("Book '%s' borrowed successfully.\n",bookTitles[found]);
}

float returnBook(int bookIDs[], int availableCopies[], int totalBooks, int borrowedBookIDs[], int *borrowedCount, int memberType, float *totalFine){
    int id,actualDays;
    printf("Enter book ID to return: ");
    scanf("%d",&id);
    printf("Enter actual days kept: ");
    scanf("%d",&actualDays);
    if(actualDays<=0){printf("Invalid days!\n");return 0;}
    int bIndex=-1;
    for(int i=0;i<*borrowedCount;i++) if(borrowedBookIDs[i]==id) bIndex=i;
    if(bIndex==-1){printf("You have not borrowed this book!\n");return 0;}
    int bookIndex=-1;
    for(int i=0;i<totalBooks;i++) if(bookIDs[i]==id) bookIndex=i;
    availableCopies[bookIndex]++;
    int allowed=(memberType==1)?14:30;
    float fine=0;
    if(actualDays>allowed){
        int extra=actualDays-allowed;
        int rate=(memberType==1)?20:10;
        fine=extra*rate;
        printf("Late! Extra days: %d, Fine: Rs. %.2f\n",extra,fine);
    }else{
        printf("Returned on time. No fine.\n");
    }
    if(fine>0){
        char code[20];
        printf("Enter membership code for waiver (LIB2026) or press Enter to skip: ");
        getchar();
        fgets(code,20,stdin);
        code[strcspn(code,"\n")]=0;
        if(strcmp(code,"LIB2026")==0){
            fine=fine*0.5f;
            printf("50%% waiver applied! Payable: Rs. %.2f\n",fine);
        }
    }
    *totalFine+=fine;
    for(int i=bIndex;i<*borrowedCount-1;i++) borrowedBookIDs[i]=borrowedBookIDs[i+1];
    (*borrowedCount)--;
    return fine;
}

void displayMemberRecord(char name[], int studentID, int memberType, int borrowedBookIDs[], int borrowedCount, float totalFine, float fineAfterWaiver){
    (void)fineAfterWaiver;
    printf("\n--- Member Record ---\n");
    printf("Name: %s\n",name);
    printf("Student ID: %d\n",studentID);
    printf("Membership Type: %s\n",(memberType==1)?"Student":"Faculty");
    printf("Currently Borrowed (%d): ",borrowedCount);
    if(borrowedCount==0) printf("None");
    else for(int i=0;i<borrowedCount;i++) printf("%d ",borrowedBookIDs[i]);
    printf("\nFinal fine payable: Rs. %.2f\n",totalFine);
}

int main(){
    int bookIDs[MAX_BOOKS]={101,102,103,104};
    char bookTitles[MAX_BOOKS][50]={"Programming in C","Data Structures","Database Systems","Computer Networks"};
    int availableCopies[MAX_BOOKS]={5,3,0,4};
    char memberName[50]="Not Registered";
    int studentID=0,memberType=0;
    int borrowedBookIDs[MAX_BORROW];
    int borrowedCount=0;
    float totalFine=0;
    int choice,isRegistered=0;
    do{
        displayMenu();
        scanf("%d",&choice);
        switch(choice){
            case 1: registerMember(memberName,&studentID,&memberType); isRegistered=1; borrowedCount=0; totalFine=0; break;
            case 2: displayBooks(bookIDs,bookTitles,availableCopies,MAX_BOOKS); break;
            case 3: if(!isRegistered) printf("Please register first!\n"); else borrowBook(bookIDs,bookTitles,availableCopies,MAX_BOOKS,borrowedBookIDs,&borrowedCount,memberType); break;
            case 4: if(!isRegistered) printf("Please register first!\n"); else if(borrowedCount==0) printf("No books to return!\n"); else returnBook(bookIDs,availableCopies,MAX_BOOKS,borrowedBookIDs,&borrowedCount,memberType,&totalFine); break;
            case 5: if(!isRegistered) printf("Please register first!\n"); else displayMemberRecord(memberName,studentID,memberType,borrowedBookIDs,borrowedCount,totalFine,totalFine); break;
            case 6: printf("Exiting... Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }
    }while(choice!=6);
    return 0;
}