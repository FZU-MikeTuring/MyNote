#include<stdio.h>
int main(){
	double x,n=80000.0,b=1.5,d;
	while(1){
		scanf("%lf",&d);
		x=(0.1*n-b*d)/(0.2*d);//��ʽ7 
		printf("%lf\n",b+0.1*x);//��ʽ2 
	}
	return 0;
} 
