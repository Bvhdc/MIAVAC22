#include "writting.h"
void CreateDsk(string name, int size)
{
    fstream MyFile;
    MyFile = fstream(name, ios_base::binary | ios_base::out);
    std::vector<char> empty(1024, '\0');
    for (int i = 0; i < size; i++)
    {
        MyFile.seekp(MyFile.tellp());
        if (!MyFile.write(&empty[0], empty.size()))
        {
            //  std::cerr << "problem writing to file" << std::endl;
        }
    }
    MyFile.close();
}

inline bool exists(const std::string &name)
{
    ifstream f(name.c_str());
    return f.good();
}

void WriteMBR(string name, MBR mbr)
{
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(name, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = 0;
    MyFile.seekp(i, std::ios_base::beg);
    MyFile.write((char *)&mbr, sizeof(struct MBR));
    MyFile.close();
}

int DeletePart(string name, string path, string ty)
{
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = 0;
    struct MBR tm;
    struct Partition N;
    char act;
    MyFile.read((char *)&tm, sizeof(struct MBR));
    if (tm.mbr_partition_1.part_name == name)
    {
        if (ty == "fast")
        {
            tm.mbr_partition_1 = N;
            WriteMBR(path, tm);
        }
        else
        {
            MyFile.seekp(i, std::ios_base::beg);
            int e = i + tm.mbr_partition_1.part_s;
            int sz = tm.mbr_partition_1.part_s;
            if (tm.mbr_partition_1.part_s > (1024 * 1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for (int i = 0; i < (sz / (1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024 * 1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (e / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024);
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else if (tm.mbr_partition_1.part_s > 1024)
            {
                e = sz % (1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (sz / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else
            {
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            tm.mbr_partition_1 = N;
            WriteMBR(path, tm);
        }
        return 0;
    }
    else if (tm.mbr_partition_2.part_name == name)
    {
        if (ty == "fast")
        {
            tm.mbr_partition_2 = N;
            WriteMBR(path, tm);
        }
        else
        {
            MyFile.seekp(i, std::ios_base::beg);
            int e = i + tm.mbr_partition_2.part_s;
            int sz = tm.mbr_partition_2.part_s;
            if (tm.mbr_partition_2.part_s > (1024 * 1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for (int i = 0; i < (sz / (1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024 * 1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (e / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024);
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else if (tm.mbr_partition_2.part_s > 1024)
            {
                e = sz % (1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (sz / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else
            {
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            tm.mbr_partition_2 = N;
            WriteMBR(path, tm);
        }
        return 0;
    }
    else if (tm.mbr_partition_3.part_name == name)
    {
        if (ty == "fast")
        {
            tm.mbr_partition_3 = N;
            WriteMBR(path, tm);
        }
        else
        {
            MyFile.seekp(i, std::ios_base::beg);
            int e = i + tm.mbr_partition_3.part_s;
            int sz = tm.mbr_partition_3.part_s;
            if (tm.mbr_partition_3.part_s > (1024 * 1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for (int i = 0; i < (sz / (1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024 * 1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (e / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024);
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else if (tm.mbr_partition_3.part_s > 1024)
            {
                e = sz % (1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (sz / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else
            {
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            tm.mbr_partition_3 = N;
            WriteMBR(path, tm);
        }
        return 0;
    }
    else if (tm.mbr_partition_4.part_name == name)
    {
        if (ty == "fast")
        {
            tm.mbr_partition_4 = N;
            WriteMBR(path, tm);
        }
        else
        {
            MyFile.seekp(i, std::ios_base::beg);
            int e = i + tm.mbr_partition_4.part_s;
            int sz = tm.mbr_partition_4.part_s;
            if (tm.mbr_partition_4.part_s > (1024 * 1024))
            {
                std::vector<char> Mempty(1048576, '\0');
                for (int i = 0; i < (sz / (1048576)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Mempty[0], Mempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024 * 1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (e / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                e = sz % (1024);
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else if (tm.mbr_partition_1.part_s > 1024)
            {
                e = sz % (1024);
                std::vector<char> Kempty(1024, '\0');
                for (int i = 0; i < (sz / (1024)); i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&Kempty[0], Kempty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            else
            {
                std::vector<char> empty(1, '\0');
                for (int i = 0; i < e; i++)
                {
                    MyFile.seekp(MyFile.tellp(), std::ios_base::beg);
                    if (!MyFile.write(&empty[0], empty.size()))
                    {
                        //  std::cerr << "problem writing to file" << std::endl;
                    }
                }
            }
            tm.mbr_partition_4 = N;
            WriteMBR(path, tm);
        }
        return 0;
    }
    return 1;
}

int WritePartition(string name, Partition part)
{
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(name, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = 0;
    struct MBR tm;
    char act;
    MyFile.read((char *)&tm, sizeof(struct MBR));
    int max = tm.mbr_tamanio;
    int min = 0 + sizeof(tm);
    int sp = 0;
    i = min;
    int e = i + part.part_s;
    int extpart = 0;
    Partition first;
    Partition second;
    Partition third;
    Partition fourth;
    while (sp < 4 && (i < max && (e < max)))
    {
        if (tm.mbr_partition_1.part_status != 'N')
        {
        }

        if (tm.mbr_partition_1.part_status != 'N')
        {
            if (tm.mbr_partition_1.part_s == 'E')
            {
                extpart++;
            }

            if ((tm.mbr_partition_1.part_start <= i) && (i <= (tm.mbr_partition_1.part_start + tm.mbr_partition_1.part_s)))
            {
                i = tm.mbr_partition_1.part_start + tm.mbr_partition_1.part_s + 1;
                e = i + part.part_s;
                if ((tm.mbr_partition_1.part_start <= e) && (e <= (tm.mbr_partition_1.part_start + tm.mbr_partition_1.part_s)))
                {
                    i = tm.mbr_partition_1.part_start + tm.mbr_partition_1.part_s + 1;
                    e = i + part.part_s;
                }
            }
        }
        if (tm.mbr_partition_2.part_status != 'N')
        {
            if (tm.mbr_partition_2.part_type == 'E')
            {
                extpart++;
            }

            if ((tm.mbr_partition_2.part_start <= i) && (i <= (tm.mbr_partition_2.part_start + tm.mbr_partition_2.part_s)))
            {
                i = tm.mbr_partition_2.part_start + tm.mbr_partition_2.part_s + 1;
                e = i + part.part_s;
                if ((tm.mbr_partition_2.part_start <= e) && (e <= (tm.mbr_partition_2.part_start + tm.mbr_partition_2.part_s)))
                {
                    i = tm.mbr_partition_2.part_start + tm.mbr_partition_2.part_s + 1;
                    e = i + part.part_s;
                }
            }
        }
        if (tm.mbr_partition_3.part_status != 'N')
        {
            if (tm.mbr_partition_3.part_type == 'E')
            {
                extpart++;
            }

            if ((tm.mbr_partition_3.part_start <= i) && (i <= (tm.mbr_partition_3.part_start + tm.mbr_partition_3.part_s)))
            {
                i = tm.mbr_partition_3.part_start + tm.mbr_partition_3.part_s + 1;
                e = i + part.part_s;
                if ((tm.mbr_partition_3.part_start <= e) && (e <= (tm.mbr_partition_3.part_start + tm.mbr_partition_3.part_s)))
                {
                    i = tm.mbr_partition_3.part_start + tm.mbr_partition_3.part_s + 1;
                    e = i + part.part_s;
                }
            }
        }
        if (tm.mbr_partition_4.part_status != 'N')
        {
            if (tm.mbr_partition_4.part_type == 'E')
            {
                extpart++;
            }

            if ((tm.mbr_partition_4.part_start <= i) && (i <= (tm.mbr_partition_4.part_start + tm.mbr_partition_4.part_s)))
            {
                i = tm.mbr_partition_4.part_start + tm.mbr_partition_4.part_s + 1;
                e = i + part.part_s;
                if ((tm.mbr_partition_4.part_start <= e) && (e <= (tm.mbr_partition_4.part_start + tm.mbr_partition_4.part_s)))
                {
                    i = tm.mbr_partition_4.part_start + tm.mbr_partition_4.part_s + 1;
                    e = i + part.part_s;
                }
            }
        }
        sp++;
    }
    if (i >= tm.mbr_tamanio || (e >= tm.mbr_tamanio))
    {
        return 1;
    }
    else
    {
        if (part.part_type == 'E')
        {
            if (extpart != 0)
            {
                return 0;
            }
            else
            {
                EBR nw;
                nw.part_status = 'N';
                nw.part_start = part.part_start;
                nw.part_s = nw.part_s;
                nw.part_next = -1;
                if (part.part_s > sizeof(struct EBR))
                {
                    fstream MyFile;
                    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
                    try
                    {
                        MyFile.open(name, ios_base::binary | ios_base::out | ios_base::in);
                    }
                    catch (std::system_error &e)
                    {
                        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
                    }
                    MyFile.seekp(part.part_start, std::ios_base::beg);
                    MyFile.write((char *)&nw, sizeof(struct MBR));
                    MyFile.close();
                }
            }
        }

        if (part.part_type == 'L')
        {
            Partition ext;
            if (tm.mbr_partition_1.part_type == 'E')
            {
                ext = tm.mbr_partition_1;
            }
            else if (tm.mbr_partition_2.part_type == 'E')
            {
                ext = tm.mbr_partition_2;
            }
            else if (tm.mbr_partition_3.part_type == 'E')
            {
                ext = tm.mbr_partition_3;
            }
            else if (tm.mbr_partition_4.part_type == 'E')
            {
                ext = tm.mbr_partition_4;
            }
            EBR te;
            fstream MyFile;
            MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                MyFile.open(name, ios_base::binary | ios_base::out | ios_base::in);
            }
            catch (std::system_error &e)
            {
                std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
            }
            MyFile.seekp(ext.part_start, std::ios_base::beg);
            MyFile.read((char *)&te, sizeof(EBR));

            // MyFile.write((char*)&nw,sizeof(struct MBR));
            MyFile.close();
        }

        part.part_start = i;
        part.part_status = 'Y';

        if (tm.mbr_partition_1.part_status == 'N')
        {
            tm.mbr_partition_1 = part;
        }
        else if (tm.mbr_partition_2.part_status == 'N')
        {
            tm.mbr_partition_2 = part;
        }
        else if (tm.mbr_partition_3.part_status == 'N')
        {
            tm.mbr_partition_3 = part;
        }
        else if (tm.mbr_partition_4.part_status == 'N')
        {
            tm.mbr_partition_4 = part;
        }
        WriteMBR(name, tm);
    }
    return 1;
};

void LogicPartition(string name, MBR tm)
{
}

void ReportDsk(MBR tmm)
{
    string graph = "digraph DSK {\n";
    graph += "node [shape=record];";
    graph += "struct0 [label=<<TABLE><tr><td bgcolor=\"yellow\">MBR</td>";
    if (tmm.mbr_partition_1.part_status != 'N')
    {
        graph += "<td bgcolor=\"green\">";
        graph += tmm.mbr_partition_1.part_name;
        graph += "</td>";
    }
    if (tmm.mbr_partition_2.part_status != 'N')
    {
        graph += "<td bgcolor=\"green\">";
        graph += tmm.mbr_partition_2.part_name;
        graph += "</td>";
    }
    if (tmm.mbr_partition_3.part_status != 'N')
    {
        graph += "<td bgcolor=\"green\">";
        graph += tmm.mbr_partition_3.part_name;
        graph += "</td>";
    }
    if (tmm.mbr_partition_4.part_status != 'N')
    {
        graph += "<td bgcolor=\"green\">";
        graph += tmm.mbr_partition_4.part_name;
        graph += "</td>";
    }
    graph += "</tr></TABLE>>];\n";
    graph += "}";
    ofstream Myfile("rep.dot");

    Myfile << graph;
    Myfile.close();
    string cmm = "dot -Tpng ";
    cmm += "rep.dot -o rep.png";
    int le = cmm.length();
    char cmp[le];
    strcpy(cmp, cmm.c_str());
    system(cmp);
}

int WriteDir(Partition part, string path, string dirpath)
{
    fstream MyFile;
    SuperBloque sup;
    Journaling jn;
    Inodo in;
    Bloque blo;
    BloqueCarpetas blc;
    std::vector<char> empty(1, '\0');
    char *father = NULL;
    int fatherp = 0;
    int i = part.part_start;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(i);
    MyFile.read((char *)&sup, sizeof(SuperBloque));
    MyFile.seekp(sup.s_bm_inode_start);
    int n = 0;
    char e = '0';
    MyFile.read((char *)&e, 1);
    if (e != '1')
    {
        MyFile.seekp(sup.s_bm_inode_start);
        e = '1';
        MyFile.write((char *)&e, sizeof(char));
        MyFile.seekp(sup.s_inode_start);
        Inodo inew;
        fill_n(inew.i_block, 16, -1);
        inew.i_uid = 0;
        inew.i_s = 0;
        inew.i_atime = time(0);
        inew.i_ctime = time(0);
        inew.i_mtime = time(0);
        inew.i_block[0] = 0;
        inew.i_type = '0';
        MyFile.write((char *)&inew, sizeof(Inodo));
        sup.s_first_ino = 1;
        MyFile.seekp(sup.s_bm_block_start);
        MyFile.write((char *)&e, sizeof(char));
        sup.s_first_blo = 1;
        BloqueCarpetas ibloque;
        for (int i = 0; i < 4; i++)
        {
            ibloque.b_content[i].b_inodo = -1;
        }

        strcpy(ibloque.b_content[0].b_name, ".");
        ibloque.b_content[0].b_inodo = 0;
        strcpy(ibloque.b_content[1].b_name, "..");
        ibloque.b_content[1].b_inodo = 0;
        MyFile.seekp(sup.s_block_start);
        MyFile.write((char *)&ibloque, sizeof(BloqueCarpetas));
        MyFile.seekp(part.part_start);
        MyFile.write((char *)&sup, sizeof(SuperBloque));
        MyFile.seekp(sup.s_bm_inode_start);
    }
    else
    {
        string altpath = path;
        char *token = strtok((char *)dirpath.c_str(), "/");
        Inodo padre;
        BloqueCarpetas bpadre;
        MyFile.seekp(sup.s_inode_start);
        MyFile.read((char *)&padre, sup.s_inode_s);
        MyFile.seekp(sup.s_block_start);
        MyFile.read((char *)&bpadre, sup.s_block_s);
        while (token != NULL)
        {
            try
            {
                padre = FindDir(token, path, part, sup);
            }
            catch (int num)
            {
                MyFile.seekp(sup.s_block_start + padre.i_block[0] * sup.s_block_s);
                MyFile.read((char *)&bpadre, sup.s_block_s);
                NewDir(bpadre.b_content[0].b_inodo, bpadre.b_content[0].b_name, token, 0, 0, path, part);
            }
            token = strtok(NULL, "/");
        }
    }
    MyFile.close();

    return 1;
}

void FormatPartition(Partition part, string path, int n)
{
    fstream MyFile;
    SuperBloque sup;
    Journaling jn;
    Inodo in;
    Bloque blo;
    sup.s_inodes_count = n;
    sup.s_blocks_count = n * 3;
    sup.s_free_blocks_count = n * 3;
    sup.s_free_inodes_count = n;
    sup.s_mtime = time(0);
    sup.s_mnt_count = 1;
    sup.s_magic = 0xEF53;
    sup.s_inode_s = sizeof(struct Inodo);
    sup.s_block_s = sizeof(struct Bloque);
    sup.s_first_ino = 0;
    sup.s_first_blo = 0;

    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = part.part_start;
    struct MBR tm;
    char act;
    MyFile.read((char *)&tm, sizeof(struct MBR));
    MyFile.seekp(i, std::ios_base::beg);
    MyFile.write((char *)&sup, sizeof(struct SuperBloque));
    sup.s_bm_inode_start = MyFile.tellg();
    std::vector<char> empty(1, '0');
    for (int j = 0; j < n; j++)
    {
        MyFile.write(&empty[0], sizeof(char));
    }
    sup.s_bm_block_start = MyFile.tellg();
    for (int j = 0; j < (3 * n); j++)
    {
        MyFile.write(&empty[0], sizeof(char));
    }
    sup.s_inode_start = MyFile.tellg();
    for (int j = 0; j < n; j++)
    {
        MyFile.write((char *)&in, sizeof(struct Inodo));
    }
    sup.s_block_start = MyFile.tellg();
    sup.s_first_blo = 0;
    for (int j = 0; j < 3 * n; j++)
    {
        MyFile.write((char *)&blo, sizeof(struct Bloque));
    }
    cout << MyFile.tellg();
    MyFile.seekp(part.part_start);
    MyFile.write((char *)&sup, sizeof(SuperBloque));
    MyFile.seekp(sup.s_bm_inode_start);
    char a;
    char b;
    MyFile.close();
    WriteDir(part, path, "/");
}
// err

Inodo NewDr(int padre, string pname, string name, int uid, int gid, string path, Partition part)
{
    Inodo inew;
    fstream MyFile;
    Inodo ipadre;
    BloqueCarpetas bpadre;
    SuperBloque sup;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(part.part_start);
    MyFile.read((char *)&sup, sizeof(SuperBloque));
    inew.i_uid = 0;
    inew.i_s = 0;
    inew.i_atime = time(0);
    inew.i_ctime = time(0);
    inew.i_mtime = time(0);
    fill_n(inew.i_block, 16, -1);
    inew.i_type = '0';
    BloqueCarpetas bnew;
    for (int i = 0; i < 4; i++)
    {
        bnew.b_content[i].b_inodo = -1;
    }
    MyFile.seekp(sup.s_inode_start + padre * sup.s_inode_s);
    MyFile.read((char *)&ipadre, sup.s_inode_s);
    MyFile.read((char *)&bpadre, sup.s_block_s);
    strcpy(bnew.b_content[0].b_name, name.c_str());
    bnew.b_content[0].b_inodo = sup.s_first_ino;
    bnew.b_content[1].b_inodo = padre;
    strcpy(bnew.b_content[1].b_name, bpadre.b_content[0].b_name);
    bool added = false;
    int fs = -1;
    for (int i = 0; i < 15; i++)
    {
        if (ipadre.i_block[i] != -1)
        {
            MyFile.seekp(sup.s_block_start + ipadre.i_block[i] * sup.s_block_s);
            MyFile.read((char *)&bpadre, sup.s_block_s);
            int j;
            for (j = 0; j < 4; j++)
            {
                if (bpadre.b_content[j].b_inodo == -1)
                {
                    bpadre.b_content[j].b_inodo = bnew.b_content[0].b_inodo;
                    strcpy(bpadre.b_content[j].b_name, bnew.b_content[0].b_name);
                    MyFile.seekp(sup.s_block_start + ipadre.i_block[i] * sup.s_block_s);
                    MyFile.write((char *)&bpadre, sup.s_block_s);
                    added = true;
                    break;
                }
            }
            if (added)
            {
                break;
            }
        }
        else if (fs == -1)
        {
            fs = i;
        }
    }
    if (!added)
    {
        BloqueCarpetas nblock;
        for (int z = 0; z < 4; z++)
        {
            nblock.b_content[z].b_inodo = -1;
        }
        nblock.b_content[0].b_inodo = bnew.b_content[0].b_inodo;
        strcpy(nblock.b_content[0].b_name, bnew.b_content[0].b_name);
        ipadre.i_block[fs] = sup.s_first_blo;
        MyFile.seekp(sup.s_block_start + ipadre.i_block[fs] * sup.s_block_s);
        MyFile.write((char *)&nblock, sup.s_block_s);
        MyFile.seekp(sup.s_bm_block_start);
        for (int b = sup.s_bm_block_start; b < sup.s_inode_start; b++)
        {
            char ac = '0';
            MyFile.read((char *)&ac, sizeof(char));
            if (ac != '1')
            {
                sup.s_first_blo = (b - sup.s_bm_block_start);
                break;
            }
        };
        MyFile.seekp(sup.s_inode_start + bpadre.b_content[0].b_inodo * sup.s_inode_s);
        MyFile.write((char *)&ipadre, sup.s_inode_s);
    }
    inew.i_block[0] = sup.s_first_blo;
    MyFile.seekp(sup.s_bm_inode_start + sup.s_first_ino);
    MyFile.write("1", sizeof(char));
    MyFile.seekp(sup.s_bm_block_start + sup.s_first_blo);
    MyFile.write("1", sizeof(char));
    MyFile.seekp(sup.s_inode_start + sup.s_first_ino * sup.s_inode_s);
    MyFile.write((char *)&inew, sup.s_inode_s);
    MyFile.seekp(sup.s_block_start + sup.s_first_blo * sup.s_block_s);
    MyFile.write((char *)&bnew, sup.s_block_s);
    char ac = '1';
    int i;
    int b;
    MyFile.seekp(sup.s_bm_inode_start);
    for (i = sup.s_bm_inode_start; i < sup.s_bm_block_start; i++)
    {
        MyFile.read((char *)&ac, sizeof(char));
        if (ac != '1')
        {
            sup.s_first_ino = (i - sup.s_bm_inode_start);
            break;
        }
    };
    MyFile.seekp(sup.s_bm_block_start);
    for (b = sup.s_bm_block_start; b < sup.s_inode_start; b++)
    {
        MyFile.read((char *)&ac, sizeof(char));
        if (ac != '1')
        {
            sup.s_first_blo = (b - sup.s_bm_block_start);
            break;
        }
    };
    MyFile.seekp(part.part_start);
    MyFile.write((char *)&sup, sizeof(SuperBloque));
    MyFile.seekp(sup.s_block_start);
    BloqueCarpetas car;
    for (int i = 0; i < 10; i++)
    {
        MyFile.read((char *)&car, sup.s_block_s);
        cout << car.b_content[0].b_inodo << endl;
    }

    MyFile.close();
    return inew;
}

void MkDir(Inodo start, string dirpath, Partition part, string path)
{
    SuperBloque sup;
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(part.part_start);
    MyFile.read((char *)&sup, sizeof(SuperBloque));
    Inodo nt;
    int val;
    val = -1;
    if (dirpath.find('/') == string::npos)
    {
        BloqueCarpetas bl;
        MyFile.seekp(sup.s_block_start + start.i_block[0] * sup.s_block_s);
        MyFile.read((char *)&bl, sup.s_block_s);
        if (strcmp(bl.b_content[0].b_name, dirpath.c_str()) == 0)
        {
            return;
        }
        else
        {
            char pn[100];
            strcpy(pn, dirpath.c_str());
            NewDir(bl.b_content[0].b_inodo, bl.b_content[0].b_name, pn, 0, 0, path, part);
            return;
        }
    }

    string adir = dirpath.substr(0, dirpath.find('/'));
    for (int i = 0; i < 16; i++)
    {
        BloqueCarpetas ba;
        if (start.i_block[i] != -1)
        {
            MyFile.seekp(sup.s_block_start + start.i_block[i] * sup.s_block_s);
            MyFile.read((char *)&ba, sup.s_block_s);
            for (int j = 0; j < 4; j++)
            {
                if (ba.b_content[j].b_inodo != -1)
                {
                    if (strcmp(ba.b_content[j].b_name, adir.c_str()) == 0)
                    {
                        if (dirpath.find('/') == string::npos)
                        {
                            return;
                        }
                        else
                        {
                            MyFile.seekp(sup.s_inode_start + ba.b_content[j].b_inodo * sup.s_inode_s);
                            MyFile.read((char *)&nt, sup.s_inode_s);
                            val = 1;
                            break;
                        }
                    }
                }
            }
        }
        if (val != -1)
        {
            break;
        }
    }
    if (val != -1)
    {
        MkDir(nt, dirpath.substr(dirpath.find('/') + 1), part, path);
    }
    else
    {
        BloqueCarpetas blp;
        MyFile.seekp(sup.s_block_start + start.i_block[0] * sup.s_block_s);
        MyFile.read((char *)&blp, sup.s_block_s);
        char pn[100];
        strcpy(pn, adir.c_str());
        nt = NewDir(blp.b_content[0].b_inodo, blp.b_content[0].b_name, pn, 0, 0, path, part);
        MkDir(nt, dirpath.substr(dirpath.find('/') + 1), part, path);
    }
}

void AddDir(string dirpath, Partition part, string path)
{
    fstream MyFile;
    Inodo root;
    SuperBloque sup;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(part.part_start);
    MyFile.read((char *)&sup, sizeof(SuperBloque));
    MyFile.seekp(sup.s_inode_start);
    MyFile.read((char *)&root, sup.s_inode_s);
    if (dirpath.find('/') == 0)
    {
        int pos = dirpath.find('/');
        dirpath = dirpath.substr(1, dirpath.find(1, '/'));
    }
    MkDir(root, dirpath, part, path);
}

Inodo FindDir(char name[12], string path, Partition part, SuperBloque sup)
{
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    Inodo ia;
    Inodo ip;
    BloqueCarpetas bp;
    BloqueCarpetas ba;
    MyFile.seekp(sup.s_inode_start);
    MyFile.read((char *)&ia, sizeof(Inodo));
    MyFile.seekp(sup.s_block_start);
    MyFile.read((char *)&ba, sizeof(BloqueCarpetas));
    ip = ia;
    bp = ba;
    int i;
    int j;
    char *token = strtok(name, "/");
    while (token != NULL)
    {

        for (i = 1; i < 13; i++)
        {
            if (ia.i_block[i] != -1)
            {
                MyFile.seekp(sup.s_block_start + ia.i_block[i] * sup.s_block_s);
                MyFile.read((char *)&ba, sup.s_block_s);
                for (j = 0; j < 4; j++)
                {
                    if (ba.b_content[j].b_inodo != -1)
                    {
                        if (strcmp(token, ba.b_content[j].b_name) == 0)
                        {
                            break;
                        }
                    }
                    if (ba.b_content[j].b_inodo != -1)
                    {
                        break;
                    }
                }
            }
        }

        if (ba.b_content[j].b_name != token)
        {
            throw 404;
        }
        MyFile.seekp(sup.s_inode_start + sup.s_inode_s * ba.b_content[j].b_inodo);
        MyFile.read((char *)&ia, sup.s_inode_s);
        token = strtok(NULL, "/");
    };
    MyFile.close();
    return ia;
}

Partition FindPartition(string path, string name)
{
    fstream MyFile;
    struct Partition N;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = 0;
    struct MBR tm;
    char act;
    MyFile.read((char *)&tm, sizeof(struct MBR));
    if (tm.mbr_partition_1.part_status != 'N')
    {
        if (tm.mbr_partition_1.part_name == name)
        {
            return tm.mbr_partition_1;
        }
    }
    else if (tm.mbr_partition_2.part_status != 'N')
    {
        if (tm.mbr_partition_2.part_name == name)
        {
            return tm.mbr_partition_2;
        }
    }
    else if (tm.mbr_partition_3.part_status != 'N')
    {
        if (tm.mbr_partition_3.part_name == name)
        {
            return tm.mbr_partition_3;
        }
    }
    else if (tm.mbr_partition_4.part_status != 'N')
    {
        if (tm.mbr_partition_4.part_name == name)
        {
            return tm.mbr_partition_4;
        }
    }
    return N;
}

MBR ReadMBR(string path)
{
    fstream MyFile;
    struct Partition N;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i = 0;
    struct MBR tm;
    char act;
    MyFile.read((char *)&tm, sizeof(struct MBR));
    return tm;
}

int Partnum(string path, Partition Part)
{
    fstream MyFile;
    MBR mb;
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    mb = ReadMBR(path);
    if (strcmp(mb.mbr_partition_1.part_name, Part.part_name) == 0)
    {
        MyFile.close();
        return 1;
    }
    if (strcmp(mb.mbr_partition_2.part_name, Part.part_name) == 0)
    {
        MyFile.close();
        return 2;
    }
    if (strcmp(mb.mbr_partition_3.part_name, Part.part_name) == 0)
    {
        MyFile.close();
        return 3;
    }
    if (strcmp(mb.mbr_partition_4.part_name, Part.part_name) == 0)
    {
        MyFile.close();
        return 4;
    }
    return 0;
};

string addnodes(string path, Inodo in, SuperBloque sup)
{
    int id;
    string rep;
    string aux;
    fstream MyFile;
    BloqueCarpetas blo;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    MyFile.seekp(sup.s_block_start + in.i_block[0] * sup.s_block_s);
    MyFile.read((char *)&blo, sup.s_block_s);
    id = blo.b_content[0].b_inodo;
    rep = rep + "inodo";
    rep = rep + to_string(blo.b_content[0].b_inodo);
    rep = rep + "[label =<\n";
    rep = rep + "<TABLE bgcolor=\"#84E1E6\">\n ";
    rep = rep + "   <TR>\n";
    rep = rep + "       <TD PORT=\"I";
    rep = rep + to_string(blo.b_content[0].b_inodo);
    rep = rep + "\">";
    rep = rep + "Inodo ";
    rep = rep + to_string(blo.b_content[0].b_inodo);
    rep = rep + "</TD>\n";
    rep = rep + "   </TR>\n";
    for (int i = 0; i < 15; i++)
    {
        if (i < 12)
        {
            rep = rep + "   <TR>\n";
            rep = rep + "       <TD>Ap ";
            rep = rep + to_string(i);
            rep = rep + "</TD>\n";
            rep = rep + "       <TD PORT=\"A";
            rep = rep + to_string(i);
            rep = rep + "\">";
            rep = rep + to_string(in.i_block[i]);
            rep = rep + "</TD>\n";
            rep = rep + "   </TR>\n";
        }
        /*for (int j = 0; j < 4; j++)
            {
                MyFile.seekp(sup.s_block_start+in.i_block[i]*sup.s_block_s);
                MyFile.read((char*)&blo,sup.s_block_s);
                rep = rep + "   <TR>\n";
                rep = rep + "       <TD>";
                rep = rep + to_string(i);
                rep + rep + "</TD>\n";
                rep = rep + "       <TD PORT=\"A";
                rep = rep + to_string(i);
                rep = rep + "\">";
                rep = rep + to_string(in.i_block[i]);
                rep + rep + "</TD>\n";
                rep = rep + "   </TR>\n";
            }*/
    }
    rep = rep + "</TABLE>>];\n";
    for (int i = 0; i < 15; i++)
    {
        if (in.i_block[i] != -1)
        {
            if (i < 12)
            {
                rep = rep + "bloquecarpeta";
                rep = rep + to_string(in.i_block[i]);
                rep = rep + "[label =<\n";
                rep = rep + "<TABLE bgcolor=\"#E85240\">\n ";
                rep = rep + "   <TR>\n";
                rep = rep + "       <TD PORT=\"B";
                rep = rep + to_string(0);
                rep = rep + "\">";
                rep = rep + "Bloque Carpeta ";
                rep = rep + to_string(in.i_block[i]);
                rep = rep + "</TD>\n";
                rep = rep + "   </TR>\n";
                for (int j = 0; j < 4; j++)
                {
                    if (blo.b_content[j].b_inodo != -1)
                    {
                        /* MyFile.seekp(sup.s_block_start + in.i_block[j] * sup.s_block_s);
                         MyFile.read((char *)&blo, sup.s_block_s);*/
                        rep = rep + "   <TR>\n";
                        rep = rep + "       <TD>";
                        rep = rep + string(blo.b_content[j].b_name);
                        rep = rep + "</TD>\n";
                        rep = rep + "       <TD PORT=\"A";
                        rep = rep + to_string(i);
                        rep = rep + "\">";
                        rep = rep + to_string(blo.b_content[j].b_inodo);
                        rep = rep + "</TD>\n";
                        rep = rep + "   </TR>\n";
                        if (i == 0)
                        {
                            if ((blo.b_content[j].b_inodo != id) && j > 1)
                            {
                                Inodo next;
                                MyFile.seekp(sup.s_inode_start + blo.b_content[j].b_inodo * sup.s_inode_s);
                                MyFile.read((char *)&next, sup.s_inode_s);
                                aux = addnodes(path, next, sup);
                            }
                        }
                        else
                        {
                            if ((blo.b_content[j].b_inodo != id))
                            {
                                Inodo next;
                                MyFile.seekp(sup.s_inode_start + blo.b_content[j].b_inodo * sup.s_inode_s);
                                MyFile.read((char *)&next, sup.s_inode_s);
                                aux = addnodes(path, next, sup);
                            }
                        }
                    }
                }
                rep = rep + "</TABLE>>];\n";
            }
        }
    }
    rep += aux;
    return rep;
}

void ReportTree(string path, Partition part, SuperBloque sup)
{
    fstream MyFile;
    string graph = "digraph tree {\n";
    Inodo root;
    graph += "node[ shape = none, fontname = \"Arial\" ];\n";
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        MyFile.open(path, ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error &e)
    {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    char active;
    MyFile.seekp(sup.s_inode_start);
    MyFile.read((char *)&root, sup.s_inode_s);
    graph += addnodes(path, root, sup);
    graph += "}";
    ofstream Myfile("rept.dot");

    Myfile << graph;
    Myfile.close();
    string cmm = "dot -Tpng ";
    cmm += "rept.dot -o rept.png";
    int le = cmm.length();
    char cmp[le];
    strcpy(cmp, cmm.c_str());
    system(cmp);
}
