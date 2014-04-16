package ü1;

public class Pair<A,B>{
    A obj1;
    B obj2;
    
    Pair(A obj1, B obj2){
        this.obj1=obj1;
        this.obj2 = obj2;
    }
    @Override
    public String toString(){
        return this.obj1.toString()+" "+this.obj2.toString();
    }
}