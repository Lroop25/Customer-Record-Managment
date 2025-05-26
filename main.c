#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include<time.h>

// function declaration
void addcust();
void deletecust();
int search();
void editcust();
void menu();
void loaddir();
void showmemdata();
void transaction();
void witdrawal();
void deposit();
int nextid();
int dateval();
int IsLeapYear (int year);
void name();
void loadcustfile(char[]);
void inquiry();
void statement();
void dir_rewrite();
void getdate();

// created a struct 
typedef struct m {
    int id;
    char fname[25];
    char lname[25];
    int amt;
    int delflag; // this is a condition/flag to say if to be deleted
}memdata; // memdata is a variable used to store data from directory.txt

typedef struct d{
  int day;
  int month;
  int year;
}dateformat; // name of variable used to store date

typedef struct c{
  char transtype[12];
  int transamt;
  int bal;  
  dateformat date; // stores date of respective transaction 
}custfile; // storing contents of customer invicual file

// global variables
memdata dir[100];
memdata cust;
custfile customer[100];
dateformat date;
int i,x,j;
char filename [50];

int main() {
  printf("Version 6\n");
   while (1) { 
    menu();
     } // end while
  return 0;
 }// end main
 
void loaddir () {
  i=0;
  FILE *fp;
  fp=fopen ("directory.txt","r");
  if (fp == NULL){// validating valid file
    printf("The file is invalid\n");
  } // end if
  while (!feof(fp)) {
  fscanf(fp, "%d,%[^,],%[^,],%d", &dir[i].id, dir[i].fname, dir[i].lname, &dir[i].amt);
    //printf("%d,%s,%s,%c,%d \n",dir[i].id, dir[i].fname, dir[i].lname, dir[i].val ,dir[i].amt );
    i++;
    }// end while
  //dir[i].id="\0";
  fclose(fp);
}//working

void loadcustfile (char filename[50]) {
   j=0;
  FILE *fp2;
  fp2=fopen (filename,"r");
  if (fp2 == NULL){// validating valid file
    printf("The file is invalid\n");
  } // end if
  while (!feof(fp2)) {
  fscanf(fp2, "%[^,],%d,%d,%d/%d/%d", customer[j].transtype, &customer[j].transamt, &customer[j].bal, &customer[j].date.day, &customer[j].date.month, &customer[j].date.year);
    j++;
    }// end while
  fclose(fp2);
  //printf(%s,%d,%d,)
}

void getdate(){
  // date is being stored to global var: date of type dates(struct)
  int flag;
  do{
    date.day=0, date.month=0, date.year=0; // inatilising so previous dates will be overwritten
    printf("Enter Today's Date in Format: DD/MM/YY\n");
    scanf("%d/%d/%d",&date.day,&date.month,&date.year);
    getchar();
    if (date.month >12 || date.month < 1 || date.year < 2020){
      flag =1;
    } // validate months and year
    else {
      if (date.month == 2) { // if february
        if (date.year %4 == 0 && date.year %100!= 0 || date.year %400 == 0 && date.year %100 == 0){
          if (date.day > 29 || date.day < 1) { // for leap year
            flag = 1; 
          }else {
            flag = 0;
          }
        } else {
          if (date.day > 28 || date.day < 1){ // for normal year (365 days)
            flag = 1;
          } else {
            flag = 0;
          }
        }
      } else { 
        if (date.month ==9 | date.month ==4 || date.month == 6 || date.month == 11){ // months with 30 days
          if (date.day > 30 || date.day <1 ){
            flag = 1;
          } else{
            flag = 0;
          }
        } else {
          if (date.day > 31 || date.day <1) { // months with 31 days
            flag = 1;
          } else {
            flag = 0;
          }
        }
        
      }
    }
    if (flag != 0){
      printf("Invalid date entered. Please enter a valid date\n");
    }
  } while(flag != 0);
}

