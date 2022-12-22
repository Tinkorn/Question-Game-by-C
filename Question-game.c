#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "string.h"
#include "time.h"

//PUSH \0 AFTER '?'
void pushNULL(char question[]){
	char *p=strchr(question,'?');
		*(p+1)='\0';	
}

//Show hint
void hint(char answer1[20]){
char answer[20];
strcpy(answer,answer1);
int n=strlen(answer),x;

	n--;
	srand(time(NULL));
	x=(rand()%n)+1;

int ran[x],i;
	for(i=0;i<x;i++){
		ran[i]=(rand()%n)+1;
		answer[ran[i]-1]='_';
	}
	printf("[%s]\n",answer);
}

//trim space ' ' out from player answer
void trim(char answer[20]){
char *p=answer;
char answer1[20]=" ";	 
int i=0;
	 while(*p!='\0'){
	 	if(*p!=' '){
	 		answer1[i]=*p;
	 		i++;
		 }
		 p++;

	 }

strcpy(answer,answer1);

}
//add question merk '?'
void add_question_mark(char question[100]){
	int n=strlen(question);
	char *p=question;	

	p=p+(n-1);
	if(*p!='?'){
		*(p+1)='?';
		*(p+2)='\0';
		
	}
}

int  main(){
	int mode;
	int k,i,number_of_player,number_of_question=0;
	char ch,str[500]="";
	
	printf("\n\n\n\n\n\n\t\t\t\t\t//// SELECT MODE ////\n\n\t\t\t\t\t1) PLAYER\n\t\t\t\t\t2) ADMIN\n\n\t\t\t\t\tEnter here: ");
	
	scanf("%d",&mode);
	system("cls");
	FILE *f;
	
		f=fopen("info.txt","r");
		
		if(f==NULL){
			printf("ERROR TO READ FILE!!");
			fclose(f);
		}else
		
		//READ AMOUNT OF QUESTIONS
		while(fgets(str,500,f)!=NULL){
			number_of_question+=1;
		}
		
		//RETURN FILE POINTER BACK TO BOF 
		rewind(f);
		
	
		//CREATE STRUCT OF INFOMATION
		struct infomation{
			char question[100];
			char answer[20];
		}info[number_of_question];
		
	
		//READ QUESTIONS ANSWERS HINTS
		for(k=0,i=0;k<number_of_question;k++){
		
			fseek(f,3,1);
			do{
				ch=fgetc(f);
				info[k].question[i]=ch;	
				i++;
				
			}while(ch!=':');
			i=0;
			fflush(stdin);
			fscanf(f,"%s",info[k].answer);
			fseek(f,2,1);
			pushNULL(info[k].question);			
	}
		fclose(f);
	
	
//player mode
	if(mode==1){
		
		int score=0;
		char NM[3];
		printf("\n\n\n\n\n\n\t\t\t\t\t//// WELCOME TO QUESTION GAME ////\n\n");
		printf("\t\t\t\t\tinput number of players: ");
		scanf("%s",NM);
		fflush(stdin);
		number_of_player=atoi(NM);
		
		
		if(number_of_player>=1){
				//STRUCT variable for player
		struct PLAYER{
			char name[20];
			char answer[number_of_question][20];
			int score;
		}player[number_of_player];
		
		
	//get player name
	for(i=0;i<number_of_player;i++){
			printf("\t\t\t\t\tenter name player[%d]: ",i+1);
			gets(player[i].name);
			fflush(stdin);
			
		}
		
	system("cls");

	
	//show question
	for(k=0;k<number_of_player;k++){
		for(i=0;i<number_of_question;i++){
			fflush(stdin);
		printf("\n\n\n\n\n\n\t\t\t\t\t[%s]\n\n",player[k].name);
		printf("\t\t\t\t\t%d) %s\n",i+1,info[i].question);
		printf("\t\t\t\t\thint :");
		hint(info[i].answer);
		printf("\n\t\t\t\t\tanswer here: ");
		gets(player[k].answer[i]);
		fflush(stdin);			
		system("cls");
		
		trim(player[k].answer[i]); //trim space ' ' out
		
		if(strcasecmp(player[k].answer[i],info[i].answer)==0){  //check answer
			score+=1;
		}
		
		}
		player[k].score=score;
		score=0;
	
	}
	
	struct PLAYER temp;
	
	//sort by score
	for(i=0;i<number_of_player;i++){
		for(k=i+1;k<number_of_player;k++){
			if(player[i].score<player[k].score){
				temp=player[i];
				player[i]=player[k];
				player[k]=temp;
			}
		}
	}
	//show answer and score of player
	printf("\n\n\n\n\n\n\t\t\t\t\t////  SCORE BORD ////\n\n");
	printf("%-34c%-27s%s\n\n",' ',"[name]","[score]");
	for(k=0;k<number_of_player;k++){
		printf("%-34c%-30s%d\n",' ',player[k].name,player[k].score);
	}printf("\n\n\n");
	
	//SAVE DATA INTO FILE
	f=fopen("report.txt","w");
	
	
	if(f==NULL){
		printf("ERROR TO OPEN FILE \n");
		fclose(f);
	}else 
	fprintf(f,"%15c\t\t// SCORE BORD //\n",' ');
	fprintf(f,"\t[name]%-30c[score]\n",' ');
	for(i=0;i<number_of_player;i++){
		fprintf(f,"\t%-38s%d\n",player[i].name,player[i].score);
	}
	fprintf(f,"\n\n\n");
	fprintf(f,"=================================[infomation]==============================\n\n");
	for(i=0;i<number_of_player;i++){
		fprintf(f,"[%s]\n",player[i].name);
		for(k=0;k<number_of_question;k++){
			fprintf(f,"%d) %s\n",k+1,player[i].answer[k]);
		}
	fprintf(f,"\n===========================================================================\n");		
	}
	fclose(f);

			
		}else {
		printf("\t\t\t\t\tERROR!");
		}
		
	
//admin mode
	}else if(mode==2){
		int select;
		
	//select menu
		printf("\n\n\n\n\n\n\t\t\t\t\t//// WELCOME TO ADMIN MODE ////\n\n");
		printf("\t\t\t\t\t1 : Create new question\n");
		printf("\t\t\t\t\t2 : Remove question\n");
		printf("\t\t\t\t\t3 : Edit question\n\n");
		printf("\t\t\t\t\tPlease select mode: ");
		scanf("%d",&select);
		fflush(stdin);
		
		//add mode 
		if(select==1){
		    char k1[3];
			int n=number_of_question,j,k,l;
			
				//SHOW OLD DATA
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Create new question mode] ////\n");
				printf("\n\t\t<< OLD DATA >>\n\n");
				printf("\t\t%-63s%s","[question]","[answer]");
				printf("\n\n");
				for(i=0;i<number_of_question;i++){
				printf("\t\t%d) %-60s%s\n",i+1,info[i].question,info[i].answer);
				}
				
				printf("\n\t\tHow many question you want to create : ");
				scanf("%s",k1);
				fflush(stdin);
				k=atoi(k1);
				system("cls");
				
							
				if(k==0){
					printf("ERROR!");
				}else if(k>0){
					
					
					struct infomation info1[k];	
					
					for(l=0;l<k;l++){
						
						
				//input new dota
				printf("\n\n\n\n\n\n\t\t\t\t//// CREATE QUETION ////\n\n");
				printf("\t\tinput new question [%d]: ",l+1);
				fflush(stdin);
				gets(info1[l].question);
				fflush(stdin);
				add_question_mark(info1[l].question); 	//add '?' 
				printf("\t\tinput answer for question: ");
				gets(info1[l].answer);
				trim(info1[l].answer);		//trim space out from string
				system("cls");
				
				
				//Open file
				f=fopen("info.txt","a");
				if(f==NULL){
				printf("ERROR TO OPEN FILE!");
				fclose(f);
				}else 
				
				if(l==0){
				fprintf(f,"\n");
				}
				
				//print new data into file
				if(k-l==1){
				 fprintf(f,"%d) %-69s:%s",n+1,info1[l].question,info1[l].answer);					
				}else
				fprintf(f,"%d) %-69s:%s\n",n+1,info1[l].question,info1[l].answer);
				n++; //incress dato
				fclose(f);
				}
					
				system("cls");
				
				//SHOW NEW DATA
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Create new question mode] ////\n");
				printf("\n\t\t<< SAVE COMPLETE >>\n\n");
				printf("\t\t%-63s%s\n\n","[question]","[answer]");
				
				for(i=0;i<number_of_question;i++){
				printf("\t\t%d) %-60s%s\n",i+1,info[i].question,info[i].answer);
				}
				
				for(i=0;i<k;i++){
					printf("\t\t%d) %-60s%s\n",number_of_question+1,info1[i].question,info1[i].answer);	
					number_of_question++;
												
				}
					
			
					
				}else if(k==0){
					printf("\t\tERROR!\n");
				}else 
					printf("\t\tERROR!\n");
				
		
		
		//remove
		}else if(select==2){
		
			int remove,n1=number_of_question,i;
			char remove1[3];
			
			system("cls");
			

			do{
				//show old data
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Remove mode] ////\n");
				printf("\t\t<< DATA >>\n\n");
				printf("\t\t%-63s%s\n\n","[question]","[answer]");
			
				for(i=0;i<n1;i++){
					printf("\t\t%d) %-60s%s%\n",i+1,info[i].question,info[i].answer);
				}
	
			
				
				//get position want to remove out
				fflush(stdin);
				printf("\n\t\tinput position you want to remove: ");
				gets(remove1); //get input on string
				fflush(stdin);
				remove=atoi(remove1); //convert string to interger
				
				
				if(remove==0){ //if input is not integer or is 0
					printf("\t\tPlease input data in correct form [Positive integer]!\n");
				}else if(remove<=0 || remove>n1){	//if don't have dota as input 			
					printf("\t\tDon't have data to remove!\n");
				}else{
				
				//switch dota in structure between you select with next structure 
				for(i=remove-1;i<n1;i++){
					info[i]=info[i+1];
					fflush(stdin);
				}
					
				n1--; // decrease number of question
					
				//Open FILE	
				f=fopen("info.txt","w");
				if(f==NULL){
					printf("ERROR TO OPEN FILE!!");
					fclose(f);
				}else
				
				//printf new dato to file
				for(i=0;i<n1;i++){
					if(n1-i==1){
						fprintf(f,"%d) %-69s:%s",i+1,info[i].question,info[i].answer);
					}else
					fprintf(f,"%d) %-69s:%s\n",i+1,info[i].question,info[i].answer);
				}
				fclose(f);
				}
				printf("\t\tPress 'Y' for exit: ");	
				}while(tolower(getch())!='y');
				
					//show old data
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Remove mode] ////\n");
				printf("\n\n\t\t<< SAVE COMPLETE >>\n\n");
				printf("\t\t%-63s%s\n\n","[question]","[answer]");
			
				for(i=0;i<n1;i++){
					printf("\t\t%d) %-60s%s\n",i+1,info[i].question,info[i].answer);
				}
								
		
		//edit
		}else if(select==3){
			char edit1[3];
			int edit,i;
			
			
			do{			
				// show old data
				fflush(stdin);
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Edit mode] ////\n\n");
				printf("\t\t<< DATA >>\n\n");
				printf("\t\t%-63s%s\n\n","[question]","[answer]");
			
				for(i=0;i<number_of_question;i++){
					printf("\t\t%d) %-60s%s\n",i+1,info[i].question,info[i].answer);
				}			
				
				printf("\n\t\tenter position you want to edit: ");
				gets(edit1); //get position you want to edit form string
				fflush(stdin);
				edit=atoi(edit1); //convert string to integer
				
				if(edit==0){	//if input is not integer or is 0
					printf("\t\tplese enter position you want to edit in [positive integer] form !!\n");
				
					
				}else if(edit<=0 || edit>number_of_question){ //if don't have dato as input
					printf("\t\tdon't have data!!\n");
					
				}else {
					
						//get new dato 
						printf("\n\t\t%-10s [%s] -->  ","Question:",info[edit-1].question);
						memset(info[edit-1].question,0,100);
						gets(info[edit-1].question);
						add_question_mark(info[edit-1].question);
						printf("\t\t%-10s [%s] -->  ","Answer:",info[edit-1].answer);
						gets(info[edit-1].answer);
						trim(info[edit-1].answer);
						
						//Openfile 
						f=fopen("info.txt","w");
						if(f==NULL){
							printf("\t\tERROR TO OPEN FILE!\n");
							fclose(f);
						}else 
						//print data into file
						for(i=0;i<number_of_question;i++){
							if(number_of_question-i==1){
								fprintf(f,"%d) %-69s:%s",i+1,info[i].question,info[i].answer);
							}else
								fprintf(f,"%d) %-69s:%s\n",i+1,info[i].question,info[i].answer);
							}								
						}
						fclose(f);
				printf("\t\tPress 'Y' for exit: ");	
				}while(tolower(getch())!='y');
				
				system("cls");
				printf("\n\n\n\n\n\n\t\t\t\t //// [Edit mode] ////\n\n");
				printf("\t\t<< SAVE COMPLETE >>\n\n");
				printf("\t\t%-63s%s\n\n","[question]","[answer]");
			
				for(i=0;i<number_of_question;i++){
					printf("\t\t%d) %-60s%s\n",i+1,info[i].question,info[i].answer);
				}			
			
		}else{
			printf("\t\t\t\t\tERROR!!");
		}
		
		
		
	}else printf("ERROR!!");
	
	return 0;
}

