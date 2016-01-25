#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int found=0,len=-1;

class node{
    public:
        char info;
        string Word;
        class node* ptrs[256];
        node(){
            for(int i=0;i<256;i++){
                ptrs[i]=NULL;
            }
            info=NULL;
            Word="";
        }
};

void insertword(string word,int pos,class node * root){
    if(word.length()==pos){
        root->Word=word;
        return;
    }
    if( root-> ptrs[word[pos]]==NULL ){
        node *newnode;
        newnode= new node;
        newnode->info=word[pos];
        root->ptrs[word[pos]]=newnode;
        insertword(word,pos+1,root->ptrs[word[pos]]);
    }
    else
        insertword(word,pos+1,root->ptrs[word[pos]]);
}

/*void find(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL))
        find(key,pos+1,root->ptrs[key[pos]]);
    else if(key==root->Word){
        cout<<"The spelling of the word '"<<root->Word<<"' is correct"<<endl;
        found=1;
    }
}
*/
void printall(class node * root){
    for(int i=0;i<256;i++)
        if(root->ptrs[i]!=NULL){
            printall(root->ptrs[i]);
        }
    if(root->Word != "" && (root->Word.length()==len && len!=-1))
        cout<<" -> "<<root->Word<<endl;
    else if(root->Word != "" && len==-1)
    {
    	cout<<" -> "<<root->Word<<endl;
    	found=1;
    }
    
}

void suggest(string key,int pos, class node * root){
    if((key != root->Word) && (root->ptrs[key[pos]] != NULL)){
            suggest(key,pos+1,root->ptrs[key[pos]]);
    }
    else{
            printall(root);
    }
}

int main(){
    ifstream in("wordlist.txt");
    string word,current="",key;
    char ch;
    node *root;
    root = new node;
    while(in){
        in>>word;
        insertword(word,0,root);
    }
    in.close();
    cout<<endl<<"Trie Construction Successful"<<endl;
    //printall(root);
    cout<<"Enter the starting letters of the word : ";
    cin>>key;
    cout<<"Do you know the length of the word?(y/n)";
    cin>>ch;
    if(ch=='y')
    {
    	cout<<"Enter the length\n";
    cin>>len;
	}
//    find(key,0,root);
//    if(!found){
        cout<<endl<<"Possible suggestions are :"<<endl;
        suggest(key,0,root);
        if(found)
        {
        	cout<<"No words of specified length found";
        }
//    }
    return 0;
}

