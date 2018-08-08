// wys++
// by wys
// 15-06-18

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <map>
#include <queue>

// #define debug(...) fprintf(stderr,__VA_ARGS__)
#define debug(...)

#define __MAIN

namespace InputManager {
	
	std::queue<int> buf;
	
	int n;
	
	inline void init()
	{
		std::cin>>n;
		int i;
		for (i=1;i<=n;i++) {
			int x;
			std::cin>>x;
			buf.push(x);
		}
	}
	
	inline int GetNextInt()
	{
		int ret=buf.front();
		buf.pop();
		return ret;
	}
	
};


// This is an "assembly language interpreter"
// by wys

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

#define report_runtime_error(...) {fprintf(stderr,"Runtime error: ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr);exit(1);}
#define report_error(...) {fprintf(stderr,"Error: ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr);exit(1);}

namespace ALI {
	
	template <int SIZE>
	struct Stack {
		int a[SIZE+1];
		int top;
		
		inline Stack()
		{
			top=0;
		}
		
		inline void push(int val)
		{
			// printf("PUSH %d\n",val);
			if (top==SIZE-1) {
				report_runtime_error("Stack overflow");
			}
			a[++top]=val;
		}
		
		inline int pop()
		{
			// printf("POPped %d\n",a[top]);
			if (top==0) {
				report_runtime_error("Stack underflow");
			}
			return a[top--];
		}
	};
	
	const int MEM_SIZE=1<<23;
	const int STACK_SIZE=1<<23;
	
	int __mem[MEM_SIZE];
	
	Stack<STACK_SIZE> ES,CS;
	
	
	
	
	// Instruction Pointer (IP)
	int IP=1;
	
	
	
	inline int GET_MEM(int p)
	{
		if (p<0 || p>=MEM_SIZE) {
			report_runtime_error("invalid memory address %d",p);
		}
		return __mem[p];
	}
	
	inline void SET_MEM(int p,int val)
	{
		if (p<0 || p>=MEM_SIZE) {
			report_runtime_error("invalid memory address %d",p);
		}
		__mem[p]=val;
	}
	
	
	
	struct Instruction {
		int type;
		int val;
	};
	
	const int MAX_INSTRUCTION_COUNT=10000000*4+100;
	
	Instruction I[MAX_INSTRUCTION_COUNT];
	
	int instruction_count=0;
	
	inline void add_instruction(int type,int val=0)
	{
		if (instruction_count==MAX_INSTRUCTION_COUNT) {
			report_runtime_error("Too many instructions");
		}
		I[++instruction_count]=(Instruction){type,val};
	}
	
	inline void add_instructions(std::vector<int> type,std::vector<int> val={})
	{
		int size=type.size();
		if (size!=(int)val.size()) {
			val=std::vector<int>(size);
		}
		int i;
		for (i=0;i<size;i++) {
			add_instruction(type[i],val[i]);
		}
	}
	
	int clock_cycles=0;
	
	
	
	
	
	const int MAX_INSTRUCTION_TYPE_ID=10000;
	
	// Instruction types
	const int I_UNDEFINED=0;
	const int I_NOP=1;	// no operation
	const int I_HALT=2;
	
	const int I_PUSH=100;	// push val to ES
	const int I_POP=101;	// pop
	const int I_DUP=102;	// duplicate top
	const int I_SWAP=103;
	
	const int I_PUSH_INT=110;	// push an int variable (and its ref) to ES, and clear it
	const int I_PUSH_ARR=111;	// push a segment of mem to ES
	const int I_PUSH_TO_CS=112;	// cnt = pop(), then push cnt values to CS
	
	const int I_POP_INT=120;	// = I_WRITEP
	const int I_POP_ARR=121;
	const int I_POP_FROM_CS=122;	// cnt = pop(), then pop cnt values from CS
	
	const int I_MEMSET=130;	// memset(start,len)
	const int I_MEMSET_1=131;	/// memset(start,1)
	
	const int I_READP=200;	// push(*pop())
	// const int I_READM=201;	// push(*(MEM + pop()))
	// const int I_READV=202;	// push(*(VSB - pop()))
	
	const int I_WRITEP=300;	// B = pop(), A = pop(), *A = B
	// const int I_WRITEM=301;	// B = pop(), A = pop(), *(MEM + A) = B
	// const int I_WRITEV=302;	// B = pop(), A = pop(), *(VSB - A) = B
	
	const int I_JUMP=400;	// A = pop(), jump to A
	const int I_JUMPZ=401;	// B = pop(), A = pop(), if (A==0) jump to B
	const int I_JUMPNZ=401;	// B = pop(), A = pop(), if (A!=0) jump to B
	
	
	const int I_CALL=500;	// A = pop(), CS.push(A + 1), jump to A
	const int I_RET=502;	// jump to CS.pop()
	
	const int I_CIN=600;	// push(CIN())
	const int I_COUT=601;	// COUT(pop())
	const int I_GETCHAR=602;	// push(getchar())
	const int I_PUTCHAR=603;	// putchar(pop())
	
	const int I_DEREFERENCE=1001;	// push(*pop())
	const int I_GET_OPPOSITE_NUMBER=1002;	// push(-pop())
	const int I_ADD=1003;	// B = pop(), A = pop(), push(A + B)
	const int I_SUB=1004;	// B = pop(), A = pop(), push(A - B)
	
	const int I_BITWISE_NOT=1005;	// push(~pop())
	const int I_LOGICAL_NOT=1006;	// push(!pop())
	const int I_MULTIPLY=1007;	// B = pop(), A = pop(), push(A * B)
	const int I_DIVISION=1008;	// B = pop(), A = pop(), push(A / B)
	const int I_MODULO=1009;	// B = pop(), A = pop(), push(A % B)
	const int I_SHIFT_RIGHT=1010;	// B = pop(), A = pop(), push(A >> B)
	const int I_SHIFT_LEFT=1011;	// B = pop(), A = pop(), push(A << B)
	const int I_GREATER=1012;	// B = pop(), A = pop(), push(A > B)
	const int I_LESS=1013;	// B = pop(), A = pop(), push(A < B)
	const int I_GREATER_OR_EQUAL=1014;	// B = pop(), A = pop(), push(A >= B)
	const int I_LESS_OR_EQUAL=1015;	// B = pop(), A = pop(), push(A <= B)
	const int I_EQUAL=1016;	// B = pop(), A = pop(), push(A == B)
	const int I_NOT_EQUAL=1017;	// B = pop(), A = pop(), push(A != B)
	const int I_BITWISE_AND=1018;	// B = pop(), A = pop(), push(A & B)
	const int I_BITWISE_XOR=1019;	// B = pop(), A = pop(), push(A ^ B)
	const int I_BITWISE_OR=1020;	// B = pop(), A = pop(), push(A | B)
	const int I_LOGICAL_AND=1021;	// B = pop(), A = pop(), push(A && B)
	const int I_LOGICAL_OR=1022;	// B = pop(), A = pop(), push(A || B)
	
	
	
	// instruction implementations ("instruction functions")
	
	inline void IF_NOP()
	{
		// no operation
		++IP;
	}
	
	inline void IF_PUSH(int val)
	{
		ES.push(val);
		++IP;
	}
	
	inline void IF_POP()
	{
		// pop
		ES.pop();
		++IP;
	}
	
	inline void IF_DUP()
	{
		// duplicate
		int val=ES.pop();
		ES.push(val);
		ES.push(val);
		++IP;
	}
	
	inline void IF_SWAP()
	{
		// swap
		int a=ES.pop(),b=ES.pop();
		ES.push(a);ES.push(b);
		++IP;
	}
	
	inline void IF_PUSH_INT()
	{
		int ref=ES.pop();
		ES.push(ref);
		ES.push(GET_MEM(ref));
		SET_MEM(ref,0);
		++IP;
	}
	
	inline void IF_POP_INT()
	{
		// = I_WRITEP
		int A,B;
		B=ES.pop();
		A=ES.pop();
		SET_MEM(A,B);
		++IP;
	}
	
	inline void IF_PUSH_ARR()
	{
		int start,cnt;
		cnt=ES.pop();
		start=ES.pop();
		if (cnt<0) report_runtime_error("invalid PUSH_ARR count");
		int i;
		for (i=0;i<cnt;i++) {
			ES.push(GET_MEM(start+i));
			SET_MEM(start+i,0);
		}
		// ES.push(start);
		// ES.push(cnt);
		++IP;
	}
	
	inline void IF_POP_ARR()
	{
		int start,cnt;
		cnt=ES.pop();
		start=ES.pop();
		int i;
		for (i=cnt-1;i>=0;i--) {
			int val=ES.pop();
			SET_MEM(start+i,val);
		}
		++IP;
	}
	
	inline void IF_PUSH_TO_CS()
	{
		int cnt;
		cnt=ES.pop();
		if (cnt<0) report_runtime_error("invalid PUSH_TO_CS count");
		while (cnt--) {
			CS.push(ES.pop());
		}
		++IP;
	}
	
	inline void IF_POP_FROM_CS()
	{
		int cnt;
		cnt=ES.pop();
		if (cnt<0) report_runtime_error("invalid POP_FROM_CS count");
		while (cnt--) {
			ES.push(CS.pop());
		}
		++IP;
	}
	
	inline void IF_MEMSET()
	{
		int start,cnt;
		cnt=ES.pop();
		start=ES.pop();
		if (cnt<0) report_runtime_error("invalid MEMSET count");
		int i;
		for (i=0;i<cnt;i++) {
			SET_MEM(start+i,0);
		}
		++IP;
	}
	
	inline void IF_MEMSET_1()
	{
		int start;
		start=ES.pop();
		SET_MEM(start,0);
		++IP;
	}
	
	inline void IF_READP()
	{
		int p=ES.pop();
		int val=GET_MEM(p);
		ES.push(val);
		++IP;
	}
	
