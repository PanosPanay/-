//���λ�����1��ʼ
#include <iostream>
#include<string>
#include<fstream>
using namespace std;
#define STUSIZE 100//�ٶ�ѧ�����Ϊ100��

class STU_INF {//ѧ����Ϣ��¼����
public:
	string order;//ѧ��
	string name;//����
	double grade;//���ݽṹ�γ̳ɼ�

	STU_INF();//Ĭ�Ϲ��캯��
};
STU_INF::STU_INF()//Ĭ�Ϲ��캯��
{

}

class STU_NODE {
public:
	STU_INF data;//ѧ����Ϣ��¼
	STU_NODE * prenode, *nextnode;//��һ��������һ�����

	STU_NODE();//Ĭ�Ϲ��캯��
};
STU_NODE::STU_NODE()//Ĭ�Ϲ��캯��
{
	prenode = NULL;
	nextnode = NULL;
}

class STUDENT {
public:
	STU_NODE * headptr;//ͷ��㣬���洢����
	STU_INF seqList[STUSIZE];//�洢���ɼ��ǵݼ�˳������õ�ѧ������
	int stuCnt;//��¼ѧ����

	STUDENT();//Ĭ�Ϲ��캯��
	void INITE();//��ʼ�������루�������û����룩
	void FILE_INITE();//���ļ��е����ʼ����
	void QuickSort();//��ѧ����¼���ұ�˫��������ʽ�����п�������
	void QSort(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode);//������H�е�headnode��tailnode֮���ѧ����¼���п�������
	STU_NODE* Partition(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode);//����һ�˿�������,��������λ��
	void SaveToSeqList();//������õ�����ת�浽˳�����
	void Search_Bin();//�����۰���ҵ��㷨��ָ���ɼ��ļ�¼���в�ѯ
	void Free();//�ͷ�������ռ�
};
STUDENT::STUDENT()//Ĭ�Ϲ��캯��
{
	stuCnt = 0;
	headptr = NULL;
}
void STUDENT::INITE()//��ʼ�������루�������û����룩
{
	//headptr = (STU_NODE*)malloc(sizeof(STU_NODE));
	headptr = new STU_NODE;
	if (headptr != NULL)
	{
		//STU_NODE* newNode = (STU_NODE*)malloc(sizeof(STU_NODE));
		STU_NODE* newNode = new STU_NODE;
		if (newNode != NULL)
		{
			cout << "������ѧ�ţ�";
			cin >> newNode->data.order;
			cout << "������������";
			cin >> newNode->data.name;
			cout << "���������ݽṹ�γ̳ɼ���";
			cin >> newNode->data.grade;
			newNode->nextnode = headptr;
			newNode->prenode = headptr;
			headptr->nextnode = newNode;
			headptr->prenode = newNode;
			stuCnt++;
			cout << "�㻹Ҫ�������ѧ����¼������Y or N(Y:YES,N:NO):";
			char option;
			cin >> option;
			while (option == 'Y')
			{
				//STU_NODE* newStuNode = (STU_NODE*)malloc(sizeof(STU_NODE));
				STU_NODE* newStuNode =new STU_NODE;
				if (newStuNode != NULL)
				{
					cout << "������ѧ�ţ�";
					cin >> newStuNode->data.order;
					cout << "������������";
					cin >> newStuNode->data.name;
					cout << "���������ݽṹ�ɼ���";
					cin >> newStuNode->data.grade;
					newStuNode->nextnode = headptr;
					newStuNode->prenode = headptr->prenode;
					headptr->prenode = newStuNode;
					newStuNode->prenode->nextnode = newStuNode;
					stuCnt++;
					cout << "�㻹Ҫ�������ѧ����¼������Y or N(Y:YES,N:NO):";
					cin >> option;
				}
				else
				{
					cout << "����������ռ�ʧ�ܣ�" << endl;
				}
			}
		}
		else
		{
			cout << "����������ռ�ʧ�ܣ�" << endl;
		}
	}
	else
	{
		cout << "��������ͷ���ռ�ʧ�ܣ�" << endl;
	}
	cout << "��ʼ�������������" << endl<<endl;
}
void STUDENT::FILE_INITE()//���ļ��е����ʼ����
{
	ifstream OpenFile;
	string ORDER, NAME;
	double SCORE;
	headptr = new STU_NODE;
	if (headptr != NULL)
	{
		headptr->nextnode = headptr;
		headptr->prenode = headptr;
		cout << "����������򿪵��ļ�����";
		string filename;
		cin>>filename;
		OpenFile.open(filename);
		for (stuCnt = 0; OpenFile >> ORDER; stuCnt++)
		{
			STU_NODE* stuptr = new STU_NODE;//������new��delete����Ϊ����string���͵ģ������malloc��free���ͻ����
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
				//�������
				cout << stuptr->data.order <<" " <<stuptr->data.name <<" "<< stuptr->data.grade << endl;
			}
			else
			{
				cout << "������ռ�ʧ�ܣ�" << endl;
			}
		}
		OpenFile.close();
	}
	else {
		cout << "����ͷ���ռ�ʧ�ܣ�" << endl;
	}
	cout << "���������" << endl << endl;
}
	
