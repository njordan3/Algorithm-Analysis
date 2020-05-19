/* Modified by Nicholas Jordan */

#include<iostream>
#include<vector>
#include<cmath>
#include<ctime>
#include<cstring>
using namespace std;


int deleteAndEarn(int nums[], int length);


int main()
{
	//DO NOT MODIFY MAIN
	//DO NOT MODIFY MAIN
	//DO NOT MODIFY MAIN

	int choice;
	int size;

	cout << "Welcome to the Delete and Earn Program\nPlease make a selection: \n\n";
	cout << "1. Generate Random Array\n2. Input my own array\nChoice: " << endl;	
	cin >> choice;

	switch(choice){
		case 1:
			{
				srand(time(0));
				size = rand() % 50 + 1;
				int nums[size];
				for(int i=0; i<size; i++) {
					nums[i] = rand() % 1000 + 1;
					cout << nums[i] << ", ";
				}
				cout << "\n\nMax Score: " << deleteAndEarn(nums, size) << endl;
			}
			break;

		case 2:
			{
				cout << "Enter the size of the array: ";
				cin >> size;
				while(!cin || size <= 0 || size > 50) {
					cout << "\nInvalid input. Please give an integer" <<
						" between 0-50: ";
					cin.clear();
					cin.ignore();
					cin >> size;
				}

				int nums[size];
				for (int i=0; i<size; i++) {
					cout << "Enter element " << i+1 << ": ";
					cin >> nums[i];
					while(!cin) {
						cout << "Invalid input. Please give an integer: ";
						cin.clear();
						cin.ignore();
						cin >> nums[i];
					}
				}
				cout << "Max Score: " << deleteAndEarn(nums, size) << endl;
			}
			break;

		default:
			cout << "Unsupported input detected. Exiting... " << endl;
			break;
	}

	return (0);
}

int deleteAndEarn(int nums[], int length)
{
	int maxVal = 0;
	for (int i = 0; i < length; i++)
		maxVal = max(maxVal, nums[i]);
// bins is used to keep track of the largest element and
// contain the number of occurances that are in the array
	int bins[maxVal+1];	
	memset(bins, 0 , sizeof(bins));
	for (int i = 0; i < length; i++)
		bins[nums[i]]++;
	int sum[maxVal+1];
	sum[0] = 0;
	for (int i = 1; i <= maxVal; i++) {
// get the sum of the current values first and second
// neighbor and take the largest of the comparison:
		if (max(i-2, 0) > 0)
			sum[i] = max(sum[i-1], i*bins[i]+sum[i-2]);
		else
			sum[i] = max(sum[i-1], i*bins[i]+sum[0]);
	}
	return sum[maxVal];
}

