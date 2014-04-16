package ü1;

public class Start {
    public static void main (String[] args){
        System.out.println("Hallo Welt");
        new Thread(
                () -> System.out.println("Test")
        ).start();
        for (Integer x : new IntRange(0,5,1)){
            System.out.println(x+"");
            
        }
        /*for (Integer x : new Fib()){
            System.out.println(x+"");
        }*/
        
        for (Character c : new IterableString("Programmiermethoden")){
            System.out.println(c);
        }
        
        for (String s : new Lines("Test"+"\n"+"Test"+"\n"+"Test"+"\n")){
            System.out.print(s);
        }
        for (Integer i : new Random (10,1,1,0)){
            System.out.println(""+i);
        }
    }
}