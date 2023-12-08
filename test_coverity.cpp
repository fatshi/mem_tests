#include "stdio.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>


using namespace std;

// uaf
void test_1(void *p) {
    free(p);
    printf("%x\n", *((int *)p));
}

// loop write
void test_2(int total, char *p) {
    char a[100];

    for(int i=0;i < total; i++) {
        if (sizeof(a) > (i - 100)) {
            a[i] = *(p + i);
        }
    }
}

void test_2_mid(int total, char *p) {
    test_2(total, p);
}

typedef struct {
    int age;
    char address[10];
}Info;

typedef struct {
    int id;
    int id2;
    char name[10];
    Info info;
}Person;

// uint8 *p
void test_3(Person *p) {
    unsigned char *ptr = (unsigned char *)p;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
        ptr++;
    }
}

// state machine
enum {
    S_START,
    S_IDLE,
    S_BUSY,
    S_UNKNOWN
};
int gState = S_START;
char *gPtr = NULL;

void handle_start() {
    int size;

    printf("input malloc size:\n");
    scanf("%d", &size);

//    gPtr = (char *)malloc(size);

    gState = S_BUSY;
    printf("S_START -> S_BUSY\n");
}

void handle_busy() {
    char buff[100];

    printf("input string:\n");
    scanf("%s", buff);

    strcpy(gPtr, buff);
    puts(gPtr);
    gState = S_IDLE;
    printf("S_BUSY -> S_IDLE\n");
}

void handle_idle(void *p) {
    char cmd;

    printf("continue or exit(C/E)?");
    scanf("%c", &cmd);

    if (cmd == 'c' || cmd == 'C') {
        gState = S_BUSY;
        printf("S_IDLE -> S_BUSY\n");
    } else {
        free(p);
        printf("S_IDLE -> S_START\n");
        printf("exit\n");
        exit(0);
    }
}

void process(void *p) {
    switch (gState) {
        case S_START:
            handle_idle(p);
            handle_start();
            break;
        case S_BUSY:
            handle_busy();
            break;
        case S_IDLE:
            handle_idle(p);
            break;
        default:
            break;
    }
}

void test_4(void *p) {
    while (1)
    {
        process(p);
    }
}

void test_5(void *pData) {
    int kind = 0;
    void *ptr = NULL;

    printf("input kind:\n");
    scanf("%d", &kind);

    switch (kind) {
        case 1:
            ptr = malloc(100);
            break;
        case 2:
            ptr = malloc(200);
            break;
        default:
            ptr = malloc(64);
            break;
    }

    switch(kind) {
        case 1:
            memcpy(ptr, pData, 1000);
            break;
        case 2:
            memcpy(ptr, pData, 2000);
            break;
        default:
            memcpy(ptr, pData, 64);
            break;
    }

    printf("result: %s\n", (char *)ptr);
    free(ptr);
}

void test_6() {
    typedef struct {
        int age;
        char data[0];
    }A;

    A *p = (A *)malloc(100);

    int LENGTH = 500;
    for (int i = 0; i < LENGTH; i++) {
        p->data[i] = 'A' + i;
    }

    printf("%s\n", p->data);
    free(p);
}

void test_7(Person *p) {
    unsigned char *ptr = (unsigned char *)p;
    unsigned char **pptr = &ptr;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
        (*pptr)++;
    }

    printf("%s\n", (char *)p);
}

void test_7_demo(Person *p) {
    unsigned char *ptr = (unsigned char *)p;
    unsigned char **pptr = &ptr;

    ((Person *)(*pptr))->id = 90;

    char buff[90];
    memset(buff, 'c', p->id);

    ((Person *)(*pptr))->id = 91;
    memset(buff, 'c', p->id);
}

void test_8(void *p) {
    unsigned char *ptr = (unsigned char *)p;

    for (int j=0; j < sizeof(Person); j++) {
        *ptr = 'a';
        ptr++;
        for(int i=0; i < sizeof(Person); i++) {
            *ptr = 'a';
            ptr++;
        }
    }

    printf("%s\n", (char *)p);
}

