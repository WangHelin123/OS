#include<bits/stdc++.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#define pb push_back
using namespace std;
int Mutex = 0;
vector<int> State;
vector<string> file_name_list;//�ǵ����ϵ�һ��
typedef struct memory_mode{
    string data="NULL";
    bool visit_for_clock_algorithm;
    bool if_free;
}memory_mode;
//�ڴ�ṹ��
//ʹ���ڴ�ǰ��Ҫ��ʼ��
//��Ҫʹ�ÿ��з������������
typedef struct table_item{
    //ҳ��ṹ��
    int page_id[64];
    map<int,int> logical_space_to_physical_space;
    void initial(){
         for(int i=0;i<=63;i++){
            page_id[i]=0;
         }
    }
}table_item;
typedef struct memory{
     memory_mode   memory_space[64];
     int mutex_of_memory=0;
     //ʹ���ڴ�ǰ��Ҫ��ʼ��
     void initial(){
       for(int i=0;i<=64;i++){
         memory_space[i].if_free=0;//0�Ļ���ʾ���ڴ�ռ���δ��ռ��
         memory_space[i].visit_for_clock_algorithm=0;
         mutex_of_memory=0;
        // memory_space[i].data="####";
       }
     }
     int get_number_of_free_memory(){
         int answer_of_get_number_of_free_memory=0;
         for(int i=0;i<64;i++){
            if(memory_space[i].if_free==0){
                answer_of_get_number_of_free_memory++;
            }
         }
         return answer_of_get_number_of_free_memory;
     }
}memory;
memory memory_of_use;//memory_of_use����Ϊȫ�ֱ���
table_item table_item_of_use;
int number_of_page=0;//��ǰҳ��
typedef struct clock_of_answer_algorithm{
      int data;
      int mark;
}clock_of_answer_algorithm;
clock_of_answer_algorithm answer_array_of_clock_algorithm[8];
//---------------------------------------------
void create();//��������
int addfile(string content);//�洢�ļ�
string selefile(int index);//��ѯ�ļ�
void deletefile(int index);//ɾ���ļ�
void clearall();//��մ���
int createtable();//����һ������
void showbitmap();//չʾλʾͼ
void addtable(int number,int index);//�����ڵĴ��̿�д����
//-----------------------------------------------
typedef struct UFD{
    string file_name;   //�ļ�����
    string file_length; //�ļ���С
    int file_locate;    //�ļ�������е�������
    string user_name;   //�������û���
    string create_time; //����ʱ��
    bool is_open;   //�Ƿ�����ڴ�-----�������ڴ��޷�ɾ���ļ�
}UFD;
typedef list<UFD> UFD_LIST; //�û��ļ�Ŀ¼�б�
typedef struct MFD{
    string user_name;   //�û�������
    UFD_LIST UFD_point;     //ָ����û��ļ�Ŀ¼��ָ��
}MFD;
typedef list<MFD> MFD_LIST; //���ļ��б�
UFD_LIST  null_list;
string root_account = " ";
string root_password = " ";
string text = "";
bool state = true; //��ǰ��¼״̬��trueΪroot�û���falseΪuser�û�
string now_user_name = "root";
MFD_LIST::iterator now_UFD_list_it;
//------------------------------------------------------------------
void gotoxy(int x, int y);    //�����ת
void gotoprint(int x, int y); //��ӡ
void ClickControl();          //��ȡ�����ź�
void printframe();            //��ӡ�߿�
void autocls(int xxx);        //�Զ�����
void window1(MFD_LIST &MFD_list, UFD_LIST &UFD_lsit);               //�û���¼����
char click='0';
int xx=1,yy=1;
//----------------------------------------------------------
typedef struct thread{
    int thread_space[8];
    string data="NULL";
    void initial(){
        for(int i=0;i<8;i++){
            thread_space[i]=-1;
            //��ʼ����¸��̲߳�ռ���ڴ��,���ռ�õĿռ���-1
            //�ڱ�����ǵ��߳�ռ�õĿռ�ֱ��ָ�����ڴ���
        }
    }
    void allocate_memory_of_thread_memory(){
  //���̷߳����ڴ�麯��
  //�˺�����ʹ��ǰ��Ҫ��֤ʣ�µĿռ��Ƿ���
     int key=0;
     for(int i=0;i<64;i++){
        if(memory_of_use.memory_space[i].if_free==0){
            memory_of_use.memory_space[i].if_free=1;
            thread_space[key]=i;
            key++;
            if(key==8) break;
        }
     }
   }
}thread_of_me;
void clock_of_algorithm(int n);
void refresh();
int index = 0;
typedef struct task{
    int task_space[8];
    string data;
    void initial(){
        for(int i=0;i<8;i++){
            task_space[i]=-1;
            //��ʼ����¸�����ռ���ڴ��,���ռ�õĿռ���-1
            //����������е�����ָ����ҳ��
        }
    }
	 void allocate_memory_of_data_memory(int num){
	         //����������ݷ����ڴ�麯��
	         //�˺�����ʹ��ǰ��Ҫ��֤ʣ��Ŀռ��Ƿ���
	           int key=0;
	           string s_answer[8 * num];
	           if(num == 1)
	           {
					for(int i=0;i<data.size();i++){
					if(i>=0&&i<4) s_answer[0]+=data[i];
					else if(i>=4&&i<8) s_answer[1]+=data[i];
					else if(i>=8&&i<12) s_answer[2]+=data[i];
					else if(i>=12&&i<16) s_answer[3]+=data[i];
					else if(i>=16&&i<20) s_answer[4]+=data[i];
					else if(i>=20&&i<24) s_answer[5]+=data[i];
					else if(i>=24&&i<28) s_answer[6]+=data[i];
					else if(i>=28&&i<32) s_answer[7]+=data[i];
					}
			   }

			   else if(num == 2)
	           {
	           		int cnt = 0;
	           		if(data.length() == 16)
					{
						int sequence[3][16] = {{0,1,2,3,8,9,10,11,4,5,6,7,12,13,14,15}
					,{8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7}, {8,9,10,11,0,1,2,3,12,13,14,15,4,5,6,7}};
						srand(unsigned(time(NULL)));
						int i = rand() % 3;
						for(int j = 0; j < 4; j ++)
						    for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
					}
					else if(data.length() == 8)
					{
						int sequence[2][8] ={{0,1,2,3,4,5,6,7}, {4,5,6,7,0,1,2,3}};
						srand(unsigned(time(NULL)));
						int i = rand() % 2;
						for(int j = 0; j < 2; j ++)
							for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
					}
					else if(data.length() == 6)
					{
						int sequence[2][6] = {{4,5,0,1,2,3}, {0,1,2,3,4,5}};
						srand(unsigned(time(NULL)));
						int i = rand() % 2;
						if(i == 1)
						{
							for(int k = 0; k < 4; k ++)s_answer[0] += data[sequence[i][cnt ++]];
							for(int m = 0; m < 2; m ++)s_answer[1] += data[sequence[i][cnt ++]];
						}
						else if(i == 0)
						{
							for(int m = 0; m < 2; m ++)s_answer[0] += data[sequence[i][cnt ++]];
							for(int k = 0; k < 4; k ++)s_answer[1] += data[sequence[i][cnt ++]];
						}
					}
	           }

			   else if(num == 3)
	           {
	           		if(data.length() == 24)
	           		{
	           			int cnt = 0;
	           			int sequence[3][24] =
	           		{
					   	{0,1,2,3,8,9,10,11,16,17,18,19,4,5,6,7,12,13,14,15,20,21,22,23},
					   	{8,9,10,11,16,17,18,19,0,1,2,3,4,5,6,7,12,13,14,15,20,21,22,23},
					   	{16,17,18,19,0,1,2,3,8,9,10,11,4,5,6,7,20,21,22,23,12,13,14,15}
					};
					srand(unsigned(time(NULL)));
					int i = rand() % 3;
					for(int j = 0; j < 6; j ++)
						for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
	           		}
	           		else if(data.length() == 12)
	           		{
						int cnt = 0;
						int sequence[3][12] =
	           			{
							{0,1,2,3,8,9,10,11,4,5,6,7},
							{4,5,6,7,8,9,10,11,0,1,2,3},
							{8,9,10,11,4,5,6,7,0,1,2,3}
						};
						srand(unsigned(time(NULL)));
						int i = rand() % 3;
						for(int j = 0; j < 3; j ++)
							for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
					}
					else if(data.length() == 10)
					{
						int cnt = 0;
						int sequence[2][10] =
						{
							{0,1,2,3,8,9,4,5,6,7},
							{4,5,6,7,0,1,2,3,8,9}
						};
						srand(unsigned(time(NULL)));
						int i = rand() % 2;
						if(i == 0)
						{
							for(int k = 0; k < 4; k ++)s_answer[0] += data[sequence[i][cnt ++]];
							for(int k = 0; k < 2; k ++)s_answer[1] += data[sequence[i][cnt ++]];
							for(int k = 0; k < 4; k ++)s_answer[2] += data[sequence[i][cnt ++]];
						}
						else if(i == 1)
						{
							for(int j = 0; j < 2; j ++)
								for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
							for(int m = 0; m < 2; m ++)s_answer[2] += data[sequence[i][cnt ++]];
						}
					}
			   }

			   else if(num == 4)
			   {
			   		if(data.length() == 32)
			   		{
			   			int cnt = 0;
			   			int sequence[4][32] =
					{
						{0,1,2,3,16,17,18,19,24,25,26,27,8,9,10,11,4,5,6,7,12,13,14,15,28,29,30,31,20,21,22,23},
						{8,9,10,11,16,17,18,19,24,25,26,27,0,1,2,3,4,5,6,7,12,13,14,15,20,21,22,23,28,29,30,31},
						{16,17,18,19,24,25,26,27,0,1,2,3,8,9,10,11,12,13,14,15,4,5,6,7,28,29,30,31,20,21,22,23},
						{24,25,26,27,8,9,10,11,0,1,2,3,16,17,18,19,4,5,6,7,28,29,30,31,20,21,22,23,12,13,14,15}
					};
						srand(unsigned(time(NULL)));
						int i = rand() % 4;
					for(int j = 0; j < 8; j ++)
						for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
			   		}
			   		else if(data.length() == 16)
			   		{
						int cnt = 0;
						int sequence[4][16] =
						{
							{0,1,2,3,8,9,10,11,4,5,6,7,12,13,14,15},
							{4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11},
							{8,9,10,11,4,5,6,7,0,1,2,3,12,13,14,15},
							{12,13,14,15,0,1,2,3,8,9,10,11,4,5,6,7}
						};
						srand(unsigned(time(NULL)));
						int i = rand() % 4;
						for(int j = 0; j < 4; j ++)
							for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
					}
					else if(data.length() == 14)
					{
						int cnt = 0;
						int sequence[4][14] =
						{
							{4,5,6,7,0,1,2,3,12,13,8,9,10,11},
							{12,13,0,1,2,3,8,9,10,11,4,5,6,7}
						};
						srand(unsigned(time(NULL)));
						int i = rand() % 2;
						if(i == 0)
						{
							for(int j = 0; j < 2; j ++)
								for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
							for(int m = 0; m < 2; m ++)s_answer[2] += data[sequence[i][cnt ++]];
							for(int m = 0; m < 4; m ++)s_answer[3] += data[sequence[i][cnt ++]];
						}
						else if(i == 1)
						{
							for(int m = 0; m < 2; m ++)s_answer[0] += data[sequence[i][cnt ++]];
							for(int j = 1; j < 4; j ++)
								for(int k = 0; k < 4; k ++)s_answer[j] += data[sequence[i][cnt ++]];
						}
					}
			   }
	           	for(int i=0;i<64;i++){
	           	  if(memory_of_use.memory_space[i].if_free==0){
	                 memory_of_use.memory_space[i].if_free=1;
	                 memory_of_use.memory_space[i].data=s_answer[key];
	                 refresh();
	                 Sleep(1000);
	                 table_item_of_use.page_id[number_of_page]=i;
	                 task_space[key]=number_of_page;
	                 number_of_page++;
	                 key ++;
	                 if(key==8*num) break;
	             }
	           }
	       }
    void recycle_memory_of_data_memory(int num){
        for(int i=0;i<8*num;i++){
            memory_of_use.memory_space[task_space[i]].data="NULL";
            memory_of_use.memory_space[task_space[i]].if_free=0;
        }
    }
}task;
bool find_empty_management_memory(){
     //�����ڴ�����
     int key=8;
     for(int i=0;i<64;i++){
        if(memory_of_use.memory_space[i].if_free==0){
            key--;
            if(key==0) return true;
        }
     }
     return false;
}
bool read_data_of_disk_memory(task &input_task, int num){
     //�Ӵ����ж������ݵ��ڴ���
     if(memory_of_use.get_number_of_free_memory()>=8){//������е��ڴ�ռ����8�Ļ�,�����
        string waiting_for_processing_data=input_task.data;
        if(waiting_for_processing_data.size()<=32){
             input_task.allocate_memory_of_data_memory(num);
         }
        else{
                //cout<<"�����˸��ڴ����"<<endl;
                int clock_i[8];
                int key=0;
                for(int i=0;i<64;i++){
                    if(memory_of_use.memory_space[i].if_free==0){
                     memory_of_use.memory_space[i].if_free=1;
                     memory_of_use.memory_space[i].visit_for_clock_algorithm=1;
                     clock_i[key]=i;
                     key++;
                     if(key>=8) break;
                  }
               }
               //������Ϊ������װ���ڴ�
               int now_number=0;
               int waiting_for_processing_data_page;
               if(waiting_for_processing_data.size()%4!=0){
                     waiting_for_processing_data_page=(waiting_for_processing_data.size()/4)+1;
               }
               else{
                     waiting_for_processing_data_page=waiting_for_processing_data.size()/4;
               }
               clock_of_algorithm(waiting_for_processing_data_page);
               //answer_array_of_clock_algorithm[0].data;
               for(int i=0;i<8;i++){
                  string temp_s="";
                  for(int j=answer_array_of_clock_algorithm[i].data*4;j<(answer_array_of_clock_algorithm[i].data*4)+4;j++){
                      temp_s+=input_task.data[j];
                      if(j>=input_task.data.size()) break;
                  }
                  memory_of_use.memory_space[clock_i[i]].data=temp_s;
                  input_task.task_space[i]=clock_i[i];
                  refresh();
                  Sleep(3000);
              }
       }
       return true;
     }
     else {
         cout<<memory_of_use.get_number_of_free_memory()<<endl;
         cout<<"�ڴ�ռ䲻��"<<endl;
         return false;//�ڴ�ռ�С��8�Ļ�,�򲻷���
    }
}

