/*
 * Name: Benjamin Cooper - bjc12b
 * Date: 8/1/2016
 * Assignment: HW6 - Generics
 * Class: Java
 * About This File: This is an example test to test Strings to see if they're
 * lower case.
 * Purpose: To practice generics by creating an interface to allow testing of
 * various types of arrays.
 */

public class AllLower implements CustomTest<String> {
	public boolean test(String s){
		String s2 = s.toLowerCase();
		if(s2.equals(s))
			return true;
		else
			return false;
	}
}
