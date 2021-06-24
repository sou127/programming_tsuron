#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "sushi.h"

typedef struct order{
	SUSHI ordered_sushi;
	int plates;
	struct order *next;
} ORDERNODE;
ORDERNODE sentinel;
ORDERNODE *new, *prev;

void printList(void);
void clearList(void);
void addNode();
int searchMenu();
int searchOrders();
int costOfItem();
int energyGained();

int n = sizeof(menu)/sizeof(menu[0]);

int main(){
	sentinel.next = NULL;
	char *order_name;
	int order_quantity;
	int cost=0;
	int energy=0;

	while(1){
		scanf("%s", order_name);
		scanf("%d", &order_quantity);

		cost += costOfItem(order_name, order_quantity);
		energy += energyGained(order_name, order_quantity);

		if(strcmp(order_name, "That'sall") && strcmp(order_name, "show")){
			if(searchOrders(order_name, order_quantity)==0)
				addNode(order_name, order_quantity);
		}else break;
	}
	ORDERNODE *ip;
	int variety=0;
	int sumOfPlates=0;
	for(ip = sentinel.next;ip!=NULL;ip=ip->next){
		variety++;
		sumOfPlates+=ip->plates;
	}
	if(!strcmp(order_name, "show")) {
		printList();
	}
	printf("\nIn total, you ordered\n");
	printf(" %d kinds of nigiri-sushi\n", variety);
	printf(" %d plates\n", sumOfPlates);
	printf(" total amount %d yen\n", cost);
	printf(" and you'll gain %d kcal.\n", energy);
	clearList();
}

void printList(void) {
	ORDERNODE *ip;
	for(ip = sentinel.next;ip!=NULL;ip=ip->next){
		printf("\t%s %d plate\n", ip->ordered_sushi.nigiri_name, ip->plates);
	}
}

void clearList(void) {
	ORDERNODE *ip, *iptmp;
	for(ip = sentinel.next;ip!=NULL;ip=iptmp){
		iptmp=ip->next;
		free(ip);
	}
}

void addNode(char *order_name, int order_quantity){
	if((new = (ORDERNODE *)malloc(sizeof(ORDERNODE)))==NULL){
		perror("allocating for a new");
		exit(EXIT_FAILURE);
	}
	if(sentinel.next==NULL) sentinel.next = new;
	else prev->next = new;
	if(searchMenu(order_name) == 1){
		strcpy(new->ordered_sushi.nigiri_name, order_name);
		new->plates = order_quantity;
		new->next = NULL;
		prev = new;
	}else{
		printf("Sorry, we can't serve items that are not on our menu: [%s %d]\n", order_name, order_quantity);
	}
}

int searchMenu(char order_name[]){
	int flag = 0;
	for(int i=0;i<n;i++){
		if(strcmp(menu[i].nigiri_name, order_name) == 0)
			flag = 1;
	}
	return flag;
}

int costOfItem(char order_name[], int order_quantity){
	int cost = 0;
	for(int i=0;i<n;i++){
		if(strcmp(menu[i].nigiri_name, order_name) == 0){
			cost += order_quantity*menu[i].nigiri_price;
		}
	}
	return cost;
}

int energyGained(char order_name[], int order_quantity){
	int energy = 0;
	for(int i=0;i<n;i++){
		if(strcmp(menu[i].nigiri_name, order_name) == 0)
			energy += order_quantity*menu[i].nigiri_energy;
	}
	return energy;
}

int searchOrders(char *order_name, int order_quantity){
	int flag = 0;
	ORDERNODE *ip;
	for(ip = sentinel.next;ip!=NULL;ip=ip->next){
		if(strcmp(order_name, ip->ordered_sushi.nigiri_name)==0){
			ip->plates += order_quantity;
			flag = 1;
		}
	}
	return flag;
}
