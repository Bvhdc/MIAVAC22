#include "./writting.h"

using namespace std;
struct Disco
{
    int size;
    char name[100];
    char path[100];
    char part_fit;
};
string tempname;

inline bool exists (const std::string& name) {
    ifstream f(name.c_str());
    return f.good();
}

struct MountedDisks
{
    string id;
    char path[100];
    int iid=0;
    char letter;
    Partition part;
    int lid=0;
};


list<MountedDisks> mounted;

/*void PrimerAjuste(string name,Partition part){
    fstream MyFile;
    MyFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
    MyFile.open(name,ios_base::binary | ios_base::out | ios_base::in);
    }
    catch (std::system_error& e) {
        std::clog << e.what() << " (" << e.code().value() << ")" << std::endl;
    }
    int i=0;
    int sp=0;
    MyFile.seekg(i);
    char act;
    MyFile.get(act);
    while (sp<part.part_size && act!=EOF)
    {
        if (act=="\0")
        {
            sp++;
        }else 
        {
            sp=0;
        }
        MyFile.get(act);
    }    
    MyFile.seekp(i-sizeof(char),std::ios_base::beg);
    MyFile.write((char*)&mbr,sizeof(struct MBR));
    MyFile.close();
};*/

int calcStructures(int size){
    float i=0;
    i=(size-sizeof(struct SuperBloque))/(1+sizeof(Journaling)+3+sizeof(Inodo)+3*sizeof(Bloque));
    int n=floor(i);
    return n;
}


/*string graphdisk(){
    string res="";
    res+="diagraph {";
    res+="\n";
    res+="node [shape=record];";
    res+="\n";
    res+="struct 3 [label=\"";
    res+= "MBR|{}"
}*/


