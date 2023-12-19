#include "disk.h"
#include "file.h"
#include "cmath"
//构造函数，初始化4kb硬盘
Disk::Disk()
{
    //初始化空闲盘区链，兑换区
    free_disk *disk_e1=new free_disk;//第一个节点
    disk_e1->disk_n=1;
    disk_e1->length=124;
    disk_e1->next_free=nullptr;
    free_list_e->next_free=disk_e1;
    free_end_e=disk_e1;
    //初始化空闲盘区链，文件区
    free_disk *disk_f1=new free_disk;//第一个节点
    disk_f1->disk_n=1;
    disk_f1->length=900;
    disk_f1->next_free=nullptr;
    free_list->next_free=disk_f1;
    free_end=disk_f1;
}

//显示空闲盘区(文件区)
int Disk::Show_file_extent()
{
    int fn=0;
    free_disk *p=free_list->next_free;
    for(int i=1;i<901;i++)
    {
        disk_file_extent[i]=1;
    }
    while(p)
    {
        for(int i=0;i<p->length;i++)
        {
            disk_file_extent[i+p->disk_n]=0;
            fn++;
        }
        p=p->next_free;
    }
    return fn;
}
//显示空闲盘区(兑换区)
int Disk::Show_exch_extent()
{
    int en=0;
    free_disk *p=free_list_e->next_free;
    for(int i=1;i<125;i++)
    {
        disk_exch_extent[i]=1;
    }
    while(p)
    {
        for(int i=0;i<p->length;i++)
        {
            disk_exch_extent[i+p->disk_n]=0;
            en++;
        }
        p=p->next_free;
    }
    return en;
}


//向文件区读入数据
void Disk::wirte_disk(file *f)
{
    free_disk *p=free_list;
    int t=0;
    if(f->file_size>0)
    {
        int f_s=(int)ceil((double)f->file_size/40);//文件将占用的盘块数
        //遍历盘区链
        while(p->next_free)
        {
            if(f_s<=p->next_free->length)//找到合适盘区
            {
                t=p->next_free->disk_n;//保存首盘块号
                int tt=t;
                //将数据写入磁盘
                for(int i=0,j=0;i<f->file_size;i++)
                {
                    if(j==40)//进入下一个盘块
                    {
                        j=0;
                        tt++;
                    }
                    disk_file[tt].data[j]=f->file_data[i];
                    j++;
                }
                //修改空闲盘区链
                if(f_s==p->next_free->length)//盘块恰好够
                {
                    free_disk *pp=p->next_free;
                    if(p->next_free==free_end)
                    {
                        free_end=p;
                    }
                    p->next_free=p->next_free->next_free;//更新空闲盘区链
                    delete pp;
                }
                else//有多余盘块
                {
                    free_disk *disk_fn=new free_disk,*pp=p->next_free;
                    disk_fn->disk_n=p->next_free->disk_n+f_s;
                    disk_fn->length=p->next_free->length-f_s;
                    if(p->next_free==free_end)
                    {
                        free_end=disk_fn;
                    }
                    disk_fn->next_free=p->next_free->next_free;//更新空闲盘区链
                    p->next_free=disk_fn;
                    delete pp;
                }
                break;
            }
            else
            {
                p=p->next_free;
            }
        }
        if(t)
        {
            f->start_num=t;//返回对应的首盘块号
        }
        else
        {
            //cout<<"写入失败，磁盘剩余空间不足！"<<endl;
        }
    }
    else
    {
        //cout<<"文件大小错误!"<<endl;
    }
}

void Disk::read_disk(file *f)
{
    free_disk *p=free_list_e;
    int t_f=f->start_num;//文件区盘块t_f
    int t_e=0;//兑换区盘块t_e
    int f_s=(int)ceil((double)f->file_size/40);//文件将占用的盘块数
    //遍历兑换区
    while(p->next_free)
    {
        if(f_s<=p->next_free->length)//找到合适盘区
        {
            t_e=p->next_free->disk_n;//保存首盘块号
            int tt=t_e;//中间变量
            //将数据从文件区写入兑换区
            for(int i=0,j=0;i<f->file_size;i++)
            {
                if(j==40)//进入下一个盘块
                {
                    j=0;
                    tt++;
                    t_f++;
                }
                disk_exchange[tt].data[j]=disk_file[t_f].data[j];
                j++;
            }
            //修改空闲盘区链
            if(f_s==p->next_free->length)//盘块恰好够
            {
                free_disk *pp=p->next_free;
                if(p->next_free==free_end_e)
                {
                    free_end_e=p;
                }
                p->next_free=p->next_free->next_free;//更新空闲盘区链
                delete pp;
            }
            else//有多余盘块
            {
                free_disk *disk_en=new free_disk,*pp=p->next_free;
                disk_en->disk_n=p->next_free->disk_n+f_s;
                disk_en->length=p->next_free->length-f_s;
                if(p->next_free==free_end_e)
                {
                    free_end_e=disk_en;
                }
                disk_en->next_free=p->next_free->next_free;//更新空闲盘区链
                p->next_free=disk_en;
                delete pp;
            }
            break;
        }
        else
        {
            p=p->next_free;
        }
    }

    if(t_e)//从兑换区读出数据
    {
        f->start_num_e=t_e;//返回对应的兑换区首盘块号

        for(int i=0,j=0;i<f->file_size;i++)
        {
            if(j==40)//进入下一个盘块
            {
                j=0;
                t_e++;
            }

            f->file_data[i]=disk_exchange[t_e].data[j];
            j++;
        }
    }
    else//兑换区已满，直接从文件区读出
    {
        for(int i=0,j=0;i<f->file_size;i++)
        {
            if(j==40)//进入下一个盘块
            {
                j=0;
                t_f++;
            }
            f->file_data[i]=disk_file[t_f].data[j];
            j++;
        }
    }
}

