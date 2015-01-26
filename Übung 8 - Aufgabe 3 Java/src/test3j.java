import java.util.Set;

/**
 * Test Class for Reimwörterbuch.java
 * 
 * @file test3j.java
 * @author Stephanie Scholl
 * @note Matrikelnummer: 979993
 * @note Hochschule RheinMain
 *
 * @note Fach: Programmiermethoden- und Techniken
 * @note 2. Semester
 * @note Projektarbeit
 *
 * @note Professor: Sven Eric Panitz
 * @note Praktikumsleiter: Christian Lassmann
 */
public class test3j {

	/**
	 * Method for printing a Set
	 * 
	 * @param set
	 *            Set - wich needs to be printed
	 */
	public static void printSet(Set<String> set) {
		for (String s : set) {
			System.out.println(s);
		}
	}

	/**
	 * main
	 * 
	 * @param args
	 */
	public static void main(String[] args) {
		Reimwörterbuch rhyme = new Reimwörterbuch("Reimwörterbuch.xml");
		rhyme.parseXML();
		/*search for haus*/
		Set<String> stringSet = rhyme.findRhyme("haus");
		printSet(stringSet);
	}

}