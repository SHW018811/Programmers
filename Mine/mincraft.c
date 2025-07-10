#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int solution(int picks[], size_t picks_len, const char* minerals[], size_t minerals_len) {
    int answer = 0,cnt = 0,group = 0, max = 0;
    int *minerals_num;
    group = (minerals_len + 4) / 5;
    minerals_num = (int*)calloc(group, sizeof(int));
    for(int i=1; i<=minerals_len; i++){
        if(strcmp(minerals[(i-1)], "diamond") == 0) minerals_num[cnt] += 25;
        else if(strcmp(minerals[(i-1)], "iron") == 0) minerals_num[cnt] += 5;
        else if(strcmp(minerals[(i-1)],"stone") == 0) minerals_num[cnt] += 1;
        if(i % 5 == 0) cnt += 1;
    }
    //for(int i=0; i<group; i++) printf("%d ", minerals_num[i]);
    while(1){
        if(picks[0] == 0 && picks[1] == 0 && picks[2] == 0) break;
        for(int i=0; i<group; i++){
            if(minerals_num[i] > max){
                max = minerals_num[i];
                cnt = i;
            }
        }
        if(max == 0) break;
        cnt *= 5;
        for(int i=0; i<group; i++) printf("%d ",minerals_num[i]);
        
        if(picks[0] != 0){
            for(int i=0; i<5; i++){
                if(strcmp(minerals[cnt + i],"diamond") == 0) minerals_num[(cnt/5)] -= 25;
                else if(strcmp(minerals[cnt + i],"iron") == 0) minerals_num[(cnt/5)] -= 5;
                else if(strcmp(minerals[cnt + i],"stone") == 0) minerals_num[(cnt/5)] -= 1;
                answer += 1;
            }
            max = 0;
            picks[0] -= 1;
        }
        else if(picks[1] != 0){
            for(int i=0; i<5; i++){
                if(strcmp(minerals[cnt + i],"diamond") == 0) minerals_num[(cnt/5)] -= 20;
                else if(strcmp(minerals[cnt + i],"iron") == 0) minerals_num[(cnt/5)] -= 5;
                else if(strcmp(minerals[cnt + i],"stone") == 0) minerals_num[(cnt/5)] -= 1;
                else answer += 1;
            }
            max = 0;
            picks[1] -= 1;
        }
        else if(picks[2] != 0){
            for(int i=0; i<5; i++){
                if(strcmp(minerals[cnt + i],"diamond") == 0) minerals_num[(cnt/5)] -= 1;
                else if(strcmp(minerals[cnt + i],"iron") == 0) minerals_num[(cnt/5)] -= 1;
                else if(strcmp(minerals[cnt + i],"stone") == 0) minerals_num[(cnt/5)] -= 1;
            }
            max = 0;
            picks[2] -= 1;
        }
        //break;
    }

    free(minerals_num);
    return answer;
}