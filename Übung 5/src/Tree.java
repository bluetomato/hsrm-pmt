import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.StringWriter;
import java.io.Writer;
import java.util.*;
import java.util.function.*;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.DOMImplementation;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

class Tree<E>{
	E elem;
	boolean isNil;
    List<Tree<E>> children = new ArrayList<>();
    E parent = null;

    Tree(){
    	isNil = true;
    }
    
    @SafeVarargs
	Tree(E e,Tree<E>... ts){
    	isNil = false;
    	elem = e;
		for (Tree<E> t:ts) children.add(t);
    }

    int size2(){
    	if (isNil) return 0;

    	int result = 1;
    	for (Tree<E> child:children){
    		result = result +child.size2();
    	}
	
    	return result;
    }

    /* Kurz und knackig mit Lambda */
    int size(){
    	if (isNil) return 0;

    	return children.stream().map( x -> x.size() ).reduce(1, (result,childSize) -> result +childSize );
    }

    void fuerAlle(Consumer<E> c) {
    	if (!isNil){
    		for (Tree<E> child:children){
    			child.fuerAlle(c);
    		}
    		c.accept(elem);
    	}
    }
    
    /* Schreiben Sie für die Klasse Tree eine Methode List<E> fringe(),
	die die Liste der Blätter des Baumes zurück gibt. Ein Blatt ist dabei ein
	Baumknoten, der keine Kinder mehr hat. */
    
	List<E> fringe(){
    	List<E> lis = new ArrayList<>();
    	
    	if (children.isEmpty()){
    		lis.add(this.elem);
    	}
    	for (Tree<E> child : this.children){
        	lis.addAll(child.fringe());
        }
        return lis;
    }
	
	/* Schreiben Sie für die Klasse Tree eine Methode
	boolean contains(java.util.function.Predicate<E> pred),
	die genau dann wahr als Ergebnis hat, wenn für eines der Elemente im Baum
	das übergebene Prädikat wahr ist. */
	
	boolean contains(java.util.function.Predicate<E> pred){
		boolean result = pred.test(elem);
		for(Tree<E> child : children){
			result = result || child.contains(pred);
		}
		return result;
	}
	
	/* Schreiben Sie für die Klasse Tree eine Methode boolean contains(E el),
	die genau dann wahr als Ergebnis hat, wenn eines der Elemente im Baum
	gleich dem übergebenen Element ist. */
	
	public boolean contains(E a){
		boolean result = a.equals(elem);
		for(Tree<E> child : children){
			result = result || child.contains(a);
		}
		return result;
	}
	
	/* Schreiben Sie für die Klasse Tree eine Methode List<E> pathTo(E elem),
	die die Elemente auf dem Pfad von der Wurzel zu dem Knoten mit der Element-Markierung
	elem zurück gibt. Sollte kein Knoten mit dem Element elem markiert sein, 
	so ist die leer Liste das Ergebnis.*/
	
	List<E> pathTo(E elem){
		List<E> result = new ArrayList<>();
		if (contains(elem)){ 
			result.add(this.elem);
		}
		for (Tree<E> child:this.children){
			result.addAll(child.pathTo(elem));
		}
		return result;		
	}
	
	/* Schreiben Sie für die Klasse Tree eine Methode <R> Tree<R> mapTree(java.util.function.Function<E, R> f),
	die einen neuen Baum erzeugt, dessen Elemente aus den Elementen des Ur-
	sprungsbaums mit Hilfe der übergebenen Funktion erzeugt werden.*/
	
	public <R> Tree<R> mapTree(java.util.function.Function<E, R> f, Tree<R> newTree)
	{
		for(Tree<E> child:children)
		{
			Tree<R> tempTree = new Tree<R>();
			tempTree.isNil =false;
			tempTree.elem = f.apply(child.elem);
			newTree.children.add(tempTree);
			((Tree<E>)child).mapTree(f, tempTree);
		}
		return newTree;
	}
	
	public void writeAsXML(java.io.Writer out, int dummy) throws IOException
	{
		if (!isNil){
			out.write("<name>" + elem.toString() + "</name> \n"); 
			for (Tree<E> child:children){
				if(children.size() > 0){
					out.write("<child>\n");
				}
    			child.writeAsXML(out, 1);
    			if(children.size() > 0){
    				out.write("</child>\n");
    			}
    		}
    	}
	}
	
	public void writeAsXML(java.io.Writer out) throws IOException
	{
		out.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
		out.write("<person>\n");
		writeAsXML(out, 1);
		out.write("</person>\n");
	}
	
	public static Tree<String> readFromXML(java.io.File xmlFile) throws Exception
	{
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder parser = factory.newDocumentBuilder();
		Document doc = parser.parse(xmlFile);
		Element root = doc.getDocumentElement();


		return buildStringTree(root.getFirstChild());	
	}

	private static Tree<String> buildStringTree(Node node) {
		NodeList childList = node.getChildNodes();	//every node has his name and his childnodes in his childList
		int listLength = childList.getLength();	//important for the loop

//		Tree<String> stringTree = new Tree<>(childList.item(0).getTextContent());	/*first child always the name
//		-> interesting for the String Tree*/
//		for(int i = 1; i < listLength; i++) {	
//			stringTree.childNodes.add(buildStringTree(childList.item(i)));	/*other elements of thechildNode List are the real children */
//		}


		return null; // stringTree;
	}
	
	static public void main(String[] args){
    	Tree<String> windsor
    		= new Tree<>("Vater", 
    				new Tree<>("Kind mit Kindern", 
    						new Tree<> ("Kindeskind")), 
    				new Tree<>("Kind ohne Kinder"));
//    		= new Tree<>("George"
//    			,new Tree<>("Elizabeth"
//				     ,new Tree<>("Charles"
//						 ,new Tree<>("William"
//								 ,new Tree<>("George")
//							     )
//						 ,new Tree<>("Harry")
//						 )
//				     ,new Tree<>("Anne")
//				     ,new Tree<>("Andrew")
//				     ,new Tree<>("Edward")
//				     )
//			 ,new Tree<>("Margret")
//			 ) ;
	System.out.println(windsor.size());
	windsor.fuerAlle(x ->  System.out.println(x));
	System.out.println("############################");
	
	List<String> liste = new ArrayList<>();
	liste = windsor.fringe();
	System.out.println(liste + "\n");
	System.out.println(windsor.pathTo("Margret"));
	System.out.println(windsor.contains((String s)->{return s.startsWith("G");}));
	
	try {
		Writer writer = new FileWriter("test.xml");
		windsor.writeAsXML(writer);
		writer.close();
	} catch (IOException e) {
		e.printStackTrace();
	}
	
	try {
		Tree<String> xmlToTreeTree = new Tree<>();
		File xmlFile = new File("test.xml");
		xmlToTreeTree = readFromXML(xmlFile);
		//System.out.println(xmlToTreeTree.toString());
	} catch (Exception e) {
		// TODO Auto-generated catch block
		e.printStackTrace();
	}
    }

}