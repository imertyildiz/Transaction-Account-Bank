#include "Account.h"

Account::Account(){
    _id=-1;
    _activity=nullptr;
    _monthly_activity_frequency=nullptr;
}

Account::Account(int id, Transaction** const activity, int* monthly_activity_frequency){
    Transaction **twodarray = new Transaction*[12];
    int *num = new int[12];
    for(int i=0;i<12;i++){
        num[i]=monthly_activity_frequency[i];
    }
    int newid=id;
    for(int i=0;i<12;i++){
        int a=monthly_activity_frequency[i];
        if(a==0){
            twodarray[i]=nullptr;
        }
        else{
            twodarray[i]=new Transaction[a];
        }
    }
    for(int a=0;a<12;a++){
        for(int b=0;b<monthly_activity_frequency[a];b++){
            twodarray[a][b]=activity[a][b];
        }
    }
    for(int i =0;i<12;i++){
        for (int a = 0; a < monthly_activity_frequency[i]-1; a++)
        {
            for (int b = 0; b < monthly_activity_frequency[i]-a-1; b++)
            {
                if(twodarray[i][b]>twodarray[i][b+1]){
                    Transaction temp=twodarray[i][b];
                    twodarray[i][b]=twodarray[i][b+1];
                    twodarray[i][b+1]=temp;
                }
            }
        }
    }
    this->_activity=twodarray;
    this->_monthly_activity_frequency=num;
    this->_id=newid;
}
Account::~Account(){
    if(this->_activity!=nullptr){
        for(int i =0;i<12;i++){
            if(this->_activity[i]!=nullptr){
                delete[] this->_activity[i];
            } 
        }
    }
    
    if(this->_activity!=nullptr){
        delete[] this->_activity;
    }
    if(this->_monthly_activity_frequency!=nullptr){
        delete[] this->_monthly_activity_frequency;
    }
}
Account::Account(const Account& rhs){
    Transaction**twodarray = new Transaction*[12];
    for(int i=0;i<12;i++){
        int a=rhs._monthly_activity_frequency[i];
        if(a==0){
            twodarray[i]=nullptr;
        }
        else{
            twodarray[i]=new Transaction[a];
        }
    }
    int *num = new int[12];
    int newid=rhs._id;
    this->_id=newid;
    for(int i=0;i<12;i++){
        num[i]=rhs._monthly_activity_frequency[i];
    }
    this->_monthly_activity_frequency=num;
    for (int i = 0; i < 12; i++){
        for (int a = 0; a < rhs._monthly_activity_frequency[i]; a++){
            twodarray[i][a]=rhs._activity[i][a];
        }
    }
    this->_activity=twodarray;
}
Account::Account(const Account& rhs, time_t start_date, time_t end_date){
   // aydaki toplam islem sayisi degisecek mi ???????????????????????????????????
    Transaction**twodarray = new Transaction*[12];
    int *kactane=new int[12];
    for(int i=0;i<12;i++){
        int x=0;
        int v=0;
        for(int a=0;a<rhs._monthly_activity_frequency[i];a++){
            if((rhs._activity[i][a]>start_date) &&(rhs._activity[i][a]<end_date)){
                x++;
            }
        }
        kactane[i]=x;
        twodarray[i]=new Transaction[x];
        for(int a=0;a<rhs._monthly_activity_frequency[i];a++){
            if((rhs._activity[i][a]>start_date)&&(rhs._activity[i][a]<end_date)){
                twodarray[i][v++]=rhs._activity[i][a];
            }
        }
    }
    int newid=rhs._id;
    this->_id=newid;
    this->_monthly_activity_frequency=kactane;
    this->_activity=twodarray;
}

Account::Account(Account&& rhs){
	this->_id = rhs._id;
	this->_activity = rhs._activity;
	this->_monthly_activity_frequency = rhs._monthly_activity_frequency;
	
	rhs._id = -1;
	rhs._activity = nullptr;
	rhs._monthly_activity_frequency = nullptr;

}

