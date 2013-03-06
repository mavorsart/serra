class Irrigazione{
  public:
    //costruttore
    Irrigazione(int oraA, int minA, int oraF, int minF, int dow); 
  //funzioni dichiarate public
  private:
    int oraA;
    int minA;
    int oraF;
    int minF;
    int dow;
};
//definizione del costruttore
    Irrigazione::Irrigazione(int oA, int mA, int oF, int mF, int d)
    {
       oraA=oA;
       minA=mA;
       oraF=oF;
       minF=mF;
       dow=d;
    }