void clock_of_algorithm(int n){
       int  now_count=0;
       for(int i=0;i<8;i++){
           answer_array_of_clock_algorithm[i].mark=1;
           answer_array_of_clock_algorithm[i].data=i;
           //ҳ���0��ʼ
           //���ȫ�ֱ��������Ժ�ǧ��Ҫ����,��Ȼ�������
       }
       int  now_data=8;
       while(1){
           if(answer_array_of_clock_algorithm[now_count].mark==1){
              answer_array_of_clock_algorithm[now_count].mark=0;
              now_count=(now_count+1)%8;
           }
           else{
               answer_array_of_clock_algorithm[now_count].mark=1;
               answer_array_of_clock_algorithm[now_count].data=now_data;
               now_data++;
               now_count=(now_count+1)%8;
               if(now_data==n)break;
           }
       }
}
void refresh(){
    int key=1,tempp=0;
    yy=5;
    gotoxy(130,3);
    cout<<"--�ڴ�������---";
    for(int i=0;i<64;i++){
        gotoxy(100+(tempp%80),yy);
        tempp+=20;
        if(tempp%80==0)yy++;

           cout<<right<<setw(6)<<"<"<<i<<","<<memory_of_use.memory_space[i].data<<">;";

        key++;
        cout<<"    ";
    }
}
//----------------------------------------------------------
struct Disk{
    char memory[1024][4];//�洢ʱһ���ַ�ռ4KB�洢�ռ�
};
struct swaps{
    char memory[124][4];
};
struct data{
    char momery[900][4];
};
struct disktable{
    int table1[1024];//һ������ ��Ÿ��ļ���ʹ�õ�����
    int index1,now1=0;
}tabtab[1024];
struct disktable2{
    int table2[1024];
    int now2=0;
}tabtab2[10][1024];
bool bitmap[33][33];
int tableindex=0;
struct Disk* disk;
//----------------------------------------------
void create_user(string user_name, bool creat_UFD, MFD_LIST &MFD_list){//�����û����������û�Ŀ¼
    if(state){
        MFD temp_MFD;
        temp_MFD.user_name = user_name;
        if(creat_UFD){//�û�ͬ�ⴴ��UFD
            UFD temp_UFD;
            temp_UFD.create_time = "";
            temp_UFD.file_length = "-1";
            temp_UFD.file_locate = -1;
            temp_UFD.file_name = "";
            temp_UFD.is_open = false;
            temp_UFD.user_name = "";
            UFD_LIST temp_UFD_list;
            temp_UFD_list.push_back(temp_UFD);
            temp_MFD.UFD_point = temp_UFD_list;
        }
        else{//�û���ͬ�ⴴ��UFD

            temp_MFD.UFD_point = null_list;
        }
        MFD_list.push_back(temp_MFD);
        now_UFD_list_it = MFD_list.begin();
    }
    else{
    	gotoxy(2,xx++);
    	autocls(xx);
        cout<<"ERROR����ǰ��¼״̬����root״̬�����������û�";
    }
}
void delete_user(string user_name, MFD_LIST &MFD_list){//ɾ���û���ͬʱɾ���û�Ŀ¼
    if(state){
        for(auto it = MFD_list.begin(); it != MFD_list.end(); it++){
            if(it->user_name == user_name){
                if((it->UFD_point).size() == 1){
                    MFD_list.erase(it);
                    break;
                }
                else{
                    gotoxy(2,xx++);
                    autocls(xx);
                    cout<<"��ǰĿ¼�����ļ�ɾ��ʧ��"<<endl;
                }
            }
        }
    }
    else{
    	gotoxy(2,xx++);
    	autocls(xx);
        cout<<"ERROR����ǰ��¼״̬����root״̬��������ɾ���û�";
    }
}
MFD_LIST::iterator cd_user(string user_name, MFD_LIST &MFD_list){//�����û�Ŀ¼�ļ�
    for(MFD_LIST::iterator it = MFD_list.begin(); it != MFD_list.end(); it++){
        if(it->user_name == user_name){
            now_user_name = it->user_name;
            state = false;
            return it;
        }
    }
    MFD_LIST::iterator iter;
    iter = MFD_list.end();
    return iter;
}
bool get_root(string password){
	gotoxy(2,xx++);
	autocls(xx);
    cout<<"������root����"<<endl;
    cin>>password;
    if(password == root_password){
        return true;
    }
    else    return false;
}