//删除文件区数据
void Disk::delete_f(file *f)
{
    free_disk *p=free_list;
    int t=f->start_num;
    //将数据从文件区删除
    for(int i=0,j=0;i<f->file_size;i++)
    {
        if(j==40)
        {
            j=0;
            t++;
        }
        disk_file[t].data[j]=NULL;
        j++;
    }
    //修改空闲盘区链
    int f_s=(int)ceil((double)f->file_size/40);//文件占用的盘块数
    int bef=0,aft=0;
    free_disk *q1=nullptr,*q2=nullptr,*q3=nullptr;//暂时储存相邻的空闲盘区
    while(p->next_free)//判断前后是否与空闲区相邻
    {
        if(p->next_free->disk_n+p->next_free->length==f->start_num)
        {
            bef=p->next_free->disk_n;//当前盘区是前领居空闲区
            q1=p->next_free;
        }
        else if(f->start_num+f_s==p->next_free->disk_n)
        {
            aft=p->next_free->disk_n;//当前盘区是后邻居空闲区
            q2=p->next_free;
            q3=p;
        }
        if(bef&&aft) break;//前后均有空闲区，直接跳出
        p=p->next_free;
    }
    if(bef&&aft)//前后均有空闲区
    {
        q1->length=q1->length+q2->length+f_s;
        q3->next_free=q2->next_free;
        delete q2;
    }
    else if(bef&&!aft)//只是前有空闲区
    {
        q1->length=q1->length+f_s;
    }
    else if(!bef&&aft)//只是后有空闲区
    {
        q2->disk_n=f->start_num;
        q2->length=f_s+q2->length;
    }
    else//前后都无空闲区
    {
        free_disk *disk_fn=new free_disk;
        disk_fn->disk_n=f->start_num;
        disk_fn->length=f_s;
        disk_fn->next_free=nullptr;
        free_end->next_free=disk_fn;
        free_end=disk_fn;
    }
}

void Disk::delete_e(file *f)
{
    free_disk *p=free_list_e;
    int t=f->start_num_e;
    //将数据从兑换区删除
    for(int i=0,j=0;i<f->file_size;i++)
    {
        if(j==40)
        {
            j=0;
            t++;
        }
        disk_exchange[t].data[j]=NULL;
        j++;
    }

    //修改空闲盘区链
    int f_s=(int)ceil((double)f->file_size/40);//文件占用的盘块数
    int bef=0,aft=0;
    free_disk *q1=nullptr,*q2=nullptr,*q3=nullptr;//暂时储存相邻的空闲盘区
    while(p->next_free)//判断前后是否与空闲区相邻
    {
        if(p->next_free->disk_n+p->next_free->length==f->start_num_e)
        {
            bef=p->next_free->disk_n;//当前盘区是前领居空闲区
            q1=p->next_free;
        }
        else if(f->start_num_e+f_s==p->next_free->disk_n)
        {
            aft=p->next_free->disk_n;//当前盘区是后邻居空闲区
            q2=p->next_free;
            q3=p;
        }
        if(bef&&aft) break;//前后均有空闲区，直接跳出
        p=p->next_free;
    }

    if(bef&&aft)//前后均有空闲区
    {
        q1->length=q1->length+q2->length+f_s;
        q3->next_free=q2->next_free;
        delete q2;
    }
    else if(bef&&!aft)//只是前有空闲区
    {
        q1->length=q1->length+f_s;
    }
    else if(!bef&&aft)//只是后有空闲区
    {
        q2->disk_n=f->start_num_e;
        q2->length=f_s+q2->length;
    }
    else//前后都无空闲区
    {
        free_disk *disk_en=new free_disk;
        disk_en->disk_n=f->start_num_e;
        disk_en->length=f_s;
        disk_en->next_free=nullptr;
        free_end->next_free=disk_en;
        free_end=disk_en;
    }
}


void Disk::rewirte_disk(file *f)
{
    int t=f->start_num;
    for(int i=0,j=0;i<f->file_size;i++)
    {
        if(j==40)//进入下一个盘块
        {
            j=0;
            t++;
        }
        disk_file[t].data[j]=f->file_data[i];
        j++;
    }
}



