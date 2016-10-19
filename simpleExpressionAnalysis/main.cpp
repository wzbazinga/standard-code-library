/*
	hdu 1237
	simulate easy calculation + - * /
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
#define MAX 210
using namespace std;

char s[MAX];
int l,p;
int command[MAX],com;

/*
	+ -11
	- -12
	* -21
	/ -22

*/

void getcommand(){
	for(int i=0;i<l;){
		int t=0;
		if(s[i]>='0'&&s[i]<='9'){
			while(i<l&&s[i]>='0'&&s[i]<='9'){
				t=t*10+s[i]-'0';
				i++;
			}
			command[com++]=t;
			i++;
		}
		else{
			switch(s[i]){
				case '+':command[com++]=-11;break;
				case '-':command[com++]=-12;break;
				case '*':command[com++]=-21;break;
				case '/':command[com++]=-22;break;
			}
			i+=2;
		}
	}
	command[com++]=-11;
}

int main(){
	while(gets(s)){
		l=strlen(s);
		if(l==1&&s[0]=='0')
			break;
		com=0;
		getcommand();
		stack<double>para;
		stack<int>op;
		para.push(0.0);
		op.push(-11);
		for(int i=0;i<com;i++){
			if(command[i]>=0)
				para.push(command[i]);
			else{
				int op1=op.top(),op2=command[i];
				while(op2/10>=op1/10){
					op.pop();
					double para2=para.top();
					para.pop();
					double para1=para.top();
					para.pop();
					double temp;
					switch(op1){
						case -11:temp=para1+para2;break;
						case -12:temp=para1-para2;break;
						case -21:temp=para1*para2;break;
						case -22:temp=para1/para2;break;
					}
					para.push(temp);
					if(op.empty())
						break;
					op1=op.top();
				}
				op.push(op2);
			}
		}
		double ans=para.top();
		printf("%.2lf\n",ans);
	}
	return 0;
}
