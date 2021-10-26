#include<bits/stdc++.h>
using namespace std;
unordered_map<int,int>l_history_table;
int g_history_register;
unordered_map<int,int>g_prediction_table;
unordered_map<int,int>l_prediction_table;
unordered_map<int,int>ch_prediction_table;
int iteration,matched = 0,mismatched = 0;
void tournament_simulator(int m,int n,int p,int q,int r,int pc,int act_val,int start_state)
{
	int l_prediction_entry = l_history_table[pc];
	int l_temp = pow(2,n);
	int p_temp = pow(2,p);
	int m_temp = pow(2,m);
	int n_temp = pow(2,n);
	int q_temp = pow(2,q);
	int r_temp = pow(2,r);
	int temp;
	/*
		 code segment for getting the local prediction and global prediciton value
	*/
	int l_prediction_value = (l_prediction_table[l_prediction_entry] >= l_temp/2 ) ? 1 : 0;   
	int g_prediction_value = (g_prediction_table[g_history_register] >= p_temp/2 ) ? 1 : 0;
	//cout<<l_prediction_value<<" "<<g_prediction_value<<endl;
	if(l_prediction_value == g_prediction_value)
	{
		if(l_prediction_value == 1) // if local prediciton is equal to global prediction and prediciton value is 1
		{
			/*
				based on the multiplexer value as 1 we increment the current state except for last state
				based on the multiplexer value as 0 we decrement the current state except for first state
			*/
			if(l_prediction_table[l_prediction_entry] != n_temp-1) l_prediction_table[l_prediction_entry] =l_prediction_table[l_prediction_entry] + 1;
			if(g_prediction_table[g_history_register] != q_temp - 1) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] + 1;
			int ch_value = ch_prediction_table[g_history_register];
			if(g_prediction_table[g_history_register] > ch_value)
			{
				if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
			}
			else
			{
				if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
			}
			g_history_register = (1 << (p-1))|(g_history_register >> 1);
			l_history_table[pc] = (1 << (m-1)) |(l_history_table[pc] >> 1);
		}
		else
		{
			/*
				based on the multiplexer value as 1 we increment the current state except for last state
				based on the multiplexer value as 0 we decrement the current state except for first state
			*/
			if(l_prediction_table[l_prediction_entry] != 0) l_history_table[l_prediction_entry] = l_prediction_table[l_prediction_entry] - 1;
			if(g_prediction_table[g_history_register] != 0) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] - 1;
			int ch_value = ch_prediction_table[g_history_register];
			if(g_prediction_table[g_history_register] > ch_value)
			{
				if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
			}
			else
			{
				if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
			}
			g_history_register = g_history_register >> 1;
			l_history_table[pc] = l_history_table[pc] >> 1;
		}
		if(l_prediction_value == act_val)matched++;
		else
		{
			/*modification of table if there is mismatch between prediction value and actual value of the branch */
				if(act_val == 1)
				{
					if(l_prediction_table[l_prediction_entry] != n_temp-1) l_prediction_table[l_prediction_entry] =l_prediction_table[l_prediction_entry] + 1;
					if(g_prediction_table[g_history_register] != q_temp - 1) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] + 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = (1 << (p-1))|(g_history_register >> 1);
					l_history_table[pc] = (1 << (m-1)) |(l_history_table[pc] >> 1);						
				}
				else
				{
					if(l_prediction_table[l_prediction_entry] != 0) l_history_table[l_prediction_entry] = l_prediction_table[l_prediction_entry] - 1;
					if(g_prediction_table[g_history_register] != 0) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] - 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = g_history_register >> 1;
					l_history_table[pc] = l_history_table[pc] >> 1;
				}
				mismatched++;
		}
	}
	else
	{
		temp = (pow(2,r))/2;    //l predictor is not equal to g predictor 
		if(ch_prediction_table[g_history_register] >= temp)
		{
			
			/*
				based on the difference between the prediction value and actual value
				we check whether the local predictor prediction is correct or global prediction is correct 
				and change the states as per the one whose prediction is correct
			*/
			if(act_val == g_prediction_value)
			{
				if(act_val == 1)
				{
					if(l_prediction_table[l_prediction_entry] != n_temp-1) l_prediction_table[l_prediction_entry] =l_prediction_table[l_prediction_entry] + 1;
					if(g_prediction_table[g_history_register] != q_temp - 1) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] + 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = (1 << (p-1))|(g_history_register >> 1);
					l_history_table[pc] = (1 << (m-1)) |(l_history_table[pc] >> 1);					
				}
				else
				{

					if(l_prediction_table[l_prediction_entry] != 0) l_history_table[l_prediction_entry] = l_prediction_table[l_prediction_entry] - 1;
					if(g_prediction_table[g_history_register] != 0) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] - 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = g_history_register >> 1;
					l_history_table[pc] = l_history_table[pc] >> 1;
				}
				matched++;
			}
			else mismatched++;
			
		}
		else
		{
			/*
				based on the difference between the prediction value and actual value
				we check whether the local predictor prediction is correct or global prediction is correct 
				we consider choice prediction changes also and correct it to predict for future predicitons 
				and change the states move states as per the one whose prediction is correct
			*/
			if(act_val == g_prediction_value)
			{
				if(act_val == 1)
				{
					if(l_prediction_table[l_prediction_entry] != n_temp-1) l_prediction_table[l_prediction_entry] =l_prediction_table[l_prediction_entry] + 1;
					if(g_prediction_table[g_history_register] != q_temp - 1) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] + 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = (1 << (p-1))|(g_history_register >> 1);
					l_history_table[pc] = (1 << (m-1)) |(l_history_table[pc] >> 1);					
				}
				else
				{

					if(l_prediction_table[l_prediction_entry] != 0) l_history_table[l_prediction_entry] = l_prediction_table[l_prediction_entry] - 1;
					if(g_prediction_table[g_history_register] != 0) g_prediction_table[g_history_register] = g_prediction_table[g_history_register] - 1;
					int ch_value = ch_prediction_table[g_history_register];
					if(g_prediction_table[g_history_register] > ch_value)
					{
						if(ch_prediction_table[g_history_register] != r_temp - 1)  ch_prediction_table[g_history_register] = ch_prediction_table[g_history_register] + 1;
					}
					else
					{
						if(ch_prediction_table[g_history_register] != 0) ch_prediction_table[g_history_register] =ch_prediction_table[g_history_register] - 1;
					}
					g_history_register = g_history_register >> 1;
					l_history_table[pc] = l_history_table[pc] >> 1;
				}		
				matched++;
			}
			
			
		}
	}
}
int main()
{
	/* 	m----------local history      3
		n----------local prediction   2
		p----------global history register 3,4,5
		q----------global prediction  2
		r----------choice prediction   2
	*/
	int m,n,p,q,r,shft_amt;
	cout<<"Enter the size of m (localhistory), n (local prediction),p (global history),q (global prediction),r (choice prediction)\n";
	cin>>m>>n>>p>>q>>r;
	cout<<"Enter your choice (1 or 2)\n1.Start state is 0 \n2.Start state is with all 1111's\n";
	int start_state;
	int choice;
	cin>>choice;
	switch(choice)
	{
		case 1: start_state = 0; break;
		case 2: start_state = pow(2,m-1);break;
	}
	/////////////////////////////////////////code segment1///////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
	uint8_t pc;
	shft_amt = 8-m;
	int a,b;
	a = 10000;
	while(a>0){ //PC:0b0100_0100
		/*
			shift amt is basically to get the last m bits of the branch to get the index
			of the local branch predictor
		*/
		pc =0b01000100;
		pc = pc<<shft_amt;
		pc = pc>>shft_amt;
		tournament_simulator(m,n,p,q,r,pc,1,start_state);
		b = 50;
		while (b>0)
		{ 	//PC: 0b0110_1100
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);
			b=b-2;
		}
		if(b <= 0)
		{
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,0,start_state);
		}
		a=a-1;
	}
	pc =0b01000100;
	pc = pc<<shft_amt;
	pc = pc>>shft_amt;
	tournament_simulator(m,n,p,q,r,pc,0,start_state);
	cout<<"The accuracy of the code segment-1 is "<<((matched)/((double)matched+mismatched))*100<<endl;
	//cout<<matched<<" "<<mismatched<<"\n";
	
	////////////////////////////////////codesegment2/////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	matched = 0;
	mismatched = 0;
	a = 0,b = 5;
	while(a<10000)
	{ //PC:0b0100_0100
		pc =0b01000100;
		pc = pc<<shft_amt;
		pc = pc>>shft_amt;
		tournament_simulator(m,n,p,q,r,pc,1,start_state);
		if (a%2==0)
		{ //PC: 0b0110_1100
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);
		}
		else
		{
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,0,start_state);
		}
		a=a+1;
		if (b==0)
		{
			
		}
	}
	pc = 0b01000100;
	pc = pc<<shft_amt;
	pc = pc>>shft_amt;
	tournament_simulator(m,n,p,q,r,pc,0,start_state);
	//cout<<matched<<" "<<mismatched<<endl;
	cout<<"The accuaracy of the codesegment-2 is "<<((matched)/((double)matched+mismatched))*100<<endl;
	matched = 0;
	mismatched = 0;
	m=10000;
	while(m>0)
	{ //PC:0b0100_0100
		pc =0b01000100;
		pc = pc<<shft_amt;
		pc = pc>>shft_amt;
		tournament_simulator(m,n,p,q,r,pc,1,start_state);
		a = m%2;
		if (a==2) 
		{//PC: 0b0110_1100
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);
		}
		else
		{
			pc = 0b01101100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			pc = pc << shft_amt;
			pc = pc >> shft_amt;
			tournament_simulator(m,n,p,q,r,pc,0,start_state);
		}
		b=(int) m/2;
		if (b==2)
		{//PC: 0b0111_0100
			pc =0b01110100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);
		}
		else
		{
			pc =0b01110100;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);

		}
		if (a!=b)
		{//PC: 0b1000_1000
			pc = 0b10001000;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			tournament_simulator(m,n,p,q,r,pc,1,start_state);
		}
		else
		{
			pc = 0b10001000;
			pc = pc<<shft_amt;
			pc = pc>>shft_amt;
			tournament_simulator(m,n,p,q,r,pc,0,start_state);
		}
		m=m-1;
		
	}
	pc =0b01000100;
	pc = pc<<shft_amt;
	pc = pc>>shft_amt;
	tournament_simulator(m,n,p,q,r,pc,0,start_state);
	//cout<<matched<<" "<<mismatched<<"\n";
	cout<<"The accuracy of the code-segment-3 is "<<((matched)/((double)matched+mismatched))*100<<endl;
	return 0;
}