Account& Account::operator=(Account&& rhs){
    if(this->_activity!=nullptr){
        for(int i =0;i<12;i++){
            if(this->_activity[i]!=nullptr){
                delete[] this->_activity[i];
        }
    }
    }
    if(this->_activity!=nullptr){
        delete[] this->_activity;
    }
    if(this->_monthly_activity_frequency!=nullptr){
        delete[] this->_monthly_activity_frequency;
    }
    
    _id = rhs._id;
	_activity = rhs._activity;
	_monthly_activity_frequency = rhs._monthly_activity_frequency;
    rhs._activity=nullptr;
    rhs._monthly_activity_frequency=nullptr;
    rhs._id=-1;
    return *this;
}
Account& Account::operator=(const Account& rhs){
    if(this->_activity!=nullptr){
        for(int i =0;i<12;i++){
            if(this->_activity[i]!=nullptr){
                delete[] this->_activity[i];
        }
    }
    }
    if(this->_activity!=nullptr){
        delete[] this->_activity;
    }
    if(this->_monthly_activity_frequency!=nullptr){
        delete[] this->_monthly_activity_frequency;
    }
    

    Transaction **twodarray = new Transaction*[12];
    int *num = new int[12];
    for(int i=0;i<12;i++){
        num[i]=rhs._monthly_activity_frequency[i];
    }
    int newid=rhs._id;
    for(int i=0;i<12;i++){
        int a=rhs._monthly_activity_frequency[i];
        if(a==0){
            twodarray[i]=nullptr;
        }
        else{
            twodarray[i]=new Transaction[a];
        }
    }
    for(int a=0;a<12;a++){
        for(int b=0;b<rhs._monthly_activity_frequency[a];b++){
            twodarray[a][b]=rhs._activity[a][b];
        }
    }
    for(int i =0;i<12;i++){
        for (int a = 0; a < rhs._monthly_activity_frequency[i]-1; a++)
        {
            for (int b = 0; b < rhs._monthly_activity_frequency[i]-a-1; b++)
            {
                if(twodarray[i][b]>twodarray[i][b+1]){
                    Transaction temp=twodarray[i][b];
                    twodarray[i][b]=twodarray[i][b+1];
                    twodarray[i][b+1]=temp;
                }
            }
        }
    }
    this->_activity=twodarray;
    this->_monthly_activity_frequency=num;
    this->_id=newid;
    return *this;
    
    /*if(this!=&rhs){
        this->~Account();
        new(this) Account(rhs);
    }
    return *this;*/
}
bool Account::operator==(const Account& rhs) const{
    if((this->_id)==(rhs._id)){
        return true;
    }
    return false;
}
bool Account::operator==(int id) const{
    if((this->_id)==(id)){
        return true;
    }
    return false;
}
Account& Account::operator+=(const Account& rhs){
    for (int i = 0; i <12; i++){
        int a= this->_monthly_activity_frequency[i]+rhs._monthly_activity_frequency[i];
        Transaction *cmonth = new Transaction[a];
        Transaction *temp = this->_activity[i];
        for (int b = 0; b <(this->_monthly_activity_frequency[i]); b++){
            cmonth[b]=temp[b];
        }
        for (int b = 0; b <(rhs._monthly_activity_frequency[i]); b++){
            cmonth[b+(this->_monthly_activity_frequency[i])]=rhs._activity[i][b];
        }
        for (int x = 0; x <a-1; x++){
            for (int b = 0; b < a-x-1; b++){
                if(cmonth[b]>cmonth[b+1]){
                    Transaction tem=cmonth[b];
                    cmonth[b]=cmonth[b+1];
                    cmonth[b+1]=tem;
                }
            }
        }
        this->_activity[i]=cmonth;
        this->_monthly_activity_frequency[i]=a;
        delete[] temp;
    }
    return *this;
}
double Account:: balance(){
    double x=0;
    for (int i = 0; i < 12; i++)
    {
        for (int a = 0; a<(this->_monthly_activity_frequency[i]); a++)
        {
            x=this->_activity[i][a]+x;
        }
    }
    return x;
}
double Account:: balance(time_t end_date){
    double x=0;
    for (int i = 0; i < 12; i++)
    {
        for (int a = 0; a<(this->_monthly_activity_frequency[i]); a++)
        {
            if(this->_activity[i][a]<end_date){
                x=this->_activity[i][a]+x;
            }
        }
    }
    return x;
}
double Account:: balance(time_t start_date, time_t end_date){
    double x=0;
    for (int i = 0; i < 12; i++)
    {
        for (int a = 0; a<(this->_monthly_activity_frequency[i]); a++)
        {
            if((this->_activity[i][a]<end_date) && (this->_activity[i][a]>start_date)){
                x=this->_activity[i][a]+x;
            }
        }
    }
    return x;
}
std::ostream& operator<<(std::ostream& os, const Account& account){
    if(account._activity==nullptr || account._monthly_activity_frequency==nullptr){
        os<<-1<<std::endl;
        return os;
    }
    os<<account._id<<std::endl;
    for(int i=0;i<12;i++){
        for (int a = 0; a < account._monthly_activity_frequency[i]; a++)
        {
            os<<account._activity[i][a];
        }
    }
    return os;
}