void STUDENT::QuickSort()//��ѧ����¼���ұ�˫��������ʽ�����п�������
{
	QSort(headptr, headptr, headptr);
	cout << "�������������" << endl<<endl;

	//�������
	cout << endl<<"��������£�"<<endl;
	STU_NODE*sptr = headptr->nextnode;
	while (sptr != headptr)
	{
		cout << sptr->data.order << " " << sptr->data.name << " " << sptr->data.grade << endl;
		sptr = sptr->nextnode;
	}
	cout << endl;
}
void STUDENT::SaveToSeqList()//������õ�����ת�浽˳�����
{
	STU_NODE*ptr = headptr->nextnode;
	for (int i=0; ptr != headptr; ptr = ptr->nextnode,i++)
	{
		seqList[i] = ptr->data;
	}
	cout << "�Ѿ��ɹ�ת�浽˳�����!" << endl<<endl;
}
void STUDENT::Search_Bin()//�����۰���ҵ��㷨��ָ���ɼ��ļ�¼���в�ѯ
{
	double keyGrade;
	char option='Y';
	//cout << "��������Ҫ��ѯ��ѧ���ĳɼ���";
	//cin >> keyGrade;
	while (option=='Y')
	{
		cout << "��������Ҫ��ѯ��ѧ���ĳɼ���";
		cin >> keyGrade;
		int low = 0, high = stuCnt - 1;
		int mid,flag=0;
		while (low <= high&&flag==0)
		{
			mid = (low + high) / 2;
			if (keyGrade == seqList[mid].grade)
			{
				flag = 1;
				//�����ͬ���������
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
					cout << "������" << seqList[j].name << endl;
					cout << "ѧ�ţ�" << seqList[j].order << endl;
					cout << "���ݽṹ�γ̳ɼ���" << seqList[j].grade << endl;
					cout << "��ͬѧ�����ݽṹ�ɼ�������" << stuCnt - mark << ",��������������λ��" << j+1 << endl << endl;
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
			cout << "����ʧ�ܣ�û�иóɼ���ѧ����¼��" << endl<<endl;
		}
		cout << "�����㻹Ҫ������ѯ������������Y(YES) or N(NOT):";
		cin >> option;
	}
	cout << "��ѯ����������" << endl << endl;
}
void STUDENT::Free()//�ͷ�������ռ�
{
	STU_NODE* temptr = headptr;
	headptr->prenode->nextnode = NULL;//�趨һ�������ı�־����˫���������һ������next��ΪNULL
	while (headptr != NULL)
	{
		headptr = headptr->nextnode;
		//free(temptr);
		delete temptr;
		temptr = headptr;
	}
}
void STUDENT::QSort(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode)//������H�е�headnode��tailnode֮���ѧ����¼���п�������
{
	//if (headnode != tailnode)//������������Ҹտ�ʼ�Ͳ����㣬����ʲô��û��������������
	//{
		STU_NODE* pivotptr = Partition(H, headnode, tailnode);//һ�˿�������õ�����λ��,�ٷֽ�Ϊ���¶�����ǰ�������Ŀ�������
		if(pivotptr->prenode!=headnode&&pivotptr->prenode->prenode!=headnode)
			QSort(H, headnode, pivotptr);
		if(pivotptr->nextnode!=tailnode&&pivotptr->nextnode->nextnode!=tailnode)
			QSort(H, pivotptr, tailnode);
	//}
}
STU_NODE* STUDENT::Partition(STU_NODE* H, STU_NODE* headnode, STU_NODE* tailnode)//����һ�˿�������,��������λ��
{
	double pivotkey = headnode->nextnode->data.grade;
	STU_NODE*ptr=headnode->nextnode->nextnode;
	STU_NODE*resultptr = headnode->nextnode;
	//int compareCnt = 0;
	while (ptr != tailnode)
	{
		if (ptr->data.grade < pivotkey)//������С�ĵľͲ嵽����ǰһ����λ��
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

	//�������
/*	cout << endl<<"һ"<<endl;
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
	//students.INITE();//�������ֹ������ʼ����
	students.FILE_INITE();//���ļ������ʼ����,���ڡ�data.txt����
	students.QuickSort();//��������
	students.SaveToSeqList();//���ź�������ݴ洢��˳�����
	students.Search_Bin();//���ֲ��ҷ�ͨ���ɼ���ѧ����¼
	students.Free();//�ͷ�������ռ�

	return 0;
}
