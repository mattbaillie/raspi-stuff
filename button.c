#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>

#define BtnPin        0
#define Gpin        1
#define Rpin        2

typedef struct node {
    int data;
    struct node * next;
} node;

void makeNode(node* head, int count);

void LED(char* color)
{
    pinMode(Gpin, OUTPUT);
    pinMode(Rpin, OUTPUT);
    if (color == "RED")
    {
        digitalWrite(Rpin, HIGH);
        digitalWrite(Gpin, LOW);
    }
    else if (color == "GREEN")
    {
        digitalWrite(Rpin, LOW);
        digitalWrite(Gpin, HIGH);
    }
    else
        printf("LED Error");
}

int main(void)
{
    if(wiringPiSetup() == -1){ //when initialize wiring failed,print messageto screen
        printf("setup wiringPi failed !");
        return 1; 
    }

    pinMode(BtnPin, INPUT);
    LED("GREEN");
    
    node* head;
    int count = 1;

    while(1){
        if(0 == digitalRead(BtnPin)){
            delay(100);
            if(0 == digitalRead(BtnPin)){
                LED("RED");    
                makeNode(head, count);
				printf("Node %d added. There are now %d nodes in the list.\n", count, count);
                count++;

            }
        }
        else if(1 == digitalRead(BtnPin)){
            delay(10);
            if(1 == digitalRead(BtnPin)){
                while(!digitalRead(BtnPin));
                LED("GREEN");
            }
        }
    }
    return 0;
}

void makeNode(node* head, int count){
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode == NULL){
        printf("That shouldn't have happened.");
        exit(0);
    }
    newNode->data = count;
    newNode->next = NULL;
    if(head == NULL){
        head = newNode;
    }
    else{
        node* currNode = head;
        while(currNode->next != NULL){
            currNode = currNode->next;
        }
        currNode->next = newNode;
    }    
}
