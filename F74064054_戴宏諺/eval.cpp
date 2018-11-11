#include<iostream>
#include<stack>
#include<sstream>
#include<string.h>
#include<cstdio>
#include<map>
using namespace std;


int operate(int,int,string);


map<string,int> token;

int main(void){
	
	string temp;
	string element;
	stack <string> str;
	stack <int> num;
	token["+"] = 12;
	token["-"] = 12;
	token["*"] = 13;
	token["/"] = 13;
	token["%"] = 13;
	int sum = 0;
	while(getline(cin,element)){
			stringstream S;
			S.str(element);
			while(S >> temp)
				str.push(temp);
			
		while(!str.empty()){
			if(token.find(str.top()) != token.end()){
				int a,b;
				a = num.top();
				num.pop();
				b = num.top();
				num.pop();
				string s = str.top();
				sum = operate(a,b,s);
				num.push(sum);
				str.pop();
			}else{
				int t;				
				try{
					t = stoi(str.top());
				}catch(exception e ){}
				num.push(t);
				str.pop();
			}
		}
		
		cout <<num.top()  << '\n';
		num.pop();
	}	
	
	

	return 0;
}

int operate(int a,int b,string s){
	
	if(s.compare("+") == 0)
		return a+b;
	else if(s.compare("-") == 0)
		return a-b;
	else if(s.compare("*") == 0)
		return a*b;
	else if(s.compare("/") == 0)
		return a/b;
	else if(s.compare("%") == 0)
		return a%b;

}
