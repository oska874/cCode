/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

int main(void)
{
    int incr[10]={[0 ... 5]={2},[6 ... 9]={1}};
    for(int i=0;i<10;i++){
        printf("%d\n",incr[i]);
    }
    return 0;
}