void test_9(Person *p) {
    unsigned char *ptr = (unsigned char *)p;

    for (int j=0; j < 10; j++) {
        *ptr = 'a';
        ptr++;
    }

    Info *pi = (Info *)ptr;
    memset(pi, 'a', 100);

    printf("%s\n", (char *)p);
}

void test_9_1(Person *p) {
    unsigned char *ptr = (unsigned char *)p;

    for (int j=0; j < 18; j++) {
        *ptr = 'a';
        ptr++;
    }

    Info *pi = (Info *)ptr;
    pi->age = 100;
    memset(pi, 'a', pi->age);
    printf("%s\n", (char *)p);
}

void test_10(Person *p) {
    unsigned char *ptr = (unsigned char *)p;

    Info *pi = (Info *)ptr;
    memset(pi, 'a', 100);

    printf("%s\n", (char *)p);
}

void test_11(Person *p) {
    unsigned int *ptr = (unsigned int *)p;

    for (int i = 0; i < 10; i++) {
        *ptr = 0x61616161;
        ptr++;
    }
    *ptr = 0;
    printf("%s\n", (char *)p);
}

void test_12() {
    Person person;
    Person *p = &person;

    p->info.age = 100;
    printf("%d\n", person.info.age);
    memset(&person, 'a', person.info.age);
}

void test_12_1() {
    Person person;
    Person *p = &person;

    p->info.age = 100;
    printf("%d\n", p->info.age);
    memset(&person, 'a', p->info.age);
}

void test_12_2() {
    Person person;
    Person *p = &person;

    p->info.age = 100;
    int i = 0;
    for (;i < person.info.age; i++) {
        p->name[i] = 'a';
    }
}

void test_13() {
    Person person;
    int *p = (int *)&person;

    *p = 100;
    printf("%d\n", person.id);
    memset(&person, 'a', person.id);
}

void test_14() {
    Person person;
    int *p = (int *)&person;

    p++;
    *p = 100;
    printf("%d\n", person.id2);
    memset(&person, 'a', person.id2);
}

void test_15() {
    Person person;
    void *ptr = person.name;

    memset(ptr, 'a', 100);
    printf("%s\n", person.name);
}

void test_15_1() {
    Person person;
    void *ptr = person.name;

    memset(ptr, 'a', 20);
    printf("%s\n", person.name);
}

void test_15_2() {
    Person *person = (Person *)malloc(200);
    void *ptr = person->name;

    memset(ptr, 'a', 100);
    printf("%s\n", person->name);
}

void test_3_0() {
    Person p;
    unsigned char *ptr = (unsigned  char *)&p;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
        ptr++;
    }
    printf("%s\n", ptr);
}

void test_3_1() {
    Person p;
    unsigned char *ptr = (unsigned  char *)&p;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
//        ptr++;
    }
    printf("%s\n", ptr);
}

void test_3_2() {
    Person p;
    unsigned char *ptr = (unsigned  char *)&p;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
        if (*ptr == 'a') {
            ptr++;
        }
    }
    printf("%s\n", ptr);
}

void test_3_3() {
    Person p;
    unsigned char *ptr = (unsigned  char *)&p;
    unsigned char *ap = (unsigned  char *)&p;

    for(int i=0; i < sizeof(Person) + 100; i++) {
        *ptr = 'a';
        ap++;
    }
    printf("%s\n", ptr);
}

void test_16() {
    Person person;
    Person *p = &person;

    for (int i = 0; i < 2; i++) {
        *p = person;
        p++;
    }
}

void test_3_4() {
    Person p;
    unsigned char *ptr = (unsigned char *)&p;

    for(int i=0; i < sizeof(Person); i++) {
        *ptr = 'a';
        ptr++;
        *ptr = 'b';
        ptr++;
    }
    printf("%s\n", ptr);
}

