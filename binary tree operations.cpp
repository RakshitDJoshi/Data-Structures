#include<iostream>
using namespace std;
struct node
{
    int data;
    node *left;
    node *right;
};
node *root=NULL, *previous=NULL;
node *Q[10];
int smallest,largest,rear=-1,fron_t=0,sum=0;
node* get_node(int value)
{
    node *newptr= new node;
    newptr->data=value;
    newptr->left=newptr->right=NULL;
    return newptr;
}
node* inser_t(int n, node*roo_t)
{
    if(roo_t==NULL)
    {
        roo_t=get_node(n);
    }
    else
        if(n<roo_t->data)
            roo_t->left=inser_t(n,roo_t->left);
        else
            roo_t->right=inser_t(n,roo_t->right);
    return roo_t;
}
void find_min(node* roo_t)
{
    if(!roo_t->left)
    {
        smallest=roo_t->data;
        return;
    }
    find_min(roo_t->left);
}
void find_max(node* roo_t)
{
    if(!roo_t->right)
    {
        largest=roo_t->data;
        return;
    }
    find_max(roo_t->right);
}
int find_height(node *roo_t)
{
    if(!roo_t)
        return -1;
    return max(find_height(roo_t->left),find_height(roo_t->right))+1 ;
}
void inorder(node *roo_t)
{
    if(!roo_t)
        return;
    inorder(roo_t->left);
    sum+=find_height(roo_t);
    inorder(roo_t->right);
}
void enqueue(node *ptr)
{
    rear++;
    Q[rear]=ptr;
}
void dequeue()
{
    cout<<Q[fron_t]->data<<endl;
    if(Q[fron_t]->left)
        enqueue(Q[fron_t]->left);
    if(Q[fron_t]->right)
        enqueue(Q[fron_t]->right);
    fron_t++;
    if(fron_t<=rear)
        dequeue();
}
void level_order(node* roo_t)
{
    enqueue(roo_t);
    dequeue();
}
node* delet_e(node *roo_t,int value)
{
    if(!roo_t)
        return roo_t;
    if(value<roo_t->data)
        roo_t->left=delet_e(roo_t->left,value);
    else if(value>roo_t->data)
        roo_t->right=delet_e(roo_t->right,value);
    else
    {
        if(roo_t->left==NULL && roo_t->right==NULL)
        {
            delete roo_t;
            roo_t=NULL;
        }
        else if(roo_t->left==NULL)
        {
            node *temp=roo_t;
            roo_t=roo_t->right;
            delete temp;
        }
        else if(roo_t->right==NULL)
        {
            node *temp=roo_t;
            roo_t=roo_t->left;
            delete temp;
        }
        else
        {
            find_min(roo_t->right);
            roo_t->data=smallest;
            roo_t->right=delet_e(roo_t->right,smallest);
        }
    }
    return roo_t;
}
void inorder_succesor(node *roo_t,int value)
{
    if(!roo_t)
        return;
    if(value<roo_t->data)
    {
        previous=roo_t;
        inorder_succesor(roo_t->left,value);
    }
    else if(value>roo_t->data)
        {
            inorder_succesor(roo_t->right,value);
        }
    else if(roo_t->right)
        {
            find_min(roo_t->right);
            cout<<smallest;
        }
        else if(previous==NULL)
                cout<<"no successor";
            else
                cout<<previous->data;
}
int main()
{
    int n,A[2001];
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>A[i];
        root = inser_t(A[i], root);
    }
    cout<<find_height(root)<<endl;
    inorder(root);
    cout<<sum;
    /*root = inser_t(10,root);
    root = inser_t(15,root);
    root = inser_t(5,root);
    root = inser_t(7,root);
    level_order(root);
    inorder_succesor(root,15);*/
    return 0;
}
