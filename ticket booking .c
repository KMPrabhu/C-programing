#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket {
    int ticketNo;
    char name[50];
    int seatNo;
};

// Book Ticket
void bookTicket() {
    FILE *fp = fopen("tickets.dat", "a");
    struct Ticket t;

    printf("Enter Ticket Number: ");
    scanf("%d", &t.ticketNo);

    printf("Enter Name: ");
    scanf(" %[^\n]", t.name);

    printf("Enter Seat Number: ");
    scanf("%d", &t.seatNo);

    fwrite(&t, sizeof(t), 1, fp);
    fclose(fp);

    printf("🎉 Ticket Booked Successfully!\n");
}

// View Tickets
void viewTickets() {
    FILE *fp = fopen("tickets.dat", "r");
    struct Ticket t;

    printf("\n--- All Tickets ---\n");

    while (fread(&t, sizeof(t), 1, fp)) {
        printf("Ticket No: %d | Name: %s | Seat: %d\n",
               t.ticketNo, t.name, t.seatNo);
    }

    fclose(fp);
}

// Cancel Ticket
void cancelTicket() {
    FILE *fp = fopen("tickets.dat", "r");
    FILE *temp = fopen("temp.dat", "w");

    struct Ticket t;
    int tno, found = 0;

    printf("Enter Ticket Number to Cancel: ");
    scanf("%d", &tno);

    while (fread(&t, sizeof(t), 1, fp)) {
        if (t.ticketNo != tno) {
            fwrite(&t, sizeof(t), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("tickets.dat");
    rename("temp.dat", "tickets.dat");

    if (found)
        printf("❌ Ticket Cancelled Successfully!\n");
    else
        printf("Ticket Not Found!\n");
}

// Search Ticket
void searchTicket() {
    FILE *fp = fopen("tickets.dat", "r");
    struct Ticket t;
    int tno, found = 0;

    printf("Enter Ticket Number to Search: ");
    scanf("%d", &tno);

    while (fread(&t, sizeof(t), 1, fp)) {
        if (t.ticketNo == tno) {
            printf("Found: Ticket No: %d | Name: %s | Seat: %d\n",
                   t.ticketNo, t.name, t.seatNo);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Ticket Not Found!\n");

    fclose(fp);
}

// Main Menu
int main() {
    int choice;

    while (1) {
        printf("\n====== Ticket Booking System ======\n");
        printf("1. Book Ticket\n");
        printf("2. View Tickets\n");
        printf("3. Search Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: bookTicket(); break;
            case 2: viewTickets(); break;
            case 3: searchTicket(); break;
            case 4: cancelTicket(); break;
            case 5: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }

    return 0;
}