void test_3_5() {
    Person p;
    unsigned char *ptr = (unsigned char *)&p;

    for(int i=0; i < sizeof(Person); i++) {
        *ptr = 'a';
        ptr++;
        *ptr = 'b';
        ptr--;
    }
    printf("%s\n", ptr);
}

void test_3_6() {
    Person p;
    unsigned char *ptr = (unsigned char *)&p;

    for(int i=0; i < sizeof(Person); i++) {
        *ptr = 'a';
        ptr++;
        *ptr = 'b';
        ptr--;
        *ptr = 'a';
        ptr++;
    }
    printf("%s\n", (char *)&p);
}

void test_3_7() {
    Person p = {'a'};
    unsigned char *ptr = (unsigned char *)&p;

    for(int i=0; i < sizeof(Person); i++) {
        *++ptr = 'c';
    }

    printf("%s\n", (char *)&p);
}

void test_3_8() {
    Person p = {};
    unsigned char *ptr = (unsigned char *)&p;

    for(int i=0; i < sizeof(Person); i++) {
        *ptr++ = 'c';
    }

    printf("%s\n", (char *)&p);
}

void test_17() {
    Person p = {};
    unsigned char *ptr = (unsigned char *)&p;
    char a[10];

    for(int i=0; i < sizeof(Person); i++) {
        *ptr++ = 'c';
    }

    unsigned int *pp = (unsigned int *)ptr;
    pp--;
    printf("%x\n", *pp);
    for(int i=0; i < *pp; i++) {
        a[i] = 'c';
    }

    printf("%s\n", a);
}

void test_18() {
    unsigned char array[2] = {0};
    unsigned char *ptr = (unsigned char *)array;

    for(int i=0; i < 1; i++) {
        *ptr++ = 'c';
        *ptr++ = 'c';
        *ptr++ = 'c';
        ptr--;
        ptr--;
        ptr--;
    }

    printf("%s\n", array);
}

int * getPointer(void *p) {
    return (int *)p;
}

void test_19() {
    char array[5];
    char *p = array;

    for (int i = 0; i < 3; i++) {
        *getPointer(p + i) = 0x61616161;
    }

    printf("%s\n", p);
}

void test_20() {
    Person person;
    Person *p = &person;
    char array[100] = {};

    p->id = 300;
    for (int i = 0; i < p->id; i++) {
        array[i] = 'a';
    }

    printf("%s\n", array);
}

void test_21() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 0; i < 200; i++) {
        *(ptr + i) = 'a';
    }

    memset(ptr, 'a', 200);

    printf("%s\n", array);
}

void test_22() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 0; i < 200; i++) {
        *ptr++ = 'a';
    }

    memset(ptr, 'a', 200);

    printf("%s\n", array);
}

void test_23() {
    Person person1, person2;
    memset(&person2, 'a', sizeof(Person));

    Person *p = &person1;
    *p = person2;
    printf("%x\n", p->id);

    char array[100] = {};
    char *ptr = array;
    for (int i = 0; i < p->id; i++) {
        *ptr++ = 'a';
    }

    printf("%s\n", array);
}

void test_24() {
    Person person;
    char *p = (char *)&person;

    p++;
    p++;
    p++;
    p++;

    for (int i = 0; i < sizeof(Person); i++) {
        *p++ = 'a';
    }

    printf("%s\n", (char *)&person);
}

void test_25() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 200; i > 0; i--) {
        *(ptr + i) = 'a';
    }

    printf("%s\n", array);
}

void test_26() {
    char array[100] = {};
    char *ptr = array;
    int total = 200;
    int tmp = 0;

    for (int i = 200; i > 0; i--) {
        tmp = total - i;
        *(ptr + tmp) = 'a';
    }

    printf("%s\n", array);
}

void test_27() {
    char array[100] = {};

    for (int i = 200; i >= 0; i--) {
        array[i] = 'a';
    }

    printf("%s\n", array);
}

void test_28() {
    char array[100] = {};
    int total = 201;
    int tmp = 0;

    for (int i = 200; i > 0; i--) {
        tmp = total - i;
        array[tmp] = 'a';
    }

    printf("%s\n", array);
}

