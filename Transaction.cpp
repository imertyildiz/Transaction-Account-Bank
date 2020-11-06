#include "Transaction.h"

Transaction::Transaction(){
    this->_amount=-1;
    this->_date=(time_t)(-1);
}
Transaction::Transaction(double amount,time_t date){
    this->_amount=amount;
    this->_date=date;
}
Transaction:: Transaction(const Transaction& rhs){
    this->_amount= rhs._amount;
    this->_date=rhs._date;
}
bool Transaction::operator<(const Transaction& rhs)const{
    if(difftime(this->_date,rhs._date)<0){
        return true;
    } 
    else{
        return false;
    }
}
bool Transaction::operator>(const Transaction& rhs)const{
    if(difftime(this->_date,rhs._date)>0){
        return true;
    } 
    else{
        return false;
    }

}
bool Transaction::operator<(const time_t date) const{
    if(difftime(this->_date,date)<0){
        return true;
    } 
    else{
        return false;
    }
}
bool Transaction::operator>(const time_t date) const{
    if(difftime(this->_date,date)>0){
        return true;
    } 
    else{
        return false;
    }
}
double Transaction::operator+(const Transaction& rhs){
    double x= (this->_amount)+(rhs._amount);
    return x;
}
double Transaction::operator+(const double add){
    double x= (this->_amount)+(add);
    return x;
}
Transaction& Transaction:: operator=(const Transaction& rhs){
    this->_amount=rhs._amount;
    this->_date=rhs._date;
    return *this;
}
std::ostream& operator<<(std::ostream& os, const Transaction& transaction){
    struct tm * ti;
    ti=localtime(&(transaction._date));

    os << transaction._amount <<"\t-\t"<<ti->tm_hour<<":"<<ti->tm_min<<":"<<ti->tm_sec<<"-"<<ti->tm_mday<<"/"<<ti->tm_mon+1<<"/"<<ti->tm_year+1900<<std::endl;
    return os;
}