#include<bits/stdc++.h>
using namespace std;

class node
{
public :
            int data;
            node *left,*right;

            node(int x){
                        data=x;
                        left=right=NULL;
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

class bst
{
            node *root;
public:
            bst(){
                        root=NULL;
            }

            void inserT(int x){
                        node *p,*q,*r;
                        r=new node(x);

                        if(root==NULL){
                                    root=r;
                                    return;
                        }

                        p=root;
                        while(p!=NULL){
                                    q=p;
                                    if(x>p->data)
                                                p=p->right;
                                    else if(x<p->data)
                                                p=p->left;
                                   else{
                                        cout<<"\nElement already exists in tree!! \n";
                                        return;
                                   }
                        }

                        if(x>q->data)
                                    q->right=r;
                        else
                                    q->left=r;

            }

            void create(){
                        int n,x,i;
                        root=NULL;
                        cout<<"\nEnter -1 to terminate ";
                        cout<<"\nEnter tree values : ";

                        while(true)
                        {
                             cin>>n;
                             if(n==-1)
                              break;

                             inserT(n);
                        }
            }

            node *del(node *t,int x){
                        node *temp;
                        if(t==NULL){
                                    cout<<"\nElement not found";
                                    return t;
                        }

                        if(x<t->data){
                                    t->left=del(t->left,x);
                                    return t;
                        }

                        if(x>t->data){
                                    t->right=del(t->right,x);
                                    return t;
                        }

                        if(t->left==NULL && t->right==NULL){          // leaf
                                    temp=t;
                                    delete temp;
                                    return NULL;
                        }

                        if(t->left==NULL){
                                    //temp=t;
                                    temp=t->right;
                                    delete t;
                                    return temp;
                        }

                        if(t->right==NULL){
                                    //temp=t;
                                    temp=t->left;
                                    delete t;
                                    return temp;
                        }

                        temp=t->right;
                        while(temp->left!=NULL)
                                    temp=temp->left;


                        t->data=temp->data;
                        t->right=del(t->right,temp->data);
                        return t;
            }

            void deletE(int x){
                    root=del(root,x);
                    cout<<"\nDelete Successful";
            }

            node *serch(int x){
                        node *t=root;
                        while(t!=NULL){
                                    if(x==t->data)
                                                return t;
                                    if(x>root->data)
                                                t=t->right;
                                    else
                                                t=t->left;
                        }
                        return NULL;
            }

            void levelOrderTraversal(){
                        q q1,q2;
                        node *p1;
                        node *t=root;

                        if(t==NULL)
                                    return;
                        q1.enter(t);
                        cout<<"\n "<<t->data;

                        while(!q1.epty()){
                                    cout<<"\n";
                                    while(!q1.epty()){
                                                p1=q1.delet();
                                                if(p1->left!=NULL){
                                                            //q1.enter(p1->left);
                                                            q2.enter(p1->left);
                                                            cout<<" "<<p1->left->data;
                                                }

                                                if(p1->right!=NULL){
                                                            //q1.enter(p1->right);
                                                            q2.enter(p1->right);
                                                            cout<<" "<<p1->right->data;
                                                }
                                    }
                                    q1=q2;
                                    q2.trash();
                        }
            }

            node *mirror(node *t){
               node *p;
               if(t!=NULL)
               {
                    p=t->left;
                    t->left=mirror(t->right);
                    t->right=mirror(p);
               }
               return t;
            }

            void swapTree(){
               root=mirror(root);
            }
};

int main()
{
            bst tree;
            node *p;
            int x,operation;

            do{
                        cout<<"\n\n1.Create \n2.Delete \n3.Search \n4.Level Order Display \n5.Mirror tree \n6.Insert \n7.Exit\n";
                        cin>>operation;

                        switch(operation)
                        {
                              case 1:   tree.create();
                                        break;

                              case 2:
                                        cout<<"\nEnter the key to be deleted : ";
                                        cin>>x;
                                        tree.deletE(x);
                                        break;
                              case 3:
                                        cout<<"\nEnter the key to be searched : ";
                                        cin>>x;
                                        p=tree.serch(x);

                                        if(p==NULL)
                                             cout<<"\n**NOT Found**";
                                        else
                                             cout<<"\n**Element Found**";
                                        break;
                              case 4:
                                        tree.levelOrderTraversal();
                                        break;
                              case 5:
                                        tree.swapTree();
                                        tree.levelOrderTraversal();
                                        tree.swapTree();
                                        break;

                              case 6:
                                        int x;
                                        cout<<"\nEnter the value to bew inserted :";
                                        cin>>x;
                                        tree.inserT(x);
                                        break;


                        }
            }while(operation!=7);
}

//            _impulse