void test_29() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i < 200; i++, j++) {
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_30() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 100, j = 100; i < 200; i++, j++) {
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_31() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i < 100; i++, j++) {
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_32() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i < 100; i++, j++) {
        *(ptr + j) = 'a';
        j += 10;
    }

    printf("%s\n", array);
}

void test_33() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i < 100; i++, j+=12) {
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_34() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i < 100; i++) {
        *(ptr + j) = 'a';
        j+=12;
    }

    printf("%s\n", array);
}

int getIndex(int i) {
    return i - 10;
}

void test_35() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; getIndex(i) < 100; i++) {
        *(ptr + j) = 'a';
        j+=12;
    }

    printf("%s\n", array);
}

void test_36() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 90, j = 0; i - 10 < 100; i++) {
        *(ptr + j) = 'a';
        j+=12;
    }

    printf("%s\n", array);
}

void test_37() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 0;

    for (; i < 100; i++) {
        j+=12;
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_38() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 0;

    for (; i < 100; i++) {
        j+=12;
        *(ptr + 2 + j) = 'a';
    }

    printf("%s\n", array);
}

void test_39() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 0;

    for (; i < 100; i++) {
        j++;
        j *= 2;
        *(ptr + 2 + j) = 'a';
    }

    printf("%s\n", array);
}

void test_40() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 2;

    for (; i < 100; i++) {
        j *= 2;
        *(ptr + 2 + j) = 'a';
    }

    printf("%s\n", array);
}

void test_41() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 0;

    for (; i < 100; i++) {
        j--;
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_42() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 1;

    for (; i < 100; i++) {
        j++;
        *(ptr + (0xf&0xf) * j) = 'a';
    }

    printf("%s\n", array);
}

void test_43() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 1;

    for (; i < 100; i++) {
        j++;
        *(ptr + (0xf&0xf) * 10 - j) = 'a';
    }

    printf("%s\n", array);
}

void test_44() {
    char array[100] = {'a'};
    char *ptr = array;

    int i = 90;
    int j = 2;

    for (; i < 100; i++) {
        j = 10 + j;
        *(ptr + j) = 'a';
    }

    printf("%s\n", array);
}

void test_45() {
    char array[100] = {'a'};
    char *ptr = array;
    int j = 0;

    for (int i = 0; i < 200; i++) {
        i = 5 + i;
        *(ptr + j++) = 'a';
    }

    printf("%s\n", array);
}

void test_46() {
    char array[100] = {'a'};
    char *ptr = array;
    int j = 0;

    for (int i = 0; i < 200; i++) {
        *(ptr + j++) = 'a';
    }

    printf("%s\n", array);
}

void test_47() {
    char array[100] = {};
    char *ptr = array;

    for (int i = 0, j = 0; (i + j) < 200; i++, j++) {
        *(ptr + j) = 'a';
        j = 10 + j;
    }

    printf("%s\n", array);
}

void test_48() {
    char array[100] = {'a'};
    char *ptr = array;
    int j = 0;

    for (int i = 0; i < 200; i++) {
        i = 1 * i;
        *(ptr + j++) = 'a';
    }

    printf("%s\n", array);
}

void test_49() {
    char array[100] = {'a'};
    char *ptr = array;
    int j = 0;

    for (int i = 0; i < 250; i++) {
        i = 1 + i;
        *(ptr + j++) = 'a';
    }

    printf("%s\n", array);
}

void test_50() {
    char array[100] = {'a'};
    char *ptr = array;

    int j = 1;
    int x = 0xf;

    for (int i = 0; i < 10; i++) {
        j++;
        *(ptr + (x&x) - j) = 'a';
        x+=20;
    }

    printf("%s\n", array);
}

void test_51() {
    char array[100] = {};
    char *ptr = array;
    int x = 10;

    for (int i = 0, j = 0; i - x < 10; i++) {
        *(ptr + j) = 'a';
        j+=12;
    }

    printf("%s\n", array);
}

