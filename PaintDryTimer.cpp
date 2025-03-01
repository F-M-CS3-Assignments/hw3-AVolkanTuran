


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


long long int get_time_remaining(DryingSnapShot dss){
	// Replace with your code
	return dss.timeToDry->GetTimeCodeAsSeconds() - (time(0) - dss.startTime);
}


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


	// get_sphere_sa
	double sa = get_sphere_sa(2.0);
	assert (50.2654 < sa && sa < 50.2655);
	// add more tests here


	// compute_time_code
	TimeCode *tc2 = compute_time_code(1.0);
	//cout << "tc: " << tc.GetTimeCodeAsSeconds() << endl;
	assert(tc2->GetTimeCodeAsSeconds() == 1);
	delete tc2;


	// add more tests here


	cout << "ALL TESTS PASSED!" << endl;

}


int main(){
	// replace with your code
	tests();
	string choice;
	string indent = "        ";
	double radius;
	vector<DryingSnapShot*> batches;

	do{
		cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: " << flush;
		cin >> choice;
		if(choice == "a" || choice == "A"){
			cout << indent << "radius: " << flush;
			cin >> radius;
			DryingSnapShot* dss = new DryingSnapShot;
			dss->name = "Batch-" + to_string(rand());
			dss->startTime = time(0);
			dss->timeToDry = compute_time_code(get_sphere_sa(radius));
			batches.push_back(dss);
			cout << indent << drying_snap_shot_to_string(*dss) << endl;
		}
		else if(choice == "v" || choice == "V"){
			int tracking = batches.size();
			for(int i = 0; i<batches.size(); i++){
				cout << indent << drying_snap_shot_to_string(*batches.at(i)) << endl;
				if(get_time_remaining(*batches.at(i))<=0){
					delete batches.at(i);
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