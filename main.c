#include<windows.h>
#include<stdio.h>
#include<malloc.h>
#include<string.h>

typedef struct _Protocol{
	unsigned char stx;//stx:2;
	unsigned char id[2];
	unsigned char command[3];
	unsigned char data[13];
	unsigned char etx;//:2;
	unsigned char sum;
	unsigned char cr;//:4;
	unsigned char result;//:1;

}PROTOCOL, *PPROTOCOL;

typedef struct _DoublePointer {
	char	*pStr;
	int		count;
	struct _DoublePointer *Next;
}DP, *PDP;

/////////////////////////////////////////////////////////////////////////////////////////////////
char *DoublePointer(int ii)
{
	int i;
	char *pStr[2];
	char **dpStr;
	char string[10];
	dpStr = (char **)malloc(sizeof(char));
	*dpStr = (char *)malloc(sizeof(char));

	for(i=0 ; i<ii ; i++){		
		printf("값을 입력하시오! -> ");
		scanf("%s", &string[i]);
		pStr[i] = (char *)malloc(sizeof(char));		strcpy(pStr[i], &string[i]);
		dpStr[i] = (char *)malloc(sizeof(char));	strcpy(dpStr[i], &string[i]);

		printf("(dpStr[%d])주소값 -> 0x%x \t (dpStr[%d])주소값 -> 0x%x \n",i, pStr[i] ,i, dpStr );
	}
	//return *pStr;
	return *dpStr;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
DP *DP_Input(DP *pgdp, int ii)
{
	DP	*pldp;
	int i;
	
	//pldp = (DP *)malloc(sizeof(DP)+1); 이곳에 있으면 나중에 ii 값만 출력됨..
	//이걸로 많이 해맸다.
	for(i=0 ; i < ii ; i++) {		
		pldp = (DP *)malloc(sizeof(DP)+1);
		pldp->pStr = (char *)malloc(sizeof(char));	
		printf("문자열 입력 ->");gets(pldp->pStr);
		pldp->count = i+1;
		printf("pldp->count-> %d\n", i+1);
		pldp->Next = pgdp->Next;
		pgdp->Next = pldp;
	} //end for
	return pldp;//pgdp 이면 에러
}
#define PCI_SWAP32(a) (a)
int main(void)
{
	//char *pfStr[2];
	int i=0;
	unsigned int bytes;
//	DP	*pdp, *pdp_show;
	
	PROTOCOL Data;	
	char *Msg=NULL;
	char R='C';

	//LPTSTR *Msg=NULL;
	LPTSTR ReadData="2A0RTC01234567891233D1"; //20 byte

	memcpy((void *)&Data,ReadData,sizeof(PROTOCOL));	

	Msg = (char *)malloc(sizeof(char)+1);
	//memset(Msg, 23, sizeof(char)*23);
/*		unsigned char stx:2;
		unsigned char id;
		unsigned char command[3];
		unsigned char etx:2;
		unsigned char sum;
		unsigned char cr:4;
		unsigned char result:1;		
*/	// PowerPack Serial Communication Protocol start
	
	printf("\nMsg = %c   R=0x%x\n", Msg[0], R);
	/*
	while(Msg[i]!=0x0D){//NULL값이 나올때 까지 루프를 돈다.
		
		Msg	+=Data.stx; 
		Msg +=Data.id[0];  
		Msg +=Data.id[1];  
		Msg +=Data.command[0];
		Msg +=Data.command[1];
		Msg +=Data.command[2];
		Msg +=Data.etx;
		Msg +=Data.sum;
		Msg +=Data.cr;
		Msg +=Data.result;
		printf("\nMsg[%d]=%c", i,Msg[i]);
		i++;
	}//end while
	*/
	printf("\nReadData = %s \t Msg = %s\n", ReadData, Msg);
	
	if(Data.cr==0x0D)
		printf("\npt.id=0x%x\n", Data.stx);
	else
		printf("\n실패\n");

	bytes = 1;//2;//4;

	
	

	i = PCI_SWAP32(3);
	
	printf("\n\ni = %d\n",i);

	printf("\n\n1 | 2 | 4 | 8 = %x\n",1 | 2 | 4 | 8);

	
	if(bytes &~ 0x3) {
		printf("\n\n0x4 &~ 0x3 (Q_32) = %x\n",bytes &~ 0x3);
	}

	if((bytes & 0x3) &~ 0x1){
		printf("\n\n(0x4 & 0x3) &~ 0x1 (Q_16) = %x\n",(bytes & 0x3) &~ 0x1);
	}

	if(bytes & 0x1){
		printf("\n\n0x4 & 0x1 (Q_8) = %x\n",bytes & 0x1);

	}
	puts("");
	printf("\n\n0x4 &~ 0x3 (Q_32) = %x\n",bytes &~ 0x3);
	printf("\n\n(0x4 & 0x3) &~ 0x1 (Q_16) = %x\n",(bytes & 0x3) &~ 0x1);
	printf("\n\n0x4 & 0x1 (Q_8) = %x\n",bytes & 0x1);
	//if(Msg)
	//	free(Msg);
//	pdp			= (DP *)malloc(sizeof(DP));	//이건 반드시 있어야 한다.
	/*
	pdp_show	= DP_Input(pdp, 3);

	while(i < 3 ) {		
		printf("\ni=%d\tpdp -> %s\tpdp -> %d\n",i, pdp_show->pStr, pdp_show->count);
		pdp_show = pdp_show->Next;
		i++;
	}//end if
	*/

	
	//pfStr = (char **)malloc(sizeof(char));
	//*pfStr = DoublePointer(2);
	//printf("\npfStr = %s \t (*pfStr)주소값 -> 0x%x \n", pfStr[0], *pfStr);
	return 0;
}