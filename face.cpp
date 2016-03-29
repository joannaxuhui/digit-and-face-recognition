# include <iostream>
# include <string>
# include <fstream>
# include <map>
# include <stdio.h>
# include <stdlib.h>
# include <queue>
# include <math.h>
# include <string>

using namespace std;
vector< string > train_label_string;
int fre[2];
int sum=0;
vector< char > train_data;
vector< vector <char > > train_base;

int zero[60*70];
int one[60*70];

vector< char > each_group;

double pro_0;
double pro_1;

double p;

int main()
{
	ifstream file;
     file.open("facedatatrainlabels");
	string string1;
     while(!file.eof())
		{
			getline(file, string1);
               if(string1.length()==0)
			break;
			train_label_string.push_back(string1);
			if(string1.at(0)=='0')
               fre[0]++;
  			else
 			fre[1]++;	
		}
		 sum= fre[0]+fre[1];
		 pro_1= (double)fre[1]/(double)sum;
		 pro_0=(double)fre[0]/(double)sum;


     
  
       ifstream train;
	  train.open("facedatatrain");
       string string2;
	  while(!train.eof())
		{
				getline(train, string2);
				if(string2.length()==0)
				break;
				for(int i=0; i< string2.length(); i++ )
				{    
					if(string2.at(i)==' ')
					train_data.push_back(' ');
					if(string2.at(i)=='#')
					train_data.push_back('#');
				}
			
        }
      
        /* for(int i=0; i< train_data.size(); i++)
		{
			if(i%60*70==0 && i!=0)
			{
			 each_group.clear();
			}
               each_group.push_back(train_data[i]);
			if(i% 60*70 == 60*70-1)
			train_base.push_back(each_group);
	     }

	     for(int i=0; i<train_base.size(); i++)
		{  
		   cout<< "the index is :"<<i << endl;
		   for(int j=0; j< train_base[i].size(); j++)
			{
				if(j%60==0)
				cout<<endl;
				cout<< train_base[i][j]<<flush;
			}
			cout<<endl;
		}*/
     string s;
     cout << train_label_string.size()<<endl;
	for(int i=0; i<train_data.size(); i++)
	{ 
	  if(i%(60*70)==0 )
        s =train_label_string[i%(60*70)];
       if(s =="1")
       {
		
			//cout<< train_base[i].size();
			one[i%(60*70)]+=train_data[i];
	  }
      else
	  {
			zero[i%(60*70)]+=train_data[i];
 	  }
       
     }


double p_0[60*70];
double p_1[60*70];

     for(int i=0; i< 60*70; i++)
	{
		p_0[i]=(double)zero[i]/(double)fre[0];
		p_1[i]=(double)one[i]/(double)fre[1];
     }

cout<<"-------test here-----"<< cout<< endl;
vector< string > right;
vector< int  > test_data;

vector<string > picked_answer;

ifstream test;
string string3;
test.open("facedatatestlabels");
while(!test.eof())
{
	getline(test, string3);
	if(string3.length()==0)
	break;
	right.push_back(string3);

}

ifstream test_file;
string string4;
test_file.open("facedatatest");
while(!test_file.eof())
{
	getline(test_file, string4);
	if(string4.length()==0)
	break;
	for(int i=0; i< string4.length(); i++)
	{
		if(string4.at(i)==' ')
          test_data.push_back(0);
		else
		test_data.push_back(1);
	}

}

map<string, pair<double, double> > final;

double p0=log(pro_0);
double p1=log(pro_1);
int index=0;
string c;
for(int i=0; i<test_data.size()%(60*70); i++)
{       
	  c=right[index];
       if(i% (60*70)==0 && i!=0)
	  {
		p0=log(pro_0);
		p1=log(pro_1);
          index++;
	  }
      if(test_data[i]==1)
	 {
      p0=p0+log(p_0[i%(60*70)]);
      p1=p1+log(p_1[i%(60*70)]);
 
	 }

     else{
	p0=p0+log(1-p_0[i%(60*70)]);
     p1=p1+log(1-p_1[i%(60*70)]);		
	}
     
     if(i% (60*70)==60*70-1)
	{
       pair<double, double > a(p0, p1);
       pair<string, pair<double, double> > b(c,a);
	  final.insert(b);
	}

}

int correct0;
int correct1;
int wrong1_0;
int wrong0_1;

for(map<string ,pair<double, double > > :: iterator it=final.begin(); it!=final.end(); it++)
{
  if(it->first=="0")
  {
     if(it->second.first > it->second.second)
	 {correct0++;}
      else
	 wrong0_1++;
  }
  else
  {
    if(it->second.second>it->second.first)
    correct1++;
    else
     wrong1_0++;
  }

}

int fre0;
int fre1;
for(int i=0; i< right.size(); i++)
{
 if(right[i]=="0")
 fre0 ++;
 else
 fre1 ++;

}/*
cout<< fre0<<endl;
cout<< fre1<< endl;
cout<< correct1<<endl;
cout << correct0<< endl;
cout<< wrong1_0<<endl;
cout<< wrong0_1<<endl;
cout<< final.size()<< endl;
double accuracy1=double(correct1)/(double)(fre1);
double accuracy0=double(correct0)/(double)(fre0);
double wrong1=double(wrong1_0)/(double)(fre0);
double wrong0=double(wrong0_1)/(double)(fre1);

cout<< "the accuracy for 0 is :"<< accuracy0<<endl;
cout<<"the accuracy for 1 is :"<< accuracy1 << endl;

cout<< "---the confusion matrix----"<< endl;
cout<<"   "<<0<<"     "<<"1"<< endl;
cout<<0<<"  "<< accuracy0<<"   "<<wrong0<<endl;
cout<<1<<"  "<< accuracy1<<"   "<<wrong1<<endl;
*/
for(int i=0 ; i<60*70; i++)
{
  if(i %60==0)
  cout<< endl;
  cout<< p_0[i]<< " "<< flush;
}
return 0;
}
