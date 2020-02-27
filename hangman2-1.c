#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void menu();
void init_temp(char** temp,int number,int j);
int how_many_times(char **temp, int x, char c, int numberOfWords);
void sort_array(int arr[26][2], int freq[26]);
int lets_find_position(int* letters, int i, int number, int x);
void fill_2d_array(char **wordarr, int i, int* letters, FILE* fp);
void print_2d_array(char **wordarr, int i, int* letters);
int dictionary_build(FILE* fp);
int lets_play(int* letters, int i, int* number);
void frequency(char** temp,int numberOfWords,int number, int freq[26]);
int main(int argc, char *argv[])
{ 	
	FILE *fp;
	int i=0, option=0, numberOfWords=0, number=0, j=0, tries=0, hang=0, no=0, x=0, k=0, err, gameOver=0;
	int freq[26];
	int arr[26][2];
	int* letters;
	int* pos;
	char** wordarr;
	char** temp;
	char c;
	for(j=0; j<26; j++){ //initialization of array freq
		freq[j]=0;
	}
	if((fp = fopen("dictionary.txt", "w")) == NULL) {
        	fprintf(stderr, "Error\n");
			fclose(fp);
			exit(0);
	}
		while((gameOver!=1)){
		
		menu();
		scanf("%d", &option);
		switch(option)
		{	case 1:{
				if(i==0){
					letters=(int*)malloc(i+1 * sizeof(int));
				}
				else{
					letters=realloc(letters, sizeof(int)* i+1);
				}
				*(letters + i)=dictionary_build(fp); 
				i++;
				break;
			}
			
			case 2:{
				int j=0;
				wordarr= (char**)malloc((i+1)* sizeof(char*));
				for(j=0;j<=i;j++){
					wordarr[j]= (char*) malloc(sizeof(char)* letters[j]);
				}
				fill_2d_array(wordarr,i,letters,fp);
				numberOfWords=lets_play(letters, i,&number);
				if(numberOfWords==0){
					letters=realloc(letters, sizeof(int)* i+1);
					*(letters + i)=dictionary_build(fp);
				}
				
				else{
					temp=(char**)malloc(sizeof(char*)*numberOfWords);
					for(j=0;j<numberOfWords; j++){
						temp[j]=(char*)malloc(sizeof(char)* number);
					}
					pos= (int*)malloc(numberOfWords * sizeof(int));
					for(j=-1; j<=numberOfWords; j++){ //initialization of pos array
						pos[j]=0;
					}
					for(j=0;j<numberOfWords; j++){
						pos[j]=lets_find_position(letters,i, number, pos[j-1]); //bazo j-1 gia na arxisei na psaxnei apo ekei pou teleiose
						strcpy(*(temp+ j), *(wordarr + (pos[j]-1)));
						printf("%s\n", temp[j]);
						frequency(temp,j,number,freq);
					}
					sort_array(arr, freq);
                    x=0;
					while((tries<6)&& (x<numberOfWords* number-number)){
						printf("Is there a(n) %c in the word? Type 1 for yes and 0 for no: ", arr[no][1]+ 'a');
                        scanf("%d", &hang);
                        c=arr[no][1]+'a';
                        if(hang==1){
                            
                            no++;
                            for(k=0; k<numberOfWords; k++){
                                err=0;
                                for(j=0; j<number; j++){
                                    if(c!=temp[k][j]){
                                       err++;
                                    }
                                    
                                }
                                if(err==number){
                                	
                                	for(j=0; j<number; j++){
                                		if(temp[k][j]!='\n') x++;
                                		temp[k][j]='\n';
									}	
								}
                            }   
                        }
                        
                        if(hang==0){
                            tries++;
                            no++;
                            for(k=0; k<numberOfWords; k++){
                                err=0;
                                for(j=0; j<number; j++){
                                    if(c==temp[k][j]){
                                       err++;
                                    }   
                                }
                                if(err>0){
                                	
                                	for(j=0; j<number; j++){
                                		if(temp[k][j]!='\n') x++;
                                		temp[k][j]='\n';
									}	
								}
								
                            }
                        }
					}
					if((tries<6)&&(x==numberOfWords * number-number)){
						printf("Wait! Is it:");
						for(k=0;k<numberOfWords; k++){
							for(j=0; j<number; j++){
								if(temp[k][j]!='\n'){
									printf("%c", temp[k][j]);
								}
							}
						}
						printf("?\n");
						printf("Type 1 for yes and 0 for no again!\n");
						scanf("%d", &hang);
						if(hang==1){
							printf("Nothing can beat me!\n");
   							gameOver=1;
						}
						else {
                        no=0;
						printf("I must be really dump! :( \n");
						letters=realloc(letters, sizeof(int)* i+1);
						*(letters + i)=dictionary_build(fp);
						gameOver=1;
						}
					}
					if((tries==6)|| (x==numberOfWords*number)){
                        no=0;
						printf("I must be really dump! :( \n");
						letters=realloc(letters, sizeof(int)* i+1);
						*(letters + i)=dictionary_build(fp);
						gameOver=1;
					}
					free(pos);
					for(j=0;j<numberOfWords; j++)
						free(temp[j]);
					free(temp);
					for(j=0;j<i;j++)
						free(wordarr[j]);
					free(wordarr);
				}
					
				break;
			}
				
			
			case 0:{
				return 0;
			}
		}
			
		}
	}

		



