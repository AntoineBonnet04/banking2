/* Program designed to implement a banking app
 * including creating bank accounts, managing withdrawals and refunds.
 * *****************************************************
 * Author               Dept.           Date             Notes
 * Antoine Bonnet       Comp.Science    March 03 2020    Initial version
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define FALSE 0
#define TRUE 1

void add(FILE* file1, char* accnum, char* name){
        fprintf(file1,"AC,%s,%s\n", accnum, name);    exit(0);}

void deposit(FILE* file1, char* accnum, char* date, char* amount){
        fprintf(file1,"TX,%s,%s,%s\n", accnum, date, amount);    exit(0);}

void withdraw(FILE* file1, char* accnum, char* date, char* amount){
	fprintf(file1, "TX,%s,%s,-%s\n", accnum, date, amount);    exit(0); }


int main(int argc, char *argv[]){

int exists = FALSE; // whether account already exists
float balance = 0; // Balance if account exists
char line[200];
char* accnum;
char* date;
char* amount;

FILE* filetest = fopen("bankdata.csv","r"); // test if exists
if (filetest == NULL) {// file not found   
       fprintf(stderr,"Error, unable to locate the data file bankdata.csv\n"); exit(100);}

FILE* file1 = fopen("bankdata.csv", "a+"); // file pointer

if (argc < 3) {fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
        exit(1);}

accnum = argv[2];

while (fgets(line,sizeof(line),filetest)){// while end of file not reached
	char* entry1 = strtok(line, ","); // first entry, delimited by commas, entry type (TX or AC)
	char* entry2 = strtok(NULL, ","); // Second entry, account number
	if (strcmp(entry2, accnum) == 0) {	 // if account numbers match
		exists = TRUE;

		if (strcmp(entry1, "TX")  == 0) { // if withdrawal or deposit, add amount to account balance
	       		entry2 = strtok(NULL, ","); entry2 = strtok(NULL, ","); // get fourth token
			balance += strtof(entry2, NULL);}
	}
}

accnum = argv[2];

if (strcmp(argv[1],"-a") == 0){// Add new account
	if (argc != 4) {
		fprintf( stderr,"Error, incorrect usage!\n-a ACCTNUM NAME\n"); exit(1);}
	else if (exists) {// If account already exists
		fprintf(stderr,"Error, account number %s already exists\n", accnum); exit(50);}

	else {char * name = argv[3]; 	add(file1, accnum, name);}}

else if (exists == FALSE) { // If file empty or account does not exist
	fprintf(stderr,"Error, account number %s does not exist\n", accnum); exit(50);}

else if (strcmp(argv[1],"-d") == 0){ // Make a deposit
	if (argc != 5){
                fprintf(stderr,"Error, incorrect usage!\n-d ACCTNUM DATE AMOUNT\n"); exit(1);}

	else { date = argv[3]; amount = argv[4];	deposit(file1, accnum, date, amount);}}

else if (strcmp(argv[1],"-w") == 0 ){// Make a withdrawal
	
	if (argc != 5) {
                fprintf( stderr,"Error, incorrect usage!\n-w ACCTNUM DATE AMOUNT\n"); exit(1);}

        else if ( strtof(argv[4],NULL) > balance ) { // insufficient funds
		fprintf(stderr, "Error, account number %s has only %.2f\n", accnum, balance); exit(60);}

	else {	date = argv[3]; char * amount = argv[4];	withdraw(file1, accnum, date, amount);}}

else {  fprintf(stderr, "Error, incorrect usage!\n-a ACCTNUM NAME\n-d ACCTNUM DATE AMOUNT\n-w ACCTNUM DATE AMOUNT\n");
	exit(1);}}

