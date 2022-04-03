class Trie {
public:
    /** Initialize your data structure here. */
    vector<Trie*> nxt;
    char st;
    bool isend;
    /** st is the first char in charset, size is the sizeof charset */
    Trie(char st='a',int size=26):st(st),nxt(size,nullptr),isend(false){
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        Trie* now=this;
        for(char c:word){
            int x=c-st;
            if(now->nxt[x]==nullptr){
                now->nxt[x]=new Trie();
            }
            now=now->nxt[x];
        }
        now->isend=true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        Trie* now=this;
        for(char c:word){
            int x=c-st;
            if(now->nxt[x]==nullptr){
                return false;
            }
            now=now->nxt[x];
        }
        return now->isend;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        Trie* now=this;
        for(char c:prefix){
            int x=c-st;
            if(now->nxt[x]==nullptr){
                return false;
            }
            now=now->nxt[x];
        }
        return true;
    }
};