void menu(){
	printf("1. Dictionary build\n");
	printf("2. Let's play\n");
	printf("0. Exit\n");
	printf("Select:\n");
	
}
int dictionary_build(FILE* fp){ 
	int i=0;
	char string[20];
	printf("Give me the word you want to add:\n");
 	fp = fopen("dictionary.txt", "a");
   	fscanf(stdin, "%s", string);
	fputs(string, fp);
   	fclose(fp);
	while(string[i]!='\0'){
		i++;
	}
	return i;
	
}
int lets_play(int* letters, int i, int* number){
	int x=0, numberOfWords=0, j=0;
	printf("Give me the number of letters you want to play with:\n");
	scanf("%d", number);
	if(*number> 20) printf("No way!\n");
	else{
		while(x<i){
			if(*number==letters[x]){
				numberOfWords++;
			}
			x++;
		}
	}
	return numberOfWords;
}

void frequency(char** temp,int j,int number, int freq[26]){
	int c = 0, x=0;
		for(c=0;c<number; c++){
 			if (temp[j][c] >= 'a' && temp[j][c] <= 'z') {
    		     x = temp[j][c] - 'a';
    		     freq[x]++;
    		  }
    		
   		}
		  	
	
}

void fill_2d_array(char **wordarr, int i, int* letters, FILE* fp){
    int x=0, j=0;
    fp=fopen("dictionary.txt", "r");
    while(x<i){
   		fgets(*(wordarr+ x), letters[x]+1, fp); //bazo +1 gt einai kai to '\n' kathe neou string dhl. to end of string
    	x++;
    }
    fclose(fp);
}
int lets_find_position(int* letters, int i, int number, int x){
	while(x<i){
		x++;
		if(number==letters[x-1]){
			return x;	
		}
		}
}	   
void sort_array(int arr[26][2], int freq[26]){
	int i=0,j=0, temp=0, k=0;
	for(i=0;i<26; i++){
		arr[i][0]=freq[i];
	}
	for(i=0; i<26; i++){
		arr[i][1]=i;
	}

	for (i = 0; i < 26; i++)                    

		for (j = 0; j < 26; j++)             
		{
			if (arr[j][0] < arr[i][0])                
			{
				temp = arr[i][0];         
				arr[i][0] = arr[j][0];            
				arr[j][0] = temp;
				temp=arr[i][1];
				arr[i][1]=arr[j][1];
				arr[j][1]=temp;           
			}
		}
}


		
    





