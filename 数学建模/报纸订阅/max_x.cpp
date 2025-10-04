#include<stdio.h>
int main(){
	double x,n=80000.0,b=1.5,d;
	while(1){
		scanf("%lf",&d);
		x=(0.1*n-b*d)/(0.2*d);//公式7 
		printf("%lf\n",b+0.1*x);//公式2 
	}
	return 0;
} 
