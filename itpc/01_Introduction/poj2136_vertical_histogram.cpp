#include <cstdio>
#include <algorithm>
using namespace std;

int main(){
    char input[100];
    int count[50];
    fill(count, count+50, 0);
    for(int i=0;i<4;i++){
        scanf(" %[^\n]", input);
        for(int j=0; input[j]; j++){
            if(input[j] >= 'A' && input[j] <= 'Z'){
                count[input[j]-'A'] ++;
            }
        }
    }
    int max_count = 0;
    for(int i=0;i<26;i++){
        if(max_count < count[i]) max_count = count[i];
    }
    for(int i=0;i<max_count;i++){
        int space_count = 0;
        for(int j=0;j<26;j++){
            if(count[j]<max_count-i){
                if(j!=0){
                    space_count++;
                }
                space_count++;
            }
            else{
                for(int k=0;k<space_count;k++){
                    printf(" ");
                }
                space_count = 0;
                if(j!=0){
                    printf(" ");
                }
                printf("*");
            }
        }
        printf("\n");
    }
    for(int i=0;i<26;i++){
        if(i!=0){
            printf(" ");
        }
        printf("%c", 'A' + i);
    }
}
