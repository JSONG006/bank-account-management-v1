#include <cmath>
#include <iostream>

using namespace std;

class SavingAccount{					 //save the user account
private:
	int id;								 //user id
	double balance;				 //user balance
	double rate;					 //year rate
	int lastDate;					 //last time to change date
	double  accumulation;	 //the sum of balance

	void record(int date, double amount, int flag);

	double accumulate(int date) const {			//get the sum of the balance
		return accumulation+balance*(date-lastDate);
	}

public:
	SavingAccount (int date, int id, double rate);
	int getId(){
		return id;
	};
	double getBalance(){
		return balance;
	}
	double getRate(){
		return rate;
	}
	void deposit(int data, double amount, int flag);		//save money
	void withdraw(int date, double amount, int flag);		//withdraw money
	void settle(int date, int flag);	//calculate rate
	void show();				//show the account info
};

	SavingAccount :: SavingAccount(int date, int id, double rate) : id(id), balance(0),rate(rate),lastDate(date),accumulation(0){
		cout<<"Date: "<<date<<"\tUser id"<<id<<" is created"<<endl;
	}

	void SavingAccount :: record(int date, double amount, int flag){	//amount = money
		accumulation = accumulate(date);
		lastDate = date;
		amount = floor(amount*100+0.5)/100;
		balance += amount;
		if(flag==1){
			cout<<"Date: "<<date<<"\tUser id: "<<id<<"\tDeposit: "<<amount<<"\tBalance: "<<balance<<endl;
		}
		else if(flag==2){
			cout<<"Date: "<<date<<"\tUser id: "<<id<<"\tWithdraw: "<<amount<<"\tBalance: "<<balance<<endl;
		}
		else{
			cout<<"Date: "<<date<<"\tUser id: "<<id<<"\tInterest: "<<amount<<"\tBalance: "<<balance<<endl;
		}
	} 
	void SavingAccount :: deposit(int date, double amount, int flag){
		record(date, amount, flag);
	}
	void SavingAccount :: withdraw(int date, double amount, int flag){
		if(amount>getBalance()){
			cout<<"Error : not enough money"<<endl;
		}
		else{
			record(date, -amount, flag);
		}
	} 
	void SavingAccount :: settle(int date, int flag){
		double interest = accumulate(date)*rate/365;
		if(interest != 0){
			record(date, interest,flag);
		}
		accumulation = 0;
	}
	void SavingAccount :: show(){
		cout<<"#"<<id<<"\tBalance: "<<balance<<endl;
	}
	int main()
	{
		//create 2 users
		SavingAccount user1(1, 1001, 0.012);
		SavingAccount user2(1, 1002, 0.012);

		//operate
		user1.deposit(5,10000,1);
		user2.deposit(20,20000,1);

		user1.deposit(35,28000,1);
		user2.withdraw(70,15000,2);

		//interest date=90
		user1.settle(90,3);
		user2.settle(90,3);

		//show info
		cout<<endl;
		user1.show();
		user2.show();
		system("pause");
		return 0;
	}