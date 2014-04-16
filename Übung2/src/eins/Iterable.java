package eins;

import eins.Append;
import eins.TwoDimIterable;
import eins.PairIterable;
import java.util.Iterator;

public interface Iterable<A> extends java.lang.Iterable<A>{
  public Iterator<A> iterator();

  public default boolean empty(){
    return !iterator().hasNext();
  }

  public default A head(){
     return iterator().next();
  }

  public  default Iterable<A> tail(){
      return ()->{
           Iterator<A> result = iterator(); 
           result.next();
           return result;
      };
  }

  //because trust noone
  public  default int length(){
    return empty() ? 0 : 1+tail().length();
  }

  public static <A> Iterable<A> nil(){
    return ()->{
        return new Iterator<A>(){
          public boolean hasNext(){return false;}
          public A next(){return null;}
        };  
    };
  }

  public default Iterable<A> cons(final A hd){
    final Iterable<A> tl = this;
    return new Iterable<A>(){
      public Iterator<A> iterator(){
        final java.util.Iterator<A> it = tl.iterator();
        final A first = hd;
        return new Iterator<A>(){
          boolean firstCall = true;
          public boolean hasNext(){return firstCall||it.hasNext();}
          public A next(){
            if (firstCall){
              firstCall = false;
              return first;
            }else {
              return it.next();
            }
          }
        };  
      }
    };
  }

  public static <A> Iterable<A> cons(A hd,final java.util.function.Supplier<Iterable<A>> tl){
    return new Iterable<A>(){
      public Iterator<A> iterator(){
        final A first = hd;
        return new Iterator<A>(){
          java.util.Iterator<A> it = null;
          boolean firstCall = true;
          public boolean hasNext(){return firstCall || it.hasNext();}
          public A next(){
            if (firstCall){
              firstCall = false;
              return first;
            }else {
              if (it==null) it=tl.get().iterator();
              return it.next();
            }
          }
        };  
      }
    };
  }

  public default Iterable<A> filter(java.util.function.Predicate<A> p){
    if (empty()) return this;
    if (p.test(head())) return tail().filter(p).cons(head());
    return tail().filter(p);
  }


  public default <B> Iterable<B> map(java.util.function.Function<A,B> f){
    if (empty()) return nil();
    return tail().map(f).cons(f.apply(head()));
  }

  public default A reduce(A start,java.util.function.BinaryOperator<A> op){
    if (empty()) return start;
    return op.apply(head(),tail().reduce(start,op));
  }
  
  
  	public default Iterable<A> append(java.lang.Iterable<A> that){
		return new Append<A>(this, (Iterable<A>) that);
	}

  	public default <B> Iterable<Pair<A,B>> zip(java.lang.Iterable<B> that){
		return new PairIterable<A,B>(this, (Iterable<B>) that);
  	}
  	
  	public default <B> Iterable<Pair<A,B>> cross(java.lang.Iterable<B> that){
  		return new TwoDimIterable<A,B>(this, (Iterable<B>) that);
  	}
  	
	public default String asString(){
		StringBuilder builder = new StringBuilder();
		for(A t : this) {
			builder.append(t);
			builder.append(" ");
		}
		return builder.toString();
	}
}

