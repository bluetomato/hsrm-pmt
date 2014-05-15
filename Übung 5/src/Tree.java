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
import org.w3c.dom.NodeList;

class Tree<E>{
	E elem;
	boolean isNil;
    List<Tree<E>> children = new ArrayList<>();

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
	
	public void writeAsXML(java.io.Writer out) throws IOException
	{
		if (!isNil){
    		for (Tree<E> child:children){
    			child.writeAsXML(out);
    		}
    		out.write(elem.toString());
    	}
		
	}

    static public void main(String[] args){
    	Tree<String> windsor
    		= new Tree<>("George"
    			,new Tree<>("Elizabeth"
				     ,new Tree<>("Charles"
						 ,new Tree<>("William"
								 ,new Tree<>("George")
							     )
						 ,new Tree<>("Harry")
						 )
				     ,new Tree<>("Anne")
				     ,new Tree<>("Andrew")
				     ,new Tree<>("Edward")
				     )
			 ,new Tree<>("Margret")
			 ) ;
	System.out.println(windsor.size());
	windsor.fuerAlle(x ->  System.out.println(x));
	System.out.println("############################");
	
	List<String> liste = new ArrayList<>();
	liste = windsor.fringe();
	System.out.println(liste + "\n");
	System.out.println(windsor.pathTo("Margret"));
	System.out.println(windsor.contains((String s)->{return s.startsWith("G");}));
	
	try {
		Writer writer = new FileWriter("test.txt");
		windsor.writeAsXML(writer);
		writer.close();
	} catch (IOException e) {
		e.printStackTrace();
	}
	
	System.out.println();
    }

}