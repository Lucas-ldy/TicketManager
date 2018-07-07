#include "ticket.h"
using namespace std;

class user
{
	friend void save();
	friend void sure_message();
	friend void browse();
	friend void ticketmenu();
	friend void search_train();
	friend void search_station();
protected:
	char bus[10];
	Time time;
	char start_station[20];
	char end_station[20];
	int ticket_price;
	int remaind_seats;
public:
	void display()
	{
		cout << " " << bus << "\t" << " " << setfill('0') << setw(2) << time.hour << ":" << setw(2) << time.minute << "\t\t" << " "\
			<< start_station << "\t" << " " << end_station << "\t" << " " << ticket_price << "\t" << " " << remaind_seats << "\t";
		t = ::time(NULL);
		tm * pt = localtime(&t);
		if (time.hour < pt->tm_hour)
			cout << "\t�ѷ��� ";
		else if (time.hour == pt->tm_hour&&time.minute <= pt->tm_min)
			cout << "\t�ѷ��� ";
		else cout << "\t ���� ";
		cout << endl;
	}
	void order()
	{
		if (time.hour< pt->tm_hour)
			cout << " �˰��г��ѷ��� ,���ܶ�Ʊ���˳��� ";
		else if (time.hour == pt->tm_hour&&time.minute <  pt->tm_min)
			cout << " �˰��г��ѷ��� ,���ܶ�Ʊ���˳��� ";
		else if (remaind_seats == 0)
			cout << " �˰��г���ûƱ�����ܶ�Ʊ���˳��� " << endl;
		else
		{
			remaind_seats = remaind_seats - 1;
			cout << bus << " �ΰ೵ " << " ��Ʊһ�Σ��ִ�Ʊ��Ϊ�� " << remaind_seats << endl;
		}
	}
	void Delete()
	{
		if (time.hour < pt->tm_hour)
			cout << " �˰��г��ѷ��� ,������Ʊ���˳��� ";
		else if (time.hour == pt->tm_hour&&time.minute <= pt->tm_min)
			cout << " �˰��г��ѷ��� ,������Ʊ���˳��� ";
		else {
			remaind_seats = remaind_seats + 1;
			cout << bus << " ���г� " << " ��Ʊһ�Σ��ִ�Ʊ��Ϊ�� " << remaind_seats << endl;
		}
	}
};
class Admin :public user
{
	friend void input();
	friend void modifyTicket();
	friend void del();
public:
	void setinfo(char* c, int h, int m, char* q, char* z, int p, int s)
	{
		strcpy(bus, c);
		time.hour = h;
		time.minute = m;
		strcpy(start_station, q);
		strcpy(end_station, z);
		ticket_price = p;
		remaind_seats = s;
	}
};

Admin ticket[N];

