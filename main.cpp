#include<bits/stdc++.h>
#include<fstream>
using namespace std;


struct trienode{
struct trienode* children[26];
bool isEnd;
};

struct trienode* getNode()
{
    struct trienode* temp=new trienode;
    temp->isEnd=false;
    for(int i=0;i<26;i++)
        temp->children[i]=NULL;
    return temp;
}

void insert(struct trienode* root,string s)
{
    struct trienode* temp=root;
    for(int i=0;i<int(s.length());i++)
    {
        int idx=s[i]-'a';
        if(!temp->children[idx])
            temp->children[idx]=getNode();
        temp=temp->children[idx];
    }
    temp->isEnd=true;
}

bool search(struct trienode* root,string s)
{
    if(root==NULL)
        return false;
    struct trienode* temp=root;
    for(int i=0;i<int(s.length());i++)
    {
        int idx=s[i]-'a';
        if(!temp->children[idx])
            return false;
        temp=temp->children[idx];
    }
    return true;
}
bool isEmpty(struct trienode* root)
{
    for (int i=0;i<26;i++)
        if(root->children[i])
            return false;
    return true;
}
struct trienode* delete_key(struct trienode* root,string s,int depth=0)
{
    if(!root)
        return NULL;
    if(depth==int(s.size()))
    {
        if(root->isEnd)
            root->isEnd=false;
        if(isEmpty(root))
        {
            delete(root);
            root=NULL;
        }
        return root;
    }
    int idx=s[depth]-'a';
    root->children[idx]=delete_key(root->children[idx],s,depth+1);

    if(isEmpty(root) && root->isEnd==false)
    {
        delete(root);
        root=NULL;
    }
    return root;
}

void autocomplete(struct trienode* root,string s)
{
    if(s.size()==0||root==NULL)
        return;
    vector<string>words;
   struct trienode* temp=root;
    for(int i=0;i<int(s.length());i++)
    {
        int idx=s[i]-'a';
        if(temp->children[idx]==NULL)
            {
                cout<<"No words found"<<endl;
            }
        temp=temp->children[idx];
    }
    //bfs
     queue<pair<trienode*,string> > q;
     q.push(make_pair(temp,s));
     string w;
     while(!q.empty())
     {
     	temp = q.front().first;
     	w = q.front().second;
     	/* if this is word ,then add it to the all_words(vector) */
     	if(temp->isEnd)
            words.push_back( w );
     	q.pop();
     	for(int i=0;i<26;i++)
     	{
     		if( temp->children[i] !=NULL )
     		{
     			q.push( make_pair( temp->children[i] , w+char(i+int('a')) ) );
     		}
     	}
     }
    if(words.size()==0)
    {
        cout<<"No suggestions for the entered word"<<endl;
        return;
    }
    cout<<"Suggestions for the prefix "<<s<<" are\n";
    for(int i=0;i<words.size();i++)
    {
        if((i+1)%10==0)
            cout<<endl;
        cout<<words[i]<<" ";
    }
    return ;
}

int main()
{
      struct trienode* root=getNode();


    ifstream Inline("20k.txt");
    string mytext;
    while(getline(Inline,mytext))
    {
        insert(root,mytext);
    }

    insert(root,"vedada");
    insert(root,"vedant");
    cout<<"Enter word to autocomplete"<<endl;
    string ans;
    cin>>ans;
    autocomplete(root,ans);
    return 0;


}










