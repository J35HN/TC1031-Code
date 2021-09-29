#include <string>
#include <vector>

class Solution {
public:
    char last(char ch){
        if(ch == ')'){
            return '(';
        } else if(ch == '}'){
            return '{';
        } else if (ch == ']') {
            return '[';
        } else {
            return '-';
        }
    }
    
    bool isValid(std::string s) {
       std::vector<char> stk;
        char lastCaract;
        for (int i = 0; i < s.length(); i++){
            stk.push_back(s[i]);
            if(stk.size() > 1){
                lastCaract = last(s[i]);
                if(lastCaract == stk[stk.size()-2]){
                    stk.pop_back();
                    stk.pop_back();
                }
            }
        }
        
        if(stk.size() == 0 ){
            return true;
        } else{
            return false;
        }
    }
};