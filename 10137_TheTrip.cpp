#include <iostream>
#include<stdio.h>

using namespace std;

double tripCosts(int n, double costs[], double cost_per_person){
  double min_cost = 0.0, min_cost1 = 0.0, min_cost2 = 0.0;
  int tmp = 0; 
  
  for (int i = 0; i < n; i++)
  {
    if(costs[i] >= cost_per_person){
      tmp = (costs[i] - cost_per_person) * 100.0;
      min_cost1 += tmp/100.0;
    }
    else{
      tmp = (cost_per_person - costs[i]) * 100.0;
      min_cost2 +=  tmp/100.0;
    }
  }
  min_cost = (min_cost1>min_cost2) ? min_cost1 : min_cost2;
  return min_cost;
}

int main(){
    int n = 0;
    double res = 0.0;
    double total , cost_per_person;
    cin>>n;

    while(n != 0){
        double costs[n];
        total = 0.0;
        for(int i = 0; i<n; i++){
            cin>>costs[i];
            total += costs[i];
        }
        cost_per_person = total / n;
        res = tripCosts(n, costs, cost_per_person);
        printf("$%.2lf\n", res);
        cin>>n;
    }
    return (0);
}