	inline void IF_WRITEP()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		SET_MEM(A,B);
		++IP;
	}
	
	inline void IF_JUMP()
	{
		int x=ES.pop();
		IP=x;
	}
	
	inline void IF_JUMPZ()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		// printf("JZ A = %d B = %d\n",A,B);
		if (A==0) {
			IP=B;
		} else {
			++IP;
		}
	}
	
	inline void IF_JUMPNZ()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		if (A!=0) {
			IP=B;
		} else {
			++IP;
		}
	}
	
	inline void IF_CALL()
	{
		int p=ES.pop();
		CS.push(IP+1);
		IP=p;
	}
	
	inline void IF_RET()
	{
		IP=CS.pop();
	}
	
	inline void IF_CIN()
	{
		int val;
		// std::cin>>val;
		val=InputManager::GetNextInt();
		ES.push(val);
		++IP;
	}
	
	inline void IF_COUT()
	{
		int val=ES.pop();
		std::cout<<val;
		++IP;
	}
	
	inline void IF_GETCHAR()
	{
		int val=getchar();
		ES.push(val);
		++IP;
	}
	
	inline void IF_PUTCHAR()
	{
		int val=ES.pop();
		putchar(val);
		++IP;
	}
	
	inline void IF_DEREFERENCE()
	{
		int p=ES.pop();
		int val=GET_MEM(p);
		ES.push(val);
		++IP;
	}
	
	inline void IF_GET_OPPOSITE_NUMBER()
	{
		int val=ES.pop();
		ES.push(-val);
		++IP;
	}
	
	inline void IF_ADD()
	{
		int A,B;
		B=ES.pop();A=ES.pop();
		ES.push(A+B);
		++IP;
	}
	
	inline void IF_SUB()
	{
		int A,B;
		B=ES.pop();A=ES.pop();
		ES.push(A-B);
		++IP;
	}
	
	inline void IF_BITWISE_NOT()
	{
		int A=ES.pop();
		ES.push(~A);
		++IP;
	}
	
	inline void IF_LOGICAL_NOT()
	{
		int A=ES.pop();
		ES.push(!A);
		++IP;
	}
	
	inline void IF_MULTIPLY()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A*B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_DIVISION()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		if (B==0) {
			report_runtime_error("division by zero");
		}
		int val=A/B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_MODULO()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		if (B==0) {
			report_runtime_error("division by zero");
		}
		int val=A%B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_SHIFT_RIGHT()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A>>B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_SHIFT_LEFT()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A<<B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_GREATER()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A>B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_LESS()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A<B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_GREATER_OR_EQUAL()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A>=B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_LESS_OR_EQUAL()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A<=B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_EQUAL()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A==B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_NOT_EQUAL()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A!=B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_BITWISE_AND()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A&B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_BITWISE_XOR()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A^B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_BITWISE_OR()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A|B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_LOGICAL_AND()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A&&B;
		ES.push(val);
		++IP;
	}
	
	inline void IF_LOGICAL_OR()
	{
		int A,B;
		B=ES.pop();
		A=ES.pop();
		int val=A||B;
		ES.push(val);
		++IP;
	}
	
	
	
	
	typedef void (*P_VOID)();
	P_VOID IFs[MAX_INSTRUCTION_TYPE_ID+1];
	
	std::string I_names[MAX_INSTRUCTION_TYPE_ID+1];
	
	
	
	inline void run()
	{
		while (1) {
			++clock_cycles;
			// if (clock_cycles>100)break;
			// printf("cc = %d *1 = %d *2 = %d IP = %d\n",clock_cycles,GET_MEM(1),GET_MEM(2),IP);
			if (IP<1 || IP>instruction_count) {
				report_runtime_error("invalid instruction pointer");
			}
			int type=I[IP].type;
			if (type<0 || type>MAX_INSTRUCTION_TYPE_ID) {
				report_runtime_error("invalid instruction (IP = %d, type = %d)",IP,type);
			}
			if (type==I_HALT) {
				break;
			} else if (type==I_PUSH) {
				IF_PUSH(I[IP].val);
			} else if (!IFs[type]) {
				report_runtime_error("invalid instruction (IP = %d, type = %d)",IP,type);
			} else {
				IFs[type]();
			}
		}
	}
	
	
	inline void out(FILE *f=stdout)
	{
		int i;
		for (i=1;i<=instruction_count;i++) {
			int type=I[i].type;
			if (type<0 || type>MAX_INSTRUCTION_TYPE_ID) {
				report_error("invalid instruction (i = %d, type = %d)",i,type);
			}
			fprintf(f,"%s",I_names[type].c_str());
			if (type==I_PUSH) {
				fprintf(f," %d",I[i].val);
			}
			fprintf(f,"\n");
		}
	}
	
	
	inline void init()
	{
		IFs[I_NOP]=IF_NOP;
		// no IF_HALT
		
		// no IF_PUSH
		IFs[I_POP]=IF_POP;
		IFs[I_DUP]=IF_DUP;
		IFs[I_SWAP]=IF_SWAP;
		
		IFs[I_PUSH_INT]=IF_PUSH_INT;
		IFs[I_PUSH_ARR]=IF_PUSH_ARR;
		IFs[I_POP_INT]=IF_POP_INT;
		IFs[I_POP_ARR]=IF_POP_ARR;
		IFs[I_PUSH_TO_CS]=IF_PUSH_TO_CS;
		IFs[I_POP_FROM_CS]=IF_POP_FROM_CS;
		IFs[I_MEMSET]=IF_MEMSET;
		IFs[I_MEMSET_1]=IF_MEMSET_1;
		
		IFs[I_READP]=IF_READP;
		// IFs[I_READM]=IF_READM;
		// IFs[I_READV]=IF_READV;
		
		IFs[I_WRITEP]=IF_WRITEP;
		// IFs[I_WRITEM]=IF_WRITEM;
		// IFs[I_WRITEV]=IF_WRITEV;
		
		IFs[I_JUMP]=IF_JUMP;
		IFs[I_JUMPNZ]=IF_JUMPNZ;
		IFs[I_JUMPZ]=IF_JUMPZ;
		
		IFs[I_CALL]=IF_CALL;
		IFs[I_RET]=IF_RET;
		
		IFs[I_CIN]=IF_CIN;
		IFs[I_COUT]=IF_COUT;
		IFs[I_GETCHAR]=IF_GETCHAR;
		IFs[I_PUTCHAR]=IF_PUTCHAR;
		
		IFs[I_DEREFERENCE]=IF_DEREFERENCE;
		IFs[I_GET_OPPOSITE_NUMBER]=IF_GET_OPPOSITE_NUMBER;
		IFs[I_ADD]=IF_ADD;
		IFs[I_SUB]=IF_SUB;
		
		IFs[I_BITWISE_NOT]=IF_BITWISE_NOT;
		IFs[I_LOGICAL_NOT]=IF_LOGICAL_NOT;
		IFs[I_MULTIPLY]=IF_MULTIPLY;
		IFs[I_DIVISION]=IF_DIVISION;
		IFs[I_MODULO]=IF_MODULO;
		IFs[I_SHIFT_RIGHT]=IF_SHIFT_RIGHT;
		IFs[I_SHIFT_LEFT]=IF_SHIFT_LEFT;
		IFs[I_GREATER]=IF_GREATER;
		IFs[I_LESS]=IF_LESS;
		IFs[I_GREATER_OR_EQUAL]=IF_GREATER_OR_EQUAL;
		IFs[I_LESS_OR_EQUAL]=IF_LESS_OR_EQUAL;
		IFs[I_EQUAL]=IF_EQUAL;
		IFs[I_NOT_EQUAL]=IF_NOT_EQUAL;
		IFs[I_BITWISE_AND]=IF_BITWISE_AND;
		IFs[I_BITWISE_XOR]=IF_BITWISE_XOR;
		IFs[I_BITWISE_OR]=IF_BITWISE_OR;
		IFs[I_LOGICAL_AND]=IF_LOGICAL_AND;
		IFs[I_LOGICAL_OR]=IF_LOGICAL_OR;
		
		
		
		// init names
		
		I_names[I_NOP]="NOP";
		I_names[I_HALT]="HALT";
		
		I_names[I_PUSH]="PUSH";
		I_names[I_POP]="POP";
		I_names[I_DUP]="DUP";
		I_names[I_SWAP]="SWAP";
		
		I_names[I_PUSH_INT]="PUSH_INT";
		I_names[I_PUSH_ARR]="PUSH_ARR";
		I_names[I_POP_INT]="POP_INT";
		I_names[I_POP_ARR]="POP_ARR";
		I_names[I_PUSH_TO_CS]="PUSH_TO_CS";
		I_names[I_POP_FROM_CS]="POP_FROM_CS";
		I_names[I_MEMSET]="MEMSET";
		I_names[I_MEMSET_1]="MEMSET_1";
		
		I_names[I_READP]="READP";
		// I_names[I_READM]="READM";
		// I_names[I_READV]="READV";
		
		I_names[I_WRITEP]="WRITEP";
		// I_names[I_WRITEM]="WRITEM";
		// I_names[I_WRITEV]="WRITEV";
		
		I_names[I_JUMP]="JUMP";
		I_names[I_JUMPNZ]="JUMPNZ";
		I_names[I_JUMPZ]="JUMPZ";
		
		I_names[I_CALL]="CALL";
		I_names[I_RET]="RET";
		
		I_names[I_CIN]="CIN";
		I_names[I_COUT]="COUT";
		I_names[I_GETCHAR]="GETCHAR";
		I_names[I_PUTCHAR]="PUTCHAR";
		
		I_names[I_DEREFERENCE]="DEREFERENCE";
		I_names[I_GET_OPPOSITE_NUMBER]="GET_OPPOSITE_NUMBER";
		I_names[I_ADD]="ADD";
		I_names[I_SUB]="SUB";
		
		I_names[I_BITWISE_NOT]="BITWISE_NOT";
		I_names[I_LOGICAL_NOT]="LOGICAL_NOT";
		I_names[I_MULTIPLY]="MULTIPLY";
		I_names[I_DIVISION]="DIVISION";
		I_names[I_MODULO]="MODULO";
		I_names[I_SHIFT_RIGHT]="SHIFT_RIGHT";
		I_names[I_SHIFT_LEFT]="SHIFT_LEFT";
		I_names[I_GREATER]="GREATER";
		I_names[I_LESS]="LESS";
		I_names[I_GREATER_OR_EQUAL]="GREATER_OR_EQUAL";
		I_names[I_LESS_OR_EQUAL]="LESS_OR_EQUAL";
		I_names[I_EQUAL]="EQUAL";
		I_names[I_NOT_EQUAL]="NOT_EQUAL";
		I_names[I_BITWISE_AND]="BITWISE_AND";
		I_names[I_BITWISE_XOR]="BITWISE_XOR";
		I_names[I_BITWISE_OR]="BITWISE_OR";
		I_names[I_LOGICAL_AND]="LOGICAL_AND";
		I_names[I_LOGICAL_OR]="LOGICAL_OR";
	}
	
	
	
}

inline void init_test_prog_1()
{
	// c++11 needed
	ALI::add_instructions({ALI::I_CIN,ALI::I_CIN,ALI::I_ADD,ALI::I_COUT});
	ALI::add_instruction(ALI::I_PUSH,'\n');
	ALI::add_instruction(ALI::I_PUTCHAR);
	ALI::add_instruction(ALI::I_HALT);
}

#ifndef __MAIN

int main()
{
	ALI::init();
	init_test_prog_1();
	ALI::run();
	
}

#endif


namespace Scanner {
	int line_num;
	int column_num;
	// char next;
	char now;
	
	inline char get_char()
	{
		if (now!='\n') {
			++column_num;
		} else {
			++line_num;
			column_num=1;
		};
		// now=next;
		// next=getchar();
		now=getchar();
		return now;
	}
	
	inline void init()
	{
		line_num=1;
		column_num=1;
		now=getchar();
		// next=getchar();
	}
	
	inline void report_pos(FILE *f)
	{
		fprintf(f,":%d:%d: ",line_num,column_num);
	}
}

inline bool is_digit(char ch)
{
	return ch>='0' && ch<='9';
}

inline bool is_letter(char ch)
{
	return (ch>='A' && ch<='Z') || (ch>='a' && ch<='z');
}

inline bool is_empty_char(char ch)
{
	return ch=='\n' || ch=='\r' || ch==' ' || ch=='\t';
}

#define report_compile_error(...) {Scanner::report_pos(stderr);fprintf(stderr,"error: ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr);exit(1);}
#define report_runtime_error(...) {fprintf(stderr,"Runtime error: ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr);exit(1);}
#define report_error(...) {fprintf(stderr,"Error: ");fprintf(stderr,__VA_ARGS__);fprintf(stderr,"\n");fflush(stderr);exit(1);}

const int TOKEN_UNDEFINED=0;
const int TOKEN_EOF=1;
const int TOKEN_EMPTY=2;
const int TOKEN_NAME=3;
const int TOKEN_INT_CONSTANT=4;
const int TOKEN_SYMBOL=5;

const char *TOKEN_TYPENAME[6]={"UNDEFINED","EOF","EMPTY","NAME","INT_CONSTANT","SYMBOL"};

inline int get_token_type(const std::string &s)
{
	if (!s.length()) return TOKEN_UNDEFINED;
	char ch=s[0];
	if (ch==EOF) return TOKEN_EOF;
	if (is_empty_char(ch)) return TOKEN_EMPTY;
	if (ch=='_' || is_letter(ch)) return TOKEN_NAME;
	if (is_digit(ch)) return TOKEN_INT_CONSTANT;
	return TOKEN_SYMBOL;
}

namespace Tokenizer {
	
	inline std::string get_word()
	{
		std::string ret;
		char ch=Scanner::now;
		if (ch==EOF) {
			ret.append(1,ch);
			return ret;
		} else if (is_empty_char(ch)) {
			ret.append(1,ch);
			Scanner::get_char();
			return ret;
		} else if (ch=='#') {
			ret.append(1,ch);
			Scanner::get_char();
			return ret;
		} else if (ch=='_' || is_letter(ch)) {
			while (ch=='_' || is_letter(ch) || is_digit(ch)) {
				ret.append(1,ch);
				ch=Scanner::get_char();
			}
			return ret;
		} else if (is_digit(ch)) {
			while (is_digit(ch)) {
				ret.append(1,ch);
				ch=Scanner::get_char();
				if (ch=='_' || is_letter(ch)) {
					std::string tmp=get_word();
					report_compile_error("invalid suffix \"%s\" on integer constant",tmp.c_str());
				}
			}
			return ret;
		} else if (ch=='+') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=' || ch=='+') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='-') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=' || ch=='-') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='*') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='/') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='(') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch==')') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch==')' || ch=='{' || ch=='}' || ch==';' || ch=='.' || ch=='[' || ch==']' || ch==',') {
			ret.append(1,ch);
			Scanner::get_char();
			return ret;
		} else if (ch=='<') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=' || ch=='<') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='>') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=' || ch=='>') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='=') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='!') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='&') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='&' || ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='|') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='|' || ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='^') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='%') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch=='=') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else if (ch=='?') {
			ret.append(1,ch);
			Scanner::get_char();
			return ret;
		} else if (ch==':') {
			ret.append(1,ch);
			ch=Scanner::get_char();
			if (ch==':') {
				ret.append(1,ch);
				Scanner::get_char();
			}
			return ret;
		} else {
			report_compile_error("invalid character \\%d",ch);
			return ret;
		}
	}
	
	std::string now;
	int now_type;
	
	inline std::string get_token()
	{
		std::string ret;
		while (1) {
			ret=get_word();
			int type=get_token_type(ret);
			if (type==TOKEN_UNDEFINED) {
				report_compile_error("undefined token");
			}
			if (type!=TOKEN_EMPTY) {
				break;
			}
		}
		now=ret;
		now_type=get_token_type(now);
		return ret;
	}
	
	inline void init()
	{
		get_token();
	}
	
}

inline void assert_token(const std::string &a,const char *b)
{
	if (a!=b) {
		report_compile_error("expected \"%s\", but \"%s\" found",b,a.c_str());
	}
}

inline void assert_token_type(const int a,const int b)
{
	if (a!=b) {
		report_compile_error("expected %s, but %s found",TOKEN_TYPENAME[b],TOKEN_TYPENAME[a]);
	}
}








struct Linked_List {
	Linked_List *next;
	int x;
	int size;
	
	inline Linked_List(){}
	
