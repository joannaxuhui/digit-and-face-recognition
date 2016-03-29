# include <iostream>
# include <string>
# include <fstream>
# include <map>
# include <stdio.h>
# include <stdlib.h>
# include <queue>
# include <math.h>
# include <string>
# include <iomanip>
using namespace std;
int sum=0;

map<string, double> prio;

vector <string> number;

map<string, int> fre;
   
      map<string, double > smooth( int v )
      {// try to use the number  fro 0 to 9 . the total number is 10;
          map<string, double> local;
		for(map<string, int >::iterator it = fre.begin(); it!=fre.end(); it++)
		{    
			double a = it->second;
			a= (a+v)/(5000+v*10);
			pair<string , double > pro(it->first, a);
			local.insert(pro);
			sum=sum+it->second;// the verify the correst number 
			//cout <<"["<< it->first <<":"<< it->second << "]"<< endl;
		}
          return local;
   }
   
	pair<string, double > max_pro( vector< pair<string, double > > & a)
		{  
		    double aa=a[0].second;
		    string bb=a[0].first;
		    for(int i=1; i< a.size() ;i++)
			{  
		      if(a[i].second>aa)
		      {
		       aa=a[i].second;
		       bb=a[i].first; 
		      }
		      else
				{;}
		     }
		    pair<string, double> pair_max(bb, aa);
		    
		    return pair_max;

		}

      pair< pair<string, string >, double>  find_max( map < pair<string, string >, double > & a )
      {
		
		map < pair<string, string> , double > ::iterator it= a.begin();
          double high= it->second;
          string s1= it->first.first;
		string s2= it ->first.second;
          for(it=a.begin(); it!=a.end(); it++)
    		{ 
               if(it->first.first!=it->first.second)
               {
			if(it->second > high)
				{
					high=it->second;
					s1=it->first.first;
					s2=it->first.second;
				}
			}
          }
         
         pair<string, string > pair_a(s1, s2);
         pair < pair<string, string > , double >  pair_b (pair_a, high);
         return pair_b;
         

      }

     double find_key_value(vector< pair<string, double > > & a, string& bb)
     {
         for(int i=0; i<a.size(); i++)
		{
			if(a[i].first==bb)
               return a[i].second;
		}

     }
        