void test_52() {
    char array[100] = {};
    char *ptr = array;
    int x = 10;

    for (int i = 0, j = 0; i - x < 10; i++) {
        *(ptr + j) = 'a';
        j+=12;
        x++;
        x--;
    }

    printf("%s\n", array);
}

void test_53() {
    long array[10] = {};
    memset(array, 'a', 80);
    printf("%s\n", (char *)array);
}

void test_54() {
    int array[10] = {};
    memset(array, 'a', 80);
    printf("%s\n", (char *)array);
}

void test_55() {
    long array[10] = {};
    memset(array, 'a', 82);
    printf("%s\n", (char *)array);
}

void test_56(int total) {
    long array[10] = {};
    char *p = (char *)array;

    for(int i = 0; i < total; i++) {
        p[i] = 'a';
    }

    printf("%s\n", (char *)array);
}

void test_57() {
    long array[10] = {};
    char *p = (char *)array;

    for(int i = 0; i < 100;) {
        p[i] = 'a';
        i++;
    }

    printf("%s\n", (char *)array);
}

void test_58() {
    long array[10] = {};
    char *p = (char *)array;
    int j = 100;

    for(int i = 0; i < j;) {
        p[i] = 'a';
        i += 2;
        j += 1;
    }

    printf("%s\n", (char *)array);
}

int get_total() {
    return 100;
}

void test_59() {
    long array[10] = {};
    char *p = (char *)array;

    for(int i = 0; i < get_total();) {
        p[i] = 'a';
        i += 1;
    }

    printf("%s\n", (char *)array);
}

void mem_leak_sub_1(char *p) {
    strcpy(p, "hello world");
    printf("%s\n", p);
}

void mem_leak_1() {
    char *p = (char *)malloc(64);
    mem_leak_sub_1(p);
}

void mem_leak_sub_1_1(char *p) {
    strcpy(p, "hello world");
    printf("%s\n", p);
    free(p);
}

void mem_leak_1_1() {
    char *p = (char *)malloc(64);
    mem_leak_sub_1_1(p);
}

void mem_leak_1_2() {
    char *p = (char *)malloc(64);
    strcpy(p, "hello world");
    printf("%s\n", p);
}

void mem_leak_2() {
    char *p = (char *)malloc(64);
    srand((unsigned)time(NULL));
    int test = rand() % 10;

    if (test > 5) {
        strcpy(p, "hello world");
        printf("%s\n", p);
        free(p);
    }
}

void mem_leak_2_1() {
    char *p = (char *)malloc(64);
    if (p != NULL) {
        strcpy(p, "hello world");
        printf("%s\n", p);
        free(p);
    }
}

void mem_leak_3() {
    char *p = (char *)malloc(64);
    srand((unsigned)time(NULL));
    int test = rand() % 10;

    if (test > 5) {
        strcpy(p, "hello world");
        printf("%s\n", p);
    }
}

void mem_leak_3_1() {
    char *p = (char *)malloc(64);
    if (p != NULL) {
        strcpy(p, "hello world");
        printf("%s\n", p);
    }
}

void mem_leak_4() {
    char *p = (char *)malloc(64);
    for (int i = 0; i < 10; ++i) {
        strcpy(p, "hello world");
        printf("%s\n", p);
        free(p);
    }
}

void mem_leak_5() {
    char *p = (char *)malloc(64);
    for (int i = 0; i < 10; ++i) {
        strcpy(p, "hello world");
        printf("%s\n", p);
    }
}

char * mem_leak_sub_2() {
    return (char *)malloc(64);
}

void mem_leak_6() {
    char *p = mem_leak_sub_2();
    strcpy(p, "hello world");
    printf("%s\n", p);
    free(p);
}

void mem_leak_6_1() {
    char *p = mem_leak_sub_2();
    strcpy(p, "hello world");
    printf("%s\n", p);
}

char *gPbuff;
void mem_leak_sub_3() {
    gPbuff = (char *)malloc(64);
}