	inline Linked_List(Linked_List *_next,int _x)
	{
		next=_next;
		x=_x;
		size=_next->size*_x;
	}
};

Linked_List *null;

inline void Linked_List_Init()
{
	null=new Linked_List();
	null->next=null;
	null->x=null->size=1;
}











const int NODE_UNDEFINED=0;
const int NODE_NAME=1;
const int NODE_INT_CONSTANT=2;

const int NODE_RIGHT_PLUS_PLUS=200;
const int NODE_RIGHT_MINUS_MINUS=201;
const int NODE_CALL_FUNCTION=202;
const int NODE_SQUARE_BRACKET=203;

const int NODE_LEFT_PLUS_PLUS=300;
const int NODE_LEFT_MINUS_MINUS=301;
const int NODE_BITWISE_NOT=302;
const int NODE_LOGICAL_NOT=303;
const int NODE_LEFT_PLUS=304;
const int NODE_LEFT_MINUS=305;
const int NODE_REFERENCE=306;
const int NODE_DEREFERENCE=307;

const int NODE_MULTIPLY=500;
const int NODE_DIVISION=501;
const int NODE_MODULO=502;

const int NODE_PLUS=600;
const int NODE_MINUS=601;

const int NODE_SHIFT_RIGHT=700;
const int NODE_SHIFT_LEFT=701;

const int NODE_GREATER=800;
const int NODE_LESS=801;
const int NODE_GREATER_OR_EQUAL=802;
const int NODE_LESS_OR_EQUAL=803;

const int NODE_EQUAL=900;
const int NODE_NOT_EQUAL=901;

const int NODE_BITWISE_AND=1000;

const int NODE_BITWISE_XOR=1100;

const int NODE_BITWISE_OR=1200;

const int NODE_LOGICAL_AND=1300;

const int NODE_LOGICAL_OR=1400;

const int NODE_ASSIGN=1500;
const int NODE_ASSIGN_MULTIPLY=1501;
const int NODE_ASSIGN_DIVISION=1502;
const int NODE_ASSIGN_MODULO=1503;
const int NODE_ASSIGN_PLUS=1504;
const int NODE_ASSIGN_MINUS=1505;
const int NODE_ASSIGN_SHIFT_RIGHT=1506;
const int NODE_ASSIGN_SHIFT_LEFT=1507;
const int NODE_ASSIGN_BITWISE_AND=1508;
const int NODE_ASSIGN_BITWISE_XOR=1509;
const int NODE_ASSIGN_BITWISE_OR=1510;

const int NODE_COMMA=1600;


const int NODE_EMPTY_STATEMENT=9999;
const int NODE_CURLY_BRACKET=10000;
const int NODE_IF=11000;
const int NODE_WHILE=12000;
const int NODE_FOR=13000;	 // ch[0~3]
const int NODE_DEFINE_VAR=20000;

const int NODE_FUNCTION=30000;
const int NODE_FUNCTION_ARG=30100;
const int NODE_RETURN=30200;	// ->r


struct AST_node {
	AST_node *l,*r;
	std::string x;
	int type;
	std::vector<AST_node*> *a;
	int IC;	// instruction count
	int IC_clear;
	int VC;	// variable count (including arrays)
	Linked_List *arr_type;
};

inline void out(AST_node *x);

inline void out(std::vector<AST_node*> *a,const char *s)
{
	int size=a->size();
	int i;
	for (i=0;i<size;i++) {
		out(a->at(i));
		if (i+1<size) printf("%s",s);
	}
}

inline void out_define_var(AST_node *a)
{
	printf("%s",a->x.c_str());
	Linked_List *t=a->arr_type;
	while (t!=null) {
		printf("[%d]",t->x);
		t=t->next;
	}
}

inline void out_define_var(std::vector<AST_node*> *a)
{
	int size=a->size();
	int i;
	for (i=0;i<size;i++) {
		out_define_var(a->at(i));
		if (i+1<size) printf(", ");
	}
}

inline void out(AST_node *x)
{
	switch (x->type) {
		case NODE_UNDEFINED:
			throw "unknown node type";
			break;
		case NODE_EMPTY_STATEMENT:
			printf(";");
			break;
		case NODE_NAME:
			printf("%s",x->x.c_str());
			break;
		case NODE_INT_CONSTANT:
			printf("%s",x->x.c_str());
			break;
		case NODE_CALL_FUNCTION:
			printf("(");
			if (x->l) out(x->l);
			printf("(");
			out(x->a,", ");
			printf(")");
			printf(")");
			break;
		case NODE_CURLY_BRACKET:
			printf("{ ");
			out(x->a,"; ");
			if (x->a->size()) printf(";");
			printf(" }");
			break;
		case NODE_IF:
			printf("if (");
			out(x->a->at(0));
			printf(") ");
			out(x->l);
			if (x->r) {
				printf(" else ");
				out(x->r);
			}
			break;
		case NODE_WHILE:
			printf("while (");
			out(x->l);
			printf(") ");
			out(x->r);
			break;
		case NODE_FOR:
			// for (ch[0] ch[1] ch[2]) ch[3]
			printf("for (");
			out(x->a->at(0));
			printf(" ");
			out(x->a->at(1));
			if (x->a->at(1)->type!=NODE_EMPTY_STATEMENT) {
				printf(";");
			}
			printf(" ");
			if (x->a->at(2)->type!=NODE_EMPTY_STATEMENT) {
				out(x->a->at(2));
			}
			printf(") ");
			out(x->a->at(3));
			break;
		case NODE_DEFINE_VAR:
			printf("int ");
			out_define_var(x->a);
			printf("; ");
			break;
		case NODE_FUNCTION:
			printf("int %s(",x->x.c_str());
			int i;
			for (i=0;i<(int)x->a->size();i++) {
				AST_node *t=x->a->at(i);
				if (t->type!=NODE_FUNCTION_ARG) {
					break;
				} else {
					if (i>0) {
						printf(", ");
					}
					printf("int %s",t->x.c_str());
				}
			}
			printf(")\n");
			printf("{\n");
			for (;i<(int)x->a->size();i++) {
				printf("		");
				out(x->a->at(i));
				printf(";\n");
			}
			printf("}\n");
			break;
		case NODE_RETURN:
			printf("return ");
			out(x->r);
			printf(";");
			break;
		default:
			printf("(");
			if (x->l) out(x->l);
			printf(" %s ",x->x.c_str());
			if (x->r) out(x->r);
			if (x->x=="[") printf(" ]");
			printf(")");
			break;
	}
}







const int DATA_UNDEFINED=0;
const int DATA_VOID=1;
const int DATA_LVALUE=2;
const int DATA_RVALUE=3;
const int DATA_CIN=4;
const int DATA_COUT=5;
const int DATA_ENDL=6;

const char *DATA_TYPE_NAME[10]={
	"UNDEFINED",
	"VOID",
	"LVALUE",
	"RVALUE",
	"CIN",
	"COUT",
	"ENDL"
};


struct Data {
	int type;
	Linked_List *arr_type;
	
	inline Data(){}
	
	inline Data(int _type,Linked_List *_arr_type)
	{
		type=_type;
		arr_type=_arr_type;
	}
	
	inline Data(int _type)
	{
		type=_type;
		arr_type=null;
	}
};





inline void assert_data_int_type(const Data &a)
{
	if (a.arr_type!=null) {
		report_error("int type expected, but array found");
	}
}





inline void data_clear(Data x)
{
	switch (x.type) {
		case DATA_UNDEFINED:
			throw "unknown data type";
			break;
		case DATA_VOID:
			break;
		case DATA_LVALUE:
		case DATA_RVALUE:
			ALI::add_instruction(ALI::I_POP);
			break;
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			break;
		default:
			throw "unknow data type";
			break;
	}
}

inline Data data_get_rvalue(Data x)
{
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			report_runtime_error("cannot cast %s to %s",DATA_TYPE_NAME[x.type],DATA_TYPE_NAME[DATA_RVALUE]);
			break;
		case DATA_LVALUE:
			if (x.arr_type!=null) {
				// x.arr_type=x.arr_type->next;
				// do nothing
				// ???
				
			} else {
				ALI::add_instruction(ALI::I_DEREFERENCE);
			}//TODO here (?)
			break;
		case DATA_RVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// return DATA_RVALUE;
	x.type=DATA_RVALUE;
	return x;
}

inline Data data_get_lvalue(Data x)
{
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
		case DATA_RVALUE:
			report_runtime_error("cannot cast %s to %s",DATA_TYPE_NAME[x.type],DATA_TYPE_NAME[DATA_LVALUE]);
		case DATA_LVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// return DATA_LVALUE;
	x.type=DATA_LVALUE;
	return x;
}

inline Data data_get_reference(Data x)
{
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
		case DATA_RVALUE:
			report_runtime_error("cannot get %s's reference",DATA_TYPE_NAME[x.type]);
			break;
		case DATA_LVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// return DATA_RVALUE;
	x.type=DATA_RVALUE;
	return x;
}

// returns: DATA_LVALUE (ref)
inline Data data_dereference(Data x)
{
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			report_runtime_error("cannot use %s as a reference",DATA_TYPE_NAME[x.type]);
			break;
		case DATA_RVALUE:
			// no instruction needed
			// no !
			x.arr_type=x.arr_type->next;
			break;
		case DATA_LVALUE:
			if (x.arr_type!=null) {
				x.arr_type=x.arr_type->next;
			} else {
				ALI::add_instruction(ALI::I_DEREFERENCE);
			}
			break;
		default:
			throw "unknown data type";
	}
	// return DATA_LVALUE;
	x.type=DATA_LVALUE;
	return x;
}



// count_data_*(x)
// modifies x to the corresponding type, and returns IC

inline int count_data_clear(Data &x)
{
	int ret=0;
	switch (x.type) {
		case DATA_UNDEFINED:
			throw "unknown data type";
			break;
		case DATA_VOID:
			break;
		case DATA_LVALUE:
		case DATA_RVALUE:
			// ALI::add_instruction(ALI::I_POP);
			++ret;
			break;
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			break;
		default:
			throw "unknow data type";
			break;
	}
	// x=DATA_VOID;
	x.type=DATA_VOID;
	return ret;
}

inline int count_data_get_rvalue(Data &x)
{
	int ret=0;
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			report_runtime_error("cannot cast %s to %s",DATA_TYPE_NAME[x.type],DATA_TYPE_NAME[DATA_RVALUE]);
			break;
		case DATA_LVALUE:
			if (x.arr_type!=null) {
				// x.arr_type=x.arr_type->next;
				// do nothing
				// ???
				
			} else {
				// ALI::add_instruction(ALI::I_DEREFERENCE);
				++ret;
			}//TODO here (?)
			break;
		case DATA_RVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// x=DATA_RVALUE;
	x.type=DATA_RVALUE;
	return ret;
}

inline int count_data_get_lvalue(Data &x)
{
	int ret=0;
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
		case DATA_RVALUE:
			report_runtime_error("cannot cast %s to %s",DATA_TYPE_NAME[x.type],DATA_TYPE_NAME[DATA_LVALUE]);
		case DATA_LVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// x=DATA_LVALUE;
	x.type=DATA_LVALUE;
	return ret;
}

inline int count_data_get_reference(Data &x)
{
	int ret=0;
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
		case DATA_RVALUE:
			report_runtime_error("cannot get %s's reference",DATA_TYPE_NAME[x.type]);
			break;
		case DATA_LVALUE:
			// no instruction needed
			break;
		default:
			throw "unknown data type";
	}
	// x=DATA_RVALUE;
	x.type=DATA_RVALUE;
	return ret;
}

inline int count_data_dereference(Data &x)
{
	int ret=0;
	switch (x.type) {
		case DATA_VOID:
		case DATA_CIN:
		case DATA_COUT:
		case DATA_ENDL:
			report_runtime_error("cannot use %s as a reference",DATA_TYPE_NAME[x.type]);
			break;
		case DATA_RVALUE:
			// no instruction needed
			// no !
			x.arr_type=x.arr_type->next;
			break;
		case DATA_LVALUE:
			if (x.arr_type!=null) {
				x.arr_type=x.arr_type->next;
			} else {
				// ALI::add_instruction(ALI::I_DEREFERENCE);
				++ret;
			}
			break;
		default:
			throw "unknown data type";
	}
	// return DATA_LVALUE;
	x.type=DATA_LVALUE;
	return ret;
}






// TODO: variables and functions

struct Function_Info {
	int pos_begin;
	int arg_cnt;
};

std::map<std::string,Function_Info> M_functions;


inline void declare_function(std::string name,int pos_begin,int arg_cnt)
{
	if (M_functions.count(name)>0) {
		report_error("redeclaration of function \"%s\"",name.c_str());
	}
	
	Function_Info FI;
	FI.pos_begin=pos_begin;
	FI.arg_cnt=arg_cnt;
	
	M_functions[name]=FI;
}


struct Variable_Info {
	int pos;
	Linked_List *arr_type;
};

std::map<std::string,Variable_Info> M_global_variables;

std::vector<std::map<std::string,Variable_Info> *> M_blocks;	// local variables

int global_variable_cnt;
int local_variable_cnt;

