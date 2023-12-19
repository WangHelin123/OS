<center><h1>操作系统课程设计任务书</h1></center>  

一、课程设计任务
本次课程设计的任务是在Linux/Windows/iOS/Android等现有操作系统基础上，模拟实现部分操作系统的功能和相关算法，加深对操作系统运行机制的掌握和理解。本部分任务每组同学完成一份（分组见“课程设计分组”部分）。任务具体要求：
以结构化或面向对象编程思想实现下面功能：
1、磁盘管理
建立一个40KB大小的文件，作为模拟磁盘，将其逻辑划分为1024块，每块大小40B。其中900块用于模拟文件区，124块用于模拟兑换分区。磁盘管理需要支持：
（1）数据组织：对存放在文件区的数据加以组织管理，可以采用连续组织方式、显式连接（FAT）方式、单级索引组织方式、二级索引组织方式、混合索引方式（每组要求不同，具体见“课程设计分组”部分，下同）。
（2）空闲块管理：能够查询并返回当前剩余的空闲块，对空闲块管理可以采用位示图法、空闲盘块表法、空闲盘块链法、成组连接法。
（3）兑换区管理：能够写入、读出兑换区数据。
2、目录管理
	为写入模拟磁盘的数据文件建立目录，目录可以是单级文件目录、双级文件目录、树形结构目录。在目录中选择某个文件可以将其数据读入模拟内存。目录中包含文件名、文件所有者、创建时间、文件结构、在磁盘中存放的地址等信息。目录管理需要支持：
（1）新建目录：在目录中新建空目录
（2）删除目录：删除空目录
（3）为文件建立目录项：一个文件被创建后，为该文件创建目录项，并将文件相关信息写入目录中。
（4）删除文件：删除目录中某个文件，删除其在磁盘中的数据，并删除目录项。如果被删除文件已经读入内存应该阻止删除，完成基本的文件保护。
3、内存管理
	申请一块2.5KB（2560B）的内存空间模拟内存，按逻辑划分为64块，每块40B。将目录中选中的文件读入内存，并显示文件中信息（字符）。内存可以同时存放多个文件信息，每个文件固定分配8个内存块，如果8个内存块不能存放文件的全部信息，采用页面置换策略，将满足置换策略条件的页换出内存，可以选择的置换策略有，全局置换、局部置换、FIFO、LRU。内存管理需要支持：
（1）分配内存块：为执行进程获得的文件数据分配内存块，每个进程默认分配8块。
（2）回收内存：执行进程结束后回收其文件数据所占用的内存。
（3）空闲内存块管理：为需要分配内存的数据寻找空闲内存块。没有空闲内存时，应给出提示。
    （4）页表管理：记录页面在内存块的对应关系，提供数据块进入模拟内存的访问、修改情况，为页面置换算法提供支持。
4、进程管理
	 本次模拟的操作系统的各部分功能以进程为基本运行单位，进程本身采用编程语言提供的进程机制，不模拟。本系统主要包括的进程有：
（1）数据生成进程：该进程负责生成外存数据，给定数据大小（按字节计算）、数据信息（英文字母）、存储目录、文件名后，该进程调用磁盘管理中空闲磁盘管理功能，申请所需大小的外存块，如果盘块不够给出提示。按照要求的数据组织方式，将数据存入磁盘块（按块分配磁盘），并调用目录管理功能为其在目录中建立目录项，更改空闲盘块信息。注意，目录本身不需要分配盘块。
（2）删除数据进程：该进程调用目录管理中删除文件功能删除数据（正在内存中的中文件不能被删除）。并回收外存空间，更新空闲盘块信息。
（3）执行进程：选择目录中的文件，执行进程将文件数据从外存调入内存，为此，首先需要调用内存管理的空闲空间管理功能，为该进程申请8块空闲内存，如果没有足够内存则给出提示，然后根据目录中文件存储信息将文件数据从外存读入内存，此间如果8块内存不够存放文件信息，需要进行换页（选择的换页策略见分组要求），换出的页面存放到磁盘兑换区。允许同时运行多个执行进程。文件数据在内存块的分布通过进程的页表（模拟）进行记录。
（4）进程互斥：对于2560B的内存，进程需要互斥访问，避免产生死锁。不能访问内存的进程阻塞，等待被唤醒。
（5）进程间通信：进程间通信采用内存映射文件或者命名管道方式。
5、用户接口
	对内存块、外存块、目录信息进行可视化显示，并能够动态刷新。文件调入内存过程、以及换页过程在块与块之间加入延时，以便观察。
	对于实现以上功能，可以采用任何熟悉的编程语言，不做具体要求。

二、选作题目
在quem等模拟平台上完成操作系统内核的基本功能，包括：启动并初始化系统、内存管理、进程管理、中断及异常机制、系统调用、文件系统和用户命令接口。
由于时间限制，对上述功能可以选择完成1-2个。也可以针对xv6等示例操作系统进行功能优化。

三、成员
| 题号 | 置换策略      | 目录结构 | 外存组织 | 空闲磁盘管理 | 进程间通信   | 成员姓名                     |  
| ---- | ------------- | -------- | -------- | ------------- | ------------ | ------------------------------- |  
| 2    | 局部置换CLOCK | 树形目录 | 索引分配 | 成组链接法   | 内存映射文件 | 吴迪 焦奕博 刘彬彬 姚锐 王贺麟 |  


