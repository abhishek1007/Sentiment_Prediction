#include<bits/stdc++.h>

using namespace std;

bool* sample(string,string,int,bool,bool*);

int main(int argc,char*argv[])
{
        srand(time(NULL));        
        bool* marked=new bool[25000];
        bool* marked2;
        bool* marked3;
        for(int i=0;i<25000;i++)
        {
                marked[i]=false;
        }
        marked2=sample(argv[1],argv[3],1000,false,marked);
        marked3=sample(argv[1],argv[3],1000,true,marked2);
        marked3=sample(argv[2],argv[3],1000,true,marked);
        
        
        
        ifstream fin;
        ofstream fout;
        string input_f,output_f;
        input_f=argv[4];
        output_f=argv[5];
        
        fin.open(input_f.c_str());
        fout.open(output_f.c_str());
        
        pair<float,int> words[89527];
        float val;
        int index=0;
        while(fin>>val)
        {
                
                words[index]=make_pair(val,index);
                index++;
        }
        sort(words,words+89527);
        
        
        int i=0;
        while(i<5000)
        {
                fout<<i<<"\n";
                i++;
        }
        
        
        
        
        fin.close();
        fout.close();
        return 0;
}

bool* sample(string in,string out,int samples,bool append,bool *marked)
{
        int posi=samples/2;
        ifstream fin;
        ofstream fout;
        
        string instance;
        
        fin.open(in.c_str());
        if(append)
        {
                fout.open(out.c_str(),ios_base::app);
        }
        else
        {
                fout.open(out.c_str());
        }
        
        int select_lines=0;
        
        bool pos_select[12500];
        memset(pos_select,false,sizeof(pos_select));
        
        bool neg_select[12500];
        memset(neg_select,false,sizeof(neg_select));
        
        int random;
        
        while(select_lines<posi)
        {
                random=rand()%12500;
                while(pos_select[random]==true || marked[random]==true)
                {
                        random=rand()%12500;
                }
                pos_select[random]=true;
                select_lines++;
        }
        
        select_lines=0;
        
        while(select_lines<posi)
        {
                random=rand()%12500;
                while(neg_select[random]==true || marked[random+12500]==true)
                {
                        random=rand()%12500;
                }
                neg_select[random]=true;
                select_lines++;
        }
        
        int line1=0,line2=0;
        int selected=0;
        
        
        
        line2=0;
        int k=0;
        
        
        selected=0;
        while(line1<12500 && selected<500 && getline(fin,instance) )
        {
                if(pos_select[line1])
                {
                       fout<<instance<<"\n"; 
                       selected++;
                }
                line1++;
        }
        
        while(line1<12500)
        {
                getline(fin,instance);
                line1++;
        }
        
        
        selected=0;
        while(line2<12500 && selected<500 && getline(fin,instance))
        {
                if(neg_select[line2])
                {
                       fout<<instance<<"\n"; 
                       selected++;
                }
                line2++;
        }
        
        
        fin.close();
        fout.close();
        
        bool *ret=new bool[25000];
        for(int i=0;i<12500;i++)
        {
                ret[i]=pos_select[i];
        }
        for(int i=0;i<12500;i++)
        {
                ret[i+12500]=neg_select[i];
        }
        return ret;
        
}


