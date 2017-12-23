//输出位序设从1开始
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
#define STUSIZE 100//假定学生最多为100人

class STU_INF {//学生信息记录的类
public:
	string order;//学号
	string name;//姓名
	double grade;//数据结构课程成绩

	STU_INF();//默认构造函数
};
STU_INF::STU_INF()//默认构造函数
{

}

class STU_NODE {
public:
	STU_INF data;//学生信息记录
	STU_NODE * prenode, *nextnode;//上一个结点和下一个结点

	STU_NODE();//默认构造函数
};
STU_NODE::STU_NODE()//默认构造函数
{
	prenode = NULL;
	nextnode = NULL;
}

class STUDENT {
public:
	STU_NODE * headptr;//头结点，不存储数据
	STU_INF seqList[STUSIZE];//存储按成绩非递减顺序排序好的学生数据
	int stuCnt;//记录学生数

	STUDENT();//默认构造函数
	void INITE();//初始数据输入（命令行用户输入）
	void FILE_INITE();//从文件中导入初始数据
	void QuickSort();//对学生记录查找表（双向链表形式）进行快速排序
	void QSort(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode);//对链表H中的headnode到tailnode之间的学生记录进行快序排序
	STU_NODE* Partition(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode);//进行一趟快速排序,返回枢轴位置
	void SaveToSeqList();//将排序好的数据转存到顺序表中
	void Search_Bin();//基于折半查找的算法对指定成绩的记录进行查询
	void Free();//释放链表结点空间
};
STUDENT::STUDENT()//默认构造函数
{
	stuCnt = 0;
	headptr = NULL;
}
void STUDENT::INITE()//初始数据输入（命令行用户输入）
{
	//headptr = (STU_NODE*)malloc(sizeof(STU_NODE));
	headptr = new STU_NODE;
	if (headptr != NULL)
	{
		//STU_NODE* newNode = (STU_NODE*)malloc(sizeof(STU_NODE));
		STU_NODE* newNode = new STU_NODE;
		if (newNode != NULL)
		{
			cout << "请输入学号：";
			cin >> newNode->data.order;
			cout << "请输入姓名：";
			cin >> newNode->data.name;
			cout << "请输入数据结构课程成绩：";
			cin >> newNode->data.grade;
			newNode->nextnode = headptr;
			newNode->prenode = headptr;
			headptr->nextnode = newNode;
			headptr->prenode = newNode;
			stuCnt++;
			cout << "你还要继续添加学生记录吗？输入Y or N(Y:YES,N:NO):";
			char option;
			cin >> option;
			while (option == 'Y')
			{
				//STU_NODE* newStuNode = (STU_NODE*)malloc(sizeof(STU_NODE));
				STU_NODE* newStuNode =new STU_NODE;
				if (newStuNode != NULL)
				{
					cout << "请输入学号：";
					cin >> newStuNode->data.order;
					cout << "请输入姓名：";
					cin >> newStuNode->data.name;
					cout << "请输入数据结构成绩：";
					cin >> newStuNode->data.grade;
					newStuNode->nextnode = headptr;
					newStuNode->prenode = headptr->prenode;
					headptr->prenode = newStuNode;
					newStuNode->prenode->nextnode = newStuNode;
					stuCnt++;
					cout << "你还要继续添加学生记录吗？输入Y or N(Y:YES,N:NO):";
					cin >> option;
				}
				else
				{
					cout << "申请链表结点空间失败！" << endl;
				}
			}
		}
		else
		{
			cout << "申请链表结点空间失败！" << endl;
		}
	}
	else
	{
		cout << "申请链表头结点空间失败！" << endl;
	}
	cout << "初始数据输入结束！" << endl<<endl;
}
void STUDENT::FILE_INITE()//从文件中导入初始数据
{
	ifstream OpenFile;
	string ORDER, NAME;
	double SCORE;
	headptr = new STU_NODE;
	if (headptr != NULL)
	{
		headptr->nextnode = headptr;
		headptr->prenode = headptr;
		cout << "请输入你想打开的文件名：";
		string filename;
		cin>>filename;
		OpenFile.open(filename);
		for (stuCnt = 0; OpenFile >> ORDER; stuCnt++)
		{
			STU_NODE* stuptr = new STU_NODE;//必须用new和delete，因为用了string类型的，如果用malloc和free会冲突报错
			if (stuptr != NULL)
			{
				stuptr->data.order = ORDER;
				OpenFile >> NAME;
				stuptr->data.name = NAME;
				OpenFile >> SCORE;
				stuptr->data.grade = SCORE;

				stuptr->nextnode = headptr;
				stuptr->prenode = headptr->prenode;
				headptr->prenode->nextnode = stuptr;
				headptr->prenode = stuptr;
				//测试输出
				cout << stuptr->data.order <<" " <<stuptr->data.name <<" "<< stuptr->data.grade << endl;
			}
			else
			{
				cout << "申请结点空间失败！" << endl;
			}
		}
		OpenFile.close();
	}
	else {
		cout << "申请头结点空间失败！" << endl;
	}
	cout << "导入结束！" << endl << endl;
}
	
