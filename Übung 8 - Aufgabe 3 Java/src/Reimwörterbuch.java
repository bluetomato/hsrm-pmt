import java.io.IOException;
import java.util.ArrayList;
import java.util.Set;
import java.util.TreeSet;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 * Class which parses an XML file and gives you a list of rhymes
 * 
 * @file Reimwörterbuch.java
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

public class Reimwörterbuch {
	String filename;
	Document document;
	ArrayList<ArrayList<String>> rhymeList;

	/**
	 * Constructor of Reimwörterbuch Builts new DOM Object as "document"
	 * 
	 * @param filename
	 *            String - the file which is going to be parsed
	 */
	Reimwörterbuch(String filename) {
		this.filename = filename;
		rhymeList = new ArrayList<ArrayList<String>>();

		/* dom */
		try {
			document = DocumentBuilderFactory.newInstance()
					.newDocumentBuilder().parse(this.filename);
		} catch (SAXException | IOException | ParserConfigurationException e) {
			e.printStackTrace();
		}
	}

	/**
	 * Method for parsing an XML to an ArrayList
	 */
	public void parseXML() {
		ArrayList<String> rhymes;
		/* only if there's a document */
		if (document != null) {
			/* get the root element */
			Element root = (Element) document.getDocumentElement();
			/* list of all children */
			NodeList children = root.getChildNodes();

			/* for every child */
			for (int i = 0; i < children.getLength(); i++) {
				/* test if child is an element node and equals "Reim" */
				if (children.item(i).getNodeType() == Node.ELEMENT_NODE
						&& children.item(i).getNodeName().equals("Reim")) {
					
					/* new list for rhyme children (all words when they rhyme) */
					NodeList rhymeChildren = children.item(i).getChildNodes();
					rhymes = new ArrayList<>();
					
					/* for every rhyme child */
					for (int j = 0; j < rhymeChildren.getLength(); j++) {
						
						/* if child is a elementnode and equals "wort" */
						if (rhymeChildren.item(j).getNodeType() == Node.ELEMENT_NODE
								&& rhymeChildren.item(j).getNodeName()
										.equals("Wort")) {
							
							/* if rhyme child is a textnode */
							if (rhymeChildren.item(j).getFirstChild()
									.getNodeType() == Node.TEXT_NODE) {
								
								/* add String to list of rhymes */
								rhymes.add(rhymeChildren.item(j)
										.getFirstChild().getNodeValue());
							} else {
								System.out.println("Fehler");
							}

						}
					}
					/* add list of rhymes */
					rhymeList.add(rhymes);
				}
			}
		}
	}

	/**
	 * To String Method
	 */
	public String toString() {
		String result = new String();

		for (ArrayList<String> rhymes : rhymeList) {
			result += "######";
			for (String s : rhymes) {
				result += s + "\n";
			}
		}
		return result;
	}

	/**
	 * Reverses an incoming String
	 * 
	 * @param old
	 *            String - String which is going to be reversed
	 * 
	 * @return reversed String
	 */
	public String reverse(String old) {
		int size = old.length();
		StringBuffer result = new StringBuffer(size);

		/* for length of string */
		for (int i = size - 1; i >= 0; i--) {
			result.append(old.charAt(i));
		}
		return result.toString();
	}

	/**
	 * Testes if word2 rhymes to word1
	 * 
	 * @param word1
	 *            String - first word
	 * @param word2
	 *            String - second word
	 * 
	 * @return TRUE if they rhyme, FALSE if they don't
	 */
	public boolean isRhyme(String word1, String word2) {
		int smallest;

		word1 = reverse(word1);
		word2 = reverse(word2);

		/* find smallest word and safe length as int */
		smallest = word1.length() > word2.length() ? word2.length() : word1.length();

		/* walk till end of smallest word */
		for (int i = 0; i < smallest; i++) {
			/* if a characters equals a, i, u, o, ä, ü, ö : it rhymes! */
			if (word1.charAt(i) == word2.charAt(i)) {
				if (word1.charAt(i) == 'a' 
						|| word1.charAt(i) == 'i'
						|| word1.charAt(i) == 'o' 
						|| word1.charAt(i) == 'u'
						|| word1.charAt(i) == -92 /* ä */
						|| word1.charAt(i) == -68 /* ü */
						|| word1.charAt(i) == -74 /* ö */) {
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * Method for finding rhymes for a word
	 * 
	 * @param word
	 *            String - word we want rhymes for
	 * 
	 * @return Set of rhymes if there are any, else an empty Set
	 */
	Set<String> findRhyme(String word) {
		Set<String> result = new TreeSet<String>();

		/* walk through rhymelist */
		for (ArrayList<String> rhymes : rhymeList) {
			/* if word from rhymelist is rhyme of word: add to result set */
			if (isRhyme(rhymes.get(0), word)) {
				for (String rhyme : rhymes) {
					if (!rhyme.equals(word)) {
						result.add(rhyme);
					}
					return result;
				}
			}
		}
		return result;
	}
}
