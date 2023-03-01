#ifndef PLAYER_H    // To make sure you don't declare the function more than once by including the header multiple times.
#define PLAYER_H

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <dirent.h>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <system_error>
#include <ctime>
#include <iostream>
#include <list>
#include <map>
#include <cmath>
using namespace std;

struct EBR 
{
    char part_status='N';
    char part_fit;
    int part_start=0;
    int part_s=0;
    int part_next=-1;
    char part_name[16]="";
};

struct Partition
{
    char part_status='N';
    char part_type;
    char part_fit;
    int part_start=0;
    int part_s=0;
    char part_name[16]="";
};

struct Bloque {
    char nombre[15];
    char informacion[50];
};

struct SuperBloque {
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    time_t s_mtime;
    time_t s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_s;
    int s_block_s;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
};

struct Journaling {
    string Journal_tipo_operacion;
    int Journal_tipo;
    string Journal_nombre;
    string Journal_contenido;
    time_t Journal_fecha;
    string Journal_propietario;
    string Journal_Permisos;
};

struct Inodo {
    int i_uid;
    int I_gid;
    int i_s;
    time_t i_atime;
    time_t i_ctime;
    time_t i_mtime;
    int i_block[16];
    char i_type;
    int i_perm;
};

struct Content{
    char b_name[12];
    int b_inodo;
};

struct PointerBlock{
    int b_pointers[16];
};

struct ABlock{
    char b_content[64];
};

struct BloqueCarpetas{
    Content b_content[4];
};

struct MBR
{
    int mbr_tamanio;
    time_t mbr_fecha_creacion;
    int mbr_disk_signature;
    Partition mbr_partition_1;
    Partition mbr_partition_2;
    Partition mbr_partition_3;
    Partition mbr_partition_4;
};
int Partnum(string path, Partition Part);
Partition FindPartition(string path,string name);
Inodo FindDir(char name[12],string path,Partition part,SuperBloque sup);
void NewDir(int padre, char *pname, char *name, int uid, int gid, string path, SuperBloque sup,Partition part);

void CreateDsk(string name,int size);

void ReportDsk(MBR tmm);

void WriteMBR(string name,MBR mbr);
MBR ReadMBR(string path);
int DeletePart(string name,string path,string ty);
int WritePartition(string name,Partition part);
Partition FindPartition(string path,string name);
void FormatPartition(Partition part,string path,int n);

#endif