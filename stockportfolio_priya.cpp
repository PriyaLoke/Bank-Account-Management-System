//Shanmukha Priya Loke
//December 13th, 2015
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>

#include "stockportfolio_priya.h"
using namespace std;

float stockaccount::total_portfolio_value=0; //initializing the static variable

stockaccount::stockaccount()//constructor
{
	firstPtr=0;
	lastPtr=0;
}

string stockaccount::getTime() //function to print the system time
{
    char timeStr[9];
    _strtime_s(timeStr);
    //cout<<"The current time is "<<timeStr;
    return timeStr;
}

void stockaccount::display() //function to display the value of a stock
{
    int i;
    string symb;
    cout<<"Please enter the stock symbol: ";
    cin>>symb;
    fstream myfile; //creating a stream object
    string line,sub;
    bool stock=false;

	//to pick one of the two available files
    i=rand()%2;
    if(i==0)
	{
        myfile.open("Results_1.txt");
	}
    else
    {
        myfile.open("Results_2.txt");
    }
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iss(line); //constructing an istringstream object
            float val;
            while(iss>>sub>>val)
            {
                if(sub==symb)
                {
                    cout<<"\nCompany-Symbol\tPrice Per Share\n";
                    cout<<"     "<<sub<<"\t      $"<<val<<endl;
                    stock=true;
                    break;
                }
            }
        }
    }
    if(stock==false)
    {
        cout<<"The symbol you entered is not present in the file. Please enter a valid symbol."<<endl;
    }

}

void stockaccount::current_portfolio() //function that displays the current portfolio
{
    cout<<"Current cash balance = $"<<cash_balance<<"\n";
    ListNode *ptr4=firstPtr;
    string sym;
    int num=0;
    float sum=0;
    if(ptr4==0) // condition that checks if portfolio is empty
	{
		cout<<"\nNo stocks to display\n";
		return;
	}
	else
    {
        cout<<"\nCompanySymbol\tNumber\tPricePerShare\tTotalValue\n";
        while(ptr4!=0)
        {
            sym=ptr4->symbol;
            num=ptr4->number;
            if(num!=0)
            {
            cout<<sym<<"\t\t"<<num<<"\t";

            fstream myfile; //creating an fstream object
            string line,sub;

			//picking one value from the 2 files
            int i=rand()%2;
            if(i==0)
            {
                myfile.open("Results_1.txt");
            }
            else
            {
                myfile.open("Results_2.txt");
            }
            if(myfile.is_open())
            {
                while(getline(myfile,line))
                {
                    istringstream iss(line); //constructing an istringstream object
                    float val;
                    while(iss>>sub>>val)
                    {
                      if(sub==sym)
                      {
                          float tot=num*val;
                          cout<<"$"<<val<<"\t\t"<<"$"<<tot<<"\n";
                          sum=sum+tot; //sums up the values of all the shares 
                          //break;
                      }
                    }
                }

            }
            }

            ptr4=ptr4->next;
        }
    }
	total_portfolio_value=sum+cash_balance; //to find out the total value of the portfolio
    cout<<"\nTotal portfolio value : $"<<total_portfolio_value<<endl;
}