int main(){
int ss=1;
ifstream file;
file.open("traininglabels");
string STRING;

while(!file.eof())
{
	getline(file,STRING);
     if(STRING.length()==0)
     break;
     number.push_back(STRING);
     pair<string,int> pair(STRING,1);
	if(fre.count(STRING))
		fre.at(STRING)++;
     else
		fre.insert(pair);
    
}
file.close();

//cout << "sum:" << sum << endl;

prio=smooth(ss);

/*(cout << "---------------------------------------" << " below is the  calculation of the related data " << endl;

cout << "-----------------the number-----"<< endl;


/*for(int i=0;i<number.size();i++)
{
	cout<<i<<":"<< number[i]<<" "<<flush;
}
*/
// read the number probility
// prio__ the map to store my probility

//
//___________________________________________________________________________


//cout<<"----------------------------------------" <<"below is the transforming of data the image" << endl;
ifstream image;
image.open("trainingimages");
string pic;
vector< int   > training_image_data;
while(!image.eof())
{   
    getline(image, pic);
    for(int i=0; i<28 ;i++)
		{    
			
			if(pic[i]==' ')
               {
               training_image_data.push_back(0);	
			}
			else if(pic[i]=='#' )
               {
 			training_image_data.push_back(1);
			}
     		else
			{
			training_image_data.push_back(1);
			}
		}
	
}

//cout << "------------"<< endl;

//cout <<"there should be 140000 lines , so the valid index for the image data should be from 0 to 3920000-1"<< endl;
//cout<< training_image_data.size()<< endl;
string cur;


map<string, vector< int > > stat_data;
int index=0;
for(int i=0;i<3920000;i++)
{
	if(i%(28*28)==0 && index<5000){	
		cur = number[index];
		index++;
	
	}

	if(stat_data.count(cur)==0)
     {
     
		vector< int > rank;
		rank.push_back(training_image_data[i]);
          pair<string, vector< int > > new_pair (cur, rank);
          stat_data.insert( new_pair);
          stat_data[cur][i%(28*28)]+=training_image_data[i];
	}
    else 
	{	
		if(stat_data[cur].size()<28*28)
          {
			stat_data[cur].push_back(training_image_data[i]);
		}
		stat_data[cur][i%(28*28)]+=training_image_data[i];
	    
	}
	
	
}




map<string, vector< double> > _probility;

//smooth(ss);


for(map<string, vector<int > > ::iterator it= stat_data.begin(); it!= stat_data.end(); it++)
{
	string local= it->first;
     vector<double> pro;
	double proi;
     for(int i=0; i< it->second.size(); i++)
	{
		double a = it->second[i]+ss;
          double b= fre[it->first]+ss;
          proi=a/b;
          pro.push_back(proi);
	}
     
     pair< string, vector<double> > proii(it->first, pro);
     _probility.insert(proii);

}

/*
for(map<string, vector< double> >:: iterator it=_probility.begin(); it!=_probility.end(); it++)
{
	cout<<"-------------------number:-------" << it->first<<endl;
     cout<<"----------------here is the start-----"<<endl;
	for(int i=0; i<it->second.size(); i++)
	{
          if(i%28==0)
			cout<<"["<<i<<":"<<it->second[i]<<"]"<<endl;
		     else
			cout << "["<<i<<":"<<it->second[i]<<"]"<<flush;
          
          if(i==it->second.size()-1)
 		cout<<"---------here is the end ----"<<endl;
	}

}*/

cout<<"-------------test------------"<<endl;

ifstream test_label;
test_label.open("testlabels");
vector< string > test_label_;
string label;

while(!test_label.eof())
{
	getline(test_label, label);
     if(label.length()==0)
	break;
	test_label_.push_back(label);

}
cout<<"-----here is the test reference-----"<<endl;

ifstream test_image;
test_image.open("testimages");

vector< char > final_test;
string test_line;
while(!test_image.eof())
{
	getline(test_image, test_line);
	for(int i=0; i<28; i++)
     {
      
		if(test_line[i]==' ')
		{
			final_test.push_back(' ');
		}
		else if(test_line[i]=='#')
		{
			final_test.push_back('#');
		}
		else
		{
			final_test.push_back('+');	
		}
    
	}


}

cout<< final_test.size()<< endl;

cout<<"the range should be 0-784000-1"<<endl;

vector< vector<char > > final_result;
int idx=0;
vector< char > new_int_group;	
for(int i=0; i<784000; i++)
{	
     if(i%(28*28)==0)
	{
	new_int_group.clear();	
	}
    char  a= final_test[i];
    new_int_group.push_back(a);
    if(i%(28*28)==783)
    final_result.push_back(new_int_group);
}


/*
for(int i=0 ; i< final_result.size(); i++)
{
  cout << "the index is :-------"<< i<<"--------"<<endl;
  for(int j=0; j<final_result[i].size(); j++)
  { 
     if(j%28==0 && j!=0)
	cout<<final_result[i][j]<< " "<<endl;
     else
	cout<<final_result[i][j] <<" "<<flush;  
  }
  cout<< "----------this is the end--------"<<endl;

}
*/
map<string, int > test_number_fre;
for(int i=0; i< test_label_.size();i++)
{
	string string_3=test_label_[i];
	if(test_number_fre.count(string_3)==0)
	{
		
          int a =1;
          pair<string, int> pair_4(string_3, a);
          test_number_fre.insert(pair_4);

	}
	else
	{
		test_number_fre[string_3]++;
	}
}

map<string, int > pass_test;
map< pair<string, string>, int > confusion;
map<string,vector<pair<string, double > > > p;
vector< vector<pair<string, double > > > q;
for(int i=0; i< final_result.size(); i++)
{         
          string right=test_label_[i];
	     vector< pair<string, double > > each_group;
		for(map<string, vector<double> >::iterator it= _probility.begin(); it!=_probility.end(); it++)
		{    
              string sss=it->first;
		    double p=log(fre[sss]);   		
		    for(int j=0;j< 28*28; j++)
			{
				if(final_result[i][j]==' ')
    				p=p+log(1-it->second[j]);
				else if(final_result[i][j]=='+' || final_result[i][j]=='#')
				p=p+log(it->second[j]);
			}
             pair<string, double > reference(it->first, p);
		   each_group.push_back(reference); 
    		 } 
           pair<string, double> picked_answer= max_pro(each_group);

           if(picked_answer.first==right)//judge right , plus 1
           {
			if(pass_test.count(right)==0)
			{
				int a =1;
 				pair<string, int > pair_6 (right, a);
				pass_test.insert(pair_6);	
			}
    			else
			{
				pass_test[right]++;				
			}
              pair< string, string > pair_a(right,right);
              if(confusion.count(pair_a)==0)
               {
				pair< string, string > pair_a(right,right);
                    int a=1;
                    pair<pair<string, string>, int> pair_b(pair_a, a);
				confusion.insert(pair_b);
               }
   			else
          		{
					confusion[pair_a]++;	
				}
 
              
		}
		else// judge wrong
			{
    				pair<string, string> pair_a(right, picked_answer.first);
                    if(confusion.count(pair_a)==0)
				{
					int a=1;
					pair< pair<string, string>, int > pair_b(pair_a, a);
					confusion.insert(pair_b);
				}
				else
				{
					confusion[pair_a]++;
				}
          		       		
			}
          
           q.push_back(each_group);
		 pair<string, vector< pair<string, double> > > pair_new(right, each_group);
           p.insert(pair_new);
}


map<pair<string, string>, double > confusion_rate;
for(map< pair<string, string>, int >::iterator it= confusion.begin(); it!=confusion.end(); it++)
{
  pair<string, string > s=it->first;
  string s2=s.first;
  int a= test_number_fre[s2];
  int b=it->second;
  double c=(double)b/(double)(a+ss);
  pair<pair<string, string>, double > pair_c(s,c);
  confusion_rate.insert(pair_c);
  	
}
map<string, double > accuracy;
for(map<string, int >::iterator it=pass_test.begin(); it!=pass_test.end(); it++)
{
	string b= it->first;
     double c= ((double)it->second+ss)/ (double) (test_number_fre[it->first]+ss);
     pair < string, double > pair_9(b, c);
	accuracy.insert(pair_9);
}

map< string, vector < pair< int, double > > > each_digit_accuracy;

for(int i=0; i< q.size(); i++)
{
    string b= test_label_[i];
    double c= find_key_value(q[i], b);

    if(each_digit_accuracy.count(b)==0)
    {
     vector< pair< int, double> > v1;
     pair<int , double > pair_9(i, c);
     v1.push_back(pair_9);
     pair< string, vector< pair<int, double > > >  pair_10(b, v1);
	each_digit_accuracy.insert(pair_10);
    }
    else
    {
     pair<int, double> pair_11(i, c);
	each_digit_accuracy[b].push_back(pair_11);
    }
   
}
cout<<"-----------the accuracy of each digit-------------------"<< endl;
for(map<string, double >::iterator it=accuracy.begin(); it!=accuracy.end(); it++)
{
	
	cout<< it->first <<" : "<< it->second<< ";"<<endl;

}

cout<< "----the confusion matrix---" << endl;
cout<<"   "<< flush;
double matrix[10][10];
for(map<pair <string, string >, double > ::iterator it= confusion_rate.begin(); it!=confusion_rate.end(); it++)
{
   // cout<< it->first.first <<":"<< it->first.second << "["<< it->second<<"]"<< " " << flush<< endl;
    int a=0;
    int b=0;
    // istringstream(it->first.first) >> a;
	sscanf(it->first.first.c_str(), "%d", &a);	
 	sscanf(it->first.second.c_str(),"%d", &b);
     double c=it->second;
     matrix[a][b]=c;
	
}
for(int i=0; i<10; i++)
{
cout<<i<<"       "<<flush;
}
cout<<"-------"<<endl;
for(int i=0; i< 10; i++)
{    
     cout<<i<<"  "<<flush;
	for(int j=0; j<10; j++)
	{
		printf("%2.2f    ",matrix[i][j]);
	}
	cout<< endl;
     cout<< endl;
}


queue<  pair <pair<string, string > , double > > heat;
pair< pair<string, string >, double > pp=find_max(confusion_rate);// to remove the first 0 number 
confusion_rate.erase(pp.first);
for(int i=0; i<4; i++)
{
	pair<pair<string, string >, double > p= find_max(confusion_rate);
     confusion_rate.erase(p.first);
     heat.push(p);
}
// find the lowest accuracy and lowest , then outpur the original _test _image

for(map<string, vector < pair<int, double > >  > :: iterator it=each_digit_accuracy.begin(); it!= each_digit_accuracy.end(); it++)
{   
    string a= it->first;
    int high=it->second[0].second;
    int low=it->second[0].second;
    int location_high;
    int location_low;
    for(int i=0; i< it->second.size(); i++)
	{
			if(it->second[i].second>high)
                {
				location_high=it->second[i].first;
                    high= it->second[i].first;
			 }
               if(it->second[i].second<low)
    			{
				location_low=it->second[i].first;
				low=it->second[i].second;
			} 	
	}
    cout<<"---------the report of :"<<it->first <<"---------"<<endl;
    cout<<"the test_image  that most happens is : (index)"<<location_high << endl;
    for(int i=0; i<28*28 ; i++)
    {
     if(i%28==0)
     cout<<final_result[location_high][i]<<endl;
     else
     cout<<final_result[location_high][i]<<flush; 
    }
    cout<<"------------------------------------"<<endl;
    cout<<"  "<<"the lowest rate that least happens is :(index) "<<location_low << endl;
    for(int i=0; i<28*28 ; i++)
    {
     if(i%28==0)
     cout<<final_result[location_low][i]<<endl;
     else
     cout<<final_result[location_low][i]<<flush; 
    }
   
}
   

for(int i =0; i< 4; i++)
{
	string s1= heat.front().first.first;
     string s2= heat.front().first.second;
     cout<<"the heat map for "<< s1 << " is "<< endl;
     for(int i=0; i< _probility[s1].size(); i++)
	{
		if(i%28==0 && i!=0)
			{
			cout<<endl;		
			}
          if(_probility[s1][i]>= 0 && _probility[s1][i] <0.1)
          cout<<"."<< " "<< flush;
		if(_probility[s1][i]>= 0.1 && _probility[s1][i] <0.2)
           cout<<"-"<< " "<< flush;
          if(_probility[s1][i]>= 0.2 && _probility[s1][i] <0.3)
		 cout<<"*"<<" "<<flush;
		if(_probility[s1][i]>= 0.3 && _probility[s1][i] <0.4)
		 cout<<"="<<" "<<flush;
		if(_probility[s1][i]>= 0.4 && _probility[s1][i] <0.5)
		 cout<<"_"<<" "<<flush; 
		if(_probility[s1][i]>= 0.5 && _probility[s1][i] <0.6)
		 cout<<"+"<<" "<<flush;
		if(_probility[s1][i]>= 0.6 && _probility[s1][i] <0.7)
		 cout<<"c"<<" "<<flush;
		if(_probility[s1][i]>= 0.7 && _probility[s1][i] <0.8)
    		 cout<<"D"<<" "<<flush;
		if(_probility[s1][i]>= 0.8 && _probility[s1][i] <0.9)
		 cout<<"N"<<" "<<flush;
		if(_probility[s1][i]>= 0.9 && _probility[s1][i] <=1.0)
		 cout<<"B"<<" "<<flush;


	}
    cout<< endl;
    cout<<"the heat map for "<< s2 << " is "<< endl;
   for(int i=0; i<_probility[s2].size(); i++)
	{
		if(i%28==0 && i!=0)
			{
			cout<<endl;		
			}
           if(_probility[s2][i]>= 0 && _probility[s2][i] <0.1)
          cout<<"."<< " "<< flush;
		if(_probility[s2][i]>= 0.1 && _probility[s2][i] <0.2)
           cout<<"-"<< " "<< flush;
          if(_probility[s2][i]>= 0.2 && _probility[s2][i] <0.3)
		 cout<<"*"<<" "<<flush;
		if(_probility[s2][i]>= 0.3 && _probility[s2][i] <0.4)
		 cout<<"="<<" "<<flush;
		if(_probility[s2][i]>= 0.4 && _probility[s2][i] <0.5)
		 cout<<"_"<<" "<<flush; 
		if(_probility[s2][i]>= 0.5 && _probility[s2][i] <0.6)
		 cout<<"+"<<" "<<flush;
		if(_probility[s2][i]>= 0.6 && _probility[s2][i] <0.7)
		 cout<<"c"<<" "<<flush;
		if(_probility[s2][i]>= 0.7 && _probility[s2][i] <0.8)
    		 cout<<"D"<<" "<<flush;
		if(_probility[s2][i]>= 0.8 && _probility[s2][i] <0.9)
		 cout<<"N"<<" "<<flush;
		if(_probility[s2][i]>= 0.9 && _probility[s2][i] <=1.0)
		 cout<<"B"<<" "<<flush;
	}
	cout << endl;
    vector<double > r;
    cout<< "the ratio that: "<< s1<<" over "<< s2 << " is :"<< endl;
     
    for(int i=0; i<28*28; i++)
	{
		double a = (double)_probility[s1][i]/(double) _probility[s2][i];
          r.push_back(log(a));

		if(i%28==0 && i!=0)
			{
			cout<<endl;		
			}
          if(r[i] <-1)
          cout<<"."<< " "<< flush;
		if(r[i]>= -1 && r[i] <-0.5)
           cout<<"-"<<" "<< flush;
          if(r[i]>= -0.5 && r[i] <0)
		 cout<<"*"<<" "<<flush;
		if(r[i]>= 0 && r[i] <0.5)
		 cout<<"="<<" "<<flush;
		if(r[i]>= 0.5 && r[i] <1.5)
		 cout<<"_"<<" "<<flush; 
		if(r[i]>= 1.5 && r[i] <2)
		 cout<<"+"<<" "<<flush;
		if(r[i]>= 2 && r[i] <2.5)
		 cout<<"c"<<" "<<flush;
		if(r[i]>= 2.5 && r[i] <3)
    		 cout<<"D"<<" "<<flush;
		if(r[i]>= 3 && r[i] <3.5)
		 cout<<"Y"<<" "<<flush;
		if(r[i]>= 3.5 && r[i] <=4)
		 cout<<"Z"<<" "<<flush;
		if(r[i]>4)
		cout<<"M"<<" "<<flush;
     }
     
      
    heat.pop();

}












return 0;
}
