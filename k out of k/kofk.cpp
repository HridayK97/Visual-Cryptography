#include<stdint.h>
#include <streambuf>
#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;

void powerSet(int k, int m, vector<int> pi[], vector<int> sigma[], vector<int> power[])
{
	int counter, j, p=0,s=0, ct;
	
    for(counter = 0; counter < 2*m; counter++)
    {
    	ct=0;
    	for(j = 0; j < k; j++)
       	{
        	if(counter & (1<<j))
        	{	
        		power[counter].push_back(j);
        		ct++;
        	}
       	}
       	if(ct%2==0){
       		pi[p++]=power[counter];
       	}
       	else
        {
        	sigma[s++]=power[counter];
        }
       	
    }
}

void createScheme(string s0[], string s1[], vector<int> pi[], vector<int> sigma[], int k, int m)
{
	int i,j,z;
	for(i=0;i<k;i++)
	{
		s0[i].resize(m);
		s1[i].resize(m);
		
		for(j=0;j<m;j++)
		{
			s0[i][j]=0;
			s1[i][j]=0;
			
			for(z=0;z<pi[j].size();z++)
			{
				if(i==pi[j][z])
				{
					s0[i][j]=1;
				}
			}
			for(z=0;z<sigma[j].size();z++)
			{
				if(i==sigma[j][z])
				{
					s1[i][j]=1;
				}
			}
			
		}
	}
}




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
	w=w*m;
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
	for(int i=0;i<54;i++)
	{
		x=(uint8_t)head[i];
		cout<<(unsigned int)x<<' ';
	}
	cout<<endl;
}


int create_transparencies(string trans[], int k, int m, string s0[], string s1[],\
						 string nhead, string &s, int siz, int start)
{
	
	srand (time(NULL));
	
	int sptr,j,rr[k],rc[m];
	char c,u[8];
	string share[k];
		
	for(sptr=start;sptr<s.size();sptr++)
	{
		c=s[sptr];
		
		for(int tr=0;tr<k;tr++)
			share[tr]="";
		
		for(j=0;j<8;j++)
		{
			u[j]=c>>(7-j);
			u[j]=u[j]%2;
			
			for(int tr=0;tr<k;tr++)
			{
				rr[tr]=rand()%k;
				int flag=0;
				for(int z=0;z<tr;z++)
					if(rr[tr]==rr[z])
						flag=1;
				if(flag)
					tr--;
			}
			for(int sub=0;sub<m;sub++)
			{
				rc[sub]=rand()%m;
				int flag=0;
				for(int z=0;z<sub;z++)
					if(rc[sub]==rc[z])
						flag=1;
				if(flag)
					sub--;
			}
			for(int tr=0;tr<k;tr++)
			{
				for(int sub=0;sub<m;sub++)
				{
					if(u[j]==0)
					{
						share[tr].push_back(s0[rr[tr]][rc[sub]]);
					}	
					else
					{
						share[tr].push_back(s1[rr[tr]][rc[sub]]);
					}
				}
			}
	
			
		}
		
		
		for(int tr=0;tr<k;tr++)
		{
			
			for(int x=0;x<share[tr].size();x+=8)
			{
				char a=0;
				for(int y=0;y<8;y++)
				{
					a*=2;
					a+=share[tr][x+y];
				}
				
				trans[tr].push_back(a);
				
				
			}
			share[tr]="";
		}
		
	}
	

	string f;
	char no[5];
	for(int i=0;i<k;i++)
	{
		f="file";
		sprintf(no,"%d",i); 
		f+=no;
		f+=".bmp";
		char fil[10];
		strcpy(fil,f.c_str());
		ofstream outp(fil,ios::binary);
		
		outp<<nhead;
		outp<<trans[i];
		
		outp.close();
	}
	
	return 0;
}

main(int argc, char **argv)
{
	int k=atoi(argv[2]);
	int m=pow(2,k-1),i;
	
	vector<int> pi[m], sigma[m], power[2*m];
	powerSet(k,m,pi,sigma,power);	
	
	string s0[k],s1[k];
	createScheme(s0,s1,pi,sigma,k,m);
	
	cout<<"Scheme 0 -\n";	
	for(i=0;i<k;i++){
		for(int j=0;j<m;j++)
			cout<<(int)s0[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl;
	
	cout<<"Scheme 1 -\n";
	for(i=0;i<k;i++){
		for(int j=0;j<m;j++)
			cout<<(int)s1[i][j]<<' ';
		cout<<endl;
	}
	cout<<endl;


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
	
	cout<<"Original Header - \n";
	for(int i=0;i<start;i++)
	{
		head.push_back(s[i]);
		x=(uint8_t)s[i];
		if(i<54)
			cout<<(unsigned int)x<<' ';
	}
	cout<<endl<<endl;
	
	string nhead=head;
	change_head(nhead,h,w,start,m);
	
	string trans[k];
	create_transparencies(trans,k,m,s0,s1,nhead,s,siz,start);	
	
	cout<<endl;
	
}
