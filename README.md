<center><h1>操作系统课程设计任务书</h1></center>
改进xv6和实现一个虚拟的操作系统
**一、课程设计任务**  
本次课程设计的任务是在Linux/Windows/iOS/Android等现有操作系统基础上，模拟实现部分操作系统的功能和相关算法，加深对操作系统运行机制的掌握和理解。本部分任务每组同学完成一份（分组见“课程设计分组”部分）。任务具体要求：  
以结构化或面向对象编程思想实现下面功能：  
1、**磁盘管理**  
建立一个40KB大小的文件，作为模拟磁盘，将其逻辑划分为1024块，每块大小40B。其中900块用于模拟文件区，124块用于模拟兑换分区。磁盘管理需要支持：  
（1）数据组织：对存放在文件区的数据加以组织管理，可以采用连续组织方式、显式连接（FAT）方式、单级索引组织方式、二级索引组织方式、混合索引方式（每组要求不同，具体见“课程设计分组”部分，下同）。  
（2）空闲块管理：能够查询并返回当前剩余的空闲块，对空闲块管理可以采用位示图法、空闲盘块表法、空闲盘块链法、成组连接法。  
（3）兑换区管理：能够写入、读出兑换区数据。  
2、**目录管理**  
为写入模拟磁盘的数据文件建立目录，目录可以是单级文件目录、双级文件目录、树形结构目录。在目录中选择某个文件可以将其数据读入模拟内存。目录中包含文件名、文件所有者、创建时间、文件结构、在磁盘中存放的地址等信息。目录管理需要支持：  
（1）新建目录：在目录中新建空目录  
（2）删除目录：删除空目录  
（3）为文件建立目录项：一个文件被创建后，为该文件创建目录项，并将文件相关信息写入目录中。  
（4）删除文件：删除目录中某个文件，删除其在磁盘中的数据，并删除目录项。如果被删除文件已经读入内存应该阻止删除，完成基本的文件保护。  
3、**内存管理**  
申请一块2.5KB（2560B）的内存空间模拟内存，按逻辑划分为64块，每块40B。将目录中选中的文件读入内存，并显示文件中信息（字符）。内存可以同时存放多个文件信息，每个文件固定分配8个内存块，如果8个内存块不能存放文件的全部信息，采用页面置换策略，将满足置换策略条件的页换出内存，可以选择的置换策略有，全局置换、局部置换、FIFO、LRU。内存管理需要支持：  
（1）分配内存块：为执行进程获得的文件数据分配内存块，每个进程默认分配8块。  
（2）回收内存：执行进程结束后回收其文件数据所占用的内存。  
（3）空闲内存块管理：为需要分配内存的数据寻找空闲内存块。没有空闲内存时，应给出提示。  
（4）页表管理：记录页面在内存块的对应关系，提供数据块进入模拟内存的访问、修改情况，为页面置换算法提供支持。  
4、**进程管理**  
本次模拟的操作系统的各部分功能以进程为基本运行单位，进程本身采用编程语言提供的进程机制，不模拟。本系统主要包括的进程有：  
（1）数据生成进程：该进程负责生成外存数据，给定数据大小（按字节计算）、数据信息（英文字母）、存储目录、文件名后，该进程调用磁盘管理中空闲磁盘管理功能，申请所需大小的外存块，如果盘块不够给出提示。按照要求的数据组织方式，将数据存入磁盘块（按块分配磁盘），并调用目录管理功能为其在目录中建立目录项，更改空闲盘块信息。注意，目录本身不需要分配盘块。  
（2）删除数据进程：该进程调用目录管理中删除文件功能删除数据（正在内存中的中文件不能被删除）。并回收外存空间，更新空闲盘块信息。  
（3）执行进程：选择目录中的文件，执行进程将文件数据从外存调入内存，为此，首先需要调用内存管理的空闲空间管理功能，为该进程申请8块空闲内存，如果没有足够内存则给出提示，然后根据目录中文件存储信息将文件数据从外存读入内存，此间如果8块内存不够存放文件信息，需要进行换页（选择的换页策略见分组要求），换出的页面存放到磁盘兑换区。允许同时运行多个执行进程。文件数据在内存块的分布通过进程的页表（模拟）进行记录。  
（4）进程互斥：对于2560B的内存，进程需要互斥访问，避免产生死锁。不能访问内存的进程阻塞，等待被唤醒。  
（5）进程间通信：进程间通信采用内存映射文件或者命名管道方式。  
5、**用户接口**  
对内存块、外存块、目录信息进行可视化显示，并能够动态刷新。文件调入内存过程、以及换页过程在块与块之间加入延时，以便观察。  
对于实现以上功能，可以采用任何熟悉的编程语言，不做具体要求。

**二、选做题目**  
在quem等模拟平台上完成操作系统内核的基本功能，包括：启动并初始化系统、内存管理、进程管理、中断及异常机制、系统调用、文件系统和用户命令接口。  
由于时间限制，对上述功能可以选择完成1-2个。也可以针对xv6等示例操作系统进行功能优化。