void stockaccount::buy_shares() //function to buy shares
{
    string symb;
    int num;
    float max_pershare;
    time_t seconds;
    seconds=time(NULL);
    struct tm *timeinfo;
	timeinfo=localtime(&seconds);
    bool stock=false;
    bool available=false;

    cout<<"Please enter the ticker symbol of the stock you want to buy: "<<endl;
    cin>>symb;
    cout<<"Please enter the number of shares you want to buy: "<<endl;
    cin>>num;
    cout<<"Please enter the maximum amount you are willing to pay for each share of the stock: "<<endl;
    cin>>max_pershare;

    fstream myfile; //creating an fstream object
    string line,sub;

	//to randomly pick one of the 2 files to read the values
    int i=rand()%2;
    if(i==0)
	{
        myfile.open("Results_1.txt");
	}
    else
    {
        myfile.open("Results_2.txt");
    }
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iss(line); //constructing an istringstream object
            float val;

            while(iss>>sub>>val)
            {
                if(sub==symb)
                {
                available=true;
                if(max_pershare>val) //checking if the user is willing to pay as much as the stock costs
                {
                    cout<<"The current value of each share is: $"<<val<<endl;
                    float total_val=num*val;
                    if(total_val>cash_balance)
                    {
                        cout<<"Transaction failed. Insufficient balance in your account.\n";
                    }
                    else
                    {
                    ofstream myfile;
                    myfile.open("stock_transaction_history.txt",ios::app); //append to existing history / log file
                    if(myfile.is_open())
                    {
                        myfile<<"Buy\t";
                        myfile<<symb<<"\t";
                        myfile<<num<<"\t";
                        myfile<<"$"<<val<<"\t";
                        myfile<<"$"<<total_val<<"\t";
                        myfile<<getTime()<<endl;
                        myfile.close();
                    }
                    else
                    {
                       cout<<"Transaction failed. Unable to open file"<<endl;
                       break;
                    }

                    ofstream myfile2;
                    myfile2.open("bank_transaction_history.txt",ios::app); //recording the transaction in bank account
                    if(myfile2.is_open())
                    {
                        myfile2<<"\nWithdrawal\t$"<<total_val<<"\t";
                    }
                    else
                    {
                        cout<<"Cannot record this transaction. File opening failed.\n";
                    }

                    cout<<"Buy\t";
                    cout<<symb<<"\t";
                    cout<<num<<"\t";
                    cout<<"$"<<val<<"\t";
                    cout<<"$"<<total_val<<endl;

                    cash_balance=cash_balance-total_val; //to deduct the amount spent in buying from the bank account
                    cout<<"Cash Balance = $"<<cash_balance<<endl;

                    ListNode *ptr=firstPtr;
                    while(ptr!=0)
                    {
                        if(ptr->symbol==symb) //if the node corresponding to the portfolio exists
                        {
                            ptr->number=num+ptr->number; //adding the number of shares currently bought to already existing shares
                            stock=true;
                            break;
                        }
                        ptr=ptr->next;
                    }
                    if(stock==false) //if a new stock is bought
                    {
                        cout<<"creating a new node for "<<symb<<endl;
                        ListNode *newNode=new ListNode(symb,num);
                        addNode(newNode);
                    }
                    break;
                    }

                }
                else
                {
                    cout<<"Transaction failed. The maximum amount entered is less than the price of the stock"<<endl;
                    break;
                }
                }

            }
        }
    }

    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to buy is not available\n";
    }
}

void stockaccount::addNode(ListNode *newNode) //function to add a new node to a list
{
    if(firstPtr==0)
    {
        firstPtr=lastPtr=newNode;
    }
    else
    {
       // cout<<"adding "<<newNode->symbol;
        newNode->next=firstPtr;
        firstPtr->prev=newNode;
        firstPtr=newNode;
        newNode->prev=NULL;
    }
}