void create_file(string file_context, string file_name, MFD_LIST &MFD_list, string user_name = now_user_name){
    if(state){
        now_UFD_list_it = cd_user(user_name,MFD_list);
        if(now_UFD_list_it == MFD_list.end()){
        	gotoxy(2,xx++);
        	autocls(xx);
            cout<<"ERROR! δ�ҵ����û�����û��޷������ļ�";
        }
        else{
            UFD temp_UFD;
            time_t now = time(0);
            char* dt = ctime(&now);
            temp_UFD.create_time = dt;
            dt[strlen(dt)-1]='\0';
            temp_UFD.file_length = to_string(file_context.size());
            temp_UFD.file_locate = addfile(file_context);
            cout<<temp_UFD.file_locate;
            temp_UFD.file_name = file_name;
            temp_UFD.is_open = 0;
            temp_UFD.user_name = user_name;
            (now_UFD_list_it->UFD_point).push_back(temp_UFD);
        }
    }
    else{
        UFD temp_UFD;
        time_t now = time(0);
        char* dt = ctime(&now);
        dt[strlen(dt)-1]='\0';
        temp_UFD.create_time = dt;
        temp_UFD.file_length = to_string(file_context.size());
        temp_UFD.file_locate = addfile(file_context);
        temp_UFD.file_name = file_name;
        temp_UFD.is_open = 0;
        temp_UFD.user_name = user_name;
        (now_UFD_list_it->UFD_point).push_back(temp_UFD);
    }

}
void delete_file(string file_name, MFD_LIST &MFD_list, string user_name=now_user_name){
    if(state){
        now_UFD_list_it=cd_user(user_name,MFD_list);
        if(now_UFD_list_it == MFD_list.end()){
        	gotoxy(2,xx++);
        	autocls(xx);
            cout<<"ERROR! δ�ҵ����û�";
        }
        else{
            for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
                if(it->file_name == file_name && it->is_open == false){
                    deletefile(it->file_locate);
                    (now_UFD_list_it->UFD_point).erase(it);
                    break;
                }
                else if(it->is_open == true){
                    gotoxy(2,xx++);
                    autocls(xx);
					cout<<"���ļ����ڱ���ȡ���޷�ɾ��";
					break;
				}
            }
        }
    }
    else{
        for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
            if(it->file_name == file_name && it->is_open == false){
                deletefile(it->file_locate);
                (now_UFD_list_it->UFD_point).erase(it);
                break;
            }
            else if(it->is_open == true){
                gotoxy(2,xx++);
                autocls(xx);
				cout<<"���ļ����ڱ���ȡ���޷�ɾ��"<<endl;
				break;
			}
        }
    }
}
int get_file_locate(string file_name,MFD_LIST MFD_list, string user_name=now_user_name){
    if(state){
        now_UFD_list_it=cd_user(user_name,MFD_list);
        if(now_UFD_list_it == MFD_list.end()){
        	gotoxy(2,xx++);
        	autocls(xx);
            cout<<"ERROR! δ�ҵ����û�";
        }
        else{
            for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
                if(it->file_name == file_name){
                    return it->file_locate;
                }
            }

        }

    }
    else{
          for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
            if(it->file_name == file_name){
                return it->file_locate;
            }
        }

    }
    return -1;
}

