
#include <iostream>
#include <assert.h>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!

	t = TimeCode::ComponentsToSeconds(0,0,0);
	assert(t==0);

	t = TimeCode::ComponentsToSeconds(900000,0,0);
	assert(t==3240000000);
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");

	tc = TimeCode(3,3,3);
	assert(tc.ToString()=="3:3:3");

	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	
	// Roll-over inputs
	TimeCode tc3 = TimeCode(3, 71, 3801);
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	
	tc = TimeCode(9000,60,60);
	assert(tc.ToString()=="9001:1:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!

	TimeCode tc1 = TimeCode(0, 0, 0);
	tc1.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);

	TimeCode tc2 = TimeCode(59, 59, 59);
	tc2.GetComponents(h, m, s);
	assert(h == 59 && m == 59 && s == 59);
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests

	TimeCode tc6 = tc4-tc1;
	assert(tc6.ToString()=="0:15:45");
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}


// Many More Tests...

void TestGetHours(){
	cout << "Testing GetHours" << endl;

	TimeCode tc = TimeCode(8,5,9);
	assert(tc.GetHours()==8);

	TimeCode tc2 = TimeCode(1,60,0);
	assert(tc2.GetHours()==2);

	cout << "PASSED!" << endl << endl;
}

void TestGetMinutes(){
	cout << "Testing GetMinutes" << endl;

	TimeCode tc = TimeCode(8,5,9);
	assert(tc.GetMinutes()==5);

	TimeCode tc2 = TimeCode(1,0,60);
	assert(tc2.GetMinutes()==1);

	cout << "PASSED!" << endl << endl;
}

void TestGetSeconds(){
	cout << "Testing GetSeconds" << endl;

	TimeCode tc = TimeCode(8,5,9);
	assert(tc.GetSeconds()==9);

	TimeCode tc2 = TimeCode(900,5,72);
	assert(tc2.GetSeconds()==12);

	cout << "PASSED!" << endl << endl;	
}

void TestAdd(){
	cout << "Testing Add" << endl;

	TimeCode tc1 = TimeCode(2,2,2);
	TimeCode tc2 = TimeCode(3,3,3);

	TimeCode tc3 = tc1+tc2;
	assert(tc3.ToString()=="5:5:5");

	TimeCode tc4 = TimeCode(1,59,59);
	TimeCode tc5 = TimeCode(0,0,1);
	TimeCode tc6 = tc4+tc5;
	assert(tc6.ToString()=="2:0:0");

	cout << "PASSED!" << endl << endl;
}

void TestDivide(){
	cout << "Testing Divide" << endl;

	TimeCode tc1 = TimeCode(2,0,0);
	TimeCode tc2 = tc1/2;
	assert(tc2.ToString()=="1:0:0");

	TimeCode tc3 = tc1/3;
	assert(tc3.ToString()=="0:40:0");

	TimeCode tc4 = tc3/5;
	assert(tc4.ToString()=="0:8:0");

	cout << "PASSED!" << endl << endl;
}

void TestMultiply(){
	cout << "Testing Multiply" << endl;

	TimeCode tc1 = TimeCode(0,1,0);
	TimeCode tc2 = tc1*2;
	assert(tc2.ToString()=="0:2:0");

	TimeCode tc3 = TimeCode(3,5,17);
	TimeCode tc4 = tc3*5.5;
	assert(tc4.ToString()=="16:59:3");

	TimeCode tc5 = TimeCode(0,5,0);
	TimeCode tc6 = tc5*2.5;
	assert(tc6.ToString()=="0:12:30");

	TimeCode tc7 = TimeCode(0,5,0);
	TimeCode tc8 = tc7*0.5;
	assert(tc8.ToString()=="0:2:30");
	
	TimeCode tc9 = tc7*0;
	assert(tc9.ToString()=="0:0:0");

	cout << "PASSED!" << endl << endl;
}

void TestEquals(){
	cout << "Testing Equals" << endl;

	TimeCode tc1 = TimeCode(1,50,9);
	TimeCode tc2 = TimeCode(tc1);
	assert(tc1==tc2);

	TimeCode tc3 = TimeCode(1,51,9);
	assert(!(tc1==tc3));

	cout << "PASSED!" << endl << endl;
}

void TestNotEquals(){
	cout << "Testing Not Equals" << endl;

	TimeCode tc1 = TimeCode(2,5,9);
	TimeCode tc2 = TimeCode(2,59,30);

	assert(tc1!=tc2);

	TimeCode tc3 = TimeCode(tc1);
	assert(!(tc1!=tc3));

	cout << "PASSED!" << endl << endl;
}

void TestLess(){
	cout << "Testing Less Than" << endl;

	TimeCode tc1 = TimeCode(1,59,59);
	TimeCode tc2 = TimeCode(2,0,0);
	assert(tc1<tc2);

	TimeCode tc3 = TimeCode(1,59,500);
	assert(tc1<tc3);

	cout << "PASSED!" << endl << endl;
}

void TestLessEqual(){
	cout << "Testing Less Than or Equal" << endl;

	TimeCode tc1 = TimeCode(0,30,68);
	TimeCode tc2 = TimeCode(4,15,10);
	assert(tc1<tc2);

	TimeCode tc3 = TimeCode(tc1);
	assert(tc1<=tc3);

	cout << "PASSED!" << endl << endl;
}

void TestGreater(){
	cout << "Testing Greater Than" << endl;
	
	TimeCode tc1 = TimeCode(9000,0,0);
	TimeCode tc2 = TimeCode(0,0,0);

	assert(tc1>tc2);

	TimeCode tc3 = TimeCode(8999,600,0);
	assert(tc3>tc1);

	cout << "PASSED!" << endl << endl;
}

void TestGreaterEqual(){
	cout << "Testing Greater Than or Equal" << endl;

	TimeCode tc1 = TimeCode(800,80,30);
	TimeCode tc2 = TimeCode(750,6800,30);
	assert(tc2>=tc1);

	TimeCode tc3 = TimeCode(tc1);
	assert(tc1>=tc3);

	cout << "PASSED!" << endl << endl;
}
	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	TestSubtract();
	TestSetMinutes();
	
	// Many othere test functions...
	TestGetHours();
	TestGetMinutes();
	TestGetSeconds();
	TestMultiply();
	TestAdd();
	TestDivide();
	TestMultiply();
	TestEquals();
	TestNotEquals();
	TestLess();
	TestLessEqual();
	TestGreater();
	TestGreaterEqual();
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