void stockaccount::sell_shares() //function that implements selling of shares
{
    string symb2;
    int num;
    float min_pershare;
    bool available=false;
    if(firstPtr!=0)
    {
    cout<<"Please enter the ticker symbol of the stock you wish to sell: "<<endl;
    cin>>symb2;
	cout<<"Please enter the number of shares you wish to sell: "<<endl;
	cin>>num;
	cout<<"Please enter the minimum amount you want to sell each share of the stock for: "<<endl;
	cin>>min_pershare;

    fstream myfile; //creating a stream object
    string line,sub;

	//randomly choosing one of the 2 files
    int i=rand()%2;
    if(i==0)
	{
        myfile.open("Results_1.txt");
	}
    else
    {
        myfile.open("Results_2.txt");
    }
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iss(line); //constructing an istringstream object
            float val;
            while(iss>>sub>>val)
            {
                ListNode *index=firstPtr;
                while(index!=0)
                {
                if(sub==symb2&&index->symbol==symb2) //checking if the stock actually exists in the portfolio
                {
                    available=true;
                    if(index->number<num) //to check if there are sufficient shares
                    {
                        cout<<"Transaction failed. You do not have enough shares to sell.\n";
                    }
                    else
                    {
                    if(min_pershare<val) 
                    {
                        float total_val=num*val;
                        ofstream myfile_in;
                        myfile_in.open("stock_transaction_history.txt",ios::app); //recording a transaction in the history file
                        if(myfile_in.is_open())
                        {
                            myfile_in<<"Sell\t";
                            myfile_in<<symb2<<"\t";
                            myfile_in<<num<<"\t";
                            myfile_in<<"$"<<val<<"\t";
                            myfile_in<<"$"<<total_val<<"\t";
                            myfile_in<<getTime()<<endl;
                            myfile_in.close();
                        }
                        else
                        {
                            cout<<"Transaction failed. Unable to open file"<<endl;
                            break;
                        }

                        ofstream myfile3;
                        myfile3.open("bank_transaction_history.txt",ios::app); //recording the transaction in the bank account
                        if(myfile3.is_open())
                        {
                            myfile3<<"\nDeposit\t\t$"<<total_val<<"\t";
                        }
                        else
                        {
                            cout<<"Cannot record this transaction. File opening failed.\n";
                        }

                        cout<<"Sell\t";
                        cout<<symb2<<"\t";
                        cout<<num<<"\t";
                        cout<<"$"<<val<<"\t";
                        cout<<"$"<<total_val<<endl;

                        cash_balance=cash_balance+total_val; //increasing the cash balance by the amount obtained from selling shares
                        cout<<"Cash Balance="<<cash_balance<<endl;

                        ListNode *ptr=firstPtr;
                        while(ptr!=0)
                        {
                            if(ptr->symbol==symb2)
                            {
                                ptr->number=ptr->number-num;
                                if(ptr->number==0) //if the total number of shares becomes zero after selling, delete the node
                                {
                                    delNode(symb2);
                                }
                            }
                            ptr=ptr->next;
                        }
                    }
                    else
                    {
                        cout<<"Transaction failed. The amount you entered is greater than the price of the stock"<<endl;
                    }
                    }

                }
                index=index->next;
                }
            }
        }
    }
    if(available==false)
    {
        cout<<"Transaction failed. The stock you want to sell is not available\n";
    }
    }
    else
        cout<<"You have no shares to sell\n";

}

void stockaccount::delNode(string node) //function to delete node when value is zero
{
    cout<<"entering into delete\n";
    ListNode *ptr=firstPtr;
    ListNode *temp1=0;
    ListNode *temp2=0;
    if(firstPtr==0)
    {
        cout<<"Stock not found\n";
    }
    while(ptr!=0) //loop to find the node to be deleted
    {
        if(ptr->symbol==node)
        {
            break;
        }
        else
        {
            ptr=ptr->next;
        }
    }
    temp1=ptr->prev; //using temporary ptrs for the previous and next node of the node to be deleted
    temp2=ptr->next;
    if(ptr==0)
    {
        cout<<"Stock not found\n";
    }
    else
    {
        if(ptr==firstPtr)
        {
            if(ptr==lastPtr)
            {
                cout<<"Selling the last stock you own\n";
                firstPtr=lastPtr=0;
            }
            else
                firstPtr=firstPtr->next;

        }
        else
        {
            temp1->next=ptr->next;
            temp2->prev=ptr->prev;
        }
        delete ptr;
    }

}

void stockaccount::transac_history()
{
    ifstream myfile;
    string line;
    myfile.open("stock_transaction_history.txt");
    if(myfile.is_open())
    {
        while(!myfile.eof())
        {
            getline(myfile,line);
            cout<<line<<endl;
        }
        myfile.close();
    }
    else
        cout<<"Error in opening the file.\n";
}

float stockaccount::getBalance()
{
    return cash_balance;
}

void stockaccount::setBalance(float blnc)
{
    cash_balance=blnc;
}

