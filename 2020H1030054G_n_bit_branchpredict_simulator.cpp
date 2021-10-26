#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>ump;
int curstate = 0,matched = 0,mismatched = 0,iteration = 0;
void n_bit_simulator(int predictor_type,int start_state,vector<int>&actual_branch_Op,int btype,int pred_val)
{
	curstate = ump[btype];
	int totalstates = pow(2,predictor_type) - 1;
	if(curstate > (totalstates)/2)//condition for branch is taken
	{
		if(actual_branch_Op[iteration] == 1) {matched++;}/*branch prediction is taken and actual output is same*/
		else 
		{
			mismatched++;  /*branch prediction is missed with actual output*/
		}
	}
	else
	{
		if(actual_branch_Op[iteration] == 0) {matched++;} /*branch prediction is taken and actual output is same*/
		else mismatched++; 
	}
	//cout<<"totalstates "<<totalstates;
	if(curstate == totalstates)
	{
		if(pred_val == 0) { curstate = curstate - 1;} /*if curstate is end state and input value is zero which means decrease cur state*/
	}
	else if(curstate == 0)
	{
		if(pred_val == 1) { curstate = curstate + 1;}/*if curstate is start state and input value is one which means move right*/
	}
	else
	{
		if(pred_val == 0) curstate = curstate - 1;/*if not both the above cases just increment/decrement based on input branch value*/
		else curstate = curstate + 1;
	}
	
	//cout<<prevstate<<" "<<curstate<<"\n";
	//cout<<curstate<<" "<<prevstate<<"\n";
	iteration++;
	ump[btype] = curstate;    //just storing the current state for using it for next iterations
}
int main()
{
    //std::ifstream inFile("branchOutcome1.txt");
	ifstream file1("branchOutcome1.txt");
	ifstream file2("branchOutcome2.txt");
	ifstream file3("branchOutcome3.txt");
	vector<int>branchOp1;
	vector<int>branchOp2;
	vector<int>branchOp3;
	
	string data = "";
	while(getline(file1, data,','))
	{
		if(data == "T")
			branchOp1.push_back(1);  /* read data from file and put it in vectors to use for prediction verification*/
		else
			branchOp1.push_back(0);
	}
	file1.close();
	data = "";
	while(getline(file2, data,','))
	{
		if(data == "T")
			branchOp2.push_back(1);
		else
			branchOp2.push_back(0);
	}
	file2.close();
	data = "";
	while(getline(file3, data,','))
	{
		if(data == "T")
			branchOp3.push_back(1);
		else
			branchOp3.push_back(0);
	}
	file3.close();
	
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////Code Segment - 1//////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	
	//cout<<branchOp1.size()<<" "<<branchOp2.size()<<" "<<branchOp3.size()<<endl;	
	int predictor_type,start_state = 0,a,b,btype,choice,ttlstates;
	cout<<"Enter the type of predictor (EX: 1 or 2 or 3 )\n";
	cin>>predictor_type;
	ttlstates = pow(2,predictor_type);
	cout<<"Enter your choice to\n 1. start state is 0\n 2. start state is all 11111 \n 3. start state is random\n";
	cin>>choice;
	/*
		code for selecting the start state 1.start state is zero 2. start state is last one 3. Random state
	*/
	switch(choice)
	{	
		case 1 : start_state = 0; break;
		case 2 : start_state = ttlstates - 1;break;
		case 3 : start_state = rand()%ttlstates;			
	}
	ump[4] = start_state;
	ump[12] = start_state;
	a=10000;
	while(a>0){ //PC:0b0100_0100
		b=50;
		btype = 4;
		n_bit_simulator(predictor_type,start_state,branchOp1,btype,1);
		while (b>0)
		{ 	//PC: 0b0110_1100
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp1,btype,1);
			b=b-2;
		}
		
		if(b<=0)
		{
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp1,btype,0);
		}
		a=a-1;
	}
	btype = 4;
	n_bit_simulator(predictor_type,start_state,branchOp1,btype,0);
	//cout<<iteration<<"\n";
	//cout<<matched<<" "<<mismatched<<"\n";
	cout<<"accuracy of code-segment 1 is  "<<(((matched/(double)branchOp1.size()))*100)<<"\n";
	
	
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////Code Segment - 2//////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	
	ump[4] = start_state;
	ump[12] = start_state;
	iteration = 0;
	matched = 0;
	mismatched =0;
	a = 0,b = 5;
	while(a<10000)
	{ //PC:0b0100_0100
		btype = 4;
		n_bit_simulator(predictor_type,start_state,branchOp2,btype,1);
		if (a%2==0)
		{ //PC: 0b0110_1100
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp2,btype,1);
		}
		else
		{
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp2,btype,0);
		}
		a=a+1;
		if (b==0)
		{
			
		}
	}
	//cout<<cbt+1<<"\n";
	btype = 4;
	n_bit_simulator(predictor_type,start_state,branchOp2,btype,0);
	//cout<<matched<<" "<<mismatched<<"\n";
	cout<<"accuracy of codesegment2  is "<<(((matched/(double)branchOp2.size()))*100)<<"\n";
	
	/////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////Code Segment - 3//////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////
	int m;
	ump[4] = start_state;
	ump[12] = start_state;
	ump[8] = start_state;
	iteration = 0;
	matched = 0;
	mismatched =0;
	m=10000;
	while(m>0)
	{ //PC:0b0100_0100
		btype = 4;
		n_bit_simulator(predictor_type,start_state,branchOp3,btype,1);
		a = m%2;
		if (a==2) 
		{//PC: 0b0110_1100
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,1);
			a=0;
		}
		else
		{
			btype = 12;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,0);
		}
		b=(int) m/2;
		if (b==2)
		{//PC: 0b0111_0100
			btype = 4;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,1);
			b=0;
		}
		else
		{
			btype = 4;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,0);
		}
		if (a!=b)
		{//PC: 0b1000_1000
			btype = 8;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,1);
			m=m-2;
		}
		else
		{
			btype = 8;
			n_bit_simulator(predictor_type,start_state,branchOp3,btype,0);
		}
		m=m-1;
		
	}
	btype = 4;
	n_bit_simulator(predictor_type,start_state,branchOp3,btype,0);
	
	//cout<<matched<<" "<<mismatched<<"\n";
	cout<<"accuracy of codesegment3  is "<<(((matched/(double)branchOp3.size()))*100)<<"\n";
    return 0;
}