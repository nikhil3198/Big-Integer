#include <stdlib.h>
#include "intal.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
static char* string_reverse(char* str,int n);
static int isSmaller(char*str1,char* str2);
static char* string_reverse(char *str,int n)
{
	char temp;
	for(int i=0;i<n/2;i++)
	{
		temp=str[i];
		str[i]=str[n-i-1];
		str[n-i-1]=temp;
	}
    str[n]='\0';
	return str;
}

static int isSmaller(char*str1,char* str2)
{
	int n1=strlen(str1);
	int n2=strlen(str2);

	if(n1<n2)
		return 1;
	else if(n1>n2)
		return 0;

	for(int i=0;i<n1;i++)
	{
		if((str1[i]-'0')<(str2[i]-'0'))
			return 1;
		else if((str1[i]-'0')>(str2[i]-'0'))
			return 0;
	}
	return 0;
}

void* intal_create(const char* str)
{
	if(!strcmp(str,""))
		return NULL;
	int len=strlen(str);
	char *intal=(char *)malloc(sizeof(char)*(len+1));

	strcpy(intal,str);
	intal[len]='\0';

	return (void*)intal;


}

void intal_destroy(void* intal)
{
	free(intal);
}

char* intal2str(void* intal)
{
	if(intal==NULL)
		{
			char *s=(char*)intal_create("NaN");
			return s;
		}	
	char* str=(char*)intal;
	return str; 
}

void* intal_increment(void* intal)
{
	if(intal==NULL)
		return NULL;
	char *temp=(char*)intal;

	char *str=(char *)malloc(sizeof(char)*(strlen(temp)+1));
	int len=strlen(temp);
	int inc=(temp[len-1] - '0') +1;
	int i=len-2;
	int r;
	int j=0,k=0;
	char ch[1];

	while(i>=0)
	{
		r=inc%10;
		inc/=10;
		sprintf(ch,"%d",r);
		str[j]=ch[0];
		inc=(temp[i] - '0') + inc;
		i--;
		j++;
		
	}

	while(inc!=0)
	{
		r=inc%10;
		inc/=10;
		
		sprintf(ch,"%d",r);
		str[j++]=ch[0];
		
	}
	
	str=string_reverse(str,j);
	return (void*)str;

}

void* intal_decrement(void* intal)
{
	if(intal==NULL)
		return NULL;
	char *str=(char*)intal;
	if(!strcmp(str,"0"))
	{
		return intal_create("0");
	}
	return intal_diff((void*)str,intal_create("1"));
}


void* intal_add(void* intal1, void* intal2)
{
	 if(intal1==NULL || intal2==NULL)
	 	return NULL;
	char *str1=(char*)intal1;
	char *str2=(char*)intal2;
	char* str3;
	
	 

	int n1=strlen(str1);
	int n2=strlen(str2);

	if(n1>n2)
		{
		str3=(char*)malloc(sizeof(char)*(n1+1));
		}
	else if(n2>n1)
		{
		str3=(char*)malloc(sizeof(char)*(n2+1));
	}
	else
	{
		str3=(char*)malloc(sizeof(char)*(n1+1));
	}
	
	int i,j,k=0;
	char ch[1];
	

	if(strlen(str1) > strlen(str2))
	{
		char *tmp=str1;
		str1=str2;
		str2=tmp;
	
	}

	 n1=strlen(str1);
	 n2=strlen(str2);
	 int diff=n2-n1;
	int carry=0,sum,r;

	for(i=n1-1;i>=0;i--)
	{
		sum=(str1[i]-'0')+(str2[i+diff] - '0') + carry;
	
		 r=sum%10;
		sprintf(ch,"%d",r);
	    
		str3[k++]=ch[0];

	  
		carry=sum/10;
		
	}
	
	for(i=n2-n1-1;i>=0;i--)
	{
		 sum=(str2[i] - '0')+carry;
		 r=sum%10;
		sprintf(ch,"%d",r);
		str3[k++]=ch[0];

		carry=sum/10;
	}

	if(carry)
	{
		sprintf(ch,"%d",carry);
		str3[k++]=ch[0];
	}
	str3[k]='\0';
	str3=string_reverse(str3,k);

	return (void*)str3;

}

