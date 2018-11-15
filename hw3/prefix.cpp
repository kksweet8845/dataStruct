#include<iostream>
#include<stack>
#include<map>
#include<sstream>
using namespace std;
map<string,int> tokens;


int main(void){
	
	string temp,element;
	stack<string> str;
	stack<string> token;
	stack<string> ans;
	tokens["+"] = 12;
	tokens["-"] = 12;
	tokens["*"] = 13;
	tokens["/"] = 13;
	tokens["%"] = 13;
	tokens["("] = 0;
	tokens[")"] = 0;

	while(getline(cin,element)){
		stringstream S;
		S.str(element);
		while(S >> temp){
			str.push(temp);
		}
		while(!str.empty()){
			if(tokens.find(str.top()) != tokens.end()){
				if(str.top() == "("){
					while(!token.empty() && token.top() != ")"){
						ans.push(token.top());
						token.pop();
					}
					token.pop();
				}else if(str.top() == ")"){
					token.push(str.top());
				}else{
					while(!token.empty() && tokens[token.top()] > tokens[str.top()]){
						ans.push(token.top());
						token.pop();
					}
					token.push(str.top());
				}
			}else{
				ans.push(str.top());
			
			}
			str.pop();
		}
		while(!token.empty()){
			ans.push(token.top());
			token.pop();
		}
		
		while(!ans.empty()){
			cout << ans.top()<<" ";
			ans.pop();
		}
		cout<<endl;
		
	}


	return 0;
}
