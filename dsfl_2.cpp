// impliment priority queue as adt for servicing a patient in a hospital
#include<bits/stdc++.h>
using namespace std;

typedef struct node
{
	string name;
	int priority;
	struct node *next;
}node;

class pQueue
{
	struct node *first;
	struct node *end;
public:

	pQueue(){
		first=NULL;
		end=NULL;
	}

	void inser(string naam, int pri)
	{
		node *t;
		t=new node;
		t->name=naam;
		t->priority=pri;
		t->next=NULL;

		if(first==NULL){
			t->next=NULL;
			first=t;
			end=t;
			return;
		}else if(first->priority<pri){
			t->next=first;
			first=t;
			return;
		}else{
			node *current=first;
			node *previous=first;
			while(current!=NULL){
				if(current->priority > pri)
				{
					previous=current;
					current=current->next;
				}
				else{
					t->next=previous->next;
					previous->next=t;
					return;
				}
			}
			end->next=t;
			end=t;
		}
	}

	void del()
	{
		node *current;
		current=first;

		first=first->next;
		cout<<"\nDEleted element is : "<<current->name<<" "<<current->priority<<endl;
		delete current;
	}

	void disSpecific(int pri)
	{
		node *current;
		current=first;

		while(current!=NULL){
			if(current->priority == pri){
				cout<<current->name<<" "<<current->priority<<endl;
			}
			current=current->next;
		}
	}

	void display()
	{
		node *current;
		current=first;

		if(current==NULL){
			cout<<"\n QUEUE IS EMPTY \n";
			return;
		}

		while(current){
			cout<<current->name<<" "<<current->priority<<endl;
			current=current->next;
		}
	}
};

int main()
{
	pQueue p;
	int choice;
	do{

		cout<<"\nENTER WHAT YOU WANT TO DO: \n1. INSERT \n2.DISPLAY ALL\n3.DISPLAY SPECIFIC\n4.DELETE\n5.EXIT\n ";
		cin>>choice;
		string name;
		int pri;

		switch(choice){
			case 1:
					cout<<"\n ENTER THE NAME OF PATIENT :";
					cin>>name;
					cout<<"\nENTER THE PRIORITY OF PATIENT :";
					//int pri;
					cin>>pri;
					p.inser(name,pri);
					break;
			case 2:
					p.display();
					break;
			case 3:
					cout<<"\nENTER THE PRIORITY OF THE ELEMENT YOU WANRT TOT SEARCH FOR \n";
					//int pri;
					cin>>pri;
					p.disSpecific(pri);
					break;
			case 4:
					p.del();
					break;
			case 5:
					break;
		}

	}while(choice!=5);

	return 0;
}

//        impulse_
