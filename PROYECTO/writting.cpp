#include "writting.h"
void CreateDsk(string name,int size){
    fstream MyFile;
    MyFile = fstream(name,ios_base::binary | ios_base::out);
    std::vector<char> empty(1024, '\0');
    for(int i = 0; i < size; i++)
    {
        MyFile.seekp(MyFile.tellp());
        if (!MyFile.write(&empty[0], empty.size()))
        {
          //  std::cerr << "problem writing to file" << std::endl;
        }
    }
    MyFile.close();
}

void WriteMBR(string name,MBR mbr){
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(name,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    MyFile.seekp(i,std::ios_base::beg);
    MyFile.write((char*)&mbr,sizeof(struct MBR));
    MyFile.close();
}

int DeletePart(string name,string path,string ty){
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    
    try {
        MyFile.open(path,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    struct MBR tm;
    struct Partition N;
    char act;
    MyFile.read((char*)&tm,sizeof(struct MBR));
    if (tm.mbr_partition_1.part_name==name)
    {
        if (ty=="fast")
        {
            tm.mbr_partition_1=N;
            WriteMBR(path,tm);
        }else{
            MyFile.seekp(i,std::ios_base::beg);
            int e=i+tm.mbr_partition_1.part_s;
            int sz=tm.mbr_partition_1.part_s;
            if (tm.mbr_partition_1.part_s>(1024*1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for(int i = 0; i < (sz/(1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e=sz%(1024*1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (e/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                e=sz%(1024);
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else
            if (tm.mbr_partition_1.part_s>1024)
            {
                e=sz%(1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (sz/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else{
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }          
            tm.mbr_partition_1=N;
            WriteMBR(path,tm);
        }
        return 0;
    }else
    if (tm.mbr_partition_2.part_name==name)
    {
        if (ty=="fast")
        {
            tm.mbr_partition_2=N;
            WriteMBR(path,tm);
        }else{
            MyFile.seekp(i,std::ios_base::beg);
            int e=i+tm.mbr_partition_2.part_s;
            int sz=tm.mbr_partition_2.part_s;
            if (tm.mbr_partition_2.part_s>(1024*1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for(int i = 0; i < (sz/(1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e=sz%(1024*1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (e/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                e=sz%(1024);
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else
            if (tm.mbr_partition_2.part_s>1024)
            {
                e=sz%(1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (sz/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else{
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }     
            tm.mbr_partition_2=N;
            WriteMBR(path,tm);
        }
        return 0;
    }else
    if (tm.mbr_partition_3.part_name==name)
    {
        if (ty=="fast")
        {
            tm.mbr_partition_3=N;
            WriteMBR(path,tm);
        }else{
            MyFile.seekp(i,std::ios_base::beg);
            int e=i+tm.mbr_partition_3.part_s;
            int sz=tm.mbr_partition_3.part_s;
            if (tm.mbr_partition_3.part_s>(1024*1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for(int i = 0; i < (sz/(1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e=sz%(1024*1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (e/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                e=sz%(1024);
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else
            if (tm.mbr_partition_3.part_s>1024)
            {
                e=sz%(1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (sz/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else{
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }     
            tm.mbr_partition_3=N;
            WriteMBR(path,tm);
        }
        return 0;
    }else
    if (tm.mbr_partition_4.part_name==name)
    {
        if (ty=="fast")
        {
            tm.mbr_partition_4=N;
            WriteMBR(path,tm);
        }else{
            MyFile.seekp(i,std::ios_base::beg);
            int e=i+tm.mbr_partition_4.part_s;
            int sz=tm.mbr_partition_4.part_s;
            if (tm.mbr_partition_4.part_s>(1024*1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for(int i = 0; i < (sz/(1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e=sz%(1024*1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (e/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                e=sz%(1024);
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else
            if (tm.mbr_partition_1.part_s>1024)
            {
                e=sz%(1024);
                std::vector<char> Kempty(1024, '\0');
                for(int i = 0; i < (sz/(1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }else{
                std::vector<char> empty(1, '\0');
                for(int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(),std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                            //  std::cerr << "problem writing to file" << std::endl;
                    }
                } 
            }    
            tm.mbr_partition_4=N;
            WriteMBR(path,tm);
        }
        return 0;
    }
    return 1;
}

int WritePartition(string name,Partition part){
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(name,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    struct MBR tm;
    char act;
    MyFile.read((char*)&tm,sizeof(struct MBR));
    int max=tm.mbr_tamanio;
    int min=0+sizeof(tm);
    int sp=0;
    i=min;
    int e=i+part.part_s;
    int extpart=0;
    Partition first;
    Partition second;
    Partition third;
    Partition fourth;
    while (sp<4&&(i<max&&(e<max)))
    {
        if (tm.mbr_partition_1.part_status!='N')
        {
            
        }
        

        if (tm.mbr_partition_1.part_status!='N')
        {
            if (tm.mbr_partition_1.part_s=='E')
            {
                extpart++;
            }
            
            if ((tm.mbr_partition_1.part_start<=i)&&(i<=(tm.mbr_partition_1.part_start+tm.mbr_partition_1.part_s)))
            {
                i=tm.mbr_partition_1.part_start+tm.mbr_partition_1.part_s+1;
                e=i+part.part_s;
                if ((tm.mbr_partition_1.part_start<=e)&&(e<=(tm.mbr_partition_1.part_start+tm.mbr_partition_1.part_s)))
                {
                    i=tm.mbr_partition_1.part_start+tm.mbr_partition_1.part_s+1;
                    e=i+part.part_s;
                }
            } 
        }
        if (tm.mbr_partition_2.part_status!='N')
        {
            if (tm.mbr_partition_2.part_type=='E')
            {
                extpart++;
            }
            
            if ((tm.mbr_partition_2.part_start<=i)&&(i<=(tm.mbr_partition_2.part_start+tm.mbr_partition_2.part_s)))
            {
                i=tm.mbr_partition_2.part_start+tm.mbr_partition_2.part_s+1;
                e=i+part.part_s;
                if ((tm.mbr_partition_2.part_start<=e)&&(e<=(tm.mbr_partition_2.part_start+tm.mbr_partition_2.part_s)))
                {
                    i=tm.mbr_partition_2.part_start+tm.mbr_partition_2.part_s+1;
                    e=i+part.part_s;
                }
                }  
        }
        if (tm.mbr_partition_3.part_status!='N')
        {
            if (tm.mbr_partition_3.part_type=='E')
            {
                extpart++;
            }
            
            if ((tm.mbr_partition_3.part_start<=i)&&(i<=(tm.mbr_partition_3.part_start+tm.mbr_partition_3.part_s)))
            {
                i=tm.mbr_partition_3.part_start+tm.mbr_partition_3.part_s+1;
                e=i+part.part_s;
                if ((tm.mbr_partition_3.part_start<=e)&&(e<=(tm.mbr_partition_3.part_start+tm.mbr_partition_3.part_s)))
                {
                    i=tm.mbr_partition_3.part_start+tm.mbr_partition_3.part_s+1;
                    e=i+part.part_s;
                }
            } 
        }
        if (tm.mbr_partition_4.part_status!='N')
        {
            if (tm.mbr_partition_4.part_type=='E')
            {
                extpart++;
            }
            
            if ((tm.mbr_partition_4.part_start<=i)&&(i<=(tm.mbr_partition_4.part_start+tm.mbr_partition_4.part_s)))
            {
                i=tm.mbr_partition_4.part_start+tm.mbr_partition_4.part_s+1;
                e=i+part.part_s;
                if ((tm.mbr_partition_4.part_start<=e)&&(e<=(tm.mbr_partition_4.part_start+tm.mbr_partition_4.part_s)))
                {
                    i=tm.mbr_partition_4.part_start+tm.mbr_partition_4.part_s+1;
                    e=i+part.part_s;
                }
            } 
        }
        sp++;
    }
    if (i>=tm.mbr_tamanio||(e>=tm.mbr_tamanio))
    {
        return 1;
    }else
    {
        if (part.part_type=='E')
        {
            if (extpart!=0)
            {
                return 0;   
            }else{
                EBR nw;
                nw.part_status='N';
                nw.part_start=part.part_start;
                nw.part_s=nw.part_s;
                nw.part_next=-1;
                if (part.part_s>sizeof(struct EBR))
                {
                    fstream MyFile;
                    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                    try {
                        MyFile.open(name,ios_base::binary | ios_base::out | ios_base::in);
                    }
                    catch (std::system_error& e) {
                        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
                    }
                    MyFile.seekp(part.part_start,std::ios_base::beg);
                    MyFile.write((char*)&nw,sizeof(struct MBR));
                    MyFile.close();
                }
                
            }
        }
        
        if (part.part_type=='L'){
            Partition ext;
            if (tm.mbr_partition_1.part_type=='E')
            {
                ext=tm.mbr_partition_1;
            }else
            if (tm.mbr_partition_2.part_type=='E')
            {
                ext=tm.mbr_partition_2;
            }else
            if (tm.mbr_partition_3.part_type=='E')
            {
                ext=tm.mbr_partition_3;
            }else
            if (tm.mbr_partition_4.part_type=='E')
            {
                ext=tm.mbr_partition_4;
            }
            EBR te;
            fstream MyFile;
            MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try {
                MyFile.open(name,ios_base::binary | ios_base::out | ios_base::in);
            }
            catch (std::system_error& e) {
                std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
            }
            MyFile.seekp(ext.part_start,std::ios_base::beg);
            MyFile.read((char*)&te,sizeof(EBR));
            
            //MyFile.write((char*)&nw,sizeof(struct MBR));
            MyFile.close();
        }

        part.part_start=i;
        part.part_status='Y';
        
        if (tm.mbr_partition_1.part_status=='N')
        {
            tm.mbr_partition_1=part;
        }else
        if (tm.mbr_partition_2.part_status=='N')
        {
            tm.mbr_partition_2=part;
        }else
        if (tm.mbr_partition_3.part_status=='N')
        {
            tm.mbr_partition_3=part;
        }else
        if (tm.mbr_partition_4.part_status=='N')
        {
            tm.mbr_partition_4=part;
        }
        WriteMBR(name,tm);
    }
    return 1;
};

void LogicPartition(string name,MBR tm){
    
}

void ReportDsk(MBR tmm){
    string graph="digraph DSK {\n";
    graph+="node [shape=record];";
    graph+="struct0 [label=\"<f0> MBR";
    if (tmm.mbr_partition_1.part_status!='N')
    {
        graph+="| <f1>";
        graph+=tmm.mbr_partition_1.part_name;
    }
    if (tmm.mbr_partition_2.part_status!='N')
    {
        graph+="| <f2>";
        graph+=tmm.mbr_partition_2.part_name;
    }
    if (tmm.mbr_partition_3.part_status!='N')
    {
        graph+="| <f3>";
        graph+=tmm.mbr_partition_3.part_name;
    }
    if (tmm.mbr_partition_4.part_status!='N')
    {
        graph+="| <f4>";
        graph+=tmm.mbr_partition_4.part_name;
    }
    graph+="\"];\n";
    graph+="}";
    ofstream Myfile("rep.dot");

    Myfile<<graph;
    Myfile.close();
    string cmm="dot -Tpng ";
    cmm+="rep.dot -o rep.png";
    int le=cmm.length();
    char cmp[le];
    strcpy(cmp,cmm.c_str());
    system(cmp);
}

void FormatPartition(Partition part,string path,int n){
    fstream MyFile;
    SuperBloque sup;
    Journaling jn;
    Inodo in;
    Bloque blo;
    sup.s_inodes_count=n;
    sup.s_blocks_count=n*3;
    sup.s_free_blocks_count=n*3;
    sup.s_free_inodes_count=n;
    sup.s_mtime=time(0);
    sup.s_mnt_count=1;
    sup.s_magic=0xEF53;
    sup.s_inode_size=sizeof(struct Inodo);
    sup.s_block_size=sizeof(struct Bloque);
    sup.s_first_ino=0;
    sup.s_first_blo=0;

    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(path,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=part.part_start;
    struct MBR tm;
    char act;
    MyFile.read((char*)&tm,sizeof(struct MBR));
    MyFile.seekp(i,std::ios_base::beg);
    MyFile.write((char*)&sup,sizeof(struct SuperBloque));
    MyFile.write((char*)&jn,sizeof(struct Journaling));
    sup.s_bm_inode_start=MyFile.tellg();
    std::vector<char> empty(1, '0');
    for (int j = 0; j < n; j++)
    {
        MyFile.write(&empty[0],1);
    }
    sup.s_bm_block_start=MyFile.tellg();
    for (int j = 0; j < (3*n); j++)
    {
        MyFile.write(&empty[0],1);
    }
    sup.s_inode_start=MyFile.tellg();
    sup.s_first_ino=sup.s_inode_start;
    for (int j = 0; j < n; j++)
    {
        MyFile.write((char*)&in,sizeof(struct Inodo));
    }
    sup.s_block_start=MyFile.tellg();
    sup.s_first_blo=sup.s_block_start;
    for (int j = 0; j < 3*n; j++)
    {
        MyFile.write((char*)&blo,sizeof(struct Bloque));
    }
}

int WriteDir(Partition part,string path,string dirpath){
    fstream MyFile;
    SuperBloque sup;
    Journaling jn;
    Inodo in;
    Bloque blo;
    BloqueCarpetas blc;
    std::vector<char> empty(1, '\0');
    char* father=NULL;
    int fatherp=0;
    int i=part.part_start;
    char* token=strtok((char*)path.c_str(),"/");
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(path,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(i,std::ios_base::beg);
    MyFile.read((char*)&sup,sizeof(SuperBloque));
    
    while (token!=NULL)
    {
        MyFile.seekp(sup.s_first_ino,std::ios_base::beg);
        MyFile.read((char*)&in,sup.s_inode_size);
        MyFile.seekp(sup.s_first_blo,std::ios_base::beg);
        MyFile.write((char*)&blc,sizeof(BloqueCarpetas));
        MyFile.write((char*)&empty[0],1);
        MyFile.seekp(sup.s_first_blo,std::ios_base::beg);
        MyFile.read((char*)&blc,sizeof(blc));
        in.i_block[0]=sup.s_first_blo;
        strcpy(blc.b_content[0].b_name,token);
        blc.b_content[0].b_inodo=sup.s_first_ino;
        strcpy(blc.b_content[1].b_name,(char*)father);
        blc.b_content[1].b_inodo=fatherp;
        sup.s_first_ino+=sizeof(Inodo);
        sup.s_first_blo+=sizeof(Bloque);
        MyFile.seekp(sup.s_bm_inode_start,std::ios_base::beg); 
    }
 
    

   return 1;
}



Partition FindPartition(string path,string name){
    fstream MyFile;
    struct Partition N;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(path,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    struct MBR tm;
    char act;
    MyFile.read((char*)&tm,sizeof(struct MBR));
    if (tm.mbr_partition_1.part_status!='N')
    {
        if (tm.mbr_partition_1.part_name==name)
        {
            return tm.mbr_partition_1;
        }
        
    }else
    if (tm.mbr_partition_2.part_status!='N')
    {
        if (tm.mbr_partition_2.part_name==name)
        {
            return tm.mbr_partition_2;
        }
        
    }else
    if (tm.mbr_partition_3.part_status!='N')
    {
        if (tm.mbr_partition_3.part_name==name)
        {
            return tm.mbr_partition_3;
        }
        
    }else
    if (tm.mbr_partition_4.part_status!='N')
    {
        if (tm.mbr_partition_4.part_name==name)
        {
            return tm.mbr_partition_4;
        }
    }
    return N;
}

MBR ReadMBR(string path){
    fstream MyFile;
    struct Partition N;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        MyFile.open(path,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    struct MBR tm;
    char act;
    MyFile.read((char*)&tm,sizeof(struct MBR));
    return tm;
}
