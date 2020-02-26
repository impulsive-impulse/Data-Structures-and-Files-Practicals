#include<bits/stdc++.h>
using namespace std;
#define COUNT 5

 bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return true;
    return false;
}

class node
{
public:
     int data;
     node *right, *left;

     node()
     {
          right=left=NULL;
     }

     node(int x){
          data=x;
          right=left=NULL;
     }
};

class stackNode
{
public:
     node* data;
     stackNode *next;

     stackNode(){
          data=NULL;
          next=NULL;
     }

     stackNode(node *t){
          data=t;
          next=NULL;
     }
};
/*
class stak
{
     int top;
     node *data[30];
public:
     stak(){
          top=-1;
     }

     int epty(){
          if(top==-1)
               return 1;
          return 0;
     }

     void push(node *t){
          data[++top]=t;
     }

     node* pop()
     {
          return data[top--];
     }
};
*/

class stak
{
     stackNode *top;
public:
     stak(){
          top=NULL;
     }

     void push(node *t){
          if(top==NULL)
               top=new stackNode(t);
          else{
               stackNode *p=new stackNode(t);
               p->next=top;
               top=p;
          }
     }

     int epty()
     {
          if(top==NULL)
               return 1;
          return 0;
     }

     node* pop()
     {
          node *t;
          if(!epty()){
               stackNode *p;
               p=top;
               if(top->next==NULL)
               {
                    t=top->data;
                    top=NULL;
                    delete p;
                    return t;
               }else{
                    t=top->data;
                    top=top->next;
                    delete p;
                    return t;
               }
          }
          return NULL;
     }
};

class bTree
{
     node *root;
public:
          node* rootNode()
          {
               return root;
          }
          void createFromPostfix(string postix){
               stak st;
               node *t,*t1,*t2;

               for(int i=0;i<postix.size();i++){
                    if(!isOperator(postix[i]))
                    {
                            t=new node(postix[i]);
                            st.push(t);
                    }else{
                            t=new node(postix[i]);
                            t1=st.pop();
                            //st.pop();
                            t2=st.pop();
                            //st.pop();

                            t->right=t1;
                            t->left=t2;
                            st.push(t);
                    }
               }
               t=st.pop();
               //st.pop();
               root=t;
          }

          void createFromPrefix(string prefix){
               stak st;
               node *t,*l,*r;

               for(int i=prefix.size()-1;i>=0;i--){
                    if(!isOperator(prefix[i])){
                         t=new node(prefix[i]);
                         st.push(t);
                    }else{
                         t=new node(prefix[i]);
                         l=st.pop();
                         //st.pop();
                         r=st.pop();
                         //st.pop();
                         t->left=l;
                         t->right=r;
                         st.push(t);
                    }
               }
               t=st.pop();
               //st.pop();
               root=t;
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
              char ch=root->data;
              cout<<ch<<"\n";

              print2D(root->left, space);
          }

          void rPreorder(node *t)
          {
               if(t!=NULL){
                    char ch=t->data;
                    cout<<" "<<ch;
                    rPreorder(t->left);
                    rPreorder(t->right);
               }
          }

          void preOrder(node *t){
               stak st;

               while(t!=NULL){
                    char ch=t->data;
                    cout<<" "<<ch;
                    st.push(t);
                    t=t->left;
               }
               while(!st.epty()){
                         t=st.pop();
                         //st.pop();
                         t=t->right;

                    while(t!=NULL){
                         char ch=t->data;
                         cout<<" "<<ch;
                         st.push(t);
                         t=t->left;
                    }
               }
          }

          void rInorder(node *t){
               if(t!=NULL){
                    rInorder(t->left);
                    char ch=t->data;
                    cout<<" "<<ch;
                    rInorder(t->right);
               }
          }

          void inOrder(node *t){
               stak st;

               while(t!=NULL){
                    st.push(t);
                    t=t->left;
               }
               while(!st.epty()){
                    t=st.pop();
                    //st.pop();
                    char ch=t->data;
                    cout<<" "<<ch;
                    t=t->right;

                    while(t!=NULL){
                         st.push(t);
                         t=t->left;
                    }
               }
          }

          void rPostorder(node *t){
               if(t!=NULL){
                    rPostorder(t->left);
                    rPostorder(t->right);
                    char ch=t->data;
                    cout<<" "<<ch;
               }
          }

          void postOrder(node *t){
               stack<node*>st;
               st.push(t);

               stack<int>out;
               while(!st.empty()){

                    node *curr=st.top();
                    st.pop();
                    out.push(curr->data);
                    if(curr->left)
                         st.push(curr->left);
                    if(curr->right)
                         st.push(curr->right);
               }

               while(!out.empty()){
                    char ch=out.top();
                    cout<<ch<<" ";
                    out.pop();
               }
          }
};

int main()
{
     bTree tree;
     string post="abc*+e*f+";
     string pre="+-ab+*cd/ef";

     int operation;
     do{
          cout<<"\nEnter what you want to do :   ";
          cout<<"\n1.Create Tree \n2.PreOrder \n3.PostOrder \n4.InOrder \n5.Display Tree \n6.Exit\n";
          cin>>operation;

          switch(operation){
          case 1:
                    int choice;
                    cout<<"\n1.From PreFix data \n2.From PostFix data \n";
                    cin>>choice;

                    switch(choice){
                    case 1:
                         cout<<"Enter PREFIX expression :  ";
                         cin>>pre;
                         tree.createFromPrefix(pre);
                         break;
                    case 2:
                         cout<<"Enter POSTFIX expression : ";
                         cin>>post;
                         tree.createFromPostfix(post);
                         break;
                    }
                    break;

          case 2:
                    cout<<"\nRECURSIVE PreOrder data :     ";
                    tree.rPreorder(tree.rootNode());
                    cout<<"\nNON-RECURSIVE PreOrder data : ";
                    tree.preOrder(tree.rootNode());
                    break;

          case 4:
                    cout<<"\nRECURSIVE InOrder data :      ";
                    tree.rInorder(tree.rootNode());
                    cout<<"\nNON-RECURSIVE InORDER data : ";
                    tree.inOrder(tree.rootNode());
                    break;

          case 3:
                    cout<<"\nRECURSIVE PostOrder data :    ";
                    tree.rPostorder(tree.rootNode());
                    cout<<"\nNON-RECURSIVE PostOrder data : ";
                    tree.postOrder(tree.rootNode());
                    break;

          case 5:
                    cout<<"\nYOUR TREE : \n";
                    tree.print2D(tree.rootNode(),0);
                    break;
          }
     }while(operation!=6);

     return 0;
}

//        _impulse