<br>
<br>
<center><h1>Operating System Course Design Task Book</h1></center>

**I. Course Design Task**  
The task of this course design is to simulate the implementation of some functionalities and related algorithms of operating systems like Linux/Windows/iOS/Android, to deepen the understanding and grasp of the operating system mechanisms. Each group of students should complete this part of the task separately (see the "Course Design Grouping" section for grouping). The specific requirements are:  
Implement the following functionalities using structured or object-oriented programming concepts:  
1. **Disk Management**  
Create a 40KB file as a simulated disk, logically divided into 1024 blocks, each block being 40B in size. Of these, 900 blocks are used to simulate the file area, and 124 blocks for the swap partition. Disk management should support:  
   (1) Data Organization: Manage and organize the data stored in the file area. This can be done using contiguous organization, explicit linking (FAT), single-level indexing, two-level indexing, or hybrid indexing methods (different requirements for each group, see the "Course Design Grouping" section for details).  
   (2) Free Block Management: Query and return current free blocks. Free block management can use bitmap, free disk block table, free disk block chain, or group linking methods.  
   (3) Swap Area Management: Ability to write to and read from the swap area.  
2. **Directory Management**  
Establish directories for data files written to the simulated disk. The directory can be a single-level file directory, a two-level file directory, or a tree-structured directory. Selecting a file in the directory should allow its data to be read into simulated memory. The directory includes information such as file name, file owner, creation time, file structure, and address in disk. Directory management should support:  
   (1) Create New Directory: Create a new empty directory in the directory.  
   (2) Delete Directory: Delete an empty directory.  
   (3) Create Directory Entry for File: After a file is created, create a directory entry for that file and write the file's related information into the directory.  
   (4) Delete File: Delete a file in the directory, delete its data on the disk, and remove the directory entry. If the file to be deleted has already been read into memory, deletion should be prevented to ensure basic file protection.  
3. **Memory Management**  
Allocate 2.5KB (2560B) of memory space to simulate memory, logically divided into 64 blocks, each block being 40B. Read selected files from the directory into memory and display the information (characters) in the files. Memory can store information of multiple files simultaneously, each file is allocated 8 memory blocks. If 8 memory blocks are not enough to store all the information of a file, use a page replacement strategy. Available strategies include global replacement, local replacement, FIFO, LRU. Memory management should support:  
   (1) Allocate Memory Blocks: Allocate memory blocks for file data obtained by executing processes, each process is allocated 8 blocks by default.  
   (2) Recycle Memory: Recycle the memory occupied by the file data after the execution process ends.  
   (3) Free Memory Block Management: Find free memory blocks for data that needs to be allocated memory. Provide a prompt when there is no free memory.  
   (4) Page Table Management: Record the correspondence of pages in memory blocks, provide access and modification status for data blocks entering simulated memory, and support page replacement algorithms.  
4. **Process Management**  
In this simulation, each part of the operating system runs based on processes. The processes themselves use the process mechanisms provided by programming languages and are not simulated. The main processes of this system include:  
   (1) Data Generation Process: This process is responsible for generating external storage data. After being given the data size (in bytes), data information (English letters), storage directory, and file name, this process calls the free disk management function of disk management to apply for the required size of external storage blocks. If there are not enough disk blocks, a prompt is given. According to the required data organization method, data is stored in disk blocks (disk allocation by block), and the directory management function is called to create a directory entry for it in the directory, updating the information of free disk blocks. Note that the directory itself does not need to allocate disk blocks.  
   (2) Data Deletion Process: This process calls the file deletion function in directory management to delete data (files in memory cannot be deleted). It also recovers external storage space and updates free disk block information.  
   (3) Execution Process: Select a file from the directory. The execution process loads the file data from external storage into memory. To do this, it first calls the free space management function of memory management to apply for 8 free memory blocks for the process. If there is not enough memory, a prompt is given. Then, according to the file storage information in the directory, file data is read from external storage into memory. If 8 memory blocks are not enough to store the file information, page swapping is required (the swapping strategy is according to group requirements), and the swapped-out pages are stored in the disk swap area. Multiple execution processes can run simultaneously. The distribution of file data in memory blocks is recorded through the process's page table (simulated).  
   (4) Process Mutual Exclusion: For the 2560B of memory, processes need to access it mutually exclusively to avoid deadlocks. Processes that cannot access memory are blocked, waiting to be awakened.  
   (5) Inter-process Communication: Inter-process communication is done using memory-mapped files or named pipes.  
5. **User Interface**  
Visualize and dynamically refresh memory blocks, external storage blocks, and directory information. Add delays between blocks during the file loading into memory and page swapping process to facilitate observation.  
For the implementation of the above functionalities, any familiar programming language can be used without specific requirements.

**II. Optional Topics**  
On simulation platforms like qemu, complete basic functionalities of an operating system kernel, including: starting and initializing the system, memory management, process management, interrupt and exception mechanisms, system calls, file systems, and user command interfaces.  
Due to time constraints, you can choose to complete 1-2 of the above functionalities. Alternatively, you can optimize functions of example operating systems like xv6.


