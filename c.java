/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

/* Name of the class has to be "Main" only if the class is public. */
public class cake{

    boolean Igual(BigDecimal a, BigDecimal b) { 
        return a.equals(b);
    }

    BigDecimal Cruz(Punto v, Punto w) {
        return v.x.multiply(w.y).subtract(v.y.multiply(w.x));
    }

    public Punto Trasladar(Punto o, Punto p) {
        return new Punto( p.x.subtract(o.x), p.y.subtract(o.y) );
    }

    int ManoDerecha(Punto o, Punto p, Punto q) {
        BigDecimal ccw = Cruz(Trasladar(o, p), Trasladar(o, q));
        return Igual(ccw, BigDecimal.ZERO)? 0: (ccw.compareTo(BigDecimal.ZERO)==-1)? -1: 1;
    }

    Poligono CercoConvexo(Poligono P){
        // Si el poligono ya esta ordenado no usar sort
        P.Ordenar();
        Poligono arriba = new Poligono(), abajo = new Poligono();
        for (int i = 0; i < P.size(); ++i) {
            while (arriba.size() > 1) {
                int p = arriba.size() - 1;
                if (ManoDerecha(arriba.obtener(p - 1),
                    arriba.obtener(p), P.obtener(i) ) < 0) break;
                arriba.borra();
            }
            arriba.inserta(P.obtener(i));
        }
        arriba.borra();
        for (int i = P.size() - 1; i >= 0; --i) {
            while (abajo.size() > 1) {
                int p = abajo.size() - 1;
                if (ManoDerecha(abajo.obtener(p - 1),
                    abajo.obtener(p), P.obtener(i) ) < 0) break;
                abajo.borra();
            }
            abajo.inserta(P.obtener(i));
        }
        arriba.insertar(abajo);
        return arriba;
    }    

    public Punto Escalar(Punto v,BigDecimal s) {
        return new Punto( v.x.multiply(s), v.y.multiply(s) );
    }

    Punto Opuesto(Punto v){
        return new Punto(v.x.negate(), v.y.negate());
    }

    public Punto Hazlo(Punto a,Punto b,BigDecimal s){
        return Trasladar( Opuesto(a) , Escalar( Trasladar( a , b ) , s ) );
    }

    public int compareToo(BigDecimal a,BigDecimal b){
        if(a.subtract(b).abs().compareTo(new BigDecimal("0.000000000000000000000000000000000000000000001"))<=0) return 0;
        return a.compareTo(b);
    }

    public long busbin(long ini,long fin,BigDecimal total,Poligono p,boolean flag){
        long v = fin;
        long med;
        while(ini<fin){
            med = ( ini + fin ) / 2;

            Poligono aux = new Poligono();
            Punto a = new Punto();
            int u = p.size()-2;

            for(int i=0;i<p.size();i++){
                BigDecimal s = BigDecimal.ONE.divide(
                    new BigDecimal(med).divide(
                        new BigDecimal("10000.0") , 100 ,BigDecimal.ROUND_HALF_UP ) , 100 ,BigDecimal.ROUND_HALF_UP);
                s = BigDecimal.ONE.subtract(s);
                if(i==0) a = Hazlo( p.obtener(i) , p.obtener(u) , s );
                else a = Hazlo( p.obtener(i) , p.obtener(i-1) , s );
                aux.inserta(a);

                a = new Punto();
                s = BigDecimal.ONE.subtract(s);
                if(i==0) a = Hazlo( p.obtener(i) , p.obtener(u) , s );
                else a = Hazlo( p.obtener(i) , p.obtener(i-1) , s );
                aux.inserta(a);
            }

            Poligono aux2 = new Poligono();
            aux2 = CercoConvexo( aux );
            BigDecimal a1 = aux2.Area();
            aux = new Poligono();
            for(int i=0;i<p.size();i++){
               BigDecimal s = BigDecimal.ONE.divide(
                    new BigDecimal(med+1).divide(
                        new BigDecimal("10000.0") , 100 ,BigDecimal.ROUND_HALF_UP ) , 100 ,BigDecimal.ROUND_HALF_UP);
                s = BigDecimal.ONE.subtract(s);

                s = BigDecimal.ONE.subtract(s);
                if(i==0) a = Hazlo( p.obtener(i) , p.obtener(u) , s );
                else a = Hazlo( p.obtener(i) , p.obtener(i-1) , s );
                aux.inserta(a);

                a = new Punto();
                s = BigDecimal.ONE.subtract(s);
                if(i==0) a = Hazlo( p.obtener(i) , p.obtener(u) , s );
                else a = Hazlo( p.obtener(i) , p.obtener(i-1) , s );
                aux.inserta(a);
            }
            aux2 = new Poligono();
            aux2 = CercoConvexo( aux );
            BigDecimal a2 = aux2.Area();
            //System.out.println( med + " " + a1 + " " + a2 + " == " + total );

            if(flag==false){
                if( compareToo(a2,a1)>0) fin = med - 1;
                else if(compareToo(a2,total)!=1 && med+1<=v) ini = med+1;
                else if(compareToo(a1,total)!=1 ) return med;
                else fin = med - 1;
            }
            else{
                if(compareToo(a1,a2)>0) ini = med + 1;
                else if(compareToo(a2,total)!=1 && med+1<=v) ini = med+1;
                else if(compareToo(a1,total)!=1) return med;
                else fin = med - 1;
            }

        }
        return ini;
    }