<center><h1>《Operating system course design assignment》</h1></center>  


1. Course design tasks
The curriculum design of the task is in the Linux/Windows/iOS/Android operating system, based on the existing simulation to realize the function of the part of the operating system and related algorithms, deepen to grasp and understanding of the operation mechanism of the operating system. Each group of students will complete one task in this part (see "Course Design Group" section). Specific task requirements:
Implement the following functions with structured or object-oriented programming thinking:
1. Disk management
Create a 40KB file as an analog disk and logically divide it into 1024 blocks, each 40B in size. Of these, 900 blocks are used to simulate the file area and 124 blocks are used to simulate the redemption partition. Disk management needs to support:
(1) Data organization: The data stored in the file area can be organized and managed by continuous organization, explicit connection (FAT), single-level index organization, second-level index organization, and mixed index (each group has different requirements, specifically see the "course design group" part, the same below).
(2) Free block management: can query and return the current remaining free blocks, the free block management can use the bitmap method, free disk block table method, free disk block chain method, group connection method.
(3) Exchange area management: can write and read the exchange area data.
2. Directory management
Create a directory for data files written to the analog disk. The directory can be a single-level file directory, a two-level file directory, or a tree-structured directory. Select a file in the directory to read its data into analog memory. The directory contains information such as file name, file owner, creation time, file structure, and disk address. Directory management requires support for:
(1) Create a directory: Create an empty directory in the directory
(2) Delete a directory: Delete an empty directory
(3) Create a directory item for a file: After a file is created, create a directory item for the file, and write the file information into the directory.
(4) Delete files: Delete a file in the directory, delete its data in the disk, and delete directory items. If the deleted file has already been read into memory, the deletion should be prevented, completing basic file protection.
3. Memory management
Apply for a 2.5KB (2560B) memory space. The analog memory space is logically divided into 64 40B blocks. Reads the selected file in the directory into memory and displays the information (characters) in the file. Memory can store multiple file information at the same time, each file fixed allocation of 8 memory blocks, if the 8 memory blocks can not store all the information of the file, the use of page replacement strategy, will meet the conditions of the replacement strategy page out of memory, can choose the replacement strategy are, global replacement, local replacement, FIFO, LRU. Memory management needs to support:
(1) Allocate memory blocks: Allocate memory blocks for the file data obtained by the execution process, and each process is allocated 8 blocks by default.
(2) Reclaim memory: The memory occupied by the file data is reclaimed after the execution process ends.
(3) Free memory block management: Find free memory blocks for data that needs to be allocated memory. If there is no free memory, a prompt should be given.
(4) Page table management: record the corresponding relationship of the page in the memory block, provide the access and modification of the data block into the analog memory, and provide support for the page replacement algorithm.
4. Process management
The functions of each part of the simulated operating system take the process as the basic operating unit, and the process itself adopts the process mechanism provided by the programming language, which is not simulated. The system mainly includes the following processes:
(1) Data generation process: the process is responsible for generating external storage data, given the data size (calculated in bytes), data information (English letters), storage directory, file name, the process calls the disk management free disk management function, apply for the required size of the external storage block, if the disk block is not enough to give a prompt. According to the required data organization mode, the data is stored in the disk block (allocate the disk by block), and the directory management function is called to create a directory entry in the directory and change the information of the free disk block. Note that the directory itself does not need to allocate a disk block.
(2) Delete data process: This process calls the delete file function in directory management to delete data (files in memory cannot be deleted). Reclaim the external storage space and update the idle disk information.
(3) Execution process: Select the file in the directory and execute the process to import the file data from the external memory. To this end, first call the free space management function of memory management to apply for 8 free memory for the process. If there is not enough memory, give a prompt, and then read the file data from the external memory according to the file storage information in the directory. You need to change the page (see the group requirements for the selected page change policy), and the replaced page is stored in the disk exchange area. Allows multiple execution processes to run simultaneously. The distribution of file data in memory blocks is recorded by the process's page table (emulation).
(4) Processes are mutually exclusive: For 2560B memory, processes must be mutually exclusive to avoid deadlock. A process that cannot access memory is blocked, waiting to be awakened.
(5) Inter-process communication: Inter-process communication uses memory-mapped files or named pipelines.
5. User interface
The information of memory blocks, external storage blocks, and directories can be visually displayed and dynamically refreshed. The file loading process and the page feed process add delays between blocks for easy observation.
To achieve the above functions, you can use any familiar programming language, do not make specific requirements.

2. Choose a topic
Complete the basic functions of the operating system kernel on the simulation platform such as quem, including: starting and initializing the system, memory management, process management, interrupt and exception mechanism, system call, file system and user command interface.
Due to time constraints, you can choose to complete 1-2 of the above functions. Features can also be optimized for example operating systems such as xv6.

Iii. Members
| issue number | Replacement policy | directory structure | External storage organization | Free disk management | Interprocess communication | Member student |
| ---- | ------------- | -------- | -------- | ------------- | ------------ | ------------------------------- |
| 2 | Local replacement CLOCK | directory in the tree | Index assignment | Group linking method | Memory mapped file | Di Wu, Yibo Jiao,Binbin Liu,Hui Yao,Helin Wang|
