#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

char **maze;
int **visited;
typedef struct{
    int x, y;
}Pos;

typedef struct{
    Pos *queue;
    int front, rear;
}Mapq;

int found_xy(char **maze, Pos start, Pos end, int maplen, int len){
    Mapq q = {(Pos*)malloc((maplen * len) * sizeof(Pos)), 0, -1};
    q.queue[++(q.rear)] = (Pos){start.x, start.y};
    visited[start.x][start.y] = 1;
    while(q.front <= q.rear){
        Pos current = q.queue[(q.front)++];
        if(current.x == end.x && current.y == end.y){
            printf("Reach");
            return 1;
        }
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        for(int i=0; i<4; i++){
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];
            if(nx >= 0 && nx < maplen && ny >= 0 && ny < len && maze[nx][ny] != 'X' && !visited[nx][ny]){
                q.queue[++(q.rear)] = (Pos){nx, ny};
                visited[nx][ny] = visited[current.x][current.y] + 1;
            }
        }
    }
    printf("No Path");
    return -1;
}

int solution(const char* maps[], size_t maps_len) {
    int answer = 0;
    int len = strlen(maps[0]);
    maze = (char**)malloc(maps_len * sizeof(char*));
    visited = (int**)calloc(maps_len, sizeof(int*));
    for(int i=0; i<maps_len; i++){
        maze[i] = (char*)malloc(len * sizeof(char));
        visited[i] = (int*)calloc(len, sizeof(int));
        strcpy(maze[i], maps[i]);
    }
    int cnt = 0;
    Pos start = {-1,-1};
    Pos end = {-1,-1};
    while(cnt < 2){
        for(int i=0; i<maps_len; i++){
            for(int j=0; j<len; j++){
                if(maze[i][j] == 'S'){
                    start = (Pos){i,j};
                }if(maze[i][j] == 'L' && cnt == 0){
                    end = (Pos){i, j};
                }if(maze[i][j] == 'E' && cnt > 0){
                    start = (Pos){end.x, end.y};
                    end = (Pos){i, j};
                }
                visited[i][j] = 0;
            }
        }
        if(start.x == -1 || start.y == -1 || end.x == -1 || end.y == -1) return -1;
        if(found_xy(maze, start, end, maps_len, len) == -1) return answer = -1;
        printf("\n");
        for(int i=0; i<maps_len; i++){
            for(int j=0; j<len; j++){
                printf("%d ", visited[i][j]);
            }
            printf("\n");
        }
        answer += visited[end.x][end.y];
        cnt += 1;
    }
    for(int i=0; i<maps_len; i++){
        free(visited[i]);
        free(maze[i]);
    }
    free(visited);
    free(maze);
    return (answer - 2);
}