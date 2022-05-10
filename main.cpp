#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include <complex.h>

using namespace std;
struct ls;
typedef ls * link;

struct ls {
    complex<double> body;
    link pre;
    link next;
}
        *list, *t,*f;

int i,n,k,c;
complex<double> m, m1;

void randomize(){
    long a=time(0);
    srand(a);
}                       //    t->body  ~  *t.body
void add(complex<double> m){
    if(!list){
        list=new ls;
        list->body=m;
        list->next=list;
        list->pre=list;
    }
    else {
        t=new ls;
        t->body=m;
        f=list->pre;
        list->pre=t;
        f->next=t;
        t->next=list;
        t->pre=f;
    }
}

void addfirst(complex<double> m){
    if(!list){
        list=new ls;
        list->body=m;
        list->next=list;
        list->pre=list;
    }
    else {
        t=new ls;
        t->body=m;
        f=list;
        list=t;
        list->next=f;
        list->pre=f->pre;
        f->pre->next=list;
        f->pre=list;
    }
}

void genlist(int n){
    for(i=0;i<n;i++){
        m=complex<double>(rand()%100, rand()%100);
        add(m);
    }
}

void printlist()
{
    if(!list) printf("\nList is empty!\n");
    else {
        printf("\nList:\n[ ");
        t=list;
        do {
            printf("%2.2f + %2.2fi, ",real((t->body)),imag(t->body));
            fflush(stdout);
            t=t->next;
        } while(t!=list);
        printf("]\n");
    }
}

complex<double> read_val(){
    complex <double> num = {0, 0};
    float real, imag;
    printf("Enter real part: ");
    fflush(stdout);
    scanf("%f",&real);
    printf("Enter imaginary part: ");
    fflush(stdout);
    scanf("%f", &imag);
    num = complex<double>(real, imag);
    return num;
}

void deleting(complex<double> m){
    if(list->body==m){
        f=list;
        if(list->next==list)list=0; else
        {
            list=list->next;
            list->pre=f->pre;
            f->pre->next=list;
        }
        delete f;
    }
    else {
        t=list;
        c=0;
        do
        { if(t->next->body==m){
                f=t->next;
                t->next=f->next;
                f->next->pre=t;
                delete f;
                c=1;
                break;
            }
            t=t->next;
        } while(t->next!=list);
        if(!c) printf("\nItem with this value not exists!\n");
    } // else
} // deleting

void insert(complex<double> m, complex<double> m1){
    t=list;
    c=0;
    do  {
        if(t->body==m){
            f=new ls;
            f->body=m1;
            f->next=t->next;
            f->pre=t;
            t->next->pre=f;
            t->next=f;
            c=1; //if(t==list->pre) list=f;
            break;
        }
        t=t->next;
    } while(t!=list);
    if(!c) printf("\nItem with this value not exists!\n");
} // insert

void action(int K){
    t=list;
    i = 1;
    do{
        if(i%K == 0){
            deleting(t->body);
        }
        i++;
        t=t->next;
    }while(t!=list);
    printf("Successful!\n");
//    t=list;
//    c=0;
//    do  {
//        if(t->body==m){
//            m1=t->pre->body;
//            t->pre->body=t->next->body;
//            t->next->body=m1;
//            c=1;
//            break;
//        }
//        t=t->next;
//    } while(t!=list);
//    if(!c) printf("\nItem with this value not exists!\n");
} // action

int main(){
    list=0;
    k=9;
    randomize();
    for(;;){
        if(k==9) printf("\nInput from 1 to 10 or 0 for actions:\n"
                        "1. Generate a list.\n2. Add new items in end of the list.\n"
                        "3. Add new items in begin of the list.\n"
                        "4. Delete from the list.\n5. Print list.\n"
                        "6. Inserting in the list.\n7. Erase list.\n"
                        "8. Length of the list.\n9. Print this MENU\n"
                        "10. Main Action\n"
                        "0. Exit the program.\n");
        printf("\nInput number of MENU: k=");
        fflush(stdout);
        scanf("%d",&k);
        if(!k) break;
        if(k==1) {
            printf("\nInput number of new items of list: n=");
            fflush(stdout);
            scanf("%d",&n);
            genlist(n);
        }
        else if(k==2) {
            printf("\nInput value of adding item: \n"); //scanf("%d",&m);
            m=read_val();
            add(m);
        }
        else if(k==3) {
            printf("\nInput value of adding item: \n"); // scanf("%d",&m);
            m=read_val();
            addfirst(m);
        }
        else if(k==4) {
            if(!list) {
                printf("\nList is empty!\n"); continue;}
            printf("\nInput value of deleting item: \n"); // scanf("%d",&m);
            m=read_val();
            deleting(m);
        }
        else if(k==5) // if(!list)printf("\nList is empty!\n");else
            printlist();
        else if(k==6) {
            if(!list) {
                printf("\nList is empty!\n");
                continue;
            }
            printf("\nInput value inserting item:\n"); //scanf("%d",&m1);
            m1=read_val();
            printf("\nInput value item after which to insert: \n"); //scanf("%d",&m);
            m=read_val();
            insert(m,m1);
        }
        else if(k==7) {
            t=list;
            if(t)do{
                    f=t;
                    t=t->next;
                    delete f;
                }
                while(t!=list);
            list=0;
        }
        else if(k==8) {
            t=list;
            n=0;
            if(t)do{
                    t=t->next;
                    n++;
                } while(t!=list);
            printf("\nLength of the list=%d\n", n);
        }
        else if(k==10) {
            if(!list) {
                printf("\nList is empty!\n");
                continue;
            }
            printf("\nInput value for main action: K=");
            int K = 0;
            scanf("%d", &K);
            action(K);
        }
        else if(k>10) printf("Have no such number of MENU\n");
    } // for
} // main

