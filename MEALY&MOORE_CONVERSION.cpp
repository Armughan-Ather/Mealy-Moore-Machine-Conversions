#include<iostream>
#include <bits/stdc++.h>
using namespace std;

struct incomingOutput {	
	//to store the incoming output to a state(used in mealy to moore conversion)
    string out[10] = { "-11","-11","-11","-11","-11","-11","-11","-11","-11","-11" };	//to store different outputs coming to same state
    string stateName;
    bool newStateNeeded = false;
};
string **transitions;	//to store transitions
int n;	//to store total no of states
int numTransitions;	//to store total no of transitions	
string *states;	//to store states
string *output;	//to store state outputs
	
void mooreToMealy()
{
	//taking inputs
	for(int i=0;i<n;i++)
	{
		cout<<"Enter state "<<i+1<<" name : ";
		cin>>states[i];
		cout<<"Enter state "<<i+1<<" output : ";
		cin>>output[i];	
	}
	for(int i=0;i<numTransitions;i++)
	{
		cout<<i+1<<". Transtion from state : ";
		cin>>transitions[i][0];
		cout<<"  With Input : ";
		cin>>transitions[i][2];
		cout<<"  To State : ";
		cin>>transitions[i][1];
	}
	for(int i=0;i<numTransitions;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(transitions[i][1]==states[j])
			{
				transitions[i][3]=output[j];
				break;
			}
		}
	}
	cout<<"moore transitions (from input) :\n";
	for(int i=0;i<numTransitions;i++)
	{
		cout<<"      "<<transitions[i][2]<<"\n";
		cout<<transitions[i][0]<<" ----------------> "<<transitions[i][1]<<"/"<<transitions[i][3]<<endl;
	}
	cout<<"\nmealy transitions : \n";
	for(int i=0;i<numTransitions;i++)
	{
		cout<<"      "<<transitions[i][2]<<" / "<<transitions[i][3]<<"\n";
		cout<<transitions[i][0]<<" ----------------> "<<transitions[i][1]<<endl;
	}
	return;
}
string getOutput(int numTransitions,int n,string state,string **transitions) {
    string str;
    for (int i = 0; i < numTransitions; i++) 
	{
        for (int j = 0; j < n; j++) 
		{
            if (state == transitions[i][1]) 
			{
                str = transitions[i][3];
            }
        }
    }
    return str;
}

