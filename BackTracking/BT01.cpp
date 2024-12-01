/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/12/1 20:36
* @version: 1.0
* @description: 
********************************************************************************/
#include  <iostream>
using namespace  std;

void func(int arr[],int i,int length,int x[])
/***
 *
 * @param arr:原数组
 * @param i
 * @param length:数组长度
 * @param x:辅助数组
 * 用于找到数组的所有子集
 */
{
    if(i == length){
        for(int  j = 0; j < length;++j){
            if(x[j] == 1){
                cout << arr[j] << " " ;
            }
        }
        cout << endl;
    }
    else{
        x[i] = 1;   //选择i节点
        func(arr,i+1,length,x);//遍历i的左孩子

        x[i] = 0;   //不选择i节点
        func(arr,i+1,length,x);//遍历i的右孩子
    }
}

int main(){
    int arr[] = {1,2,3};
    int length = (int)sizeof(arr)/ sizeof(arr[0]);
    int x[3] ={0};
    func(arr,0,length,x);
}