void mem_leak_7() {
    mem_leak_sub_3();
    char *p = gPbuff;
    strcpy(p, "hello world");
    printf("%s\n", p);
    free(p);
}

void mem_leak_7_1() {
    mem_leak_sub_3();
    char *p = gPbuff;
    strcpy(p, "hello world");
    printf("%s\n", p);
}

void pointer_1() {
    char buff[16];
    int data[] = {100, 200,300};
    int *array = data;
    array = &array[0];
    int d = array[1];
    memset(buff, d, d);
}

void pointer_2() {
    char buff[16];
    int data[] = {100, 200,300};
    int *array = data;
    array = &data[0];
    int d = array[1];
    memset(buff, d, d);
}

template<typename  T> void myswap(T& t1, T& t2) {
    T tmpT;
    tmpT = t1;
    t1 = t2;
    t2 = tmpT;
}
void test_refer() {
    char buff[16];

    int num1 = 1, num2 = 200;
    myswap<int>(num1, num2);
    int a = num1;
    memset(buff, 'a', a);
}

#pragma pack (1)
void test_size_calc() {
    //sizeof == 60
    typedef struct S1 {
        int name;
        char id;
        int a[12];
        char sex;
    }S2;

    struct S1 s1;
    S2 s2;

    printf("%lu\n", sizeof(s1));
    printf("%lu\n", sizeof(s2));

    memset(&s1, 'a', 54);
    memset(&s1, 'a', 55);

    memset(&s2, 'a', 54);
    memset(&s2, 'a', 55);
}

void test_size_calc2() {
    //sizeof == 60
    typedef struct S1 {
        int name;
        char id;
        char sex;
        struct {
            int a;
            int a1[12];
        }sss;
    }S2;

    struct S1 s1;
    S2 s2;

    printf("%lu\n", sizeof(s1));
    printf("%lu\n", sizeof(s2));

    memset(&s1, 'a', 58);
    memset(&s1, 'a', 59);

    memset(&s2, 'a', 58);
    memset(&s2, 'a', 59);
}
#pragma pack ()

void test_defend1() {
    int i = 120;
    char buff[32] = {0};

    if (i > 32) {
        return;
    }

    memset(buff, 'a', i);
}

void test_defend2() {
    int i = 120;
    char buff[32] = {0};

//    if (i > 32) {
//        return;
//    }

    memset(buff, 'a', i);
}

void test_if() {
    unsigned int i;
    puts("input:");
    scanf("%d", &i);

    unsigned char buff[10];
    if (i > 9) {
        i = 9;
    }
    buff[i] = 'a';

    memset(buff, 'a', i);
}

void test_if1() {
    unsigned int i;
    puts("input:");
    scanf("%d", &i);

    unsigned char buff[10];
    buff[i] = 'a';

    memset(buff, 'a', i);
}

void test_if2() {
    unsigned int i;
    puts("input:");
    scanf("%d", &i);

    unsigned char buff[10];

    buff[i] = 'a';
}

void test_int_overflow() {
    int i = 0xFFFFFF;

    printf("%d\n", i);
    printf("%d\n", i * 0xFF);
}

void test_5_1(void *pData) {
    int kind = 0;
    int flag = 0;
    void *ptr = NULL;

    printf("input kind:\n");
    scanf("%d", &kind);


    switch (kind) {
        case 1:
            flag = 100;
            ptr = malloc(100);
            break;
        case 2:
            flag = 200;
            ptr = malloc(200);
            break;
        default:
            flag = 300;
            ptr = malloc(64);
            break;
    }

    switch(kind) {
        case 1:
            memcpy(ptr, pData, flag * 10);
            break;
        case 2:
            memcpy(ptr, pData, flag * 10);
            break;
        default:
            memcpy(ptr, pData, 64);
            break;
    }

    printf("result: %s\n", (char *)ptr);
    free(ptr);
}

