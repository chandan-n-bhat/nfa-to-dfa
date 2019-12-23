//NFA to DFA algorithm
// Chandan N Bhat

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

struct node
{
  char in;
  char out;
  char sym;
  struct node* next;
};

struct Nfa
{	char**h;
	struct Nfa* link;
};
typedef struct Nfa nfa;

struct state
{
	char name;
	int *v;
};
typedef struct state s;

struct node* first;
int flag=1;

int main()
{
	void lambdaclosure(int*a,char c,char*sl);
	void insert_head(struct node **);
	void display(struct node*);

	int ch,x,y;
	int no_of_states=0;
	int n1,n2;
	printf("Enter no of aphabets\n");
	scanf("%d",&n1);
	fflush(stdin);
	char alpha[n1];//Array of the alphabets
	printf("\nEnter set of alphabets\n");
	for (int k=0;k<n1;k++)
	{
		scanf("%c",&alpha[k]);
		fflush(stdin);
	}
	printf("\nEnter no of states\n");
	scanf("%d",&n2);
	fflush(stdin);
	char dfa[100][n2+1];
	int v[100];//visit array
	for(int m=0;m<100;m++)
	{
		v[m]=-1;
	}
	char statey[n2];//Array of states
	printf("\nEnter set of states\n");
	for (int k=0;k<n2;k++)
	{
		scanf("%c",&statey[k]);
		fflush(stdin);
	}
	printf("\nEnter start state\n");
	char start;
	scanf("%c",&start);
	fflush(stdin);
	char fstates[n2];
	printf("\nEnter final states\n");
	scanf("%c",&fstates[0]);
	int z=0;
	while(fstates[z]!='#')//Terminates when user gives input as #
	{
		z++;
		scanf("%c",&fstates[z]);
	}
	fstates[z]='#';

	first=NULL;
	char b[3];

	while(flag)
	{
		display(first);
		if(flag)
		{
			insert_head(&first);
		}
	}

	no_of_states=n2;
	s lambda[no_of_states];
	char sl[no_of_states];

	for(int i=0;i<no_of_states;i++)
	{
		sl[i]=statey[i];
		lambda[i].name=statey[i];
		lambda[i].v=(int*)malloc(sizeof(int)*no_of_states);
	}

	for(int i=0;i<no_of_states;i++)
	{
		for(int j=0;j<no_of_states;j++)
		{
			lambda[i].v[j]=0;
		}
		lambdaclosure(lambda[i].v,lambda[i].name,sl);
	}

	char startclosure[n2+1]; int  j=0;
	for(int k=0;k<n2;k++)
	{
		if(lambda[k].name==start)
		{
			for(int q=0;q<n2;q++)
			{
				if(lambda[k].v[q]==1)
				{
					startclosure[j++]=lambda[q].name;//Finding the start state
				}
			}
			startclosure[j] ='\0';
			break;
		}
	}

	printf("\n\n\n");

	int a[n2];
	for(int i=0;i<n2;i++)
	{
		a[i]=0;
	}

	nfa*head=NULL;

	int index; char strout[n2];
	char strin[n2];
	strcpy(dfa[0],startclosure);
	v[0]=0;
	strcpy(strout,startclosure);
	int top=0;
	char*final[100][n1+1];
	printf("%s\t","State");
	for(int r=0;r<n1;r++)
	{
		printf("%c\t",alpha[r]);
	}
	printf("\n\n");
	while(v[top]!=-1)
	{
		strcpy(strin,dfa[top]);
		v[top]=1;
		nfa*N=(nfa*)malloc(sizeof(nfa));
		char**table=(char**)malloc(sizeof(char*)*(n1+1));
		N->h=table;
		N->link=head;
		head=N;
		struct node *temp1;
		table[0]=(char*)malloc(sizeof(char)*strlen(strin));
		strcpy(table[0],strin);
		if(strcmp(N->h[0],"")==0)
		{
			printf("{}\t");
		}
		else
		{
			printf("%s\t",N->h[0]);
		}

		final[top][0]=(char*)malloc(sizeof(char)*n2+1);
		strcpy(final[top][0],N->h[0]);
		for(int c=0;c<n1;c++)
		{
			for(int i=0;i<n2;i++)
			{
				a[i]=0;//Array to keep track of lambda closures
			}
			for(int b=0;b<strlen(strin);b++)
			{
				temp1=first;
				while(temp1!=NULL)
				{
					if(temp1->in==strin[b] && temp1->sym==alpha[c])
					{
						for(int e=0;e<n2;e++)
						{
							if(statey[e]==temp1->out)
							{
								index=e;
								break;

							}
						}
						for(int f=0;f<n2;f++)
						{
							a[f]=lambda[index].v[f]|a[f];//Union of lambda closures
						}
					}
					temp1=temp1->next;
				}

			}
			int y=0;

			strcpy(strout,"");
			for(int x=0;x<n2;x++)
			{
				if(a[x]==1)
				{
					strout[y++]=lambda[x].name;
				}
			}
			strout[y]='\0';
			N->h[c+1]=(char*)malloc(sizeof(char)*strlen(strout));
			strcpy(N->h[c+1],strout);
			if(strcmp(N->h[c+1],"")==0)
			{
				printf("{}\t");
			}
			else
			{
				printf("%s\t",N->h[c+1]);
			}

			final[top][c+1]=(char*)malloc(sizeof(char)*n2+1);//Stores the DFA table
			strcpy(final[top][c+1],N->h[c+1]);
			int l=0; int fflag=1;
			while(v[l]!=-1)
			{
				if(strcmp(dfa[l],strout)==0)
				{
					fflag=0;
					break;
				}
				l++;
			}
			if(fflag==1)
			{
				strcpy(dfa[l],strout);v[l]=0;
			}

		}
		printf("\n");
		top=top+1;
	}



	final[top][0]=(char*)malloc(sizeof(char)*7);
	strcpy(final[top][0],"Empty");
	int rep1=0;
	char*s;
	int xx;
	int o=0;
	char*finale[100];
	int ftop=0;
	int flag1=1;
	while(strcmp(final[rep1][0],"Empty")!=0)
	{
		s=final[rep1][0];
		xx=0;
		flag1=1;
		while(flag1 && s[xx]!='\0')
		{
			o=0;
			while(flag1 && fstates[o]!='#')
			{
				if(s[xx]==fstates[o])
				{
					finale[ftop]=(char*)malloc(sizeof(char)*(n2+1));
					strcpy(finale[ftop++],s);

					flag1=0;
				}
				o++;
			}
			xx++;
		}
		rep1++;
	}
	finale[ftop]=(char*)malloc(sizeof(char)*(n2+1));
	strcpy(finale[ftop],"#");
	int r=0;
	printf("\nStart state  : %s",final[0][0]);
	printf("\nFinal states : ");
	while(strcmp(finale[r],"#")!=0)
	{
		printf("%s  ",finale[r]);
		r++;
	}


	printf("\n\n\nAfter renaming states\n\n\n");
	printf("%s\t","State");
	for(int r=0;r<n1;r++)
	{
		printf("%c\t",alpha[r]);
	}
	printf("\n\n");
	int rep=0;int g=0;

	while(strcmp(final[rep][0],"Empty")!=0)
	{
		for(int u=0;u<n1+1;u++)
		{
			g=0;
			while(v[g]!=-1)
			{
				if(strcmp(dfa[g],final[rep][u])==0)
				{
					break;
				}
				g++;
			}
			if(strcmp(final[rep][u],"")==0)
			{
				printf("{}\t");
			}

			else
			{
				printf("%c\t",'A'+g);//Assign each state a different letter
			}

		}
		printf("\n");
		rep=rep+1;
	}

	printf("\nStart state  : %c",'A');
	printf("\nFinal states : ");
	r=0;
	while(strcmp(finale[r],"#")!=0)
	{
		rep=0;
		while(strcmp(final[rep][0],"Empty")!=0)
		{
			if(strcmp(finale[r],final[rep][0])==0)
			{
				printf("%c ",'A'+rep);
			}
			rep++;
		}
		r++;
	}
	printf("\n\n\n");

}



