#include<bits/stdc++.h>
using namespace std;
#define COUNT 10

class node
{
public :
            int data;
            node *left,*right;

            node(int x){
                        data=x;
                        left=right=NULL;
            }

            node()
            {
                 left=right=NULL;
            }
};

class qNode
{
public:
     node *data;
     qNode *next;

     qNode()
     {
          data=NULL;
          next=NULL;
     }

     qNode(node *t)
     {
          data=t;
          next=NULL;
     }
};

/*
class q
{
            node* data[30];
            int r,f;
public:
            q(){
            r=f=-1;}

            int epty(){
                        if(r==-1)
                                    return 1;
                        return 0;
            }

            void enter(node *p)
            {
                        if(epty())
                                    r=f=0;
                        else
                                    r++;
                        data[r]=p;
            }

            node* delet(){
                        node *p=data[f];
                        if(r==f)
                                    r=f=-1;
                        else
                                    f++;
                        return p;
            }

            void trash()
            {
                 r=f=-1;
            }
};
*/

class q
{
     qNode *f,*r;
public:
     q()
     {
          f=r=NULL;
     }

     int epty()
     {
          if(f==NULL)
               return 1;
          return 0;
     }

     void enter(node *p){
          qNode *t=new qNode(p);

          if(epty()){
               f=r=t;
          }else{
               r->next=t;
               r=r->next;
          }
     }

     node *delet()
     {
          node *t;
          t=f->data;
          qNode *p=f;
          f=f->next;

          if(f==NULL)
               r=NULL;
          delete p;
          return t;
     }

     void trash()
     {
          f=r=NULL;
     }
};

class bTree
{
     node *root;
public:
     bTree(){
          root=NULL;
     }

     bTree(node *t){
          root=t;
     }

     node* treeRoot(){
          return root;
     }

     void inserT(int key)
     {
          q que;
          node *t =root;
          que.enter(t);
          while(!que.epty())
          {
               node *temp=que.delet();
               if(!temp->left){
                    temp->left=new node(key);
                    break;
               }else
                    que.enter(temp->left);

               if(!temp->right){
                    temp->right=new node(key);
                    break;
               }else
                    que.enter(temp->right);
          }
     }

     node *create(){
         node *p;
         int x;
         cout<<"\nEnter data or -1 for ending tree creation : ";
         cin>>x;

         if(x==-1)
               return NULL;
         p=new node(x);

         cout<<"\nEnter left child of "<<x;
         p->left=create();
         cout<<"\nEnter right child of "<<x;
         p->right=create();
         return p;
     }

     void create2(){
          root=create();
     }

     void print2D(node *root, int space)
     {
          if (root == NULL)
               return;
         space += COUNT;

         print2D(root->right, space);
         cout<<endl;

         for (int i = COUNT; i < space; i++)
             cout<<" ";
         cout<<root->data<<"\n";

         print2D(root->left, space);
     }

     int rDot(node *t){
          int hl,hr;

          if(t->left==NULL && t->right==NULL)
               return 1;

          hl=rDot(t->left);
          hr=rDot(t->right);

          if(hr>hl)
               return hr+1;
          return hl+1;
     }

     int dot(node *t){
          if(t==NULL)
               return 0;

          queue<node*>q;
          q.push(t);
          int ctr=0;

          while(true){

               int count1=q.size();
               if(count1==0)
                    return ctr;
               ctr++;
               while(count1>0){
                    node* temp=q.front();
                    q.pop();
                    if(temp->left!=NULL)
                         q.push(temp->left);
                    if(temp->right!=NULL)
                         q.push(temp->right);
                    count1--;
               }
          }
     }

     int leaves(node *t){
          int i;
          if(t==NULL)
               return 0;
          if(t->left==NULL && t->right==NULL)
               return 1;

          i=leaves(t->left)+leaves(t->right);
          return i;
     }

     node *copyTree(node *t){
          node *p;
          p=NULL;

          if(t!=NULL)
          {
               p =new node;
               p->data=t->data;
               p->left=copyTree(t->left);
               p->right=copyTree(t->right);
          }
          return p;
     }
};

int main()
{
     bTree tree;

     int x,operation;

     do{
          cout<<"\nEnter what you want to do : \n"
          <<"1.Create \n2.Insert \n3.Display \n4.Depth of tree \n5.Display leaf nodes \n6.Create copy of tree \n7.Exit\n";
          cin>>operation;

          switch(operation)
          {
          case 1:
                    tree.create2();
                    break;

          case 2:
                    int key;
                    cout<<"\nEnter value to be inserted : ";
                    cin>>key;
                    tree.inserT(key);
                    break;

          case 3:
                    tree.print2D(tree.treeRoot(),0);
                    break;

          case 4:
                    cout<<endl<<"Depth of your tree is : "<<tree.dot(tree.treeRoot())-1;
                    break;
          case 5:
                    cout<<endl<<"Number of leaf nodes in your tree are : "<<tree.leaves(tree.treeRoot());
                    break;
          case 6:
                    node *t;
                    t=tree.copyTree(tree.treeRoot());
                    bTree tree2(t);
                    tree2.print2D(t,0);
                    break;
          }
     }while(operation!=7);

     return 0;
}

//   _impulse