inline void declare_global_variable(std::string name,Linked_List *arr_type=null)
{
	if (M_global_variables.count(name)>0) {
		report_error("redeclaration of variable \"%s\"",name.c_str());
	}
	
	Variable_Info VI;
	// ++global_variable_cnt;
	global_variable_cnt+=arr_type->size;
	VI.pos=ALI::MEM_SIZE-global_variable_cnt;
	VI.arr_type=arr_type;
	
	M_global_variables[name]=VI;
}

inline void declare_global_variables(std::vector<AST_node*> *a)
{
	int size=a->size();
	int i;
	for (i=0;i<size;i++) {
		declare_global_variable(a->at(i)->x,a->at(i)->arr_type);
	}
}

inline void add_block()
{
	M_blocks.push_back(new std::map<std::string,Variable_Info>());
}

inline void del_block()
{
	std::map<std::string,Variable_Info> *a;
	a=M_blocks.back();
	a->clear();
	M_blocks.pop_back();
}

inline void declare_local_variable(std::string name,Linked_List *arr_type=null)
{
	std::map<std::string,Variable_Info> *a;
	a=M_blocks.back();
	
	if (a->count(name)>0) {
		report_error("redeclaration of variable \"%s\"",name.c_str());
	}
	
	Variable_Info VI;
	VI.pos=local_variable_cnt;
	// ++local_variable_cnt;
	local_variable_cnt+=arr_type->size;
	VI.arr_type=arr_type;
	
	(*a)[name]=VI;
}


inline Data get_variable_or_function(std::string x)	// returns: data type
{
	Data ret;
	ret.arr_type=null;
	if (M_functions.count(x)>0) {
		Function_Info FI;
		FI=M_functions[x];
		
		ALI::add_instruction(ALI::I_PUSH,FI.pos_begin);
		// return DATA_RVALUE;
		ret.type=DATA_RVALUE;
	} else {
		int block_cnt=M_blocks.size();
		int i;
		for (i=block_cnt-1;i>=0;i--) {
			std::map<std::string,Variable_Info> *a;
			a=M_blocks[i];
			if (a->count(x)>0) {
				break;
			}
		}
		
		Variable_Info VI;
		
		if (i>=0) {
			VI=M_blocks[i]->at(x);
			
			ALI::add_instruction(ALI::I_PUSH,VI.pos);
			// return DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=VI.arr_type;
		} else if (M_global_variables.count(x)>0) {
			VI=M_global_variables[x];
			
			ALI::add_instruction(ALI::I_PUSH,VI.pos);
			// return DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=VI.arr_type;
		} else {
			report_error("\"%s\" not declared",x.c_str());
		}
	}
	
	return ret;
}

inline int count_get_variable_or_function(std::string x,Data &ret)	// ret <- data type, returns IC
{
	int IC=0;
	ret.arr_type=null;
	if (M_functions.count(x)>0) {
		Function_Info FI;
		FI=M_functions[x];
		
		// ALI::add_instruction(ALI::I_PUSH,FI.pos_begin);
		IC+=1;
		// return DATA_RVALUE;
		// ret=DATA_RVALUE;
		ret.type=DATA_RVALUE;
	} else {
		int block_cnt=M_blocks.size();
		int i;
		for (i=block_cnt-1;i>=0;i--) {
			std::map<std::string,Variable_Info> *a;
			a=M_blocks[i];
			if (a->count(x)>0) {
				break;
			}
		}
		
		Variable_Info VI;
		
		if (i>=0) {
			VI=M_blocks[i]->at(x);
			
			// ALI::add_instruction(ALI::I_PUSH,VI.pos);
			IC+=1;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=VI.arr_type;
		} else if (M_global_variables.count(x)>0) {
			VI=M_global_variables[x];
			
			// ALI::add_instruction(ALI::I_PUSH,VI.pos);
			IC+=1;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=VI.arr_type;
		} else {
			report_error("\"%s\" not declared",x.c_str());
		}
	}
	return IC;
}

inline Data compile(AST_node *x);
inline void compile_function(AST_node *x);


int _pos_return;

inline void compile_function(AST_node *x)
{
	if (!x || x->type!=NODE_FUNCTION) {
		throw "not a function";
	}
	
	local_variable_cnt=0;
	
	add_block();
	
	int size=x->a->size();
	int arg_cnt=0;
	int i;
	for (i=0;i<size;i++) {
		if (x->a->at(i)->type!=NODE_FUNCTION_ARG) {
			break;
		} else {
			++arg_cnt;
			declare_local_variable(x->a->at(i)->x.c_str());
		}
	}
	
	int pos_begin=ALI::instruction_count+1;
	
	declare_function(x->x,pos_begin,arg_cnt);
	
	// set pos_ret
	int pos_return;	// = ?
	pos_return=pos_begin+2+3+2+3;
	for (i=arg_cnt;i<size;i++) {
		pos_return+=x->a->at(i)->IC_clear;
	}
	pos_return+=1;
	_pos_return=pos_return;
	
	// compile!
	
	// backup args
	ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	ALI::add_instruction(ALI::I_PUSH_TO_CS);
	
	// allocate variables
	ALI::add_instruction(ALI::I_PUSH,0);
	ALI::add_instruction(ALI::I_PUSH,x->VC);
	ALI::add_instruction(ALI::I_PUSH_ARR);
	
	// restore args
	ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	ALI::add_instruction(ALI::I_POP_FROM_CS);
	
	// write args to mem
	ALI::add_instruction(ALI::I_PUSH,0);
	ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	ALI::add_instruction(ALI::I_POP_ARR);
	
	
	// statements
	for (i=arg_cnt;i<size;i++) {
		Data t=compile(x->a->at(i));
		data_clear(t);
	}
	
	// no return here
	ALI::add_instruction(ALI::I_PUSH,0);
	
	// return here
	
	
	// backup ret
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_PUSH_TO_CS);
	
	// deallocate variables
	ALI::add_instruction(ALI::I_PUSH,0);
	ALI::add_instruction(ALI::I_PUSH,x->VC);
	ALI::add_instruction(ALI::I_POP_ARR);
	
	// restore ret
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_POP_FROM_CS);
	
	// ret
	ALI::add_instruction(ALI::I_RET);
	
	
	// ... done !
	
	
	del_block();
}




// TODO: count instructions

inline Data count(AST_node *x);	// returns: data type
inline void count_function(AST_node *x);

inline void count_function(AST_node *x)
{
	if (!x || x->type!=NODE_FUNCTION) {
		throw "not a function";
	}
	
	local_variable_cnt=0;
	
	int VC=0;
	int IC=0;
	
	add_block();	// ?
	
	int size=x->a->size();
	int arg_cnt=0;
	int i;
	for (i=0;i<size;i++) {
		if (x->a->at(i)->type!=NODE_FUNCTION_ARG) {
			break;
		} else {
			++arg_cnt;
			++VC;
			declare_local_variable(x->a->at(i)->x.c_str());
		}
	}
	
	declare_function(x->x,-1,arg_cnt);
	
	// set pos_ret (not needed)
	
	// compile!
	
	// backup args
	// ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	// ALI::add_instruction(ALI::I_PUSH_TO_CS);
	IC+=2;
	
	// allocate variables
	// ALI::add_instruction(ALI::I_PUSH,0);
	// ALI::add_instruction(ALI::I_PUSH,x->VC);
	// ALI::add_instruction(ALI::I_PUSH_ARR);
	IC+=3;
	
	// restore args
	// ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	// ALI::add_instruction(ALI::I_POP_FROM_CS);
	IC+=2;
	
	// write args to mem
	// ALI::add_instruction(ALI::I_PUSH,0);
	// ALI::add_instruction(ALI::I_PUSH,arg_cnt);
	// ALI::add_instruction(ALI::I_POP_ARR);
	IC+=3;
	
	
	// statements
	for (i=arg_cnt;i<size;i++) {
		// int t=count(x->a->at(i));
		// data_clear(t);
		count(x->a->at(i));
		IC+=x->a->at(i)->IC_clear;
		VC+=x->a->at(i)->VC;
	}
	
	// no return here
	// ALI::add_instruction(ALI::I_PUSH,0);
	IC+=1;
	
	// return here
	
	
	
	// backup ret
	// ALI::add_instruction(ALI::I_PUSH,1);
	// ALI::add_instruction(ALI::I_PUSH_TO_CS);
	IC+=2;
	
	// deallocate variables
	// ALI::add_instruction(ALI::I_PUSH,0);
	// ALI::add_instruction(ALI::I_PUSH,x->VC);
	// ALI::add_instruction(ALI::I_POP_ARR);
	IC+=3;
	
	// restore ret
	// ALI::add_instruction(ALI::I_PUSH,1);
	// ALI::add_instruction(ALI::I_POP_FROM_CS);
	IC+=2;
	
	
	// ret
	// ALI::add_instruction(ALI::I_RET);
	IC+=1;
	
	// ... done !
	
	
	del_block();
	
	x->VC=VC;
	x->IC=IC;
	x->IC_clear=IC;
}






