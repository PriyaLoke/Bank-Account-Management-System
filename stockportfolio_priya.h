//Shanmukha Priya Loke
//December 13th, 2015

#ifndef STOCKPORTFOLIO_PRIYA_H
#define STOCKPORTFOLIO_PRIYA_H

#include "account_priya.h"
#include<string>
using namespace std;

class ListNode //implementation of list nodes
{
    friend class stockaccount; //declaring stockaccount as friend
    public: //pubic member functions
        ListNode(string& name,int numb)
        :symbol(name),number(numb)
        {
            this->next=NULL;
            this->prev=NULL;
        }

private:
    string symbol;
    int number;
    ListNode *next;//next node in the list
    ListNode *prev;
};

class stockaccount:public account //public inheritance from class account
{
public:
    stockaccount();
    static float total_portfolio_value;
    void display();
    void current_portfolio();
    void buy_shares();
    void addNode(ListNode *);
    void sell_shares();
    void delNode(string node);
    void transac_history();
    void update_stocks();
    string getTime();

	//functions that constitute the merge sort operation
    ListNode *split(ListNode *);
    ListNode *merge_sort(ListNode *);
    ListNode *sortList(ListNode *first,ListNode *second);
    void sort_wrapper();
    virtual float getBalance();
	virtual void setBalance(float);
private:
    ListNode *firstPtr; //pointer to first node
    ListNode *lastPtr; //pointer to second node
    int size_list; //size of the doubly linked list
};
#endif // STOCKPORTFOLIO_PRIYA_H
