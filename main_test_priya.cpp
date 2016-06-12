//Shanmukha Priya Loke
//December 13th, 2015

//header files required to connect to matlab
/*#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
#include<engine.h> */

#include<iostream>
#include<cstdlib>
#include<stdlib.h>
#include<string>
#include<fstream>
#include<sstream>
#include<time.h>


#include "account_priya.h"
#include "stockportfolio_priya.h"
#include "bankAccount_priya.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
/*
#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib") */

int main()
{
    
	/*Engine *ep; //creating an engine
	ep = engOpen(NULL);
	if (ep == NULL)
	{
		std::cout << "Error: NOT FOUND!" << endl;
		exit(1);
	} */
    int choice=999,s_choice=999,b_choice=999;
    float deposit, withdraw;
	int length = 0;
	int value = 0;
	double array_1[100]; //arrays for plotting
	double array_2[100];
    stockaccount stk_obj; //creating objects of bankaccount and stockaccount
    bankAccount bank_obj;

    fstream myfile;
    string line;
    float sub;
    myfile.open("cash_balance.txt"); //copying the cash balance from the text file that has the closing value from previous run
    if(myfile.is_open())
    {
        while(getline(myfile,line))
        {
            istringstream iss(line);
            while(iss>>sub)
            {
                account::cash_balance=sub;
            }
        }
    }
    else
        cout<<"Error in opening the file\n";

    //cout<<"Cash balance at the beginning is "<<account::cash_balance<<"$\n";

    stk_obj.update_stocks(); //updating the stocks from previous transactions
    stk_obj.current_portfolio(); //priting the current portfolio
    //cout<<"Sorting....."<<endl;
    //stk_obj.sort_wrapper(); //function for sorting the portfolio
    while(choice!=3)
    {
        cout<<"Welcome to the Account Management System.\n";
        cout<<"Please select an account to access: \n1. Stock Portfolio Account \n2. Bank Account \n3. Exit";
        cout<<"\nOption: ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            {
            cout<<"\nStock Portfolio Account \nPlease select an option: \n1. Display the price for a stock symbol";
            cout<<"\n2. Display the current portfolio \n3. Buy shares \n4. Sell shares \n5. View a graph for the portfolio value";
            cout<<"\n6. View transaction history \n7. Return to previous menu \n";
            cout<<"\nOption: ";
            cin>>s_choice;

            while(s_choice!=7)
            {
				switch (s_choice)
				{
				case 1:
					stk_obj.display(); //function to display current value of stock
					break;
				case 2:
					stk_obj.sort_wrapper(); //function for sorting the portfolio
					stk_obj.current_portfolio();
					break;
				case 3:
					stk_obj.buy_shares(); //function to buy shares
					break;
				case 4:
					stk_obj.sell_shares(); //function to sell shares
					break;
				case 5: //for plotting the graph of changing portfolio 
			/*	{
					
					fstream file("total_portfolio_value.txt", ios::in);
					string line;
					while (getline(file, line))
					{
						istringstream iss(line);
						double no;
						while (iss >> no)
						{
							array_1[length] = no;
							array_2[value] = length + 1;
							length = length + 1;
							value = value + 1;
						}
					}
					for (int i = 0; i < length; i++)
					{
						cout << (double)array_1[i] << endl;
					}
					for (int j = 0; j < length; j++)
					{
						cout << (double)array_2[j] << endl;
					}

					mxArray *A = NULL;//Creating mxArray
					A = mxCreateDoubleMatrix(1, length, mxREAL);
					memcpy((void *)mxGetPr(A), (void *)array_1, sizeof(array_1));
					engPutVariable(ep, "x", A);

					mxArray *B = NULL;//Creating mxArray
					B = mxCreateDoubleMatrix(1, length, mxREAL);
					memcpy((void *)mxGetPr(B), (void *)array_2, sizeof(array_2));
					engPutVariable(ep, "y", B);

					engEvalString(ep, "A1=y;");
					engEvalString(ep, "B1=x;");
					engEvalString(ep, "plot(A1,B1);");//plotting in MATLAB
					engEvalString(ep, "xlabel('Number of transactions');");
					engEvalString(ep, "ylabel('Total portfolio value');");
					engEvalString(ep, "title('Change in total portfolio value');");
				}*/
                break; 
            case 6:
                stk_obj.transac_history();
                break;
            case 7:
                break;
            default:
                cout<<"Please enter a number in between 1 and 7"<<endl;
                break;
            }
            cout<<"\nStock Portfolio Account \nPlease select an option: \n1. Display the price for a stock symbol";
            cout<<"\n2. Display the current portfolio \n3. Buy shares \n4. Sell shares \n5. View a graph for the portfolio value";
            cout<<"\n6. View transaction history \n7. Return to previous menu \n";
            cout<<"\nOption: ";
            cin>>s_choice;
            }
            }
            break;


        case 2:
            {
            cout<<"\nBank Account \nPlease select an option: \n1. View account balance \n2. Deposit money \n3. Withdraw money";
            cout<<"\n4. Print out history \n5. Return to previous menu"<<endl;
            cout<<"\nOption: ";
            cin>>b_choice;
            while(b_choice!=5)
            {
            switch(b_choice)
            {
            case 1:
                bank_obj.view_balance();
                break;
            case 2:
                cout<<"Please enter the amount you wish to deposit: ";
                cin>>deposit;
                bank_obj.deposit_bank(deposit);
                break;
            case 3:
                cout<<"Please enter the amount you wish to withdraw: ";
                cin>>withdraw;
                bank_obj.withdraw_bank(withdraw);
                break;
            case 4:
                bank_obj.print_bankHistory(); //to print all transactions related to the account
                break;
            case 5:
                break;
            default:
                cout<<"Please enter a number in between 1 and 5"<<endl;
                break;
            }
            cout<<"\nBank Account \nPlease select an option: \n1. View account balance \n2. Deposit money \n3. Withdraw money";
            cout<<"\n4. Print out history \n5. Return to previous menu"<<endl;
            cout<<"\nOption: ";
            cin>>b_choice;
            }
            }
            break;


        case 3:
            break;
        default:
            cout<<"Please enter a number in between 1 and 3"<<endl;
            break;
            }

    }

    //stk_obj.sort_wrapper();
    stk_obj.current_portfolio();
    float tpf_value=stockaccount::total_portfolio_value; //to save the portfolio value at the end in a file
    ofstream myfile3;
    myfile3.open("total_portfolio_value.txt",ios::app);
    myfile3<<tpf_value<<endl;
    myfile3.close();

    ofstream myfile2;
    myfile2.open("cash_balance.txt"); //to save cash balance at the end in a file
    myfile2<<"$"<<account::cash_balance<<"\t"<<bank_obj.getDate()<<"\t"<<stk_obj.getTime()<<endl;
    myfile2.close();

    system("pause");
    return 0;
}