    double Distancia(Punto p, Punto q) {
        return Math.hypot(p.x.doubleValue() - q.x.doubleValue(), p.y.doubleValue() - q.y.doubleValue());
    }

	public static void main (String[] args) throws java.lang.Exception{
		Scanner sc = new Scanner( System.in );
        BigDecimal r;
        cake programa = new cake();
        int n;
        Poligono p = new Poligono();
        r = sc.nextBigDecimal();
        n = sc.nextInt();

        for(int i=0;i<n;i++){
            Punto a = new Punto();
            a.x = sc.nextBigDecimal();
            a.y = sc.nextBigDecimal();
            p.inserta(a);
        }
        p.inserta(p.obtener(0));

        BigDecimal total = p.Area().multiply(r);

        double otro = 1000.0;
        for(int i=0;i<n;i++)
            otro = Math.min( otro , programa.Distancia( p.obtener(i) , p.obtener(i+1) ) );

        long uno = programa.busbin( 2000 , 100000000L , total , p , false);
        long dos = programa.busbin( 2000 , 100000000L , total , p , true );
        uno = Math.max( uno , dos );
        BigDecimal u = new BigDecimal( uno ).divide( new BigDecimal("10000.0") , 6 , BigDecimal.ROUND_HALF_UP);

        System.out.println( u );
	}
}

class Poligono{
    ArrayList<Punto> p;

    Poligono(){
        p = new ArrayList<Punto>();
    }

    public BigDecimal Cruz(Punto v,Punto w){
        return v.x.multiply(w.y).subtract(v.y.multiply(w.x));
    }

    public void inserta(Punto a){
        p.add(a);
    }

    public Punto obtener(int i){
        return p.get(i);
    }

    public BigDecimal Area() {
        BigDecimal area = BigDecimal.ZERO;
        for (int i = 1; i < p.size(); ++i)
            area = area.add(this.Cruz(p.get(i - 1), p.get(i)));
        return area.divide(new BigDecimal("2.0") , 100 , BigDecimal.ROUND_HALF_UP).abs();
    }

    public int size(){
        return p.size();
    }

    public void Limpia(){
        p.clear();
    }

    public void borra(){
        p.remove( p.size() - 1 );
    }

    public void insertar(Poligono a){
        for(int i=0;i<a.size();i++)
            p.add(a.obtener(i));
    }

    public void Ordenar() {
        Collections.sort(p , new Punto.Comp());
    }
}

class Punto{
    BigDecimal x, y;

    Punto(){
         x = BigDecimal.ZERO;
         y = x;
    }

    Punto(BigDecimal x_ , BigDecimal y_){
        x = x_;
        y = y_;
    }

    public static class Comp implements Comparator<Punto> {
        public int compare(Punto a, Punto b){
            if(a.x.compareTo(b.x)!=0) return a.x.compareTo(b.x);
            return a.y.compareTo(b.y);
        }
    }

    public String toString(){
        return x.toString() + " , " + y.toString();
    }
}