MFD_LIST::iterator cd_exit(MFD_LIST &MFD_list){
    MFD_LIST::iterator it;
    it = MFD_list.begin();
    now_user_name = "root";
    state = true;
    return it;
}

void show_MFD_Info(MFD_LIST &MFD_list){
	gotoxy(2,xx++);
	autocls(xx);
    cout<<"��ǰ����Ա�û�Ŀ¼״̬:"<<endl;
    for(auto it = MFD_list.begin(); it != MFD_list.end(); it++){
    	gotoxy(2,xx++);
    	autocls(xx);
        cout<<it->user_name<<endl;
        auto iter = (it->UFD_point).begin();
        iter++;
        for(iter; iter != (it->UFD_point).end(); iter++){
        	gotoxy(2,xx++);
        	autocls(xx);
            cout<<"---->"<<iter->file_name<<endl;
        }
    }
}

void show_UFD_Info(){
	auto it = (now_UFD_list_it->UFD_point).begin();
	it++;
	gotoxy(2,xx++);
	autocls(xx);
	cout<<setw(15)<<"�ļ�����"<<setw(15)<<"�ļ���С"<<setw(15)<<"������"<<setw(15)<<"�����û���"<<setw(28)<<"����ʱ��"<<endl;
    for(it; it != (now_UFD_list_it->UFD_point).end(); it++){
    	gotoxy(2,xx++);
    	autocls(xx);
       	cout<<setw(15)<<it->file_name<<setw(15)<<it->file_length<<setw(15)<<it->file_locate<<setw(15)<<it->user_name<<setw(30)<<it->create_time<<endl;
	}
}