void menu(){
  int opt, subopt;
  // need to do a do while loop for menu to loop constanty ?

   printf("Welcome to Lasko Credit Union's Computerised data management software \n Please enterthe number that corresponds to your intended purpose:\n");
  printf("1) Customer Management \n");
  printf("2) Customer Search \n");
  printf("3) Record a Transaction \n");
  printf("4)  Balance Inquiry\n");
  printf("5)  Account statement\n");
  printf("6)  Exit\n");
        
    scanf("%d", &opt);
    getchar();
  
  switch (opt){
    
    case 1: // customer affairs
      printf("Press 1 to register a new customer\n");
      printf("Press 2 to Edit customer data\n");
      printf("Press 3 to Delete a customer\n");
       printf("Press 4 to Return \n");
      scanf("%d" ,&subopt);
      getchar();

      switch (subopt){
        case 1:
          addcust();
        break;

        case 2:
          editcust();
        break;

        case 3:
          deletecust();
        break;

      case 4:
       printf("Press enter to continue \n");
       getchar();
       break;

      default:
      printf("Unknown command entered\n Try again\n \n");
      }// end switch
    break;
    
    case 2:
      search();
    break;

    
    
    case 3: // case completed do not interfere; work on witdraw and deposit function
      printf("Press 1 to record a Deposit \t\n");
      printf("Press 2 to record a witdrawal \t\n");
       printf("Press 3 to Return \t\n");
      scanf ("%d",&subopt);
      getchar();
      
      switch (subopt) {
        
        case 1: 
          deposit();
        break;

        case 2:
          witdrawal();
        break;

        case 3:
         printf("Press enter to continue \n");
        getchar();
        break;
        
        default:
        printf("Unknown command entered\n Try again\n \n");
        //break;
        
      }// end switch
    break;

    case 4:
    inquiry();
    break;

    case 5:
    statement();
    break;

    case 6: // completed; do not interfere
    printf("Goodbye \n");
    exit (0);
    break;
    
default:
    printf("Unknown command entered\n Try again\n \n");
    //getchar();
    //exit (0); we want to loop back so do not brea
    } // end switch
  } // end menu

void name() {
  printf("Enter customer's First Name \n");
  fgets(cust.fname,25,stdin);
  printf("Enter customer's last Name \n");
  fgets(cust.lname,25,stdin);
  
  cust.fname[(strlen(cust.fname)-1)] = '\0';
  cust.lname[(strlen(cust.lname)-1)] = '\0';

  x=0;
  while (cust.fname[x] != '\0') { // conv fname to =cap
    cust.fname[x] = toupper(cust.fname[x]);
    x++;
    }
  x=0;// reset counter 
  while (cust.lname[x] != '\0') { // conv lname to cap
    cust.lname[x] = toupper(cust.lname[x]);
      x++;
    }  
}// end name

void addcust() {
  char filename[50];
  FILE *fp;
  FILE *fp2;
  
  cust.id = nextid();
  name();
  printf("enter opening balance\n");
  scanf("%d",&cust.amt);
  getchar();

  fp = fopen("directory.txt","a"); //appending directory to show customer on reccord
   fprintf(fp, "\n%d,%s,%s,%d",cust.id, cust.fname, cust.lname, cust.amt);
  fclose(fp);

  strcpy(filename, cust.fname);
  strcat(filename, cust.lname);
  strcat(filename, ".txt");

  getdate();
  
  // need to do date input/vaidation and to write date to fp2...
  fp2 = fopen(filename ,"w");// creating file for customer account history
  fprintf(fp, "DEPOSIT ,%d,%d,%d/%d/%d\n",cust.amt, cust.amt, date.day, date.month, date.year); // writing opening bal
  // writing to file in format: ("DEPOSIT,50(AMT DEPOISTED),350, 5/5/21")
  fclose(fp);

  //printing success statement to let people know acc created
  printf("Success! Customer has been registered with the following details:\n");
  printf("\n Account number: %d \n First name: %s \n Last name: %s \n Balance: %d \n",cust.id,cust.fname, cust.lname, cust.amt);
  printf("on %d/%d/%d\n",date.day, date.month, date.year);
  printf("\n");
  // need to do customer validation to make sure customer isnt already registered prolly do it in a function... if cust exists print account num
  // jelanin doing function to call and auto insert date
  // needto do a function for when reading strings to convert all to common letters
  
}

int nextid() {
  i=0; 
  int id;
  loaddir();
  //printf("i %d\n",i);
  id = dir[i-1].id+1;
  //printf("%d\n",id);
  return id;
}

