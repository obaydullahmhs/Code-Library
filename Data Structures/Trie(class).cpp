class Trie{
public:
    struct Node{
        Node* ar[26];
        bool endmark;
        Node(){
            endmark=false;
            for(int i=0; i<26; i++) ar[i]=NULL;
        }
    };
    Node* root;
    Trie(){
        root=new Node();
    }
    void Insert(const string& s){
        Node* cur=root;
        for(int i=0; i<s.size(); i++){
            int ascii=s[i]-'a';
            if(cur->ar[ascii]==NULL) cur->ar[ascii]=new Node();
            cur=cur->ar[ascii];
        }
        cur->endmark=true;
    }
    bool Search(const string& s){
        Node* cur=root;
        for(int i=0; i<s.size(); i++){
            int ascii=s[i]-'a';
            if(cur->ar[ascii]==NULL) return 0;
            cur=cur->ar[ascii];
        }
        return cur->endmark;
    }
    void Del(Node* cur)
    {
        for(int i=0; i<26; i++){
            if(cur->ar[i]!=NULL) Del(cur->ar[i]);
        }
        delete(cur);
    }
    void Delete(){
        Del(root);
    }
}trie;