string get_file_string(string file_name, MFD_LIST MFD_list, string user_name=now_user_name){
    if(state){
        now_UFD_list_it=cd_user(user_name,MFD_list);
        if(now_UFD_list_it == MFD_list.end()){
            cout<<"ERROR! δ�ҵ����û�";
        }
        else{
            for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
                if(it->file_name == file_name){
                	it->is_open = true;
                    return selefile(it->file_locate);
                }
            }

        }

    }
    else{
          for(UFD_LIST::iterator it = (now_UFD_list_it->UFD_point).begin(); it != (now_UFD_list_it->UFD_point).end(); it++){
            if(it->file_name == file_name){
            	it->is_open = true;
                return selefile(it->file_locate);
            }
        }

    }
    return "ERROR";
}

string stora_dic(MFD_LIST MFD_list){
    MFD_LIST :: iterator it = MFD_list.begin();
    while(it != MFD_list.end()){
        text = text + it->user_name;
        text = text + ":";
        UFD_LIST::iterator iter = (it->UFD_point).begin();
        if(iter != null_list.begin()){
            text= text + "1";
            iter++;
            while(iter != (it->UFD_point).end()){
                //it->file_name<<setw(15)<<it->file_length<<setw(15)<<it->file_locate<<setw(15)<<it->user_name<<setw(30)<<it->create_time<<endl;
                text = text + iter->file_name;
                text = text + "/";
                text = text + iter->file_length + "/" + to_string(iter->file_locate) + "/" + iter->user_name + "/" + iter->create_time + "#";
                iter++;
            }
            text = text + "*";
        }
        else{
            text = text + "0";
            text = text + "*";
        }
        it++;
    }

    return text;
}
void load_create_file(string file_name, MFD_LIST &MFD_list, string user_name, string file_length, int file_locate, string create_time){
    if(state){
        now_UFD_list_it = cd_user(user_name,MFD_list);
        if(now_UFD_list_it == MFD_list.end()){
        	gotoxy(2,xx++);
        	autocls(xx);
            cout<<"ERROR! δ�ҵ����û�����û��޷������ļ�";
        }
        else{
            UFD temp_UFD;
            temp_UFD.create_time = create_time;
            temp_UFD.file_length = file_length;
            temp_UFD.file_locate = file_locate;
            cout<<temp_UFD.file_locate;
            temp_UFD.file_name = file_name;
            temp_UFD.is_open = 0;
            temp_UFD.user_name = user_name;
            (now_UFD_list_it->UFD_point).push_back(temp_UFD);
        }
    }
    else{
        UFD temp_UFD;
        temp_UFD.create_time = create_time;
        temp_UFD.file_length = file_length;
        temp_UFD.file_locate = file_locate;
        temp_UFD.file_name = file_name;
        temp_UFD.is_open = 0;
        temp_UFD.user_name = user_name;
        (now_UFD_list_it->UFD_point).push_back(temp_UFD);
    }

}

