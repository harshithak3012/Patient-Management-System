#include <stdio.h>
#include <stdlib.h>
//structure to represent patient details
typedef struct {
    char name[100];
    int age;
    int id;
}details;
// Structure for a patient
typedef struct Patient {
    details data;
    int priority;
    struct Patient* next;
} Patient;

// Structure for the patient queue
typedef struct PatientQueue {
    Patient* front;
} PatientQueue;

// Function to create a new patient node
Patient* createPatient(details data, int priority) {
    Patient* newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->data = data;
    newPatient->priority = priority;
    newPatient->next = NULL;
    return newPatient;
}

// Function to create a new patient queue
PatientQueue* createQueue() {
    PatientQueue* queue = (PatientQueue*)malloc(sizeof(PatientQueue));
    queue->front = NULL;
    return queue;
}

// Function to check if the patient queue is empty
int isEmpty(PatientQueue* queue) {
    return (queue->front == NULL);
}

// Function to insert a patient into the queue based on priority
void enqueue(PatientQueue* queue, details patient,int priority) {
    Patient* newPatient = createPatient(patient, priority);

    // If the queue is empty or the new patient has higher priority than the front patient
    if (isEmpty(queue) || priority < queue->front->priority) {
        newPatient->next = queue->front;
        queue->front = newPatient;
    }
    else {
        Patient* current = queue->front;

        // Traverse the queue to find the appropriate position to insert the new patient
        while (current->next != NULL && current->next->priority <= priority) {
            current = current->next;
        }

        newPatient->next = current->next;
        current->next = newPatient;
    }
}

// Function to remove the highest priority patient from the queue
details dequeue(PatientQueue* queue) {
    if (isEmpty(queue)) {
        details emptypatient={"",-1,-1};
        return emptypatient;
    }
    
    Patient* front = queue->front;
    details frontpatient=front->data;
    queue->front = front->next;
    free(front);
    return frontpatient;
}

// Function to display the patients in the queue
void displayQueue(PatientQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }

    Patient* current = queue->front;
    printf("Patient Queue:\n");
    while (current != NULL) {
        printf("Patient name:%s,Patient age:%d,Patient id:%d,Priority:%d\n",current->data.name,current->data.age,current->data.id,current->priority);
        current = current->next;
    }
}

int main() {
    PatientQueue* queue = createQueue();
    int choice;
    do {
        printf("\n-- Patient Management System --\n");
        printf("1. Register new patient\n");
        printf("2. Process next patient\n");
        printf("3. Display patient queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                int priority;
                details patient;
                printf("Enter patient name: ");
                scanf("%s", patient.name);
                printf("Enter patient age: ");
                scanf("%d", &patient.age);
                printf("Enter patient ID: ");
                scanf("%d", &patient.id);
                printf("Enter patient priority: ");
                scanf("%d", &priority);

                enqueue(queue,patient,priority);
                printf("Patient registered successfully.\n");
                break;
            }
            case 2: {
                details nextPatient = dequeue(queue);
                if (nextPatient.id != -1) {
                    printf("Patient name:%s,Patient age:%d,Patient id:%d\n",nextPatient.name,nextPatient.age,nextPatient.id);
                } else {
                    printf("No patients in the queue.\n");
                }
                break;
            }
            case 3: {
                displayQueue(queue);
                break;
            }
            case 4: {
                printf("Exiting program.\n");
                break;
            }
            default: {
                printf("Invalid choice. Please try again.\n");
                break;
            }
        }
    } while (choice != 4);

    
    return 0;
}
