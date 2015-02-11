import java.io.*;
import java.util.*;

public class Scan{

	BufferedReader buffer;
	StringTokenizer tok;

	Scan(){
		buffer = new BufferedReader(new InputStreamReader(System.in));
	}

	boolean hasNext(){
		while(tok==null || !tok.hasMoreElements()){
			try{
				tok = new StringTokenizer(buffer.readLine());
			}catch(Exception e){
				return false;
			}
		}
		return true;
	}

	String next(){
		if(hasNext()) return tok.nextToken();
		return null;
	}

	String nextLine(){
		if(hasNext()) return tok.nextToken("\n");
		return null;
	}

	int nextInt(){
		return Integer.parseInt(next());
	}

	long nextLong(){
		return Long.parseLong(next());
	}

	double nextDouble(){
		return Double.parseDouble(next());
	}
}
