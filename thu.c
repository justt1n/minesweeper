#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#define M 6
#define N 6
#define MINE -1

int B[M][N];
int T[M][N] = {};

void magenta() {
  printf("\033[1;35m");
}

void red() {
	printf("\033[0;31m");
}

void red1() {
	printf("\033[1;31m");
}

void green() {
	printf("\033[0;32m");
}

void cyan() {
	printf("\033[1;36m");
}

void reset() {
	printf("\033[0m");
}

void yellow() {
  	printf("\033[1;33m");
}

int init_mines(int k){
    int i = 1;
    int cnt = 0, r, c;
    while(i<=k){
        r = rand()%6;
        c = rand()%6;
        if(B[r][c] != MINE){
            B[r][c] = MINE;
            if(B[r-1][c-1]!=MINE && r-1 >= 0 && c-1 >= 0)
                B[r-1][c-1]+=1;
            if(B[r-1][c]!=MINE && r-1 >= 0)
                B[r-1][c]+=1;
            if(B[r-1][c+1]!=MINE && r-1 >=0 && c+1 < N)
                B[r-1][c+1]+=1;
            if(B[r][c-1]!=MINE && c-1 >= 0)
                B[r][c-1]+=1;
            if(B[r][c+1]!=MINE && c+1 < N)
                B[r][c+1]+=1;
            if(B[r+1][c-1]!=MINE && r+1 <= M && c-1 >= 0)
                B[r+1][c-1]+=1;
            if(B[r+1][c]!=MINE && r+1 <= M)
                B[r+1][c]+=1;
            if(B[r+1][c+1]!=MINE && r+1 <= M && c+1 < N)
                B[r+1][c+1]+=1;
            i++;
            cnt++;
        }
    }
}

void openAll(){
    for(int i=0; i<M; i++)
        for(int j=0; j<N; j++)
            T[i][j] = 1;
}

void printMap2(){
	cyan();
	printf("===Tro choi do min===\n");
	printf("---------------------\n");   
	reset();    
	printf("   ");
	yellow();
    for(int j = 0; j<M; j++)
        printf("%2d", j);
    red();
	printf("\n  .");
    for(int i = 0; i <= M; i++)
    	printf(" .");
    reset();
    printf("\n");
    for(int i = 0; i < M; i++){
        yellow();
		printf("%d ", i);
        red();
        printf(". ");
        reset();
        for(int j = 0; j < N; j++){
            if(T[i][j] == 0)
                printf("# ");
            else if(T[i][j] == 1){
            	cyan();
                if(B[i][j] == MINE){
                    printf("x ");
                }
                else if(B[i][j] == 0){
                    printf(". ");
                }else
                    printf("%d ", B[i][j]);
                reset();
            }
        }
        red();
        printf(".\n");
        reset();
    }
	red();
	printf("  .");
    for(int i = 0; i <= M; i++)
    	printf(" .");
    reset(); 
    printf("\n");
}

int count_remain(){
    int count_remain = 0;
    for(int i=0; i<M; i++)
        for(int j=0;j<N; j++)
            if(T[i][j] == 0)
                count_remain++;
    return count_remain;
}

void open_cell_3(int r, int c){
    if(T[r][c] == 1)
        return;
    if(r >= 0 && r < M && c >= 0 && c < N && B[r][c] != MINE){
        T[r][c] = 1;
        if(B[r][c] == 0){
            open_cell_3(r-1, c-1);
            open_cell_3(r-1, c);
            open_cell_3(r-1, c+1);
            open_cell_3(r, c-1);
            open_cell_3(r, c+1);
            open_cell_3(r+1, c-1);
            open_cell_3(r+1, c);
            open_cell_3(r+1, c+1);
        }
    } 
}

int main(){
	//Doi kich thuoc console  
	SMALL_RECT windowSize = {-15 , 0 , 15 , 15}; 
    SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &windowSize);
	
	PlaySound(TEXT("go.wav"), NULL, SND_LOOP | SND_ASYNC);
    int r, c;
    int k;
    
    red();
	system("cls"); // xoa man hinh
    printf("Ban muon may qua? ");
	reset();
    scanf("%d", &k);
    init_mines(k);
    while(1){
		int a;
		system("cls");
        printMap2();
        magenta();
        printf("Nhap o can mo: ");
        scanf("%d%d", &r,&c);
        reset();
		system("cls");
        if(B[r][c] == MINE){
            openAll();
			system("cls");
			red();
            printMap2();
            red1();
            printf("You lose.\n");
            reset();
            break;
        }
        open_cell_3(r, c);
        if(count_remain() == k){
			system("cls");
            printMap2();
            green();
            printf("You win.\n");
            reset();
            break;
        }
		
    }
    	/*Chen nhac
	PlaySound(TEXT("C:\\Users\\trung\\Desktop\\Baocao\\go.wav"),NULL,SND_SYNC);
	*/
	getch();
    return 0;
    
}
