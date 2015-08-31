/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;
import java.math.*;

/* Name of the class has to be "Main" only if the class is public. */
public class divisions
{

    ArrayList<Long> prime = new ArrayList<Long>();
    long MAXN = 10000007;
	boolean is[] = new boolean [10000010];

    public long SumDiv(long n){
        int k = 0;
		long ans = 1 , otro = (long) prime.get(0);
		
		while( k<prime.size() && otro<=(long)Math.sqrt(n) ){
			long power = 0;
			while(n%otro==0){
				n = n/otro;
				power++;
			}
			
			ans = ans * (power+1);
			k++;
			if(k<prime.size()) otro = (long) prime.get(k);
		}

        return ans;
    }

    public void Criba(){
		
		prime.add((long)2);
		for(int i = 4;i<MAXN;i+=2)
			is[i] = true;
		
		
		long aux = (long)Math.sqrt(MAXN);
		for(long i=3;i<=MAXN;i+=2)
			if(!is[(int)i]){
				prime.add(i);
				for(long j=i*i;j<=MAXN;j+=i)
					is[(int)j] = true;
			}
    }

    public long Regresa(long n){
        int k = 0;
		long otro = (long) prime.get(0);
		
		while( k<prime.size() && otro<=(long)Math.sqrt(n) ){
			while(n%otro==0) n = n/otro;
			k++;
			if(k<prime.size()) otro = (long) prime.get(k);
		}
        return n;
    }

	public static void main (String[] args) throws java.lang.Exception{
		Scanner sc = new Scanner( System.in );
        divisions thisi = new divisions();
		thisi.Criba();		
		long n = sc.nextLong();
        if(n==1){
            System.out.println(1);
            return;
        }

		long ans = thisi.SumDiv(n);
        n = thisi.Regresa(n);
		
		if(n<=thisi.MAXN){
			if(n!=1) ans *= 2;
			System.out.println(ans);
		}else{
			if(n>1){
				BigInteger aux2 = new BigInteger("0").valueOf(n);
				BigInteger aux3 = new BigInteger("0").valueOf( (long)Math.sqrt(n) );
				BigInteger aux4 = aux3.multiply(aux3);
				if(aux2.isProbablePrime(10)) ans = ans*2;
				else if(aux4.equals(aux2)) ans = ans*3;
				else ans = ans * 4;
			}
			
			System.out.println(ans);
		}
		
	}
}