void save()
{
	ofstream file(" ���� .txt", ios::out);//����һ�����������file
	for (int j = 0; j <= g_num; j++)
	{
		file << ticket[j].bus << " ";
		file << ticket[j].time.hour << " ";
		file << ticket[j].time.minute << " ";
		file << ticket[j].start_station << " ";
		file << ticket[j].end_station << " ";
		file << ticket[j].ticket_price << " ";
		file << ticket[j].remaind_seats << endl;
	}
	file.close();
	cout << " ��Ϣ�Ѵ����ļ� " << endl;
}
void del()
{
	char name[10];
	int i, j;
	cout << "��ѡ��ɾ�����ͣ�1.������ 2.��˳��" << endl;
	int k;
	cin >> k;
	switch (k)
	{
	case 1:
		cout << "\n������Ҫɾ���ĳ�������";
		cin >> name;
		for (i = 0;i <= g_num; i++)
		{
			if (strcmp(name, ticket[i].bus) == 0)
			{
				for (j = i + 1; j <= g_num; j++)
				{
					ticket[j - 1] = ticket[j];
				}
				cout << endl << "\t\t\tɾ���ɹ���\n";
				break;
			}

		}
		if (i > g_num)
		{
			cout << "�Բ���û�д˳�����Ϣ��" << endl;
		}
		else
		{
			g_num--;
			save();
		}
		break;
	case 2:
		cout << "\n������ɾ�����кţ��������£�" << endl;
		int lines;
		cin >> lines;
		for (; lines > g_num + 1;)
		{
			cout << "ָ��������������룡" << endl;
			cin >> lines;
			cout << endl << endl;
		}
		for (j = lines; j <= g_num; j++)
		{
			ticket[j - 1] = ticket[j];
		}
		cout << endl << "\t\t\tɾ���ɹ���\n";
		g_num--;
		save();
		break;

	}
}
void input()
{
	g_num++;
	char c[10];
	int h;
	int m;
	char q[20];
	char z[20];
	int p;
	int s;
	cout << " ���� :"; cin >> c;
	cout << " ����ʱ�� hour:"; cin >> h;
	cout << " ����ʱ�� minute:"; cin >> m;
	cout << " ��ʼ :"; cin >> q;
	cout << " �յ� :"; cin >> z;
	cout << " Ʊ�� :"; cin >> p;
	cout << " ʣ����λ :"; cin >> s;
	ticket[g_num].setinfo(c, h, m, q, z, p, s);
	save();
}
void modifyTicket()
{
	int j = 0;
	char bus[10];
	cout << " ������Ҫ�޸ĵĳ��Σ� ";
	cin >> bus;
	cout << endl << endl;
	for (j = 0; j <= g_num; j++)
		if (strcmp(bus, ticket[j].bus) == 0)
		{
			int h;
			int m;
			char q[20];
			char z[20];
			int p;
			int s;
			cout << " ����ʱ�� hour:"; cin >> h;
			cout << " ����ʱ�� minute:"; cin >> m;
			cout << " ��ʼ :"; cin >> q;
			cout << " �յ� :"; cin >> z;
			cout << " Ʊ�� :"; cin >> p;
			cout << " ʣ����λ :"; cin >> s;
			ticket[j].setinfo(bus, h, m, q, z, p, s);
			save();
			cout << "��Ʊ��Ϣ�޸ĳɹ�" << endl;
			break;
		}
	if (j > g_num)
		cout << " �Բ���û�����˳�����Ϣ�� ";
}
void browse()
{
	int j;
	t = time(NULL);
	tm * pt = localtime(&t);
	cout << " ��ǰʱ�䣺 " << setfill('0') << setw(2) << pt->tm_hour << ':';
	cout << setw(2) << pt->tm_min << ':';
	cout << setw(2) << pt->tm_sec << endl << endl;
	cout << " �ִ泵����Ϣ���£� " << endl << endl;
	cout << " ���� \t" << " ����ʱ�� \t" << " ��ʼ \t" << " �յ� \t" << " Ʊ�� \t" << " ʣ����λ \t" << " ״̬ \t" << endl;
	for (j = 0; j <= g_num; j++)
	{
		ticket[j].display();
	}
}
void search_train()
{
	int j = 0;
	char bus[10];
	cout << " ������Ҫ��ѯ�ĳ��Σ� ";
	cin >> bus;
	cout << endl << endl;
	for (j = 0; j <= g_num; j++)
	{
		if (strcmp(bus, ticket[j].bus) == 0)
		{
			cout << " ��ѯ����� " << endl;
			cout << " ���� \t" << " ����ʱ�� \t" << " ��ʼ \t" << " �յ� \t" << " Ʊ�� \t" << " ʣ����λ \t" << " ״̬ \t" << endl;
			ticket[j].display();
			break;
		}
	}
	if (j > g_num)
		cout << " �Բ���û�����˳�����Ϣ�� ";
}
void search_station()
{
	int j = 0;
	int i = 0;
	int flag = 1;
	char station[20];
	cout << " ������Ҫ��ѯ��վ�㣺 ";
	cin >> station;
	cout << endl << endl;
	for (j = 0; j <= g_num; j++)
	{
		if ((strcmp(station, ticket[j].start_station) == 0) || (strcmp(station, ticket[j].end_station) == 0))
		{
			if (flag)
			{
				cout << " ��ѯ����� " << endl;
				cout << " ���� \t" << " ����ʱ�� \t" << " ��ʼ \t" << " �յ� \t" << " Ʊ�� \t" << " ʣ����λ \t" << " ״̬\t" << endl;
				flag = 0;
			}
			ticket[j].display();
			i++;
		}
	}
	if (j > g_num && i == 0)
		cout << " �Բ���û���йش�վ��ĳ�����Ϣ�� ";
}
void ticketmenu()
{
	time_t t = time(0);
	tm * pt = localtime(&t);
	int functionNumber;
	int j;
	cout << " >>>>>> Ʊ��˵� <<<<<< \n";
	char bus[10]; char station[20];
	cout << " �ɰ�վ��򳵴β�ѯ��Ʊ�� 1.��վ�㣬 2.�����Σ� " << endl;
	cout << " ѡ������Ҫ�Ĺ��� :";
	cin >> functionNumber; getchar();
	for (; functionNumber != 1 && functionNumber != 2;)
	{
		cout << " ָ��������������룡 " << endl;
		cin >> functionNumber;
	}
	cout << endl << endl;
	if (functionNumber == 1)
	{
		cout << " ������Ҫ��Ʊ����Ʊ��վ�㣺 ";
		cin >> station;
		cout << endl << endl;
		for (j = 0; j <= g_num; j++)
			if ((strcmp(station, ticket[j].start_station) == 0) || (strcmp(station, ticket[j].end_station) == 0))
			{
				cout << " �������ִ���Ϣ :" << endl;
				cout << " ���� \t" << " ����ʱ�� \t" << " ��ʼ \t" << " �յ� \t" << " Ʊ�� \t" << " ʣ����λ \t" << " ״̬\t" << endl;
				ticket[j].display(); break;
			}
		if (j>g_num)
			cout << " �Բ���û�����˳�����Ϣ�� ,�޷�����Ʊ�� ";
	}
	if (functionNumber == 2)
	{
		cout << " ������Ҫ��Ʊ����Ʊ�ĳ��Σ� ";
		cin >> bus;
		cout << endl << endl;
		for (j = 0; j <= g_num; j++)
			if (strcmp(bus, ticket[j].bus) == 0)
			{
				cout << " �������ִ���Ϣ :" << endl;
				cout << " ���� \t" << " ����ʱ�� \t" << " ��ʼ \t" << " �յ� \t" << " Ʊ�� \t" << " ʣ����λ \t" << " ״̬\t" << endl;
				ticket[j].display(); break;
			}
		if (j>g_num)
			cout << " �Բ���û���йش�վ��ĳ�����Ϣ���޷�����Ʊ�� ";
	}
	if (ticket[j].time.hour<pt->tm_hour)
		cout << " �˰��г��ѷ��� ,���ܶ���Ʊ�� ";
	else if (ticket[j].time.hour == pt->tm_hour&&ticket[j].time.minute <= pt->tm_min)
		cout << " �˰��г��ѷ��� ,���ܶ���Ʊ�� ";
	else
	{
		cout << "\n";
		cout << " 1.��Ʊ \n";
		cout << " 2.��Ʊ \n";
		cout << " 3.�������˵� \n";
		cout << "\n";
		cout << " ѡ������Ҫ�Ĺ��� :";
		cin >> functionNumber;
		for (; functionNumber != 1 && functionNumber != 2 && functionNumber != 3;)
		{
			cout << " ָ��������������룡 " << endl;
			cin >> functionNumber;
		}
		cout << endl << endl;
		switch (functionNumber)
		{
		case 1:ticket[j].order(); save(); break;
		case 2:ticket[j].Delete(); save(); break;
		case 3:mainmenu(); break;
		}//switch ends
	}
}
void search_menu()
{
	int functionNumber;
	cout << " >>>>>> ��ѯ�Ӳ˵� <<<<<< \n";
	cout << endl;
	cout << " 1.����β�ѯ \n";
	cout << " 2.��վ���ѯ \n";
	cout << " 3.�������˵� \n";
	cout << endl;
	cout << " ��ѡ��������Ҫ�Ĺ��� :";
	cin >> functionNumber;
	cout << endl << endl;
	for (; functionNumber != 1 && functionNumber != 2 && functionNumber != 3;)
	{
		cout << " ָ��������������룡 " << endl;
		cin >> functionNumber;
		cout << endl << endl;
	}
	switch (functionNumber)
	{
	case 1:
		search_train(); break;
	case 2:
		search_station(); break;
	case 3:
		system("cls");
		mainmenu();
	}
}
void mainmenu()
{
	int functionNumber;
	cout << " >>>>>> ��ӭʹ��Ʊ��С�ܼ� <<<<<< \n";
	cout << endl;
	cout << " 1.¼������Ϣ \n";
	cout << " 2.ɾ�������Ϣ\n";
	cout << " 3.�޸ĳ�Ʊ��Ϣ\n";
	cout << " 4.��������Ϣ \n";
	cout << " 5.��ѯ�г�·�� \n";
	cout << " 6.��Ʊ����Ʊ \n";
	cout << " 7.�˳� \n";

	cout << endl;
	cout << " ��ѡ��������Ҫ�Ĺ��� :";
	cin >> functionNumber;
	cout << endl << endl;
	switch (functionNumber)
	{
	case 1:
	{
		char c;
		if (A)
		{
			do
			{
				input();
				cout << " ��¼�� " << g_num + 1 << " �������Ϣ�������Ѵ��ļ��ж�ȡ�ģ� �������¼����(y / n)" << endl;
				cin >> c;
				for (; c != 'y'&&c != 'n';)
				{
					cout << " ָ��������������룡 " << endl;
					cin >> c;
				}
			} while (c == 'y');
		}
		else
			cout << " �Բ��������ǹ���Ա���ܽ������������ ";
		cout << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 2:
	{
		if (A)
		{
			del();
		}
		else
		{
			cout << " �Բ��������ǹ���Ա���ܽ������������ ";

		}
		cout << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 4://���
	{
		browse();
		cout << endl << endl << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 5://����
	{
		search_menu();
		cout << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 6:
	{
		ticketmenu();
		cout << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 7:
	{
		t = time(NULL);
		tm* pt = localtime(&t);
		system("cls");
		cout << endl << endl << endl << endl << endl << endl << endl;
		cout << " >>>>>> ллʹ�ó�Ʊ����ϵͳ <<<<<< \n";
		B = false;
	}
	break;
	case 3:
	{

		if (A)
			modifyTicket();
		else
			cout << "�Բ��������ǹ���Ա���ܽ������������";
		cout << endl << endl << endl << " ������������˵� ......" << endl;
		getchar();
		getchar();
		system("cls");


	}
	break;

	default:
	{
		cout << " ������� ,��ȷ���������Ϊ 1--6" << endl;
		cout << " ������������˵� ......" << endl;
		getchar();
		system("cls");
	}
	}//switch ends
}
void sure_message()
{
	cout << " >>>>>> ��ӭʹ��Ʊ��С�ܼ� <<<<<< \n"
		<< endl << endl;
	ifstream file(" ���� .txt", ios::in);
	if (!file)
	{
		if (A)
		{
			cout << " ��û¼�����Ϣ ,������¼����Ϣ " << endl;
			input();
			cout << endl << " ������������˵� ......" << endl;
			getchar();
			system("cls");
			mainmenu();
		}
		else cout << " �Բ���ϵͳ��û¼����κ���Ϣ ,����ʾ����Ա¼����Ϣ�� ";
	}
	else {
		cout << " ����������δ¼����Ϣ��Ĭ�϶�ȡ�Ѵ���Ϣ \n";
		cout << " ���������ȡ ......\n";
		getchar();
		getchar();
		while (!file.eof())
		{
			g_num++;
			file >> ticket[g_num].bus;
			file >> ticket[g_num].time.hour;
			file >> ticket[g_num].time.minute;
			file >> ticket[g_num].start_station;
			file >> ticket[g_num].end_station;
			file >> ticket[g_num].ticket_price;
			file >> ticket[g_num].remaind_seats;
		}
		g_num--;
		file.close();//ʹ��eof���������������ļ�������־EOFʱ���������̷���ture�����ǻ����������һ���ŷ��ء�
		cout << " ��ȡ��ϣ� " << endl;
	}
}
void main()
{
	int functionNumber, code;
	cout << " ������������ݣ� 1.����Ա�� 2.�˿ͣ� " << endl;
	cout << " ������� :";
	cin >> functionNumber;
	for (; functionNumber != 1 && functionNumber != 2;)
	{
		cout << " ָ��������������룡 " << endl;
		cin >> functionNumber;
	}
	if (functionNumber == 1)
	{
		cout << " ���������룺 ";
		cin >> code;
		for (; code != 123;)
		{
			cout << " ָ��������������룡 " << endl;
			cin >> code;
		}
		A = true;
	}
	sure_message();
	do mainmenu();
	while (B);
}