#include "memory.h"
#include <QMessageBox>
Memory::Memory()
{
    for(int i=0;i<64;i++)
    {
        is_leisure[i]=0;
    }
}
//为执行线程获得的文件数据分配8个内存块
void Memory::alloc_mem(file *cur_file)
{
//    //把这些内存设为被占用，修改页表
    deque<int> ql;
    ql = find_leisure(8);

    if(ql.size()==8)
    {
        int block_num=(cur_file->file_size)/40;       //所占用内存块数目
        if((cur_file->file_size%40)!=0)
        {
            block_num++;
        }
        deque<int> ql_use=ql;

        mem_of_file *mymem=new mem_of_file;
        mem_deep_copy(mymem,cur_file,ql);
        mymem->file_in_mem.in_memory=true;
        cur_file->in_memory=true;
        page_info.push_back(mymem);
        cout<<mymem->file_in_mem.name;
        for(int i=0;i<8;i++)
        {
            mem_state[ql_use.front()].blc=cur_file->start_num+i;
            mem_state[ql_use.front()].mem=ql_use.front();
            mem_state[ql_use.front()].file_in_mem=mymem->file_in_mem;
            if(i==0)
            {
                mem_state[ql_use.front()].is_protected=1;
            }
            else
            {
                mem_state[ql_use.front()].is_protected=0;
            }
            fifo_que.push_back(mem_state[ql_use.front()]);
            mymem->block_num.push_back(mem_state[ql_use.front()].blc);
            ql_use.pop_front();
        }

    }
//    else
//    {
//        QMessageBox::information(nullptr,"警告","系统资源不足，请稍后重试");
//    }
}

//回收内存，执行线程结束后回收其文件数据所占用的内存
void Memory::recl_mem(file *cur_file)
{
    //需要一个数据结构动态记录进入内存的某个文件此时占用的内存块
    cur_file->in_memory=false;
    unsigned int n=page_info.size();
    for(unsigned int i=0;i<n;i++)
    {
        mem_of_file *cur_info=new mem_of_file;
        cur_info=page_info.front();
        page_info.pop_front();
        if((cur_info->file_in_mem.name==cur_file->name))
        {
            deque<int> ql=cur_info->block_index;
            while(!ql.empty())
            {
                deque<block_mem> ql_use;
                while(!fifo_que.empty())
                {
                    if(ql.front()==fifo_que.front().mem)
                    {
                        fifo_que.pop_front();
                    }
                    else
                    {
                        ql_use.push_back(fifo_que.front());
                        fifo_que.pop_front();
                    }
                }
                while(!ql_use.empty())
                {
                    fifo_que.push_front(ql_use.back());
                    ql_use.pop_back();
                }
                mem_state[ql.front()].blc=-1;
                mem_state[ql.front()].is_protected=0;
                is_leisure[ql.front()]=0;
                ql.pop_front();
            }
            delete(cur_info);
        }
        else
        {
//            mem_of_file back_info=*cur_info;
            page_info.push_back(cur_info);
        }
    }


}

//为需要分配内存的数据寻找空闲内存块，没有空闲内存时给出提示
deque<int> Memory::find_leisure(int need_size)
{
    deque<int> ql;
    int count=0;
//    if(leisure_num()>=need_size)
//    {
        for(int i=0;i<64;i++)
        {
            if(is_leisure[i]==0)
            {
                ql.push_back(i);
                is_leisure[i]=1;
                count++;
            }

            if(count>=need_size)
            {
                break;
            }
        }
//    }
    return ql;
}

