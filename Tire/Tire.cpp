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

using namespace  std;

class  TireTree{
public:
    //字典树的初始化
    TireTree(){
        root_ = new TireNode('\0',0);
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

    return 0;
}