// returns: data type
inline Data count(AST_node *x)
{
	int VC=0;
	int IC=0;
	Data ret;
	ret.arr_type=null;
	
	Data t;
	Data t1,t2;
	switch (x->type) {
		case NODE_UNDEFINED:
			throw "unknown node type";
			break;
		case NODE_NAME:
			if (x->x=="cin") {
				// ret=DATA_CIN;
				ret.type=DATA_CIN;
				break;
			} else if (x->x=="cout") {
				// ret=DATA_COUT;
				ret.type=DATA_COUT;
				break;
			} else if (x->x=="endl") {
				// ret=DATA_ENDL;
				ret.type=DATA_ENDL;
				break;
			} else {
				// variable or function
				// return get_variable(x->x);
				// return get_variable_or_function(x->x);
				IC+=count_get_variable_or_function(x->x,ret);
				break;
			}
			break;
		case NODE_INT_CONSTANT:
			// val=atoi(x->x.c_str());
			// ALI::add_instruction(ALI::I_PUSH,val);
			IC+=1;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			ret.arr_type=null;
			break;
		
		
		case NODE_EMPTY_STATEMENT:
			// do nothing
			// return DATA_VOID;
			// ret=DATA_VOID;
			ret.type=DATA_VOID;
			break;
		case NODE_CURLY_BRACKET:
			{
				add_block();
				
				int size=x->a->size();
				int i;
				for (i=0;i<size;i++) {
					AST_node *t=x->a->at(i);
					count(t);
					IC+=t->IC_clear;
					VC+=t->VC;
				}
				
				del_block();
				
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		case NODE_IF:
			{
				Data tmp=count(x->a->at(0));
				IC+=x->a->at(0)->IC;
				IC+=count_data_get_rvalue(tmp);
				assert_data_int_type(tmp);
				if (!x->r) {
					// int pos_end;	// = ALI::instruction_count + 2 + x->l->IC_clear + 1
					// int pos_end=ALI::instruction_count+2+x->l->IC_clear+1;
					
					// ALI::add_instruction(ALI::I_PUSH,pos_end);
					// ALI::add_instruction(ALI::I_JUMPZ);
					IC+=2;
					// int _l=count(x->l);
					// data_clear(_l);
					count(x->l);
					IC+=x->l->IC_clear;
					VC+=x->l->VC;
				} else {
					// int pos_false;	// = ALI::instruction_count + 2 + x->l->IC_clear + 2 + 1
					// int pos_end;	// = pos_false + x->r->IC_clear
					// int pos_false=ALI::instruction_count+2+x->l->IC_clear+2+1;
					// int pos_end=pos_false+x->r->IC_clear;
					
					// ALI::add_instruction(ALI::I_PUSH,pos_false);
					// ALI::add_instruction(ALI::I_JUMPZ);
					IC+=2;
					// int _l=compile(x->l);
					// data_clear(_l);
					count(x->l);
					IC+=x->l->IC_clear;
					VC+=x->l->VC;
					// ALI::add_instruction(ALI::I_PUSH,pos_end);
					// ALI::add_instruction(ALI::I_JUMP);
					IC+=2;
					// int _r=compile(x->r);
					// data_clear(_r);
					count(x->r);
					IC+=x->r->IC_clear;
					VC+=x->r->VC;
				}
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		
		case NODE_WHILE:
			{
				// int pos_begin;	// = ALI::instruction_count + 1
				// int pos_end;	// = pos_begin + x->l->IC_clear + 2 + x->r->IC_clear + 2
				// int pos_begin=ALI::instruction_count+1;
				// int pos_end=pos_begin+x->l->IC_clear+2+x->r->IC_clear+2;
				
				Data tmp=count(x->l);
				IC+=x->l->IC;
				VC+=x->l->VC;
				IC+=count_data_get_rvalue(tmp);
				assert_data_int_type(tmp);
				// ALI::add_instruction(ALI::I_PUSH,pos_end);
				// ALI::add_instruction(ALI::I_JUMPZ);
				IC+=2;
				// int _r=compile(x->r);
				// data_clear(_r);
				count(x->r);
				IC+=x->r->IC_clear;
				VC+=x->r->VC;
				// ALI::add_instruction(ALI::I_PUSH,pos_begin);
				// ALI::add_instruction(ALI::I_JUMP);
				IC+=2;
				
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		
		case NODE_FOR:
			{
				add_block();
				
				if (x->a->at(1)->type!=NODE_EMPTY_STATEMENT) {
					
					// int pos_begin;	// = ALI::instruction_count + 1
					// int pos_start;	// = pos_begin + ch[0]->IC_clear
					// int pos_end;	// = pos_start + ch[2]->IC + 2 + ch[3]->IC_clear + ch[1]->IC_clear + 2
					// int pos_begin=ALI::instruction_count+1;
					// int pos_start=pos_begin+x->a->at(0)->IC_clear;
					// int pos_end=pos_start+x->a->at(2)->IC+2+x->a->at(3)->IC_clear+x->a->at(1)->IC_clear+2;
					
					
					// int t0=compile(x->a->at(0));
					// data_clear(t0);
					count(x->a->at(0));
					IC+=x->a->at(0)->IC_clear;
					VC+=x->a->at(0)->VC;
					
					Data t1=count(x->a->at(1));
					IC+=x->a->at(1)->IC;
					VC+=x->a->at(1)->VC;	// must be 0
					IC+=count_data_get_rvalue(t1);
					assert_data_int_type(t1);
					// ALI::add_instruction(ALI::I_PUSH,pos_end);
					// ALI::add_instruction(ALI::I_JUMPZ);
					IC+=2;
					
					// int t3=compile(x->a->at(3));
					// data_clear(t3);
					count(x->a->at(3));
					IC+=x->a->at(3)->IC_clear;
					VC+=x->a->at(3)->VC;
					// int t1=compile(x->a->at(1));
					// data_clear(t1);
					count(x->a->at(2));
					IC+=x->a->at(2)->IC_clear;
					VC+=x->a->at(2)->VC;
					// ALI::add_instruction(ALI::I_PUSH,pos_start);
					// ALI::add_instruction(ALI::I_JUMP);
					IC+=2;
					
					del_block();
					
				} else {
					
					// int pos_begin;	// = ALI::instruction_count + 1
					// int pos_start;	// = pos_begin + ch[0]->IC_clear
					// int pos_end;	// = pos_start + ch[2]->IC + 2 + ch[3]->IC_clear + ch[1]->IC_clear + 2
					// int pos_begin=ALI::instruction_count+1;
					// int pos_start=pos_begin+x->a->at(0)->IC_clear;
					// int pos_end=pos_start+x->a->at(2)->IC+2+x->a->at(3)->IC_clear+x->a->at(1)->IC_clear+2;
					
					
					// int t0=compile(x->a->at(0));
					// data_clear(t0);
					count(x->a->at(0));
					IC+=x->a->at(0)->IC_clear;
					VC+=x->a->at(0)->VC;
					
					// int t3=compile(x->a->at(3));
					// data_clear(t3);
					count(x->a->at(3));
					IC+=x->a->at(3)->IC_clear;
					VC+=x->a->at(3)->VC;
					// int t1=compile(x->a->at(1));
					// data_clear(t1);
					count(x->a->at(2));
					IC+=x->a->at(2)->IC_clear;
					VC+=x->a->at(2)->VC;
					// ALI::add_instruction(ALI::I_PUSH,pos_start);
					// ALI::add_instruction(ALI::I_JUMP);
					IC+=2;
					
					del_block();
					
				}
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		
		
		case NODE_DEFINE_VAR:
			{
				std::vector<AST_node*> *a=x->a;
				int size=a->size();
				int i;
				for (i=0;i<size;i++) {
					AST_node *x=a->at(i);
					declare_local_variable(x->x,x->arr_type);
					// ++VC;
					VC+=x->arr_type->size;
					Data t;
					IC+=count_get_variable_or_function(x->x,t);
					IC+=count_data_get_lvalue(t);
					if (t.arr_type==null) {
						// I_MEMSET_1
						IC+=1;
					} else {
						// I_PUSH [size]
						// I_MEMSET
						IC+=2;
					}
					
					
					// // ALI::add_instruction(ALI::I_MEMSET_1);
					// IC+=1;
				}
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		
		case NODE_RETURN:
			{
				Data t=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->VC;
				IC+=count_data_get_rvalue(t);
				assert_data_int_type(t);
				// ALI::add_instruction(ALI::I_PUSH,_pos_return);
				// ALI::add_instruction(ALI::I_JUMP);
				IC+=2;
				// return DATA_VOID;
				// ret=DATA_VOID;
				ret.type=DATA_VOID;
			}
			break;
		
		
		case NODE_RIGHT_PLUS_PLUS:
			// x++
			t=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_lvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_SWAP);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_PUSH,1);
			// ALI::add_instruction(ALI::I_ADD);
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=8;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			ret.arr_type=t.arr_type;	// must be null
			break;
		case NODE_RIGHT_MINUS_MINUS:
			// x--
			t=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_lvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_SWAP);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_PUSH,1);
			// ALI::add_instruction(ALI::I_SUB);
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=8;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			ret.arr_type=t.arr_type;	// must be null
			break;
		case NODE_CALL_FUNCTION:
			{
				// x->l ( x->a )
				int size=x->a->size();
				int i;
				for (i=0;i<size;i++) {
					Data tmp=count(x->a->at(i));
					IC+=x->a->at(i)->IC;
					VC+=x->a->at(i)->VC;
					IC+=count_data_get_rvalue(tmp);
					assert_data_int_type(tmp);
				}
				Data t=count(x->l);
				IC+=x->l->IC;
				VC+=x->l->VC;
				IC+=count_data_get_rvalue(t);
				assert_data_int_type(t);
				// ALI::add_instruction(ALI::I_CALL);
				IC+=1;
				// return DATA_RVALUE;
				// ret=DATA_RVALUE;
				ret.type=DATA_RVALUE;
				ret.arr_type=t.arr_type;	// must be null
			}
			break;
		case NODE_SQUARE_BRACKET:
			// report_runtime_error("[] not supported QAQ");
			{
				// a [ b ]
				// * ( a + b )
				
				t1=count(x->l);
				IC+=x->l->IC;
				VC+=x->l->VC;
				IC+=count_data_get_rvalue(t1);
				
				if (t1.arr_type==null) {
					// int + ?
					t2=count(x->r);
					IC+=x->r->IC;
					VC+=x->r->VC;
					IC+=count_data_get_rvalue(t2);
					
					if (t2.arr_type==null) {
						// int + int
						// I_ADD
						IC+=1;
						ret.type=DATA_RVALUE;
					} else {
						// int + arr
						// I_SWAP
						// arr + int
						// I_PUSH [size]
						// I_MUL
						// I_ADD
						IC+=4;
						ret.type=DATA_RVALUE;
						ret.arr_type=t2.arr_type;
					}
				} else {
					// arr + int
					t2=count(x->r);
					IC+=x->r->IC;
					VC+=x->r->VC;
					IC+=count_data_get_rvalue(t2);
					
					assert_data_int_type(t2);
					
					// I_PUSH [size]
					// I_MUL
					// I_ADD
					IC+=3;
					
					ret.type=DATA_RVALUE;
					ret.arr_type=t1.arr_type;
				}
				
				
				IC+=count_data_dereference(ret);
				
			}
			break;
		case NODE_LEFT_PLUS_PLUS:
			// ++x
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_lvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_PUSH,1);
			// ALI::add_instruction(ALI::I_ADD);
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=6;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=t.arr_type;	// must be null
			break;
		case NODE_LEFT_MINUS_MINUS:
			// --x
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_lvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			// ALI::add_instruction(ALI::I_PUSH,1);
			// ALI::add_instruction(ALI::I_SUB);
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=6;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			ret.arr_type=t.arr_type;	// must be null
			break;
		case NODE_BITWISE_NOT:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_BITWISE_NOT);
			IC+=1;
			// return t;
			ret=t;
			break;
		case NODE_LOGICAL_NOT:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_LOGICAL_NOT);
			IC+=1;
			// return t;
			ret=t;
			break;
		case NODE_LEFT_PLUS:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t);
			assert_data_int_type(t);
			// no instruction needed
			// return t;
			ret=t;
			break;
		case NODE_LEFT_MINUS:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t);
			assert_data_int_type(t);
			// ALI::add_instruction(ALI::I_GET_OPPOSITE_NUMBER);
			IC+=1;
			// return t;
			ret=t;
			break;
		case NODE_REFERENCE:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_reference(t);
			// return t;
			ret=t;
			break;
		case NODE_DEREFERENCE:
			t=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_dereference(t);
			// return t;
			ret=t;
			break;
		case NODE_MULTIPLY:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			assert_data_int_type(t1);
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			// ALI::add_instruction(ALI::I_MULTIPLY);
			IC+=1;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			break;
		case NODE_DIVISION:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			assert_data_int_type(t1);
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			// ALI::add_instruction(ALI::I_DIVISION);
			IC+=1;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			break;
		case NODE_MODULO:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			assert_data_int_type(t1);
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			// ALI::add_instruction(ALI::I_MODULO);
			IC+=1;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			break;
		case NODE_PLUS:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			
			if (t1.arr_type==null) {
				// int + ?
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->VC;
				IC+=count_data_get_rvalue(t2);
				
				if (t2.arr_type==null) {
					// int + int
					// I_ADD
					IC+=1;
					ret.type=DATA_RVALUE;
				} else {
					// int + arr
					// I_SWAP
					// arr + int
					// I_PUSH [size]
					// I_MUL
					// I_ADD
					IC+=4;
					ret.type=DATA_RVALUE;
					ret.arr_type=t2.arr_type;
				}
			} else {
				// arr + int
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->VC;
				IC+=count_data_get_rvalue(t2);
				
				assert_data_int_type(t2);
				
				// I_PUSH [size]
				// I_MUL
				// I_ADD
				IC+=3;
				
				ret.type=DATA_RVALUE;
				ret.arr_type=t1.arr_type;
			}
			
			
			
			// t2=count(x->r);
			// IC+=x->r->IC;
			// VC+=x->r->VC;
			// IC+=count_data_get_rvalue(t2);
			// // ALI::add_instruction(ALI::I_ADD);
			// IC+=1;
			// // return DATA_RVALUE;
			// ret=DATA_RVALUE;
			break;
		case NODE_MINUS:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			
			assert_data_int_type(t2);
			
			if (t1.arr_type==null) {
				// int - int
				
				// I_SUB
				IC+=1;
				
				ret.type=DATA_RVALUE;
			} else {
				// arr - int
				
				// I_PUSH [size]
				// I_MUL
				// I_SUB
				IC+=3;
				
				ret.type=DATA_RVALUE;
				ret.arr_type=t1.arr_type;
			}
			
			
			// // ALI::add_instruction(ALI::I_SUB);
			// IC+=1;
			// // return DATA_RVALUE;
			// ret=DATA_RVALUE;
			break;
		case NODE_SHIFT_RIGHT:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			if (t1.type==DATA_CIN) {
				// cin >> lvalue
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->VC;
				IC+=count_data_get_lvalue(t2);
				assert_data_int_type(t2);
				// <del>ALI::add_instruction(ALI::I_DUP);</del>
				// ALI::add_instruction(ALI::I_CIN);
				// ALI::add_instruction(ALI::I_WRITEP);
				IC+=2;
				// return DATA_CIN;
				// ret=DATA_CIN;
				ret.type=DATA_CIN;
			} else {
				IC+=count_data_get_rvalue(t1);
				assert_data_int_type(t1);
				
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->VC;
				IC+=count_data_get_rvalue(t2);
				assert_data_int_type(t2);
				
				// ALI::add_instruction(ALI::I_SHIFT_RIGHT);
				IC+=1;
				// return DATA_RVALUE;
				// ret=DATA_RVALUE;
				ret.type=DATA_RVALUE;
			}
			break;
		case NODE_SHIFT_LEFT:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			if (t1.type==DATA_COUT) {
				// cout << endl
				// cout << rvalue
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->IC;
				if (t2.type==DATA_ENDL) {
					// ALI::add_instruction(ALI::I_PUSH,'\n');
					// ALI::add_instruction(ALI::I_PUTCHAR);
					IC+=2;
				} else {
					IC+=count_data_get_rvalue(t2);
					assert_data_int_type(t2);
					
					// ALI::add_instruction(ALI::I_COUT);
					IC+=1;
				}
				// return DATA_COUT;
				// ret=DATA_COUT;
				ret.type=DATA_COUT;
			} else {
				IC+=count_data_get_rvalue(t1);
				assert_data_int_type(t1);
				
				t2=count(x->r);
				IC+=x->r->IC;
				VC+=x->r->IC;
				IC+=count_data_get_rvalue(t2);
				assert_data_int_type(t2);
				
				// ALI::add_instruction(ALI::I_SHIFT_LEFT);
				IC+=1;
				// return DATA_RVALUE;
				// ret=DATA_RVALUE;
				ret.type=DATA_RVALUE;
			}
			break;
		case NODE_GREATER:
		case NODE_LESS:
		case NODE_GREATER_OR_EQUAL:
		case NODE_LESS_OR_EQUAL:
		case NODE_EQUAL:
		case NODE_NOT_EQUAL:
		case NODE_BITWISE_AND:
		case NODE_BITWISE_XOR:
		case NODE_BITWISE_OR:
		case NODE_LOGICAL_AND:
		case NODE_LOGICAL_OR:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			
			// ALI::add_instruction(ALI::I_LESS);
			IC+=1;
			// return DATA_RVALUE;
			// ret=DATA_RVALUE;
			ret.type=DATA_RVALUE;
			break;
		case NODE_ASSIGN:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_lvalue(t1);
			// must be lvalue of int
			assert_data_int_type(t1);
			
			// ALI::add_instruction(ALI::I_DUP);
			IC+=1;
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=1;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			break;
		case NODE_ASSIGN_MULTIPLY:
		case NODE_ASSIGN_DIVISION:
		case NODE_ASSIGN_MODULO:
		case NODE_ASSIGN_PLUS:
		case NODE_ASSIGN_MINUS:
		case NODE_ASSIGN_SHIFT_RIGHT:
		case NODE_ASSIGN_SHIFT_LEFT:
		case NODE_ASSIGN_BITWISE_AND:
		case NODE_ASSIGN_BITWISE_XOR:
		case NODE_ASSIGN_BITWISE_OR:
			t1=count(x->l);
			IC+=x->l->IC;
			VC+=x->l->VC;
			IC+=count_data_get_lvalue(t1);
			// must be lvalue of int
			assert_data_int_type(t1);
			
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DUP);
			// ALI::add_instruction(ALI::I_DEREFERENCE);
			IC+=3;
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			IC+=count_data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			// ALI::add_instruction(ALI::I_BITWISE_OR);
			// ALI::add_instruction(ALI::I_WRITEP);
			IC+=2;
			// return DATA_LVALUE;
			// ret=DATA_LVALUE;
			ret.type=DATA_LVALUE;
			break;
		case NODE_COMMA:
			// t1=compile(x->l);
			// data_clear(t1);
			count(x->l);
			IC+=x->l->IC_clear;
			VC+=x->l->VC;
			t2=count(x->r);
			IC+=x->r->IC;
			VC+=x->r->VC;
			// return t2;
			ret=t2;
			break;
		default:
			throw "???";
	}
	
	x->IC=IC;
	x->VC=VC;
	Data ret1=ret;
	IC+=count_data_clear(ret1);
	x->IC_clear=IC;
	return ret;
}