void lambdaclosure(int*a,char c,char*sl)
{
	int j; int l=strlen(sl);
	for(int i=0;i<l;i++)
	{
		if(sl[i]==c)
		{
			j=i;
			break;
		}
	}
	a[j]=1;
	struct node *temp=first;
	while(temp!=NULL)
	{
		if(temp->in==c && temp->sym=='$' )
		{
			lambdaclosure(a,temp->out,sl);
		}
		temp=temp->next;
	}
}



void insert_head(struct node **p)
{

	struct node *temp; char b[3];
	printf("\nEnter transition: ");
	scanf("%s",b);
	fflush(stdin);
	//create a node

	temp=(struct node*)malloc(sizeof(struct node));
	temp->in=b[0];
	temp->sym=b[1];
	temp->out=b[2];
	temp->next=NULL;
	if(b[0]=='#'){//Terminates when user gives input as #
	flag=0;
	}

	if(flag)
	{
		//is this first node ?
		if(*p==NULL)
		*p=temp;
		else //link to the first node
		{
			temp->next=*p;
			*p=temp; //copy address of new node into first
		}
	}
}


void display(struct node *p)
{
	if(p==NULL)
	{
		printf("\nEmpty Transitions\n");
	}

	else
	{
		while(p!=NULL)
		{
			printf("%c%c%c , ",p->in,p->sym,p->out);
			p=p->next;//go to the next node
		}
	}
}