void mealyToMoore()
{
	incomingOutput io[n];	//used to store incoming transitions to a state
	//taking inputs
	for(int i=0;i<n;i++)
	{
		cout<<"Enter state "<<i+1<<" name : ";
		cin>>states[i];
	}
	for(int i=0;i<numTransitions;i++)
	{
		string temp;
		cout<<i+1<<". Transtion from state : ";
		cin>>transitions[i][0];
		cout<<"  With Input : ";
		cin>>transitions[i][2];
		cout<<"  And Output : ";
		cin>>transitions[i][3];
		cout<<"  To State : ";
		cin>>transitions[i][1];
	}
	//storing data in incomingOutput struct 
	for(int i=0;i<numTransitions;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(transitions[i][1]==states[j])
			{
				int a=0;
				while(1)
				{
					if(io[j].out[a]==transitions[i][3])
					{
						break;
					}
					else if(io[j].out[a]=="-11")
					{
						io[j].out[a]=transitions[i][3];
						io[j].stateName=transitions[i][1];
						break;
					}
					a++;
				}
				
				break;
			}
		}
	}
	//checking if converting single state into multiple state is needed(if a state has 2 different incoming outputs)
	for(int i=0;i<n;i++)
	{
		string str=io[i].out[0];
		for(int j=0;j<10;j++)
		{
			if(str!=io[i].out[j] && io[i].out[j]!="-11")
			{
				io[i].newStateNeeded=true;
				break;
			}
		}
	}
	cout<<"mealy transitions (from input) : \n";
	for(int i=0;i<numTransitions;i++)
	{
		cout<<"      "<<transitions[i][2]<<" / "<<transitions[i][3]<<"\n";
		cout<<transitions[i][0]<<" ----------------> "<<transitions[i][1]<<endl;
	}
	cout<<"\nmoore transitions :\n";
	for(int i=0;i<numTransitions;i++)
	{
		for(int j=0;j<n;j++)
		{
			if(io[j].stateName==transitions[i][0] && io[j].newStateNeeded)
			{	
				//for the case where single state has been converted to multiple states 
				//each state outgoing transitions must be the same as initial state(the state which was converted into multiple states) outgoing transition's
				for(int k=0;k<10;k++)
				{
					int flag=0;
					if(io[j].out[k]!="-11")
					{
						string arr[10]={"-11","-11","-11","-11","-11","-11","-11","-11","-11","-11"};
						for(int l=0;l<10;l++)	//to make sure that each different output get no more than 1 new state for each
						{
							if(arr[l]=="-11")
							{
								arr[l]=io[j].out[k];
								break;
							}
							else if(arr[l]==io[j].out[k])
							{
								flag=1;
								break;
							}
							
						}
						if(flag==1)
						{	
							break;
						}
						string s=io[j].stateName+"/"+io[j].out[k];
						cout<<"      "<<transitions[i][2]<<"\n";
						cout<<s<<" ----------------> "<<transitions[i][1]<<"/"<<transitions[i][3]<<endl;
						transitions[i][4]="1";		
					}
					if(flag==1)
					{
						break;
					}
				}
				break;
			}
			else if(io[j].stateName==transitions[i][1] && io[j].newStateNeeded)
			{	
				//for the case where incoming transitions have different outputs(breaking single state into more states)
				for(int k=0;k<10;k++)
				{
					if(io[j].out[k]!="-11")
					{
						if(io[j].out[k]==transitions[i][3])
						{
							string s=io[j].stateName+"/"+io[j].out[k];
							string str=getOutput(numTransitions,n,transitions[i][0],transitions);
							str=transitions[i][0]+"/"+str;
							cout<<"      "<<transitions[i][2]<<"\n";
							cout<<str<<" ----------------> "<<s<<endl;
							transitions[i][4]="1";
							break;
						}
							
					}
				}
				break;
			}
		}	
	}
	for(int i=0;i<numTransitions;i++)
	{
		if(transitions[i][4]!="1")	
		{
			//for the states which does not get changed after conversion(no changes in incoming or outgoing transitions)
			string str=getOutput(numTransitions,n,transitions[i][0],transitions);
			str=transitions[i][0]+"/"+str;
			cout<<"      "<<transitions[i][2]<<"\n";
			cout<<str<<" ----------------> "<<transitions[i][1]<<"/"<<transitions[i][3]<<endl;
			
		}
	}
	return;
}

int main() 
{
    
    // Asking user for the type of conversion
    cout << "1.Moore To Mealy Conversion\n2.Mealy To Moore Conversion\nYour Choice : ";
    int conversionType;
    cin >> conversionType;
	if(conversionType!=1 && conversionType!=2)
	{
		cout<<"Invalid Input\nExiting";
		exit(0);	
	}
    // Asking for the total number of states and transitions
    cout << "Enter total number of states: ";
    cin >> n;
    cout << "Enter total number of transitions: ";
    cin >> numTransitions;

    states=new string[n];
    output=new string[n];
    transitions = new string*[numTransitions];
    
    // Allocating memory for transition details array
    for (int i = 0; i < numTransitions; i++) 
	{
        transitions[i] = new string[5];
    }
	
	for(int i=0;i<numTransitions;i++)
	{
		for(int j=0;j<5;j++)
		{
			transitions[i][j]="";	
		}	
	}
    // Asking for state names   
	if(conversionType==1)
	{
		mooreToMealy();
	}
	else if(conversionType==2)
	{
		mealyToMoore();
	}
    // Deallocating memory for the transitions array
    for (int i = 0; i < numTransitions; i++) 
	{
        delete[] transitions[i];
    }
    delete[] transitions;
	delete[] states;
	delete[] output;
    return 0;
}
