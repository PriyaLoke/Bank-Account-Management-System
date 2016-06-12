//Shanmukha Priya Loke
//December 13th, 2015
#include<string>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<time.h>
#include<cstdlib>
#include "bankAccount_priya.h"
#include "account_priya.h"
using namespace std;

bankAccount::bankAccount() //constructor
{

}

bankAccount::~bankAccount() //destructor
{

}

string bankAccount::getDate() //fucntion to print the date
{
    char dateStr[9];
    _strdate_s(dateStr);
    return dateStr;
}

float bankAccount::view_balance() //function to print the cash_balance
{
    cout<<"Your account balance is "<<cash_balance<<"$\n";
    return cash_balance;
}

void bankAccount::deposit_bank(float money) //function to deposit money into bank account
{
    cash_balance+=money;
    cout<<"Your cash balance after depositing "<<money<<"$ is "<<cash_balance<<"$"<<endl;

	//writing the transaction to the history / log file
    ofstream myfile;
    myfile.open("bank_transaction_history.txt",ios::app);
    if(myfile.is_open())
    {
        myfile.eof();
        myfile<<"\nDeposit\t\t$"<<money<<"\t"<<getDate()<<"\t$"<<cash_balance<<endl;
    }
    else
    {
        cout<<"Cannot record this transaction. File opening failed.\n";
    }
}

void bankAccount::withdraw_bank(float money) //function to withdraw money from the bank account
{
    if(money<cash_balance)
    {
        cash_balance-=money;
        cout<<"Your cash balance after withdrawal of "<<money<<"$ is "<<cash_balance<<"$"<<endl;

		//writing the transaction to the history / log file
        ofstream myfile;
        myfile.open("bank_transaction_history.txt",ios::app);
        if(myfile.is_open())
        {
            myfile<<"\nWithdrawal\t$"<<money<<"\t"<<getDate()<<"\t"<<cash_balance<<endl;
        }
        else
        {
            cout<<"Cannot record this transaction. File opening failed.\n";
        }
    }
    else
        cout<<"Transaction failed. Insufficient balance\n"; //if balance not sufficient to withdraw
}

void bankAccount::print_bankHistory() //function to print transactions of the bank account
{
    ifstream myfile;
    string line;
    myfile.open("bank_transaction_history.txt",ios::app);
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

float bankAccount::getBalance()
{
	return cash_balance;
}

void bankAccount::setBalance(float blnc)
{
	cash_balance=blnc;
}