// returns: data type
inline Data compile(AST_node *x)
{
	int val;
	Data t;
	Data t1,t2;
	switch (x->type) {
		case NODE_UNDEFINED:
			throw "unknown node type";
			break;
		case NODE_NAME:
			if (x->x=="cin") {
				// return DATA_CIN;
				return Data(DATA_CIN);
			} else if (x->x=="cout") {
				// return DATA_COUT;
				return Data(DATA_COUT);
			} else if (x->x=="endl") {
				// return DATA_ENDL;
				return Data(DATA_ENDL);
			} else {
				// variable or function
				// return get_variable(x->x);
				return get_variable_or_function(x->x);
			}
			break;
		case NODE_INT_CONSTANT:
			val=atoi(x->x.c_str());
			ALI::add_instruction(ALI::I_PUSH,val);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		
		
		case NODE_EMPTY_STATEMENT:
			// do nothing
			// return DATA_VOID;
			return Data(DATA_VOID);
			break;
		case NODE_CURLY_BRACKET:
			{
				add_block();
				
				int size=x->a->size();
				int i;
				for (i=0;i<size;i++) {
					AST_node *t=x->a->at(i);
					Data tmp=compile(t);
					data_clear(tmp);
				}
				
				del_block();
				
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		case NODE_IF:
			{
				Data tmp=compile(x->a->at(0));
				tmp=data_get_rvalue(tmp);
				assert_data_int_type(tmp);
				
				if (!x->r) {
					// int pos_end;	// = ALI::instruction_count + 2 + x->l->IC_clear + 1
					int pos_end=ALI::instruction_count+2+x->l->IC_clear+1;
					
					ALI::add_instruction(ALI::I_PUSH,pos_end);
					ALI::add_instruction(ALI::I_JUMPZ);
					Data _l=compile(x->l);
					data_clear(_l);
				} else {
					// int pos_false;	// = ALI::instruction_count + 2 + x->l->IC_clear + 2 + 1
					// int pos_end;	// = pos_false + x->r->IC_clear
					int pos_false=ALI::instruction_count+2+x->l->IC_clear+2+1;
					int pos_end=pos_false+x->r->IC_clear;
					
					ALI::add_instruction(ALI::I_PUSH,pos_false);
					ALI::add_instruction(ALI::I_JUMPZ);
					Data _l=compile(x->l);
					data_clear(_l);
					ALI::add_instruction(ALI::I_PUSH,pos_end);
					ALI::add_instruction(ALI::I_JUMP);
					Data _r=compile(x->r);
					data_clear(_r);
				}
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		
		case NODE_WHILE:
			{
				// int pos_begin;	// = ALI::instruction_count + 1
				// int pos_end;	// = pos_begin + x->l->IC_clear + 2 + x->r->IC_clear + 2
				int pos_begin=ALI::instruction_count+1;
				int pos_end=pos_begin+x->l->IC+2+x->r->IC_clear+2;
				
				Data tmp=compile(x->l);
				data_get_rvalue(tmp);
				pos_end+=count_data_get_rvalue(tmp);
				assert_data_int_type(tmp);
				
				ALI::add_instruction(ALI::I_PUSH,pos_end);
				ALI::add_instruction(ALI::I_JUMPZ);
				Data _r=compile(x->r);
				data_clear(_r);
				ALI::add_instruction(ALI::I_PUSH,pos_begin);
				ALI::add_instruction(ALI::I_JUMP);
				
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		
		case NODE_FOR:
			{
				add_block();
				
				if (x->a->at(1)->type!=NODE_EMPTY_STATEMENT) {
					
					// int pos_begin;	// = ALI::instruction_count + 1
					// int pos_start;	// = pos_begin + ch[0]->IC_clear
					// int pos_end;	// = pos_start + ch[2]->IC + 2 + ch[3]->IC_clear + ch[1]->IC_clear + 2
					int pos_begin=ALI::instruction_count+1;
					int pos_start=pos_begin+x->a->at(0)->IC_clear;
					int pos_end=pos_start+x->a->at(1)->IC+2+x->a->at(3)->IC_clear+x->a->at(2)->IC_clear+2;
					
					
					Data t0=compile(x->a->at(0));
					data_clear(t0);
					
					Data t1=compile(x->a->at(1));
					data_get_rvalue(t1);
					pos_end+=count_data_get_rvalue(t1);
					assert_data_int_type(t1);
					
					ALI::add_instruction(ALI::I_PUSH,pos_end);
					ALI::add_instruction(ALI::I_JUMPZ);
					
					Data t3=compile(x->a->at(3));
					data_clear(t3);
					Data t2=compile(x->a->at(2));
					data_clear(t2);
					ALI::add_instruction(ALI::I_PUSH,pos_start);
					ALI::add_instruction(ALI::I_JUMP);
					
					del_block();
					
				} else {
					
					// int pos_begin;	// = ALI::instruction_count + 1
					// int pos_start;	// = pos_begin + ch[0]->IC_clear
					// int pos_end;	// = pos_start + ch[2]->IC + 2 + ch[3]->IC_clear + ch[1]->IC_clear + 2
					int pos_begin=ALI::instruction_count+1;
					int pos_start=pos_begin+x->a->at(0)->IC_clear;
					// int pos_end=pos_start+x->a->at(1)->IC+x->a->at(3)->IC_clear+x->a->at(2)->IC_clear+2;
					
					
					Data t0=compile(x->a->at(0));
					data_clear(t0);
					
					Data t3=compile(x->a->at(3));
					data_clear(t3);
					Data t2=compile(x->a->at(2));
					data_clear(t2);
					ALI::add_instruction(ALI::I_PUSH,pos_start);
					ALI::add_instruction(ALI::I_JUMP);
					
					del_block();
					
				}
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		
		
		case NODE_DEFINE_VAR:
			{
				std::vector<AST_node*> *a=x->a;
				int size=a->size();
				int i;
				for (i=0;i<size;i++) {
					AST_node *x=a->at(i);
					declare_local_variable(x->x,x->arr_type);
					Data t=get_variable_or_function(x->x);
					t=data_get_lvalue(t);
					if (t.arr_type==null) {
						ALI::add_instruction(ALI::I_MEMSET_1);
					} else {
						ALI::add_instruction(ALI::I_PUSH,t.arr_type->size);
						ALI::add_instruction(ALI::I_MEMSET);
					}
					// ALI::add_instruction(ALI::I_MEMSET_1);
				}
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		
		case NODE_RETURN:
			{
				Data t=compile(x->r);
				t=data_get_rvalue(t);
				assert_data_int_type(t);
				ALI::add_instruction(ALI::I_PUSH,_pos_return);
				ALI::add_instruction(ALI::I_JUMP);
				// return DATA_VOID;
				return Data(DATA_VOID);
			}
			break;
		
		
		case NODE_RIGHT_PLUS_PLUS:
			// x++
			t=compile(x->l);
			t=data_get_lvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_SWAP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_PUSH,1);
			ALI::add_instruction(ALI::I_ADD);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_RIGHT_MINUS_MINUS:
			// x--
			t=compile(x->l);
			t=data_get_lvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_SWAP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_PUSH,1);
			ALI::add_instruction(ALI::I_SUB);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_CALL_FUNCTION:
			{
				// x->l ( x->a )
				int size=x->a->size();
				int i;
				for (i=0;i<size;i++) {
					Data tmp=compile(x->a->at(i));
					data_get_rvalue(tmp);
					assert_data_int_type(tmp);
				}
				Data t=compile(x->l);
				data_get_rvalue(t);
				assert_data_int_type(t);
				ALI::add_instruction(ALI::I_CALL);
				// return DATA_RVALUE;
				return Data(DATA_RVALUE);
			}
			break;
		case NODE_SQUARE_BRACKET:
			// report_runtime_error("[] not supported QAQ");
			{
				// a [ b ]
				// * ( a + b )
				
				Data ret;
				
				t1=compile(x->l);
				t1=data_get_rvalue(t1);
				
				if (t1.arr_type==null) {
					// int + ?
					t2=compile(x->r);
					t2=data_get_rvalue(t2);
					
					if (t2.arr_type==null) {
						// int + int
						ALI::add_instruction(ALI::I_ADD);
						return Data(DATA_RVALUE);
					} else {
						// int + arr
						ALI::add_instruction(ALI::I_SWAP);
						// arr + int
						ALI::add_instruction(ALI::I_PUSH,t2.arr_type->next->size);
						ALI::add_instruction(ALI::I_MULTIPLY);
						ALI::add_instruction(ALI::I_ADD);
						
						ret=Data(DATA_RVALUE,t2.arr_type);
					}
				} else {
					// arr + int
					t2=compile(x->r);
					t2=data_get_rvalue(t2);
					assert_data_int_type(t2);
					
					ALI::add_instruction(ALI::I_PUSH,t1.arr_type->next->size);
					ALI::add_instruction(ALI::I_MULTIPLY);
					ALI::add_instruction(ALI::I_ADD);
					
					ret=Data(DATA_RVALUE,t1.arr_type);
				}
				
				ret=data_dereference(ret);
				return ret;
			}
			break;
		case NODE_LEFT_PLUS_PLUS:
			// ++x
			t=compile(x->r);
			t=data_get_lvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_PUSH,1);
			ALI::add_instruction(ALI::I_ADD);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_LEFT_MINUS_MINUS:
			// --x
			t=compile(x->r);
			t=data_get_lvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			ALI::add_instruction(ALI::I_PUSH,1);
			ALI::add_instruction(ALI::I_SUB);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_BITWISE_NOT:
			t=compile(x->r);
			t=data_get_rvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_BITWISE_NOT);
			return t;
			break;
		case NODE_LOGICAL_NOT:
			t=compile(x->r);
			t=data_get_rvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_LOGICAL_NOT);
			return t;
			break;
		case NODE_LEFT_PLUS:
			t=compile(x->r);
			t=data_get_rvalue(t);
			assert_data_int_type(t);
			
			// no instruction needed
			return t;
			break;
		case NODE_LEFT_MINUS:
			t=compile(x->r);
			t=data_get_rvalue(t);
			assert_data_int_type(t);
			
			ALI::add_instruction(ALI::I_GET_OPPOSITE_NUMBER);
			return t;
			break;
		case NODE_REFERENCE:
			t=compile(x->r);
			t=data_get_reference(t);
			return t;
			break;
		case NODE_DEREFERENCE:
			t=compile(x->r);
			t=data_dereference(t);
			return t;
			break;
		case NODE_MULTIPLY:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_MULTIPLY);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_DIVISION:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_DIVISION);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_MODULO:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_MODULO);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_PLUS:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			
			if (t1.arr_type==null) {
				// int + ?
				t2=compile(x->r);
				t2=data_get_rvalue(t2);
				
				if (t2.arr_type==null) {
					// int + int
					ALI::add_instruction(ALI::I_ADD);
					return Data(DATA_RVALUE);
				} else {
					// int + arr
					ALI::add_instruction(ALI::I_SWAP);
					// arr + int
					ALI::add_instruction(ALI::I_PUSH,t2.arr_type->next->size);
					ALI::add_instruction(ALI::I_MULTIPLY);
					ALI::add_instruction(ALI::I_ADD);
					
					return Data(DATA_RVALUE,t2.arr_type);
				}
			} else {
				// arr + int
				t2=compile(x->r);
				t2=data_get_rvalue(t2);
				assert_data_int_type(t2);
				
				ALI::add_instruction(ALI::I_PUSH,t1.arr_type->next->size);
				ALI::add_instruction(ALI::I_MULTIPLY);
				ALI::add_instruction(ALI::I_ADD);
				
				return Data(DATA_RVALUE,t1.arr_type);
			}
			// t2=compile(x->r);
			// t2=data_get_rvalue(t2);
			// ALI::add_instruction(ALI::I_ADD);
			// return DATA_RVALUE;
			break;
		case NODE_MINUS:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			
			assert_data_int_type(t2);
			
			if (t1.arr_type==null) {
				// int - int
				
				ALI::add_instruction(ALI::I_SUB);
				
				return Data(DATA_RVALUE);
			} else {
				// arr - int
				
				ALI::add_instruction(ALI::I_PUSH,t1.arr_type->next->size);
				ALI::add_instruction(ALI::I_MULTIPLY);
				ALI::add_instruction(ALI::I_SUB);
				
				return Data(DATA_RVALUE,t1.arr_type);
			}
			
			// ALI::add_instruction(ALI::I_SUB);
			// return DATA_RVALUE;
			break;
		case NODE_SHIFT_RIGHT:
			t1=compile(x->l);
			if (t1.type==DATA_CIN) {
				// cin >> lvalue
				t2=compile(x->r);
				t2=data_get_lvalue(t2);
				assert_data_int_type(t2);
				
				// <del>ALI::add_instruction(ALI::I_DUP);</del>
				ALI::add_instruction(ALI::I_CIN);
				ALI::add_instruction(ALI::I_WRITEP);
				return DATA_CIN;
			} else {
				t1=data_get_rvalue(t1);
				assert_data_int_type(t1);
				
				t2=compile(x->r);
				t2=data_get_rvalue(t2);
				assert_data_int_type(t2);
				
				ALI::add_instruction(ALI::I_SHIFT_RIGHT);
				// return DATA_RVALUE;
				return Data(DATA_RVALUE);
			}
			break;
		case NODE_SHIFT_LEFT:
			t1=compile(x->l);
			if (t1.type==DATA_COUT) {
				// cout << endl
				// cout << rvalue
				t2=compile(x->r);
				if (t2.type==DATA_ENDL) {
					ALI::add_instruction(ALI::I_PUSH,'\n');
					ALI::add_instruction(ALI::I_PUTCHAR);
				} else {
					t2=data_get_rvalue(t2);
					assert_data_int_type(t2);
					
					ALI::add_instruction(ALI::I_COUT);
				}
				// return DATA_COUT;
				return Data(DATA_COUT);
			} else {
				t1=data_get_rvalue(t1);
				assert_data_int_type(t1);
				
				t2=compile(x->r);
				t2=data_get_rvalue(t2);
				assert_data_int_type(t2);
				
				ALI::add_instruction(ALI::I_SHIFT_LEFT);
				// return DATA_RVALUE;
				return Data(DATA_RVALUE);
			}
			break;
		case NODE_GREATER:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_GREATER);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_LESS:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_LESS);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_GREATER_OR_EQUAL:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_GREATER_OR_EQUAL);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_LESS_OR_EQUAL:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_LESS_OR_EQUAL);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_EQUAL:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_EQUAL);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_NOT_EQUAL:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_NOT_EQUAL);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_BITWISE_AND:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_AND);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_BITWISE_XOR:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_XOR);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_BITWISE_OR:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_OR);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_LOGICAL_AND:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_LOGICAL_AND);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_LOGICAL_OR:
			t1=compile(x->l);
			t1=data_get_rvalue(t1);
			assert_data_int_type(t1);
			
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_LOGICAL_OR);
			// return DATA_RVALUE;
			return Data(DATA_RVALUE);
			break;
		case NODE_ASSIGN:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			// must be lvalue of int
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_MULTIPLY:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			// must be lvalue of int
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_MULTIPLY);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_DIVISION:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_DIVISION);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_MODULO:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_MODULO);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_PLUS:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_ADD);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_MINUS:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_SUB);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_SHIFT_RIGHT:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_SHIFT_RIGHT);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_SHIFT_LEFT:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_SHIFT_LEFT);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_BITWISE_AND:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_AND);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_BITWISE_XOR:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_XOR);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_ASSIGN_BITWISE_OR:
			t1=compile(x->l);
			t1=data_get_lvalue(t1);
			assert_data_int_type(t1);
			
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DUP);
			ALI::add_instruction(ALI::I_DEREFERENCE);
			t2=compile(x->r);
			t2=data_get_rvalue(t2);
			assert_data_int_type(t2);
			
			ALI::add_instruction(ALI::I_BITWISE_OR);
			ALI::add_instruction(ALI::I_WRITEP);
			// return DATA_LVALUE;
			return Data(DATA_LVALUE);
			break;
		case NODE_COMMA:
			t1=compile(x->l);
			data_clear(t1);
			t2=compile(x->r);
			return t2;
			break;
		default:
			throw "???";
	}
}





