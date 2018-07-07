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
			cout << "\t已发出 ";
		else if (time.hour == pt->tm_hour&&time.minute <= pt->tm_min)
			cout << "\t已发出 ";
		else cout << "\t 正常 ";
		cout << endl;
	}
	void order()
	{
		if (time.hour< pt->tm_hour)
			cout << " 此班列车已发出 ,不能订票，退出！ ";
		else if (time.hour == pt->tm_hour&&time.minute <  pt->tm_min)
			cout << " 此班列车已发出 ,不能订票，退出！ ";
		else if (remaind_seats == 0)
			cout << " 此班列车已没票，不能订票，退出！ " << endl;
		else
		{
			remaind_seats = remaind_seats - 1;
			cout << bus << " 次班车 " << " 售票一次，现存票量为： " << remaind_seats << endl;
		}
	}
	void Delete()
	{
		if (time.hour < pt->tm_hour)
			cout << " 此班列车已发出 ,不能退票，退出！ ";
		else if (time.hour == pt->tm_hour&&time.minute <= pt->tm_min)
			cout << " 此班列车已发出 ,不能退票，退出！ ";
		else {
			remaind_seats = remaind_seats + 1;
			cout << bus << " 次列车 " << " 退票一次，现存票量为： " << remaind_seats << endl;
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
	ofstream file(" 数据 .txt", ios::out);//定义一个输出流对象file
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
	cout << " 信息已存入文件 " << endl;
}
void del()
{
	char name[10];
	int i, j;
	cout << "请选择删除类型（1.按车次 2.按顺序）" << endl;
	int k;
	cin >> k;
	switch (k)
	{
	case 1:
		cout << "\n请输入要删除的车次名：";
		cin >> name;
		for (i = 0;i <= g_num; i++)
		{
			if (strcmp(name, ticket[i].bus) == 0)
			{
				for (j = i + 1; j <= g_num; j++)
				{
					ticket[j - 1] = ticket[j];
				}
				cout << endl << "\t\t\t删除成功！\n";
				break;
			}

		}
		if (i > g_num)
		{
			cout << "对不起，没有此车次信息！" << endl;
		}
		else
		{
			g_num--;
			save();
		}
		break;
	case 2:
		cout << "\n请输入删除的行号（从上往下）" << endl;
		int lines;
		cin >> lines;
		for (; lines > g_num + 1;)
		{
			cout << "指令错误！请重新输入！" << endl;
			cin >> lines;
			cout << endl << endl;
		}
		for (j = lines; j <= g_num; j++)
		{
			ticket[j - 1] = ticket[j];
		}
		cout << endl << "\t\t\t删除成功！\n";
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
	cout << " 车次 :"; cin >> c;
	cout << " 开车时间 hour:"; cin >> h;
	cout << " 开车时间 minute:"; cin >> m;
	cout << " 起始 :"; cin >> q;
	cout << " 终点 :"; cin >> z;
	cout << " 票价 :"; cin >> p;
	cout << " 剩余座位 :"; cin >> s;
	ticket[g_num].setinfo(c, h, m, q, z, p, s);
	save();
}
void modifyTicket()
{
	int j = 0;
	char bus[10];
	cout << " 输入你要修改的车次： ";
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
			cout << " 开车时间 hour:"; cin >> h;
			cout << " 开车时间 minute:"; cin >> m;
			cout << " 起始 :"; cin >> q;
			cout << " 终点 :"; cin >> z;
			cout << " 票价 :"; cin >> p;
			cout << " 剩余座位 :"; cin >> s;
			ticket[j].setinfo(bus, h, m, q, z, p, s);
			save();
			cout << "车票信息修改成功" << endl;
			break;
		}
	if (j > g_num)
		cout << " 对不起，没有这趟车次信息！ ";
}
void browse()
{
	int j;
	t = time(NULL);
	tm * pt = localtime(&t);
	cout << " 当前时间： " << setfill('0') << setw(2) << pt->tm_hour << ':';
	cout << setw(2) << pt->tm_min << ':';
	cout << setw(2) << pt->tm_sec << endl << endl;
	cout << " 现存车次信息如下： " << endl << endl;
	cout << " 车次 \t" << " 开车时间 \t" << " 起始 \t" << " 终点 \t" << " 票价 \t" << " 剩余座位 \t" << " 状态 \t" << endl;
	for (j = 0; j <= g_num; j++)
	{
		ticket[j].display();
	}
}
void search_train()
{
	int j = 0;
	char bus[10];
	cout << " 输入你要查询的车次： ";
	cin >> bus;
	cout << endl << endl;
	for (j = 0; j <= g_num; j++)
	{
		if (strcmp(bus, ticket[j].bus) == 0)
		{
			cout << " 查询结果： " << endl;
			cout << " 车次 \t" << " 开车时间 \t" << " 起始 \t" << " 终点 \t" << " 票价 \t" << " 剩余座位 \t" << " 状态 \t" << endl;
			ticket[j].display();
			break;
		}
	}
	if (j > g_num)
		cout << " 对不起，没有这趟车次信息！ ";
}
void search_station()
{
	int j = 0;
	int i = 0;
	int flag = 1;
	char station[20];
	cout << " 输入你要查询的站点： ";
	cin >> station;
	cout << endl << endl;
	for (j = 0; j <= g_num; j++)
	{
		if ((strcmp(station, ticket[j].start_station) == 0) || (strcmp(station, ticket[j].end_station) == 0))
		{
			if (flag)
			{
				cout << " 查询结果： " << endl;
				cout << " 车次 \t" << " 开车时间 \t" << " 起始 \t" << " 终点 \t" << " 票价 \t" << " 剩余座位 \t" << " 状态\t" << endl;
				flag = 0;
			}
			ticket[j].display();
			i++;
		}
	}
	if (j > g_num && i == 0)
		cout << " 对不起，没有有关此站点的车次信息！ ";
}
void ticketmenu()
{
	time_t t = time(0);
	tm * pt = localtime(&t);
	int functionNumber;
	int j;
	cout << " >>>>>> 票务菜单 <<<<<< \n";
	char bus[10]; char station[20];
	cout << " 可按站点或车次查询订票（ 1.按站点， 2.按车次） " << endl;
	cout << " 选择你需要的功能 :";
	cin >> functionNumber; getchar();
	for (; functionNumber != 1 && functionNumber != 2;)
	{
		cout << " 指令错误！请重新输入！ " << endl;
		cin >> functionNumber;
	}
	cout << endl << endl;
	if (functionNumber == 1)
	{
		cout << " 输入你要订票或退票的站点： ";
		cin >> station;
		cout << endl << endl;
		for (j = 0; j <= g_num; j++)
			if ((strcmp(station, ticket[j].start_station) == 0) || (strcmp(station, ticket[j].end_station) == 0))
			{
				cout << " 本车次现存信息 :" << endl;
				cout << " 车次 \t" << " 开车时间 \t" << " 起始 \t" << " 终点 \t" << " 票价 \t" << " 剩余座位 \t" << " 状态\t" << endl;
				ticket[j].display(); break;
			}
		if (j>g_num)
			cout << " 对不起，没有这趟车次信息！ ,无法订退票！ ";
	}
	if (functionNumber == 2)
	{
		cout << " 输入你要订票或退票的车次： ";
		cin >> bus;
		cout << endl << endl;
		for (j = 0; j <= g_num; j++)
			if (strcmp(bus, ticket[j].bus) == 0)
			{
				cout << " 本车次现存信息 :" << endl;
				cout << " 车次 \t" << " 开车时间 \t" << " 起始 \t" << " 终点 \t" << " 票价 \t" << " 剩余座位 \t" << " 状态\t" << endl;
				ticket[j].display(); break;
			}
		if (j>g_num)
			cout << " 对不起，没有有关此站点的车次信息！无法订退票！ ";
	}
	if (ticket[j].time.hour<pt->tm_hour)
		cout << " 此班列车已发出 ,不能订退票！ ";
	else if (ticket[j].time.hour == pt->tm_hour&&ticket[j].time.minute <= pt->tm_min)
		cout << " 此班列车已发出 ,不能订退票！ ";
	else
	{
		cout << "\n";
		cout << " 1.订票 \n";
		cout << " 2.退票 \n";
		cout << " 3.返回主菜单 \n";
		cout << "\n";
		cout << " 选择你需要的功能 :";
		cin >> functionNumber;
		for (; functionNumber != 1 && functionNumber != 2 && functionNumber != 3;)
		{
			cout << " 指令错误！请重新输入！ " << endl;
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
	cout << " >>>>>> 查询子菜单 <<<<<< \n";
	cout << endl;
	cout << " 1.按班次查询 \n";
	cout << " 2.按站点查询 \n";
	cout << " 3.返回主菜单 \n";
	cout << endl;
	cout << " 请选择你所需要的功能 :";
	cin >> functionNumber;
	cout << endl << endl;
	for (; functionNumber != 1 && functionNumber != 2 && functionNumber != 3;)
	{
		cout << " 指令错误！请重新输入！ " << endl;
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
	cout << " >>>>>> 欢迎使用票务小管家 <<<<<< \n";
	cout << endl;
	cout << " 1.录入班次信息 \n";
	cout << " 2.删除班次信息\n";
	cout << " 3.修改车票信息\n";
	cout << " 4.浏览班次信息 \n";
	cout << " 5.查询行车路线 \n";
	cout << " 6.售票与退票 \n";
	cout << " 7.退出 \n";

	cout << endl;
	cout << " 请选择你所需要的功能 :";
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
				cout << " 已录入 " << g_num + 1 << " 条班次信息（包括已从文件中读取的） ，想继续录入吗(y / n)" << endl;
				cin >> c;
				for (; c != 'y'&&c != 'n';)
				{
					cout << " 指令错误！请重新输入！ " << endl;
					cin >> c;
				}
			} while (c == 'y');
		}
		else
			cout << " 对不起，您不是管理员不能进行这项操作！ ";
		cout << endl << " 按任意键回主菜单 ......" << endl;
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
			cout << " 对不起，您不是管理员不能进行这项操作！ ";

		}
		cout << endl << " 按任意键回主菜单 ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 4://浏览
	{
		browse();
		cout << endl << endl << endl << " 按任意键回主菜单 ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 5://查找
	{
		search_menu();
		cout << endl << " 按任意键回主菜单 ......" << endl;
		getchar();
		getchar();
		system("cls");
	}
	break;
	case 6:
	{
		ticketmenu();
		cout << endl << " 按任意键回主菜单 ......" << endl;
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
		cout << " >>>>>> 谢谢使用车票管理系统 <<<<<< \n";
		B = false;
	}
	break;
	case 3:
	{

		if (A)
			modifyTicket();
		else
			cout << "对不起，您不是管理员不能进行这项操作！";
		cout << endl << endl << endl << " 按任意键回主菜单 ......" << endl;
		getchar();
		getchar();
		system("cls");


	}
	break;

	default:
	{
		cout << " 输入错误 ,请确保你的输入为 1--6" << endl;
		cout << " 按任意键回主菜单 ......" << endl;
		getchar();
		system("cls");
	}
	}//switch ends
}
void sure_message()
{
	cout << " >>>>>> 欢迎使用票务小管家 <<<<<< \n"
		<< endl << endl;
	ifstream file(" 数据 .txt", ios::in);
	if (!file)
	{
		if (A)
		{
			cout << " 从没录入过信息 ,请您先录入信息 " << endl;
			input();
			cout << endl << " 按任意键回主菜单 ......" << endl;
			getchar();
			system("cls");
			mainmenu();
		}
		else cout << " 对不起，系统还没录入过任何信息 ,请提示管理员录入信息！ ";
	}
	else {
		cout << " 本次运行尚未录入信息，默认读取已存信息 \n";
		cout << " 按任意键读取 ......\n";
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
		file.close();//使用eof（）函数，读到文件结束标志EOF时并不会立刻返回ture，而是会读到他的下一个才返回。
		cout << " 读取完毕！ " << endl;
	}
}
void main()
{
	int functionNumber, code;
	cout << " 请输入您的身份（ 1.管理员， 2.乘客） " << endl;
	cout << " 您的身份 :";
	cin >> functionNumber;
	for (; functionNumber != 1 && functionNumber != 2;)
	{
		cout << " 指令错误！请重新输入！ " << endl;
		cin >> functionNumber;
	}
	if (functionNumber == 1)
	{
		cout << " 请输入密码： ";
		cin >> code;
		for (; code != 123;)
		{
			cout << " 指令错误！请重新输入！ " << endl;
			cin >> code;
		}
		A = true;
	}
	sure_message();
	do mainmenu();
	while (B);
}