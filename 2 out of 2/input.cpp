#include<stdint.h>
#include <streambuf>
#include<bits/stdc++.h>
using namespace std;

int cnt;

float readfile(char *fil, string &s)
{	
	uint8_t c;
	long long int i,j,k;
  
  	ifstream inp(fil,ios::binary);
    if(!inp.is_open())
      	return 0;
	
    inp.seekg(0,ios::end);  
    cnt=inp.tellg();
    inp.seekg(0,ios::beg);
    
    string u;
    stringstream x;

    s="";
    s.resize(cnt);
	
    x<<inp.rdbuf();
    s=u=x.str();
	
    inp.close(); 
    
    return 0;
}

void change_head(string &head, unsigned int &h, unsigned int &w, int start)
{
	w=w*4;
	h=h*1;
	unsigned int h2=h,w2=w;
	uint16_t x;

	head[18]=w2%(1<<8);
	w2=w2>>8;
	head[19]=w2%(1<<8);
	w2=w2>>8;
	head[20]=w2%(1<<8);
	w2=w2>>8;
	head[21]=w2%(1<<8);
	w2=w2>>8;
	
	head[22]=h2%(1<<8);
	h2=h2>>8;
	head[23]=h2%(1<<8);
	h2=h2>>8;
	head[24]=h2%(1<<8);
	h2=h2>>8;
	head[25]=h2%(1<<8);
	h2=h2>>8;
	
	
	cout<<"\nChanged header - \n";
	for(int i=0;i<start;i++)
	{
		x=(uint8_t)head[i];
		cout<<(unsigned int)x<<' ';
	}
	cout<<endl;
}



void setpix(uint32_t *newpix,int siz,int col)
{
	for(int i=0;i<siz;i++)
	{
		newpix[i]=col;
	}
}

void scheme1(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,255);
	setpix(newpix[1],siz/8,255);
	setpix(newpix[2],siz/8,0);
	setpix(newpix[3],siz/8,0);			
}
void scheme2(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,255);
	setpix(newpix[1],siz/8,0);
	setpix(newpix[2],siz/8,255);
	setpix(newpix[3],siz/8,0);			
}
void scheme3(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,255);
	setpix(newpix[1],siz/8,0);
	setpix(newpix[2],siz/8,0);
	setpix(newpix[3],siz/8,255);			
}
void scheme4(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,0);
	setpix(newpix[1],siz/8,255);
	setpix(newpix[2],siz/8,255);
	setpix(newpix[3],siz/8,0);			
}
void scheme5(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,0);
	setpix(newpix[1],siz/8,255);
	setpix(newpix[2],siz/8,0);
	setpix(newpix[3],siz/8,255);			
}
void scheme6(uint32_t **newpix,int siz)
{
	setpix(newpix[0],siz/8,0);
	setpix(newpix[1],siz/8,0);
	setpix(newpix[2],siz/8,255);
	setpix(newpix[3],siz/8,255);			
}



int create_transparencies(string trans[], int notrans, string nhead, string &s, int siz, int start)
{
	srand (time(NULL));
	
	int nosub=4,randscheme;
	
	for(int i=0;i<notrans;i++)
		trans[i]=nhead;
	
	for(int i=start;i<s.size();i+=siz/8)		//Assume pixel size is greater than 1B 
	{
		uint32_t pix[siz/8], newpix[notrans][nosub][siz/8];
		
		for(int j=0;j<siz/8;j++)
		{
			pix[j]=(uint8_t)s[i+j];
		}
		randscheme=rand()%3;
		
		/*
		uint32_t ***nop=newpix,**np[notrans];
		for(int j=0;j<notrans;j++)
		{
			np[i]=nop[i];
		}
		*/
		if(pix[0]==255)
		{
			switch(randscheme)
			{
				case 0:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,255);
					break;
				
				case 1:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,255);
					break;
				
				case 2:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,0);
					break;
				case 3:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,255);
					break;
				case 4:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,0);
					break;
				
				case 5:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,0);
					break;
				
			}
		}
		else
		{
			switch(randscheme)
			{
				case 0:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,0);
					break;
				
				case 1:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,0);
					break;
				
				case 2:
					setpix(newpix[0][0],siz/8,255);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,255);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,255);
					break;
				case 3:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,0);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,0);
					break;
				case 4:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,255);
					setpix(newpix[0][2],siz/8,0);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,255);
					setpix(newpix[1][2],siz/8,0);
					setpix(newpix[1][3],siz/8,255);
					break;
				
				case 5:
					setpix(newpix[0][0],siz/8,0);
					setpix(newpix[0][1],siz/8,0);
					setpix(newpix[0][2],siz/8,255);
					setpix(newpix[0][3],siz/8,255);
					setpix(newpix[1][0],siz/8,0);
					setpix(newpix[1][1],siz/8,0);
					setpix(newpix[1][2],siz/8,255);
					setpix(newpix[1][3],siz/8,255);
					break;
				
			}		
		}
		
		for(int j=0;j<notrans;j++)
		{
			for(int k=0;k<nosub;k++)
			{
				for(int l=0;l<siz/8;l++)
				{
					trans[j].push_back(newpix[j][k][l]);
				}
			}
		}
	}
	
	string f;
	for(int i=0;i<notrans;i++)
	{
		f="file";
		f.push_back(char(i+48));
		f+=".bmp";
		char fil[10];
		strcpy(fil,f.c_str());
		ofstream outp(fil,ios::binary);
		
		outp<<trans[i];
		
		outp.close();
	}
	
	return 0;
}

main(int argc, char **argv)
{
	string s,head;
	uint16_t x,y=7;
	int c=1,start;
	
	readfile(argv[1],s);
	//cout<<sizeof(s[0]);
	
	unsigned int h=0,w=0;
	uint16_t siz=0;
	for(int i=21;i>=18;i--)
	{
		h=(h<<8);
		h+=(uint8_t)s[i+4];
		
		w=(w<<8);
		w+=(uint8_t)s[i];
	}
	
	siz=(uint8_t)s[29];
	siz=(siz<<8);
	siz+=(uint8_t)s[28];
	//cout<<siz<<endl<<h<<' '<<w<<endl;
	
	switch(siz)
	{
		case 1:
			start=62;
			break;
		case 4:
			start=118;
			break;
		case 8:
			start=1078;
			break;
		case 16:
			start=54;
			break;
		case 24:
			start=54;
			break;
		case 32:
			start=54;
			break;
			
	}
	
	cout<<"Original Header - \n";
	for(int i=0;i<start;i++)
	{
		head.push_back(s[i]);
		x=(uint8_t)s[i];
		cout<<(unsigned int)x<<' ';
		//cout<<i<<endl;
	}
	cout<<endl<<head.length()<<endl;
	
	string nhead=head;
	change_head(nhead,h,w,start);
	
	int notrans=2;
	string trans[notrans];
	create_transparencies(trans,notrans,nhead,s,siz,start);	
	
	/*
	for(int i=start;i<1100;i+=1)
	{
		x=(uint8_t)trans[0][i];
		printf("%u ",(unsigned int)x);
	}
	*/
	cout<<endl;
	
}
