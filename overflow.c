#include <stdio.h>
#include <string.h>

void printchar(unsigned char c){
    if(isprint(c)){// int isprint(int c)  변수 c가 출력 가능한 ASCII 코드인지 판별
        printf("%c", c);
    }
    else{
        printf(".");
    }
}

void dumpcode(unsigned char *buff, int len){//unsigned char=1byte 0~ 255, len=32  //8bit = 1byte 
    int i;
    for(i=0; i<len; i++){//32번 반복    
        if(i%16==0){
            printf("0x%08x  ", &buff[i]);
        }
        printf("%02x ", buff[i]);//char 하나씩 가져옴. 00 ~ FF 두글자식 출력

        if(i%16-15==0){
            int j;
            printf("   ");
            for(j=i-15; j<=i; j++){
                printchar(buff[j]);
                }
        printf("\n");
        }
    }
    printf("\n");
}

void hack(){
    //buffer overflow가 발생하면 실행 될 함수
    //해킹 함수가 실행이 됨. 리턴값이 점프됫기때문에 Sgmentaion fault 가 떳지만, 내가 원하는 함수는 실행됨.
    printf("Hacking Success!\n");
}

int main(int argc, char* argv[]){
    char buf[20];//20byte 버퍼 저장공간
    dumpcode((char*)buf, 32);//buf의 초기화 값을 전달
    printf("buf:%x\n", &buf);
    strcpy(buf, argv[1]);
    printf("%s\n", buf);
    dumpcode((char*)buf, 32);
    return 0;
}