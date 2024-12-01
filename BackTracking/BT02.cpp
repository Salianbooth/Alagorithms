/********************************************************************************
* @author: Alan Chen
* @email: salianbooth@gmail.com
* @date: 2024/12/1 20:50
* @version: 1.0
* @description: 
********************************************************************************/
#include  <iostream>
using namespace  std;
//整数选择问题,使得被选中的数字之和和未被选中的数字之和 的差值最小
int arr[] = {12,6,7,11,16,3,9};
const int length = sizeof(arr)/sizeof(arr[0]);
int x[length] = {0};    //辅助数组
int bestx[length] = {0};//记录最优
unsigned int m = 0xFFFFFFFF;
int sum = 0;
int r = 0; //记录没有选择的数字的和

void func(int i)
{
    if(i == length){
        //sum
        int result = abs(sum -r);
        if(result < m){
           m = result;
            for (int j = 0;j < length;++j) {
                bestx[j] = x[j];
            }
        }


    } else{
        //选择这个节点
        r -= arr[i];
        sum += arr[i];
        x[i] = 1;
        func(i+1);

        //不选择这个结点
        r += arr[i];
        sum -=arr[i];
        x[i] = 0;
        func(i+1);
    }
}

int main(){
    for(int v:arr){
        r += v;
    }
    func(0);
    for(int i = 0 ; i < length;++i){
        if(bestx[i] == 1){
            cout << arr[i] << " ";
        }
    }
    cout <<endl;
    cout << "min:" << m;
}