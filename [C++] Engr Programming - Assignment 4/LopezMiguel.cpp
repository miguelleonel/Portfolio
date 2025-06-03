// Filename: Assignment4.cpp
// EE 5103 Assignment 4
// Miguel Lopez
// 04/13/2021

// NOTE TO GRADER
// If I understood HW correctly, and understood professor correctly,
// There are a lot of places with "least precipitation" (ie. 0)
// Outputted # of places that would be listed for 0 precipitation.
// Program works well for finding most precipitation...

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

class Weather
{
	private:
	vector<string> myData1,myData2,myData3,myData5,myData6,myData7;
	vector<string> myArray,myIDs,myNames;
	vector<int> myData4;
	string data1,data2,data3,data4,data5,data6,data7;
	int Data4;
	int size,size2;
	
	public:
	int GetData()
	{
		ifstream data ("20180101.csv");
		if (!data)
		{
			cerr << "There was an error opening file.\n";
			return 0;
		}
		
		while (data.good())
		{
			getline(data,data1,',');
			myData1.push_back(data1);
			getline(data,data2,',');
			myData2.push_back(data2);
			getline(data,data3,',');
			myData3.push_back(data3);
			getline(data,data4,',');
			Data4 = stoi(data4);	// converting string to int.
			myData4.push_back(Data4);
			getline(data,data5,',');
			myData5.push_back(data5);
			getline(data,data6,','); 
			myData6.push_back(data6);
			getline(data,data7,'\n');
			myData7.push_back(data7);
		}
		size = myData1.size()-1;			// all myData should be same size.
		data.close();
		return 0;
	}
	
		void GetText ()
	{
		ifstream file ("ghcnd-stations.txt");
		string temp;
		if (!file)
		{
			cerr << "There was an error opening file.\n";
			return;
		}
		
		while(file.good())
		{
			getline(file,temp);
			myArray.push_back(temp);
		}
		file.close();
	}
	void GetNames(string name)
	{
		size2 = 108081;
		string tmp;
		stringstream buffer;
		for (int i = 0; i<size2; i++)
		{
			for (int j = 0; j<11; j++)
			{
				buffer<<myArray[i][j];
			}
			buffer<<endl;
		}
		while (buffer >> tmp) 
		{
		  myIDs.push_back(tmp);
		}
		buffer.str(std::string());
		buffer.clear();
		
		for(int i = 0; i<size2; i++)
		{
			if(myIDs[i]==name)
			{
				int n = i+1;
				for (; i<n; i++)
				{
					for (int j = 41; j<71; j++)
					{
						cout<<myArray[i][j];
					}
					cout<<"\n";
				}
			}
		}
	}
	
	void AvgMax()
	{
		int temp=0, count=0;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="TMAX")
			{
				temp+=myData4[i];
				count++;
			}
		}
		temp = (float) temp / count;
		cout<<"The average maximum temperature of the world is "<<temp<<endl;
	}
	
	void AvgMin()
	{
		int temp=0, count=0;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="TMIN")
			{
				temp+=myData4[i];
				count++;
			}
		}
		temp = (float) temp / count;
		cout<<"The average minimum temperature of the world is "<<temp<<endl;
	}
	
	void MaxTemp() 
	{
		int max=0;
		string maxName;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="TMAX")
			{
				if(myData4[i]>max)
				{
					max = myData4[i];
					maxName = myData1[i];
				}
			}
		}
		cout<<"The maximum temperature of "<<max<<" was at "<<endl;
		GetNames(maxName);
	}
	
	void MinTemp()
	{
		int min=0;
		string minName;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="TMIN")
			{
				if(myData4[i]<min)
				{
					min = myData4[i];
					minName = myData1[i];
				}
			}
		}
		cout<<"The minimum temperature of "<<min<<" was at "<<endl;
		GetNames(minName);
	}
	
	void LeastArid()
	{
		int arid=0, count=0;
		string aridName;
		vector<string> aridNames;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="PRCP")
			{
				if(myData4[i]<arid)	// change this logic to have most/least arid place(s).
				{
					arid = myData4[i];
					aridName = myData1[i];
				}
			}
			
		}
		for(int i=0;i<size;i++)
		{
			if(myData4[i]==arid)
			{
				aridNames.push_back(myData1[i]);
				count++;
			}
		}

		cout<<"Least precipitation of "<<arid<<" which was at "<<count<<" places. Far too many to list."<<endl;
		
		
		/*
		for(int i=0;i<count;i++)
		{
			GetNames(aridNames[i]);
		}
		*/
	}
	
		void MostArid()
	{
		int arid=0, count=0;
		string aridName;
		vector<string> aridNames;
		for(int i=0;i<size;i++)
		{
			if(myData3[i]=="PRCP")
			{
				if(myData4[i]>arid)	// change this logic to have most/least arid place(s).
				{
					arid = myData4[i];
					aridName = myData1[i];
				}
			}
			
		}
		for(int i=0;i<size;i++)
		{
			if(myData4[i]==arid)
			{
				aridNames.push_back(myData1[i]);
				count++;
			}
		}

		cout<<"Most precipitation of "<<arid<<" was at "<<endl;
		for(int i=0;i<count;i++)
		{
			GetNames(aridNames[i]);
		}
	}
	
	
};

int main()
{
	
	Weather Mig;
	Mig.GetData();	// initializing values with data from csv file
	Mig.GetText();	// initializing text file.
	Mig.MaxTemp();	
	Mig.MinTemp();
	Mig.AvgMax();
	Mig.AvgMin();
	Mig.LeastArid(); 
	Mig.MostArid();
	return 0;
}