void stockaccount::update_stocks() //for updating the values of stocks bought
{
    bool stock=false;
    ifstream myfile;
    myfile.open("stock_transaction_history.txt");
    string line,event,stock_symb,date;
    int number_shares;
    float value_perShare, total_value;
    while(getline(myfile,line))
    {
        istringstream iss(line);
		if (myfile.eof())
			break;
        while(iss>>event>>stock_symb>>number_shares>>value_perShare>>total_value>>date)
        {

            if(event=="Buy") //if there is a transaction of buy
            {
               // cout<<"First ptr is "<<firstPtr->symbol<<endl;
                ListNode *ptr=firstPtr;
                //stock=true;
                while(ptr!=0)
                {
                    if(ptr->symbol==stock_symb)
                    {
                        stock=true;
                        ptr->number=number_shares+ptr->number;
                       // cout<<"Printing after adding "<<ptr->symbol<<"\n";
                       // cout<<ptr->symbol<<"\t"<<ptr->number<<endl;
                    }
                    else
                        stock=false;
                    ptr=ptr->next;
                }
                if(stock==false)
                {
                   // cout<<"creating "<<stock_symb<<endl;

                    ListNode *newNode=new ListNode(stock_symb,number_shares);
                    addNode(newNode); //adding a new node
                }
		
            }
            else if(event=="Sell")
            {
			
				ListNode *ptr5=firstPtr;
                stock=false;
                while(ptr5!=0)
                {
                    if(ptr5->symbol==stock_symb)
                    {
                        stock=true;
                        ptr5->number=ptr5->number-number_shares;
                        if(ptr5->number==0)
                        {
                            delNode(stock_symb);
                        }
                    }
                    ptr5=ptr5->next;
                }
              /*  if(stock==false)
                {
                    cout<<"You do not have shares of this stock in your portfolio.\n";
                }*/
            }
	
        }
	

    }
}

ListNode *stockaccount::sortList(ListNode *first,ListNode *second)
{
    if(!first) // if first linked list is empty
        return second;
    if(!second) // if second linked list is empty
        return first;

    ifstream myfile;
    string line,sub;
    float temp_value1,temp_value2;
    //ListNode *current=firstPtr;

    int j=rand()%2;
    if(j==0)
    {
        myfile.open("Results_1.txt");
    }
    else
    {
        myfile.open("Results_2.txt");
    }
    while(getline(myfile,line))
    {
        istringstream iss(line); //constructing an istringstream object
        float val;

        while(iss>>sub>>val)
        {
            if(sub==first->symbol)
            {
                temp_value1=val;
                //cout<<"Found temp1 "<<temp_value1<<"\n";
            }
            if(sub==second->symbol)
            {
                temp_value2=val;
                //cout<<"Found temp2 "<<temp_value2<<"\n";
            }
        }

    }

    if(((first->number)*temp_value1) > ((second->number)*temp_value2)) //to check the total value of all the shares
    {
       // cout<<"Correct\n";
        first->next=sortList(first->next,second);
        first->next->prev = first;
        first->prev = NULL;
       // cout<<"returning... \n";
        return first;
    }
    else
    {
       // cout<<"Wrong\n";
        second->next = sortList(first,second->next);
       // cout<<"Pass"<<endl;
        second->next->prev = second;
        second->prev = NULL;
       // cout<<"Returning\n";
        return second;
    }

}

ListNode *stockaccount::split(ListNode *first) //function to split the DLL recursively
{
    ListNode *temp1=first;
    ListNode *temp2=first;
    ListNode *temp;

    while(temp1->next&&temp1->next->next)
    {
        temp1=temp1->next->next;
        temp2=temp2->next;
    }
    temp=temp2->next;
    temp2->next=NULL;
    return temp;
}

ListNode *stockaccount::merge_sort(ListNode *firstN) //function to perform merge sort
{
    if(!firstN || !firstN->next)
    {
        return firstN;
    }
    ListNode *second=split(firstN);
    firstN=merge_sort(firstN);
    second=merge_sort(second);

    return sortList(firstN,second);
}

void stockaccount::sort_wrapper() //wrapper function for merge sort
{
    if(firstPtr==0)
    {

    }
    else
    {
        //cout<<"firstptr is "<<firstPtr->symbol<<endl;
        firstPtr=merge_sort(firstPtr);
    }

}


