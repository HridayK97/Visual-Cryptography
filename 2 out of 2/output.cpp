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
	w=w/4;
	h=h/1;
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


int merge(char *fil,string &s, int start, int printsiz)
{
	uint8_t c;
	long long int i,j,k;
	
	ifstream inp(fil,ios::binary);
    if(!inp.is_open())
      	return 0;
	
    string u;
    stringstream x;

    x<<inp.rdbuf();
   	u=x.str();
    
    inp.close();
    
    
    uint16_t y,z,a;
    for(i=start;i<cnt;i++)
    {
    	s[i]=s[i]|u[i];
    	
    	/*if(i<1000)
		{
			cout<<(int)s[i]<<' ';
			if((i+7)%(printsiz*4)==0)
				cout<<endl;
		}
		if(i==1000)
			cout<<endl<<endl;
    	*/
    }
    
    return 0;
}

void condense(string &news, string &s, int start, int siz)
{
	int nosub=4;
	char share[nosub][siz/8],pix[siz/8];
	int ct=start;
	for(int i=start;i<s.size();i+=nosub*siz/8)
	{
		for(int k=0;k<siz/8;k++)
		{
			pix[k]=255;
		}
		
		for(int j=0;j<nosub*siz/8;j+=siz/8)
		{
			for(int k=0;k<siz/8;k++)
			{
				share[j][k]=s[ct];
				//if(i<1000)
				//cout<<(int)share[j][k]<<' ';
				pix[k]=pix[k] & share[j][k];
				ct++;
			}
		}
		
		//if(i<1000)
		//cout<<" - ";
		
		for(int k=0;k<siz/8;k++)
		{
			//if(i<1000)
			//cout<<(int)pix[k]<<' ';
			news.push_back(pix[k]);
		}
		
		//if(i<1000)
		//cout<<endl;
	}
	
}

void writefile(char *fil, string &s)
{
	ofstream outp(fil,ios::binary);
		
	outp<<s;
		
	outp.close();
}

main(int argc, char **argv)
{
	string s,head;
	uint16_t x,y=7;
	int c=1,start;
	
	readfile(argv[1],s);
	
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
	
	cout<<"Original Header -\n";
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
	
	merge(argv[2],s,start,siz/8);
	writefile(argv[3],s);
	
	string news=nhead;
	condense(news,s,start,siz);		

	/*
	for(int i=start;i<1000;i++)
	{
		cout<<(int)news[i]<<' ';
	}
	cout<<endl;
*/
	writefile(argv[4],news);
}
