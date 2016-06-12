//Shanmukha Priya Loke
//December 13th, 2015
#ifndef ACCOUNT_PRIYA_H
#define ACCOUNT_PRIYA_H

class account //abstract base class
{
 public:
     account(); //constructor
     static float cash_balance;

     //pure virtual functions to make the base class abstract
     virtual float getBalance()=0;
     virtual void setBalance(float)=0;
};
#endif // ACCOUNT_PRIYA_H
