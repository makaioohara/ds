#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Patient{
    char name[50];
    int age;
    int priority;
    struct Patient* next;
} Patient;
typedef struct Stack {
    char name[50];
    struct Stack* next;
} Stack;
Patient* pq[3] = {NULL, NULL, NULL};
Stack* discharged = NULL;

Patient* createPatient(char name[], int age, int priority) {
    Patient* newP = (Patient*)malloc(sizeof(Patient));
    strcpy(newP->name, name);
    newP->age = age;
    newP->priority = priority;
    newP->next = NULL;
    return newP;
}
void addPatient() {
    char name[50];
    int age, priority;
    printf("\nEnter name: ");
    fgets(name ,sizeof(name),stdin);
    name[strcspn(name,"\n")] = '\0';
    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter priority (1=High, 2=Medium, 3=Low): ");
    scanf("%d", &priority);
    if (priority < 1 || priority > 3) {
        printf("Invalid priority!\n");
        return;
    }
    Patient* newP = createPatient(name, age, priority);
    int index = priority - 1;
    if (pq[index] == NULL)
        pq[index] = newP;
    else {
        Patient* temp = pq[index];
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newP;
    }

    printf("Patient added successfully!\n");
}
void pushDischarge(char name[]) {
    Stack* newS = (Stack*)malloc(sizeof(Stack));
    strcpy(newS->name, name);
    newS->next = discharged;
    discharged = newS;
}
void servePatient() {
    for (int i = 0; i < 3; i++) {
        if (pq[i] != NULL) {
            Patient* temp = pq[i];
            pq[i] = pq[i]->next;
            printf("\nServing patient: %s (Priority %d)\n", temp->name, temp->priority);
            pushDischarge(temp->name);
            free(temp);
            return;
        }
    }
    printf("No patients waiting!\n");
}

void viewWaitingList() {
    printf("\n--- Waiting List ---\n");
    for (int i = 0; i < 3; i++) {
        Patient* temp = pq[i];
        printf("Priority %d: ", i + 1);

        if (temp == NULL) {
            printf("No patients\n");
        } else {
            while (temp != NULL) {
                printf("[%s (%d)] -> ", temp->name, temp->age);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}
void viewDischarged() {
    printf("\n--- Discharged Patients ---\n");
    Stack* temp = discharged;

    if(!temp) {
        printf("No discharged patients.\n");
        return;
    }
    while(temp != NULL) {
        printf("%s -> ", temp->name);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main() {
    int choice;

    while(1){
        printf("\n\n===== ER MANAGEMENT SYSTEM =====\n");
        printf("1. Add Patient\n");
        printf("2. Serve Next Patient\n");
        printf("3. View Waiting List\n");
        printf("4. View Discharged Patients\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: servePatient(); break;
            case 3: viewWaitingList(); break;
            case 4: viewDischarged(); break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
