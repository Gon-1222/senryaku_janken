#include<stdio.h>
#include <stdlib.h>
#include <time.h>

#define SHIKOU_KAISU 1
#define KACHI_KAISU 4
#define MAKE_KAISU 2
#define G 0
#define C 1
#define P 2
#define MAX_RANDOM 1000
#define DRAW 0
#define LOSE 1
#define WIN 2

int main(void){
  int i;//一時変数
  int buf=0;//一時変数
  int flag=0;//一時変数
  char dummy;//一時変数
  char cmd;//コマンド
  int human;//人の出した値
  int computer;//コンピュータの出した値
  int table [3][3]={{1,1,1},{1,1,1},{1,1,1}};//デシジョンテーブル
  int last = 0;//前回の手
  int goukei=0;//前回の手の母数
  int ransu=0;//0~1000の乱数
  int kakuritsu[2];//デシジョンテーブルの確率値(‰)
  int result[1000];//勝敗データ{最下位から試行ビット、負けビット、勝ちビット}１のときTrue
  int last_result[4]={0};//最終結果{勝数,負数,引分数,試行回数}
  //前処理
  srand((unsigned int)time(NULL));
  //メインループ
  while(1){
  //入力
  printf("一文字入力してください>>");
  scanf("%c",&cmd);
  scanf("%c", &dummy);
  //データ検査
  if (!(cmd=='G'||cmd=='C'||cmd=='P'||cmd=='E')){
    printf("正しい値を入力してださい。\n");
    continue;
  }

  //終了処理
  if (cmd=='E' || flag==1){
    i=0;
    while(result[i]&SHIKOU_KAISU){

      if (result[i]&SHIKOU_KAISU){
        last_result[3]++;
      }
      if(result[i]&MAKE_KAISU){
        last_result[1]++;
      }
      if(result[i]&KACHI_KAISU){
        last_result[0]++;
      }
      i++;
    }
    last_result[2]=  last_result[3]-last_result[1]-last_result[0];
    printf("%d回行い、あなたは%d回勝ち、%d回負け、%d回引き分けでした。",last_result[3],last_result[0],last_result[1],last_result[2]);
    break;
  }

  //勝負実行
  //コマンドを数値に変更
  human = (cmd=='G') ? G:(cmd=='C'? C : P);
 //デシジョンテーブルに追加
    table[last][human]+=1;
//コンピュータの手の決定
    goukei=0;
    for (i=0;i<3;i++){
      goukei+=table[last][i];
    }
    kakuritsu[G]=MAX_RANDOM *table[last][G]/goukei;
    kakuritsu[C]=MAX_RANDOM *table[last][C]/goukei+kakuritsu[G];
    ransu=(rand() % MAX_RANDOM );
    if(ransu<kakuritsu[G]) {
      computer=P;
    }else if (ransu<kakuritsu[C]){
      computer=G;
    }else{
      computer=C;
    }

//勝敗判定・勝敗結果の表示
 if ((human-computer+3)%3==DRAW){
   printf("引き分け、");
   result[buf]=SHIKOU_KAISU;
 }else if((human-computer+3)%3==LOSE){
   printf("あなたの負け、");
   result[buf]=SHIKOU_KAISU+MAKE_KAISU;
 }else if((human-computer+3)%3==WIN){
   printf("あなたの勝ち、");
   result[buf]=SHIKOU_KAISU+KACHI_KAISU;
 }else{
   printf("エラー\n");
 }
 printf("human:%s:computer:%s\n",(human==G)?"グー":(human==C?"チョキ":"パー"),(computer==G)?"グー":(computer==C?"チョキ":"パー"));
 last=human;
 buf++;

 if (buf>999){
   flag=1;
   printf("試行回数制限オーバーです。\n");
 }
}
  return 0;
}
