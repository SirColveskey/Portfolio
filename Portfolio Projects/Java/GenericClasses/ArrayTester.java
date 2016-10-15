/*
 * Name: Benjamin Cooper - bjc12b
 * Date: 8/1/2016
 * Assignment: HW6 - Generics
 * Class: Java
 * About This File: This is the container class for the items to be tested and the
 * CustomTest to run on them.
 * Purpose: To practice generics by creating an interface to allow testing of
 * various types of arrays.
 */

public class ArrayTester<T extends Comparable<T>>{
	public T[] value;
	public CustomTest<T> tester;
	
	public ArrayTester(T t[],CustomTest<T> c){
		value = t; //loads the arguments
		tester = c;
		int exchanges = 0;
		do{ //executes a bubble sort on the array
			exchanges = 0;
			for(int i=0; i<value.length-1; i++)
			{
				if(value[i].compareTo(value[i+1])>0)
				{
					T temp = value[i];
					value[i] = value[i+1];
					value[i+1] = temp;
					exchanges += 1;
				}
			}
		}
		while(exchanges != 0);
	}
	public void printIfValid(){ //prints out the members of the array that pass
		for(int i=0; i<value.length; i++)
		{
			if(tester.test(value[i])){
				System.out.print(value[i] + " ");
			}
		}
		System.out.print("\n");
	}
	public int countIfValid(){ //Gets a count of the members that pass
		int count = 0;
		for(int i=0;i<value.length;i++)
		{
			if(tester.test(value[i])){
				count += 1;
			}
		}
		return count;
	}
}