int search(){
  int subopt=0,flag=0,a,b;
  printf("To search by name Press 1 \n");
  printf("To search by account number Press 2 \n");
  printf("To View a directory Press 3\n");
   printf("To return press 4 \n");
  scanf("%d",&subopt);
  getchar();
  
  switch (subopt){
    case 1: do{
      name();
      //printf("%s %s",cust.fname, cust.lname);
      loaddir();
      flag=0;
      for (x=0;x<i;x++){
        a = strcmp(cust.fname, dir[x].fname);
        b = strcmp(cust.lname, dir[x].lname);
       // printf("a=%d  b=%d",a,b);
        if(a ==b ){
          flag = 1;
          //printf("match X: %d\n",x);
          break;
          //return x;
          } else {
          flag = 0;
          //printf("no match\n");
          }// end if
      }// end for
      if (flag==1) {
        printf("Customer found: \n Name: %s %s \n Account Number: %d\n",dir[x].fname, dir[x].lname, dir[x].id);
        printf("\n Press 0 to search again\n Press 1 to continue");
        scanf("%d",&flag);
        getchar();
          if (flag == 1){
            //printf("x%d\n",x);
            return x;}
        } else {
          printf("There is no one registered under that name\n");
        printf("Press 0 to search again \n Press 1 to exit search\n");
        scanf("%d",&flag);
        getchar();
        }// end else
      } while (flag == 0);
    break;
     case 2:
       do{
    loaddir();
    printf("Enter customer's Account Number \n");
    scanf("%d", &cust.id);
    getchar();
    for (x = 0; x < i; x++) {
      if (cust.id == dir[x].id) {
        flag = 1;
        break;
        //return x; // return x?
        // general rule x+1=id
      } else {
        flag = 0;
      } // end else
    } // end for
         if (flag==1) {
        printf("Customer found: \n Name: %s %s \n Account Number: %d\n",dir[x].fname, dir[x].lname, dir[x].id);
        printf("\n Press 0 to search again\n Press 1 to continue\n");
        scanf("%d",&flag);
        getchar();
          if (flag == 1){
            //printf("x%d\n",x);
            return x;}
        } else {
          printf("There is no one registered under that name\n");
           do{
        printf("Press 0 to search again \n Press 1 to exit search\n");
        scanf("%d",&flag);
        getchar();
           } while(flag <1 && flag >-1); // check
        }// end else
      } while (flag == 0);
    break;
         
  case 3:
    loaddir();
    for (x = 0; x < i; x++) {
      printf("Customer Name: %s %s\n Account #: %d\n \n",
      dir[x].fname, dir[x].lname, dir[x].id);
    }
    printf("Press Enter to continue\n \n");
    getchar();
    return 0;

    case 4:
    printf("Press enter to continue \n");
    getchar();
     return 0;

     default:
      printf("Unknown command entered\n Try again\n \n");
  }
}

void deletecust() { // will come bk to
  int loc;
  char filename[50];
 // loaddir();
  loc = search();
  dir[loc].delflag ='1';
  strcpy(filename, dir[loc].fname);
  strcat(filename, dir[loc].lname);
  strcat(filename, ".txt");
  remove(filename);
  dir_rewrite();
  }// to do

void editcust() {
  int loc, opt;
  char ofilename[50];
  char nfilename[50];
  char tempname[50];
  loc = search();
  printf("\nPress 1 to modify Customer's First Name\n Press 2 to modify Customer's Last Name\n Presss 3 to Return\n");
  scanf("%d",&opt);
  getchar();
  switch (opt){
    case 1 :
      printf("Enter Customer's First Name");
      fgets(nfilename,50,stdin); 
       nfilename[(strlen(nfilename)-1)] = '\0'; // remove \n from fgets
      x=0;
      while (nfilename[x] != '\0') { // conv name to =cap
      nfilename[x] = toupper(nfilename[x]);
      x++;
       }
      printf("Press 0 to confirm changing Customer's First name from %s to %s\n Press 1 to cancel\n",dir[loc].fname,nfilename);
      scanf("%d",&opt);
        switch (opt){
          case 0:
            
            strcpy(ofilename,dir[loc].fname); // copying old file name to ofilename 
            printf("Sucess! Customer's First name has been changed from %s to %s \n",ofilename,nfilename);
            strcat(ofilename,dir[loc].lname); // copying last name to 1st to formulate indivual cust file
           strcat(ofilename, ".txt");
            
            strcpy(dir[loc].fname, nfilename); // copying new file name to array
            strcpy (nfilename,dir[loc].fname);  // formulating filename
            strcat(nfilename,dir[loc].lname); // copying last name to 1st to formulate indivual cust file
           strcat(nfilename, ".txt");
            rename(ofilename, nfilename);// renaming indiv cust  file
          printf("Press enter to continue \n\n");
        getchar();
        break;

          case 1:
          break;
          
          default:
            printf("Unknown command entered\n Try again\n \n");
          
        }
      dir_rewrite();
    break;
    
    case 2:
      printf("Enter Customer's Last Name");
      fgets(tempname,50,stdin); 
       tempname[(strlen(tempname)-1)] = '\0'; // remove \n from fgets
      x=0;
      while (tempname[x] != '\0') { // conv name to =cap
      tempname[x] = toupper(tempname[x]);
      x++;
       }
      printf("Press 0 to confirm changing Customer's last name from %s to %s\n Press 1 to cancel\n",dir[loc].lname,tempname);
      scanf("%d",&opt);
        switch (opt){
          case 0:
            
            strcpy(ofilename,dir[loc].fname); // copying old file name to ofilename 
            printf("Sucess! Customer's Last name has been changed from %s to %s \n",dir[loc].lname,tempname);
            strcat(ofilename,dir[loc].lname); // copying last name to 1st to formulate indivual cust file
           strcat(ofilename, ".txt");
            
            strcpy(dir[loc].lname,tempname); // copying new file name to array
            strcpy (nfilename,dir[loc].fname);  // formulating filename
            strcat(nfilename,dir[loc].lname); // copying last name to 1st to formulate indivual cust file
           strcat(nfilename, ".txt");
            rename(ofilename, nfilename);// renaming indiv cust  file
            dir_rewrite();
          printf("Press enter to continue \n\n");
        getchar();
            break;
          
          case 1:
          break;

           default:
        printf("Unknown command entered\n Try again\n \n");
        }
    
    case 3:
      printf("Press enter to continue \n");
      getchar();
      break;

    default:
    printf("Unknown command entered\n Try again\n \n");
    
  } 
}// to do

