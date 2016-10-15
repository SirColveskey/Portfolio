/*
 * Name: Benjamin Cooper - bjc12b
 * Date: 8/1/2016
 * Assignment: HW6 - Generics
 * Class: Java
 * About This File: This is an example test which tests Numbers to see if they're
 * even.
 * Purpose: To practice generics by creating an interface to allow testing of
 * various types of arrays.
 */

public class IsEven<T extends Number> implements CustomTest<T>{
	public boolean test(T arg){
		int x = arg.intValue();
		if(x % 2 == 0)
			return true;
		else
			return false;
	}

}
