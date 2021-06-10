#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char* data;
    struct Node* left;
    struct Node* right;
} Node;
Node* newNode (char* sentence)
{
    Node* n = malloc(sizeof(Node));
    n->data = malloc(200);
    strcpy(n->data, sentence);
    n->left=NULL;
    n->right=NULL;
    return n;
}
Node* insert(Node* node, char* key)
{
    if(node==NULL)
        return newNode(key);
    if(strcasecmp(key, node -> data) == -1)
        node->left = insert(node->left,key);
    else if(strcasecmp(key, node -> data) == 1)
        node->right = insert(node->right,key);
    return node;
}
Node* search(Node* node, char* key)
{
    if(node == NULL)
        return NULL;
    if(strcasecmp(key, node->data) == 0)
        return node;
    else if(strcasecmp(key, node->data) == 1)
        return search(node->right,key);
    else
        return search(node->left,key);
}
int count(Node* node)
{
    if(node==NULL)
        return 0;
    else
        return 1+ count(node->left)+ count(node->right);
}
int max(int x, int y)
{
    return x>y ? x : y;
}
int height(Node* node)
{
    if(node==NULL)
        return -1;
    else
        return 1+ max(height(node->left), height(node->right));
}
/*void read(char filename [])
{
    Node* root = NULL;
    char word[100];

    FILE* f= fopen(filename,"r");

    if (f == NULL)
    {
        printf("Could not open file");
    }
    else
    {
        printf("Dictionary Loaded Successfully...!\n");
        printf("..................................\n");
        fscanf(f,"%[^\n]",word);
        root = insert(root, word);
        fscanf(f,"\n");
        while(fgets(word, 200, f)!=NULL)
        {
            root = insert(root, word);
        }

    }
    fclose(f);
    printf("Size = %d\n",count(root));
    printf("..................................\n");
    printf("Height = %d\n",height(root));
    printf("..................................\n");
    //printf("%s",root->data);
    /*  else
      {
          printf("File not found");
      }
      fclose(f);

}*/
/*void search_for_word(Node* node, char* sentence)
{
    char *token = strtok(sentence, " ");
    while(token!=NULL)
    {
        search(node,token);
        if(search(node,token)==NULL)
        {
            printf("%s INCORRECT",token);
        }
        else
            printf("%s CORRECT",token);
        token = strtok(NULL, " ");
    }*/
Node* min(Node* node)
{
    if(node==NULL)
        return NULL;
    else if(node->left!=NULL)
        return min(node->left);
    else
        return node;
}
Node* getSuccessor(Node* node, Node* last)
{
    Node* successor;
    if(last->right != NULL)
        return min(last->right);
    else
        while(node!=NULL)
        {
            if(strcasecmp(last->data,node->data)==-1)
            {
                successor= node;
                node=node->left;
            }
            else if(strcasecmp(last->data,node->data)==1)
            {
                node=node->right;
            }
            else
                break;
        }
        return successor;
}

Node* getLast(Node* root, char* token)
{
    while(root!=NULL)
    {
        if(strcasecmp(token,root->data)==-1)
        {
            if(root->left==NULL)
                return root;
            root=root->left;
        }
        else if(strcasecmp(token,root->data)==1)
        {
            if(root->right == NULL)
                return root;
            root=root->right;
        }
    }
}
int main()
{
    char sentence [200];

    // read("EN-US-Dictionary.txt");
    Node* root = NULL;
    char word[100];

    FILE* f= fopen("EN-US-Dictionary.txt","r");
    if (f == NULL)
    {
        printf("Could not open file");
    }
    else
    {
        printf("Dictionary Loaded Successfully...!\n");
        printf("..................................\n");
        fscanf(f,"%[^\n]",word);
        root = insert(root, word);
        fscanf(f,"\n");
        while(fgets(word, 200, f)!=NULL)
        {
            word [strlen(word)-1] = '\0';
            root = insert(root, word);
        }

    }
    fclose(f);
    printf("Size = %d\n",count(root));
    printf("..................................\n");
    printf("Height = %d\n",height(root));
    printf("..................................\n");
    printf("Enter a sentence: \n");
    gets(sentence);
    char *token = strtok(sentence, " ");
    while(token != NULL)
    {
        //printf("%s",search(root,token));
        if(search(root,token)!= NULL)
            printf("%s - Correct\n",token);
        else
        {

            Node* lastNode = getLast(root, token);
            char* successor= getSuccessor(root, lastNode)->data;
            if(getSuccessor(root, lastNode)->data==NULL)
                successor='No successor';
            printf("%s - Incorrect, Suggestions: %s %s\n",token,lastNode->data,successor);
        }

        token = strtok(NULL, " ");
    }

//    Node* root = NULL;
//    root = insert(root,'hello');
//    root= insert(root,'world');
//    root= insert(root,'hi');
//    printf("%d",root->data);
//    printf("%d",height(root));

    return 0;
}
