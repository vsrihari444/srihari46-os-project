#include<iostream>

#include<algorithm>

#include<vector>

#include<unistd.h>

#include<iomanip>

#include <fstream>

using namespace std;

int tq=0,ti=1;

void pexecutor(vector<int> &hpr_queue,vector<int> &mpr_queue,vector<int> &lpr_queue,vector<int> &vbt,vector<int> &TAT,vector<int> &CT,vector<int> &WT,int pbt[])

{

	 int x=0,y=0,z=0;

	 cout<<"\nExecution started\n";

	while(hpr_queue.empty()==false||mpr_queue.empty()==false||lpr_queue.empty()==false)

	{

		if(hpr_queue.empty()==false)

		{

			cout<<"\nProcessing High priority queue for time quantum=10 seconds using Round Robin Scheduling having time quantum=4\n....";

			for(int a0=1;a0<=10;a0++ )

			{

				if(hpr_queue.empty()==false)

				{

				x=hpr_queue.front();

				if(tq==4)

				{

					int ref;

					ref=hpr_queue.front();

					hpr_queue.erase(hpr_queue.begin());

					hpr_queue.push_back(ref);

					tq=0;

					x=hpr_queue.front();

				}

				if(vbt[x]!=0)

				{

					vbt[x]=vbt[x]-1;

				}

				if(vbt[x]==0)

				{

					//CT[x]=ti;

					TAT[x]=ti;//CT[x]-0 arrival time for all processes considered as 0 since it is not mentioned in the question

					WT[x]=TAT[x]-pbt[x];

					hpr_queue.erase(hpr_queue.begin());

				}

			    tq++;

				ti++;

				sleep(1);

			}

			}

		}

		if(mpr_queue.empty()==false)

		{

			cout<<"\nProcessing Medium priority queue for time quantum=10 seconds using Priority Scheduling\n....";

			for(int a1=1;a1<=10;a1++ )

			{

				if(mpr_queue.empty()==false)

				{

				y=mpr_queue.front();

					if(vbt[y]!=0)

				{

					vbt[y]=vbt[y]-1;

				}

				if(vbt[y]==0)

				{

					CT[y]=ti;

					TAT[y]=CT[y]-0;//arrival time for all processes considered as 0 since it is not mentioned in the question

					WT[y]=TAT[y]-pbt[y];

					mpr_queue.erase(mpr_queue.begin());

				}

				

				ti++;

				sleep(1);

			}

			}

		}

		if(lpr_queue.empty()==false)

		{

			cout<<"\nProcessing Low priority queue for time quantum=10 seconds using FCFS Scheduling\n....";

			for(int a2=1;a2<=10;a2++ )

			{

				if(lpr_queue.empty()==false)

				{

				z=lpr_queue.front();

					if(vbt[z]!=0)

				{

					vbt[z]=vbt[z]-1;

				}

				if(vbt[z]==0)

				{

					CT[z]=ti;

					TAT[z]=CT[z]-0;//arrival time for all processes considered as 0 since it is not mentioned in the question

					WT[z]=TAT[z]-pbt[z];

					lpr_queue.erase(lpr_queue.begin());

				}

				 ti++;

				 sleep(1);

			    }

			}

		}

	}

	return;

}

int main()

{

	ofstream fout;

	fout.open("tejafile1.txt", ios::app); 

	int n,Arrival_time=0;

	vector<int> hpr_queue,mpr_queue,lpr_queue,TAT,CT,WT,vbt;

	cout<<setw(320)<<"Multilevel queue CPU scheduling algorithm\n";

	cout<<"\n  Enter number of processess : ";

	cin>>n;

	int pid_pr[n],pbt[n];

	cout<<"\n\n  ************* Note : Priority should be 1 to 15 and higher the number higher the priority**************** \n\n";

	cout<<"--->1 to 5 considered as low priority\n--->6 to 10 considered as medium priority\n--->11 to 15 considered as high priority\n";

	for(int i=0;i<n;i++)

	{

		cout<<"\n enter priority number for p"<<i<<" : ";

		cin>>pid_pr[i];

		cout<<"\n enter burst time for p"<<i<<" : ";

		cin>>pbt[i];

		vbt.push_back(pbt[i]);

	}

	

	for(int i1=0;i1<n;i1++)

	{

		TAT.push_back(i1);

		CT.push_back(i1);

        WT.push_back(i1);

		if(pid_pr[i1]<=5)

		{

			lpr_queue.push_back(i1);

		 } 

		 if(pid_pr[i1]>=6 && pid_pr[i1]<=10)

		 {

		 	mpr_queue.push_back(i1);

		 }

		 if(pid_pr[i1]>=11)

		 {

		 	hpr_queue.push_back(i1);

		 }

	}

if(mpr_queue.empty()==false)

	for (int i = 0; i < mpr_queue.size()-1; i++) 

   { 

     for (int j = 0; j < mpr_queue.size()-i-1; j++) 

     { 

        if (pid_pr[mpr_queue[j]] < pid_pr[mpr_queue[j+1]]) 

        { 

           swap(mpr_queue[j], mpr_queue[j+1]); 

           

        } 

     } 

 }

    pexecutor(hpr_queue,mpr_queue,lpr_queue,vbt,TAT,CT,WT,pbt);

	cout<<"\n\nprocess ID | Priority | Burst Time | Turn Around Time | Waiting Time\n";

	fout<<"\nprocess ID | Priority | Burst Time | Turn Around Time | Waiting Time\n";

	int avgwt=0,avgtat=0;

for(int d=0;d<n;d++)

{

	cout<<"p"<<d<<setw(11)<<"| "<<pid_pr[d]<<setw(10)<<"| "<<pbt[d]<<setw(13)<<"| "<<TAT[d]<<setw(17)<<"| "<<WT[d]<<"\n";

    fout<<"p"<<d<<setw(11)<<"| "<<pid_pr[d]<<setw(10)<<"| "<<pbt[d]<<setw(13)<<"| "<<TAT[d]<<setw(17)<<"| "<<WT[d]<<"\n";

    avgwt=avgwt+WT[d];

    avgtat=avgtat+TAT[d];

}

avgwt=avgwt/WT.size();

avgtat=avgtat/TAT.size();

cout<<"\n  Average Waiting Time = "<<avgwt<<"\n  Average Turn Around Time = "<<avgtat<<"\n";

fout<<"  Average Waiting Time = "<<avgwt<<"\n  Average Turn Around Time = "<<avgtat<<"\n";

cout<<"\n--->You can also see the output in a text file saved as tejafile1.txt in the same directory where this program file is present.";

fout.close();
}