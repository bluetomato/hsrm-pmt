
public class GeradeZahlenKleiner10Iterierer{
  int i; //die Schleifenvariable
  GeradeZahlenKleiner10Iterierer(int i){
    this.i = i; //Initialisierung der Schleifenvariable
  }
  boolean schleifenTest(){
    return i < 10; //Test ueber die Schleifenvariable
  }
  void schleifeWeiterschalten(){
    i = i + 2; //fuer naechsten Schleifendurchlauf
  }

  int schleifenWert(){
    return i;
  }

  public static void main(String[] args){
    for (GeradeZahlenKleiner10Iterierer it 
          = new GeradeZahlenKleiner10Iterierer(0)
        ; it.schleifenTest()
        ; it.schleifeWeiterschalten()){      
      System.out.println(it.schleifenWert());
    } 
  }
}