void* intal_diff(void* intal1, void* intal2)
{
 if(intal1==NULL || intal2==NULL)
	 	return NULL;


	char *str1=(char*)intal1;
	char *str2=(char*)intal2;
	char* str3;
	
	 if (isSmaller(str1,str2))
        {
        	char *tmp=str1;
			str1=str2;
			str2=tmp;
        }
     int n1=strlen(str1);
	int n2=strlen(str2);
     
     if(n1==1 && n2==1)
     {
     	int val=(str1[0]-'0') - (str2[0]-'0');
     	char *s=(char*)malloc(sizeof(char));
		sprintf(s,"%d",val);
		return (void*)s;
     }
	
	
	if(n1>n2)
		{
		str3=(char*)malloc(sizeof(char)*(n1+1));
		}
	else if(n2>n1)
		{
		str3=(char*)malloc(sizeof(char)*(n2+1));
	}
	else
	{
		str3=(char*)malloc(sizeof(char)*(n1+1));
	}

	int i,j,k=0;
	char ch[1];
	int diff=n1-n2;
	int carry=0,sub;

	for(i=n2-1;i>=0;i--)
	{
		sub=(str1[i+diff]-'0')-(str2[i] - '0') - carry;
		
		if(sub<0)
		{
			sub=sub+10;
			carry=1;
		}		
		else
			carry=0;

		sprintf(ch,"%d",sub);
		str3[k++]=ch[0];
	}
	
	for(i=n1-n2-1;i>=0;i--)
	{
		if(str1[i]=='0' && carry)
		{
			str3[k++]='9';
			continue;
		}
		sub=(str1[i] - '0')-carry;
		if(i>0 || sub > 0)
		{
			sprintf(ch,"%d",sub);
			str3[k++]=ch[0];
		}
		carry=0;
	}
	
	str3=string_reverse(str3,k);

	str3[k]='\0';
	int n3=strlen(str3);
	
	for(i=0;i<n3;i++)
	{
		
		if(str3[i]!='0')
			break;
	}
	char *res=(char*)malloc(sizeof(char)*(n3-i+1));
	strncpy(res,&str3[i],n3-i);
	res[n3-i]='\0';

	return (void*)res;
}

int intal_compare(void* intal1, void* intal2)
{

	 if(intal1==NULL || intal2==NULL)
	 	return -2;

	char *string1=(char*)intal1;
	char *string2=(char*)intal2;

	
   
	int n1=strlen(string1);
	int n2=strlen(string2);
	int i;
	for(i=0;i<n1;i++)
	{
		if(string1[i]!='0')
			break;
	}
	char *str1=(char*)malloc(sizeof(char)*(n1-i+1));
	strncpy(str1,&string1[i],n1-i);
	str1[n1-i]='\0';

	for(i=0;i<n2;i++)
	{
		if(string2[i]!='0')
			break;
	}
	char *str2=(char*)malloc(sizeof(char)*(n2-i+1));
	strncpy(str2,&string2[i],n2-i);
	str2[n2-i]='\0';

	n1=strlen(str1);
	n2=strlen(str2);

	if(n1<n2)
		return -1;
	else if(n1>n2)
		return 1;

	for(int i=0;i<n1;i++)
	{
		if((str1[i]-'0')<(str2[i]-'0'))
			return -1;
		else if((str1[i]-'0')>(str2[i]-'0'))
			return 1;
	}
	return 0;
}