void load_dic(string text, MFD_LIST &MFD_list){
    //create_file(string file_context, string file_name, MFD_LIST &MFD_list, string user_name = now_user_name)
    //create_user(string user_name, bool creat_UFD, MFD_LIST &MFD_list)
    string temp = "";
    string user_name = "";
    int i = 0;
    while(i < text.length()){
        if(text[i] == ':'){
            user_name = temp;
            i = i + 1;
            bool creat_UFD = text[i] - 48;
            create_user(user_name,creat_UFD,MFD_list);
            i = i + 1;
            temp = "";
            while(text[i] != '*'){
                while(text[i] != '/'){
                    temp = temp + text[i];
                    i++;
                }
                string file_name = temp;
                temp = "";
                i = i + 1;
                while(text[i] != '/'){
                    temp = temp + text[i];
                    i++;
                }
                string file_length = temp;
                temp = "";
                i = i + 1;
                int file_locate = text[i] - 48;
                i = i + 2;
                while(text[i]!= '/'){
                    temp = temp + text[i];
                    i++;
                }
                string user_name = temp;
                temp = "";
                i= i+1;
                while(text[i] != '#'){
                    temp = temp + text[i];
                    i++;
                }
                string create_time = temp;
                temp = "";
                load_create_file(file_name,MFD_list,user_name,file_length,file_locate,create_time);
                i++;
            }
            now_UFD_list_it = cd_exit(MFD_list);
            i++;
        }
        else{
            while(text[i] != ':'){
                temp = temp + text[i];
                i++;
            }
        }
    }
}

void clear_dic(MFD_LIST &MFD_list){
    MFD_list.clear();
    now_UFD_list_it = MFD_list.begin();
}

