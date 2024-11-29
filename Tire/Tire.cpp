/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/11/26 20:41
* @version: 1.0
* @description: 
********************************************************************************/
#include  <iostream>
# include  <string>
#include <map>
#include <vector>
#include <queue>

using namespace  std;

class  TireTree{
public:
    //字典树的初始化
    TireTree(){
        root_ = new TireNode('\0',0);
    }
    ~TireTree(){
        queue<TireNode*> que;
        que.push(root_);

        while(!que.empty()){
                TireNode* front = que.front();
                que.pop();
                for(auto & pair : front->nodeMap_) {
                    //将子节点加入队列
                    que.push(pair.second);
                }
                //释放当前结点
                delete front;
        }
    }

    //添加单词串
    void add(const string& word){
        TireNode* cur = root_;
        for(int i = 0; i < word.size();i++){
            auto childIt = cur-> nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end()){
                //相应结点没有，创建它
                TireNode* child = new TireNode(word[i],0);
                cur->nodeMap_.emplace(word[i],child);
                cur = child;
            }
            else{
                //相应的字符结点已经存在，移动cur指向对应的字符结点
                cur = childIt -> second;
            }
        }
        //cur指向了单词的最后一个结点
        cur->freqs_ ++;
    }

    //删除单词
    void remove(const string& word){
        TireNode* cur = root_;
        TireNode* del= root_;
        char delch = word[0];
        for(int i = 0 ; i < word.size();i++){
            auto childIt = cur->nodeMap_.find(word[i]);
            if(childIt == cur->nodeMap_.end()){
                return ;
            }

            if(cur->freqs_ > 0 || cur->nodeMap_.size() > 1){
                //有一个独立的单词
                del = cur;
                delch = word[i];
            }
            //移动到下一个结点
            cur = childIt->second;
        }
        //cur指向了末尾字符结点,出来了以后，单词存在
        //情况一 ：
        if(cur-> nodeMap_.empty()){
            //开始删除
            TireNode* child = del->nodeMap_[delch];
            del ->nodeMap_.erase(delch);

            //释放相应的结点内存
            queue<TireNode*> que;
            que.push(child);

            while(!que.empty()){
                TireNode* front = que.front();
                que.pop();
                for(auto & pair : front->nodeMap_) {
                    //将子节点加入队列
                    que.push(pair.second);
                }
                //释放当前结点
                delete front;
            }

        }
        else{
            //情况1
            //当前单词末尾字符后面还有字符结点,相当于删除
            cur-> freqs_ = 0;
        }

    }

    //查询单词
    int query(const string& word){
        TireNode* cur = root_;
        for(int i = 0 ; i < word.size();i++){
            //查找效率很高，o(m)  m -> word.size()
            auto childId = cur->nodeMap_.find(word[i]);
            if(childId == cur-> nodeMap_.end()){
                return 0;
            }
            //移动cur指向下一个单词的字符结点上
            cur = childId -> second;
        }
        return cur->freqs_;
    }

    //前序遍历字典树
    void preOrder(){
        string word;
        vector<string> wordlist ;
        preOrder(root_,word,wordlist);
        for(auto words:wordlist){
            cout << words << endl;
        }
        cout << endl;

    }
    //串的前缀搜索
    vector<string>  queryPrefix(const string& prefix){
        TireNode* cur = root_;
        for(int i = 0 ; i < prefix.size();i++){
            auto childIt = cur->nodeMap_.find(prefix[i]);
            if(childIt == cur->nodeMap_.end()){
                return {};
            }
            cur = childIt->second;
        }

        //cur就指向了前缀的最后一个字符结点了
        vector<string > wordlist;
        string word = prefix.substr(0,prefix.size()-1);
        preOrder(cur, word, wordlist);
        return wordlist;
    }

private:
    //结点的定义
    struct TireNode{
        TireNode(char ch,int freqs):ch_(ch),freqs_(freqs) {}

        char ch_;   //字节存储的字符数据
        int freqs_; //单词末尾的字符存储单词的数量
        //存储孩子结点的字符数据和结点指针的对应关系
        map<char,TireNode*> nodeMap_;
    };

private:
    void preOrder(TireNode* cur, string word,vector<string> &wordlist){
        //前序遍历VLR
        if(cur != root_){
            word.push_back(cur -> ch_);
            if(cur->freqs_ > 0){
                wordlist.emplace_back(word);
            }
        }
        //递归处理孩子结点
        for(auto pair : cur->nodeMap_){
            preOrder(pair.second,word,wordlist);
        }
    }
private:
    //定义树的类型
    TireNode* root_;   // 指向树的根节点

};


int main(){
    TireTree tire;
    tire.add("hello");
    tire.add("hello");
    tire.add("hel");
    tire.add("hel");
    tire.add("hello");
    tire.add("he");
    tire.add("he");
    tire.add("china");
    tire.add("ch");
    tire.add("hellw");

    cout << "hello : " <<tire.query("hello") << endl;
    cout << "hel : " <<tire.query("hel") << endl;
    cout << "china : " <<tire.query("china") << endl;
    cout << "ch : " <<tire.query("ch") << endl;

    cout << "======================" << endl;

    tire.preOrder();

    cout << "======================" << endl;

    vector<string> wordlist = tire.queryPrefix("hell");
    for(auto word:wordlist){
        cout<<word << endl;
    }
    cout << "======================" << endl;
    tire.remove("ch");
    tire.preOrder();
    return 0;
}