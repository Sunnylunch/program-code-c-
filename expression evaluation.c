#include<stdio.h>
#include<stdlib.h>

#define STACK_INIT_MEMORY 20                  //初始时开辟栈的内存大小
#define STACK_GROW_MEMORY 10                  //当栈满时，追加内存的大小

const char arr[7];                            //声明一个存放运算符的一维数组，作为索引
void init_priority_list(char list[][7]);      //初始化符号表

typedef struct stack_num                      //声明一个存放运算数的结构体类型
{
	int *esp;                                 //栈顶指针
	int *ebp;                                 //栈底指针
	int size;                                 //记录当前栈空间最多能存几个元素
}stack_num;

void creatstack_num(stack_num *S);            //创建存放运算数的栈
void push_num(stack_num *S, int x);           //将参数x中的数压入运算数栈中
int pop_num(stack_num *S, int *x);            //弹出栈顶元素，并通过形参x带回

typedef struct stackpop_opreation             //声明一个存放运算符的结构体类型
{
	char *esp;                                //栈顶指针
	char *ebp;                                //栈底指针
	int size;                                 //记录当前栈空间最多能存几个元素
}stack_operation;
void creatstack_operation(stack_operation *S);         //创建一个存放运算符的栈
void push_operation(stack_operation *S, char symbol);  //将符号压入运算符栈中
int pop_opreation(stack_operation *S, char *top);      //将运算符栈中的栈顶元素弹出



char judge_priority(stack_operation* S, char c);       //判断读取的运算符与栈顶符号的优先级,并返回
int operation(int a, char symbol, int b);              //对运算数进行相的运算，并将结果返回
int judge_num(char c);                                 //判断读取的是符号还是数字，如果是数字返回1


const char arr[7] = { '+', '-', '*', '/', '(', ')', '#' };     //通过arr[7]来查找list[][]中的优先级

void init_priority_list(char list[][7])                      //初始化优先级列表
{
	int arr2[7] = { 1, 1, 2, 2, 3, 0, -1 };                  //列作为栈顶元素，行代表读取的运算符
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			if ((i == 4 && j == 5) || (i == 6 && j == 6))    //令'('与‘）’，‘#’与‘#’优先级相同
				list[i][j] = '=';
			else
			{
				if (arr2[i] >= arr2[j])
					list[i][j] = '>';                        //栈顶优先级高
				else if (arr2[i] <= arr2[j])
					list[i][j] = '<';                        //读取的运算符优先级高
			}

		}
	}
}

void creatstack_num(stack_num *S)                            //创建运算数栈
{
	S->ebp = (int *)malloc(sizeof(int)* STACK_INIT_MEMORY);
	if (S->ebp == NULL)                                      //判断动态内存是否开辟成功
		exit(1);
	S->size = STACK_INIT_MEMORY;             
	S->esp = S->ebp;                                          //空栈，让栈顶指针指向栈底
}
void push_num(stack_num *S, int x)
{
	if (S->esp - S->ebp >= S->size)                           //判断当前栈是否已满
	{                                                         //栈满追加空间
		S->ebp = (int *)realloc(S->ebp, sizeof(int)*(S->size + STACK_GROW_MEMORY));
		if (S->ebp == NULL)
			exit(1);
		S->esp = S->ebp + S->size;                            //让栈顶指针向后偏移指向要入栈的位置
		S->size += STACK_GROW_MEMORY;                         //更新栈size
	}
	*S->esp++ = x;
}
int pop_num(stack_num *S, int *x)               
{
	if (S->esp == S->ebp)
		return 0;                                             //如果是空栈，则返回0
	else
	{
		*x = *--S->esp;
		return 1;                                             //如果弹出成功，返回1，并将弹出的元素保存在x中带回
	}
}




