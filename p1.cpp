#include <iostream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <vector>
#include <deque>
#include <cmath>
// this program only converts virtual address to physical addresses
using namespace std;
template <class T>
void printBitVector(T bit_virtual_address)
{
	for(int i = 0; i < bit_virtual_address.size(); i++)
	{
		if(i % 4 == 0)
		{
			printf("   ");
		}
		printf("%i ", bit_virtual_address[i]);

	}
}
deque<int> valueToBitVector(int the_virtual_address,
							 deque<int> bit_virtual_address)
{
	printf("the virtual address is %x\n", the_virtual_address);
	//int tracker = 1;
	while(the_virtual_address > 0)
	{

		//if(tracker & the_virtual_address)
		//{
			//printf("%i ", 1);
		bit_virtual_address.push_back(the_virtual_address % 2);
		the_virtual_address /= 2;
		//}
		//else
		//{
		//	printf("%i ", 0);
		//	bit_virtual_address.push_back(0);

		//}

		//tracker = tracker << 1;
	}
	// padding added to begining
	int j = bit_virtual_address.size();
	while(j % 4 != 0 )
	{
		//printf("%i ", 0);
		bit_virtual_address.push_back(0);
		j++;
	}
	//cout << endl;

	reverse(bit_virtual_address.begin(), bit_virtual_address.end());
	printBitVector(bit_virtual_address);
	cout << endl;
	return bit_virtual_address;
}
deque<int> getVirtualAddress(deque<int> bit_vector, int virtual_address_size)
{
	deque<int> virtual_address;
	for(int i = 0; i < virtual_address_size; i++)
	{
		virtual_address.push_front(bit_vector[virtual_address_size-i]);
	}
	return virtual_address;
}
int bitVectorToValue(vector<int> bit_virtual_address)
{
	//cout << "in bit to vector\n";
	reverse(bit_virtual_address.begin(), bit_virtual_address.end());
	int value = 0;
	for(int i = 0; i < bit_virtual_address.size(); i++)
	{
		//cout << value <<  bit_virtual_address[i] << endl;
		value +=  bit_virtual_address[i] * (int) pow(2.0, i);
	}
	return value;
}

int countDigits(int number)
{
	int count = 0;
	while(number > 0)
	{
		number /= 10;
		count++;
		//printf("%i ", number);
	}
	//printf("%i\n", count);
	return count;
}
int main(int argc, char** argv) {


	ifstream inFile;
	int num = 0;
	int virtual_address;
	int physical_address;
	int bytes_in_physical_page;

	inFile.open("test.txt");
	if (!inFile) {
		cout << "Unable to open file";
		exit(1); // terminate with error
	}

	if (inFile >> num){
		virtual_address = num;
		if (inFile >> num){
			physical_address = num;
			if(inFile >> num){
				bytes_in_physical_page = num;
			}
		}

	}

	vector<int> row;
	while(inFile >> num){
		row.push_back(num);
	}

	vector<int> valid;
	vector<int> permission;
	vector<int> pgNum;
	vector<int> useBit;
	for(int i = 0; i < row.size(); i++){
		//printf("%i ", row[i]);
		if( i % 4 == 0){
			valid.push_back(row[i]);
		}
		if(i % 4 == 1){
			permission.push_back(row[i]);
		}
		if(i % 4 == 2){
			pgNum.push_back(row[i]);
		}
		if (i % 4 == 3){
			useBit.push_back(row[i]);
		}
	}

	// todo: put in sanity checks

	int the_virtual_address = 0x28;
	// from value to bit vector
	deque<int> bit_virtual_address;
	bit_virtual_address = getVirtualAddress(valueToBitVector(the_virtual_address, bit_virtual_address), virtual_address);

	printBitVector(bit_virtual_address);


	while(bit_virtual_address.size() > virtual_address)
	{
		bit_virtual_address.pop_front();
	}
	printf("\n");
	//printBitVector(bit_virtual_address);
	//exit(1);
	//printf("\nanswer %x\n", value);
	printf("\n");
	//char buffer[50];
	//sprintf(buffer, "%x", the_virtual_address);
	//printf("%s\n", buffer);
	/*
	log2() Parameters
	The log2() function takes a single mandatory argument in the range [0, ∞].
	If the value is less than zero, log2() returns NaN (Not a Number).
	*/


	int offset_number_of_bits_representing_physical_page_size = (int) log2(bytes_in_physical_page);
	printf("offset to physical page size %i\n", offset_number_of_bits_representing_physical_page_size);

	int segment_size = virtual_address - offset_number_of_bits_representing_physical_page_size;
	printf("segment index size %i\n", segment_size);


	vector<int> segment;
	for(int i = 0; i < segment_size; i++)
	{
		segment.push_back(bit_virtual_address[i]);
	}
	for(int i = 0; i < segment.size(); i++)
	{
		cout << segment[i];

	}

	cout << endl;
	int index = bitVectorToValue(segment);
	cout << "the index to the table is " << index << endl;


	vector<int> physical_page_offset;
	for(int i = segment_size; i < segment_size + offset_number_of_bits_representing_physical_page_size; i++)
	{
		physical_page_offset.push_back(bit_virtual_address[i]);
	}

	printf("the physical page offset is ");
	printBitVector(physical_page_offset);
	printf("\n");
	if(index >= pgNum.size())
	{
		cout << "page " << index << " does not exist\n";
		cout << pgNum.size() << endl;
	}
	else
	{
		cout << "accessing page table\n";
		//cout << pgNum[index] << endl;
		deque<int> physical_page_number;

		physical_page_number = valueToBitVector(pgNum[index], physical_page_number);
		printBitVector(physical_page_number);
		printBitVector(physical_page_offset);


		vector<int> physical_address_;

		for(int i = 0; i < physical_page_number.size(); i++)
		{
			physical_address_.push_back(physical_page_number[i]);
		}
		for(int i = 0; i < physical_page_offset.size(); i++)
		{
			physical_address_.push_back(physical_page_offset[i]);
		}
		printf("\nphysical address to mem\n");
		printBitVector(physical_address_);

		int physical_address_to_mem = bitVectorToValue(physical_address_);
		printf("\nfinal address is %x", physical_address_to_mem);

	}
	cout << endl;
	inFile.close();


    return 0;
}