//----------------------------------------------
void create(){
     disk = (Disk*) malloc(sizeof(Disk));
}
void clearall(){
    memset(bitmap,0,sizeof(bitmap));
    memset(disk->memory,0,sizeof(disk->memory));
}
int addfile(string content){
	int i,j;
    int point=0;
    int index=createtable();
    int num=floor(content.size()/4+2)-1,numm=0;
    for(i=1;i<=10;i++){
    	for(j=1;j<=32;j++){
    		if(bitmap[i][j]==0)
    			numm++;
    		else
    			numm=0;
    		if(numm==num)break;
		}
		if(numm==num) break;
	}
    while(point<content.size()){
        for(;i<=10;i++){
            for(j=j-num+1;j<=32;j++){
                if(bitmap[i][j]==0){
                    bitmap[i][j]=1;
                    addtable((i-1)*32+(j-1),index);
                    for(int k=0;k<4;k++){
                        disk->memory[(i-1)*32+(j-1)][k]=content[point];
                        point++;
                        if(point==content.size()){
                            showbitmap();
                            return index;
                        }
                    }
                }
            }
        }
    }
    showbitmap();
    return index;
}
int createtable(){
    tabtab[tableindex].now1=0;
    return tableindex++;
}
void addtable(int number,int index){
    int index2=tabtab[index].now1;
    tabtab2[index][index2].table2[tabtab2[index][index2].now2++]=number;
    if(tabtab2[index][index2].now2==1024){
        tabtab[index].now1++;
    }
    if(tabtab[index].now1==1024){
            cout<<"�������ˣ�������"<<endl;
    }
}
string selefile(int index){
    string s="";
    int k=0;
    while(k<=tabtab[index].now1){
        int kk=0;
        while(kk<tabtab2[index][k].now2){
            int temp=tabtab2[index][k].table2[kk];
            for(int i=0;i<4;i++)
                s+=disk->memory[temp][i];
            kk++;
        }
        k++;
    }
    return s;
}
void deletefile(int index){
    int k=0;
    while(k<=tabtab[index].now1){
        int kk=0;
        while(kk<tabtab2[index][k].now2){
            int temp=tabtab2[index][k].table2[kk];
            int hang=(temp/32)+1;
            int lie=temp-(hang-1)*32+1;
            bitmap[hang][lie]=0;
            for(int i=0;i<4;i++)
            disk->memory[temp][i]=0;
            kk++;
        }
        k++;
    }
    showbitmap();
}
void showbitmap(){
	gotoxy(35,28);
	cout<<"--------λʾͼ--------" ;
	gotoxy(0,30);
    for(int i=0;i<=32;i++)
        cout<<setw(2)<<i<<" ";
    cout<<endl;
    for(int i=1;i<=32;i++){
        cout<<setw(2)<<i<<" ";
        for(int j=1;j<=32;j++){
            cout<<setw(2)<<bitmap[i][j]<<" ";
        }
        cout<<endl;
    }
}
void storebitmap(){
    string suoyin="";
    suoyin+=char(tableindex+'0');
    suoyin+=',';
    for(int i=0;i<tableindex;i++){
        suoyin+=char(tabtab2[i][0].now2+'0');
        suoyin+=',';
        for(int j=0;j<tabtab2[i][0].now2;j++){;
            suoyin+=char(tabtab2[i][0].table2[j]+'0');
            suoyin+=',';
        }
    }
    for(int j=0;j<=32;j++)
        bitmap[4][j]=0;
    int indexx=0;
    for(int j=1;j<=suoyin.size();j++){
            bitmap[4][j]=1;
            for(int k=0;k<4;k++){
                disk->memory[(4-1)*32+(j-1)][k]=suoyin[indexx++];
                if(indexx==suoyin.size())
                    break;
            }
            if(indexx==suoyin.size())
                break;
    }
        ofstream out("disk.txt",ios::out);
    for(int i=1;i<=32;i++){
        for(int j=1;j<=32;j++){
            if(bitmap[i][j]){
                for(int k=0;k<4;k++){
                    out<<disk->memory[(i-1)*32+(j-1)][k];
                }
                out<<" ";
            }
            else
                out<<"#### ";
        }
        out<<endl;
    }
}
void loadbitmap(){
    ifstream in ("disk.txt",ios::in);
	string ss;
    for(int i=1;i<=32;i++){
        for(int j=1;j<=32;j++){
            in>>ss;
            if(ss[0]!='#'){
                for(int k=0;k<4;k++){
                    disk->memory[(i-1)*32+(j-1)][k]=ss[k];
                }
                bitmap[i][j]=1;
            }
            else{
                bitmap[i][j]=0;
            }

        }
    }
    int indexx=0,iindex=0;
    indexx=(4-1)*32+(1-1);
    tableindex=int(disk->memory[indexx][iindex++]-'0');
    iindex++;
    for(int i=0;i<tableindex;i++){
        tabtab2[i][0].now2=int(disk->memory[indexx][iindex++]-'0');
        if(disk->memory[indexx][iindex]==',')
            iindex++;
        indexx+=(iindex/4);
        iindex=iindex%4;
        for(int j=0;j<tabtab2[i][0].now2;j++){
            tabtab2[i][0].table2[j]=int(disk->memory[indexx][iindex++]-'0');
            if(disk->memory[indexx][iindex]==',')
                iindex++;
            indexx+=(iindex/4);
            iindex=iindex%4;
        }
    }

}
int addstorefile(string content){//�ļ���
    int point=0;
    int index;
    index=createtable();
    while(point<content.size()){
        for(int i=3;i<=32;i++){
            for(int j=1;j<=32;j++){
                if(bitmap[i][j]==0){
                    bitmap[i][j]=1;
                    addtable((i-1)*32+(j-1),index);
                    for(int k=0;k<4;k++){
                        disk->memory[(i-1)*32+(j-1)][k]=content[point];
                        point++;
                        if(point==content.size()){
                            return index;
                        }
                    }
                }
            }
        }
    }
    showbitmap();
    return index;
}
void storemulu(string s){
    addstorefile(s);

}
string loadmulu(){
    string s=selefile(tableindex-1);
    deletefile(tableindex-1);
    return s;
}
//------------------------------------------------
void gotoxy(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	ofstream outfile;
    outfile.open("getkey.txt",ios::in|ios::out);
	SetConsoleCursorPosition(hOutput, pos);
}
void gotoprint(int x, int y)
{
	gotoxy(x, y);
	printf("��");
}
void ClickControl()
{
    char c;
    while(1)
    {
        if (_kbhit())
		{
            system("cls");
			click = _getch();
		}
    }
}
void printframe(){
    int i;
	for (i = 0; i<100; i += 2)//��ӡ���±߿�
	{
		gotoprint(i, 0);
		gotoprint(i, 26);
	}
	for (i = 1; i < 26; i++)
	{
		gotoprint(0, i);
		gotoprint(98, i);
	}
}