void* intal_multiply(void* intal1, void* intal2)
{
	 if(intal1==NULL || intal2==NULL)
	 	return NULL;
    char *str1=(char*)intal1;
	char *str2=(char*)intal2;

	int n1=strlen(str1);
	int n2=strlen(str2);

	if(!strcmp(str1,"0") || !strcmp(str2,"0"))
	{
		char *s=(char*)malloc(sizeof(char));
		strcpy(s,"0");
		return (void*)s;
	}

	int *res=(int*)malloc(sizeof(int)*(n1+n2));

	int i_n1=0;
	int i_n2=0;
	int i,j,k=0,carry,num1,num2,sum;
	for(i=n1-1;i>=0;i--)
	{
		
		 carry=0;
		 num1=str1[i]-'0';

		 i_n2=0;

		 for(j=n2-1;j>=0;j--)
		 {
		 	num2=str2[j]-'0';
		 	sum=num1*num2 + res[i_n1+i_n2] + carry;
		 	carry=sum/10;
		 	res[i_n1+i_n2]=sum%10;

		 	i_n2++;
		 }

		 if(carry>0)
		 	 res[i_n1 + i_n2] += carry;

		 i_n1++;

	}
	
	i=n1+n2-1;

	while(i>=0 && res[i]==0)
		i--;
	if(i==-1)
	{
		char *s=(char*)malloc(sizeof(char));
		strcpy(s,"0");
		return (void*)s;
	}
	char* res1=(char*)malloc(sizeof(char)*(i+1));
	while(i>=0)
	{
		res1[k++]=res[i]+'0';
		i--;

	}
	res1[k]='\0';

	return (void*)res1;
}


void* intal_divide(void* intal1, void* intal2)
{

	if(intal1==NULL || intal2==NULL)
	 	return NULL;

	char *str1=(char*)intal1;
	char *str2=(char*)intal2;
	int k=0;
	
	if(!strcmp(str2,"0"))
	{
		return NULL;
	}
	if(!strcmp(str2,"1"))
		return (void*)str1;

	if(isSmaller(str1,str2))
	{
		char *s=(char*)malloc(sizeof(char));
		strcpy(s,"0");
		return (void*)s;
	}
	

	int n1=strlen(str1);
	int n2=strlen(str2);
	char *res=(char*)malloc(sizeof(char)*(n1));
	char *temp=(char*)malloc(sizeof(char)*2);
	int j,count=0;
	
	char* s1=(char*)malloc(sizeof(char)*(n2+1));
	strncpy(s1,str1,n2);
	s1[n2]='\0';

	if(isSmaller(s1,str2))
		{
			strncat(s1,&str1[n2],1);
			n2++;
		}

	for(j=n2;j<=n1;j++)
	{
		count=0;
		
		while(intal_compare(s1,str2)!=-1)
		{
			
			s1=(char*)intal_diff((void*)s1,(void*)str2);
		
			count++;
			
		}

		strncat(s1,&str1[j],1);
		sprintf(temp,"%d",count);
		strcat(res,temp);
	}

	int res_len=strlen(res);
	
	res[res_len]='\0';
	int i;
	for(i=0;i<res_len;i++)
	{
		
		if(res[i]!='0')
			break;
	}
	char *res1=(char*)malloc(sizeof(char)*(res_len-i+1));
	strncpy(res1,&res[i],res_len-i);
	res1[res_len-i]='\0';

	return (void*)res1;	

}

void* intal_pow(void* intal1, void* intal2)
{

	if(intal1==NULL || intal2==NULL)
	 	return NULL;

	char *string1=(char*)intal1;
	char *string2=(char*)intal2;

	int n1=strlen(string1);
	int n2=strlen(string2);
	char *str1=(char*)malloc(sizeof(char)*(n1));
	char *str2=(char*)malloc(sizeof(char)*(n2));

	strcpy(str1,string1);
	strcpy(str2,string2);

	if(!strcmp(str2,"1"))
	{
		return (void*)str1;
	}
	if(!strcmp(str1,"0"))
	{
		
		return intal_create("0");
	}
	if(!strcmp(str2,"0") || !strcmp(str1,"1"))
	{
		return intal_create("1");
	}

	char* p=(char*)intal_pow((void*)str1,intal_divide((void*)str2,intal_create("2")));
	p=(char*)intal_multiply((void*)p,(void*)p);

	if((str2[n2-1]-'0')%2!=0)
		p=(char*)intal_multiply((void*)p,(void*)str1);

	int len=strlen(p);
	
	p[len]='\0';
	
	return intal_create(p);
}