void test_5_2(void *pData) {
    int kind = 0;
    int flag = 0;
    void *ptr = NULL;

    printf("input kind:\n");
    scanf("%d", &kind);


    switch (kind) {
        case 1:
            flag = 100;
            ptr = malloc(100);
            break;
        case 2:
            flag = 200;
            ptr = malloc(200);
            break;
        default:
            flag = 300;
            ptr = malloc(64);
            break;
    }

    switch(kind) {
        case 1:
            if ((flag * 10) < 100) {
                memcpy(ptr, pData, flag * 10);
            }
            break;
        case 2:
            if ((flag * 10) < 200) {
                memcpy(ptr, pData, flag * 10);
            }
            break;
        default:
            if (flag < 64) {
                memcpy(ptr, pData, 64);
            }
            break;
    }

    printf("result: %s\n", (char *)ptr);
    free(ptr);
}

void sub_test_5(int kind, void *ptr, void *pData) {
    switch(kind) {
        case 1:
            memcpy(ptr, pData, 1000);
            break;
        case 2:
            memcpy(ptr, pData, 2000);
            break;
        default:
            memcpy(ptr, pData, 64);
            break;
    }
}

void test_5_3(void *pData) {
    int kind = 0;
    void *ptr = NULL;

    printf("input kind:\n");
    scanf("%d", &kind);


    switch (kind) {
        case 1:
            ptr = malloc(100);
            break;
        case 2:
            ptr = malloc(2000);
            break;
        case 3:
            ptr = malloc(300);
            break;
        default:
            ptr = malloc(64);
            break;
    }
    sub_test_5(kind, ptr, pData);
    printf("result: %s\n", (char *)ptr);
    free(ptr);
}

void test_multi_array_0() {
    int a[10][10] ={{1,2,3,4,5,6,7,8,9,10}};

    a[0][200] = 100;
    a[10][0] = 100;

    printf("max addr: %p, write addr: %p", &a[9][9], &a[0][99]);
    int b[][10] = {{1,2,3,4,5,6,7,8,9,10}, {}, {}};
    b[0][200] = 100;
    b[3][0] = 100;
}

void test_decrease() {
    char arr[32] = {};
    char *p = arr + 31; // 将指针p指向数组的最后一个元素

    for (int i = 0; i < 330; i++) {
        *(p--) = 'a'; // 通过--改变指针p的位置，并将'a'赋值给当前指向的元素
    }
    puts(arr);
}

void test_decrease_1() {
    char arr[32] = {};
    char *p = arr + 31; // 将指针p指向数组的最后一个元素

    int j = 0;
    for (int i = 0; i < 330; i++) {
        p[j--] = 'a'; // 通过--改变指针p的位置，并将'a'赋值给当前指向的元素
    }
}

void test_decrease_2() {
    char arr[32];
    char *p = arr + 31; // 将指针p指向数组的最后一个元素

    for (int i = 0; i < 32; i++) {
        *(p--) = 'a'; // 通过--改变指针p的位置，并将'a'赋值给当前指向的元素
    }

    p  = arr + 33;
    for (int i = 0; i < 33; i++) {
        *(p--) = 'a'; // 通过--改变指针p的位置，并将'a'赋值给当前指向的元素
    }
}

void test_different_increase_1() {
    char arr[32];
    char *p = arr; // 将int指针p指向数组arr的首地址

    // 第一次循环赋值
    for (int i = 0; i < 32; i++) {
        *(p++) = 0xff; // 通过++改变指针p的位置，并将0xffffffff赋值给当前指向的元素

    }

    // 第二次循环赋值
    p = arr;
    for (int i = 0; i < 330; i++) {
        *(p++) = 0xff; // 通过++改变指针p的位置，并将0xffffffff赋值给当前指向的元素
    }
}

void test_different_increase_2() {
    char arr[32];
    char *p = arr; // 将int指针p指向数组arr的首地址

    // 第一次循环赋值
    for (int i = 0; i < 32; i++) {
        *p = 0xff; // 通过++改变指针p的位置，并将0xffffffff赋值给当前指向的元素
        p++;
    }

    // 第二次循环赋值
    p = arr;
    for (int i = 0; i < 33; i++) {
        *p = 0xff; // 通过++改变指针p的位置，并将0xffffffff赋值给当前指向的元素
        p++;
    }
}

