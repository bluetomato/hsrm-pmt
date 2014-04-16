import java.util.Iterator;

public class IntegerRange implements Iterable<Integer>{
  int from;
  int to;
  int step;

  public IntegerRange(int from, int to, int step){
    this.from = from;
    this.to = to;
    this.step = step;
  }

  public IntegerRange(int from, int to){
    this(from, to, 1);
  }  
  public IntegerRange(int from){
    this(from, Integer.MAX_VALUE, 1);
  }

  public Iterator<Integer> iterator(){
    return new IntegerRangeIterator(from,to,step);
  }

  private static class IntegerRangeIterator implements Iterator<Integer>{
    int from;
    int to;
    int step;

    IntegerRangeIterator(int from, int to, int step){
      this.from = from;
      this.to = to;
      this.step = step;
    }
    public boolean hasNext(){
      return from < to;
    }
    public Integer next(){
      int result  = from;
      from = from + step;
      return result;
    }
    public void remove(){}
  }
}

