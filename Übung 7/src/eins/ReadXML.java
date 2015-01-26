package eins;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.xpath.XPath;
import javax.xml.xpath.XPathConstants;
import javax.xml.xpath.XPathExpression;
import javax.xml.xpath.XPathExpressionException;
import javax.xml.xpath.XPathFactory;

import org.w3c.dom.Document;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

public class ReadXML {
	
	public static void main(String[] args) throws ParserConfigurationException, SAXException, IOException, XPathExpressionException {
		DocumentBuilderFactory domFactory = DocumentBuilderFactory.newInstance();
		domFactory.setNamespaceAware(true); 
		DocumentBuilder builder = domFactory.newDocumentBuilder();
		Document doc = builder.parse("skript_test.xml");
		XPath xpath = XPathFactory.newInstance().newXPath();

		XPathExpression expr = xpath.compile("//anhang//code//text()");

		Object result = expr.evaluate(doc, XPathConstants.NODESET);
		NodeList nodes = (NodeList) result;
		for (int i = 0; i < nodes.getLength(); i++) {
			System.out.println(nodes.item(i).getNodeValue()); 
		}
		
		// viel zu viel für die Konsole, daher schreiben in eine Datei
		FileWriter writer;
		File file = new File("codeschnipsel.txt");
	    try {
	    	// Datei wird überschrieben, falls sie existiert
	    	writer = new FileWriter(file);
	       
	    	for(int i = 0; i < nodes.getLength(); i++){
	    		int j = i+1;
	    		writer.write("-----------------Codeschnipsel Nummer " + j + ":------------------------------------------------");
	    		writer.write(System.getProperty("line.separator")); // Zeilenumbruch
	    		writer.write(nodes.item(i).getNodeValue());
	    		writer.write(System.getProperty("line.separator"));
	    		writer.write(System.getProperty("line.separator"));
	    	}	       
	       
	    	writer.flush();
	       
	    	// Schließt den Stream
	    	writer.close();
	    } catch (IOException e) {
	    	e.printStackTrace();
	    }
	}
}