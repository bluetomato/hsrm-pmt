package ü1;



import java.util.Iterator;

public class Fib implements Iterator <Integer>, Iterable <Integer>{
    
    int number1 = 1;
    int number2 = 0;
    
    @Override
    public boolean hasNext() {
        return true;
    }

    @Override
    public Integer next() {
        int result = number1+number2;
        number1=number2;
        number2=result;
        return result;
    }

    @Override
    public void remove() {
       
    }

    @Override
    public Iterator<Integer> iterator() {
        return this;
    }
    
}