void witdrawal(){ // note loaddir called in search
  int loc, witamt, newbal, flag1;
  char filename[50];
  loc = search(); // location of cust in array dir[100]
  if (loc == 0){
    return;
  }// end if
  printf("Enter amount Witdrawn\n");
  scanf("%d",&witamt);
  getchar();
  getdate();
  newbal = dir[loc].amt - witamt;//new balance after witdrawn amt    
  //printf("b4%d,aft%d",dir[loc].amt, newbal);
  strcpy (filename,dir[loc].fname);
  strcat(filename,dir[loc].lname);
  strcat(filename, ".txt");
  //loadcustfile(filename);
  //printf("bal before trans %d\n",dir[loc].amt);
  dir[loc].amt = newbal;
  //printf("new bal? %d\n",dir[loc].amt);
  dir_rewrite();
  
  FILE *fp2;
  fp2 = fopen(filename,"a");
  fprintf(fp2,"WITDRAWAL,%d,%d,%d/%d/%d\n",witamt,newbal,date.day, date.month, date.year);
  fclose(fp2);
  printf("\n Witdrawal Success!\n %d/%d/%d \n Customer Name: %s %s \n Account Number: %d\n Witdrawal: $%d \n Current Balance: $%d\n \n",date.day, date.month, date.year, dir[loc].fname, dir[loc].lname, dir[loc].id,witamt, newbal);
  printf("Press enter to continue\n \n");
  getchar();
}

void deposit(){// working
  int loc, depamt, newbal;
  char filename[50];
  loc = search(); // location of cust in array dir[100]
  if (loc == 0){
    return;
  }// end if
  printf("Enter amount Deposited");
  scanf("%d",&depamt);
  getchar();
  getdate();
  newbal = dir[loc].amt + depamt;//new balance after witdrawn amt
  strcpy (filename,dir[loc].fname);
  strcat(filename,dir[loc].lname);
  strcat(filename, ".txt");
  dir[loc].amt = newbal;
  dir_rewrite();
  FILE *fp2;
  fp2 = fopen(filename,"a");          
  fprintf(fp2,"DEPOSIT,%d,%d,%d/%d/%d\n",depamt,newbal,date.day, date.month, date.year);
  fclose(fp2);
  printf("\n Deposit Success!\n %d/%d/%d \n Customer Name: %s %s \n Account Number: %d\n Deopsit: $%d \n Current Balance: $%d\n \n",date.day, date.month, date.year, dir[loc].fname, dir[loc].lname, dir[loc].id,depamt, newbal);
  printf("Press enter to continue\n \n");
  getchar();
  }

void inquiry(){
  int loc;
  loc = search();
  printf("\n Customer Name: %s %s\n Account Number: %d \n Current Balance: $%d\n ",dir[loc].fname, dir[loc].lname, dir[loc].id, dir[loc].amt);
  printf("Press Enter to continue\n \n");
}

void statement (){
  int loc;
  loc = search();
  strcpy (filename,dir[loc].fname);
  strcat(filename,dir[loc].lname);
  strcat(filename, ".txt");
  loadcustfile(filename);
  printf("\n Customer Name: %s %s \n Account Number: %d\n ", dir[loc].fname, dir[loc].lname, dir[loc].id);
printf("Transaction Type\t Transaction Amount\t Balance\t Date \n");
  printf("________________________________________________________\n\n");
  for (x=0;x<j-1;x++){
    printf("%s\t\t\t %d\t\t\t\t\t %d\t\t %d/%d/%d \n", customer[x].transtype, customer[x].transamt, customer[x].bal, customer[x].date.day, customer[x].date.month, customer[x].date.year);
  }// end for
  printf("\nCURRENT BALANCE: $%d \n",dir[loc].amt);
  
  printf("Press Enter to continue\n \n");
  getchar();
}

void dir_rewrite(){
   FILE *fp;
  fp = fopen("directory.txt","w");
  for (x=0;x<i;x++){ // rewrite directory with change of user's balance
    //printf("x=%d delflag =%d\n",x,dir[x].delflag);
    if (dir[x].delflag != 1){
    fprintf(fp, "\n%d,%s,%s,%d",dir[x].id, dir[x].fname, dir[x].lname, dir[x].amt);
    }// end if
    }// end for
  fclose(fp);
}
