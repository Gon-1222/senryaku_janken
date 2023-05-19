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
  int i;//�ꎞ�ϐ�
  int buf=0;//�ꎞ�ϐ�
  int flag=0;//�ꎞ�ϐ�
  char dummy;//�ꎞ�ϐ�
  char cmd;//�R�}���h
  int human;//�l�̏o�����l
  int computer;//�R���s���[�^�̏o�����l
  int table [3][3]={{1,1,1},{1,1,1},{1,1,1}};//�f�V�W�����e�[�u��
  int last = 0;//�O��̎�
  int goukei=0;//�O��̎�̕ꐔ
  int ransu=0;//0~1000�̗���
  int kakuritsu[2];//�f�V�W�����e�[�u���̊m���l(��)
  int result[1000];//���s�f�[�^{�ŉ��ʂ��玎�s�r�b�g�A�����r�b�g�A�����r�b�g}�P�̂Ƃ�True
  int last_result[4]={0};//�ŏI����{����,����,������,���s��}
  //�O����
  srand((unsigned int)time(NULL));
  //���C�����[�v
  while(1){
  //����
  printf("�ꕶ�����͂��Ă�������>>");
  scanf("%c",&cmd);
  scanf("%c", &dummy);
  //�f�[�^����
  if (!(cmd=='G'||cmd=='C'||cmd=='P'||cmd=='E')){
    printf("�������l����͂��Ă������B\n");
    continue;
  }

  //�I������
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
    printf("%d��s���A���Ȃ���%d�񏟂��A%d�񕉂��A%d����������ł����B",last_result[3],last_result[0],last_result[1],last_result[2]);
    break;
  }

  //�������s
  //�R�}���h�𐔒l�ɕύX
  human = (cmd=='G') ? G:(cmd=='C'? C : P);
 //�f�V�W�����e�[�u���ɒǉ�
    table[last][human]+=1;
//�R���s���[�^�̎�̌���
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

//���s����E���s���ʂ̕\��
 if ((human-computer+3)%3==DRAW){
   printf("���������A");
   result[buf]=SHIKOU_KAISU;
 }else if((human-computer+3)%3==LOSE){
   printf("���Ȃ��̕����A");
   result[buf]=SHIKOU_KAISU+MAKE_KAISU;
 }else if((human-computer+3)%3==WIN){
   printf("���Ȃ��̏����A");
   result[buf]=SHIKOU_KAISU+KACHI_KAISU;
 }else{
   printf("�G���[\n");
 }
 printf("human:%s:computer:%s\n",(human==G)?"�O�[":(human==C?"�`���L":"�p�["),(computer==G)?"�O�[":(computer==C?"�`���L":"�p�["));
 last=human;
 buf++;

 if (buf>999){
   flag=1;
   printf("���s�񐔐����I�[�o�[�ł��B\n");
 }
}
  return 0;
}