//页表管理，记录页面在内存块对应关系，提供数据块进入模拟内存的访问修改情况
void Memory::page_table()
{

}
//FIFO全局置换，bool值为真向后，为假向前
void Memory::FIFO(file *cur_file,int need_num,int cur_num)
{
    mem_of_file *cur_info=page_info.front();
    unsigned int n=page_info.size();
    for(unsigned int i=0;i<n;i++)
    {
        if((cur_info->file_in_mem.name==cur_file->name))
        {
            cur_info=page_info.front();
        }
//        else
//        {
//            page_info.push_back(page_info.front());
//        }
        page_info.push_back(page_info.front());
        page_info.pop_front();
    }
    if(is_lack(need_num)) //缺页
    {
        mem_state[get_mem_num(cur_num)].is_protected=0;
        if(leisure_num()==0)    //无空闲
        {
            deque<block_mem> ql;
            block_mem bm;
            while(fifo_que.front().is_protected==1)
            {
                ql.push_back(fifo_que.front());
                fifo_que.pop_front();
            }
            bm=fifo_que.front();
            fifo_que.pop_front();
            while(!ql.empty())
            {
                fifo_que.push_front(ql.back());
                ql.pop_back();
            }

            mem_state[bm.mem].file_in_mem=*cur_file;
            mem_state[bm.mem].blc=need_num;
            mem_state[bm.mem].is_protected=1;

            mem_of_file *change_file=new mem_of_file;  //找之前盘块号对应的文件
            change_file=find_file(bm);
            deque<int> ql1,ql2;
//            while(change_file->block_index.front()!=bm.mem)
//            {
//                ql1.push_back(change_file->block_index.front());
//                change_file->block_index.pop_front();
//            }
//            change_file->block_index.pop_front();
//            while(!ql1.empty())
//            {
//                change_file->block_index.push_front(ql1.back());
//                ql1.pop_back();
//            }

//            if(bm.blc!=-1)
//            {
//                while(change_file->block_num.front()!=bm.blc)
//                {
//                    ql2.push_back(change_file->block_num.front());
//                    change_file->block_num.pop_front();
//                }
//                change_file->block_num.pop_front();
//                while(!ql2.empty())
//                {
//                    change_file->block_num.push_front(ql2.back());
//                    ql2.pop_back();
//                }
//            }

            cur_info->block_index.push_back(bm.mem);
            cur_info->block_num.push_back(need_num);

            fifo_que.push_back(mem_state[bm.mem]);
        }
        else
        {
            deque<int> ql=find_leisure(1);
            cur_info->block_index.push_back(ql.front());
            cur_info->block_num.push_back(need_num);

            mem_state[ql.front()].mem=ql.front();
            mem_state[ql.front()].blc=need_num;
            mem_state[ql.front()].is_protected=1;
            fifo_que.push_back(mem_state[ql.front()]);
        }
    }
    else
    {
        mem_state[get_mem_num(cur_num)].is_protected=0;
        mem_state[get_mem_num(need_num)].is_protected=1;
    }

}
//返回空闲块个数
int Memory::leisure_num()
{
    int count=0;
    for(int i=0;i<64;i++)
    {
        if(is_leisure[i]==0)
        {
            count++;
        }
    }
    return count;
}

//结构体深拷贝
void Memory::mem_deep_copy(mem_of_file *mymem, file *cur_file,deque<int> ql)
{
    mymem->block_index=ql;
    mymem->file_in_mem.name=cur_file->name;
    mymem->file_in_mem.owner=cur_file->owner;
    mymem->file_in_mem.create_time=cur_file->create_time;
    mymem->file_in_mem.file_struct=cur_file->file_struct;
    mymem->file_in_mem.disk_address=cur_file->disk_address;
    mymem->file_in_mem.file_size=cur_file->file_size;

    for(int i=0;i<1000;i++)
    {
        mymem->file_in_mem.file_data[i]=cur_file->file_data[i];
    }
    mymem->file_in_mem.start_num=cur_file->start_num;
    mymem->file_in_mem.is_file=cur_file->is_file;
    mymem->file_in_mem.in_memory=cur_file->in_memory;
    mymem->file_in_mem.sibling=cur_file->sibling;
    mymem->file_in_mem.firstchild=cur_file->firstchild;
    mymem->file_in_mem.father=cur_file->father;
}

//是否缺页
bool Memory::is_lack(int block_num)
{
    deque<block_mem> ql;
    int flag=0;
    while(!fifo_que.empty())
    {
        if(fifo_que.front().blc==block_num)
        {
            flag=1;
        }
        ql.push_back(fifo_que.front());
        fifo_que.pop_front();
    }
    while(!ql.empty())
    {
        fifo_que.push_front(ql.back());
        ql.pop_back();
    }
    if(flag==1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//由外存块得到文件
mem_of_file* Memory::find_file(block_mem bm)
{
    mem_of_file *myret=new mem_of_file;
    unsigned int n=page_info.size();
    for(unsigned int i=0;i<n;i++)
    {
        int size=page_info.front()->file_in_mem.file_size/40;
        if((page_info.front()->file_in_mem.file_size%40)!=0)
        {
            size++;
        }
        if((page_info.front()->file_in_mem.start_num<=bm.blc)&&((page_info.front()->file_in_mem.start_num+size)>=bm.blc))
        {
            myret=page_info.front();
        }
        page_info.push_back(page_info.front());
        page_info.pop_front();
    }
}

//由外存块得到内存块号
int Memory::get_mem_num(int block_num)
{
    for(int i=0;i<64;i++)
    {
        if(mem_state[i].blc==block_num)
        {
            return i;
        }
    }
    return -1;
}

