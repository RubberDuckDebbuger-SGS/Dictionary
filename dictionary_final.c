#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node
{
	char word[20];
	char meaning[100];
	struct Node* next;
};

void add (struct Node** head_ref,char user_input_word[20],char user_input_defn[100]);
void print (struct Node* head_print);
void delete (struct Node** head_del,char word_del[20]);
void look_up(struct Node* head_look,char word_look[20]);
void sort (struct Node** head_sort);
void write_to_file(struct Node** head_w);
void load_from_file(struct Node** head_load);

void add (struct Node** head_ref,char user_input_word[20],char user_input_defn[100])
{
	struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
	strcpy(new_node->word,user_input_word);
	strcpy(new_node->meaning,user_input_defn);
	new_node->next = *head_ref;
	*head_ref = new_node;
	sort(head_ref);
}

void sort (struct Node** head_sort)
{
	struct Node* c = *head_sort;
	struct Node* i = NULL;
	char temp_word[20];
	char temp_defn[20];
	int result;
	while (c != NULL)
	{
		i = c->next;
		while (i != NULL)
		{
			result = strcmp(c->word,i->word);
			if ( result > 0 )  
			{
				strcpy(temp_word,c->word);
				strcpy(temp_defn,c->meaning);
				
				strcpy(c->word,i->word);
				strcpy(c->meaning,i->meaning);
				
				strcpy(i->word,temp_word);
				strcpy(i->meaning,temp_defn);
			}
			i = i->next;
		}
		c = c->next;
	}
}

void print (struct Node* head_print)
{
	struct Node* temp_1 = head_print;
	while (temp_1 != NULL)
	{
		printf("%s=",temp_1->word);
		printf("%s",temp_1->meaning);
		printf("\n");
		temp_1 = temp_1->next;
	}
}

void delete (struct Node** head_del,char word_del[20])
{
	struct Node* temp = *head_del;
	struct Node* prev = *head_del;
	int compare,comp;
	compare = strcmp((*head_del)->word,word_del);
	if (compare == 0)
	{
		*head_del = temp->next;
		free(temp);
		return;
	}
	
	while (temp != NULL && comp != 0)
	{
		prev = temp;
		temp = temp->next;
		comp = strcmp(temp->word,word_del);
	}
	prev->next = temp->next;
	free(temp);
}

void look_up(struct Node* head_look,char word_look[20])
{
	struct Node* cur = head_look;
	int c;
	while (cur != NULL)
	{
		c = strcmp(cur->word,word_look);
		if ( c == 0 )
		{
			printf("%s = ",cur->word);
			printf("%s",cur->meaning);
		}
		cur = cur->next;
	}
}

void write_to_file(struct Node** head_w)
{
	FILE *fp;
	fp = fopen("dict.txt","a");
	struct Node* current = *head_w;
	if (fp != NULL)
	{
		while (current != NULL)
		{
			fprintf(fp,"\n%s = %s",current->word,current->meaning);
			current = current->next;
		}
	printf("\n");
	}
	else
	{
		printf("The file cannot be opened.");
	}
	fclose(fp);
}

void load_from_file(struct Node** head_load)
{
	FILE *fp_1;
	fp_1 = fopen("dict.txt","r");
	char singleline[120],temp[20],temp_2[100];
	int i,new,j;
	if ( (fp_1 = fopen("dict.txt","r")) == NULL )
	{
		printf("fopen failed.");
	}
	while (fgets(singleline,120,fp_1) != NULL)
	{
		i=0;
		new=0;
		j=0;
		while (singleline[i] != '=')
		{
			temp[i] = singleline[i];
			i++;
		}
		temp[i] = '\0';
		new = i+1;
		while (singleline[new] != '\0')
		{
			temp_2[j] = singleline[new];
			new++;
			j++;
		}
		temp_2[j] = '\0';
		add(head_load,temp,temp_2);
	}
	fclose(fp_1);
}

int main()
{
	struct Node* head = NULL;
	char user_input_word[20];
	char user_input_defn[100];
	char del[20],look[20];
	int n,choice;
	printf("1.Add a word to the file\n2.Delete a word\n3.Search a word\n4.Load dictionary from a file\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);
	printf("\n");
	if (choice == 1)
	{ 
		printf("Enter the number of entries you want to make: ");
		scanf("%d",&n);
		for (int i=0;i<n;i++)
		{
			printf("Enter new entry of Dictionary: ");
			while ((getchar()) != '\n'); 
			scanf("%[^\n]",user_input_word);
			
			printf("Enter the definition: ");
			while ((getchar()) != '\n'); 
			scanf("%[^\n]",user_input_defn);
			
			add(&head,user_input_word,user_input_defn);
		}
		print(head);
		write_to_file(&head);
	}
	else if (choice == 2)
	{	
		printf("Enter the word you want to delete: ");
		scanf("%s",del);
		delete(&head,del);
		printf("\n");
	}
		
	else if (choice == 3)
	{
		printf("Enter the word you want to look up: ");
		scanf("%s",look);
		look_up(head,look);
	}
	else 
	{
		load_from_file(&head);
		print(head);
	}
}