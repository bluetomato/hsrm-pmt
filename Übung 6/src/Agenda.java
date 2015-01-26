import java.io.File;
import java.sql.Timestamp;
import java.time.Duration;
import java.time.LocalDateTime;
import java.util.Iterator;
import java.util.LinkedList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.*;

/**
 * 
 * @author Alexander Koch & Stephanie Scholl
 *
 */
public class Agenda{
	private LinkedList<CalEntry> calendar;
	
	public Agenda(){
		calendar = new LinkedList<CalEntry>();
	}
	
	public boolean addEntry(LocalDateTime start, Duration duration, String description, String location){
		if(getEntry(description) == null){
			calendar.add(new CalEntry(start, duration, description, location));
			return true;
		}else{
			return false;
		}
	}
	
	
	public boolean addEntry(String start, long duration, String description, String location){
		if(getEntry(description) == null){
			calendar.add(new CalEntry(Timestamp.valueOf(start).toLocalDateTime(), Duration.ofMinutes(duration), description, location));
			return true;
		}else{
			return false;
		}
	}
	
	public boolean delEntry(CalEntry todel){
		return calendar.remove(todel);
	}
	
	public CalEntry getEntry(String description){
		Iterator<CalEntry> it = calendar.iterator();
		CalEntry temp;
		
		if(it.hasNext()){
			temp = it.next();
		}else{
			return null;
		}
		while(!temp.getDescription().equals(description)){
			if(it.hasNext()){
				temp = it.next();
			}
			else{
				return null;
			}
			
		}
		return temp;
	}
	
	public String toString(){
		String ret = "";
		for(CalEntry temp : calendar)
		{
			ret = ret + temp;
		}
		return ret;
	}
	
	public void writeToXML(String path) throws ParserConfigurationException, TransformerException{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder();
		Document doc = builder.newDocument();
		
		Element root = (Element) doc.createElement("agenda");
		doc.appendChild(root);
		
		for(CalEntry temp : calendar){
			// calEntry Tag
			Element cal = doc.createElement("calEntry");
			root.appendChild(cal);
			
			// Start Tag
			Element start = doc.createElement("start");
			start.appendChild(doc.createTextNode(Timestamp.valueOf(temp.getStart()).toString()));
			cal.appendChild(start);
			
			// Dauer Tag
			Element second = doc.createElement("dauer");
			second.appendChild(doc.createTextNode(String.valueOf(temp.getDuration().toMinutes())));
			cal.appendChild(second);
			
			// Beschreibung Tag
			Element description = doc.createElement("beschreibung");
			description.appendChild(doc.createTextNode(temp.getDescription()));
			cal.appendChild(description);
			
			// Ort Tag
			Element fourth = doc.createElement("ort");
			fourth.appendChild(doc.createTextNode(temp.getLocation()));
			cal.appendChild(fourth);
		}
		
		TransformerFactory tfactory = TransformerFactory.newInstance();
		Transformer trans = tfactory.newTransformer();
		DOMSource source = new DOMSource(doc);
		StreamResult result = new StreamResult(new File(path));
		trans.transform(source, result);
	}
	
	public void readFromXML(String path) throws Exception
	{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder parser = factory.newDocumentBuilder();
		Document doc = parser.parse(new java.io.File(path));
		Element root = doc.getDocumentElement();
		NodeList calendarEntries = root.getChildNodes();
		
		for(int i = 0; i < calendarEntries.getLength(); i++){
			String start = null, duration = null, location = null, description = null;
			NodeList entry = calendarEntries.item(i).getChildNodes();
			if(entry.item(0).getFirstChild().getNodeType() == Node.TEXT_NODE && entry.item(0).getNodeName().equals("start")){
				start = entry.item(0).getFirstChild().getNodeValue();
			}
			if(entry.item(1).getFirstChild().getNodeType() == Node.TEXT_NODE && entry.item(1).getNodeName().equals("dauer")){
				duration = entry.item(1).getFirstChild().getNodeValue();
			}
			if(entry.item(2).getFirstChild().getNodeType() == Node.TEXT_NODE && entry.item(2).getNodeName().equals("beschreibung")){
				description = entry.item(2).getFirstChild().getNodeValue();
			}
			if(entry.item(3).getFirstChild().getNodeType() == Node.TEXT_NODE && entry.item(3).getNodeName().equals("ort")){
				location = entry.item(3).getFirstChild().getNodeValue();
			}
			

			
			this.addEntry(start, Long.valueOf(duration), description, location);
		}
	}
}
