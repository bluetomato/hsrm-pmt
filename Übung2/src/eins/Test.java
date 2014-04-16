package eins;

public class Test {
	public static void main(String[] args){
		ArrayListe<Integer> a = new ArrayListe<>(1, 17, 3, 32);
		ArrayListe<Integer> b = new ArrayListe<>(2, 4);
		ArrayListe<Integer> ys = new ArrayListe<>(2, 4);
		
		System.out.println("___________________________________________");
		System.out.println("asString & add von einzelnen Elementen:");
		ArrayListe<String> cs = new ArrayListe<>();
		cs.add("H");
		cs.add("a");
		cs.add("l");
		cs.add("l");
		cs.add("o");
		cs.add(" ");
		cs.add("d");
		cs.add("u");
		cs.add("d");
		cs.add("a");
		cs.add("!");
		cs.add("!");
		//cs.add(2); //Integer hinzufügen geht nicht
		System.out.println(cs.asString() + "\n");
		
		System.out.println("___________________________________________");
		System.out.println("Hinzufügen von mehreren Elementen:");
		
		ArrayListe<Integer> xs = new ArrayListe<>(1, 17, 3, 32); //hinzufügen von mehreren Elementen
		System.out.println(xs.asString() + "\n");
		
		System.out.println("___________________________________________");
		System.out.println("Append:");
		System.out.println("Liste 1: " + xs.asString());
		System.out.println("Liste 2: " + ys.asString() + "\n");
		
		for(Integer i : xs.append(ys)){
			System.out.println(i);
		}
		
		System.out.println("___________________________________________");
		System.out.println("Zip:");
		System.out.println("Liste 1: " + a.asString());
		System.out.println("Liste 2: " + b.asString() + "\n");
		
		Iterable<Pair<Integer,Integer>> c = a.zip(b);
		for(Pair<Integer, Integer> i : c){
			System.out.println(i.a + " " + i.b);
		}
		

		System.out.println("___________________________________________");
		System.out.println("Cross:");
		b.add(8);
		System.out.println("Liste 1: " + a.asString());
		System.out.println("Liste 2: " + b.asString() + "\n");
		
		Iterable<Pair<Integer,Integer>> d = a.cross(b);
		for(Pair<Integer, Integer> i : d){
			System.out.println(i.a + " " + i.b);
		}
	}

}