void test_different_increase_demo2() {
    int array[10];
    char *p = (char *)array;
    for (int i=0;i<39;i++) {
        *++p = 'a';
    }
    p = (char *)array;
    for (int i=0;i<40;i++) {
        *++p = 'a';
    }
}

void test_special_array() {
    int a[] = {1,2,3,4,5,6,7,8,9,10};
    int i = 2;
    i[a] = 100 * i[a];
    memset(a, 'a', i[a]);
}

class Trigger {
public:
    void setCount(int val) {
        this->count = val;
    }

    int getCount() {
        return this->count;
    }

    void process() {
        printf("count = %d\n", this->count);
        name[count] = 'a';
    }

private:
    int count;
    char name[10];
};

struct MyClass {
    typedef Trigger SubType;
};

template<typename T>
class MyTemp {
public:
    typename T::SubType* ptr;
    MyTemp(typename T::SubType* a) {
        ptr = a;
    }

    void print(int val) {
        ptr->setCount(val);
        ptr->process();
    }
};

void test_template_demo2() {
    Trigger a;
    MyTemp<MyClass> temp(&a);
    temp.print(12);
}

int main()
{
//    int a, b[], c[][];
//    void *p = malloc(10);
//    test_1(p);

//    char *buff = (char *)malloc(120);
//    test_2_mid(110, buff);

//    Person person;
//    test_3(&person);
//
//    void *p4;
//    test_4(p4);
//
//    char *p5 = (char *)malloc(2000);
//    test_5(p5);

//    test_6();

//    Person p;
//    test_7(&p);

//    void *p = malloc(sizeof(Person));
//    test_8(p);

//    Person p9;
//    test_9(&p9);
//
//    Person p10;
//    test_10(&p10);

//    Person p11;
//    test_11(&p11);

//    test_12();

//    test_12_1();

//    Person p9_1;
//    test_9_1(&p9_1);
//
//    test_15();
//
//    test_15_1();
//
//    test_15_2();

//    test_3_0();
//    test_3_1();
//    test_3_2();
//    test_3_3();

//    test_16();
//    test_3_4();

//    test_3_5();
//    test_3_6();

//    test_3_7();
//    test_3_8();

//    test_17();

//    test_18();

//    test_19();

//    test_20();

//    test_21();
//    test_22();

//    test_23();

//    test_24();

//    test_25();
//    test_26();
//    test_27();
//    test_28();

//    test_29();
//    test_30();
//    test_31();
//    test_32();
//    test_33();
//    test_34();

//    test_35();
//    test_36();
//    test_37();
//    test_38();
//    test_39();

//    test_40();
//    test_41();
//    test_42();
//    test_43();
//    test_44();

//    test_45();
//    test_46();
//    test_47();

//    test_48();
//    test_49();

//    test_50();

//    test_51();
//    test_52();

//    test_53();
//    test_54();
//    test_55();

//    test_56(100);
//    test_57();

//    test_58();
//    test_59();

//    mem_leak_1();
//    mem_leak_1_2();
//    mem_leak_2();
//    mem_leak_2_1();
//    mem_leak_3();
//    mem_leak_3_1();
//    mem_leak_4();
//    mem_leak_5();

//    mem_leak_6();
//    mem_leak_6_1();
//    mem_leak_7();
//    mem_leak_7_1();

//    pointer_1();
//    pointer_2();

//    test_refer();
//    test_size_calc();
//    test_size_calc2();

//    test_defend1();
//    test_defend2();

//    test_if();
//    test_if1();
//    test_if2();

//    test_int_overflow();

//    test_multi_array_0();
//    test_decrease();
//    test_different_increase_1();
//    test_different_increase_2();

//    test_special_array();
//    test_different_increase_demo2();
//    Person p;
//    test_7_demo(&p);
//    test_template_demo2();

    mem_leak_1_1();

    return 0;
}
