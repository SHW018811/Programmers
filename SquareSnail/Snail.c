#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_LEN (n * (n + 1) / 2)

int* solution(int n){
    int* answer = (int*)calloc(n * (n+1) / 2, sizeof(int));
    int current = 1, loop = n, value = 1, cnt = 0, cnt2 = 0;
    char mode = 'L';
    while(value <= MAX_LEN){
        if(mode == 'L'){
            for(int i=0; i<loop; i++){
                current += (i + cnt);
                answer[current-1] = value;
                value += 1;
            }
            cnt += 2;
            mode = 'D';
        }
        else if(mode == 'D'){
            for(int i=0; i<loop; i++){
                current += 1;
                answer[current-1] = value;
                value += 1;
            }
            mode = 'R';
        }
        else if(mode == 'R'){
            for(int i=0; i<loop; i++){
                current -= (n - i - cnt2);
                answer[current-1] = value;
                value += 1;
            }
            mode = 'L';
            cnt2 += 1;
        }
        loop -= 1;
    }
    return answer;
}