void creatstack_operation(stack_operation *S)                  //创建运算符栈
{
	S->ebp = (char *)malloc(sizeof(char)*STACK_INIT_MEMORY);
	if (S->ebp == NULL)
		exit(1);                                               //判断动态内存是否开辟成功
	S->size = STACK_INIT_MEMORY;
	S->esp = S->ebp;
}
void push_operation(stack_operation *S, char symbol)
{
	if (S->esp - S->ebp >= S->size)                            //如果栈满则追加空间
	{
		S->ebp = (char *)realloc(S->ebp, sizeof(char)*(S->size += STACK_GROW_MEMORY));
		if (S->ebp == NULL)
			exit(1);
		S->ebp = S->ebp + S->size - STACK_GROW_MEMORY;
	}
	*S->esp++ = symbol;
}
int pop_opreation(stack_operation *S, char *top)
{
	if (S->esp == S->ebp)
		return 0;                                              //如果栈是空栈，则返回0
	else
		*top = *--S->esp;                                       //否则将弹出的匀速保存在top中带回
	return 1;
}


char judge_priority(stack_operation* S, char c)                  //判断栈顶运算符与读取的运算符的优先级
{
	char list[7][7];
	init_priority_list(list);                                    //初始化优先级表
	int line = 0;                                  
	int row = 0;
	for (line = 0; line < 7; line++)
	{
		if (arr[line] == *(S->esp - 1))                          //将栈顶符号在arr[]中的位置作为行下标
			break;
	}
	for (row = 0; row < 7; row++)
	{
		if (arr[row] == c)                                       //将读取的运算符在arr[]中的位置作为列下标
			break;
	}
	return list[line][row];                                      //通过优先级表，返回优先级关系
}


int operation(int a, char symbol, int b)        
{
	int ret = 0;
	switch (symbol)
	{
	case '+':
		ret = a + b;
		break;
	case '-':
		ret = a - b;
		break;
	case '*':
		ret = a*b;
		break;
	case '/':
		ret = a / b;
		break;
	default:
		break;
	}
	return ret;
}


int judge_num(char c)                             //判断读取的是不是数字
{
	int i = 0;
	for (i = 0; i < 7; i++)
	{
		if (arr[i] == c)                        
			break;
	}
	if (i == 7)
		return 1;                                 //如果是数字则返回1
	else
		return 0;                                 //如果不是数字则返回0
}


int main()
{

	stack_num num_stack;
	creatstack_num(&num_stack);                      //建立一个运算数栈
	stack_operation operator_stack;
	creatstack_operation(&operator_stack);           //建立一个运算符栈
	int c;
	char symbol;
	int a = 0;
	int b = 0;
	int ret = 0;
	push_operation(&operator_stack, '#');            //将‘#’入栈，作为运算符栈的栈底
	c=getchar();
	while (c!='#'||*(operator_stack.esp-1)!='#')     //接受表达式并且判断表达式是否输入完毕
	{
		
		if (judge_num(c))                            //如果是数字则进入运算数栈
		{
			int num = 0;
			while (judge_num(c))                     //把连续的char类型的数字全部读取并转化成相应的整数
			{
				num = num * 10 + (c-'0');            //因为这是的运算数是char类型，所以先要转换成int
				c = getchar();
			}
			push_num(&num_stack,num);                 //将运算数入栈
		}
		else                                                        
		{
			switch (judge_priority(&operator_stack,c))     //判断读取的运算符与栈顶符号的优先级关系
			{
			case '<':                                      //如果读取的符号优先级高，则直接进入运算符栈
				push_operation(&operator_stack, c);
				c=getchar();
				break;
			case '>':                                    //如果读取的符号优先级低，则栈顶符号退栈，将运算结果入栈
				pop_opreation(&operator_stack, &symbol); //则栈顶符号退栈
				pop_num(&num_stack, &b);                
				pop_num(&num_stack, &a);                 // 将运算数栈栈顶的两个元素弹出
				ret=operation(a, symbol, b);             //将这两个元素进行运算
				push_num(&num_stack, ret);               //将运算结果入栈
				break;
			case '=':                                     //当读取到“）”时则一直退栈直到遇到“（”
				pop_opreation(&operator_stack, &symbol);
				c=getchar();
				break;
			default:
				break;
			}
		}		

	}
	printf("%d\n", *(num_stack.esp-1));                  //将运算数栈最后剩下的数输出
	system("pause");
	free(num_stack.ebp);
	free(operator_stack.ebp);
	return 0;
}
