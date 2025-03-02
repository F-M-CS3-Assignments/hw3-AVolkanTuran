


#include <ctime> // for time(0)
#include <iostream> // for cin and cout
#include <cmath> // for M_PI and others
#include <vector> // for vectors (duh)
#include <cstdlib> // for random
#include <cassert> // for assert in the tests() function
#include "TimeCode.h" // for timecode's (duh)

using namespace std;




struct DryingSnapShot {
	// This is a struct, it's like an object
	// that doesn't have any methods.
	// You can read more about them in the ZyBook
	// just search for "struct"
	string name;
	time_t startTime;
	TimeCode *timeToDry;
};

//Finds the difference between the total time to try and the time that has passed ever since the dss has been added.
long long int get_time_remaining(DryingSnapShot dss){
	// Replace with your code
	return dss.timeToDry->GetTimeCodeAsSeconds() - (time(0) - dss.startTime);
}

//String representation of dss
string drying_snap_shot_to_string(DryingSnapShot dss){
	// Replace with your code
	string output;
	if(get_time_remaining(dss)<=0){
		output = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) DONE!";
	}
	else{
		output = dss.name + " (takes " + dss.timeToDry->ToString() + " to dry) time remaining: " + TimeCode(0,0,get_time_remaining(dss)).ToString();
	}
	return output;
}


double get_sphere_sa(double rad){
	// replace with your code
	return 4*M_PI*rad*rad;
}

//Creates a TimeCode pointer with surfaceArea as the seconds
TimeCode *compute_time_code(double surfaceArea){
	// replace with your code
	TimeCode *tc = new TimeCode(0,0, surfaceArea);
	return tc;
}


void tests(){
	// get_time_remaining
	DryingSnapShot dss;
	dss.startTime = time(0);
	TimeCode tc = TimeCode(0, 0, 7);
	dss.timeToDry = &tc;
	long long int ans = get_time_remaining(dss);
	assert(ans > 6 && ans < 8);
	// add more tests here

	dss.startTime = time(0);
	tc = TimeCode(0,0,10000);
	dss.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans>9999 && ans < 10001);

	dss.startTime = time(0);
	tc = TimeCode(1,0,0);
	dss.timeToDry = &tc;
	ans = get_time_remaining(dss);
	assert(ans>3599 && ans < 3601);


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here

	sa = get_sphere_sa(39.1);
	assert(19211.5930 < sa && sa < 19211.5931);

	sa = get_sphere_sa(57.49);
	assert(41533.1127 < sa && sa < 41533.1128);

	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here
	TimeCode *tc3 = compute_time_code(98000);
	assert(tc3->GetTimeCodeAsSeconds() == 98000);
	delete tc3;

	TimeCode *tc4 = compute_time_code(342.5);
	assert(tc4->GetTimeCodeAsSeconds() == 342);

	delete tc4;

	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	tests();
	string choice;
	string indent = "        ";
	double radius;
	vector<DryingSnapShot> batches;

	do{
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: " << flush;
		cin >> choice;
		if(choice == "a" || choice == "A"){
			cout << indent << "radius: " << flush;
			cin >> radius;
			DryingSnapShot dss;
			dss.name = "Batch-" + to_string(rand());
			dss.startTime = time(0);
			dss.timeToDry = compute_time_code(get_sphere_sa(radius));
			batches.push_back(dss);
			cout << indent << drying_snap_shot_to_string(dss) << endl;
			delete dss.timeToDry;
		}
		else if(choice == "v" || choice == "V"){
			int tracking = batches.size();
			for(unsigned int i = 0; i<batches.size(); i++){
				cout << indent << drying_snap_shot_to_string(batches.at(i)) << endl;
				if(get_time_remaining(batches.at(i))<=0){
					batches.erase(batches.begin() + i);
					i--;
				}
			}
			cout << indent << tracking << " batches being tracked." << endl;
		}
	}
	while(choice != "q" && choice != "Q");

	return 0;
}