
public class GeradeZahlenIterierer2
         implements GenerischerIterierer<Integer>{
  int from;
  int to;
  GeradeZahlenIterierer2(int from, int to){
    this.from = from;
    this.to = to;
  }
  public boolean schleifenTest(){
    return from < to;
  }
  public void schleifeWeiterschalten(){
    from = from + 2;
  }
  public Integer schleifenWert(){
    return from;
  }

  public static void main(String[] args){
    for (GenerischerIterierer<Integer> it 
           = new GeradeZahlenIterierer2(0,10)
        ; it.schleifenTest()
        ; it.schleifeWeiterschalten()){      
      int i = (int) it.schleifenWert();
      System.out.println(i);
    } 
  }
}

