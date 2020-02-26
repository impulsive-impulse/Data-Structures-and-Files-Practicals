#include<bits/stdc++.h>
#include<string.h>
using namespace std;
struct node
{
    char data;
    struct node *next;
};

class stac
{
    struct node *top;
    public:
        stac()
        {
            top=NULL;
        }

        void push(char data)
        {
            struct node *ptr;
            struct node *temp;
                ptr=new node;
                ptr->data=data;
                ptr->next=NULL;
                if(top==NULL)
                {
                    top=ptr;
                }
                else
                {
                    ptr->next=top;
                    top=ptr;
                }
        }

        char pop()
        {
            char temp;
            if(!isempty())
            {
                struct node *ptr;
                ptr=top;
                if(top->next==NULL)
                {
                    temp=top->data;
                    top=NULL;
                    delete ptr;
                    return temp;
                }
                else
                {
                    temp=top->data;
                    top=top->next;
                    delete ptr;
                    return temp;
                }
            }
        }

        char peek()
        {
            if(!isempty())
            {
                return top->data;
            }
        }

        bool isempty()
        {
            if(top==NULL)
                return true;
            else
                return false;
        }
};

int priority(char x)
{
            if(x=='-')
                return 1;
            else if(x=='+')
                return 2;
            else if(x=='*')
                return 3;
            else
                return 4;
}

void postfix(char infix[], char post[])
{
    int i=0,j=0,top=-1,val1,val2,x;
    char temp,te;
    stac s;
    for(i=0;infix[i]!='\0';i++)
    {
        if(infix[i]==40)
        {
            s.push(infix[i]);
            top++;
        }
        else if(isalpha(infix[i]))
        {
            post[j]=infix[i];
            j++;
        }
        else if(infix[i]=='-' || infix[i]=='+' || infix[i]=='*' || infix[i]=='/')
        {
            te=s.peek();
            if(top==-1 || te==40)
            {
                s.push(infix[i]);
                top++;
            }
            else
            {
                temp=s.pop();
                top--;
                val1=priority(temp);
                val2=priority(infix[i]);
                if(val1>val2)
                {
                    post[j]=temp;
                    j++;
                    s.push(infix[i]);
                    top++;
                }
                else
                {
                    s.push(temp);
                    top++;
                    s.push(infix[i]);
                    top++;
                }
            }
        }
        else if(infix[i]==41)
        {
            while(1)
            {
                temp=s.pop();
                top--;
                if(temp==40)
                    break;
                post[j]=temp;
                j++;
            }
        }
    }
    while(!s.isempty())
    {
        post[j]=s.pop();
        top--;
        j++;
    }
    post[j]='\0';
}

void prefix(char infix[],char pre[])
{
    int i,l1,l2,j;
    char in[100],pref[100];
    strrev(infix);
    for(i=0;infix[i]!='\0';i++)
    {
        if(infix[i]==40)
        {
            infix[i]=41;
        }
        else if(infix[i]==41)
        {
            infix[i]=40;
        }
    }
    postfix(infix,pre);
    strrev(pre);
}

int operation(int op1,int op2,char op)
{
    if(op=='-')
        return op1-op2;
    else if(op=='+')
        return op1+op2;
    else if(op=='*')
        return op1*op2;
    else
        return op1/op2;
}

int post_evaluation(char pos[])
{
    int i,res,op1,op2;
    stac s;
    for(i=0;pos[i]!='\0';i++)
    {
        if(pos[i]>='0' && pos[i]<='9')
            s.push(pos[i]-48);
        else
        {
            op2=s.pop();
            op1=s.pop();
            res=operation(op1,op2,pos[i]);
            s.push(res);
        }
    }
    return s.pop();
}

int pre_evaluation(char pre[])
{
    int i,res,op1,op2;
    stac s;
    strrev(pre);
    for(i=0;pre[i]!='\0';i++)
    {
        if(pre[i]>='0' && pre[i]<='9')
            s.push(pre[i]-48);
        else
        {
            op1=s.pop();
            op2=s.pop();
            res=operation(op1,op2,pre[i]);
            s.push(res);
        }
    }
    return s.pop();
}

int main()
{
    char s1[100],s2[100];
    int ans;
    int ch,i;
    do
    {   cout<<"\nENTER YOUR CHOICE :\n";
        cout<<"\n1.INFIX TO POSTFIX CONVERSION\n2.INFIX TO PREFIX CONVERSION\n3.POSTFIX EVALUATION\n4.PREFIX EVALUATION\n5.EXIT\n ";
        cin>>ch;
        switch(ch)
        {
            case 1: cout<<"\nENTER THE EXPRESSION: ";
                    cin>>s1;
                    postfix(s1,s2);
                    cout<<"\nPOSTFIX EXPRESSION: ";
                    for(i=0;s2[i]!='\0';i++)
                    {
                        cout<<s2[i];
                    }
                    break;

            case 2: cout<<"\nENTER THE EXPRESSION: ";
                    cin>>s1;
                    prefix(s1,s2);
                    cout<<"\nPREFIX EXPRESSION IS: ";
                    for(i=0;s2[i]!='\0';i++)
                    {
                        cout<<s2[i];
                    }
                    break;

            case 3: cout<<"\nENTER THE EXPRESSION: ";
                    cin>>s1;
                    ans=post_evaluation(s1);
                    cout<<"\nRESULT : "<<ans;
                    break;

            case 4: cout<<"\nENTER THE EXPRESSION: ";
                    cin>>s1;
                    ans=pre_evaluation(s1);
                    cout<<"\nRESULT : "<<ans;
                    break;
        }
    }while(ch!=5);
}