void comandos(char *comando){
    char *token = strtok(comando," ");
    while (token != NULL)
    {
        if (strcasecmp(token,"mkdisk")==0)
        {
            struct Disco nwd;
            struct MBR nwt;
            int multiplier=1024*1024;
            time(&nwt.mbr_fecha_creacion);
            nwt.mbr_disk_signature=rand()%100;
            token=strtok(NULL," =");
            while(token != NULL){
                if (strcasecmp(token,">size")==0)
                {
                    token=strtok(NULL," ");
                    int s=atoi(token);
                    if(s>0){
                    nwd.size=s;
                    
                }
                }else
                if (strcasecmp(token,">path")==0)
                {
                    token=strtok(NULL," ");
                    string temp=string(token);
                    char* name=strrchr(token,'//')+1;
                    name=strtok(name,".");
                    string pth=temp.substr(0,temp.find(name));
                    int le=pth.length();
                    char cmp[le];
                    strcpy(cmp,pth.c_str());
                    strcpy(nwd.path,cmp);
                    strcpy(nwd.name,name);
                    DIR* dir = opendir(cmp);
                    if (dir)
                    {
                        
                        closedir(dir);
                    }
                    else if (ENOENT == errno)
                    {
                        string pth="mkdir -p "+string(nwd.path);
                        //string perm="chmod 755 "+temp;
                        int le=pth.length();
                      //  int lp=perm.length();
                        char cmp[le];
                     //   char crp[lp];
                        strcpy(cmp,pth.c_str());
                     //   strcpy(crp,perm.c_str());
                        const int dir_err = system(cmp);
                        //system(crp);
                        if (-1 == dir_err)
                        {
                            printf("Error creating directory!n");
                            exit(1);
                        }
                    }
                    else
                    {
                    
                    }        
                }else
                if (strcasecmp(token,">unit")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"K")==0){
                        multiplier=1;
                    }else
                    if(strcasecmp(token,"M")==0){
                        multiplier=1024;
                    }
                }else
                if (strcasecmp(token,">fit")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"BF")==0){
                        nwd.part_fit='B';
                    }else
                    if(strcasecmp(token,"FF")==0){
                        nwd.part_fit='F';
                    }else
                    if(strcasecmp(token,"WF")==0){
                        nwd.part_fit='W';
                    }
                }
                token=strtok(NULL," =");
            }
            string fname=string(nwd.path)+string(nwd.name)+".dsk\"";
            fname = fname.substr(0,fname.length()-1);
            nwd.size=nwd.size*multiplier;
            nwt.mbr_tamanio=nwd.size*multiplier;
            CreateDsk(fname,nwd.size);
            WriteMBR(fname,nwt);
            tempname=fname;
        }else
        if (strcasecmp(token,"rmdisk")==0)
        {
            token=strtok(NULL," =");
            while(token != NULL){
                if (strcasecmp(token,">path=")==0)
                {
                    token=strtok(NULL,"”");
                    string temp=string(token);
                    string pth="rm "+temp;
                    int le=pth.length();
                    char cmp[le];
                    strcpy(cmp,pth.c_str());
                    const int dir_err = system(cmp);
                    if (-1 == dir_err)
                    {
                        printf("Error deleting file !n");
                        exit(1);
                    }               
                }
                token=strtok(NULL," =");
            }
        }else
        if (strcasecmp(token,"mount")==0)
        {
            char path[100]="";
            struct Partition nwd;
            token=strtok(NULL,"=");
            while(token != NULL){
                if (strcasecmp(token,">path")==0)
                {
                    token=strtok(NULL," ");
                    string temp=string(token);
                    strcpy(path,token);
                    if (exists(path))
                    {
                    }else{
                        printf("Error Finding file !n");
                        exit(1);
                    }              
                }else
                if (strcasecmp(token,">name")==0)
                {
                    token=strtok(NULL," \n");
                    strcpy(nwd.part_name,token);
                }
                token=strtok(NULL," =");
            }
            if (strcasecmp(path,"")!=0&&strcasecmp(nwd.part_name,"")!=0)
            {
                Partition prt=FindPartition(path,nwd.part_name);
                auto match = std::find_if(mounted.cbegin(), mounted.cend(), [&path,&prt] (const MountedDisks& s) {
                return strcasecmp(s.path,path)==0;
                });
                if (match != mounted.cend()) {
                    MountedDisks nw;
                    nw.id="vd";
                    nw.iid=(match->iid)+1;
                    nw.lid=match->lid;
                    string i= to_string(nw.iid);
                    nw.id+=match->letter+i;
                    nw.letter=match->letter;
                    nw.part=prt;
                    strcpy(nw.path,path);
                    mounted.push_front(nw);
                }else{
                    MountedDisks nw;
                    nw.id="vd";
                    if (mounted.empty())
                    {
                        nw.iid=1;
                        nw.lid=97;
                    }else{
                        nw.iid=(mounted.begin()->iid)+1;
                        nw.lid=(mounted.begin()->lid)+1;
                    }
                    nw.letter=char(nw.lid);
                    strcpy(nw.path,path);
                    nw.part=prt;
                    string i= to_string(nw.iid);
                    nw.id+=nw.letter+i;
                    mounted.push_front(nw);
                }
            }else{
                for (auto i = mounted.begin(); i != mounted.end(); ++i)
                {
                    printf(i->id.c_str());
                    printf("\n");
                }
                
            }

        }else
        if (strcasecmp(token,"fdisk")==0)
        {
            struct Partition nwd;
            int multiplier=1024;
            char path[100];
            int modific=0;
            string delt="";
            token=strtok(NULL," =");
            while(token != NULL){
                if (strcasecmp(token,">size")==0)
                {
                    token=strtok(NULL," ");
                    int s=atoi(token);
                    if(s>0){
                        nwd.part_s=s;
                    }
                }else
                if (strcasecmp(token,">unit")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"B")==0){
                        multiplier=1;
                    }else
                    if(strcasecmp(token,"K")==0){
                        multiplier=1024;
                    }else
                    if(strcasecmp(token,"M")==0){
                        multiplier=1024*1024;
                    }
                }else
                if (strcasecmp(token,">path")==0)
                {
                    token=strtok(NULL," ");
                    string temp=string(token);
                    string pth=temp.substr(0,temp.find('"'));
                    int le=pth.length();
                    char cmp[le];
                    strcpy(cmp,pth.c_str());
                    strcpy(path,cmp);
                    if (exists(path))
                    {
                    }else{
                        printf("Error Finding file !n");
                        exit(1);
                    }              
                }else
                if (strcasecmp(token,">type")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"P")==0){
                        nwd.part_type='P';
                    }else
                    if(strcasecmp(token,"E")==0){
                        nwd.part_type='E';
                    }else
                    if(strcasecmp(token,"L")==0){
                        nwd.part_type='L';
                    }
                }else
                if (strcasecmp(token,">fit")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"BestFit")==0){
                        nwd.part_fit='B';
                    }else
                    if(strcasecmp(token,"FirstFit")==0){
                        nwd.part_fit='F';
                    }else
                    {
                        nwd.part_fit='W';
                    }
                }else
                if (strcasecmp(token,">delete")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"full")==0){
                        delt=string(token);
                    }else
                    if(strcasecmp(token,"fast")==0){
                        delt=string(token);
                    }
                }else
                if (strcasecmp(token,">name")==0)
                {
                    token=strtok(NULL," \n");
                    strcpy(nwd.part_name,token);
                }
                else
                if (strcasecmp(token,">add")==0)
                {
                    token=strtok(NULL," \n");
                    modific=atoi(token);
                    
                }/*else
                if (strcasecmp(token,"$mov=")==0)
                {
                    token=strtok(NULL," \n");
                }*/
                token=strtok(NULL," =");
            }
            nwd.part_s=nwd.part_s*multiplier;
            if (delt!="")
            {
                if (exists(path))
                {
                    DeletePart(nwd.part_name,path,delt);
                }
                
            }else{
                WritePartition(path,nwd);
            }
            
        }else
        if (strcasecmp(token,"rep")==0)
        {


            MBR tmm=ReadMBR(tempname);
            ReportDsk(tmm);
        }else
        if (strcasecmp(token,"execute")==0)
        {
            token=strtok(NULL," =");
            while(token != NULL){
                if (strcasecmp(token,">path")==0)
                {
                    token=strtok(NULL," ");
                    string temp=string(token);
                    if (exists(temp))
                    {
                        fstream newfile;
                        newfile.open(temp,ios::in); //open a file to perform read operation using file object
                        if (newfile.is_open()){   //checking whether the file is open
                            string tp;
                            while(getline(newfile, tp)){ //read data from file object and put it into string.
                                int le=tp.length();
                                char cmp[le];
                                strcpy(cmp,tp.c_str());
                                comandos(cmp);
                            }
                            newfile.close(); //close the file object.
                        }           
                    }else{
                        printf("Error Finding file !n");
                        exit(1);
                    }              
                }
            }
            
        }else
        if (strcasecmp(token,"mkfs")==0)
        {
            Partition nwd;
            int multiplier=1024;
            char* path;
            char type;
            int modific=0;
            string delt="";
            token=strtok(NULL," >");
            while(token != NULL){
                if (strcasecmp(token,">id=")==0)
                {
                    token=strtok(NULL," ");
                    
                    auto match = std::find_if(mounted.cbegin(), mounted.cend(), [&token] (const MountedDisks& s) {
                        char *idp;
                        strcpy(idp,s.id.c_str());
                        return strcasecmp(idp,token)==0;
                    });
                    if (match != mounted.cend()) {
                        nwd=match->part;
                        path=(char*)&match->path[0];
                }
                }else
                if (strcasecmp(token,">type=")==0)
                {
                    token=strtok(NULL," ");
                    if(strcasecmp(token,"Fast")==0){
                        type='f';
                    }else
                    if(strcasecmp(token,"Full")==0){
                        nwd.part_type='F';
                    }
                }else
                if (strcasecmp(token,">fs=")==0)
                {
                    token=strtok(NULL," ");
                }
                token=strtok(NULL," >");
            }
            int nst=calcStructures(nwd.part_s);
            FormatPartition(nwd,path,nst);
        }else{
            printf("Error");
        }

        token = strtok (NULL, " ");
    }
    
    
    
}


void consola(){
    char lineaComando[100];
    cout<<"Bryan Vladimir Hernandez Del Cid"<<endl;
    cout<<"201700672"<<endl;
    printf("Comando:= ");
    scanf(" %[^\n]s",lineaComando);
    comandos(lineaComando);
    consola();
}

int main(){
    consola();
    return 0;
}