void autocls(int xxx){
	if(xxx==26){
		xx=1;
	    system("cls");
		showbitmap();
	    printframe();
	    gotoxy(2,xx++);
	}
}
void window1(MFD_LIST &MFD_list, UFD_LIST &UFD_list)
{

    task task_on_work;
    string s = "";
    int MemorySize;
    printframe();
    gotoxy(20, 11);
    cout<<"��ӭʹ��os";
    char x;
    x=getchar();
    system("cls");
    printframe();
    int num,key;
	gotoxy(3,8);
	printf("���ȵ�½�˻�");
	gotoxy(5,10);
	printf("���������Ա�ʺ�:");
	scanf("%d",&num);
	gotoxy(5,12);
	printf("���������Ա����:");
    cin>>key;
    system("cls");
    showbitmap();
    printframe();
    gotoxy(2,xx++);
    autocls(xx);
    cout<<"root #:";
    while(1){
        string ss;
        cin>>ss;
        if(ss== "mkdir"){
            string user_name;
            int flag;
            cin>>user_name;
            cin>>flag;
            create_user(user_name,flag,MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
        }
        else if(ss == "cd"){
            string user_name;
            cin>>user_name;
            now_UFD_list_it = cd_user(user_name,MFD_list);
            gotoxy(2,xx ++);
            autocls(xx);
           cout<<"root/"<<now_user_name<<" $:";
        }
        else if(ss == "ls"){
            show_MFD_Info(MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
        }
        else if(ss == "touch"){
            string all;
            int i;
            string user_name = "";
            string file_name = "";
            string file_context;
            getline(cin,all);
            for(i = 1; i < all.length(); i++){
                if(all[i] != ' '){
                    file_name += all[i];
                }
                else break;
            }
            for(i = i + 1; i < all.length(); i++){
                user_name += all[i];
            }
            //xx=1;
            //system("cls");
            printframe();
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"�������ļ����ݣ�";
            cin>>file_context;
            if(user_name == ""){
                create_file(file_context,file_name,MFD_list);
            }
            else{
                create_file(file_context,file_name,MFD_list,user_name);
            }
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root/"<<now_user_name<<" $:";
        }
        else if(ss == "rmdir"){
            string user_name;
            cin>>user_name;
            delete_user(user_name,MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
        }
        else if(ss == "rm"){
            string all;
            int i;
            string user_name = "";
            string file_name = "";
            getline(cin,all);
            for(i = 1; i < all.length(); i++){
                if(all[i] != ' '){
                    file_name += all[i];
                }
                else break;
            }
            for(i = i + 1; i < all.length(); i++){
                user_name += all[i];
            }
            if(user_name == ""){
                delete_file(file_name,MFD_list);
            }
            else{
                delete_file(file_name,MFD_list,user_name);
            }
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root/"<<now_user_name<<" $:";
        }
        else if(ss=="cd.."){
            now_UFD_list_it = cd_exit(MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
             cout<<"root #:";
        }
        else if(ss=="lsuser"){
			show_UFD_Info();
			gotoxy(2,xx++);
			autocls(xx);
			cout<<"root/"<<now_user_name<<" $:";
		}
		else if(ss=="cls"){
			system("cls");
			xx=1;
			gotoxy(2,xx++);
			autocls(xx);
			cout<<"root #:";
		}
		else if(ss=="shutdown"){
            storemulu(text);
        storebitmap();
			break;
		}
		else if(ss == "read")
		{
		    gotoxy(2,xx++);
			cout << "������Ҫ��ȡ���ļ���:" << '\n';
			gotoxy(2,xx++);
			cin >> num;
			for(int i = 0; i < num; i ++)State.pb(0);
			for(int i = 0; i < num; i ++)
			{
				string filename;
				string filecontext;
				gotoxy(2,xx++);
                autocls(xx);
				cout << "������Ҫ��ȡ���ļ���:" << '\n';
                gotoxy(2,xx++);
                autocls(xx);
				cin >> filename;
				file_name_list.push_back(filename);
				filecontext = get_file_string(filename, MFD_list);
				s += filecontext;
				MemorySize = s.length() / 4;
				//cout << filecontext << '\n';
			}
			if(Mutex == 0)
			{
				Mutex = 1;
				task_on_work.initial();
				task_on_work.data = s;
				read_data_of_disk_memory(task_on_work, num);
				for(int i = 0; i < MemorySize; i ++)bitmap[1][i + 1] = 0;
				showbitmap();
				gotoxy(2,xx);
				Mutex = 0;
				State.clear();
			}
			gotoxy(2,xx++);
			autocls(xx);
			cout<<"root/"<<now_user_name<<" $:";
		}
		else if(ss == "close"){
            task_on_work.recycle_memory_of_data_memory(num);
            for(int i = 0; i< file_name_list.size();i++){
                for(MFD_LIST :: iterator  it = MFD_list.begin(); it != MFD_list.end(); it++){
                    UFD_LIST::iterator iter = (it->UFD_point).begin();
                    iter++;
                    for(iter; iter != (it->UFD_point).end(); iter++){
                        if(iter->file_name == file_name_list[i]){
                            iter->is_open = false;
                        }
                    }
                }

            }                for(int i = 0; i < MemorySize; i ++)bitmap[1][i + 1] = 1;
                showbitmap();
            refresh();
            gotoxy(2,xx++);
			autocls(xx);
			cout<<"root/"<<now_user_name<<" $:";
			file_name_list.clear();
        }
        else if(ss == "stora"){
            text = stora_dic(MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
		}
		else if(ss == "clear"){
            clear_dic(MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
		}
		else if(ss == "load"){
            load_dic(loadmulu(),MFD_list);
            gotoxy(2,xx++);
            autocls(xx);
            cout<<"root #:";
		}
    }
}


int main()
{
	memory_of_use.initial();
	system("color 0E");
	create();
	clearall();
    loadbitmap();
	MFD_LIST MFD_list;
	UFD_LIST UFD_list;
	window1(MFD_list,UFD_list);


    return 0;
}
