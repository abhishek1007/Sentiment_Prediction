#include<bits/stdc++.h>

using namespace std;

int max_accuracy=0;

struct node{
node* left;
node* right;
bool label;
int attribute;
bool majority;
};

vector<int> words_index;

int n_nodes=0;
int l_nodes=0;
int recur=0;
int maxd=0;

int InfoGain(vector<int>,vector<int>,int**);
int accuracy(node*,int**);
void prune_tree(node*,node*,int**);

node* ID3_1(vector<int>,vector<int>,int**,float threshhold);
bool find(node*,int**,int);
double find_accuracy(node*,int**);
void corrupt(int**,int**,float);
float df_accuracy(node*[],int**,int);
void freq_attributes(node*[]);
void bfs(node* node,vector< pair<int,int> >& att);

int main(int argc,char*argv[])
{
        string t_file2,t_file;
        
        srand(time(NULL));
        vector<int> attributes;
        vector<int> examples;
        int line=0,tag,num,i,siz,word,word_count;
        
        map<int,int> words;
        int** reviews;
        int** validation_data;
        int** test_data;
        int** cor_reviews;
        
        reviews=new int*[1000];
        
        for(i=0;i<1000;i++)
        {
                reviews[i]=new int[5001];
        }
        
        test_data=new int*[1000];
        
        
        for(i=0;i<1000;i++)
        {
                test_data[i]=new int[5001];
        }
        
        validation_data=new int*[1000];
        
        
        for(i=0;i<1000;i++)
        {
                validation_data[i]=new int[5001];
        }
        
        cor_reviews=new int*[1000];
        
        for(i=0;i<1000;i++)
        {
                cor_reviews[i]=new int[5001];
        }
        
        for(int p=0;p<1000;p++)
        {
                for(int q=0;q<1000;q++)
                {
                        test_data[p][q]=0;
                        reviews[p][q]=0;
                        validation_data[p][q]=0;
                }
        }
        
        
        t_file="../selectedfeatures.feat";
        ifstream fin,fin2;
        
        // Making a map of the word number and its corresponding column number in the matrix
        
        fin.open(t_file.c_str());
        
        i=0;
        
        
        while(fin>>word)
        {
            words[word]=i;
            attributes.push_back(i);
            words_index.push_back(word);
            i++;    
        }
        
        
        // Making the matrix
        
        t_file2=argv[1];
        fin2.open(t_file2.c_str());
        string review;
        int tag_n=0;
        line=0;
        while(line<1000 && getline(fin2,review))
        {
                examples.push_back(line);
                
                i=0;
        
                tag=1;
                if(review[0]<='4' && !(review[i]=='1' && review[i+1]=='0'))
                {
                        tag=0;
                        tag_n++;
                }
                
                if(review[i+1]='0')
                {
                        i++;
                }
                
                reviews[line][5000]=tag;
                
                i=i+2;
                siz=review.length();
              
              
                while(i<siz)
                {
                        
                        word=0;
                        word_count=0;
                        
                        while(i!=siz && review[i]!=':')
                        {
                                word=word*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
                        
                        while(i!=siz && review[i]!=' ')
                        {
                                word_count=word_count*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
     
                        if(words.find(word)!=words.end())
                        {
                                reviews[line][words[word]]=word_count;
                        }
                }
                
                line++;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////
        
        line=0;
        tag_n=0;
        while(line<1000 && getline(fin2,review))
        {
                
                i=0;
        
                tag=1;
                if(review[0]<='4' && !(review[i]=='1' && review[i+1]=='0'))
                {
                        tag=0;
                        tag_n++;
                        
                }
                
                if(review[i+1]='0')
                {
                        i++;
                }
                
                validation_data[line][5000]=tag;
                
                i=i+2;
                siz=review.length();
              
              
                while(i<siz)
                {
                        
                        word=0;
                        word_count=0;
                        
                        while(i!=siz && review[i]!=':')
                        {
                                word=word*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
                        
                        while(i!=siz && review[i]!=' ')
                        {
                                word_count=word_count*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
     
                        if(words.find(word)!=words.end())
                        {
                                validation_data[line][words[word]]=word_count;
                        }
                }
                
                line++;
        }
        
        
        ///////////////////////////////////////////////////////////////////////////////////////
        
        
        line=0;
        tag_n=0;
        while(line<1000 && getline(fin2,review))
        {
                
                i=0;
        
                tag=1;
                if(review[0]<='4' && !(review[i]=='1' && review[i+1]=='0'))
                {
                        tag=0;
                        tag_n++;
                        
                }
                
                if(review[i+1]='0')
                {
                        i++;
                }
                
                test_data[line][5000]=tag;
                
                i=i+2;
                siz=review.length();
              
              
                while(i<siz)
                {
                        
                        word=0;
                        word_count=0;
                        
                        while(i!=siz && review[i]!=':')
                        {
                                word=word*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
                        
                        while(i!=siz && review[i]!=' ')
                        {
                                word_count=word_count*10+(review[i]-'0');
                                i++;
                        }
                        
                        i++;
     
                        if(words.find(word)!=words.end())
                        {
                                test_data[line][words[word]]=word_count;
                        }
                }
                
                line++;
        }
        
        
        
        
        ////////// ALL THE THREE DATA SETS HAVE BEEN PREPARED  ////////////////////////////////
        
        int ch;
        string choice;
        choice=argv[2];
        ch=atoi(choice.c_str());
        cout<<"You have chosen Experiment "<<ch<<"\n";

        
        if(ch==2)
        {
                
                
                cout<<"\n\nOrignal Decision Tree\n";
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                
                
                cout<<"\n\nDecision tree with Threshhold : 0.9\n";
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root1;
                root1=ID3_1(examples,attributes,reviews,0.9);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root1,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root1,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root1,test_data);
                
                
                
                cout<<"\n\nDecision tree with Threshhold : 0.8\n";
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root2;
                root2=ID3_1(examples,attributes,reviews,0.8);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root2,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root2,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root2,test_data);
                
                
                
                cout<<"\n\nDecision tree with Threshhold : 0.7\n";
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root3;
                root3=ID3_1(examples,attributes,reviews,0.7);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root3,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root3,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root3,test_data);
                
                
                node* trees[4];
                trees[0]=root;
                trees[1]=root1;
                trees[2]=root2;
                trees[3]=root3;
                cout<<"\n\n\nMost commonly used attributes with their index in the vocab file:\n\n";
                freq_attributes(trees);
                
        }
        
        
        else if(ch==3)
        {
                
                
                cout<<"\n\n0.5% Corruption of data\n";
                corrupt(reviews,reviews,0.5);
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                
                
                cout<<"\n\n1.0% Corruption of data\n";
                corrupt(reviews,reviews,1.0);
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                root=NULL;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                
                
                cout<<"\n\n5.0% Corruption of data\n";
                corrupt(reviews,reviews,5.0);
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                root=NULL;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                
                
                cout<<"\n\n10.0% Corruption of data\n";
                corrupt(reviews,reviews,10.0);
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                root=NULL;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                
        }
        
        else if(ch==4)
        {
                
                
                cout<<"\n\nTree before Pruning\n";
                n_nodes=0;
                l_nodes=0;
                maxd=0;
                node* root;
                root=ID3_1(examples,attributes,reviews,1.0);
                cout<<"\nNUMBER of Nodes in the Tree: "<<n_nodes<<"\n";
                cout<<"\nNUMBER of leaf Nodes in the Tree: "<<l_nodes<<"\n";
                cout<<"\nDepth: "<<maxd<<"\n";
                
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                
                      
                cout<<"\n";                
                //max_accuracy=accuracy(root,validation_data);
                //cout<<max_accuracy<<" Orignal accuracy\n";

                prune_tree(root,root,validation_data);
                
                //cout<<max_accuracy<<" New accuracy\n";
                
                cout<<"\n\nTree after Pruning\n"; 
                cout<<"\nTraining set\n";
                find_accuracy(root,reviews);
                cout<<"\nValidation set\n";
                find_accuracy(root,validation_data);
                cout<<"\nTesting set\n";
                find_accuracy(root,test_data);
                

                
                     
        }
        
        else if(ch==5)
        {
                int n_attributes;
                int n_trees;
                                
                vector<int> sel_attributes;                
                bool atts[5000];
                
                
                /////////////////////////////////////////////////////////////////////////////
                
                n_attributes=500;
                n_trees=50;
                cout<<"\nNumber of trees: "<<n_trees<<"\n";
                cout<<"\nAtributes used per tree: "<<n_attributes<<"\n";
                node* trees[n_trees];

                cout<<"\nForming "<<n_trees<<" trees...\n\n";
                for(int i=0;i<n_trees;i++)
                {
                        memset(atts,false,sizeof(atts));
                        int k=0;
                        
                        while(k<n_attributes)
                        {
                                int pos=rand()%5000;
                                while(atts[pos])
                                {
                                        pos=rand()%5000;
                                }
                                atts[pos]=true;
                                sel_attributes.push_back(pos);
                                k++;
                        }
                        trees[i]=ID3_1(examples,sel_attributes,reviews,1.0);
                        while(!sel_attributes.empty())
                        {
                                sel_attributes.pop_back();
                        }
                        
                }
                
                cout<<"\nTraining Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees,reviews,n_trees)<<"\n";
                                
                cout<<"\nValidation Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees,validation_data,n_trees)<<"\n";
                
                cout<<"\nTesting Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees,test_data,n_trees)<<"\n";
                
                /////////////////////////////////////////////////////////////////////////
                
                n_attributes=500;
                n_trees=100;
                cout<<"\nNumber of trees: "<<n_trees<<"\n";
                cout<<"\nAtributes used per tree: "<<n_attributes<<"\n";
                node* trees1[n_trees];
                cout<<"\nForming "<<n_trees<<" trees...\n\n";
                
                for(int i=0;i<n_trees;i++)
                {
                        memset(atts,false,sizeof(atts));
                        int k=0;
                        
                        while(k<n_attributes)
                        {
                                int pos=rand()%5000;
                                while(atts[pos])
                                {
                                        pos=rand()%5000;
                                }
                                atts[pos]=true;
                                sel_attributes.push_back(pos);
                                k++;
                        }
                        trees1[i]=ID3_1(examples,sel_attributes,reviews,1.0);
                        while(!sel_attributes.empty())
                        {
                                sel_attributes.pop_back();
                        }
                        
                }
                
                cout<<"\nTraining Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees1,reviews,n_trees)<<"\n";
                                
                cout<<"\nValidation Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees1,validation_data,n_trees)<<"\n";
                
                cout<<"\nTesting Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees1,test_data,n_trees)<<"\n";
                
                /////////////////////////////////////////////////////////////////////////
                
                n_attributes=500;
                n_trees=200;
                cout<<"\nNumber of trees: "<<n_trees<<"\n";
                cout<<"\nAtributes used per tree: "<<n_attributes<<"\n";
                node* trees2[n_trees];
                cout<<"\nForming "<<n_trees<<" trees...\n\n";
                
                for(int i=0;i<n_trees;i++)
                {
                        memset(atts,false,sizeof(atts));
                        int k=0;
                        
                        while(k<n_attributes)
                        {
                                int pos=rand()%5000;
                                while(atts[pos])
                                {
                                        pos=rand()%5000;
                                }
                                atts[pos]=true;
                                sel_attributes.push_back(pos);
                                k++;
                        }
                        trees2[i]=ID3_1(examples,sel_attributes,reviews,1.0);
                        while(!sel_attributes.empty())
                        {
                                sel_attributes.pop_back();
                        }
                        
                }
                
                cout<<"\nTraining Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees2,reviews,n_trees)<<"\n";
                                
                cout<<"\nValidation Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees2,validation_data,n_trees)<<"\n";
                
                cout<<"\nTesting Set\n";
                cout<<"Accuracy: "<<df_accuracy(trees2,test_data,n_trees)<<"\n";
                
                /////////////////////////////////////////////////////////////////////////    
                
        }
        
        return 0;
}

void freq_attributes(node* trees[])
{
        vector< pair<int,int> > attributes;
        for(int i=0;i<4;i++)
        {
                bfs(trees[i],attributes);
        }
        sort(attributes.begin(),attributes.end());
        for(int i=attributes.size()-1;i>=0;i--)
        {
                cout<<words_index[attributes[i].second]<<" : "<<attributes[i].first<<"\n";
        }
}

void bfs(node* node,vector< pair<int,int> >& att)
{
        if(node->left!=NULL)
        {
                bfs(node->left,att);
        }
        
        if(node->left!=NULL && node->right!=NULL)
        {
                int find=-1;
                int siz=att.size();
                for(int i=0;i<siz;i++)
                {
                        if(node->attribute==att[i].second)
                        {
                                att[i].first=att[i].first+1;
                                find=i;
                        }
                }
                if(find==-1)
                {
                        att.push_back(make_pair(1,node->attribute));
                }
        }
        
        if(node->right!=NULL)
        {
                bfs(node->right,att);
        }
}

float df_accuracy(node* trees[],int** test_data,int n_trees)
{
        int posi=0,negi=0;
        bool result;
        int ac_result;
        int t=0;
        for(int i=0;i<1000;i++)
        {
                negi=0;
                posi=0;
                for(int j=0;j<n_trees;j++)
                {
                        result=find(trees[j],test_data,i);
                        if(result)
                        {
                                posi++;
                        }
                        else
                        {
                                negi++;
                        }       
                }
                if(posi>=negi)
                {
                        ac_result=1;
                }
                else
                {
                        ac_result=0;
                }
                if(ac_result==test_data[i][5000])
                {
                        t++;
                }
        }
        float ans=float(t)/10.0;
        return ans;
        

}

void corrupt(int** reviews,int** cor_reviews,float per)
{
        int n_corrupt=(per*10);
        //cout<<n_corrupt<<" corrupted number\n";
        bool cor[1000];
        memset(cor,false,sizeof(cor));
        int k=0;
        int pos;
        while(k<n_corrupt)
        {
                pos=rand()%1000;
                while(cor[pos])
                {
                        pos=rand()%1000;
                }
                cor[pos]=true;
                k++;
        }
        for(int j=0;j<1000;j++)
        {
                for(int k=0;k<5001;k++)
                {
                        cor_reviews[j][k]=reviews[j][k];
                }
                if(cor[j])
                {
                        if(reviews[j][5000]==0)
                        {
                                cor_reviews[j][5000]=1;
                        }
                        else
                        {
                                cor_reviews[j][5000]=0;
                        }
                }
        }
}


double find_accuracy(node* root,int** test_data)
{
        int t1=0,t2=0,t=0,f=0,att;
        node* n;
        for(int i=0;i<1000;i++)
        {
                n=root;
                while(n->left!=NULL || n->right!=NULL)
                {
                        att=n->attribute;
                        if(test_data[i][att]>0)
                        {
                                n=n->left;
                        }
                        else
                        {
                                n=n->right;
                        }
                }
                if(n->label==true && test_data[i][5000]==1)
                {
                        t1++;
                }
                else if(n->label==false && test_data[i][5000]==0)
                {
                        t2++;
                }      
                if(n->label==true)
                {
                        t++;
                } 
                else if(n->label==false)
                {
                        f++;
                }
        }
        
        
        
        //cout<<t<<" "<<f<<" "<<t1<<" "<<t2<<" counts\n";
        cout<<"Accuracy: "<<(t1+t2)/10.0<<"\n";
        return (t1+t2)/10.0;
                       
}

void prune_tree(node* root,node* cur,int** test_data)
{
        node* temp=new node;
        temp->left=cur->left;
        temp->right=cur->right;
        temp->label=cur->label;
        temp->majority=cur->majority;
        temp->attribute=cur->attribute;
        int accu;
        if(cur->left!=NULL)
        {
                prune_tree(root,cur->left,test_data);
        }
        if(cur->right!=NULL)
        {
                prune_tree(root,cur->right,test_data);
        }
        
        
        if(cur==root)
        {
                // do nothing
        }
        else if(cur->left!=NULL && cur->right!=NULL)
        {
                cur->left=NULL;
                cur->right=NULL;
                cur->label=cur->majority;
                accu=accuracy(root,test_data);
                if(accu<max_accuracy)
                {
                        cur->left=temp->left;
                        cur->right=temp->right;
                        cur->label=temp->label;
                        cur->attribute=temp->attribute;
                }
                else
                {
                        max_accuracy=accu;
                }
        }
}
bool find(node* root,int** test_data,int i)
{
        node* n=root;
        int att;
        while(n->left!=NULL && n->right!=NULL)
        {
                att=n->attribute;
                if(test_data[i][att]>0)
                {
                        n=n->left;
                }
                else
                {
                        n=n->right;
                }
        }
        return n->label;
        
}

int accuracy(node* root,int** test_data)
{
        node* n;
        int t1=0,t2=0;
        int att;
        for(int i=0;i<1000;i++)
        {
                n=root;
                while(n->left!=NULL && n->right!=NULL)
                {
                        att=n->attribute;
                        if(test_data[i][att]>0)
                        {
                                n=n->left;
                        }
                        else
                        {
                                n=n->right;
                        }
                }
                if(n->label==true && test_data[i][5000]==1)
                {
                        t1++;
                }
                else if(n->label==false && test_data[i][5000]==0)
                {
                        t2++;
                }      
                
        }
        return t1+t2;
        
}

float entropy(vector<int> examples,int att,int**reviews)
{
        double zero_positive=0,zero_negative=0;
        double other_positive=0,other_negative=0;
        double siz=examples.size();
        double zero=0,other=0;
        double e1=0,e2=0,p1=0,p2=0;

        
        for(int i=0;i<siz;i++)
        {
                if(reviews[examples[i]][att]>0)
                {
                        if(reviews[examples[i]][5000]==1)
                        {
                                other_positive++;
                        }
                        else
                        {
                                other_negative++;
                        }
                        other++;
                }
                else
                {
                        if(reviews[examples[i]][5000]==1)
                        {
                                zero_positive++;
                        }
                        else
                        {
                                zero_negative++;
                        }
                        zero++;
                }
        }
                
        if(other_positive==0 || other_negative==0)
        {
                e2=0;
        }
        else
        {
                p1=other_positive/other;
                p2=other_negative/other;
                e2=p1*log2(p1)+p2*log2(p2);
                e2=(-1)*e2;

        }
                
        if(zero_positive==0 || zero_negative==0)
        {
                e1=0;
        }
        else
        {
                p1=zero_positive/zero;
                p2=zero_negative/zero;
                e1=p1*log2(p1)+p2*log2(p2);
                e1=(-1)*e1;

        }
        double ans=e1*(zero/siz)+e2*(other/siz);
        
}

int InfoGain(vector<int> attributes,vector<int> examples,int**reviews)
{
        
        double n_posi=0,n_negi=0;
        double siz=examples.size();
        double lm,mr;
        double b1=0,b2=0,b3=0;
        double p1,p2,p3,ig=0;
        
        double mini=1000;
        int minia=-1,att;
        int siz2=attributes.size();
        
        for(int a=0;a<siz2;a++)
        {
                
                
                b1=0;
                b2=0;
                att=attributes[a];
                        
                double zero_positive=0,zero_negative=0;
                double other_positive=0,other_negative=0;
                double siz=examples.size();
                double zero=0,other=0;
                double e1=0,e2=0,p1=0,p2=0;
                
                
                for(int i=0;i<siz;i++)
                {
                        if(reviews[examples[i]][att]>0)
                        {
                                if(reviews[examples[i]][5000]==1)
                                {
                                        other_positive++;
                                }
                                else
                                {
                                        other_negative++;
                                }
                                other++;
                        }
                        else
                        {
                                if(reviews[examples[i]][5000]==1)
                                {
                                        zero_positive++;
                                }
                                else
                                {
                                        zero_negative++;
                                }
                                zero++;
                        }
                }
                        
                if(other_positive==0 || other_negative==0)
                {
                        e2=0;
                }
                else
                {
                        p1=other_positive/other;
                        p2=other_negative/other;
                        e2=p1*log2(p1)+p2*log2(p2);
                        e2=(-1)*e2;
                }
                        
                if(zero_positive==0 || zero_negative==0)
                {
                        e1=0;
                }
                else
                {
                        p1=zero_positive/zero;
                        p2=zero_negative/zero;
                        e1=p1*log2(p1)+p2*log2(p2);
                        e1=(-1)*e1;
                }
                
                
                
                double ans=e1*(zero/siz)+e2*(other/siz);
                
                ig=ans;
                
                if(ig<mini)
                {
                        mini=ig;
                        minia=att;
                }
              
        }
        return minia;
}

node* ID3_1(vector<int> examples,vector<int> attributes,int**reviews,float threshhold)
{
        recur++;
        
        
        if(recur>maxd)
        {
                maxd=recur;
        }
        
        int n_posi=0,n_negi=0;
        int siz=examples.size();
        for(int i=0;i<siz;i++)
        {
        
                if(reviews[examples[i]][5000]==0)              // positive example
                {
                        n_negi++;
                }
                else                                           // negative example
                {
                        n_posi++;
                }
                  
        }
        
        double pp,pn;
        pp=double(n_posi)/siz;
        pn=double(n_negi)/siz;
        
        if(pp>=threshhold || pn>=threshhold)
        {
                node* root;
                if(pn>=threshhold)
                {
                        root=new node;
                        root->left=NULL;
                        root->right=NULL;
                        root->label=false;
                        root->majority=false;
                }
                else if(pp>=threshhold)
                {
                        root=new node;
                        root->left=NULL;
                        root->right=NULL;
                        root->label=true;
                        root->majority=true;
                }
                l_nodes++;
                
                recur--;
                n_nodes++;
                
                return root;        
        }
        
        if(n_posi==0 || n_negi==0)
        {
                node* root;
                
                if(n_negi==0)
                {
                        root=new node;
                        root->left=NULL;
                        root->right=NULL;
                        root->label=true;
                        root->majority=true;
                }
                else if(n_posi==0)
                {
                        root=new node;
                        root->left=NULL;
                        root->right=NULL;
                        root->label=false;
                        root->majority=false;
                }
                recur--;
                n_nodes++;
                l_nodes++;
                return root;
        }
        if(attributes.size()==0)
        {
                node* root=new node;
                if(n_posi>=n_negi)
                {
                        root->label=true;
                        root->majority=true;
                }
                else
                {
                        root->label=false;
                        root->majority=false;
                }
                root->left=NULL;
                root->right=NULL;
                recur--;
                n_nodes++;
                l_nodes++;
                return root;
                
        }
        int attribute;
        
        attribute=InfoGain(attributes,examples,reviews);
        node* root=new node;
        n_nodes++;
        root->attribute=attribute;
        
        if(n_posi>n_negi)
        {
                root->majority=true;
        }
        else
        {
                root->majority=false;
        }
        
        attributes.erase(remove(attributes.begin(),attributes.end(),attribute),attributes.end());
        
        
        vector<int> examples_1,examples_2;
        siz=examples.size();
        
        for(int i=0;i<siz;i++)
        {
        
                if(reviews[examples[i]][attribute]>0)
                {
                        examples_1.push_back(examples[i]);
                } 
                else
                {
                        examples_2.push_back(examples[i]);
                }      
        }
        
        if(!examples_1.empty())
        {
                root->left=ID3_1(examples_1,attributes,reviews,threshhold);
        }
        else
        {
                if(n_posi>n_negi)
                {       
                        root->left=new node;
                        (root->left)->label=true;
                        (root->left)->majority=true;
                        (root->left)->left=NULL;
                        (root->left)->right=NULL;
                }
                else
                {
                        root->left=new node;
                        (root->left)->label=false;
                        (root->left)->majority=false;
                        (root->left)->left=NULL;
                        (root->left)->right=NULL;
                }
                l_nodes++;
                n_nodes++;
        }
        if(!examples_2.empty())
        {
                root->right=ID3_1(examples_2,attributes,reviews,threshhold);
        }
        else
        {
                if(n_posi>n_negi)
                {       
                        root->right=new node;
                        (root->right)->label=true;
                        (root->right)->majority=true;
                        (root->right)->left=NULL;
                        (root->right)->right=NULL;
                }
                else
                {
                        root->right=new node;
                        (root->right)->label=false;
                        (root->right)->majority=false;
                        (root->right)->left=NULL;
                        (root->right)->right=NULL;
                }
                n_nodes++;
                l_nodes++;
        }
        
        recur--;
	return root;
}

