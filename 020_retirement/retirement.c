#include <stdlib.h>
#include <stdio.h>

struct _retire_info {
  int months;//工作/退休多少月
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double calculate(int startAge, double balance, retire_info a){
  int year, month;
  year = startAge/12;
  month = startAge%12;

  for(int i = a.months; i > 0; i--){ 
     printf("Age %3d month %2d you have $%.2lf\n", year, month, balance);
     balance = (1.0 + a.rate_of_return)*balance + a.contribution;
     month++;
     if (month == 12){
       year++;
       month = 0;
     }
  }
  return balance;
}

void retirement (int startAge,   //in months
                 double initial, //initial savings in dollars
                 retire_info working, //info about working
                 retire_info retired){//info about being retired
  //working
  initial = calculate(startAge, initial, working);
  //retire
  calculate(startAge+working.months, initial, retired);
}

int main(){
  retire_info working = {489,1000,0.045/12};
  retire_info retired = {384,-4000,0.01/12};
  retirement(327,21345,working,retired);
  return 0;
}
  
