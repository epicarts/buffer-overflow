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
        if(i%16==0){//2번 들어감  4bit(4bit는 16진수) + 4bit = 8bit  = 00~ff  = 1byte / 32bit = 4byte / 16 = 2byte 00 00 
            printf("0x%08x  ", &buff[i]);// 0X 12345678 buf의 현재 주소 값
        }

        //8자리 공간쓰고 추가되면 0으로 패딩을 하는데, 16진수로 출력 (1,2,3,4,5 '''' A,B,C,D,F) 4bit
        printf("%02x ", buff[i]);//char 하나씩 가져옴 . 16진수(4bit로 표현가능) + 16진수(4bit로 표현가능) = 00 ~ FF 두글자식 출력

        if(i%16-15==0){
            int j;
            printf("   ");
            for(j=i-15; j<=i; j++){
                printchar(buff[j]);
                }
        printf("\n");
        }
    }

    if(i%16 != 0){
        int j;
        int space = (len-i+16-i)*3+2;
        for(j=0;j<space;j++){
            printf(" ");
        }
        for(j=i-i%16; j<len; j++){
            printchar(buff[j]);
        }
    }
    printf("\n");
}

void hack(){
    //buffer overflow가 발생하면 실행 될 함수
    printf("Hacking Success!\n");
}

int main(int argc, char* argv[]){
    char buf[20];//20byte 버퍼 저장공간
    dumpcode((char*)buf, 32);//buf의 원 주소의 값을 전달
    printf("buf:%x\n", &buf);
    strcpy(buf, argv[1]);
    printf("%s\n", buf);
    dumpcode((char*)buf, 32);
    return 0;
}

    //char를 사람이 입력하는데, 버퍼라는 거에 추가 캐릭터를 저장해놓는거지. buf




int main(int argc, char* argv[]){
    char buf[20]; //20개 이상 을 넣으면 ...?
    dumpcode((char*)buf, 32);// 2byte 까지 쓰겠다고 해서 전달 len=32
    //메모리 안에 들어감을 확인해야댐

    //4바이트는 프레임 포인터 나머지 4바이트는 리턴값을 저장함. 40 03 09 cb 리틀 엔디안으로 저장함. 보이는건 return (cb 09 03 40)
    //이게 남아 있으므로 프로그램이 정상적으로 동작함


    //hack 은 08 04 86 14 임/ 실제로는 14 86 04 08 
    //dep aslr도 없기때문에 가능. 32bit C 컴파일러 자체가 포인터를 쓸 수 있기 때문에
    // 한번 실행하고 나서 주소 보면 안바뀐것을 볼 수 있음(RedHat으로 하는 이유 /08 04 86 14 르 다시 확인) 
}

./overflow 'python -c ' 14 86 04 08 로 넣어라!!
//리턴 값이 바뀜 
//해킹 함수가 실행이 됨. 리턴값이 점프됫기떄문에 Sgmentaion fault 가 떳지만, 내가 원 하는 함수는 실행됨.
// C언어가 가지는 문제점(메모리) => 버퍼오버플로우가 가능할수 밖에 없음.
//프로그램의 주도권을 가지게 할수 밖에 없음

'''
DEP 기법 조사
스택이나 힙 영역의 실행코드 방지 (스택, 힙에 대한 정의 조사하기)


ASLR 기법 조사
랜덤하게 주소를 바꿈. 윈 7,8,9
메모리가 랜덤하게 바뀜(redhat은 안바뀜 /??? 좀더 조사 필요)

위의 기법이 있다면,,, 어떻게 우회하는가 ???
cat /proc/self/maps | grep rwxp 명령어를 실행하여 dep 기법와 ASLR 기능 있는지 확인 가능 - Redhat 과 칼리를 비교하쟈.
'''

buf[20];
printf("buf") //

strcpy() //20개 이상들어오면 오버플로우가 발생하면서 리턴값을 조작 가능


argv[1] 명령을 버퍼에다가

overflow.c 파일이 필요.

버퍼 오버플로우가 발생했을때 주소