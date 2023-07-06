#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 17

typedef struct node
{
    char data;
    int height;
    struct node* right, *left;
}node;
node* root = NULL;

void inorder(node* root)
{
    if(root==NULL) return;
    inorder(root->left);
    printf("%c ", root->data);
    inorder(root->right);
}
void preorder(node* root)
{
    if(root==NULL) return;
    printf("%c ", root->data);
    preorder(root->left);
    preorder(root->right);
}
int max(int a, int b)
{
    return (a>=b) ? a : b;
}
int height(node* N)
{
    if(N==NULL)
        return -1;
    else
        return N->height;
}
node* get_new_node(char data)
{
    node* temp = (node*)malloc(sizeof(node));
    temp->right=temp->left=NULL;
    temp->height = 0;
    temp->data = data;
    return temp;
}
int get_balance(node* N)
{
    if(N==NULL)
        return 0;
    return height(N->left) - height(N->right);
}



node* rightrotate(node* x)
{
    node* y = x->left;
    node* t = y->right;
    
    y->right = x;
    x->left = t;
    
    // the order of updating the respectives heights can't be changed as x is now below y in hierarchy
    // first x's height is updated and then y's height
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    
    return y;
}
node* leftrotate(node* x)
{
    node* y = x->right;
    node* t = y->left;
    
    y->left = x;
    x->right = t;
    
    // the order of updating the respectives heights can't be changed as x is now below y in hierarchy
    // first x's height is updated and then y's height
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    
    return y;
}


node* insert(node* root, char data)
{
    if(root==NULL)
        root = get_new_node(data);
    else if(root->data > data)
        root->left = insert(root->left, data);
    else if(root->data < data)
        root->right = insert(root->right, data);
    else  // not inserting the duplicate keys
        return root;
    
    
    root->height = 1 + max(height(root->left), height(root->right));
    
    int balance = get_balance(root);
    
    if(balance>1 && data < root->left->data)  // the balance condition has to be written first or else the second condition will give segmentation fault
        root = rightrotate(root);
    else if(balance<-1 && data > root->right->data)
        root = leftrotate(root);
    else if(balance>1 && data > root->left->data)
    {
        root->left = leftrotate(root->left);
        root = rightrotate(root);
    }
    else if(balance<-1 && data < root->right->data)
    {
        root->right = rightrotate(root->right);
        root = leftrotate(root);
    }
    
    return root;
}

void next_ext(char* str, int n)              // next extension
{
    for(int i=0; str[i] != '\0'; i++)
        str[i] = ( 65 + ((int)str[i] - 65 + 1)%26 );
}

void step_1(char* str, int n)
{
    if(n==16)
        return;

    int rem = 16-n;
    rem = rem*(rem<n) + n*(n<rem);

    char extension[rem+1];
    memcpy(extension, str, rem);
    extension[rem] = '\0';

    // printf("%s\n", extension);
    while(strlen(str) < MAX_SIZE - 1)
    {
        next_ext(extension, rem+1);
        strcat(str, extension);
        if(strlen(str) > MAX_SIZE)
            str[MAX_SIZE-1] = '\0';
    }
}

void step_2(char* str, int n)
{
    int freq[26] = {0};
    char x = '0';
    for(int i=0; str[i]!='\0'; i++)
    {
        freq[str[i] - 'A'] += 1;
        if(freq[str[i] - 'A'] > 2)
        {
            str[i] = '!';   //using ! to mark the character as deleted   
            // freq[str[i] - 'A']--;
            continue;
        }
        if(freq[str[i] - 'A'] == 2)
        {
            str[i] = x++;
            freq[str[i] - 'A']--;
        }
    }
    
    int count = 0;   
    char new_str[n+1];
    for(int i=0; str[i]!='\0'; i++)
        if(str[i]!= '!')
            new_str[count++] = str[i];
    
    for(int i=0; i<count; i++)
        str[i] = new_str[i];
    str[count] = '\0';
}

void step_3(char* str, int n)
{
    for(int i=0; i<n; i++)
        root = insert(root, str[i]);
}

void task_1(char* str, int n)
{
    step_1(str, n);
    step_2(str, n);
    step_3(str, strlen(str));
    printf("final : %s\n", str);
}

void main()
{
    char name[MAX_SIZE];

    // taking input of first 16 characters of user's name (wihtout spaces)
    fgets(name, MAX_SIZE, stdin);   // stores '\n' too
    if(strlen(name)==MAX_SIZE-1)
        name[strlen(name)] = '\0';
    else
        name[strlen(name)-1] = '\0';


    printf("String : %s\n", name);
    
    printf("String length : %d\n", strlen(name));

    task_1(name, strlen(name));

    if(root == NULL)    printf("hi");
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");

}