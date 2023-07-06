#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//creation of a node
struct node
{
  char data;
  struct node *link;
};
struct node*head=NULL;
int o_len=0;
//inserting elements like an array 
void insertattail(char value)
{
  
  struct node *current=head;
  struct node *temp=(struct node*)malloc(sizeof(struct node));
  temp->data=value;
  temp->link=NULL;
  if(head == NULL)
  {
    head=temp;
    return;
  }
 while(current->link != NULL)
 {
    current=current->link;
 }
  current->link=temp;
  return;
  
}
 void insertathead(char value)
{
  struct node *temp=(struct node *)malloc(sizeof(struct node));
  temp->data=value;
  temp->link=NULL;
  if(head==NULL)
  {
    head=temp;
 } 
  else
  {  
    temp->link=head;
    head=temp;  
  }
  return;
}
void printlist()
{
    struct node *point=head;
    while(point!=NULL)
    {
        printf("%c",point->data);
        point=point->link;
    }
    return;
}

int main(){
    char name[30];
    printf("Enter the string:\n");
    scanf("%s",name);
    int a[26]={0};
    o_len=strlen(name);
    for(int i=0;i<strlen(name);i++)
    {
        a[name[i]-97]++;
    }
   
    int idx=-1;
    int hlen=0;
    for(int i=0;i<26;i++)
    {
        if(a[i] ==  1)
        {
            idx=i;
            break;
        }
    }
    
    if(idx!=-1)
    {
    insertathead((char)(idx+97));
    }
    for(int i=0;i<26;i++)
    {
        char ch=(char)(i+97);
        if(i==idx)
        {
            continue;
        }
        if(a[i]%2 == 0 && a[i]>0)
        {
         
            for(int h=0;(h<(a[i]/2));h++)
            {
                //insert at head and tail
                insertathead(ch);
                insertattail(ch);

            }
        }
        else if(a[i]%2==1)
        {
           hlen=a[i];
            if(hlen==o_len){
              printf("%s",name);
              break;
            }
            for(int h=0;h<((a[i]+1)/2);h++)
            {
                //insert at head and tail;
                insertathead(ch);
                insertattail(ch);
            }
        }

    }
    printlist();
}