#include<stdint.h>
#include <streambuf>
#include<bits/stdc++.h>
using namespace std;



float readfile(char *fil, string &s)
{
	int cnt;
  
  	ifstream inp(fil,ios::binary);
    if(!inp.is_open())
      	return 0;
	
    inp.seekg(0,ios::end);  
    cnt=inp.tellg();
    inp.seekg(0,ios::beg);
    
    stringstream x;

    s="";
    s.resize(cnt);
	
    x<<inp.rdbuf();
    s=x.str();
	
    inp.close(); 
    
    return 0;
}


void change_head(string &head, unsigned int &h, unsigned int &w, int start, int m)
{
	w=w/m;
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
	int cnt;
	long long int i;
	
	ifstream inp(fil,ios::binary);
    if(!inp.is_open())
      	return 0;
	
    string u;
    stringstream x;

    x<<inp.rdbuf();
   	u=x.str();
    
    inp.close();
    
    for(i=start;i<cnt;i++)
    {
    	s[i]=s[i]|u[i];
    }
    
    return 0;
}

void condense(string &news, string &s, int start, int siz, int m)
{
	int i,j;
	char c;
	string inter,inter2;
	
	for(i=start;i<s.size();i++)
		for(j=0;j<8;j++)
			inter.push_back(char((s[i]<<j)>>7));
	
	for(i=0;i<inter.size();i+=m)
	{
		c=1;
		for(j=0;j<m;j++)
			c = c & inter[i+j];
			
		if(c)
			inter2.push_back(1);
		else
			inter2.push_back(0);
	}
		
	for(i=0;i<inter2.size();i+=8)
	{
		c=0;
		for(j=0;j<8;j++)
		{
			c*=2;
			c+=inter2[i+j];
		}
		news.push_back(c);
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
	int k=atoi(argv[5]);
	int m=pow(2,k-1);
	
	string s,head;
	uint16_t x;
	int start;
	
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
	}
	cout<<endl<<endl;
	
	string nhead=head;
	change_head(nhead,h,w,start,m);
	
	merge(argv[2],s,start,siz/8);
	writefile(argv[3],s);
	
	string news=nhead;
	condense(news,s,start,siz,m);		

	writefile(argv[4],news);
}