inline AST_node *E0();
inline AST_node *E2();
inline AST_node *E3();
inline AST_node *E5();
inline AST_node *E6();
inline AST_node *E7();
inline AST_node *E8();
inline AST_node *E9();
inline AST_node *E10();
inline AST_node *E11();
inline AST_node *E12();
inline AST_node *E13();
inline AST_node *E14();
inline AST_node *E15();
inline AST_node *E16();

inline AST_node *Expression();
inline AST_node *Expression_without_comma();

inline AST_node *Statement_expr();
inline AST_node *Statement_defvar();
inline AST_node *Statement();
inline std::vector<AST_node*> *Statements();



inline AST_node *E0()
{
	int type=Tokenizer::now_type;
	std::string now=Tokenizer::now;
	if (type==TOKEN_EOF) {
		report_compile_error("expected integer constant or name or '(', but EOF found");
	} else if (type==TOKEN_INT_CONSTANT) {
		AST_node *ret=new AST_node((AST_node){NULL,NULL,now,NODE_INT_CONSTANT});
		Tokenizer::get_token();
		return ret;
	} else if (type==TOKEN_NAME) {
		AST_node *ret=new AST_node((AST_node){NULL,NULL,now,NODE_NAME});
		Tokenizer::get_token();
		return ret;
	} else if (now[0]=='(') {
		Tokenizer::get_token();
		AST_node *ret=Expression();
		assert_token(Tokenizer::now,")");
		Tokenizer::get_token();
		return ret;
	} else {
		report_compile_error("expected integer constant or name or '(', but \"%s\" found",now.c_str());
	}
}

inline std::vector<AST_node*> * E2_ARG_LIST()
{
	std::vector<AST_node*> *ret=new std::vector<AST_node*>;
	if (Tokenizer::now==")") return ret;	// no args
	ret->push_back(Expression_without_comma());
	while (1) {
		std::string now=Tokenizer::now;
		if (now==",") {
			Tokenizer::get_token();
			ret->push_back(Expression_without_comma());
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E2()
{
	AST_node *ret=E0();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="++") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_RIGHT_PLUS_PLUS});
			ret=tmp;
			Tokenizer::get_token();
		} else if (now=="--") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_RIGHT_MINUS_MINUS});
			ret=tmp;
			Tokenizer::get_token();
		} else if (now=="()") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_CALL_FUNCTION});
			tmp->a=new std::vector<AST_node*>;
			ret=tmp;
			Tokenizer::get_token();
		} else if (now=="(") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_CALL_FUNCTION});
			Tokenizer::get_token();
			tmp->a=E2_ARG_LIST();
			ret=tmp;
			assert_token(Tokenizer::now,")");
			Tokenizer::get_token();
		} else if (now=="[") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_SQUARE_BRACKET});
			Tokenizer::get_token();
			tmp->r=Expression();
			ret=tmp;
			assert_token(Tokenizer::now,"]");
			Tokenizer::get_token();
		} else {
			break;
		}
	}
	return ret;
}




inline AST_node *E3()
{
	std::string now=Tokenizer::now;
	AST_node *ret=NULL;
	if (now=="++") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_LEFT_PLUS_PLUS});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="--") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_LEFT_MINUS_MINUS});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="~") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_BITWISE_NOT});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="!") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_LOGICAL_NOT});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="+") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_LEFT_PLUS});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="-") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_LEFT_MINUS});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="&") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_REFERENCE});
		Tokenizer::get_token();
		ret->r=E3();
	} else if (now=="*") {
		ret=new AST_node((AST_node){NULL,NULL,now,NODE_DEREFERENCE});
		Tokenizer::get_token();
		ret->r=E3();
	} else {
		ret=E2();
	}
	return ret;
}

inline AST_node *E5()
{
	AST_node *ret=E3();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="*") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_MULTIPLY});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E3();
		} else if (now=="/") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_DIVISION});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E3();
		} else if (now=="%") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_MODULO});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E3();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E6()
{
	AST_node *ret=E5();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="+") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_PLUS});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E5();
		} else if (now=="-") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_MINUS});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E5();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E7()
{
	AST_node *ret=E6();
	while (1) {
		std::string now=Tokenizer::now;
		if (now==">>") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_SHIFT_RIGHT});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E6();
		} else if (now=="<<") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_SHIFT_LEFT});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E6();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E8()
{
	AST_node *ret=E7();
	while (1) {
		std::string now=Tokenizer::now;
		if (now==">") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_GREATER});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E7();
		} else if (now=="<") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_LESS});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E7();
		} else if (now==">=") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_GREATER_OR_EQUAL});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E7();
		} else if (now=="<=") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_LESS_OR_EQUAL});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E7();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E9()
{
	AST_node *ret=E8();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="==") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_EQUAL});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E8();
		} else if (now=="!=") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_NOT_EQUAL});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E8();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E10()
{
	AST_node *ret=E9();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="&") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_BITWISE_AND});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E9();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E11()
{
	AST_node *ret=E10();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="^") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_BITWISE_XOR});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E10();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E12()
{
	AST_node *ret=E11();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="|") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_BITWISE_OR});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E11();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E13()
{
	AST_node *ret=E12();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="&&") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_LOGICAL_AND});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E12();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E14()
{
	AST_node *ret=E13();
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="||") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_LOGICAL_OR});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E13();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *E15()
{
	std::vector<AST_node*> A;
	std::vector<std::string> Ops;
	A.push_back(E14());
	while (1) {
		std::string now=Tokenizer::now;
		if (now=="=" || now=="*=" || now=="/=" || now=="%=" || now=="+=" || now=="-="
			|| now==">>=" || now=="<<=" || now=="&=" || now=="^=" || now=="|=") {
			Tokenizer::get_token();
			Ops.push_back(now);
			A.push_back(E14());
		} else {
			break;
		}
	}
	int size=A.size();
	AST_node *ret=A[size-1];
	int i;
	for (i=size-2;i>=0;i--) {
		std::string op=Ops[i];
		AST_node *tmp=new AST_node((AST_node){A[i],ret,op,NODE_UNDEFINED});
		ret=tmp;
		if (op=="=") {
			ret->type=NODE_ASSIGN;
		} else if (op=="*=") {
			ret->type=NODE_ASSIGN_MULTIPLY;
		} else if (op=="/=") {
			ret->type=NODE_ASSIGN_DIVISION;
		} else if (op=="%=") {
			ret->type=NODE_ASSIGN_MODULO;
		} else if (op=="+=") {
			ret->type=NODE_ASSIGN_PLUS;
		} else if (op=="-=") {
			ret->type=NODE_ASSIGN_MINUS;
		} else if (op==">>=") {
			ret->type=NODE_ASSIGN_SHIFT_RIGHT;
		} else if (op=="<<=") {
			ret->type=NODE_ASSIGN_SHIFT_LEFT;
		} else if (op=="&=") {
			ret->type=NODE_ASSIGN_BITWISE_AND;
		} else if (op=="^=") {
			ret->type=NODE_ASSIGN_BITWISE_XOR;
		} else if (op=="|=") {
			ret->type=NODE_ASSIGN_BITWISE_OR;
		}
	}
	return ret;
}

inline AST_node *E16()
{
	AST_node *ret=E15();
	while (1) {
		std::string now=Tokenizer::now;
		if (now==",") {
			AST_node *tmp=new AST_node((AST_node){ret,NULL,now,NODE_COMMA});
			ret=tmp;
			Tokenizer::get_token();
			ret->r=E15();
		} else {
			break;
		}
	}
	return ret;
}

inline AST_node *Expression()
{
	return E16();
}

inline AST_node *Expression_without_comma()
{
	return E15();
}

inline AST_node *Statement_expr()
{
	AST_node *ret=Expression();
	assert_token(Tokenizer::now,";");
	Tokenizer::get_token();
	return ret;
}