void STUDENT::QuickSort()//对学生记录查找表（双向链表形式）进行快速排序
{
	QSort(headptr, headptr, headptr);
	cout << "快速排序结束！" << endl<<endl;

	//测试输出
	cout << endl<<"排序后如下："<<endl;
	STU_NODE*sptr = headptr->nextnode;
	while (sptr != headptr)
	{
		cout << sptr->data.order << " " << sptr->data.name << " " << sptr->data.grade << endl;
		sptr = sptr->nextnode;
	}
	cout << endl;
}
void STUDENT::SaveToSeqList()//将排序好的数据转存到顺序表中
{
	STU_NODE*ptr = headptr->nextnode;
	for (int i=0; ptr != headptr; ptr = ptr->nextnode,i++)
	{
		seqList[i] = ptr->data;
	}
	cout << "已经成功转存到顺序表中!" << endl<<endl;
}
void STUDENT::Search_Bin()//基于折半查找的算法对指定成绩的记录进行查询
{
	double keyGrade;
	char option='Y';
	//cout << "请输入你要查询的学生的成绩：";
	//cin >> keyGrade;
	while (option=='Y')
	{
		cout << "请输入你要查询的学生的成绩：";
		cin >> keyGrade;
		int low = 0, high = stuCnt - 1;
		int mid,flag=0;
		while (low <= high&&flag==0)
		{
			mid = (low + high) / 2;
			if (keyGrade == seqList[mid].grade)
			{
				flag = 1;
				//检查相同分数的情况
				int i,sameflag=0;
				for (i = mid + 1, sameflag = 0; i <stuCnt && sameflag == 0; i++)
				{
					if (seqList[i].grade != keyGrade)
						sameflag = 1;
				}
				int mark = i - 2;
				for (i = mid - 1, sameflag = 0; i > 0 && sameflag == 0; i--)
				{
					if (seqList[i].grade != keyGrade)
						sameflag = 1;
				}
				int j=i+2 ;
				for (sameflag = 0, j = i + 2; sameflag == 0 && j <= mark; j++)
				{
					cout << "姓名：" << seqList[j].name << endl;
					cout << "学号：" << seqList[j].order << endl;
					cout << "数据结构课程成绩：" << seqList[j].grade << endl;
					cout << "该同学的数据结构成绩排名第" << stuCnt - mark << ",即在有序序列中位序：" << j+1 << endl << endl;
				}
			}
			else if (keyGrade < seqList[mid].grade)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}
		if (flag == 0)
		{
			cout << "查找失败，没有该成绩的学生记录！" << endl<<endl;
		}
		cout << "请问你还要继续查询操作吗？请输入Y(YES) or N(NOT):";
		cin >> option;
	}
	cout << "查询操作结束！" << endl << endl;
}
void STUDENT::Free()//释放链表结点空间
{
	STU_NODE* temptr = headptr;
	headptr->prenode->nextnode = NULL;//设定一个结束的标志，将双向链表最后一个结点的next设为NULL
	while (headptr != NULL)
	{
		headptr = headptr->nextnode;
		//free(temptr);
		delete temptr;
		temptr = headptr;
	}
}
void STUDENT::QSort(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode)//对链表H中的headnode到tailnode之间的学生记录进行快序排序
{
	//if (headnode != tailnode)//这个条件导致我刚开始就不满足，所以什么都没发生。。。无用
	//{
		STU_NODE* pivotptr = Partition(H, headnode, tailnode);//一趟快速排序得到枢轴位置,再分解为如下对枢轴前和枢轴后的快速排序
		if(pivotptr->prenode!=headnode&&pivotptr->prenode->prenode!=headnode)
			QSort(H, headnode, pivotptr);
		if(pivotptr->nextnode!=tailnode&&pivotptr->nextnode->nextnode!=tailnode)
			QSort(H, pivotptr, tailnode);
	//}
}
STU_NODE* STUDENT::Partition(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode)//进行一趟快速排序,返回枢轴位置
{
	double pivotkey = headnode->nextnode->data.grade;
	STU_NODE*ptr=headnode->nextnode->nextnode;
	STU_NODE*resultptr = headnode->nextnode;
	//int compareCnt = 0;
	while (ptr != tailnode)
	{
		if (ptr->data.grade < pivotkey)//比枢轴小的的就插到枢轴前一个的位置
		{
			//compareCnt++;
			//if (compareCnt == 1)
			//	resultptr = ptr;
			STU_NODE*tempre = ptr->prenode;
			STU_NODE*tempnext = ptr->nextnode;
			ptr->nextnode = resultptr;
			ptr->prenode = resultptr->prenode;
			resultptr->prenode->nextnode = ptr;
			resultptr->prenode = ptr;
			tempre->nextnode = tempnext;
			tempnext->prenode = tempre;
			ptr = tempnext;
		}
		else
		{
			ptr = ptr->nextnode;
		}
	}

	//测试输出
/*	cout << endl<<"一"<<endl;
	STU_NODE*sptr = headptr->nextnode;
	while (sptr != headptr)
	{
		cout << sptr->data.order << " " << sptr->data.name << " " << sptr->data.grade << endl;
		sptr = sptr->nextnode;
	}
	cout << endl;*/

	return resultptr;
}

int main()
{
	STUDENT students;
	//students.INITE();//命令行手工输入初始数据
	students.FILE_INITE();//从文件导入初始数据,存在“data.txt”中
	students.QuickSort();//快速排序
	students.SaveToSeqList();//将排好序的数据存储到顺序表中
	students.Search_Bin();//二分查找法通过成绩查学生记录
	students.Free();//释放链表结点空间

	return 0;
}
