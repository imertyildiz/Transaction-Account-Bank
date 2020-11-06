#include "Bank.h"

Bank::Bank(){
    this->_bank_name="not_defined";
    this->_users=nullptr;
    this->_user_count=0;
}
Bank::Bank(std::string bank_name, Account* const users, int user_count){
    this->_bank_name=bank_name;
    this->_user_count=user_count;
    Account *hesap= new Account[user_count];
    for (int i = 0; i < user_count; i++)
    {
        hesap[i]=users[i];
    }
    this->_users=hesap;
}
Bank::~Bank(){
    delete[] this->_users;
}
Bank::Bank(const Bank& rhs){
    this->_bank_name=rhs._bank_name;
    this->_user_count=rhs._user_count;
    Account *hesap= new Account[this->_user_count];
    for (int i = 0; i <this->_user_count; i++)
    {
        hesap[i]=rhs._users[i];
    }
    this->_users=hesap;
}
Bank& Bank::operator+=(const Bank& rhs){
	/**
     * If both banks has a user with the same id, Transactions of these users will be merged in to the same Account
     * For example:
     * Bank1 has [1,2] id users
     * Bank2 has [2,3] id users
     * 
     * Bank1 after += operator will have [1,2,3] id users
     * User with id 2 will have its transactions histories merged
     * 
     * Transactions with of the users with the same id should be merged and updated
     * @param rhs Merged Bank
     * @return this Bank
     */
     if(this!=&rhs){
     	if (_users == NULL){
     		int i;
     		if(rhs._users==NULL|| rhs._user_count==0){
     			return *this;
			 }
     		_users = new Account[rhs._user_count];
     		_user_count = rhs._user_count;
     		for(i=0;i<rhs._user_count;i++){
     			_users[i]=rhs._users[i];
			 }
	        return *this;
		 }
		
		else if(rhs._users == NULL){
			return *this;
		}
		
		else{
			int i,j,k;
			int total = _user_count+rhs._user_count;
			for(i=0;i<_user_count;i++){
				for(j=0;j<rhs._user_count;j++){
					if(_users[i]==rhs._users[j]){
						total--;
					}
				}
			}
			
			Account *temp = new Account[total];
			k=0;
			for(i=0;i<_user_count;i++){
				bool check = true;
				for(j=0;j<rhs._user_count;j++){
				
						if(_users[i]==rhs._users[j]){
							_users[i]+=rhs._users[j];
							temp[k]=_users[i];
							k++;
							check = false;
							break;
						}
				}
				if (check){
					temp[k] = _users[i];
					k++;
				}
				
			}
			if(k<total){
				for(i=0;i<rhs._user_count;i++){
					bool check = true;
					for(j=0;j<_user_count;j++){
						if(rhs._users[i]==_users[j]){
							check = false;
							break;
						}
					}
					if(check){
						temp[k]= rhs._users[i];
						k++; 
					}
				}
			}			
		for(i=0;i<_user_count;i++){
			_users[i].~Account();
		}
	
		_users = temp;
		_user_count = total;
		}	
	 }
	 return *this;
}
/*
Bank& Bank::operator+=(const Bank& rhs){
    int x=0;
    int b=0;
    int count=0;
    for(int i=0;i<rhs._user_count;i++){
        for (int a = 0; a < this->_user_count; a++)
        {
            if(rhs._users[i]==this->_users[a]){
                x++;
            }
        }
    }
    b+=this->_user_count+rhs._user_count-x;
    Account *hesap= new Account[b];
    Account *temp= this->_users;
    for(int i=0;i<this->_user_count;i++){
        hesap[i]=temp[i];
    }
    for (int i = 0,xx=0; i < rhs._user_count; i++)
    {
        for(int v=0;v<this->_user_count;v++){
            if(hesap[v]==rhs._users[i]){
                xx=1;
                hesap[v]+=rhs._users[i];
            }
        }
        if(xx){
            xx=0;
        }
        else{
            hesap[(this->_user_count)+(count++)]=rhs._users[i];
        }
        xx=0;
    }
    this->_users=hesap;
    this->_user_count=b;
    delete[] temp;
    return *this;
}
*/
Bank& Bank::operator+=(const Account& new_acc){
    int xx=0;
    for (int i = 0; i < this->_user_count; i++)
    {
        if(this->_users[i]==new_acc){
            (this->_users[i])+=new_acc;
            xx=1;
        }
    }
    if(xx==0){
        Account *hesap= new Account[this->_user_count+1];
        Account *temp = this->_users;
        for(int i=0;i<this->_user_count;i++){
            hesap[i]=this->_users[i];
        }
        hesap[this->_user_count]=new_acc;
        this->_user_count++;
        this->_users=hesap;
        delete[] temp;
    }
    return *this; 
}
Account& Bank::operator[](int account_id){
    for(int i=0;i<this->_user_count;i++){
        if(this->_users[i]==account_id){
            return this->_users[i];
        }
    }
    return this->_users[0];
}
std::ostream& operator<<(std::ostream& os, const Bank& bank){
    int people=0;
    double totalmoney=0;
    for(int i=0;i<bank._user_count;i++){
        int money=0;
        int ckpep=0;
        time_t rawtime;
        time_t rawtime1;
        struct tm timeinfo0;
        struct tm timeinfo1;
        timeinfo0.tm_year = 119;
        timeinfo0.tm_mon = 0;
        timeinfo0.tm_mday = 1;
        timeinfo0.tm_hour=0;
        timeinfo0.tm_min=0;
        timeinfo0.tm_sec=0;
        timeinfo1.tm_year = 119;
        timeinfo1.tm_mon = 1;
        timeinfo1.tm_mday = 1;
        timeinfo1.tm_hour=0;
        timeinfo1.tm_min=0;
        timeinfo1.tm_sec=0;
        timeinfo0.tm_isdst=0;
        timeinfo1.tm_isdst=0;
        rawtime=mktime(&timeinfo0);
        rawtime1=mktime(&timeinfo1);
        for(int a=0;a<12;a++){
            double tempmoney=(bank._users[i]).balance(rawtime,rawtime1);
            if(tempmoney<0){
                if(money==1){
                    ckpep=1;
                }
                money=1;
            }
            else
            {
                money=0;
            }
            totalmoney+=tempmoney;
            if(timeinfo1.tm_mon==11){
                timeinfo0.tm_mon++;
                timeinfo1.tm_mday=31;
                timeinfo1.tm_hour=23;
                timeinfo1.tm_min=59;
                timeinfo1.tm_sec=59;
                rawtime=mktime (&timeinfo0);
                rawtime1=mktime(&timeinfo1);
            }
            else{
                timeinfo0.tm_mon++;
                timeinfo1.tm_mon++;
                rawtime=mktime (&timeinfo0);
                rawtime1=mktime(&timeinfo1);
            }
        }
        if(ckpep==1){
            people++;
        }
    }
    os<<bank._bank_name<<"\t"<<bank._user_count-people<<"\t"<<totalmoney<<std::endl;
    return os;
}