inline AST_node *get_define_var(std::string s)
{
	AST_node *ret=new AST_node();
	ret->l=ret->r=NULL;
	ret->x=s;
	std::vector<int> A;
	while (1) {
		if (Tokenizer::now=="[") {
			Tokenizer::get_token();
			assert_token_type(Tokenizer::now_type,TOKEN_INT_CONSTANT);
			int size=atoi(Tokenizer::now.c_str());
			A.push_back(size);
			Tokenizer::get_token();
			assert_token(Tokenizer::now,"]");
			Tokenizer::get_token();
		} else {
			break;
		}
	}
	Linked_List *arr_type=null;
	while (A.size()>0) {
		int tmp=A.back();
		A.pop_back();
		arr_type=new Linked_List(arr_type,tmp);
	}
	
	ret->arr_type=arr_type;
	
	return ret;
}

inline AST_node *get_define_var()
{
	std::string now=Tokenizer::now;
	Tokenizer::get_token();
	return get_define_var(now);
}

inline AST_node *Statement_define_var()
{
	debug("--- statement define var --- \n");
	std::string now=Tokenizer::now;
	assert_token(now,"int");
	AST_node *ret=new AST_node();
	Tokenizer::get_token();
	ret->type=NODE_DEFINE_VAR;
	std::vector<AST_node*> *a=new std::vector<AST_node*>;
	while (1) {
		a->push_back(get_define_var());
		now=Tokenizer::now;
		Tokenizer::get_token();
		if (now==",") {
			continue;
		} else {
			break;
		}
	}
	assert_token(now,";");
	ret->a=a;
	return ret;
}




inline AST_node *Statement_in_for_0()
{
	std::string now=Tokenizer::now;
	if (now==";") {
		Tokenizer::get_token();
		AST_node *ret=new AST_node();
		ret->type=NODE_EMPTY_STATEMENT;
		return ret;
	} else if (now=="int") {
		// define var
		return Statement_define_var();
	} else {
		AST_node *ret=Statement_expr();
		return ret;
	}
}


inline AST_node *Statement_in_for_1()
{
	std::string now=Tokenizer::now;
	if (now==";") {
		Tokenizer::get_token();
		AST_node *ret=new AST_node();
		ret->type=NODE_EMPTY_STATEMENT;
		return ret;
	} else {
		return Statement_expr();
	}
}

inline AST_node *Statement_in_for_2()
{
	std::string now=Tokenizer::now;
	if (now==")") {
		AST_node *ret=new AST_node();
		ret->type=NODE_EMPTY_STATEMENT;
		return ret;
	} else {
		return Expression();
	}
}




inline AST_node *Statement()
{
	debug("statemnt [now = %s]\n",Tokenizer::now.c_str());
	std::string now=Tokenizer::now;
	if (now==";") {
		Tokenizer::get_token();
		AST_node *ret=new AST_node();
		ret->type=NODE_EMPTY_STATEMENT;
		return ret;
	} else if (now=="{") {
		Tokenizer::get_token();
		AST_node *ret=new AST_node((AST_node){NULL,NULL,now,NODE_CURLY_BRACKET});
		ret->a=Statements();
		assert_token(Tokenizer::now,"}");
		Tokenizer::get_token();
		return ret;
	} else if (now=="int") {
		// define var
		return Statement_define_var();
	} else if (now=="if") {
		Tokenizer::get_token();
		assert_token(Tokenizer::now,"(");
		Tokenizer::get_token();
		AST_node *ret=new AST_node((AST_node){NULL,NULL,now,NODE_IF});
		ret->a=new std::vector<AST_node*>(1);
		ret->a->at(0)=Expression();
		// debug("expr ok\n");
		assert_token(Tokenizer::now,")");
		Tokenizer::get_token();
		ret->l=Statement();
		now=Tokenizer::now;
		if (now=="else") {
			Tokenizer::get_token();
			ret->r=Statement();
		}
		return ret;
	} else if (now=="while") {
		Tokenizer::get_token();
		assert_token(Tokenizer::now,"(");
		Tokenizer::get_token();
		AST_node *ret=new AST_node((AST_node){NULL,NULL,now,NODE_WHILE});
		ret->l=Expression();
		assert_token(Tokenizer::now,")");
		Tokenizer::get_token();
		ret->r=Statement();
		return ret;
	} else if (now=="for") {
		Tokenizer::get_token();
		assert_token(Tokenizer::now,"(");
		Tokenizer::get_token();
		AST_node *ret=new AST_node();
		ret->type=NODE_FOR;
		ret->a=new std::vector<AST_node*>;
		ret->a->push_back(Statement_in_for_0());
		ret->a->push_back(Statement_in_for_1());
		ret->a->push_back(Statement_in_for_2());
		assert_token(Tokenizer::now,")");
		Tokenizer::get_token();
		ret->a->push_back(Statement());
		return ret;
	} else if (now=="return") {
		// return [expr];
		Tokenizer::get_token();
		AST_node *ret=new AST_node();
		ret->type=NODE_RETURN;
		ret->r=Expression();
		assert_token(Tokenizer::now,";");
		Tokenizer::get_token();
		return ret;
	} else {
		AST_node *ret=Statement_expr();
		return ret;
	}
}






inline std::vector<AST_node*> *Statements()
{
	std::vector<AST_node*> *ret=new std::vector<AST_node*>;
	while (1) {
		std::string now=Tokenizer::now;
		if (now==";") {
			Tokenizer::get_token();
			continue;
		} else if (now=="}") {
			break;
		} else {
			ret->push_back(Statement());
		}
	}
	return ret;
}

inline AST_node *func(std::string name)
{
	AST_node *ret=new AST_node();
	ret->type=NODE_FUNCTION;
	ret->x=name;
	std::string now=Tokenizer::now;
	ret->a=new std::vector<AST_node*>;
	if (now=="()") {
		Tokenizer::get_token();
	} else {
		assert_token(now,"(");
		Tokenizer::get_token();
		if (Tokenizer::now=="int") {
			Tokenizer::get_token();
			assert_token_type(Tokenizer::now_type,TOKEN_NAME);
			AST_node *t=new AST_node();
			t->type=NODE_FUNCTION_ARG;
			t->x=Tokenizer::now;
			ret->a->push_back(t);
			Tokenizer::get_token();
			while (Tokenizer::now==",") {
				Tokenizer::get_token();
				assert_token(Tokenizer::now,"int");
				Tokenizer::get_token();
				assert_token_type(Tokenizer::now_type,TOKEN_NAME);
				AST_node *t=new AST_node();
				t->type=NODE_FUNCTION_ARG;
				t->x=Tokenizer::now;
				ret->a->push_back(t);
				Tokenizer::get_token();
			}
		}
		assert_token(Tokenizer::now,")");
		Tokenizer::get_token();
	}
	assert_token(Tokenizer::now,"{");
	Tokenizer::get_token();
	while (1) {
		std::string now=Tokenizer::now;
		if (now==";") {
			Tokenizer::get_token();
			continue;
		} else if (now=="}") {
			break;
		} else {
			ret->a->push_back(Statement());
		}
	}
	assert_token(Tokenizer::now,"}");
	Tokenizer::get_token();
	return ret;
}

inline AST_node *def_var(std::string name)
{
	AST_node *ret=new AST_node();
	ret->type=NODE_DEFINE_VAR;
	std::vector<AST_node*> *a=new std::vector<AST_node*>;
	std::string now;
	while (1) {
		if (a->empty()) {
			a->push_back(get_define_var(name));
		} else {
			a->push_back(get_define_var());
		}
		now=Tokenizer::now;
		Tokenizer::get_token();
		if (now==",") {
			continue;
		} else {
			break;
		}
	}
	assert_token(now,";");
	ret->a=a;
	return ret;
}

inline AST_node *func_or_var()
{
	assert_token(Tokenizer::now,"int");
	Tokenizer::get_token();
	assert_token_type(Tokenizer::now_type,TOKEN_NAME);
	std::string s=Tokenizer::now;
	Tokenizer::get_token();
	if (Tokenizer::now=="(" || Tokenizer::now=="()") {
		return func(s);
	} else {
		return def_var(s);
	}
}

inline std::vector<AST_node*> *func_and_var()
{
	std::vector<AST_node*> *ret=new std::vector<AST_node*>;
	while (1) {
		int now_type=Tokenizer::now_type;
		if (now_type==TOKEN_EOF) break;
		ret->push_back(func_or_var());
	}
	return ret;
}

inline std::vector<AST_node*> *program_uoj_98()
{
	assert_token(Tokenizer::now,"#");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"include");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"<");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"iostream");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,">");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"#");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"include");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"<");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"cstdio");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,">");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"using");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"namespace");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,"std");
	Tokenizer::get_token();
	assert_token(Tokenizer::now,";");
	Tokenizer::get_token();
	
	return func_and_var();
}





inline void test_1e7_0()
{
	ALI::init();
	int n=10000000;
	int i;
	ALI::add_instruction(ALI::I_PUSH,1);
	for (i=1;i<=n;i++) {
		ALI::add_instruction(ALI::I_PUSH,10);
		ALI::add_instruction(ALI::I_MULTIPLY);
		ALI::add_instruction(ALI::I_PUSH,998244353);
		ALI::add_instruction(ALI::I_MODULO);
	}
	ALI::add_instruction(ALI::I_COUT);
	ALI::add_instruction(ALI::I_HALT);
	ALI::run();
}

inline void test_1e7_1()
{
	ALI::init();
	int n=10000000;
	
	// while (*1) --*1,*2=*2*10%mo;
	
	// *1 = 1e7
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_PUSH,n);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// *2 = 1
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// 7	 while (*1) 
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,27);
	ALI::add_instruction(ALI::I_JUMPZ);
	
	// --*1
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_SUB);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// *2=*2*10%mo
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,10);
	ALI::add_instruction(ALI::I_MULTIPLY);
	ALI::add_instruction(ALI::I_PUSH,998244353);
	ALI::add_instruction(ALI::I_MODULO);
	ALI::add_instruction(ALI::I_WRITEP);
	
	
	ALI::add_instruction(ALI::I_PUSH,7);
	ALI::add_instruction(ALI::I_JUMP);
	// 27 [end of while]
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	
	
	ALI::add_instruction(ALI::I_COUT);
	ALI::add_instruction(ALI::I_HALT);
	ALI::run();
}

inline void test_1e7()
{
	ALI::init();
	int n=10000000;
	
	// for (*1=1;*1<=1e7;*1++) *2=*2*10%998244353
	
	// *1 = 1
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// *2 = 1
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// 7	
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,n);
	ALI::add_instruction(ALI::I_LESS_OR_EQUAL);
	ALI::add_instruction(ALI::I_PUSH,29);
	ALI::add_instruction(ALI::I_JUMPZ);
	
	
	
	// *2=*2*10%mo
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,10);
	ALI::add_instruction(ALI::I_MULTIPLY);
	ALI::add_instruction(ALI::I_PUSH,998244353);
	ALI::add_instruction(ALI::I_MODULO);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// ++*1
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	ALI::add_instruction(ALI::I_PUSH,1);
	ALI::add_instruction(ALI::I_ADD);
	ALI::add_instruction(ALI::I_WRITEP);
	
	// 27
	ALI::add_instruction(ALI::I_PUSH,7);
	ALI::add_instruction(ALI::I_JUMP);
	// 29
	
	
	
	ALI::add_instruction(ALI::I_PUSH,2);
	ALI::add_instruction(ALI::I_DEREFERENCE);
	
	
	ALI::add_instruction(ALI::I_COUT);
	ALI::add_instruction(ALI::I_HALT);
	ALI::run();
}

inline void init_function_putchar()
{
	// the "inline" function putchar
	declare_function("putchar",4,1);
	ALI::add_instruction(ALI::I_DUP);
	ALI::add_instruction(ALI::I_PUTCHAR);
	ALI::add_instruction(ALI::I_RET);
}

int main()
{
	freopen("a.txt","r",stdin);
	InputManager::init();
	
	// test_1e7();
	// return 0;
	
	Linked_List_Init();
	
	Scanner::init();
	Tokenizer::init();
	
	std::vector<AST_node*> *root=program_uoj_98();
	// out(root,"");
	// debug("\n");
	
	declare_function("putchar",4,1);
	
	int size=root->size();
	int i;
	for (i=0;i<size;i++) {
		if (root->at(i)->type==NODE_FUNCTION) {
			count_function(root->at(i));
		} else {
			declare_global_variables(root->at(i)->a);
		}
	}
	debug("count ok\n");
	M_functions.clear();
	M_global_variables.clear();
	global_variable_cnt=0;
	ALI::init();
	ALI::add_instruction(ALI::I_PUSH,4);
	ALI::add_instruction(ALI::I_CALL);
	ALI::add_instruction(ALI::I_HALT);
	
	init_function_putchar();
	
	for (i=0;i<size;i++) {
		if (root->at(i)->type==NODE_FUNCTION) {
			compile_function(root->at(i));
		} else {
			declare_global_variables(root->at(i)->a);
		}
	}
	
	if (M_functions.count("main")==0) {
		report_error("int main() not found");
	}
	
	ALI::I[1].val=M_functions["main"].pos_begin;
	
	// 
	// 
	// 
	
	debug("");
	debug("--------------------");
	
	ALI::run();
	
	debug("");
	debug("--------------------");
	debug("ALI::IC = %d\n",ALI::instruction_count);
	debug("ALI::CC = %d\n",ALI::clock_cycles);
	
	return 0;
	
}
