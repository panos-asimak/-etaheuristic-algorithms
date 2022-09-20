#include<iostream>
#include<fstream>
#include<istream>
#include<string>
#include<cstdlib>
#include<vector>
#include<time.h>
#include<cmath>
#include<math.h>

#define PosostoMeiwsisTh_SA 0.85//to pososto pou tha meiwnei th thermokrasia
#define PosostoMeeiwshsTh_TA 0.85//syntelesths meiwshs 8ermokrasias ston TA
#define telh_min 0.08 // define to poso pou plhrwneis otan distance <30 km 
#define telh_max 0.12 // define to poso pou plhrwneis otan distance >30 km
#define costAnaKm 0.65 // define to poso poy plhrwneis ana km
#define ThSTART 100

using namespace std;

class initSolut{
private:    
    int station;
public:
    initSolut(){station=0;}
    initSolut(int in_station){station=in_station;}
	int get_station(){return station;}
};
int main() 
{	//srand(time(0));
    initSolut initSol[11];
	int TSP_array[10][10];// o pinakas dedomenwn
	int  k, j,in_station;

    fstream in_file;

	in_file.open("TSP_ARRAY.txt");
	if (!in_file.is_open()) { cout << "Could not open file!"; exit(1); }

	//OPEN FILE
	int i = 0; string ch; int ind;
	getline(in_file, ch);

	while (!in_file.eof()) {
		for (k = 0; k < 10; k++)
		{
			for (j = 0; j < 10; j++)
				in_file >> TSP_array[k][j]; //pernaw ta noumera tou arxeiou.txt ston 2D pinaka
		}
		i++;
	}
	ind = i - 1;
	in_file.close();//END OPEN FILE

	cout << "   ";
	for (k = 0; k < 10; k++)
		cout << "S" << k + 1 << "  ";
	cout << endl;
	for (k = 0; k < 10; k++)
	{
		cout << "S" << k + 1 << "  ";
		for (j = 0; j < 10; j++)
			cout << TSP_array[k][j] << "  ";// o pinakas ths ekfwnhshs
		cout << endl;
	}// print o pinakas ths ekfwnhshs

    vector <int> initialSolution;
    initialSolution.clear();
 	//fstream in_file;
    in_file.open("StochasticResults.txt");
    if (!in_file.is_open()) { cout << "Could not open file!"; exit(1); }

    //OPEN FILE
    int c=0; string chh; int indd;
    getline(in_file, chh);

    while (!in_file.eof()) {
     
            in_file >> in_station;
            initSol[c]=initSolut(in_station);
        c++;
    }
    indd=c-1;
    in_file.close();//END OPEN FILE
    for(j=0;j<11;j++) 
        initialSolution.push_back(initSol[j].get_station());//pernaw tis times mesw ths klashs gia to 1o solution

	 vector <double> random;
	 int countRandom=0; // o counter gia na allazw kathe fora ton random

	for (j = 0; j <300; j++){
        random.push_back((double)rand() / (RAND_MAX));
		//cout << random[j] << " ||";
	}//random generator array
	cout << endl;
	
	double sum_cost=0.0; //To sunoliko kostos
	vector <double> seg9; // arxika tha exw 9 pithanes lyseis gia swap
	vector <double> seg8; // 	afou vrw prwth lush pros swap meiwnei kata 1 ta segments etsi wste na mhn einai sto neo segment
	double segPortion9=9.0; // tha xwristei to pedio se 9 segments me 0.111 to kathe ena	
	double segPortion8=8.0;// tha xwristei to pedio se 9 segments me 0.125 to kathe ena	
	double Zbest;

	for(j=0;j<10;j++)// edw vriskw total cost apo opoiadipote diadromh thelw
		{ 
			if(TSP_array[initialSolution[j]-1][initialSolution[j+1]-1]>=30)
				{
					sum_cost += TSP_array[initialSolution[j]-1][initialSolution[j+1]-1] * costAnaKm + telh_max * TSP_array[initialSolution[j]-1][initialSolution[j+1]-1];			
		}
		else { sum_cost += TSP_array[initialSolution[j]-1][initialSolution[j+1]-1] * costAnaKm + telh_min * TSP_array[initialSolution[j]-1][initialSolution[j+1]-1]; }
		}
	double Zcurrent=sum_cost;// vazw Zcurrent to kostos ths initial solution

	cout<<endl<<"                 START OF SIMULATION ANNEALING ALGORITHM                  "<<endl<<endl;
	cout<<"INITIAL SOLUTION :";
    for(j=0;j<11;j++) 
       {
        cout<<"S"<<initialSolution[j]<<"-";}
    cout<<endl;
	cout<<"ZCurrent=Zbest="<<Zcurrent<<endl;
	cout<<"Meiwsi thermokrasias kathe 3 epanalispeis"<<endl;
		int countLusewn=0;

	for(j=1;j<10;j++)
		{
			seg9.push_back(j*1.0/segPortion9);// gemise tous pinakes me ta diasthmata gia segments 9
		//cout<<seg9[j-1]<<" ";
		}	
		cout<<endl;		
	for(j=1;j<9;j++)
		{
			seg8.push_back(j*1.0/segPortion8);// gemise tous pinakes me ta diasthmata gia segments 8

		}
		int segmentPosition9;
		int segmentPosition8;
		int iteration=0;
		vector <int> forChangeStations; // ta pithana station poy mporw na paw gia ton algorithmo ola ektos apo station 1
		vector <int> forChangeStations2; // ta pithana staion pou mporw na paw gia ton algoritho XWRIS OMWS TO STATION THS PRWTHS ALLAGHS
		vector <int> tempSolution; // h temp lush
		tempSolution.clear();
		forChangeStations.clear();
		forChangeStations2.clear();

		for(j=0;j<11;j++)
			tempSolution.push_back(initialSolution[j]);//vazw temp lush thn initial lush

		for(j=1;j<10;j++)
			{forChangeStations.push_back(tempSolution[j]);//edw gemizw to vector me tis luseis anamesa apo ta S1
			//cout<<forChangeStations[j-1]<<" *";
			}cout<<endl;

		int temp,temp2;
		int deikths1,deikths2; // Oi deiktes deixnoun se poious 2 stathmous tha ginei to swap
		Zbest=Zcurrent;
		Zcurrent=0.0;
		sum_cost=0.0;
		double Th=100.0;
		vector <string> Sbest;// enas pinakas string me ton kalytero syndiasmo diadromwn
		Sbest.clear();
	for(j=0;j<tempSolution.size();j++)
			{Sbest.push_back("S" + to_string(tempSolution[j]));// INSERT to Sbest th kaluterh lush
			//cout<<Sbest[j]<<"-";
			}
		cout<<endl;	
	//*************************************************************************************************************************************************************	
	while(iteration<10.0)
		{	
			//vres pia gia 1st swap
			cout<<"             ITERATION No: "<<iteration +1<<endl<<"Th="<<Th<<endl<<" FIRST RANDOM "<<random[countRandom];
		if (random[countRandom] < seg9.front())// an random < 1ou segment phgaine 1o dynato sta8mo
			{
				segmentPosition9= 0;

			}
		for (j = 0; j < 9; j++) {
			if (random[countRandom] > seg9[j] && random[countRandom] < seg9[j + 1])// vriskei  poios o prwtos sta8mos pros allagh
				{segmentPosition9 = j + 1;	}
			}
			/*if (random[countRandom] > seg9.back())// an random > tou final segment phgaine ston last dynato sta8mo!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
				{
				segmentPosition9 = 9; 
				}*/
		countRandom++;
			cout<<"   SECOND RANDOM "<<random[countRandom]<<endl;
			cout<<" CHANGE  S"<<forChangeStations[segmentPosition9];

		for(j=0;j<9;j++)
			{if(forChangeStations[j] != forChangeStations[segmentPosition9])// ftiaxno to deutero segment gia na vrw to deutero station pou ua allaksw
				{
					forChangeStations2.push_back(forChangeStations[j]);
				}
			}
		if (random[countRandom] < seg8.front())// an random < 1ou segment phgaine 1o dynato sta8mo gia deutrto random
			{
				segmentPosition8= 0;
			}
		for (j = 0; j < 8; j++) {
			if (random[countRandom] > seg8[j] && random[countRandom] < seg8[j + 1])// vriskei  poios o deuteros sta8mos pros allagh
					segmentPosition8 = j + 1;	
			}
		countRandom++;	
			cout<<" WITH  S"<<forChangeStations2[segmentPosition8]<<endl;

		for(j=0;j<11;j++)
			if(tempSolution[j]==forChangeStations[segmentPosition9])
				deikths1=j;// vriskei ton prwto stathmo pros allagh
		for(j=0;j<11;j++)
			if(tempSolution[j]==forChangeStations2[segmentPosition8])
				deikths2=j;	// vriskei ton deutero stathmo pros allagh	
				cout<<"**********SOLUTION*******"<<endl;
		cout<<"From:";
		for(j=0;j<11;j++)
			cout<<"S"<<tempSolution[j]<<"-";
			cout<<endl;
			temp=tempSolution[deikths1];
			tempSolution[deikths1]=tempSolution[deikths2];
			tempSolution[deikths2]=temp;//edw kanw to swap twn duo lusewn

		for(j=0;j<10;j++)
			{ 		
			if(TSP_array[tempSolution[j]-1][tempSolution[j+1]-1]>=30)
			{
			sum_cost += TSP_array[tempSolution[j]-1][tempSolution[j+1]-1] * costAnaKm + telh_max * TSP_array[tempSolution[j]-1][tempSolution[j+1]-1];
					
			}
			else {
			 sum_cost += TSP_array[tempSolution[j]-1][tempSolution[j+1]-1] * costAnaKm + telh_min * TSP_array[tempSolution[j]-1][tempSolution[j+1]-1]; }
		}

		Zcurrent=sum_cost;
	
		cout<<"To  :";
		for(j=0;j<11;j++)
			cout<<"S"<<tempSolution[j]<<"-";
		cout<<endl<<"with Zcurrent :"<< Zcurrent<<endl;

		if(Zcurrent-Zbest <= 0 ){
			Zbest=Zcurrent;
			Sbest.clear();
			cout<<"NEW BEST SOLUTION--->";
			for(j=0;j<tempSolution.size();j++)
				{Sbest.push_back("S"+to_string(tempSolution[j]));
			cout<<Sbest[j]<<"-";}
			cout<<endl<<" NEW Zbest="<<Zbest<<endl;
			for(j=1;j<10;j++)
				forChangeStations[j-1]=tempSolution[j];
			}
			else
			{
				cout<<"Dz ="<<Zcurrent-Zbest<<"$ more expensive"<<endl<<"next random value "<<random[countRandom]<<endl<<"Th="<<Th<<endl;
				if(random[countRandom]<exp((-(Zcurrent-Zbest)/Th)))// an pithanothta ths xeiroterhs > apo ton andom arithmo thn dexomai
					{
					cout<<"NEW WORSE SOLUTION WITH CHANCE="<<exp((-(Zcurrent-Zbest)/Th))<<endl;
					for(j=0;j<11;j++)
						cout<<"S"<<tempSolution[j]<<"-";
					cout<<endl<<"Zcurrent="<<Zcurrent<<endl;	
						countRandom++;
						for(j=1;j<10;j++)
							forChangeStations[j-1]=tempSolution[j];
					}
						else
						{
						cout<<"Solution declined because "<<"P="<<exp((-(Zcurrent-Zbest)/Th))<<"<"<<random[countRandom]<<" return to initial solution"<<endl;
						temp2=tempSolution[deikths1];
						tempSolution[deikths1]=tempSolution[deikths2];
						tempSolution[deikths2]=temp2;//edw kanw to swap twn duo lusewn kai gurnaw sthn arxikh lush prin thn allagh
						cout<<"Initial solution of iteration--->>>";
						for(j=0;j<11;j++)
							cout<<"S"<<tempSolution[j]<<"-";
								cout<<endl;
								for(j=1;j<10;j++)
									forChangeStations[j-1]=tempSolution[j];
						}	
			}
	//forChangeStations.clear();
	forChangeStations2.clear();
	
	sum_cost=0.0;
	Zcurrent=0.0;
	iteration++;
	if(iteration%3==0)//kathe 3 epanalipseis meiwse thermokrasia
		Th=Th*PosostoMeiwsisTh_SA;
	if(iteration==9)
	countRandom+=3;
	
	cout<<endl<<endl;
	}// end while
	cout<<"                   END OF SIMULATION ANNEALING"<<endl<<endl<<"BEST SOLUTION FOUND"<<endl;
	for(j=0;j<11;j++)
		cout<<Sbest[j]<<"-";
	cout<<endl<<"Zbest="<<Zbest<<endl;
	cout<<endl<<"                   START OF THRESHOLD ACCEPTING"<<endl;
	cout<<endl<<"INITIAL SOLUTION OF THRESHOLD ACCEPTING "<<endl;
	for(j=0;j<11;j++)
	//cout<<Sbest[j]<<"-";
	//cout<<endl<<"Zinitial="<<Zbest<<endl;

	double Th2Initial=Zbest*0.8;
	double Th2=Zbest*PosostoMeeiwshsTh_TA; // arxikh thermokrasia  threshold accepting
	iteration=0;
	tempSolution.clear();

	for(j=0;j<11;j++)
		{Sbest[j].erase(0,1);
		tempSolution.push_back(stoi(Sbest[j]));
	//cout<<tempSolution[j]<<"-";
	}
		for(j=1;j<10;j++)
		forChangeStations[j-1]=tempSolution[j];
	vector <string> Sbest2;
	cout<<endl;
	for(j=0;j<tempSolution.size();j++)
		{Sbest2.push_back("S" + to_string(tempSolution[j]));// INSERT to Sbest th kaluterh lush
		cout<<Sbest2[j]<<"-";}
		cout<<endl<<"Zinitial="<<Zbest<<endl;
		cout<<endl;
	
	cout<<endl;
	cout<<"Initial temperature->Th=Zbest*D= "<<Th2<<endl<<"reduction percentage D="<<PosostoMeeiwshsTh_TA<<endl;
	cout<<"Reduction each iteration"<<endl;
	cout<<endl;

	while(iteration<5)
		{
			//for(j=0;j<9;j++)
			//cout<<forChangeStations[j]<<"*****";
			cout<<endl;
			//vres pia gia 1st swap
			cout<<"             ITERATION No: "<<iteration +1<<endl<<"FIRST RANDOM "<<random[countRandom];
		if (random[countRandom] < seg9.front())// an random < 1ou segment phgaine 1o dynato sta8mo
			{
			segmentPosition9= 0;

			}
			for (j = 0; j < 9; j++) {
				if (random[countRandom] > seg9[j] && random[countRandom] < seg9[j + 1])// vriskei  poios o prwtos sta8mos pros allagh
					{segmentPosition9 = j + 1;	}
			}
		countRandom++;
			cout<<"   SECOND RANDOM "<<random[countRandom]<<endl;
			cout<<"CHANGE  S"<<forChangeStations[segmentPosition9];

		for(j=0;j<9;j++)
			{if(forChangeStations[j] != forChangeStations[segmentPosition9])// ftiaxno to deutero segment gia na vrw to deutero station pou ua allaksw
				{
					forChangeStations2.push_back(forChangeStations[j]);
				}
			}
		if (random[countRandom] < seg8.front())// an random < 1ou segment phgaine 1o dynato sta8mo gia deutrto random
			{
				segmentPosition8= 0;
			}
		for (j = 0; j < 8; j++) {
			if (random[countRandom] > seg8[j] && random[countRandom] < seg8[j + 1])// vriskei  poios o deuteros sta8mos pros allagh
				segmentPosition8 = j + 1;	
			}
		countRandom++;	
		
		cout<<" WITH  S"<<forChangeStations2[segmentPosition8]<<endl;
		
		cout<<"From:";
		for(j=0;j<11;j++)
			cout<<"S"<<tempSolution[j]<<"-";
		cout<<endl;
		for(j=0;j<11;j++)
			if(tempSolution[j]==forChangeStations[segmentPosition9])
				deikths1=j;
		for(j=0;j<11;j++)
			if(tempSolution[j]==forChangeStations2[segmentPosition8])
				deikths2=j;		
			
			temp=tempSolution[deikths1];
			tempSolution[deikths1]=tempSolution[deikths2];
			tempSolution[deikths2]=temp;//edw kanw to swap twn duo lusewn

	for(j=0;j<10;j++)
		{ 		
		if(TSP_array[tempSolution[j]-1][tempSolution[j+1]-1]>=30)
			{
			sum_cost += TSP_array[tempSolution[j]-1][tempSolution[j+1]-1] * costAnaKm + telh_max * TSP_array[tempSolution[j]-1][tempSolution[j+1]-1];			
		}
		else {
			 sum_cost += TSP_array[tempSolution[j]-1][tempSolution[j+1]-1] * costAnaKm + telh_min * TSP_array[tempSolution[j]-1][tempSolution[j+1]-1]; }
		}
	Zcurrent=sum_cost;
	
	cout<<"To  :";
		for(j=0;j<11;j++)
			cout<<"S"<<tempSolution[j]<<"-";
		cout<<endl<<"with Zcurrent :"<< Zcurrent<<endl;
		//if(iteration%2==0)
			Th2=Th2*PosostoMeeiwshsTh_TA;
		cout<<"Th_new="<<Th2<<endl;

			if(Zcurrent<Zbest)
				{	
				Zbest=Zcurrent;
				Sbest2.clear();
				cout<<"NEW BEST SOLUTION--->";
				for(j=0;j<tempSolution.size();j++)
					{Sbest2.push_back("S"+to_string(tempSolution[j]));
					cout<<Sbest2[j]<<"-";}
					cout<<endl<<" NEW Zbest="<<Zbest<<endl;
					cout<<"Th_new="<<Th2<<endl;
					for(j=1;j<10;j++)
						forChangeStations[j-1]=tempSolution[j];
				}
				else
					{
					if(Zcurrent-Zbest<Th2)
					{	cout<<"Accepted because Zcurrent-Zbest<Th, "<<Th2<<" Zcurrent-Zbest="<<Zcurrent-Zbest<<endl;
						cout<<"Zbest="<<Zbest<<endl;
						//if(iteration%2==0)
							Th2=Th2*PosostoMeeiwshsTh_TA;
						cout<<"Th_new="<<Th2<<endl;
						
						for(j=0;j<11;j++)
							cout<<"S"<<tempSolution[j]<<"-";
						cout<<endl<<"Zcurrent="<<Zcurrent<<endl;
						for(j=1;j<10;j++)
							forChangeStations[j-1]=tempSolution[j];
					}
					else
					{
						cout<<"Denied because  Zcurrent-Zbest>Th, "<<Th2<<" Zcurrent-Zbest="<<Zcurrent-Zbest<<endl;
						cout<<"Zbest="<<Zbest<<endl;
						cout<<"Th_new="<<Th2<<endl;
							Th2=Th2/PosostoMeeiwshsTh_TA;
							cout<<"Solution declined, return to initial solution"<<endl;
							temp2=tempSolution[deikths1];
							tempSolution[deikths1]=tempSolution[deikths2];
							tempSolution[deikths2]=temp2;//edw kanw to swap twn duo lusewn kai gurnaw sthn arxikh lush prin thn allagh
							cout<<"Initial solution of iteration--->>>";
								for(j=0;j<11;j++)
									cout<<"S"<<tempSolution[j]<<"-";
									cout<<endl;
									for(j=1;j<10;j++)
										forChangeStations[j-1]=tempSolution[j];
					}
						}
	//forChangeStations.clear();
	forChangeStations2.clear();
	sum_cost=0.0;
	Zcurrent=0.0;
	iteration++;}//end while threshold
	cout<<endl<<"************************END THESHOLD ACCEPT*******************"<<endl<<endl;
	cout<<"BEST SOLUTION-->";
	for(j=0;j<11;j++)
		cout<<Sbest2[j]<<"-";
		cout<<endl<<"WITH MINIMUM COST-->"<<Zbest<<endl;
    return 0;
}// end main