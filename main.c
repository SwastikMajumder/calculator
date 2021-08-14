#include <stdio.h>
#include <string.h>

float multiply(char *str, int length);
float add(char *str, int length);

float multiply(char *str, int length){
    int i;
    for (i=0; i<length; ++i){
        printf("%c", str[i]);
    }
    printf("\n");
    int j;
    int b;
    float product = 1.0f;
    for (i=0; i<length; ++i){ //For the whole term
        if (str[i] == '('){ //If there is a bracket
            b=0;
            for (j=i+1; ;++j){ //Skip all inner brackets
                if (b == 0 && str[j] == ')'){
                    break;
                }
                if (str[j] == '('){
                    ++b;
                }
                else if (str[j] == ')'){
                    --b;
                }
            }
            if (i == 0 || str[i-1] == '*'){ //If the bracket is multiplied by something
                product *= add(str + i + 1, j-i-1); //Do it by adding the inner terms
            }
            else if (str[i-1] == '/'){ //Handle the division of brackets
                product *= 1.0f / add(str + i + 1, j-i-1);
            }
            i=j+1;
        } else { //Multiply the term normally if there is no bracket, we need no more recursion
            if (i == 0 || str[i-1] == '*'){
                product *= (float)(str[i] - '0');
            }
            else if (str[i-1] == '/'){
                product *= 1.0f / (float)(str[i] - '0');
            }
            ++i;
        }
    }
    return product;
}

float add(char *str, int length){
    int i;
    for (i=0; i<length; ++i){
        printf("%c", str[i]);
    }
    printf("\n");
    int b=0;
    float sum=0.0f;
    float sign;
    int c;
    int j;
    for (i=0; i < length; ++i){ //Iterate through the string
        if (i == 0 || str[i] == '+' || str[i] == '-'){ //detect a term by a plus or minus sign, if it is the first letter it may not have sign
            if (str[i] == '-'){ //Term is negetive, multiply the term by minus one
                sign = -1.0f;
                ++i; //Go to next letter
            } else {
                sign = 1.0f;
                if (str[i] == '+'){
                    ++i;
                }
            }
            c=0;
            for (j=i; j < length; ++j){ //Find the end of the term, without recursion initially
                if (c == 0 && (str[j] == '+' || str[j] == '-')){
                    break;
                }
                if (str[j] == '('){
                    ++c;
                }
                else if (str[j] == ')'){
                    --c;
                }
            }
            sum += multiply(str + i, j-i) * sign; //Send the term to multiply
            i = j - 1;
        }
    }
    return sum;
};

int main (){

  char *lhs = "-3*(5*(4+3))+9*(-1)";

  float lhs_0 = add(lhs, strlen(lhs));
  printf("%.3f\n", lhs_0);

  return 0;
}
