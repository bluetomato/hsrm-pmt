package ü1;import java.util.Iterator;

public class Lines implements Iterator <String>,Iterable<String> {
    
    String string;
    String[] strings;
    static int count;
    Lines(String string){
        this.string = string;
        this.count = 0;
        this.strings= string.split("\n");
    }
    
    @Override
    public boolean hasNext() {
        return count < strings.length;
    }

    @Override
    public String next() {
        String result = strings[count];
        count++;
        return result;
    }

    @Override
    public void remove() {
        
    }

    @Override
    public Iterator<String> iterator() {
        return this;
    }
    
    public static void main(String[] args) {
    	  for (String s : new Lines("Test"+"\n"+"Test"+"\n"+"Test"+"\n")){
              System.out.println(count);
          }
    	
	}
    
}